/*
004C46AA   50               PUSH EAX
004C46AB   51               PUSH ECX
004C46AC   E8 FFBDF7FF      CALL Nobunaga.004404B0
004C46B1   83C4 08          ADD ESP,8
004C46B4   8946 3A          MOV DWORD PTR DS:[ESI+3A],EAX
004C46B7   5E               POP ESI
004C46B8   C2 0400          RETN 4
*/





#include <windows.h>
#include "output_debug_stream.h"
#include "on_event.h"
#include "game_process.h"


using namespace std;

#pragma unmanaged

int iUpdateSobaUmaEAX = -1;
void OnSSRExeUpdateSobaUmaExecute() {
	OutputDebugStream("���������n���ꂪ�X�V����܂���!!!:%d\n", iUpdateSobaUmaEAX);
	onUpdateSobaUma(iUpdateSobaUmaEAX);
}


/*
004C46AA   50               PUSH EAX
004C46AB   51               PUSH ECX
004C46AC   E8 FFBDF7FF      CALL Nobunaga.004404B0
004C46B1   83C4 08          ADD ESP,8
004C46B4   8946 3A          MOV DWORD PTR DS:[ESI+3A],EAX
004C46B7   5E               POP ESI
004C46B8   C2 0400          RETN 4
*/



int pSSRExeJumpFromToOnSSRExeUpdateSobaUma = 0x4C46AC; // �֐��͂��̃A�h���X����AOnSSRExeUpdateSobaUma�ւƃW�����v���Ă���B
int pSSRExeJumpCallFromToOnSSRExeUpdateSobaUma = 0x4404B0; // ���X������������Call��
int pSSRExeReturnLblFromOnSSRExeUpdateSobaUma = 0x4C46B1; // �֐����Ō�܂ł����ƁA���̎��sexe���ɒ��ڃW�����v����

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeUpdateSobaUma() {
	// �X�^�b�N�ɂ��߂Ă���
	__asm {

		call pSSRExeJumpCallFromToOnSSRExeUpdateSobaUma // ���̏���

		mov iUpdateSobaUmaEAX, EAX

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeUpdateSobaUmaExecute();

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

		mov iUpdateSobaUmaEAX, EAX

		jmp pSSRExeReturnLblFromOnSSRExeUpdateSobaUma
	}
}
#pragma warning(default: 4733) // ���[�j���O�̗}������������



char cmdOnSSRExeJumpFromUpdateSobaUma[6] = "\xE9";
// ���̖��߂�5�o�C�g�A�Ȍ�̊֐��Ő��܂�閽�߂����v�T�o�C�g�Ȃ̂Łc �Ō�P�g��Ȃ�


// �j�[���j�b�N���������p
void WriteAsmJumperOnSSRExeUpdateSobaUma() {

	// �܂��A�h���X�𐔎��Ƃ��Ĉ���
	int iAddress = (int)OnSSRExeUpdateSobaUma;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeUpdateSobaUma + 5);
	// �T�Ƃ����̂́A0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  �̖��߂ɕK�v�ȃo�C�g���B�v����ɂT�o�C�g�����Ǝ��̃j�[���j�b�N���ߌQ�Ɉړ�����̂��B�����Ă�������̍������W�����v����ۂ̖ړI�i�Ƃ��ė��p�����B
	memcpy(cmdOnSSRExeJumpFromUpdateSobaUma + 1, &SubAddress, 4); // +1 ��E9�̎�����4�o�C�g�����������邩��B

	// �\�z�����j�[���j�b�N���߂����sexe�̃������ɏ���������
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeUpdateSobaUma), cmdOnSSRExeJumpFromUpdateSobaUma, 5, NULL); //5�o�C�g�̂ݏ�������
}

#pragma managed
