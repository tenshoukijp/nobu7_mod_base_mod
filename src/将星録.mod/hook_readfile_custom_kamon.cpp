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

#include "usr_custom_mod.h"

// �ƕ�̉摜�͕���24, ������24�B�}�W�b�N�i���o�[�ɂȂ��Ă��܂����A����ύX�ɂȂ�����͉i�v�ɂ��Ȃ����߁A���̂܂ܖ��ߍ��ށB(�������̕����萔���g�����킩��₷��)

#pragma pack(1)
struct KAMON_PICLINE {
    BYTE at[24];
};
#pragma pack()

#pragma pack(1)
struct KAMON_PICTURE {
    KAMON_PICLINE line[24];
};
#pragma pack()

extern int nTargetKamonID;
BOOL Hook_ReadFileCustom_KamonPic(
    HANDLE hFile, // �t�@�C���̃n���h��
    LPVOID lpBuffer, // �f�[�^�̊i�[��
    DWORD nNumberOfBytesToRead, // �ǂݍ��ރo�C�g��
    LPDWORD lpNumberOfBytesRead, // ���ۂɓǂݍ��񂾃o�C�g��
    LPOVERLAPPED lpOverlapped // �I�[�o�[���b�v�\���̂̃|�C���^
) {
    if (nTargetKamonID < 0) {
        return FALSE;
    }

    std::unique_ptr<KAMON_PICTURE> pickamonFileOrigin(new KAMON_PICTURE);
    std::unique_ptr<KAMON_PICTURE> pickamonFlipSidePp(new KAMON_PICTURE);
    /*
    KAMON_PICTURE pickamonFileOrigin = { 0 };
    KAMON_PICTURE pickamonFlipSidePp = { 0 };
    */
    std::string filename = "";

    // C#�̃J�X�^��.mod.dll����̏㏑��
    try {
        System::Collections::Generic::Dictionary<System::String^, System::Object^>^ dic = gcnew System::Collections::Generic::Dictionary<System::String^, System::Object^>(5);
        dic->Add("�Ɩ�ԍ�", nTargetKamonID);
        System::Collections::Generic::Dictionary<System::String^, System::Object^>^ ret = InvokeUserMethod("on�Ɩ�摜�v����", dic);
        if (ret != nullptr && ret->ContainsKey("�t�@�C����")) {
            System::String^ override_filename = (System::String^)(ret["�t�@�C����"]);
            if (System::String::IsNullOrEmpty(override_filename)) {
                ;
            }
            else {
                filename = to_native_string(override_filename);
            }
        }

    }
    catch (System::Exception^) {
        OutputDebugStream("on�Ɩ�摜�v�����ŃG���[");
    }


    if (filename == "") {
        char filenameBuf[512] = "";
        sprintf_s(filenameBuf, "OVERRIDE\\KAMON\\%03d.bmp", nTargetKamonID);
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

    file.seekg(-(24 * 24), std::ios::end);

    std::vector<char> buffer(24 * 24);
    file.read(buffer.data(), buffer.size());

    if (file.fail()) {
        OutputDebugStream("�t�@�C��" + filename + "�̓ǂݍ��݂Ɏ��s���܂����B\n");
        return FALSE;
    }

    // ���̉摜���R�s�[
    if (nNumberOfBytesToRead == buffer.size()) {
        memcpy(pickamonFileOrigin.get(), buffer.data(), buffer.size());

        // �㉺���]�������̂� picfileOrigin��picflipSidePp �ɃR�s�[
        for (int i = 0; i < 24; i++) {
            memcpy(&(pickamonFlipSidePp->line[24 - 1 - i]), &(pickamonFileOrigin->line[i]), 24);
        }

        memcpy(lpBuffer, pickamonFlipSidePp.get(), (24 * 24));
    }


    return TRUE;
}
