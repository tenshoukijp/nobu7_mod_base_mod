#include <windows.h>

#include <string>
using namespace std;

#include "data_game_struct.h"
#include "bushou_albedo.h"
#include "output_debug_stream.h"


string getArubedoSei() {
    return "�ɑ�";
}

string getArubedoMei() {
    return "������";
}

string getArubedoSeiMei() {
    return getArubedoSei() + getArubedoMei();
}

// �A���x�h�ƑΛ����镐���̐퓬�\�͂�1�ɂȂ��Ă��܂�
int iOverrideBushouID = -1;
int iBackupBushou�퓬 = 0;
int overrideYasenBattleAbirityChangeAlbedo(string attack, string defend) {

    string targetBushouName = "";

    OutputDebugStream("�����\�͂��㏑��\n");

    // �U�������A���x�h�Ȃ�A��������^�[�Q�b�g�ɂ���
    if (attack == getArubedoSeiMei()) {
        targetBushouName = defend;
    }
    if (defend == getArubedoSeiMei()) {
        targetBushouName = attack;
    }

    // �A���x�h�ƑΛ����镐���̐퓬�\�͂�1�ɂ��A���̕����̌��X�̐퓬�l��ێ����Ă����B
    for (int iBushouID = 0; iBushouID < �ő吔::�������::�z��; iBushouID++) {
        if (targetBushouName == getBushou����FromBushouID(iBushouID) ) {
            iOverrideBushouID = iBushouID;
            iBackupBushou�퓬 = nb7�������[iBushouID].�퓬;
            nb7�������[iBushouID].�퓬 = 1;
            break;
        }
    }
    return 1;
}

// ���ŕύX�����퓬����̔\�͂����ƂւƖ߂�
int resetYasenBattleAbirityChangeAlbedo() {

    if (0 <= iOverrideBushouID && iOverrideBushouID < �ő吔::�������::�z��) {
        nb7�������[iOverrideBushouID].�퓬 = iBackupBushou�퓬;

        iOverrideBushouID = -1;
        iBackupBushou�퓬 = 0;
    }

    return TRUE;
}

int nAlbedo�s���ςݕ����J�E���^�[ = -1;
void resetAlbedoKoudouCounter() {
    nAlbedo�s���ςݕ����J�E���^�[ = 5;
}

int decreaseAlbedoKoudouCounter() {
    for (int iBushouID = 0; iBushouID < �ő吔::�������::�z��; iBushouID++) {
        // �A���x�h�Ȃ�
        if (getBushou����FromBushouID(iBushouID) == getArubedoSeiMei()) {
            // �A���x�h���u�s���ς݁v�ɂȂ��Ă��A����5��܂ł͍s���ł���悤�ɂ���
            if (nAlbedo�s���ςݕ����J�E���^�[ > 0) {
                if (nb7�������[iBushouID].�s����) {
                    nb7�������[iBushouID].�s���� = 0;
                    nAlbedo�s���ςݕ����J�E���^�[--;
                }
            }
		}
    }

    return TRUE;
}