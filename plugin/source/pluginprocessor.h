#pragma once
#include "version.h"
#include "public.sdk/source/vst/vstaudioeffect.h"
#include <vector>
#include "modelmanager.h"

namespace Steinberg {
namespace Vst {

class RvcProcessor : public AudioEffect
{
public:
    RvcProcessor();
    ~RvcProcessor() SMTG_OVERRIDE;

    static FUnknown* createInstance(void*) { return (IAudioProcessor*)new RvcProcessor(); }

    tresult PLUGIN_API initialize(FUnknown* context) SMTG_OVERRIDE;
    tresult PLUGIN_API process(ProcessData& data) SMTG_OVERRIDE;
    tresult PLUGIN_API terminate() SMTG_OVERRIDE;

private:
    /** RVC inference engine */
    RvcModel rvcModel;
    /** Ring buffer for accumulating audio samples into fixed-size blocks */
    std::vector<float> ringBuffer;
    /** Buffer for processed output block */
    std::vector<float> processedBuffer;
    int32 writePos = 0;
    int32 readPos = 0;
    bool blockReady = false;
    static constexpr int32 blockSize = 2048;
    void handleBlock(const float* inL, const float* inR);
    tresult PLUGIN_API setState(IBStream* state) SMTG_OVERRIDE { return kResultOk; }
    tresult PLUGIN_API getState(IBStream* state) SMTG_OVERRIDE { return kResultOk; }
};

} // namespace Vst
} // namespace Steinberg
