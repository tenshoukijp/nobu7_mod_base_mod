/*
0041317B   6A 19            PUSH 19
0041317D   B9 A0815300      MOV ECX,Nobunaga.005381A0
00413182   E8 C9640000      CALL Nobunaga.00419650
00413187   8B5424 14        MOV EDX,DWORD PTR SS:[ESP+14]
*/



#include <windows.h>
#include <string>
#include "data_game_struct.h"
#include "data_bushou_struct.h"
#include "output_debug_stream.h"
#include "game_process.h"

using namespace std;

#pragma unmanaged


// ������OnSSRExeCastleBattleTaihouDefendKyotenDamageExecute�ōU�������̔ԍ����E�����߂����̂���

int iCastleBattleTaihouAttackBushou = -1;
void OnSSRExeCastleBattleTaihouDefendKyotenBushouExecute() {
	iCastleBattleTaihouAttackBushou = get1stBushouIDFromMessageBushou();
	OutputDebugStream("��������C�̍U�����̕���" + getBushou����FromBushouID(iCastleBattleTaihouAttackBushou) + "\n");
}

/*
0041317B   6A 19            PUSH 19
0041317D   B9 A0815300      MOV ECX,Nobunaga.005381A0
00413182   E8 C9640000      CALL Nobunaga.00419650
00413187   8B5424 14        MOV EDX,DWORD PTR SS:[ESP+14]
*/


int pSSRExeJumpFromToOnSSRExeCastleBattleTaihouDefendKyotenBushou = 0x413182; // �֐��͂��̃A�h���X����AOnSSRExeCastleBattleTaihouDefendKyotenBushou�ւƃW�����v���Ă���B
int pSSRExeJumpCallFromToOnSSRExeCastleBattleTaihouDefendKyotenBushou = 0x419650; // ���X������������Call��
int pSSRExeReturnLblFromOnSSRExeCastleBattleTaihouDefendKyotenBushou = 0x413187; // �֐����Ō�܂ł����ƁA����TENSHOU.EXE���ɒ��ڃW�����v����

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeCastleBattleTaihouDefendKyotenBushou() {
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

	OnSSRExeCastleBattleTaihouDefendKyotenBushouExecute();

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

		call pSSRExeJumpCallFromToOnSSRExeCastleBattleTaihouDefendKyotenBushou

		jmp pSSRExeReturnLblFromOnSSRExeCastleBattleTaihouDefendKyotenBushou
	}
}
#pragma warning(default: 4733) // ���[�j���O�̗}������������



char cmdOnSSRExeJumpFromCastleBattleTaihouDefendKyotenBushou[6] = "\xE9";
// ���̖��߂�5�o�C�g�A�Ȍ�̊֐��Ő��܂�閽�߂����v�T�o�C�g�Ȃ̂Łc �Ō�P�g��Ȃ�


// �j�[���j�b�N���������p
void WriteAsmJumperOnSSRExeCastleBattleTaihouDefendKyotenBushou() {

	// �܂��A�h���X�𐔎��Ƃ��Ĉ���
	int iAddress = (int)OnSSRExeCastleBattleTaihouDefendKyotenBushou;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeCastleBattleTaihouDefendKyotenBushou + 5);
	// �T�Ƃ����̂́A0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  �̖��߂ɕK�v�ȃo�C�g���B�v����ɂT�o�C�g�����Ǝ��̃j�[���j�b�N���ߌQ�Ɉړ�����̂��B�����Ă�������̍������W�����v����ۂ̖ړI�i�Ƃ��ė��p�����B
	memcpy(cmdOnSSRExeJumpFromCastleBattleTaihouDefendKyotenBushou + 1, &SubAddress, 4); // +1 ��E9�̎�����4�o�C�g�����������邩��B

	// �\�z�����j�[���j�b�N���߂�TENSHOU.EXE�̃������ɏ���������
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeCastleBattleTaihouDefendKyotenBushou), cmdOnSSRExeJumpFromCastleBattleTaihouDefendKyotenBushou, 5, NULL); //5�o�C�g�̂ݏ�������
}

#pragma managed
