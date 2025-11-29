#pragma once

#include <string>
#include <memory>
#include <onnxruntime_cxx_api.h>

/**
 * RvcModel encapsulates the RVC inference engine for real-time voice conversion.
 * Implements model loading and block-based processing.
 */
class RvcModel {
public:
    RvcModel();
    ~RvcModel();

    /**
     * Load the RVC model from the given file path.
     * @param modelPath filesystem path to the model file
     * @return true if loading succeeded, false otherwise
     */
    bool loadModel(const std::string& modelPath);

    /**
     * Perform voice conversion on a block of audio samples.
     * @param inL pointer to left-channel input samples
     * @param inR pointer to right-channel input samples
     * @param outL pointer to left-channel output samples buffer (blockSize samples)
     * @param outR pointer to right-channel output samples buffer (blockSize samples)
     * @param blockSize number of frames to process
     */
    void process(const float* inL, const float* inR, float* outL, float* outR, int blockSize);

private:
    // ONNX Runtime inference context
    Ort::Env ortEnv{ORT_LOGGING_LEVEL_WARNING, "RVC"};
    Ort::SessionOptions sessionOptions;
    std::unique_ptr<Ort::Session> session;
};
