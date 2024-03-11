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

// ��̉摜�͕���64, ������80�B�}�W�b�N�i���o�[�ɂȂ��Ă��܂����A����ύX�ɂȂ�����͉i�v�ɂ��Ȃ����߁A���̂܂ܖ��ߍ��ށB(�������̕����萔���g�����킩��₷��)

#pragma pack(1)
struct KAO_PICLINE {
    BYTE at[64];
};
#pragma pack()

#pragma pack(1)
struct KAO_PICTURE {
    KAO_PICLINE line[80];
};
#pragma pack()


bool isBattleFaceCondition(int iTargetKaoID) {
    int status = get�Q�[����ʃX�e�[�^�X();
    if (status == �����^::��::�Q�[����ʃX�e�[�^�X::����� ||
        status == �����^::��::�Q�[����ʃX�e�[�^�X::�ď����) {
        return true;
    }

    for (int iUnitID = 0; iUnitID < �ő吔::���j�b�g���::�z��; iUnitID++) {
        // ���j�b�g��ʂ͌R���A�������́A�R�D�ł���
        int iBushouID = getBushouIDFromUnitID(iUnitID);
        if (isValidBushouID(iBushouID)) {
            if (nb7���j�b�g���[iUnitID].��� == ��::���j�b�g::���::�R�� || nb7���j�b�g���[iUnitID].��� == ��::���j�b�g::���::�R�D) {
                int iKaoID = nb7�������[iBushouID].��ԍ�;
                if (iKaoID == iTargetKaoID) {
					return true;
				}
            }
        }
    }

    return false;
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

    std::unique_ptr<KAO_PICTURE> picKaoFileOrigin(new KAO_PICTURE);
    std::unique_ptr<KAO_PICTURE> picKaoFlipSidePp(new KAO_PICTURE);

    char filenameBuf[512] = "";
    std::string filename = "";

    // C#�̃J�X�^��.mod.dll����̏㏑��
    try {
        System::Collections::Generic::Dictionary<System::String^, System::Object^>^ dic = gcnew System::Collections::Generic::Dictionary<System::String^, System::Object^>(5);
        dic->Add("��ԍ�", nTargetKaoID);
        System::Collections::Generic::Dictionary<System::String^, System::Object^>^ ret = InvokeUserMethod("on��摜�v����", dic);
        if (ret != nullptr && ret->ContainsKey("�t�@�C����")) {
            System::String^ override_filename = (System::String^)(ret["�t�@�C����"]);
            if (System::String::IsNullOrEmpty(override_filename)) {
                OutputDebugStream("AAAAAA\n");
                ;
            }
            else {
                OutputDebugStream("BBBBBB\n");
                filename = to_native_string(override_filename);
            }
        }

    }
    catch (System::Exception^) {
        OutputDebugStream("on��摜�v�����ŃG���[");
    }


    // �퓬���Ȃ� 0000_B.bmp �̂悤�ȃt�@�C�������݂���΂������D��Ŏg�����Ƃ����݂�
    if (filename == "" && isBattleFaceCondition(nTargetKaoID)) {
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
        memcpy(picKaoFileOrigin.get(), buffer.data(), buffer.size());

        // �㉺���]�������̂� picfileOrigin��picflipSidePp �ɃR�s�[
        for (int i = 0; i < 80; i++) {
            memcpy(&(picKaoFlipSidePp->line[80-1 - i]), &(picKaoFileOrigin->line[i]), 64);
        }

        memcpy(lpBuffer, picKaoFlipSidePp.get(), (64 * 80));
    }


    return TRUE;
}





