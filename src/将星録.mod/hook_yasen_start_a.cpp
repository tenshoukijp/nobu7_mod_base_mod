/*
�Q�ƃf�[�^ �F Nobunaga:.text -> 00479FA0
���ڽ      �ި�������                                ����
00479FA0   PUSH ESI                                  (CPU����޳�ł̑I���ӏ�)
0047A139   CALL Nobunaga.00479FA0
0048CCFC   CALL Nobunaga.00479FA0
*/

/*
0047A139   E8 62FEFFFF      CALL Nobunaga.00479FA0
0047A13E   B9 80515800      MOV ECX,Nobunaga.00585180

*/


#include <windows.h>
#include <string>
#include "output_debug_stream.h"
#include "game_process.h"


using namespace std;

#pragma unmanaged

BOOL hookYasenBattleStart = 0;
BOOL hookYasenBattleFirstTurn = 0; // ����̖��ɂ����āA�ŏ��̃^�[���ł���B

void OnSSRExeYasenBattleStartALocExecute() {
	hookYasenBattleStart = 1;
	hookYasenBattleFirstTurn = 1;
	OutputDebugStream("�����������J�nA�|�C���g��������\n");
}

/*
0047A139   E8 62FEFFFF      CALL Nobunaga.00479FA0
0047A13E   B9 80515800      MOV ECX,Nobunaga.00585180
*/
int pSSRExeJumpFromToOnSSRExeYasenBattleStartALoc = 0x47A139; // �֐��͂��̃A�h���X����AOnSSRExeYasenBattleStartALoc�ւƃW�����v���Ă���B
int pSSRExeJumpCallFromToOnSSRExeYasenBattleStartALoc = 0x479FA0; // ���X������������Call��
int pSSRExeReturnLblFromOnSSRExeYasenBattleStartALoc = 0x47A13E; // �֐����Ō�܂ł����ƁA����TENSHOU.EXE���ɒ��ڃW�����v����

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeYasenBattleStartALoc() {
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

	OnSSRExeYasenBattleStartALocExecute();

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

		call pSSRExeJumpCallFromToOnSSRExeYasenBattleStartALoc

		jmp pSSRExeReturnLblFromOnSSRExeYasenBattleStartALoc
	}
}
#pragma warning(default: 4733) // ���[�j���O�̗}������������



char cmdOnSSRExeJumpFromYasenBattleStartALoc[6] = "\xE9";
// ���̖��߂�5�o�C�g�A�Ȍ�̊֐��Ő��܂�閽�߂����v�T�o�C�g�Ȃ̂Łc �Ō�P�g��Ȃ�


// �j�[���j�b�N���������p
void WriteAsmJumperOnSSRExeYasenBattleStartALoc() {

	// �܂��A�h���X�𐔎��Ƃ��Ĉ���
	int iAddress = (int)OnSSRExeYasenBattleStartALoc;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeYasenBattleStartALoc + 5);
	// �T�Ƃ����̂́A0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  �̖��߂ɕK�v�ȃo�C�g���B�v����ɂT�o�C�g�����Ǝ��̃j�[���j�b�N���ߌQ�Ɉړ�����̂��B�����Ă�������̍������W�����v����ۂ̖ړI�i�Ƃ��ė��p�����B
	memcpy(cmdOnSSRExeJumpFromYasenBattleStartALoc + 1, &SubAddress, 4); // +1 ��E9�̎�����4�o�C�g�����������邩��B

	// �\�z�����j�[���j�b�N���߂�TENSHOU.EXE�̃������ɏ���������
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeYasenBattleStartALoc), cmdOnSSRExeJumpFromYasenBattleStartALoc, 5, NULL); //5�o�C�g�̂ݏ�������
}

#pragma managed
