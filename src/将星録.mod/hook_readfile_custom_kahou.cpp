#include <Windows.h>

#include <fstream>
#include <iostream>
#include <vector>
#include <windows.h>
#include <string>
#include "output_debug_stream.h"
#include "file_attribute.h"
#include "game_screen.h"
#include "data_game_struct.h"

// �ƕ�̉摜�͕���64, ������64�B�}�W�b�N�i���o�[�ɂȂ��Ă��܂����A����ύX�ɂȂ�����͉i�v�ɂ��Ȃ����߁A���̂܂ܖ��ߍ��ށB(�������̕����萔���g�����킩��₷��)

struct KAHOU_PICLINE {
    BYTE at[64];
};
struct KAHOU_PICTURE {
    KAHOU_PICLINE line[64];
};

extern int iKahouIDOfLastShowKahouID;
extern int nTargetKahouGazouID;
BOOL Hook_ReadFileCustom_KahouPic(
    HANDLE hFile, // �t�@�C���̃n���h��
    LPVOID lpBuffer, // �f�[�^�̊i�[��
    DWORD nNumberOfBytesToRead, // �ǂݍ��ރo�C�g��
    LPDWORD lpNumberOfBytesRead, // ���ۂɓǂݍ��񂾃o�C�g��
    LPOVERLAPPED lpOverlapped // �I�[�o�[���b�v�\���̂̃|�C���^
) {
    if (nTargetKahouGazouID < 0) {
        return FALSE;
    }

    KAHOU_PICTURE picItemFileOrigin = { 0 };
    KAHOU_PICTURE picItemFlipSidePp = { 0 };

    std::string filename = "";

    if (isValidKahouID(iKahouIDOfLastShowKahouID)) {
        char filenameBuf[512] = "";
        sprintf_s(filenameBuf, "OVERRIDE\\ITEMDATA\\%s.bmp", nb7�ƕ���[iKahouIDOfLastShowKahouID].�ƕ�);
        OutputDebugStream("�������͂��邩�H%s\n", filenameBuf);
        if (isFileExists(filenameBuf)) {
            filename = filenameBuf;
        }
    }

    if (filename == "") {
        char filenameBuf[512] = "";
        sprintf_s(filenameBuf, "OVERRIDE\\ITEMDATA\\%03d.bmp", nTargetKahouGazouID);
        OutputDebugStream("�������͂��邩�H%s\n", filenameBuf);
        if (isFileExists(filenameBuf)) {
            filename = filenameBuf;
        }
    }

    if (filename == "") {
        return FALSE;
    }

    if (!isFileExists(filename)) {
        return FALSE;
    }

    std::ifstream file(filename, std::ios::binary);

    if (!file) {
        OutputDebugStream("�t�@�C��" + filename + "���J�����Ƃ��ł��܂���ł����B\n");
        return FALSE;
    }

    file.seekg(-(64 * 64), std::ios::end);

    std::vector<char> buffer(64 * 64);
    file.read(buffer.data(), buffer.size());

    if (file.fail()) {
        OutputDebugStream("�t�@�C��" + filename + "�̓ǂݍ��݂Ɏ��s���܂����B\n");
        return FALSE;
    }

    // ���̉摜���R�s�[
    if (nNumberOfBytesToRead == buffer.size()) {
        memcpy(&picItemFileOrigin, buffer.data(), buffer.size());

        // �㉺���]�������̂� picfileOrigin��picflipSidePp �ɃR�s�[
        for (int i = 0; i < 64; i++) {
            memcpy(&(picItemFlipSidePp.line[64 - 1 - i]), &(picItemFileOrigin.line[i]), 64);
        }

        memcpy(lpBuffer, &picItemFlipSidePp, (64 * 64));
    }


    return TRUE;
}
