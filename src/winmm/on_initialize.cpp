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
    OutputDebugString("�����^�̊J�n\n");
    Mod_onGameInitialize(hNB7Wnd);

}

const char* NB7_CLASS_NAME = "�M���̖�]������^ �p���[�A�b�v�L�b�g";

BOOL isFirstMciSendCommand = FALSE;
void onMciSendCommand() {
    // mciSendCommandA�����̃v���Z�X�ɂď��߂Ď��s����ۂ̂݃`�F�b�N����B�ŏ��̂P��ڂŕK�����������؂ł���B
    // ���Ȃ炸�x�ɖ���E�B���h�E��T���悤�Ȃ��Ƃ̂Ȃ��悤�ɁB
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