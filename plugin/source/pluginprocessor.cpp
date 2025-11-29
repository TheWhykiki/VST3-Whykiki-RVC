#include "pluginprocessor.h"
#include "modelmanager.h"
#include <string>
#include "public.sdk/source/vst/vstparameters.h"
#include <thread>
#include <chrono>
#include "public.sdk/source/vst/vstbus.h"

using namespace Steinberg;
using namespace Steinberg::Vst;

RvcProcessor::RvcProcessor() {
    setControllerClass(ControllerUID);
}

// handleBlock: called when ring buffer is filled with blockSize samples per channel
void RvcProcessor::handleBlock(const float* inL, const float* inR) {
    // Perform RVC inference on a full block of samples
    std::vector<float> outL(blockSize), outR(blockSize);
    rvcModel.process(inL, inR, outL.data(), outR.data(), blockSize);
    // Store processed samples for output playback
    for (int32 i = 0; i < blockSize; ++i) {
        processedBuffer[i * 2 + 0] = outL[i];
        processedBuffer[i * 2 + 1] = outR[i];
    }
    blockReady = true;
    readPos = 0;
}

RvcProcessor::~RvcProcessor() {}

tresult PLUGIN_API RvcProcessor::initialize(FUnknown* context) {
    tresult result = AudioEffect::initialize(context);
    if (result != kResultOk)
        return result;
    addAudioInput(USTRING("Stereo In"), SpeakerArr::kStereo);
    addAudioOutput(USTRING("Stereo Out"), SpeakerArr::kStereo);
    // prepare buffers for block-based processing
    ringBuffer.assign(blockSize * 2, 0.0f);
    processedBuffer.assign(blockSize * 2, 0.0f);
    writePos = 0;
    readPos = 0;
    blockReady = false;
    // Load RVC model (adjust path to actual model file in assets/models)
    rvcModel.loadModel("assets/models/rvc_model.onnx");
    // Start RVC API server and trigger conversion automatically
    {
        // Launch FastAPI server
        std::system("nohup python3 ../../external/rvc-webui/api_240604.py >/dev/null 2>&1 &");
        std::this_thread::sleep_for(std::chrono::seconds(2));
        // Configure and start conversion via HTTP
        std::system("curl -s -X POST -H 'Content-Type: application/json' -d '{\"pth_path\":\"assets/models/rvc_model.onnx\",\"index_path\":\"assets/models/rvc_model.onnx\"}' http://127.0.0.1:6242/config");
        std::system("curl -s -X POST http://127.0.0.1:6242/start");
    }
    return kResultOk;
}

tresult PLUGIN_API RvcProcessor::process(ProcessData& data) {
    if (data.numInputs == 0 || data.numOutputs == 0)
        return kResultOk;
    auto in = data.inputs[0].channelBuffers32;
    auto out = data.outputs[0].channelBuffers32;
    for (int32 i = 0; i < data.numSamples; ++i) {
        // accumulate input into ring buffer
        ringBuffer[writePos * 2 + 0] = in[0][i];
        ringBuffer[writePos * 2 + 1] = in[1][i];
        writePos++;
        if (writePos >= blockSize) {
            // full block reached, run inference
            handleBlock(&ringBuffer[0], &ringBuffer[1]);
            writePos = 0;
        }
        // output either processed block or passthrough
        float left = in[0][i];
        float right = in[1][i];
        if (blockReady) {
            left = processedBuffer[readPos * 2 + 0];
            right = processedBuffer[readPos * 2 + 1];
            readPos++;
            if (readPos >= blockSize)
                blockReady = false;
        }
        out[0][i] = left;
        out[1][i] = right;
    }
    return kResultOk;
}

tresult PLUGIN_API RvcProcessor::terminate() {
    // Stop conversion and shut down API server
    std::system("curl -s -X POST http://127.0.0.1:6242/stop");
    std::system("pkill -f api_240604.py");
    return AudioEffect::terminate();
}
