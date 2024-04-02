#include <windows.h>
#include "output_debug_stream.h"
#include "hook_textouta_custom.h"
#include "onigwrap.h"
#include "data_game_struct.h"
#include "bushou_albedo.h"
#include "game_screen.h"
#include "hook_functions_direct.h"
#include "on_event.h"
#include "usr_custom_mod.h"
using namespace ��;

void onOpeningMovie() {
    hookFunctionsDirect();
    set�Q�[����ʃX�e�[�^�X(�Q�[����ʃX�e�[�^�X::�N�����);
	OutputDebugStream("���I�[�v�j���O���[�r�[\n");
}

extern void resetMapBushouKoudouzumiCacheInMonth();
extern void resetCastleBattleInfo();
BOOL isYasenBattle = FALSE;
BOOL isCastleBattle = FALSE;
// �Q�[���̏����ݒ���
void onInitialGameMenu() {

    isYasenBattle = FALSE;
    isCastleBattle = FALSE;

    OutputDebugStream("�����^�̏����ݒ���\n");
    resetAlbedoKoudouCounter();
    resetMapBushouKoudouzumiCacheInMonth();
    resetCastleBattleInfo();
    set�Q�[����ʃX�e�[�^�X(�Q�[����ʃX�e�[�^�X::�����ݒ���);

    // C#�̃J�X�^��.mod.dll����̏㏑��
    try {
        System::Collections::Generic::Dictionary<System::String^, System::Object^>^ dic = gcnew System::Collections::Generic::Dictionary<System::String^, System::Object^>(5);
        System::Collections::Generic::Dictionary<System::String^, System::Object^>^ ret = InvokeUserMethod("on�����ݒ��ʎ�", dic);
    }
    catch (System::Exception^) {
        OutputDebugStream("on�����ݒ��ʎ��ŃG���[���������܂����B");
    }

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

void onMenuOriginalBushouEditStart() {
    OutputDebugStream("���j���[-�����ҏW���\n");
}

void onMenuOriginalShiroEditStart() {
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

void onDrawText(string text) {
    // C#�̃J�X�^��.mod.dll����̏㏑��
    try {
        System::Collections::Generic::Dictionary<System::String^, System::Object^>^ dic = gcnew System::Collections::Generic::Dictionary<System::String^, System::Object^>(5);
        dic->Add("�e�L�X�g", gcnew System::String(text.c_str()));
        System::Collections::Generic::Dictionary<System::String^, System::Object^>^ ret = InvokeUserMethod("on�e�L�X�g�`�掞", dic);
    }
    catch (System::Exception^) {
        OutputDebugStream("on�����ݒ��ʎ��ŃG���[���������܂����B");
    }
}

extern void initAlbedoKahou();

void onStrategyGameStart() {
    OutputDebugStream("�헪��ʂŃQ�[�����X�^�[�g���܂���\n");

    initAlbedoKahou();

    // C#�̃J�X�^��.mod.dll����̏㏑��
    try {
        System::Collections::Generic::Dictionary<System::String^, System::Object^>^ dic = gcnew System::Collections::Generic::Dictionary<System::String^, System::Object^>(5);
        System::Collections::Generic::Dictionary<System::String^, System::Object^>^ ret = InvokeUserMethod("on���C���Q�[���J�n��", dic);
    }
    catch (System::Exception^) {
        OutputDebugStream("on���C���Q�[���J�n��");
    }


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
    OutputDebugStream("���������đ���X�V %d\n ", (int)nb7�^�[�����.��);
}

void onUpdateSobaUma(int iSobaUma) {
    OutputDebugStream("���������n����X�V %d\n ", (int)nb7�^�[�����.��);
}

void onUpdateSobaTeppou(int iSobaTeppou) {

    OutputDebugStream("���������S�C����X�V %d\n ", (int)nb7�^�[�����.��);

    resetAlbedoKoudouCounter();

    resetMapBushouKoudouzumiCacheInMonth();

}

// �n�̑���̏��������݂����ꂽ
void onWriteSobaUma(int iSobaUma) {
}

// �S�C�̑���̏��������݂����ꂽ
void onWriteSobaTeppou(int iSobaTeppou) {
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

/*
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
*/

void onYasenBattleStart(int iAttackBushouID, int iDefendBushouID, int iAttackUnitID, int iDefendUnitID) {

}

void onYasenBattleTurn(int iRemainTurn, int iAttackBushouID, int iDefendBushouID, int iAttackUnitID, int iDefendUnitID) {

}

/*
string previousBattleTurnInfo = "";
string previousRegexBattleTurnInfo = "";

void onYasenBattleTurn(string battleYanseTurnInfo) {
    // OutputDebugStream("�퓬�^�[�����:" + battleYanseTurnInfo + "\n");

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
    }
}
*/

void onYasenButaiAttack(int iRemainTurn, int iAttackBushouID, int iButaiID, int iDefendBushouID) {
    OutputDebugStream("���݂̕����̍U���ɂ���\n");
    OutputDebugStream("�c��^�[��\n");
    OutputDebugStream("�U������" + getBushou����FromBushouID(iAttackBushouID) + "\n");
    OutputDebugStream("�U������%d\n", iButaiID);
    OutputDebugStream("�h�䕐��" + getBushou����FromBushouID(iDefendBushouID) + "\n");

    // C#�̃J�X�^��.mod.dll����̏㏑��
    try {
        System::Collections::Generic::Dictionary<System::String^, System::Object^>^ dic = gcnew System::Collections::Generic::Dictionary<System::String^, System::Object^>(5);
        dic->Add("�c��^�[��", iRemainTurn);
        dic->Add("�U�������ԍ�", iAttackBushouID);
        dic->Add("�U�������ԍ�", iButaiID);
        dic->Add("�h�䕐���ԍ�", iDefendBushouID);
        System::Collections::Generic::Dictionary<System::String^, System::Object^>^ ret = InvokeUserMethod("on��핔���s���O", dic);
    }
    catch (System::Exception^) {
        OutputDebugStream("on�헪��ʑ喼�^�[���ύX���ŃG���[���������܂����B");
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

    OutputDebugStream("���̐퓬���I�����܂���\n\n" + endYanseBattleInfo + "\n");

    set�Q�[����ʃX�e�[�^�X(�Q�[����ʃX�e�[�^�X::�헪���);

    isYasenBattle = FALSE;
}

extern int hookYasenBattleStart;
// ���R�s���ȏI����
void onYasenBattleEnd() {
    if (hookYasenBattleStart) {

        // C#�̃J�X�^��.mod.dll����̏㏑��
        try {
            System::Collections::Generic::Dictionary<System::String^, System::Object^>^ dic = gcnew System::Collections::Generic::Dictionary<System::String^, System::Object^>(5);
            System::Collections::Generic::Dictionary<System::String^, System::Object^>^ ret = InvokeUserMethod("on���I����", dic);
        }
        catch (System::Exception^) {
            OutputDebugStream("on���I�����ɃG���[���������܂���");
        }


        reset����̃A���x�h�̓G�����̐퓬�l();

        �A���x�h�̃��j�b�g���R����R�D�Ȃ畺������();

        OutputDebugStream("���̐퓬���I�����܂���\n\n");
    }

    set�Q�[����ʃX�e�[�^�X(�Q�[����ʃX�e�[�^�X::�헪���);

    isYasenBattle = FALSE;
}

void onCastleBattlePreStart() {
    isCastleBattle = TRUE;

    �A���x�h�̃��j�b�g���R����R�D�Ȃ畺������();

    set�Q�[����ʃX�e�[�^�X(�Q�[����ʃX�e�[�^�X::�ď����);

    OutputDebugStream("��U�߂̐퓬���J�n���܂���\n");
}

void onCastleBattleStart(int iCastleID, int iAttackDaimyoID, int iDefendDaimyoID) {
    // C#�̃J�X�^��.mod.dll����̏㏑��
    try {
        System::Collections::Generic::Dictionary<System::String^, System::Object^>^ dic = gcnew System::Collections::Generic::Dictionary<System::String^, System::Object^>(5);
        dic->Add("��ԍ�", iCastleID);
        dic->Add("�U���喼�ԍ�", iAttackDaimyoID);
        dic->Add("�h��喼�ԍ�", iDefendDaimyoID);
        System::Collections::Generic::Dictionary<System::String^, System::Object^>^ ret = InvokeUserMethod("on�ď��J�n��", dic);
    }
    catch (System::Exception^) {
        OutputDebugStream("on�ď��J�n���ɃG���[���������܂���");
    }
}

int nPreviousCastleBattleTurn = -1;
void onCastleBattleTurn(string battleCastleTurnInfo) {
    Matches ma;
    if (OnigMatch(battleCastleTurnInfo, "^(.+?)(\\1)�c(\\d+)��ݎc(\\d+)���(.+?)(\\d+)(\\5)(\\6)(.+?)(\\d+)(\\9)(\\10)$", &ma)) {
        int nRemainTurn = stoi(ma[4], nullptr, 10);
        if (nPreviousCastleBattleTurn != nRemainTurn) {
            nPreviousCastleBattleTurn = nRemainTurn;

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

void onCastleBattleTurn(int iRemainTurn) {
    // C#�̃J�X�^��.mod.dll����̏㏑��
    try {
        System::Collections::Generic::Dictionary<System::String^, System::Object^>^ dic = gcnew System::Collections::Generic::Dictionary<System::String^, System::Object^>(5);
        dic->Add("�c��^�[��", iRemainTurn);
        System::Collections::Generic::Dictionary<System::String^, System::Object^>^ ret = InvokeUserMethod("on�ď��c��^�[���ύX��", dic);
    }
    catch (System::Exception^) {
        OutputDebugStream("on�ď��c��^�[���ύX���ɃG���[���������܂���");
    }
}


extern int iLastBattleRemainTurn;
extern bool isCastleBattleMode;

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
    �A���x�h�̃��j�b�g���R����R�D�Ȃ畺������();
    OutputDebugStream("��U�߂̐퓬���I�����܂���\n\n" + battleCastleEndInfo + "\n");
    set�Q�[����ʃX�e�[�^�X(�Q�[����ʃX�e�[�^�X::�헪���);
    isCastleBattle = FALSE;
}

// ���R�s���ȏI����
void onCastleBattleEnd() {
    if (isCastleBattleMode) {
        iLastBattleRemainTurn = -1;
        nPreviousCastleBattleTurn = -1;
        reset�ď��̃A���x�h�̓G�����͐퓬�l();
        �A���x�h�̃��j�b�g���R����R�D�Ȃ畺������();
        OutputDebugStream("��U�߂̐퓬���I�����܂���\n\n");

        try {
			System::Collections::Generic::Dictionary<System::String^, System::Object^>^ dic = gcnew System::Collections::Generic::Dictionary<System::String^, System::Object^>(5);
			System::Collections::Generic::Dictionary<System::String^, System::Object^>^ ret = InvokeUserMethod("on�ď��I����", dic);
		}
        catch (System::Exception^) {
            OutputDebugStream("on�ď��I�����ɃG���[���������܂���");
        }
        set�Q�[����ʃX�e�[�^�X(�Q�[����ʃX�e�[�^�X::�헪���);
    }
    isCastleBattle = FALSE;
}

void onStrategyScreen() {
    OutputDebugStream("onStrategyScreen\n");
}

void onStrategyDaimyoTurnChanged(int iDaimyoID) {
    if (isValidDaimyoID(iDaimyoID)) {
        �A���x�h�̃��j�b�g���R����R�D�Ȃ畺������();

        // C#�̃J�X�^��.mod.dll����̏㏑��
        try {
            int iBushouID = getBushouIDFromDaimyoID(iDaimyoID);
            if (isValidBushouID(iBushouID)) {
                OutputDebugStream("�喼�^�[���̕�����"s + nb7�������[iBushouID].���� + "\n");
                System::Collections::Generic::Dictionary<System::String^, System::Object^>^ dic = gcnew System::Collections::Generic::Dictionary<System::String^, System::Object^>(5);
                dic->Add("�喼�ԍ�", iDaimyoID);
                dic->Add("�����ԍ�", iBushouID);
                System::Collections::Generic::Dictionary<System::String^, System::Object^>^ ret = InvokeUserMethod("on�헪��ʑ喼�^�[���ύX�O", dic);
            }
        }
        catch (System::Exception^ ) {
            OutputDebugStream("on�헪��ʑ喼�^�[���ύX���ŃG���[���������܂����B");
        }

    }
}


void onStrategyPlayerDaimyoTurn(int iDaimyoID) {
    set�Q�[����ʃX�e�[�^�X(�Q�[����ʃX�e�[�^�X::�헪���);

    if (isValidDaimyoID(iDaimyoID)) {

        // C#�̃J�X�^��.mod.dll����̏㏑��
        try {
            int iBushouID = getBushouIDFromDaimyoID(iDaimyoID);
            if (isValidBushouID(iBushouID)) {
                OutputDebugStream("�喼�^�[���̕�����"s + nb7�������[iBushouID].���� + "\n");
                System::Collections::Generic::Dictionary<System::String^, System::Object^>^ dic = gcnew System::Collections::Generic::Dictionary<System::String^, System::Object^>(5);
                dic->Add("�喼�ԍ�", iDaimyoID);
                dic->Add("�����ԍ�", iBushouID);
                System::Collections::Generic::Dictionary<System::String^, System::Object^>^ ret = InvokeUserMethod("on�헪��ʃv���C���喼�^�[���ύX�O", dic);
            }
        }
        catch (System::Exception^) {
            OutputDebugStream("on�헪��ʑ喼�^�[���ύX���ŃG���[���������܂����B");
        }
    }

    �A���x�h�̃��j�b�g���R����R�D�Ȃ畺������();
    resetAlbedo�����鉺�⍦����();

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
    /*
    if (OnigMatch(bufferTextOut, "�����ݒ�.+�a�f�l���ʉ��A�j����Փxү���ޖ��U��퓐������ĐV�����Q�[�����n�߂�ꍇ�́u��ص�v��O��̑�������n�߂�ꍇ�́u۰�ށv��I�����Ă���������ص1��ص2��ص3��ص4��ص5��ص6��ص7��ص8��ص9��ص10���ؓ��ؓ��؏��㑬���x�S�ϔۑS�ϔۗL���L�����[�h")) {
        isYasenBattle = FALSE;
        onInitialGameMenu();
    }
    */
    if (OnigMatch(bufferTextOut, "���[�h�V�i���I.+\\d\\d/\\d\\d/\\d\\d\\d\\d:\\d\\d:\\d\\d")) {
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
    /*
    else if (OnigMatch(bufferTextOut, "�����:(.+?)�퓬:(\\d+?)�m�C:(\\d+?)����:(\\d+?)(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?�U����:(.+?)�퓬:(\\d+?)�m�C:(\\d+?)����:(\\d+?)(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(\\d+?)�N(\\d+?)���c��(\\d+?)�^�[��(.+?\\d�����̐�p)")) {
        // �����:�z�g�`���퓬:28�m�C:90����:3000:900:�c:900:�c:900:�c:900:�c:900:�c�U����:�D�c�M���퓬:103�m�C:90����:3000:1000:�`:1000:�`:1000:�`:1000:�`:1000:�`1551�N4���c��4�^�[���D�c�M���Ύz�g�`���D�c�M���R��1�����̐�p------------
        if (!isYasenBattle) {
            isYasenBattle = TRUE;
            onYasenBattleStart(bufferTextOut);
        }
        isYasenBattle = TRUE;
        onYasenBattleTurn(bufferTextOut);
    }
    */
    /*
    else if (OnigMatch(bufferTextOut, "���(.+?)�l���Ȃ��̔ԂƂȂ�܂���")) {
    }
    */
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