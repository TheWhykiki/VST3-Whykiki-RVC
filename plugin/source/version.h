#pragma once

#define PLUG_MFR "Whykiki"
#define PLUG_NAME "VST3RVC"
#define PLUG_VENDOR_ID "Wkki"
#define PLUG_CLASS_UID "12345678-1234-1234-1234-1234567890ab"
#define PLUG_CATEGORY "Instrument|Synth"
#define PLUG_VERSION_HEX 0x00010000
#define PLUG_VERSION_STR "0.1.0"
#define PLUG_DESCRIPTION "Real-time voice conversion via RVC"
#define PLUG_ENTRY_POINT RvcProcessor::createInstance
#define PLUG_VIEW_ENTRY_POINT RvcController::createInstance
#define SMTG_ALIGN 16
