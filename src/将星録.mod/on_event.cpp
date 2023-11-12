#include <windows.h>
#include "output_debug_stream.h"
#include "hook_textouta_custom.h"
#include "onigwrap.h"
#include "data_game_struct.h"
#include "bushou_arubedo.h"

void onOpeningMovie() {
	OutputDebugStream("�I�[�v�j���O���[�r�[\n");
}
// �Q�[���̏����ݒ���
void onInitialGameMenu() {
	OutputDebugStream("�����^�̏����ݒ���\n");
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

string previousBattleTurnInfo = "";
string previousRegexBattleTurnInfo = "";
void onBattleTurn(string battleTurnInfo) {
    OutputDebugStream("�퓬�^�[�����:" + battleTurnInfo + "\n");

    // �O��ƑS�������Ȃ�A�������Ȃ��B�����ł͂������Ƃňȉ��̐��K�\���ɍs���p�x�����炷
    if (previousBattleTurnInfo == battleTurnInfo) {
        return;
    }
    // �������A����̐퓬�^�[������ۑ�����
    else {
        previousBattleTurnInfo = battleTurnInfo;
    }

    Matches ma;

    if (OnigMatch(battleTurnInfo, "�����:(.+?)�퓬:(\\d+?)�m�C:(\\d+?)����:(\\d+?)(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?�U����:(.+?)�퓬:(\\d+?)�m�C:(\\d+?)����:(\\d+?)(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(\\d+?)�N(\\d+?)���c��(\\d+?)�^�[��(.+?\\d�����̐�p)", &ma)) {

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
        if (ma[1] == albedoSeiMei || ma[2] == albedoSeiMei) {
            overrideBushouAlbedo();
        }
    }
}

void onStrategyPlayerDaimyoTurn(string strategyTurnInfo) {
    Matches ma;

    if (OnigMatch(strategyTurnInfo, "���(.+?)�l���Ȃ��̔ԂƂȂ�܂���", &ma)) {
        OutputDebugStream("�v���C���[�S���喼�^�[��:" + ma[1]);
    }

    overrideBushouAlbedo();
}

void onBushouCyuseiChange(string chanteInfo) {
    Matches ma;

    if (OnigMatch(chanteInfo, "�m�F(.+)�̒����x��(\\d+)�ɂȂ�܂���", &ma)) {
        OutputDebugStream("����" + ma[1] + "�̒����l���A" + ma[2] + "�ւƕω����܂���\n");
    }

    overrideBushouAlbedo();
}



int dispatchEvent() {
    // ���K�\���ŏ󋵂𔻒f����
    const string bufferTextOut = getBufferTextOut();
    if (OnigMatch(bufferTextOut, "�����ݒ�.+�a�f�l���ʉ��A�j����Փxү���ޖ��U��퓐������ĐV�����Q�[�����n�߂�ꍇ�́u��ص�v��O��̑�������n�߂�ꍇ�́u۰�ށv��I�����Ă���������ص1��ص2��ص3��ص4��ص5��ص6��ص7��ص8��ص9��ص10���ؓ��ؓ��؏��㑬���x�S�ϔۑS�ϔۗL���L�����[�h")) {
        onInitialGameMenu();
    }
    else if (OnigMatch(bufferTextOut, "���[�h�V�i���I.+\\d\\d/\\d\\d/\\d\\d\\d\\d:\\d\\d:\\d\\d")) {
        onLoadSaveDataMenu();
    }
    else if (OnigMatch(bufferTextOut, "�Z�[�u�V�i���I.+\\d\\d/\\d\\d/\\d\\d\\d\\d:\\d\\d:\\d\\d")) {
        onSaveSaveDataMenu();
    }
    else if (OnigMatch(bufferTextOut, "�d��---�N����.+���̎҂��̗p�Ȃ����܂����H")) {
        onShikanWindow();
    }
    else if (OnigMatch(bufferTextOut, "�����:(.+?)�퓬:(\\d+?)�m�C:(\\d+?)����:(\\d+?)(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?�U����:(.+?)�퓬:(\\d+?)�m�C:(\\d+?)����:(\\d+?)(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(\\d+?)�N(\\d+?)���c��(\\d+?)�^�[��(.+?\\d�����̐�p)")) {
        // �����:�z�g�`���퓬:28�m�C:90����:3000:900:�c:900:�c:900:�c:900:�c:900:�c�U����:�D�c�M���퓬:103�m�C:90����:3000:1000:�`:1000:�`:1000:�`:1000:�`:1000:�`1551�N4���c��4�^�[���D�c�M���Ύz�g�`���D�c�M���R��1�����̐�p------------

        onBattleTurn(bufferTextOut);
    }
    else if (OnigMatch(bufferTextOut, "���(.+?)�l���Ȃ��̔ԂƂȂ�܂���")) {
        onStrategyPlayerDaimyoTurn(bufferTextOut);
    }
    else if (OnigMatch(bufferTextOut, "�m�F(.+)�̒����x��(\\d+)�ɂȂ�܂���")) {
        onBushouCyuseiChange(bufferTextOut);
    }
    return 1;
}