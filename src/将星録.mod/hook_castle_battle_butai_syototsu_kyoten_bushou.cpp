/*
00417A01   50               PUSH EAX
00417A02   E8 D9C1FEFF      CALL Nobunaga.00403BE0
00417A07   6A 00            PUSH 0

ESP 0019FA68

0019FA68  B3 01 00 00 EC 06 54 00 04 02 54 00 00 15 54 00  �..�ET.T..T.
0019FA78  7E 09 54 00 48 3C 56 00 68 94 56 00 04 00 54 00  ~.T.H<V.h�V..T.
0019FA88  F4 01 00 00 84 03 00 00 04 02 54 00 04 01 00 00  �E..�E..T...

*/




#include <windows.h>
#include <string>
#include "data_game_struct.h"
#include "data_bushou_struct.h"
#include "output_debug_stream.h"
#include "game_screen.h"
#include "game_process.h"

using namespace std;

#pragma unmanaged

/*
ESP 0019FA68

0019FA68  B3 01 00 00 EC 06 54 00 04 02 54 00 00 15 54 00  �..�ET.T..T.
0019FA78  7E 09 54 00 48 3C 56 00 68 94 56 00 04 00 54 00  ~.T.H<V.h�V..T.
0019FA88  F4 01 00 00 84 03 00 00 04 02 54 00 04 01 00 00  �E..�E..T...
*/

int iCastleBattleButaiKyotenAttackBushou = -1;
static int ESPOfCastleBattleButaiSyototsuKyotenBushou = 0;
void OnSSRExeCastleBattleButaiSyototsuKyotenBushouExecute() {

	iCastleBattleButaiKyotenAttackBushou = -1;

	int nBushouAddress = (int)(BYTE *)(ESPOfCastleBattleButaiSyototsuKyotenBushou + 0x14); // 0x14=20
	OutputDebugStream("���_�ւ̒ʏ�U���̕����|�C���^ %x\n", *((int *)(nBushouAddress)));
	int nBushouInfoPtr = *((int *)(nBushouAddress));
	int iBushouID = getBushouIDFromBushouPtr((int *)nBushouInfoPtr);
	if (isValidBushouID(iBushouID)) {
		OutputDebugStream("iCastleBattleButaiKyotenAttackBushou �̑��\n");
		iCastleBattleButaiKyotenAttackBushou = iBushouID;
		OutputDebugStream("���_�ւ̒ʏ�U���̕���" + getBushou����FromBushouID(iBushouID) + "\n");
	}

}

/*
00417A01   50               PUSH EAX
00417A02   E8 D9C1FEFF      CALL Nobunaga.00403BE0
00417A07   6A 00            PUSH 0
*/

int pSSRExeJumpFromToOnSSRExeCastleBattleButaiSyototsuKyotenBushou = 0x417A02; // �֐��͂��̃A�h���X����AOnSSRExeCastleBattleButaiSyototsuKyotenBushou�ւƃW�����v���Ă���B
int pSSRExeJumpCallFromToOnSSRExeCastleBattleButaiSyototsuKyotenBushou = 0x403BE0; // ���X������������Call��
int pSSRExeReturnLblFromOnSSRExeCastleBattleButaiSyototsuKyotenBushou = 0x417A07; // �֐����Ō�܂ł����ƁA����TENSHOU.EXE���ɒ��ڃW�����v����

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeCastleBattleButaiSyototsuKyotenBushou() {
	// �X�^�b�N�ɂ��߂Ă���
	__asm {

		mov ESPOfCastleBattleButaiSyototsuKyotenBushou, esp

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeCastleBattleButaiSyototsuKyotenBushouExecute();

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

		call pSSRExeJumpCallFromToOnSSRExeCastleBattleButaiSyototsuKyotenBushou

		jmp pSSRExeReturnLblFromOnSSRExeCastleBattleButaiSyototsuKyotenBushou
	}
}
#pragma warning(default: 4733) // ���[�j���O�̗}������������



char cmdOnSSRExeJumpFromCastleBattleButaiSyototsuKyotenBushou[6] = "\xE9";
// ���̖��߂�5�o�C�g�A�Ȍ�̊֐��Ő��܂�閽�߂����v�T�o�C�g�Ȃ̂Łc �Ō�P�g��Ȃ�


// �j�[���j�b�N���������p
void WriteAsmJumperOnSSRExeCastleBattleButaiSyototsuKyotenBushou() {

	// �܂��A�h���X�𐔎��Ƃ��Ĉ���
	int iAddress = (int)OnSSRExeCastleBattleButaiSyototsuKyotenBushou;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeCastleBattleButaiSyototsuKyotenBushou + 5);
	// �T�Ƃ����̂́A0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  �̖��߂ɕK�v�ȃo�C�g���B�v����ɂT�o�C�g�����Ǝ��̃j�[���j�b�N���ߌQ�Ɉړ�����̂��B�����Ă�������̍������W�����v����ۂ̖ړI�i�Ƃ��ė��p�����B
	memcpy(cmdOnSSRExeJumpFromCastleBattleButaiSyototsuKyotenBushou + 1, &SubAddress, 4); // +1 ��E9�̎�����4�o�C�g�����������邩��B

	// �\�z�����j�[���j�b�N���߂�TENSHOU.EXE�̃������ɏ���������
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeCastleBattleButaiSyototsuKyotenBushou), cmdOnSSRExeJumpFromCastleBattleButaiSyototsuKyotenBushou, 5, NULL); //5�o�C�g�̂ݏ�������
}

#pragma managed
