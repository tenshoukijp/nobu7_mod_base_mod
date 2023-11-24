#include <windows.h>
#include "output_debug_stream.h"
#include "hook_textouta_custom.h"
#include "onigwrap.h"
#include "data_game_struct.h"
#include "bushou_albedo.h"
#include "game_screen.h"
#include "hook_functions_direct.h"
void onOpeningMovie() {
    hookFunctionsDirect();
    set�Q�[����ʃX�e�[�^�X(�Q�[����ʃX�e�[�^�X::�N�����);
	OutputDebugStream("�I�[�v�j���O���[�r�[\n");
}
// �Q�[���̏����ݒ���
void onInitialGameMenu() {
    set�Q�[����ʃX�e�[�^�X(�Q�[����ʃX�e�[�^�X::�����ݒ���);
    OutputDebugStream("�����^�̏����ݒ���\n");
    resetAlbedoKoudouCounter();
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

/*
void onYanseBattlePrePreStart() {
    OutputDebugStream("���ɂ�����������܂�\n\n");

    resetAlbedoUnitHeisuu();
}
*/

void onYasenBattlePreStart() {
    OutputDebugStream("���̐퓬���J�n���܂���\n\n");
    set�Q�[����ʃX�e�[�^�X(�Q�[����ʃX�e�[�^�X::�����);

    resetAlbedoUnitHeisuu();
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
            overrideYasenBattleAbirityChangeAlbedo(syubigawa, kougekigawa);
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

    resetYasenBattleAbirityChangeAlbedo();

    resetAlbedoUnitHeisuu();

    OutputDebugStream("���̐퓬���I�����܂���\n\n" + endYanseBattleInfo + "\n");

    set�Q�[����ʃX�e�[�^�X(�Q�[����ʃX�e�[�^�X::�헪���);
}

// ���R�s���ȏI����
void onYasenBattleEnd() {
    resetYasenBattleAbirityChangeAlbedo();

    resetAlbedoUnitHeisuu();

    OutputDebugStream("���̐퓬���I�����܂���\n\n");

    set�Q�[����ʃX�e�[�^�X(�Q�[����ʃX�e�[�^�X::�헪���);
}

BOOL isCastleBattle = FALSE;
void onCastleBattlePreStart() {
    isCastleBattle = TRUE;

    resetAlbedoUnitHeisuu();

    set�Q�[����ʃX�e�[�^�X(�Q�[����ʃX�e�[�^�X::�ď����);

    OutputDebugStream("��U�߂̐퓬���J�n���܂���\n");
}

void onCastleBattleTurn(string battleCastleTurnInfo) {
	OutputDebugStream("��U�߂̐퓬�^�[�����:" + battleCastleTurnInfo + "\n");
}

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

    resetYasenBattleAbirityChangeAlbedo();

    OutputDebugStream("��U�߂̐퓬���I�����܂���\n\n" + battleCastleEndInfo + "\n");

    set�Q�[����ʃX�e�[�^�X(�Q�[����ʃX�e�[�^�X::�헪���);
}

// ���R�s���ȏI����
void onCastleBattleEnd() {
    resetYasenBattleAbirityChangeAlbedo();

    resetAlbedoUnitHeisuu();

    OutputDebugStream("��U�߂̐퓬���I�����܂���\n\n" );

    set�Q�[����ʃX�e�[�^�X(�Q�[����ʃX�e�[�^�X::�헪���);
}

void onStrategyDaimyoturnChanged(string strategyTurnInfo) {
    Matches ma;
    if (OnigMatch(strategyTurnInfo, "^(.+?)��(\\1(.+?))\\1��\\2$", &ma)) {
        OutputDebugStream("�喼�^�[�����ς��܂����B" + ma[1] + "�Ƃ�" + ma[2] + "\n"s);

        set�Q�[����ʃX�e�[�^�X(�Q�[����ʃX�e�[�^�X::�헪���);

        resetAlbedoUnitHeisuu();
    }

}

void onStrategyPlayerDaimyoTurn(string strategyTurnInfo) {

    Matches ma;

    if (OnigMatch(strategyTurnInfo, "���(.+?)�l���Ȃ��̔ԂƂȂ�܂���", &ma)) {

        set�Q�[����ʃX�e�[�^�X(�Q�[����ʃX�e�[�^�X::�헪���);

        // �A���x�h�̍s���ς݃J�E���^�[�̃��Z�b�g
        resetAlbedoKoudouCounter();
        resetAlbedoUnitHeisuu();

        OutputDebugStream("�v���C���[�S���喼�^�[��:" + ma[1]);
    }
}

void onBushouCyuseiChange(string chanteInfo) {
    Matches ma;

    if (OnigMatch(chanteInfo, "�m�F(.+)�̒����x��(\\d+)�ɂȂ�܂���", &ma)) {
        OutputDebugStream("����" + ma[1] + "�̒����l���A" + ma[2] + "�ւƕω����܂���\n");
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
    else if(OnigMatch(bufferTextOut, "^(.+?)��(\\1(.+?))\\1��\\2$")) {
        onStrategyDaimyoturnChanged(bufferTextOut);
    }

    return 1;
}