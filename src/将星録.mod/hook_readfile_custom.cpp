#include <Windows.h>

#include <fstream>
#include <iostream>
#include <vector>
#include <windows.h>
#include "output_debug_stream.h"
#include "file_attribute.h"
#include "game_screen.h"

// ��̉摜�͕���64, ������80�B�}�W�b�N�i���o�[�ɂȂ��Ă��܂����A����ύX�ɂȂ�����͉i�v�ɂ��Ȃ����߁A���̂܂ܖ��ߍ��ށB(�������̕����萔���g�����킩��₷��)

struct KAO_PICLINE {
    BYTE at[64];
};
struct KAO_PICTURE {
    KAO_PICLINE line[80];
};

KAO_PICTURE picKaoFileOrigin = { 0 };
KAO_PICTURE picKaoFlipSidePp = { 0 };

bool fileExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good(); // �t�@�C�������݂����true��Ԃ�
}
extern int nTargetKaoID;
BOOL Hook_ReadFileCustom_BushouKao(
    HANDLE hFile, // �t�@�C���̃n���h��
    LPVOID lpBuffer, // �f�[�^�̊i�[��
    DWORD nNumberOfBytesToRead, // �ǂݍ��ރo�C�g��
    LPDWORD lpNumberOfBytesRead, // ���ۂɓǂݍ��񂾃o�C�g��
    LPOVERLAPPED lpOverlapped // �I�[�o�[���b�v�\���̂̃|�C���^
) {
    if (nTargetKaoID < 0) {
        return FALSE;
    }

    char filenameBuf[512] = "";
    std::string filename = "";
    int status = get�Q�[����ʃX�e�[�^�X();

    // �퓬���Ȃ� 0000_B.bmp �̂悤�ȃt�@�C�������݂���΂������D��Ŏg�����Ƃ����݂�
    if (status == �����^::��::�Q�[����ʃX�e�[�^�X::����� || status == �����^::��::�Q�[����ʃX�e�[�^�X::�ď����) {
        sprintf_s(filenameBuf, "OVERRIDE\\KAODATA\\%04d_B.bmp", nTargetKaoID);
        OutputDebugStream("�������͂��邩�H%s\n", filenameBuf);
        if (isFileExists(filenameBuf)) {
            filename = filenameBuf;
        }
    }

    // 0000_B�t�@�C�������݂��Ȃ����A�������͐퓬���ȊO�́A0000.bmp �̂悤�ȃt�@�C�����g�����Ƃ����݂�
    if (filename == "") {
        sprintf_s(filenameBuf, "OVERRIDE\\KAODATA\\%04d.bmp", nTargetKaoID);
        OutputDebugStream("�������͂��邩�H%s\n", filenameBuf);
        if (isFileExists(filenameBuf)) {
            filename = filenameBuf;
        }
    }

    if (filename == "" || !isFileExists(filename)) {
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
        memcpy(&picKaoFileOrigin, buffer.data(), buffer.size());

        // �㉺���]�������̂� picfileOrigin��picflipSidePp �ɃR�s�[
        for (int i = 0; i < 80; i++) {
            memcpy(&(picKaoFlipSidePp.line[80-1 - i]), &(picKaoFileOrigin.line[i]), 64);
        }

        memcpy(lpBuffer, &picKaoFlipSidePp, (64 * 80));
    }


    return TRUE;
}






struct KAHOU_PICLINE {
    BYTE at[64];
};
struct KAHOU_PICTURE {
    KAHOU_PICLINE line[64];
};

KAHOU_PICTURE picItemFileOrigin = { 0 };
KAHOU_PICTURE picItemFlipSidePp = { 0 };

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

    char filenameBuf[512] = "";
    sprintf_s(filenameBuf, "OVERRIDE\\ITEMDATA\\%03d.bmp", nTargetKahouGazouID);
    OutputDebugStream("�������͂��邩�H%s\n", filenameBuf);
    std::string filename = filenameBuf;
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
            memcpy(&(picItemFlipSidePp.line[64-1 - i]), &(picItemFileOrigin.line[i]), 64);
        }

        memcpy(lpBuffer, &picItemFlipSidePp, (64 * 64));
    }


    return TRUE;
}
