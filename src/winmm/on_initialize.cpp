#include "dllextern.h"
#include "process.h"
#include "loadmod.h"

void onInitialize() {
    setDllFuncAddress();
}

BOOL isNB7GameInitialized = FALSE;
void onGameInitialize() {
    OutputDebugString("将星録の開始\n");

    loadNB7Mod();

    Mod_onInitialize();

    Mod_onGameInitialize();

}


const char* NB7_CLASS_NAME = "信長の野望･将星録 パワーアップキット";

BOOL isFirstMciSendCommand = FALSE;
void onMciSendCommand() {
    // mciSendCommandAをこのプロセスにて初めて実行する際のみチェックする。最初の１回目で必ず正しく検証できる。
    // 音ならず度に毎回ウィンドウを探すようなことのないように。
    if (!isFirstMciSendCommand && isTargetProcessing) {
        if (!isNB7GameInitialized) {
            if (IsMatchCurrentClass(NB7_CLASS_NAME)) {
                onGameInitialize();
                isNB7GameInitialized = TRUE;
            }
		}
    }

    isFirstMciSendCommand = TRUE;
}