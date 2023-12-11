#include <windows.h>
#include <string>
#include <vector>
#include <map>

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
map<int, int> mapOverrideKeyBushouValueYasenBattle;
int ��풆�̃A���x�h�̓G�����͐퓬�l���Œ�ƂȂ�(string attack, string defend) {

    string targetBushouName = "";

    // �U�������A���x�h�Ȃ�A��������^�[�Q�b�g�ɂ���
    if (attack == getArubedoSeiMei()) {
        targetBushouName = defend;
    }
    if (defend == getArubedoSeiMei()) {
        targetBushouName = attack;
    }

    // �A���x�h�ƑΛ����镐���̐퓬�\�͂�1�ɂ��A���̕����̌��X�̐퓬�l��ێ����Ă����B
    for (int iBushouID = 0; iBushouID < �ő吔::�������::���z��; iBushouID++) {
        if (targetBushouName == getBushou����FromBushouID(iBushouID)) {
            if (nb7�������[iBushouID].�퓬 >= 3) {
                mapOverrideKeyBushouValueYasenBattle[iBushouID] = nb7�������[iBushouID].�퓬;
                nb7�������[iBushouID].�퓬 = 1;
                break;
            }
        }
    }
    return 1;
}

// ���ŕύX�����퓬����̔\�͂����ƂւƖ߂�
int reset����̃A���x�h�̓G�����̐퓬�l() {
    for (auto itr = mapOverrideKeyBushouValueYasenBattle.begin(); itr != mapOverrideKeyBushouValueYasenBattle.end(); ++itr) {
		int iSaveBushouID = itr->first;
		int iSaveBattle = itr->second;

        if (isValidBushouID(iSaveBushouID)) {
            int iCurBattle = nb7�������[iSaveBushouID].�퓬;
            if (0 <= iCurBattle && iCurBattle <= 3) {
                nb7�������[iSaveBushouID].�퓬 = iSaveBattle;
                mapOverrideKeyBushouValueYasenBattle.erase(itr);
                break;
            }
        }
	}

    return TRUE;
}

int nAlbedo�s���ςݕ����J�E���^�[ = -1;
void resetAlbedoKoudouCounter() {
    nAlbedo�s���ςݕ����J�E���^�[ = 20;
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
            break;
        }
    }

    return TRUE;
}

int �A���x�h�g�҃��j�b�g���̂���������() {
    OutputDebugStream("resetAlbedoSisyaUnitMoney\n");
    for (int iUnitID = 0; iUnitID < �ő吔::���j�b�g���::�z��; iUnitID++) {
        int iBushouID = getBushouIDFromUnitID(iUnitID);
        if (isValidBushouID(iBushouID)) {
            if (getBushou����FromBushouID(iBushouID) == getArubedoSeiMei()) {

                OutputDebugStream("�A���x�h���j�b�g���%d\n", nb7���j�b�g���[iUnitID].���);

                // �g�҂Ȃ�A���K���Œ�3000�ɂ���
                if (nb7���j�b�g���[iUnitID].��� == ��::���j�b�g::���::�g��) {
                    OutputDebugStream("�A���x�h�g�҂̋��K%d\n", nb7���j�b�g���[iUnitID].���K);
                    if (nb7���j�b�g���[iUnitID].���K < 8000) {
                        nb7���j�b�g���[iUnitID].���K = 8000;
                    }
                }
                break;
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
    
    vector<int>::iterator itr;

    target�w�`�ʒu = nb7���j�b�g���[iUnitID].��P�����̐w�`�ʒu;
    itr= std::find(���g�p�w�`.begin(), ���g�p�w�`.end(), target�w�`�ʒu);
    if (itr != ���g�p�w�`.end()) {
        ���g�p�w�`.erase(itr);
    }

    target�w�`�ʒu = nb7���j�b�g���[iUnitID].��Q�����̐w�`�ʒu;
    itr = std::find(���g�p�w�`.begin(), ���g�p�w�`.end(), target�w�`�ʒu);
    if (itr != ���g�p�w�`.end()) {
        ���g�p�w�`.erase(itr);
    }

    target�w�`�ʒu = nb7���j�b�g���[iUnitID].��R�����̐w�`�ʒu;
    itr = std::find(���g�p�w�`.begin(), ���g�p�w�`.end(), target�w�`�ʒu);
    if (itr != ���g�p�w�`.end()) {
		���g�p�w�`.erase(itr);
	}

    target�w�`�ʒu = nb7���j�b�g���[iUnitID].��S�����̐w�`�ʒu;
    itr = std::find(���g�p�w�`.begin(), ���g�p�w�`.end(), target�w�`�ʒu);
    if (itr != ���g�p�w�`.end()) {
		���g�p�w�`.erase(itr);
	}

    target�w�`�ʒu = nb7���j�b�g���[iUnitID].��T�����̐w�`�ʒu;
    itr = std::find(���g�p�w�`.begin(), ���g�p�w�`.end(), target�w�`�ʒu);
    if (itr != ���g�p�w�`.end()) {
        ���g�p�w�`.erase(itr);
    }

    return ���g�p�w�`;
}


// �A���x�h�����̃��j�b�g�́A�������������^���ł���B
void �A���x�h�̃��j�b�g���R����R�D�Ȃ畺������() {

    for (int iUnitID = 0; iUnitID < �ő吔::���j�b�g���::�z��; iUnitID++) {
        int iBushouID = getBushouIDFromUnitID(iUnitID);
        if (isValidBushouID(iBushouID)) {
            if (getBushou����FromBushouID(iBushouID) == getArubedoSeiMei()) {

                // ��P���������݂��Ȃ��Ƃ������Ƃ́A�R�������ł͂Ȃ��Ƃ������ƁB�������Ȃ�
                if (nb7���j�b�g���[iUnitID].��P�����̐w�`�ʒu == 0xFFFF) {
                    return;
                }

                // ���j�b�g��ʂ��u�R���v�ł��Ȃ��u�R�D�v�ł��Ȃ���΁A�������Ȃ�
                if (nb7���j�b�g���[iUnitID].��� != ��::���j�b�g::���::�R�� &&
                    nb7���j�b�g���[iUnitID].��� != ��::���j�b�g::���::�R�D
                    ) {
                    return;
                }

                // �܂��A���ƁE��C�E�S�b�D�̏���
                nb7���j�b�g���[iUnitID].���� = 3000;
                nb7���j�b�g���[iUnitID].��C = 1;
                nb7���j�b�g���[iUnitID].�S�b�D = 1;

                OutputDebugStream("���g�p�w�`�`�F�b�N�O\n");
                // �g���Ă��Ȃ��w�`�ʒu���擾
                vector<int> ���g�p�w�` = get���g�p�w�`(iUnitID);

                // �������񕜂��A(������ł��Ă�����A���g�p�̐w�`�ʒu�ւƔz������)
                int �g�� = nb7�������[iBushouID].�g��;
                int �����ő啺�� = get�R�����j�b�g�����ő啺��FromUnitID(iUnitID);

                int ���ݕ��� = 0;
                ���ݕ��� = nb7���j�b�g���[iUnitID].��P��������;
                if (���ݕ��� < �����ő啺��) {
                    OutputDebugStream("��P�����̉�\n");
                    nb7���j�b�g���[iUnitID].��P�������� = �����ő啺��;

                    // �������̂��̂���ł��Ă�����A����𑫌y�Ƃ��ĕ�������
                    int j = nb7���j�b�g���[iUnitID].��P�����̐w�`�ʒu;
                    if (j == 0xFFFF) {
                        nb7���j�b�g���[iUnitID].��P�����̐w�`�ʒu = ���g�p�w�`[0];
                        ���g�p�w�`.erase(���g�p�w�`.begin());
                        nb7���j�b�g���[iUnitID].��P�������� = 0;
                    }
                }
                ���ݕ��� = nb7���j�b�g���[iUnitID].��Q��������;
                if (���ݕ��� < �����ő啺��) {
                    OutputDebugStream("��Q�����̉�\n");
                    nb7���j�b�g���[iUnitID].��Q�������� = �����ő啺��;

                    // �������̂��̂���ł��Ă�����A����𑫌y�Ƃ��ĕ�������
                    int j = nb7���j�b�g���[iUnitID].��Q�����̐w�`�ʒu;
                    if (j == 0xFFFF) {
						nb7���j�b�g���[iUnitID].��Q�����̐w�`�ʒu = ���g�p�w�`[0];
                        ���g�p�w�`.erase(���g�p�w�`.begin());
                        nb7���j�b�g���[iUnitID].��P�������� = 0;
                    }
                }
                ���ݕ��� = nb7���j�b�g���[iUnitID].��R��������;
                if (���ݕ��� < �����ő啺��) {
                    OutputDebugStream("��R�����̉�\n");
                    nb7���j�b�g���[iUnitID].��R�������� = �����ő啺��;

                    int j = nb7���j�b�g���[iUnitID].��R�����̐w�`�ʒu;
                    if (j == 0xFFFF) {
                        nb7���j�b�g���[iUnitID].��R�����̐w�`�ʒu = ���g�p�w�`[0];
                        ���g�p�w�`.erase(���g�p�w�`.begin());
                        nb7���j�b�g���[iUnitID].��P�������� = 0;
                    }
                }
                ���ݕ��� = nb7���j�b�g���[iUnitID].��S��������;
                if (���ݕ��� < �����ő啺��) {
                    OutputDebugStream("��S�����̉�\n");
                    nb7���j�b�g���[iUnitID].��S�������� = �����ő啺��;

                    // �������̂��̂���ł��Ă�����A����𑫌y�Ƃ��ĕ�������
                    int j = nb7���j�b�g���[iUnitID].��S�����̐w�`�ʒu;
                    if (j == 0xFFFF) {
                        nb7���j�b�g���[iUnitID].��S�����̐w�`�ʒu = ���g�p�w�`[0];
                        ���g�p�w�`.erase(���g�p�w�`.begin());
                        nb7���j�b�g���[iUnitID].��P�������� = 0;
                    }

                }
                ���ݕ��� = nb7���j�b�g���[iUnitID].��T��������;
                if (���ݕ��� < �����ő啺��) {
                    OutputDebugStream("��T�����̉�\n");
                    nb7���j�b�g���[iUnitID].��T�������� = �����ő啺��;

                    // �������̂��̂���ł��Ă�����A����𑫌y�Ƃ��ĕ�������
                    int j = nb7���j�b�g���[iUnitID].��T�����̐w�`�ʒu;
                    if (j == 0xFFFF) {
                        nb7���j�b�g���[iUnitID].��T�����̐w�`�ʒu = ���g�p�w�`[0];
                        ���g�p�w�`.erase(���g�p�w�`.begin());
                        nb7���j�b�g���[iUnitID].��P�������� = 0;
                    }
                }
                break;
            }
        }
    }
}

// �A���x�h���g����喼�����ޘQ�l����A�⍦����������
void resetAlbedo�����鉺�⍦����() {
    for (int iBushouID = 0; iBushouID < �ő吔::�������::�z��; iBushouID++) {
        if (getBushou����FromBushouID(iBushouID) == getArubedoSeiMei()) {
            // �A���x�h���u�����v�ł���A�������̓A���x�h�͑喼�ł���
            if (nb7�������[iBushouID].��� == ��::����::���::���� || nb7�������[iBushouID].��� == ��::����::���::�喼) {
                int iAlbedoCastleID = getCastleIdFromBushouID(iBushouID);
                if (isValidCastleID(iAlbedoCastleID)) {
                    int*pAlbedo�����喼 = nb7����[iAlbedoCastleID].p�����喼;

                    // ���̑喼�����ޘQ�l����⍦����������
                    for (int b = 0; b < �ő吔::�������::�z��; b++) {
                        // �Q�l�ł���
                        if (nb7�������[b].��� == ��::����::���::�Q�l) {
                            if (nb7�������[b].p�⍦�喼 == pAlbedo�����喼) {
                                OutputDebugStream("�Q�l:%s\n", nb7�������[b].����);
                                //  nb7�������[b].�⍦ = 0;
                                nb7�������[b].p�⍦�喼 = �������::p�⍦�喼::����;
                            }
                        }
                    }
                }

            }
            break;
        }
    }
}


// �ď�펞�ɐ퓬�͂��P�ɂ����l�ꗗ
map<int, int> mapOverrideKeyBushouValueCastleBattle;
void �ď钆�̃A���x�h�̓G�����͐퓬�l���Œ�ƂȂ�(std::string sCastleName)
{
    // �A���x�h�̏����喼�𓾂�
    int iAlbedoDaimyoID = -1;
    for (int iBushouID = 0; iBushouID < �ő吔::�������::�z��; iBushouID++) {
        if (getBushou����FromBushouID(iBushouID) == getArubedoSeiMei()) {
            iAlbedoDaimyoID = getDaimyoIDFromBushouID(iBushouID);
            break;
        }
    }

    for (int iCastleID = 0; iCastleID < �ő吔::����::�z��; iCastleID++) {
        // �Y���̏閼�����������Ȃ�
        if (sCastleName == nb7����[iCastleID].�閼 + get���(iCastleID)) {
            int iRoujoCastleID = iCastleID;
            OutputDebugStream("CastleID��:%d�ł�\n", iCastleID);
            for (int iBushouID = 0; iBushouID < �ő吔::�������::�z��; iBushouID++) {
                // �������喼�ł���
                if (nb7�������[iBushouID].��� == ��::����::���::���� || nb7�������[iBushouID].��� == ��::����::���::�喼) {
                    int iBushouCastleID = getCastleIdFromBushouID(iBushouID);
                    // �Y���������ď�풆�̏�ɋA�����Ă���(�ď��ɎQ�����Ă���Ƃ͌���Ȃ�)
                    if (iBushouCastleID == iRoujoCastleID) {
                        // �A���x�h�Ƃ͑喼���قȂ�
                        if (getDaimyoIDFromBushouID(iBushouID) != iAlbedoDaimyoID) {
                            // �퓬�͂��P�ɂ��Ă����A���̐퓬�͕͂ۑ����Ă����B
                            if (nb7�������[iBushouID].�퓬 >= 3) {
                                mapOverrideKeyBushouValueCastleBattle[iBushouID] = nb7�������[iBushouID].�퓬;
                                nb7�������[iBushouID].�퓬 = 1;
                            }
                        }
                    }
                }
            }
            break;
        }
    }
}

// �ď��ŕύX�����퓬����̔\�͂����ƂւƖ߂�
int reset�ď��̃A���x�h�̓G�����͐퓬�l() {
    for (auto itr = mapOverrideKeyBushouValueCastleBattle.begin(); itr != mapOverrideKeyBushouValueCastleBattle.end(); ++itr) {
        int iSaveBushouID = itr->first;
        int iSaveBattle = itr->second;

        if (isValidBushouID(iSaveBushouID)) {
            int iCurBattle = nb7�������[iSaveBushouID].�퓬;
            if (0 <= iCurBattle && iCurBattle <= 3) {
                nb7�������[iSaveBushouID].�퓬 = iSaveBattle;
                mapOverrideKeyBushouValueCastleBattle.erase(itr);
            }
        }
    }

    return TRUE;
}


extern int iLastAttackBushouID;
extern int iLastDefendBushouID;

static int iPreviousAttackTurnBushouID = -1; // �P�O�Ƀ`�F�b�N�������̍U��������ID
static int iPreviousButaiID = -1; // �P�O�Ƀ`�F�b�N�������̍U���������̕���ID

extern int nRemainYasenTurn;
static int iPreviousRemainYasenTurn; // �P�O�Ƀ`�F�b�N�������̎c����^�[����

void do�A���x�h�����^�[��������(int iCurrentAttackTurnBushouID, int iButaiID)
{
    // �O��Ə󋵂��ς���Ă��Ȃ��Ȃ�A�������Ȃ��B�A�j���[�V�����Ƃ��E�B���h�E�̃A�N�e�B�u���ς���Ė߂��Ă����肵�čēx���s���ꂽ�̂��낤�B
    if (iPreviousRemainYasenTurn == nRemainYasenTurn &&
        iCurrentAttackTurnBushouID == iPreviousAttackTurnBushouID &&
        iButaiID == iPreviousButaiID) {
		return;
	}
    iPreviousAttackTurnBushouID = iCurrentAttackTurnBushouID;
    iPreviousButaiID = iButaiID;

    OutputDebugStream("�������U��������ID:%d\n", iLastAttackBushouID);
    OutputDebugStream("���������������ID:%d\n", iLastDefendBushouID);

    if (isValidBushouID(iLastAttackBushouID)) {
        // �U�������A���x�h�Ȃ�
        if (nb7�������[iLastAttackBushouID].���� == getArubedoSeiMei()) {
            // �A���x�h�̃��j�b�gID�����߂�
            int �ő啺�� = get�R�����j�b�g�����ő啺��FromBushouID(iLastAttackBushouID);
            int bix = iButaiID;
            for (int bix = 0; bix < �ő吔::���j�b�g���::�R��������; bix++) {
                if (0 < nb7���U�����������[bix].���� && nb7���U�����������[bix].���� < �ő啺��) {
                    nb7���U�����������[bix].���� = (nb7���U�����������[bix].���� * 3 + �ő啺��) / 4; // �����������񕜂���
                }
                // �ő啺���߂��܂ōs������A����ɂ���
                if (�ő啺�� - nb7���U�����������[bix].���� < 10) {
                    nb7���U�����������[bix].���� = �ő啺��;
                }
            }
        }
    }
    if (isValidBushouID(iLastDefendBushouID)) {
        // �U�������A���x�h�Ȃ�
        if (nb7�������[iLastDefendBushouID].���� == getArubedoSeiMei()) {
            // �A���x�h�̃��j�b�gID�����߂�
            int �ő啺�� = get�R�����j�b�g�����ő啺��FromBushouID(iLastDefendBushouID);
            int bix = iButaiID;
            for (int bix = 0; bix < �ő吔::���j�b�g���::�R��������; bix++) {
                if (0 < nb7��������������[bix].���� && nb7��������������[bix].���� < �ő啺��) {
                    nb7��������������[bix].���� = (nb7��������������[bix].���� * 3 + �ő啺��) / 4; // �����������񕜂���
                }
                // �ő啺���߂��܂ōs������A����ɂ���
                if (�ő啺�� - nb7��������������[bix].���� < 10) {
                    nb7��������������[bix].���� = �ő啺��;
                }
            }
        }
    }
}
