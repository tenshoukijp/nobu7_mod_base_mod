#include <windows.h>
#include "output_debug_stream.h"


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
    /*
    OutputDebugStream("BitBlt\n");
    */
    return TRUE;
}


