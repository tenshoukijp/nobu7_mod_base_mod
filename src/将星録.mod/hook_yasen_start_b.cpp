/*
�Q�ƃf�[�^ �F Nobunaga:.text -> 00479FA0
���ڽ      �ި�������                                ����
00479FA0   PUSH ESI                                  (CPU����޳�ł̑I���ӏ�)
0047A139   CALL Nobunaga.00479FA0
0048CCFC   CALL Nobunaga.00479FA0
*/

/*
0048CCFC   E8 9FD2FEFF      CALL Nobunaga.00479FA0
0048CD01   8BCE             MOV ECX,ESI
*/




#include <windows.h>
#include <string>
#include "output_debug_stream.h"
#include "game_process.h"


using namespace std;

#pragma unmanaged

extern BOOL hookYasenBattleStart;
extern BOOL hookYasenBattleFirstTurn;

void OnSSRExeYasenBattleStartBLocExecute() {
	hookYasenBattleStart = 1;
	hookYasenBattleFirstTurn = 1;
	OutputDebugStream("�����������J�nB�|�C���g��������\n");
}

/*
0048CCFC   E8 9FD2FEFF      CALL Nobunaga.00479FA0
0048CD01   8BCE             MOV ECX,ESI
*/
int pSSRExeJumpFromToOnSSRExeYasenBattleStartBLoc = 0x48CCFC; // �֐��͂��̃A�h���X����AOnSSRExeYasenBattleStartBLoc�ւƃW�����v���Ă���B
int pSSRExeJumpCallFromToOnSSRExeYasenBattleStartBLoc = 0x479FA0; // ���X������������Call��
int pSSRExeReturnLblFromOnSSRExeYasenBattleStartBLoc = 0x48CD01; // �֐����Ō�܂ł����ƁA���̎��sexe���ɒ��ڃW�����v����

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeYasenBattleStartBLoc() {
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

	OnSSRExeYasenBattleStartBLocExecute();

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

		call pSSRExeJumpCallFromToOnSSRExeYasenBattleStartBLoc

		jmp pSSRExeReturnLblFromOnSSRExeYasenBattleStartBLoc
	}
}
#pragma warning(default: 4733) // ���[�j���O�̗}������������



char cmdOnSSRExeJumpFromYasenBattleStartBLoc[6] = "\xE9";
// ���̖��߂�5�o�C�g�A�Ȍ�̊֐��Ő��܂�閽�߂����v�T�o�C�g�Ȃ̂Łc �Ō�P�g��Ȃ�


// �j�[���j�b�N���������p
void WriteAsmJumperOnSSRExeYasenBattleStartBLoc() {

	// �܂��A�h���X�𐔎��Ƃ��Ĉ���
	int iAddress = (int)OnSSRExeYasenBattleStartBLoc;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeYasenBattleStartBLoc + 5);
	// �T�Ƃ����̂́A0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  �̖��߂ɕK�v�ȃo�C�g���B�v����ɂT�o�C�g�����Ǝ��̃j�[���j�b�N���ߌQ�Ɉړ�����̂��B�����Ă�������̍������W�����v����ۂ̖ړI�i�Ƃ��ė��p�����B
	memcpy(cmdOnSSRExeJumpFromYasenBattleStartBLoc + 1, &SubAddress, 4); // +1 ��E9�̎�����4�o�C�g�����������邩��B

	// �\�z�����j�[���j�b�N���߂����sexe�̃������ɏ���������
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeYasenBattleStartBLoc), cmdOnSSRExeJumpFromYasenBattleStartBLoc, 5, NULL); //5�o�C�g�̂ݏ�������
}

#pragma managed
