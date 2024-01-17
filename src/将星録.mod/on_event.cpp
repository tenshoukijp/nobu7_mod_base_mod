#include <windows.h>
#include "output_debug_stream.h"
#include "hook_textouta_custom.h"
#include "onigwrap.h"
#include "data_game_struct.h"
#include "bushou_albedo.h"
#include "game_screen.h"
#include "hook_functions_direct.h"
#include "on_event.h"

using namespace ��;

void onOpeningMovie() {
    hookFunctionsDirect();
    set�Q�[����ʃX�e�[�^�X(�Q�[����ʃX�e�[�^�X::�N�����);
	OutputDebugStream("�I�[�v�j���O���[�r�[\n");
}

extern void resetMapBushouKoudouzumiCacheInMonth();
// �Q�[���̏����ݒ���
void onInitialGameMenu() {
    set�Q�[����ʃX�e�[�^�X(�Q�[����ʃX�e�[�^�X::�����ݒ���);
    OutputDebugStream("�����^�̏����ݒ���\n");
    resetAlbedoKoudouCounter();
    resetMapBushouKoudouzumiCacheInMonth();
}

void onLoadSaveDataMenu() {
    OutputDebugStream("�Z�[�u�f�[�^�̃��[�h���\n");
}

void onSaveSaveDataMenu() {
    OutputDebugStream("�Z�[�u�f�[�^�̃Z�[�u���\n");
}

void onShikanWindow() {
    OutputDebugStream("�m�����\n");
}

void onMenuBushouEditStart() {
    OutputDebugStream("���j���[-�����ҏW���\n");
}

void onMenuShiroEditStart() {
    OutputDebugStream("���j���[-��ҏW���\n");
}

void onMenuNenpyoSengokushiStart() {
	OutputDebugStream("���j���[-�N�\-�퍑�j���\n");
}

void onMenuJyohoDaimyoIchiranStart() {
	OutputDebugStream("���j���[-���-�喼�ꗗ���\n");
}

void onMenuJyohoShiroIchiranStart() {
	OutputDebugStream("���j���[-���-��ꗗ���\n");
}

void onMenuJyohoBushouIchiranStart() {
   	OutputDebugStream("���j���[-���-�����ꗗ���\n");
}

void onMenuJyohoUnitIchiranStart() {
   	OutputDebugStream("���j���[-���-���j�b�g�ꗗ���\n");
}

void onMenuJyohoKahouIchiranStart() {
   	OutputDebugStream("���j���[-���-�����ꗗ���\n");
}

void onMenuJyohoKanniIchiranStart() {
	OutputDebugStream("���j���[-���-���ʈꗗ���\n");
}

void onMenuJyohoYakusyokuIchiranStart() {
    OutputDebugStream("���j���[-���-��E�ꗗ���\n");
}

void onMenuCyuChizuStart() {
	OutputDebugStream("���j���[-���n�}���\n");
}

void onMenuShiroIchiranStart() {
    OutputDebugStream("���j���[-��ꗗ���\n");
}

void onMenuKashinBushoIchiranStart() {
    OutputDebugStream("���j���[-�Ɛb-�����ꗗ���\n");
}

void onMenuKashinUnitIchiranStart() {
    OutputDebugStream("���j���[-�Ɛb-���j�b�g�ꗗ���\n");
}

void onStrategyGameStart() {
    OutputDebugStream("�헪��ʂŃQ�[�����X�^�[�g���܂���\n");
}

// �N�̏��������݂����ꂽ
void onWriteYear() {
}

// ���̏��������݂����ꂽ
void onWriteMonth() {
}

void onUpdateMonth(int iMonth) {
    set�Q�[����ʃX�e�[�^�X(��::�Q�[����ʃX�e�[�^�X::�헪���);
    OutputDebugStream("�����ς�����̂ŃA���x�h�̃J�E���^�����Z�b�g���܂�\n");
}

// ���Ƃ̑���̏��������݂����ꂽ
void onWriteSobaKome(int iSobaKome) {
    if (iSobaKome != 0) {
        set�Q�[����ʃX�e�[�^�X(��::�Q�[����ʃX�e�[�^�X::�헪���);
    }
}

void onUpdateSobaKome(int iSobaKome) {
}

void onUpdateSobaUma(int iSobaUma) {
}

void onUpdateSobaTeppou(int iSobaTeppou) {
}

// �n�̑���̏��������݂����ꂽ
void onWriteSobaUma(int iSobaUma) {
}

// �S�C�̑���̏��������݂����ꂽ
void onWriteSobaTeppou(int iSobaTeppou) {
    if (iSobaTeppou != 0) {
        onStrategyGameStart();
    }
}


void onChoteiKenjo(string choteiKenjoInfo) {

    OutputDebugStream("�����쌣��\n");

    Matches ma;
    if ( OnigMatch(choteiKenjoInfo, "����g��(.+?)����(�e�����G|�R�Ȍ��p|���C�����L)�F�D�x(\\d+)", &ma)) {
    	OutputDebugStream("���쌣��g��:" + ma[1] + "\n");
		OutputDebugStream("����F�D�x:" + ma[3] + "\n");

        // ���쌣��g�҂̓A���x�h�ł���B
        if (ma[1].find(getArubedoSeiMei()) != string::npos ) {
			OutputDebugStream("�A���x�h������g�҂������̂ŁA�����[\n");
			�A���x�h�g�҃��j�b�g���̂���������();
        }
    }
}

void onDoumeiShisha(string doumeiShishaInfo) {
    OutputDebugStream("�����g��\n");
    Matches ma;
    if (OnigMatch(doumeiShishaInfo, "�����g��(.+?)�F�D�x(\\d+)", &ma)) {
        OutputDebugStream("�����F�D�x\n");
        // ���쌣��g�҂̓A���x�h�ł���B
        if (ma[1].find(getArubedoSeiMei()) != string::npos) {
            OutputDebugStream("�A���x�h������g�҂������̂ŁA�����[\n");
            �A���x�h�g�҃��j�b�g���̂���������();
        }
    }
}

void onGoumotsuShisha(string goumotsuShishaInfo) {
    OutputDebugStream("�v���g��\n");
    Matches ma;
    if (OnigMatch(goumotsuShishaInfo, "�v���g��(.+?)�F�D�x(\\d+)", &ma)) {
        OutputDebugStream("�v���F�D�x\n");
        // ���쌣��g�҂̓A���x�h�ł���B
        if (ma[1].find(getArubedoSeiMei()) != string::npos) {
            OutputDebugStream("�A���x�h������g�҂������̂ŁA�����[\n");
            �A���x�h�g�҃��j�b�g���̂���������();
        }
    }
}




/*
void onYanseBattlePrePreStart() {
    OutputDebugStream("���ɂ�����������܂�\n\n");

    resetAlbedoUnitHeisuu();
}
*/

void onYasenBattlePreStart() {
    OutputDebugStream("���̐퓬���J�n���܂���\n\n");
    set�Q�[����ʃX�e�[�^�X(��::�Q�[����ʃX�e�[�^�X::�����);

    �A���x�h�̃��j�b�g���R����R�D�Ȃ畺������();
}

void onYasenBattleStart(string battleYanseStartInfo) {

    Matches ma;
    if (OnigMatch(battleYanseStartInfo, "�����:(.+?)�퓬:(\\d+?)�m�C:(\\d+?)����:(\\d+?)(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?�U����:(.+?)�퓬:(\\d+?)�m�C:(\\d+?)����:(\\d+?)(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(\\d+?)�N(\\d+?)���c��(\\d+?)�^�[��(.+?\\d�����̐�p)", &ma)) {
        OutputDebugStream("�����:" + ma[1] + "\n");
        string syubigawa = ma[1];

        OutputDebugStream("�퓬:" + ma[2] + "\n");
        OutputDebugStream("�m�C:" + ma[3] + "\n");
        OutputDebugStream("����:" + ma[4] + "\n");
        OutputDebugStream("��P��������:" + ma[6] + "\n");
        OutputDebugStream("��P�����K��:" + ma[7] + "\n");
        OutputDebugStream("��Q��������:" + ma[9] + "\n");
        OutputDebugStream("��Q�����K��:" + ma[10] + "\n");
        OutputDebugStream("��R��������:" + ma[12] + "\n");
        OutputDebugStream("��R�����K��:" + ma[13] + "\n");
        OutputDebugStream("��S��������:" + ma[15] + "\n");
        OutputDebugStream("��S�����K��:" + ma[16] + "\n");
        OutputDebugStream("��T��������:" + ma[18] + "\n");
        OutputDebugStream("��T�����K��:" + ma[19] + "\n");

        OutputDebugStream("�U����:" + ma[20] + "\n");
        string kougekigawa = ma[20];

        OutputDebugStream("�퓬:" + ma[21] + "\n");
        OutputDebugStream("�m�C:" + ma[22] + "\n");
        OutputDebugStream("����:" + ma[23] + "\n");
        OutputDebugStream("��P��������:" + ma[25] + "\n");
        OutputDebugStream("��P�����K��:" + ma[26] + "\n");
        OutputDebugStream("��Q��������:" + ma[28] + "\n");
        OutputDebugStream("��Q�����K��:" + ma[29] + "\n");
        OutputDebugStream("��R��������:" + ma[31] + "\n");
        OutputDebugStream("��R�����K��:" + ma[32] + "\n");
        OutputDebugStream("��S��������:" + ma[34] + "\n");
        OutputDebugStream("��S�����K��:" + ma[35] + "\n");
        OutputDebugStream("��T��������:" + ma[37] + "\n");
        OutputDebugStream("��T�����K��:" + ma[38] + "\n");
        OutputDebugStream("�N:" + ma[39] + "\n");
        OutputDebugStream("��:" + ma[40] + "\n");
    }
}

string previousBattleTurnInfo = "";
string previousRegexBattleTurnInfo = "";
BOOL isYasenBattle = FALSE;

void onYasenBattleTurn(string battleYanseTurnInfo) {
    OutputDebugStream("�퓬�^�[�����:" + battleYanseTurnInfo + "\n");

    // �O��ƑS�������Ȃ�A�������Ȃ��B�����ł͂������Ƃňȉ��̐��K�\���ɍs���p�x�����炷
    if (previousBattleTurnInfo == battleYanseTurnInfo) {
        return;
    }
    // �������A����̐퓬�^�[������ۑ�����
    else {
        previousBattleTurnInfo = battleYanseTurnInfo;
    }

    Matches ma;

    if (OnigMatch(battleYanseTurnInfo, "�����:(.+?)�퓬:(\\d+?)�m�C:(\\d+?)����:(\\d+?)(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?�U����:(.+?)�퓬:(\\d+?)�m�C:(\\d+?)����:(\\d+?)(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(\\d+?)�N(\\d+?)���c��(\\d+?)�^�[��(.+?\\d�����̐�p)", &ma)) {

        OutputDebugStream("m0����!!:" + ma[0] + "\n");
        string regexBattleTurnInfo = ma[0];

        // ���K�\���ł̈�v�������O��ƑS�������Ȃ�A�������Ȃ�
        if (previousRegexBattleTurnInfo == regexBattleTurnInfo) {
            return;
        }
        // �������A����̐��K�\���ł̈�v������ۑ�����
        else {
            previousRegexBattleTurnInfo = regexBattleTurnInfo;
        }

        OutputDebugStream("�����:" + ma[1] + "\n");
        string syubigawa = ma[1];

        OutputDebugStream("�퓬:" + ma[2] + "\n");
        OutputDebugStream("�m�C:" + ma[3] + "\n");
        OutputDebugStream("����:" + ma[4] + "\n");
        OutputDebugStream("��P��������:" + ma[6] + "\n");
        OutputDebugStream("��P�����K��:" + ma[7] + "\n");
        OutputDebugStream("��Q��������:" + ma[9] + "\n");
        OutputDebugStream("��Q�����K��:" + ma[10] + "\n");
        OutputDebugStream("��R��������:" + ma[12] + "\n");
        OutputDebugStream("��R�����K��:" + ma[13] + "\n");
        OutputDebugStream("��S��������:" + ma[15] + "\n");
        OutputDebugStream("��S�����K��:" + ma[16] + "\n");
        OutputDebugStream("��T��������:" + ma[18] + "\n");
        OutputDebugStream("��T�����K��:" + ma[19] + "\n");

        OutputDebugStream("�U����:" + ma[20] + "\n");
        string kougekigawa = ma[20];

        OutputDebugStream("�퓬:" + ma[21] + "\n");
        OutputDebugStream("�m�C:" + ma[22] + "\n");
        OutputDebugStream("����:" + ma[23] + "\n");
        OutputDebugStream("��P��������:" + ma[25] + "\n");
        OutputDebugStream("��P�����K��:" + ma[26] + "\n");
        OutputDebugStream("��Q��������:" + ma[28] + "\n");
        OutputDebugStream("��Q�����K��:" + ma[29] + "\n");
        OutputDebugStream("��R��������:" + ma[31] + "\n");
        OutputDebugStream("��R�����K��:" + ma[32] + "\n");
        OutputDebugStream("��S��������:" + ma[34] + "\n");
        OutputDebugStream("��S�����K��:" + ma[35] + "\n");
        OutputDebugStream("��T��������:" + ma[37] + "\n");
        OutputDebugStream("��T�����K��:" + ma[38] + "\n");
        OutputDebugStream("�N:" + ma[39] + "\n");
        OutputDebugStream("��:" + ma[40] + "\n");
        OutputDebugStream("�c��^�[��:" + ma[41] + "\n");

        string turnButaiInfo = ma[42];
        OutputDebugStream("�^�[������:" + turnButaiInfo + "\n");

        Matches turn_ma;

        if (OnigMatch(turnButaiInfo, kougekigawa + "��" + syubigawa + "(.+)�R��(\\d)�����̐�p", &turn_ma)) {
            OutputDebugStream("�^�[���R:" + turn_ma[1] + "\n");
            OutputDebugStream("�^�[�������ԍ�:" + turn_ma[2] + "\n");
        }
        else if (OnigMatch(turnButaiInfo, syubigawa + "��" + kougekigawa + "(.+)�R��(\\d)�����̐�p", &turn_ma)) {
            OutputDebugStream("�^�[���R:" + turn_ma[1] + "\n");
            OutputDebugStream("�^�[�������ԍ�:" + turn_ma[2] + "\n");
        }

        string albedoSeiMei = getArubedoSeiMei();
        if (kougekigawa == albedoSeiMei || syubigawa == albedoSeiMei) {
            ��풆�̃A���x�h�̓G�����͐퓬�l���Œ�ƂȂ�(syubigawa, kougekigawa);
        }


    }
}

void onYasenBattleEnd(string endYanseBattleInfo) {
    if (OnigMatch(
        endYanseBattleInfo,
        "���.+?������R����S�ł����܂���|"
        "���.+?������R�����S�ł��܂���|"
        "���.+?������R���̎m�C��(0|�O)�ɂ��܂���|"
        "���.+?������R���̎m�C��(0|�O)�ɂȂ�܂���|"
        "���.+?�͐�ꂩ��ދp���܂���|"
        "���.+?�����͂��܂���ł���|"
        "���.+?�R�̖{�w��S�ł����܂���|"
        "���.+?�R�̖{�w���S�ł��܂���|"
        "���.+?�𓢂����܂���|"
        "���.+?���펀���܂���|"
        "���.+?�𓢂����܂���|"
        "���.+?��(.+?)�̍U�����󂯂����Ȃ��Ŋ��𐋂���"
    )
    ) {
    }

    reset����̃A���x�h�̓G�����̐퓬�l();

    �A���x�h�̃��j�b�g���R����R�D�Ȃ畺������();

    OutputDebugStream("���̐퓬���I�����܂���\n\n" + endYanseBattleInfo + "\n");

    set�Q�[����ʃX�e�[�^�X(�Q�[����ʃX�e�[�^�X::�헪���);
}

// ���R�s���ȏI����
void onYasenBattleEnd() {
    reset����̃A���x�h�̓G�����̐퓬�l();

    �A���x�h�̃��j�b�g���R����R�D�Ȃ畺������();

    OutputDebugStream("���̐퓬���I�����܂���\n\n");

    set�Q�[����ʃX�e�[�^�X(�Q�[����ʃX�e�[�^�X::�헪���);
}

BOOL isCastleBattle = FALSE;
void onCastleBattlePreStart() {
    isCastleBattle = TRUE;

    �A���x�h�̃��j�b�g���R����R�D�Ȃ畺������();

    set�Q�[����ʃX�e�[�^�X(�Q�[����ʃX�e�[�^�X::�ď����);

    OutputDebugStream("��U�߂̐퓬���J�n���܂���\n");
}

int nPreviousCastleBattleTurn = -1;
void onCastleBattleTurn(string battleCastleTurnInfo) {
    Matches ma;
    if (OnigMatch(battleCastleTurnInfo, "^(.+?)(\\1)�c(\\d+)��ݎc(\\d+)���(.+?)(\\d+)(\\5)(\\6)(.+?)(\\d+)(\\9)(\\10)$", &ma)) {
        int nRemainTurn = stoi(ma[4], nullptr, 10);
        if (nPreviousCastleBattleTurn != nRemainTurn) {
            nPreviousCastleBattleTurn = nRemainTurn;

            // �܂��ŏ��̃^�[���ŁA���̏�ɋA�����镐���B�̃��X�g��T��
            if (nRemainTurn == 15) {
                string sCastleName = ma[1];

                �ď钆�̃A���x�h�̓G�����͐퓬�l���Œ�ƂȂ�(sCastleName);
            }
            OutputDebugStream("��U�߂̐퓬�^�[�����:" + battleCastleTurnInfo + "\n");
            OutputDebugStream("ma[1]:" + ma[1] + "\n");
            OutputDebugStream("ma[3]:" + ma[3] + "\n");
            OutputDebugStream("ma[5]" + ma[5] + "\n");
            OutputDebugStream("ma[6]" + ma[6] + "\n");
            OutputDebugStream("ma[9]" + ma[9] + "\n");
            OutputDebugStream("ma[10]" + ma[10] + "\n");
        }
    }

}

extern int iLastBattleRemainTurn;

void onCastleBattleEnd(string battleCastleEndInfo) {

    if (OnigMatch(
        battleCastleEndInfo,
        "���(.+?)��������s�k���܂���|"
        "���(.+?)�U�����͓P�ނ��܂���|"
        "���(.+?)�ŏI�^�[�����I�����܂���|"
        "���(.+?)�U�����͑S�ł��܂���|"
        "���(.+?)�U�������s�k���܂���|"
        "���(.+?)���U�ߗ��Ƃ��܂���|"
        "���(.+?)�����ʂ��܂���|"
        "���(.+?)���U�ߗ��Ƃ��܂���ł���|"
        "���(.+?)��D���܂���|"
        "���(.+?)���U�ߗ��Ƃ��܂���|"
        "���(.+?)���U�ߗ��Ƃ��܂���ł���"
    )
    ) {
    }

    iLastBattleRemainTurn = -1;
    nPreviousCastleBattleTurn = -1;
    reset����̃A���x�h�̓G�����̐퓬�l();
    OutputDebugStream("��U�߂̐퓬���I�����܂���\n\n" + battleCastleEndInfo + "\n");

    set�Q�[����ʃX�e�[�^�X(�Q�[����ʃX�e�[�^�X::�헪���);
}

// ���R�s���ȏI����
void onCastleBattleEnd() {
    iLastBattleRemainTurn = -1;
    nPreviousCastleBattleTurn = -1;
    reset�ď��̃A���x�h�̓G�����͐퓬�l();

    �A���x�h�̃��j�b�g���R����R�D�Ȃ畺������();

    OutputDebugStream("��U�߂̐퓬���I�����܂���\n\n" );

    set�Q�[����ʃX�e�[�^�X(�Q�[����ʃX�e�[�^�X::�헪���);
}

void onStrategyScreen() {
    OutputDebugStream("onStrategyScreen\n");
}

void onStrategyDaimyoturnChanged(string strategyTurnInfo) {
    Matches ma;
    if (OnigMatch(strategyTurnInfo, "^(.+?)��(\\1(.+?))\\1��\\2$", &ma)) {
        OutputDebugStream("�喼�^�[�����ς��܂����B" + ma[1] + "�Ƃ�" + ma[2] + "\n"s);

        int iBushouID = getStrategyTurnDaimyoBushouID();
        if (isValidBushouID(iBushouID)) {
			OutputDebugStream("�喼�^�[���̕�����"s + nb7�������[iBushouID].���� + "\n");
		}

        set�Q�[����ʃX�e�[�^�X(�Q�[����ʃX�e�[�^�X::�헪���);

        �A���x�h�̃��j�b�g���R����R�D�Ȃ畺������();
    }
}

void checkStrategyPlayerTurnInformation()
{
    int iBushouID = getStrategyTurnDaimyoBushouID();
    if (isValidBushouID(iBushouID)) {
        OutputDebugStream("�喼�^�[���̕�����"s + nb7�������[iBushouID].���� + "\n");
    }

}


extern void initAlbedoKahou();
void onStrategyPlayerDaimyoTurn(string strategyTurnInfo) {

    Matches ma;

    if (OnigMatch(strategyTurnInfo, "���(.+?)�l���Ȃ��̔ԂƂȂ�܂���", &ma)) {

        set�Q�[����ʃX�e�[�^�X(�Q�[����ʃX�e�[�^�X::�헪���);

        initAlbedoKahou();
        checkStrategyPlayerTurnInformation();

        �A���x�h�̃��j�b�g���R����R�D�Ȃ畺������();
        resetAlbedo�����鉺�⍦����();

        // �A���x�h���u�g�ҁv�Ȃ炨�����Œ���z�ێ�
        �A���x�h�g�҃��j�b�g���̂���������();

        OutputDebugStream("�v���C���[�S���喼�^�[��:" + ma[1]);
    }
}

void onBushouCyuseiChange(string chanteInfo) {
    Matches ma;

    if (OnigMatch(chanteInfo, "�m�F(.+)�̒����x��(\\d+)�ɂȂ�܂���", &ma)) {
        OutputDebugStream("����" + ma[1] + "�̒����l���A" + ma[2] + "�ւƕω����܂���\n");
    }
}

void onPerishedDaimyo(string perishedDaimyoInfo) {
	Matches ma;

    if (OnigMatch(perishedDaimyoInfo, "^(.+?)�Ƃ�\xA?�ŖS���܂���", &ma)) {
        resetAlbedo�����鉺�⍦����();

        OutputDebugStream("�喼" + ma[1] + "���ŖS���܂���\n");
        OutputDebugStream("��������\n");

    }
}

void onTouyouPrevious(string touyouInfo) {
	Matches ma;

    if (OnigMatch(touyouInfo, "^�o�p(.+?)����(\\d+?)�q�d(\\d+)", &ma)) {
        string �o�p���鑤�̕����� = ma[1];
        string �o�p���鑤�̐��� = ma[2];
        string �o�p���鑤�̒q�d = ma[3];
        if (�o�p���鑤�̕����� == getArubedoSeiMei()) {
            OutputDebugStream("�o�p����̂Ń��Z�b�g\n");
            resetAlbedo�����鉺�⍦����();
        }
    }
}

int dispatchEvent() {
    // ���K�\���ŏ󋵂𔻒f����
    const string bufferTextOut = getBufferTextOut();
    if (OnigMatch(bufferTextOut, "�����ݒ�.+�a�f�l���ʉ��A�j����Փxү���ޖ��U��퓐������ĐV�����Q�[�����n�߂�ꍇ�́u��ص�v��O��̑�������n�߂�ꍇ�́u۰�ށv��I�����Ă���������ص1��ص2��ص3��ص4��ص5��ص6��ص7��ص8��ص9��ص10���ؓ��ؓ��؏��㑬���x�S�ϔۑS�ϔۗL���L�����[�h")) {
        isYasenBattle = FALSE;
        onInitialGameMenu();
    }
    else if (OnigMatch(bufferTextOut, "���[�h�V�i���I.+\\d\\d/\\d\\d/\\d\\d\\d\\d:\\d\\d:\\d\\d")) {
        isYasenBattle = FALSE;
        onLoadSaveDataMenu();
    }
    else if (OnigMatch(bufferTextOut, "�Z�[�u�V�i���I.+\\d\\d/\\d\\d/\\d\\d\\d\\d:\\d\\d:\\d\\d")) {
        isYasenBattle = FALSE;
        onSaveSaveDataMenu();
    }
    else if (OnigMatch(bufferTextOut, "�d��---�N����.+���̎҂��̗p�Ȃ����܂����H")) {
        onShikanWindow();
    }
    /*
    else if (OnigMatch(bufferTextOut,
        "���̂��̂����A.+?���Ԃ��Ⴍ�ꂮ������f�Ȃ��悤�I|"
        "���Ȃ��ɏ����𒧂ނ�|"
        "����܂Œp���c���ȁI|"
        "���̎񂱂�.+?�����Վd��|"
        ".+?�̌R���������Ȃ��܂ŏR�U�炵�Ă���"
    )) {
        onYanseBattlePrePreStart();
    }
    */
    else if (OnigMatch(bufferTextOut, "�����:(.+?)�퓬:(\\d+?)�m�C:(\\d+?)����:(\\d+?)(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?�U����:(.+?)�퓬:(\\d+?)�m�C:(\\d+?)����:(\\d+?)(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(\\d+?)�N(\\d+?)���c��(\\d+?)�^�[��(.+?\\d�����̐�p)")) {
        // �����:�z�g�`���퓬:28�m�C:90����:3000:900:�c:900:�c:900:�c:900:�c:900:�c�U����:�D�c�M���퓬:103�m�C:90����:3000:1000:�`:1000:�`:1000:�`:1000:�`:1000:�`1551�N4���c��4�^�[���D�c�M���Ύz�g�`���D�c�M���R��1�����̐�p------------
        if (!isYasenBattle) {
            isYasenBattle = TRUE;
            onYasenBattleStart(bufferTextOut);
        }
        isYasenBattle = TRUE;
        onYasenBattleTurn(bufferTextOut);
    }
    else if (OnigMatch(bufferTextOut, "���(.+?)�l���Ȃ��̔ԂƂȂ�܂���")) {
        isYasenBattle = FALSE;
        onStrategyPlayerDaimyoTurn(bufferTextOut);
    }
    else if (OnigMatch(bufferTextOut, "�m�F(.+)�̒����x��(\\d+)�ɂȂ�܂���")) {
        onBushouCyuseiChange(bufferTextOut);
    }
    else if (
        OnigMatch(
            bufferTextOut,
            "���.+?������R����S�ł����܂���|"
            "���.+?������R�����S�ł��܂���|"
            "���.+?������R���̎m�C��(0|�O)�ɂ��܂���|"
            "���.+?������R���̎m�C��(0|�O)�ɂȂ�܂���|"
            "���.+?�͐�ꂩ��ދp���܂���|"
            "���.+?�����͂��܂���ł���|"
            "���.+?�R�̖{�w��S�ł����܂���|"
            "���.+?�R�̖{�w���S�ł��܂���|"
            "���.+?�𓢂����܂���|"
            "���.+?���펀���܂���|"
            "���.+?�𓢂����܂���|"
            "���.+?��(.+?)�̍U�����󂯂����Ȃ��Ŋ��𐋂���"
        )
        ) {
        onYasenBattleEnd(bufferTextOut);
        isYasenBattle = FALSE;
    }
    else if (OnigMatch(bufferTextOut, "^(.+?)(\\1)�c(\\d+)��ݎc(\\d+)���(.+?)(\\d+)(\\5)(\\6)(.+?)(\\d+)(\\9)(\\10)$")) {
        onCastleBattleTurn(bufferTextOut);
    }
    else if (
        OnigMatch(
            bufferTextOut,
            "���(.+?)��������s�k���܂���|"
            "���(.+?)�U�����͓P�ނ��܂���|"
            "���(.+?)�ŏI�^�[�����I�����܂���|"
            "���(.+?)�U�����͑S�ł��܂���|"
            "���(.+?)�U�������s�k���܂���|"
            "���(.+?)���U�ߗ��Ƃ��܂���|"
            "���(.+?)�����ʂ��܂���|"
            "���(.+?)���U�ߗ��Ƃ��܂���ł���|"
            "���(.+?)��D���܂���|"
            "���(.+?)���U�ߗ��Ƃ��܂���|"
            "���(.+?)���U�ߗ��Ƃ��܂���ł���"
        )
        ) {
        onCastleBattleEnd(bufferTextOut);
        isCastleBattle = FALSE;
    }
    else if (OnigMatch(bufferTextOut, "^.+�Ƃ�\xA?�ŖS���܂���")) {
        onPerishedDaimyo(bufferTextOut);
    }
    else if(OnigMatch(bufferTextOut, "^(.+?)��(\\1(.+?))\\1��\\2$")) {
        onStrategyDaimyoturnChanged(bufferTextOut);
    }
    else if (OnigMatch(bufferTextOut, "����g��(.+?)����(�e�����G|�R�Ȍ��p|���C�����L)�F�D�x(\\d+)")) {
        onChoteiKenjo(bufferTextOut);
    }
    else if (OnigMatch(bufferTextOut, "�����g��(.+?)�F�D�x(\\d+)")) {
        onDoumeiShisha(bufferTextOut);
    }
    else if (OnigMatch(bufferTextOut, "�v���g��(.+?)�F�D�x(\\d+)")) {
        onGoumotsuShisha(bufferTextOut);
    }
    else if (OnigMatch(bufferTextOut, "^�o�p(.+?)����(\\d+?)�q�d(\\d+)")) {
        onTouyouPrevious(bufferTextOut);
    }

    return 1;
}