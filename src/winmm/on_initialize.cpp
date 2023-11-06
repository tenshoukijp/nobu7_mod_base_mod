#include "dllextern.h"
#include "process.h"
#include "loadmod.h"

void onInitialize() {
    setDllFuncAddress();
}

BOOL isNB7GameInitialized = FALSE;
void onGameInitialize() {
    OutputDebugString("�����^�̊J�n\n");

    loadNB7Mod();

    Mod_onInitialize();

    Mod_onGameInitialize();

}


const char* NB7_CLASS_NAME = "�M���̖�]������^ �p���[�A�b�v�L�b�g";

BOOL isFirstMciSendCommand = FALSE;
void onMciSendCommand() {
    // mciSendCommandA�����̃v���Z�X�ɂď��߂Ď��s����ۂ̂݃`�F�b�N����B�ŏ��̂P��ڂŕK�����������؂ł���B
    // ���Ȃ炸�x�ɖ���E�B���h�E��T���悤�Ȃ��Ƃ̂Ȃ��悤�ɁB
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