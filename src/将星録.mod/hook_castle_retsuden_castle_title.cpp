/*
004BDFAA   892D 8CC86000    MOV DWORD PTR DS:[60C88C],EBP
004BDFB0   E8 3B8DFDFF      CALL Nobunaga.00496CF0
004BDFB5   50               PUSH EAX                           // ����EAX(=0x5D9638)�̐�Ɂu�閼 �ж�Łv������B
004BDFB6   68 0C0A5200      PUSH Nobunaga.00520A0C                   ; ASCII "%s"
004BDFBB   68 A8C86000      PUSH Nobunaga.0060C8A8                   ; ASCII "��R"

*/

// ���̃t�@�C���͒������s�B���ɗ����Ȃ��B�R���p�C���Ώۂ���O��Ă���

#include <windows.h>
#include <string>
#include "data_game_struct.h"
#include "output_debug_stream.h"
#include "game_process.h"


using namespace std;

#pragma unmanaged

extern void replaceMessage(string message);
extern std::pair<string, string> getOverrideCastleRetsuden(int iCastleID);


extern int iCastleIDCastleRetsudenShowBgn;
string strOnCastleDetailRequest = "";
void OnSSRExeCastleTitleExecute() {
	int iCastleID = iCastleIDCastleRetsudenShowBgn;
	strOnCastleDetailRequest = "";
	if (isValidCastleID(iCastleID)) {
		auto [title, detail] = getOverrideCastleRetsuden(iCastleID);
		if (title.size() > 0) {
			replaceMessage(title);
			strOnCastleDetailRequest = detail;
		}
	}
}

/*
004BDFAA   892D 8CC86000    MOV DWORD PTR DS:[60C88C],EBP
004BDFB0   E8 3B8DFDFF      CALL Nobunaga.00496CF0
004BDFB5   50               PUSH EAX                           // ����EAX(=0x5D9638)�̐�Ɂu�閼 �ж�Łv������B
004BDFB6   68 0C0A5200      PUSH Nobunaga.00520A0C                   ; ASCII "%s"
004BDFBB   68 A8C86000      PUSH Nobunaga.0060C8A8                   ; ASCII "��R"
*/

int pSSRExeJumpFromToOnSSRExeCastleTitle = 0x4BDFB0; // �֐��͂��̃A�h���X����AOnSSRExeCastleTitle�ւƃW�����v���Ă���B
int pSSRExeJumpCallFromToOnSSRExeCastleTitle = 0x496CF0; // ���X������������Call��
int pSSRExeReturnLblFromOnSSRExeCastleTitle = 0x4BDFB5; // �֐����Ō�܂ł����ƁA����TENSHOU.EXE���ɒ��ڃW�����v����

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeCastleTitle() {
	// �X�^�b�N�ɂ��߂Ă���
	__asm {

		call pSSRExeJumpCallFromToOnSSRExeCastleTitle // ���̏���

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeCastleTitleExecute();

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

		jmp pSSRExeReturnLblFromOnSSRExeCastleTitle
	}
}
#pragma warning(default: 4733) // ���[�j���O�̗}������������



char cmdOnSSRExeJumpFromCastleTitle[6] = "\xE9";
// ���̖��߂�5�o�C�g�A�Ȍ�̊֐��Ő��܂�閽�߂����v�T�o�C�g�Ȃ̂Łc �Ō�P�g��Ȃ�


// �j�[���j�b�N���������p
void WriteAsmJumperOnSSRExeCastleTitle() {

	// �܂��A�h���X�𐔎��Ƃ��Ĉ���
	int iAddress = (int)OnSSRExeCastleTitle;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeCastleTitle + 5);
	// �T�Ƃ����̂́A0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  �̖��߂ɕK�v�ȃo�C�g���B�v����ɂT�o�C�g�����Ǝ��̃j�[���j�b�N���ߌQ�Ɉړ�����̂��B�����Ă�������̍������W�����v����ۂ̖ړI�i�Ƃ��ė��p�����B
	memcpy(cmdOnSSRExeJumpFromCastleTitle + 1, &SubAddress, 4); // +1 ��E9�̎�����4�o�C�g�����������邩��B

	// �\�z�����j�[���j�b�N���߂�TENSHOU.EXE�̃������ɏ���������
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeCastleTitle), cmdOnSSRExeJumpFromCastleTitle, 5, NULL); //5�o�C�g�̂ݏ�������
}

#pragma managed
