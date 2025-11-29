#include "plugincontroller.h"

using namespace Steinberg;
using namespace Steinberg::Vst;

tresult PLUGIN_API RvcController::initialize(FUnknown* context) {
    return EditController::initialize(context);
}
