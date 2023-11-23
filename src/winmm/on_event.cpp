#include "dllextern.h"
#include "process.h"
#include "loadmod.h"
#include "output_debug_stream.h"
#include "dllextern.h"
#include "loadmod.h"


void onInitialize() {

    setDllFuncAddress();

    loadNB7Mod();

    Mod_onInitialize();
}


void onMciSendCommand() {
}


void onFinalize() {
    freeNB7Mod();

    OutputDebugStream("«¯˜^‚ÌI—¹\n");
}