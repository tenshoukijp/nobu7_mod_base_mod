#include "dllextern.h"
#include "process.h"
#include "loadmod.h"

void onInitialize() {

    setDllFuncAddress();

    loadNB7Mod();

    Mod_onInitialize();
}


BOOL isNB7GameInitialized = FALSE;
void onGameInitialize(HWND hNB7Wnd) {
    OutputDebugString("将星録の開始\n");
    Mod_onGameInitialize(hNB7Wnd);

}

const char* NB7_CLASS_NAME = "信長の野望･将星録 パワーアップキット";

BOOL isFirstMciSendCommand = FALSE;
void onMciSendCommand() {
    // mciSendCommandAをこのプロセスにて初めて実行する際のみチェックする。最初の１回目で必ず正しく検証できる。
    // 音ならず度に毎回ウィンドウを探すようなことのないように。
    if (!isFirstMciSendCommand && isTargetProcessing) {
        if (!isNB7GameInitialized) {
            HWND hNB7Wnd = GetNB7WindowHandle(NB7_CLASS_NAME);
            if (hNB7Wnd) {
                onGameInitialize(hNB7Wnd);
                isNB7GameInitialized = TRUE;
            }
		}
    }

    isFirstMciSendCommand = TRUE;
}