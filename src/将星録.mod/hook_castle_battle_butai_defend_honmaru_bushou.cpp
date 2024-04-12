


/*
00416DE3   8BCE             MOV ECX,ESI
00416DE5   E8 F6CDFEFF      CALL Nobunaga.00403BE0
00416DEA   8D0CED 00000000  LEA ECX,DWORD PTR DS:[EBP*8]

*/




#include <windows.h>
#include <string>
#include "data_game_struct.h"
#include "data_bushou_struct.h"
#include "output_debug_stream.h"
#include "game_process.h"

using namespace std;

#pragma unmanaged

/*
ESP 0019FA68

0019FA5C  0A 00 00 00 88 08 54 00 68 02 54 00 00 15 54 00  ....�ET.hT..T.
0019FA6C  84 06 54 00 48 3C 56                             �ET.H<V.

*/

int iCastleBattleButaiHonmaruAttackBushou = -1;
static int ESPOfCastleBattleButaiDefendHonmaruBushou = 0;
void OnSSRExeCastleBattleButaiDefendHonmaruBushouExecute() {

	iCastleBattleButaiHonmaruAttackBushou = -1;

	int nBushouAddress = (int)(BYTE*)(ESPOfCastleBattleButaiDefendHonmaruBushou + 0x14); // 0x14=20
	OutputDebugStream("���_�ւ̒ʏ�U���̕����|�C���^ %x\n", *((int*)(nBushouAddress)));
	int nBushouInfoPtr = *((int*)(nBushouAddress));
	int iBushouID = getBushouIDFromBushouPtr((int*)nBushouInfoPtr);
	if (isValidBushouID(iBushouID)) {
		OutputDebugStream("iCastleBattleButaiHonmaruAttackBushou �̑��\n");
		iCastleBattleButaiHonmaruAttackBushou = iBushouID;
		OutputDebugStream("���_�ւ̒ʏ�U���̕���" + getBushou����FromBushouID(iBushouID) + "\n");
	}

}

/*
00416DE3   8BCE             MOV ECX,ESI
00416DE5   E8 F6CDFEFF      CALL Nobunaga.00403BE0
00416DEA   8D0CED 00000000  LEA ECX,DWORD PTR DS:[EBP*8]
*/

int pSSRExeJumpFromToOnSSRExeCastleBattleButaiDefendHonmaruBushou = 0x416DE5; // �֐��͂��̃A�h���X����AOnSSRExeCastleBattleButaiDefendHonmaruBushou�ւƃW�����v���Ă���B
int pSSRExeJumpCallFromToOnSSRExeCastleBattleButaiDefendHonmaruBushou = 0x403BE0; // ���X������������Call��
int pSSRExeReturnLblFromOnSSRExeCastleBattleButaiDefendHonmaruBushou = 0x416DEA; // �֐����Ō�܂ł����ƁA���̎��sexe���ɒ��ڃW�����v����

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeCastleBattleButaiDefendHonmaruBushou() {
	// �X�^�b�N�ɂ��߂Ă���
	__asm {

		mov ESPOfCastleBattleButaiDefendHonmaruBushou, esp

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeCastleBattleButaiDefendHonmaruBushouExecute();

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

		call pSSRExeJumpCallFromToOnSSRExeCastleBattleButaiDefendHonmaruBushou

		jmp pSSRExeReturnLblFromOnSSRExeCastleBattleButaiDefendHonmaruBushou
	}
}
#pragma warning(default: 4733) // ���[�j���O�̗}������������



char cmdOnSSRExeJumpFromCastleBattleButaiDefendHonmaruBushou[6] = "\xE9";
// ���̖��߂�5�o�C�g�A�Ȍ�̊֐��Ő��܂�閽�߂����v�T�o�C�g�Ȃ̂Łc �Ō�P�g��Ȃ�


// �j�[���j�b�N���������p
void WriteAsmJumperOnSSRExeCastleBattleButaiDefendHonmaruBushou() {

	// �܂��A�h���X�𐔎��Ƃ��Ĉ���
	int iAddress = (int)OnSSRExeCastleBattleButaiDefendHonmaruBushou;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeCastleBattleButaiDefendHonmaruBushou + 5);
	// �T�Ƃ����̂́A0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  �̖��߂ɕK�v�ȃo�C�g���B�v����ɂT�o�C�g�����Ǝ��̃j�[���j�b�N���ߌQ�Ɉړ�����̂��B�����Ă�������̍������W�����v����ۂ̖ړI�i�Ƃ��ė��p�����B
	memcpy(cmdOnSSRExeJumpFromCastleBattleButaiDefendHonmaruBushou + 1, &SubAddress, 4); // +1 ��E9�̎�����4�o�C�g�����������邩��B

	// �\�z�����j�[���j�b�N���߂�TENSHOU.EXE�̃������ɏ���������
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeCastleBattleButaiDefendHonmaruBushou), cmdOnSSRExeJumpFromCastleBattleButaiDefendHonmaruBushou, 5, NULL); //5�o�C�g�̂ݏ�������
}

#pragma managed
