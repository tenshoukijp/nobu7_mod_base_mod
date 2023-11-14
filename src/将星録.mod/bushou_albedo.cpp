#include <windows.h>

#include <string>
using namespace std;

#include "data_game_struct.h"
#include "bushou_arubedo.h"
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