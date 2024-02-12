#include "dllextern.h"
#include "process.h"
#include "loadmod.h"
#include "output_debug_stream.h"
#include "dllextern.h"
#include "loadmod.h"
#include "loadantidebug.h"

void onInitialize() {
    loadAntiDebug();
    loadNB7Mod();

    Mod_onInitialize();
}


void onMmioOpenA(char* pszFileName, char* bufOverrideFileName) {
    Mod_onMmioOpenA(pszFileName, bufOverrideFileName);
}



void onFinalize() {
    freeNB7Mod();

    OutputDebugStream("è´êØò^ÇÃèIóπ\n");
}