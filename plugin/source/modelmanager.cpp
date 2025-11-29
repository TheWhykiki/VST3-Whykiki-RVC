#include "modelmanager.h"
#include <iostream>

RvcModel::RvcModel()
    : ortEnv(ORT_LOGGING_LEVEL_WARNING, "RVC"), sessionOptions() {
    sessionOptions.SetIntraOpNumThreads(1);
    // TODO: configure sessionOptions (execution providers, graph optimization)
}
RvcModel::~RvcModel() {}

bool RvcModel::loadModel(const std::string& modelPath) {
    std::cerr << "Loading RVC model from: " << modelPath << std::endl;
    try {
        session = std::make_unique<Ort::Session>(ortEnv, modelPath.c_str(), sessionOptions);
    } catch (const Ort::Exception& e) {
        std::cerr << "Failed to load ONNX model: " << e.what() << std::endl;
        return false;
    }
    return true;
}

void RvcModel::process(const float* inL, const float* inR, float* outL, float* outR, int blockSize) {
    // TODO: implement RVC inference; for now, pass-through
    for (int i = 0; i < blockSize; ++i) {
        outL[i] = inL[i];
        outR[i] = inR[i];
    }
}
