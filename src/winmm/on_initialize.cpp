#include "dllextern.h"
#include "process.h"

void onInitialize() {
    setDllFuncAddress();
}

BOOL isNB7GameInitialized = FALSE;
void onGameInitialize() {
    OutputDebugString("将星録の開始\n");
    MessageBoxA(NULL, "見つけた", "見つけた", NULL);
}

const char* NB7_CLASS_NAME = "信長の野望･将星録 パワーアップキット";

BOOL isFirstMciSendCommand = FALSE;
void onMciSendCommand() {
    // mciSendCommandAをこのプロセスにて初めて実行する際のみチェックする。最初の１回目で必ず正しく検証できる。
    // 音ならず度に毎回ウィンドウを探すようなことのないように。
    if (!isFirstMciSendCommand && isTargetProcess) {
        if (!isNB7GameInitialized) {
            if (IsMatchCurrentClass(NB7_CLASS_NAME)) {
                onGameInitialize();
                isNB7GameInitialized = TRUE;
            }
		}
    }

    isFirstMciSendCommand = TRUE;
}