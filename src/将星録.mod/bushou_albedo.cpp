#include <windows.h>
#include <string>
#include <vector>

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
    nAlbedo�s���ςݕ����J�E���^�[ = 10;
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
                    break;
                }
            }
		}
    }

    return TRUE;
}

vector<int> get���g�p�w�`(int iUnitID) {
    // 
    vector<int> ���g�p�w�` = { 4,1,0,2,3,5,7,6,8 }; // �����̐w�`�Ŏ�肤��w�`�ԍ��B�d�v�Ȉʒu����B

    // ���p�ς݂̐w�`���J�b�g
    int target�w�`�ʒu = 0;
    
    target�w�`�ʒu = nb7���j�b�g���[iUnitID].��P�����̐w�`�ʒu;
    vector<int>::iterator itr;
    itr= std::find(���g�p�w�`.begin(), ���g�p�w�`.end(), target�w�`�ʒu);
    ���g�p�w�`.erase(itr);

    target�w�`�ʒu = nb7���j�b�g���[iUnitID].��Q�����̐w�`�ʒu;
    itr = std::find(���g�p�w�`.begin(), ���g�p�w�`.end(), target�w�`�ʒu);
    ���g�p�w�`.erase(itr);

    target�w�`�ʒu = nb7���j�b�g���[iUnitID].��R�����̐w�`�ʒu;
    itr = std::find(���g�p�w�`.begin(), ���g�p�w�`.end(), target�w�`�ʒu);
    ���g�p�w�`.erase(itr);

    target�w�`�ʒu = nb7���j�b�g���[iUnitID].��S�����̐w�`�ʒu;
    itr = std::find(���g�p�w�`.begin(), ���g�p�w�`.end(), target�w�`�ʒu);
    ���g�p�w�`.erase(itr);

    target�w�`�ʒu = nb7���j�b�g���[iUnitID].��T�����̐w�`�ʒu;
    itr = std::find(���g�p�w�`.begin(), ���g�p�w�`.end(), target�w�`�ʒu);
    ���g�p�w�`.erase(itr);

    return ���g�p�w�`;
}


// �A���x�h�����̃��j�b�g�́A�������������^���ł���B
void resetAlbedoUnitHeisuu() {

    for (int iUnitID = 0; iUnitID < �ő吔::���j�b�g���::�z��; iUnitID++) {
        int iBushouID = getBushouIDFromUnitID(iUnitID);
        if (0 <= iBushouID && iBushouID < �ő吔::�������::�z��) {
            if (getBushou����FromBushouID(iBushouID) == getArubedoSeiMei()) {

                // ��P���������݂��Ȃ��Ƃ������Ƃ́A�R�������ł͂Ȃ��Ƃ������ƁB�������Ȃ�
                if (nb7���j�b�g���[iUnitID].��P�����̐w�`�ʒu == 0xFFFF) {
                    return;
                }

                // ���j�b�g��ʂ��u�R���v�ł��Ȃ��u�R�D�v�ł��Ȃ���΁A�������Ȃ�
                if (nb7���j�b�g���[iUnitID].���j�b�g��� != ���j�b�g���::���j�b�g���::�R�� &&
                    nb7���j�b�g���[iUnitID].���j�b�g��� != ���j�b�g���::���j�b�g���::�R��
                    ) {
                    return;
                }

                // �܂��A���ƁE��C�E�S�b�D�̏���
                nb7���j�b�g���[iUnitID].���� = 3000;
                nb7���j�b�g���[iUnitID].��C = 1;
                nb7���j�b�g���[iUnitID].�S�b�D = 1;

                // �g���Ă��Ȃ��w�`�ʒu���擾
                vector<int> ���g�p�w�` = get���g�p�w�`(iUnitID);

                // �������񕜂��A(������ł��Ă�����A���g�p�̐w�`�ʒu�ւƔz������)
                int �g�� = nb7�������[iBushouID].�g��;
                int �Œᕺ�� = 400 + (�g�� * 50);
                int ���ݕ��� = 0;
                ���ݕ��� = nb7���j�b�g���[iUnitID].��P��������;
                if (���ݕ��� < �Œᕺ��) {
                    OutputDebugStream("��P�����̉�\n");
                    nb7���j�b�g���[iUnitID].��P�������� = �Œᕺ��;

                    // �������̂��̂���ł��Ă�����A����𑫌y�Ƃ��ĕ�������
                    int h = nb7���j�b�g���[iUnitID].��P��������;
                    if (h == 0xFFFF) { nb7���j�b�g���[iUnitID].��P�������� = 0; }

                    int p = nb7���j�b�g���[iUnitID].��P�����̐w�`�ʒu;
                    if (p == 0xFFFF) {
                        nb7���j�b�g���[iUnitID].��P�����̐w�`�ʒu = ���g�p�w�`[0];
						���g�p�w�`.erase(���g�p�w�`.begin());
                    }
                }
                ���ݕ��� = nb7���j�b�g���[iUnitID].��Q��������;
                if (���ݕ��� < �Œᕺ��) {
                    OutputDebugStream("��Q�����̉�\n");
                    nb7���j�b�g���[iUnitID].��Q�������� = �Œᕺ��;

                    // �������̂��̂���ł��Ă�����A����𑫌y�Ƃ��ĕ�������
                    int h = nb7���j�b�g���[iUnitID].��P��������;
                    if (h == 0xFFFF) { nb7���j�b�g���[iUnitID].��P�������� = 0; }

                    int p = nb7���j�b�g���[iUnitID].��Q�����̐w�`�ʒu;
                    if (p == 0xFFFF) {
						nb7���j�b�g���[iUnitID].��Q�����̐w�`�ʒu = ���g�p�w�`[0];
                        ���g�p�w�`.erase(���g�p�w�`.begin());
                    }
                }
                ���ݕ��� = nb7���j�b�g���[iUnitID].��R��������;
                if (���ݕ��� < �Œᕺ��) {
                    OutputDebugStream("��R�����̉�\n");
                    nb7���j�b�g���[iUnitID].��R�������� = �Œᕺ��;

                    // �������̂��̂���ł��Ă�����A����𑫌y�Ƃ��ĕ�������
                    int h = nb7���j�b�g���[iUnitID].��P��������;
                    if (h == 0xFFFF) { nb7���j�b�g���[iUnitID].��P�������� = 0; }

                    int p = nb7���j�b�g���[iUnitID].��R�����̐w�`�ʒu;
                    if (p == 0xFFFF) {
                        nb7���j�b�g���[iUnitID].��R�����̐w�`�ʒu = ���g�p�w�`[0];
                        ���g�p�w�`.erase(���g�p�w�`.begin());
                    }
                }
                ���ݕ��� = nb7���j�b�g���[iUnitID].��S��������;
                if (���ݕ��� < �Œᕺ��) {
                    OutputDebugStream("��S�����̉�\n");
                    nb7���j�b�g���[iUnitID].��S�������� = �Œᕺ��;

                    // �������̂��̂���ł��Ă�����A����𑫌y�Ƃ��ĕ�������
                    int h = nb7���j�b�g���[iUnitID].��P��������;
                    if (h == 0xFFFF) { nb7���j�b�g���[iUnitID].��P�������� = 0; }

                    int p = nb7���j�b�g���[iUnitID].��S�����̐w�`�ʒu;
                    if (p == 0xFFFF) {
                        nb7���j�b�g���[iUnitID].��S�����̐w�`�ʒu = ���g�p�w�`[0];
                        ���g�p�w�`.erase(���g�p�w�`.begin());
                    }

                }
                ���ݕ��� = nb7���j�b�g���[iUnitID].��T��������;
                if (���ݕ��� < �Œᕺ��) {
                    OutputDebugStream("��T�����̉�\n");
                    nb7���j�b�g���[iUnitID].��T�������� = �Œᕺ��;

                    // �������̂��̂���ł��Ă�����A����𑫌y�Ƃ��ĕ�������
                    int h = nb7���j�b�g���[iUnitID].��P��������;
                    if (h == 0xFFFF) { nb7���j�b�g���[iUnitID].��P�������� = 0; }

                    int p = nb7���j�b�g���[iUnitID].��T�����̐w�`�ʒu;
                    if (p == 0xFFFF) {
                        nb7���j�b�g���[iUnitID].��T�����̐w�`�ʒu = ���g�p�w�`[0];
                        ���g�p�w�`.erase(���g�p�w�`.begin());
                    }
                }

                break;
            }
        }
    }
}