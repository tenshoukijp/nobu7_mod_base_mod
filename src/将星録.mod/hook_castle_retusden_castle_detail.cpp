/*
004BDFE2   C705 8CC86000 40>MOV DWORD PTR DS:[60C88C],40
004BDFEC   E8 FF8CFDFF      CALL Nobunaga.00496CF0
004BDFF1   50               PUSH EAX
004BDFF2   68 0C0A5200      PUSH Nobunaga.00520A0C                   ; ASCII "%s"
004BDFF7   68 A8C86000      PUSH Nobunaga.0060C8A8                   ; ASCII "��R"
004BDFFC   E8 D1650400      CALL Nobunaga.005045D2
004BE001   83C4 48          ADD ESP,48
*/


// ���̃t�@�C���͒������s�B���ɗ����Ȃ��B�R���p�C���Ώۂ���O��Ă���

#include <windows.h>
#include <string>
#include "data_game_struct.h"
#include "data_bushou_struct.h"
#include "output_debug_stream.h"
#include "data_kahou_struct.h"
#include "data_kanni_struct.h"
#include "data_yakusyoku_struct.h"
#include "data_castle_struct.h"
#include "data_turn_struct.h"
#include "game_screen.h"
#include "game_process.h"
#include "on_serihu_message.h"
#include "bushou_albedo.h"
#include "game_screen.h"
#include "message_albedo.h"


using namespace std;

#pragma unmanaged

extern void replaceMessage(string message);
extern std::pair<string, string> getOverrideCastleRetsuden(int iCastleID);


extern int iCastleIDCastleRetsudenShowBgn;

extern string strOnCastleDetailRequest;
void OnSSRExeCastleDetailExecute() {
	int iCastleID = iCastleIDCastleRetsudenShowBgn;
	if (isValidCastleID(iCastleID)) {
		string detail = strOnCastleDetailRequest;
		if (detail.size() > 0) {
			replaceMessage(detail);
		}
	}
}

/*
004BDFE2   C705 8CC86000 40>MOV DWORD PTR DS:[60C88C],40
004BDFEC   E8 FF8CFDFF      CALL Nobunaga.00496CF0
004BDFF1   50               PUSH EAX
004BDFF2   68 0C0A5200      PUSH Nobunaga.00520A0C                   ; ASCII "%s"
004BDFF7   68 A8C86000      PUSH Nobunaga.0060C8A8                   ; ASCII "��R"
004BDFFC   E8 D1650400      CALL Nobunaga.005045D2
004BE001   83C4 48          ADD ESP,48
*/
int pSSRExeJumpFromToOnSSRExeCastleDetail = 0x4BDFEC; // �֐��͂��̃A�h���X����AOnSSRExeCastleDetail�ւƃW�����v���Ă���B
int pSSRExeJumpCallFromToOnSSRExeCastleDetail = 0x496CF0; // ���X������������Call��
int pSSRExeReturnLblFromOnSSRExeCastleDetail = 0x4BDFF1; // �֐����Ō�܂ł����ƁA����TENSHOU.EXE���ɒ��ڃW�����v����

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeCastleDetail() {
	// �X�^�b�N�ɂ��߂Ă���
	__asm {

		call pSSRExeJumpCallFromToOnSSRExeCastleDetail // ���̏���

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeCastleDetailExecute();

	// �X�^�b�N�Ɉ����o��
	__asm {
		pop edi
		pop esi
		pop ebp
		pop esp
		pop edx
		pop ecx
		pop ebx
		pop eax

		jmp pSSRExeReturnLblFromOnSSRExeCastleDetail
	}
}
#pragma warning(default: 4733) // ���[�j���O�̗}������������



char cmdOnSSRExeJumpFromCastleDetail[6] = "\xE9";
// ���̖��߂�5�o�C�g�A�Ȍ�̊֐��Ő��܂�閽�߂����v�T�o�C�g�Ȃ̂Łc �Ō�P�g��Ȃ�


// �j�[���j�b�N���������p
void WriteAsmJumperOnSSRExeCastleDetail() {

	// �܂��A�h���X�𐔎��Ƃ��Ĉ���
	int iAddress = (int)OnSSRExeCastleDetail;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeCastleDetail + 5);
	// �T�Ƃ����̂́A0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  �̖��߂ɕK�v�ȃo�C�g���B�v����ɂT�o�C�g�����Ǝ��̃j�[���j�b�N���ߌQ�Ɉړ�����̂��B�����Ă�������̍������W�����v����ۂ̖ړI�i�Ƃ��ė��p�����B
	memcpy(cmdOnSSRExeJumpFromCastleDetail + 1, &SubAddress, 4); // +1 ��E9�̎�����4�o�C�g�����������邩��B

	// �\�z�����j�[���j�b�N���߂�TENSHOU.EXE�̃������ɏ���������
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeCastleDetail), cmdOnSSRExeJumpFromCastleDetail, 5, NULL); //5�o�C�g�̂ݏ�������
}

#pragma managed
