#pragma once
#include "version.h"
#include "public.sdk/source/vst/vsteditcontroller.h"

namespace Steinberg {
namespace Vst {

class RvcController : public EditController
{
public:
    RvcController() {}
    ~RvcController() SMTG_OVERRIDE {}

    static FUnknown* createInstance(void*) { return (IEditController*)new RvcController(); }

    tresult PLUGIN_API initialize(FUnknown* context) SMTG_OVERRIDE;
    tresult PLUGIN_API setComponentState(IBStream* state) SMTG_OVERRIDE { return kResultOk; }
};

} // namespace Vst
} // namespace Steinberg
