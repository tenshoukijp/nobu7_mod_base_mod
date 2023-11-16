#include <windows.h>
#include "output_debug_stream.h"
#include "data_game_struct.h"
#include "on_serihu_message.h"
#include "data_turn_struct.h"
#include "bushou_albedo.h"
int prevMonth = -1;

BOOL Hook_BitBltCustom(
    HDC hdcDest, // �o�̓f�o�C�X�R���e�L�X�g�̃n���h��
    int nXDest,  // �o�͐�̒����`�̍������ x ���W
    int nYDest,  // �o�͐�̒����`�̍������ y ���W
    int nWidth,  // �o�͐�̒����`�̕��i�s�N�Z���P�ʁj
    int nHeight, // �o�͐�̒����`�̍����i�s�N�Z���P�ʁj
    HDC hdcSrc,  // ���̓f�o�C�X�R���e�L�X�g�̃n���h��
    int nXSrc,   // ���͌��̒����`�̍������ x ���W
    int nYSrc,   // ���͌��̒����`�̍������ y ���W
    DWORD dwRop  // ���X�^�I�y���[�V�����R�[�h
) {
    int month = �^�[�����.��;

    // �����ς������A�A���x�h�̃J�E���^�����Z�b�g����
    if (month != prevMonth) {
        prevMonth = month;
        resetAlbedoKoudouCounter();
        OutputDebugStream("�����ς�����̂ŃA���x�h�̃J�E���^�����Z�b�g���܂�\n");
    }
    /*
    OutputDebugStream("BitBlt\n");
    */
    return TRUE;
}


