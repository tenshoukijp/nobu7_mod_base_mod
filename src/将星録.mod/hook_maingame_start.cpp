/*
�V�i���I����̑I���A�������́A���[�h����ŃQ�[�����J�n�����B


00460172   > 8BCE           MOV ECX,ESI                              ;  Case 5 of switch 004600F6
00460174   . E8 374AFDFF    CALL Nobunaga.00434BB0
00460179   . E9 B5000000    JMP Nobunaga.00460233
*/


#include <windows.h>
#include <string>
#include "game_process.h"
#include "output_debug_stream.h"

using namespace std;

#pragma unmanaged

extern void onStrategyGameStart();

void OnSSRExeMainGameStartExecute() {
	OutputDebugStream("�����������C���Q�[�����J�n���܂���\n");
	onStrategyGameStart();
}


/*
00460172   > 8BCE           MOV ECX,ESI                              ;  Case 5 of switch 004600F6
00460174   . E8 374AFDFF    CALL Nobunaga.00434BB0
00460179   . E9 B5000000    JMP Nobunaga.00460233
*/




int pSSRExeJumpFromToOnSSRExeMainGameStart = 0x460174; // �֐��͂��̃A�h���X����AOnSSRExeMainGameStart�ւƃW�����v���Ă���B
int pSSRExeJumpCallFromToOnSSRExeMainGameStart = 0x434BB0; // ���X������������Call��
int pSSRExeReturnLblFromOnSSRExeMainGameStart = 0x460179; // �֐����Ō�܂ł����ƁA���̎��sexe���ɒ��ڃW�����v����

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeMainGameStart() {
	// �X�^�b�N�ɂ��߂Ă���
	__asm {

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeMainGameStartExecute();

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

		call pSSRExeJumpCallFromToOnSSRExeMainGameStart // ���̏���

		jmp pSSRExeReturnLblFromOnSSRExeMainGameStart
	}
}
#pragma warning(default: 4733) // ���[�j���O�̗}������������



char cmdOnSSRExeJumpFromMainGameStart[6] = "\xE9";
// ���̖��߂�5�o�C�g�A�Ȍ�̊֐��Ő��܂�閽�߂����v�T�o�C�g�Ȃ̂Łc �Ō�P�g��Ȃ�


// �j�[���j�b�N���������p
void WriteAsmJumperOnSSRExeMainGameStart() {

	// �܂��A�h���X�𐔎��Ƃ��Ĉ���
	int iAddress = (int)OnSSRExeMainGameStart;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeMainGameStart + 5);
	// �T�Ƃ����̂́A0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  �̖��߂ɕK�v�ȃo�C�g���B�v����ɂT�o�C�g�����Ǝ��̃j�[���j�b�N���ߌQ�Ɉړ�����̂��B�����Ă�������̍������W�����v����ۂ̖ړI�i�Ƃ��ė��p�����B
	memcpy(cmdOnSSRExeJumpFromMainGameStart + 1, &SubAddress, 4); // +1 ��E9�̎�����4�o�C�g�����������邩��B

	// �\�z�����j�[���j�b�N���߂����sexe�̃������ɏ���������
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeMainGameStart), cmdOnSSRExeJumpFromMainGameStart, 5, NULL); //5�o�C�g�̂ݏ�������
}

#pragma managed
