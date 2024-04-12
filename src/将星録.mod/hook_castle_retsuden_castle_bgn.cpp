
/*
004BDEE4   8B8E 80000000    MOV ECX,DWORD PTR DS:[ESI+80]   // ECX�͏���̊Y����ւ̃|�C���^
004BDEEA   50               PUSH EAX
004BDEEB   E8 D0DEFEFF      CALL Nobunaga.004ABDC0
004BDEF0   8B08             MOV ECX,DWORD PTR DS:[EAX]

*/



// ���̃t�@�C���͒������s�B���ɗ����Ȃ��B�R���p�C���Ώۂ���O��Ă���

#include <windows.h>
#include <string>
#include "data_game_struct.h"
#include "output_debug_stream.h"
#include "data_castle_struct.h"
#include "game_process.h"


using namespace std;

#pragma unmanaged

int iCastleIDCastleRetsudenShowBgn = -1;
static int iCastleRetsudenShowBgnECX = -1; // �Ώۉƕ�ւ̃|�C���^�B�ƕ�z��ւ̓���̃|�C���^
void OnSSRExeCastleRetsudenShowBgnExecute() {
	OutputDebugStream("CastleRetsudenShowBgn:%x", iCastleRetsudenShowBgnECX);
	int iCastleID = (iCastleRetsudenShowBgnECX - ����A�h���X) / sizeof(NB7����^);
	if (isValidCastleID(iCastleID)) {
		iCastleIDCastleRetsudenShowBgn = iCastleID;
		OutputDebugStream("����������ID:%d!!!��\n", iCastleID);
	}
}

/*
004BDEE4   8B8E 80000000    MOV ECX,DWORD PTR DS:[ESI+80]   // ECX�͏���̊Y����ւ̃|�C���^
004BDEEA   50               PUSH EAX
004BDEEB   E8 D0DEFEFF      CALL Nobunaga.004ABDC0
004BDEF0   8B08             MOV ECX,DWORD PTR DS:[EAX]

*/
int pSSRExeJumpFromToOnSSRExeCastleRetsudenShowBgn = 0x4BDEEB; // �֐��͂��̃A�h���X����AOnSSRExeCastleRetsudenShowBgn�ւƃW�����v���Ă���B
int pSSRExeJumpCallFromToOnSSRExeCastleRetsudenShowBgn = 0x4ABDC0; // ���X������������Call��
int pSSRExeReturnLblFromOnSSRExeCastleRetsudenShowBgn = 0x4BDEF0; // �֐����Ō�܂ł����ƁA���̎��sexe���ɒ��ڃW�����v����

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeCastleRetsudenShowBgn() {
	// �X�^�b�N�ɂ��߂Ă���
	__asm {
		mov iCastleRetsudenShowBgnECX, ecx
		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeCastleRetsudenShowBgnExecute();

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

		call pSSRExeJumpCallFromToOnSSRExeCastleRetsudenShowBgn // ���̏���

		jmp pSSRExeReturnLblFromOnSSRExeCastleRetsudenShowBgn
	}
}
#pragma warning(default: 4733) // ���[�j���O�̗}������������



char cmdOnSSRExeJumpFromCastleRetsudenShowBgn[6] = "\xE9";
// ���̖��߂�5�o�C�g�A�Ȍ�̊֐��Ő��܂�閽�߂����v�T�o�C�g�Ȃ̂Łc �Ō�P�g��Ȃ�


// �j�[���j�b�N���������p
void WriteAsmJumperOnSSRExeCastleRetsudenShowBgn() {

	// �܂��A�h���X�𐔎��Ƃ��Ĉ���
	int iAddress = (int)OnSSRExeCastleRetsudenShowBgn;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeCastleRetsudenShowBgn + 5);
	// �T�Ƃ����̂́A0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  �̖��߂ɕK�v�ȃo�C�g���B�v����ɂT�o�C�g�����Ǝ��̃j�[���j�b�N���ߌQ�Ɉړ�����̂��B�����Ă�������̍������W�����v����ۂ̖ړI�i�Ƃ��ė��p�����B
	memcpy(cmdOnSSRExeJumpFromCastleRetsudenShowBgn + 1, &SubAddress, 4); // +1 ��E9�̎�����4�o�C�g�����������邩��B

	// �\�z�����j�[���j�b�N���߂�TENSHOU.EXE�̃������ɏ���������
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeCastleRetsudenShowBgn), cmdOnSSRExeJumpFromCastleRetsudenShowBgn, 5, NULL); //5�o�C�g�̂ݏ�������
}

#pragma managed
