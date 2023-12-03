#include <Windows.h>

#include <fstream>
#include <iostream>
#include <vector>
#include <windows.h>
#include "output_debug_stream.h"

// ��̉摜�͕���64, ������80�B�}�W�b�N�i���o�[�ɂȂ��Ă��܂����A����ύX�ɂȂ�����͉i�v�ɂ��Ȃ����߁A���̂܂ܖ��ߍ��ށB(�������̕����萔���g�����킩��₷��)

struct KAO_PICLINE {
    BYTE at[64];
};
struct KAO_PICTURE {
    KAO_PICLINE line[80];
};

KAO_PICTURE picfileOrigin = { 0 };
KAO_PICTURE picflipSidePp = { 0 };

bool fileExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good(); // �t�@�C�������݂����true��Ԃ�
}
extern int nTargetKaoID;
BOOL Hook_ReadFileCustom(
    HANDLE hFile, // �t�@�C���̃n���h��
    LPVOID lpBuffer, // �f�[�^�̊i�[��
    DWORD nNumberOfBytesToRead, // �ǂݍ��ރo�C�g��
    LPDWORD lpNumberOfBytesRead, // ���ۂɓǂݍ��񂾃o�C�g��
    LPOVERLAPPED lpOverlapped // �I�[�o�[���b�v�\���̂̃|�C���^
) {

    char filenameBuf[512] = "";
    sprintf_s(filenameBuf, "KAODATA\\%04d.bmp", nTargetKaoID);
    OutputDebugStream("�������͂��邩�H%s\n" ,filenameBuf);
    std::string filename = filenameBuf;
    if (!fileExists(filename)) {
        return FALSE;
    }

    std::ifstream file(filename, std::ios::binary);

    if (!file) {
        OutputDebugStream("�t�@�C��" + filename + "���J�����Ƃ��ł��܂���ł����B\n");
        return FALSE;
    }

    file.seekg(-(64 * 80), std::ios::end);

    std::vector<char> buffer(64 * 80);
    file.read(buffer.data(), buffer.size());

    if (file.fail()) {
        OutputDebugStream("�t�@�C��" + filename + "�̓ǂݍ��݂Ɏ��s���܂����B\n");
        return FALSE;
    }

    // ���̉摜���R�s�[
    if (nNumberOfBytesToRead == buffer.size()) {
        memcpy(&picfileOrigin, buffer.data(), buffer.size());

        // �㉺���]�������̂� picfileOrigin��picflipSidePp �ɃR�s�[
        for (int i = 0; i < 80; i++) {
            memcpy(&(picflipSidePp.line[79 - i]), &(picfileOrigin.line[i]), 64);
        }

        memcpy(lpBuffer, &picflipSidePp, 64 * 80);
    }


    return TRUE;
}
