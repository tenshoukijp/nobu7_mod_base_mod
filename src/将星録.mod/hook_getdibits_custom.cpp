#include <windows.h>
#include "output_debug_stream.h"

int Hook_GetDIBitsCustom(
    HDC hdc, // �f�o�C�X�R���e�L�X�g�̃n���h��
    HBITMAP hbm, // �r�b�g�}�b�v�̃n���h��
    UINT start, // �X�L�������C���̍ŏ��̃C���f�b�N�X
    UINT cLines, // �X�L�������C���̐�
    LPVOID lpvBits, // �r�b�g�}�b�v�f�[�^�̃|�C���^
    LPBITMAPINFO lpbmi, // �r�b�g�}�b�v���̃|�C���^
    UINT usage // �r�b�g�}�b�v�̎g�p���@
) {

    return 1;
}