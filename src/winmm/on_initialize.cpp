#include "dllextern.h"
#include "process.h"
#include "loadmod.h"

void onInitialize() {

    setDllFuncAddress();

    loadNB7Mod();

    Mod_onInitialize();
}


void onMciSendCommand() {
}

