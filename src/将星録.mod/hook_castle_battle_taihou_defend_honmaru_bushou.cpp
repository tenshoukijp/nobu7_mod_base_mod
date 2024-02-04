/*
���̃^�C�~���O�ōU�����̕����|�C���^���E���Ă����B

00415B11   8D4424 14        LEA EAX,DWORD PTR SS:[ESP+14]
00415B15   50               PUSH EAX
00415B16   E8 E5DFFEFF      CALL Nobunaga.00403B00
00415B1B   8B4C24 18        MOV ECX,DWORD PTR SS:[ESP+18]
00415B1F   83EC 08          SUB ESP,8



�{�ۂő�C���󂯂��ۂ̖h�䑤�̕�����EDX�ɓ����Ă��邩�H

00415B8E   B9 A0815300      MOV ECX,Nobunaga.005381A0
00415B93   E8 B83A0000      CALL Nobunaga.00419650
00415B98   8B5424 14        MOV EDX,DWORD PTR SS:[ESP+14]
00415B9C   3B15 00925300    CMP EDX,DWORD PTR DS:[539200]            ; Nobunaga.005694B0
00415BA2   74 50            JE SHORT Nobunaga.00415BF4
00415BA4   8B4C24 10        MOV ECX,DWORD PTR SS:[ESP+10]

*/



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
#include "castle_battle_attack_heisuu_sum.h"

using namespace std;

#pragma unmanaged


// ������OnSSRExeCastleBattleTaihouDefendHonmaruDamageExecute�ōU�������̔ԍ����E�����߂����̂���

int iCastleBattleTaihouHonmaruAttackBushou = -1;
void OnSSRExeCastleBattleTaihouDefendHonmaruBushouExecute() {
	int nBushouAddress = (int)(���b�Z�[�W�������.p��̕���);
	iCastleBattleTaihouHonmaruAttackBushou = getBushouIDFromBushouPtr((int*)nBushouAddress);
	OutputDebugStream("��������C�̍U�����̕���" + getBushou����FromBushouID(iCastleBattleTaihouHonmaruAttackBushou) + "\n");
}

/*
00415B11   8D4424 14        LEA EAX,DWORD PTR SS:[ESP+14]
00415B15   50               PUSH EAX
00415B16   E8 E5DFFEFF      CALL Nobunaga.00403B00
00415B1B   8B4C24 18        MOV ECX,DWORD PTR SS:[ESP+18]
00415B1F   83EC 08          SUB ESP,8
*/


int pSSRExeJumpFromToOnSSRExeCastleBattleTaihouDefendHonmaruBushou = 0x415B16; // �֐��͂��̃A�h���X����AOnSSRExeCastleBattleTaihouDefendHonmaruBushou�ւƃW�����v���Ă���B
int pSSRExeJumpCallFromToOnSSRExeCastleBattleTaihouDefendHonmaruBushou = 0x403B00; // ���X������������Call��
int pSSRExeReturnLblFromOnSSRExeCastleBattleTaihouDefendHonmaruBushou = 0x415B1B; // �֐����Ō�܂ł����ƁA����TENSHOU.EXE���ɒ��ڃW�����v����

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeCastleBattleTaihouDefendHonmaruBushou() {
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

	OnSSRExeCastleBattleTaihouDefendHonmaruBushouExecute();

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

		call pSSRExeJumpCallFromToOnSSRExeCastleBattleTaihouDefendHonmaruBushou

		jmp pSSRExeReturnLblFromOnSSRExeCastleBattleTaihouDefendHonmaruBushou
	}
}
#pragma warning(default: 4733) // ���[�j���O�̗}������������



char cmdOnSSRExeJumpFromCastleBattleTaihouDefendHonmaruBushou[6] = "\xE9";
// ���̖��߂�5�o�C�g�A�Ȍ�̊֐��Ő��܂�閽�߂����v�T�o�C�g�Ȃ̂Łc �Ō�P�g��Ȃ�


// �j�[���j�b�N���������p
void WriteAsmJumperOnSSRExeCastleBattleTaihouDefendHonmaruBushou() {

	// �܂��A�h���X�𐔎��Ƃ��Ĉ���
	int iAddress = (int)OnSSRExeCastleBattleTaihouDefendHonmaruBushou;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeCastleBattleTaihouDefendHonmaruBushou + 5);
	// �T�Ƃ����̂́A0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  �̖��߂ɕK�v�ȃo�C�g���B�v����ɂT�o�C�g�����Ǝ��̃j�[���j�b�N���ߌQ�Ɉړ�����̂��B�����Ă�������̍������W�����v����ۂ̖ړI�i�Ƃ��ė��p�����B
	memcpy(cmdOnSSRExeJumpFromCastleBattleTaihouDefendHonmaruBushou + 1, &SubAddress, 4); // +1 ��E9�̎�����4�o�C�g�����������邩��B

	// �\�z�����j�[���j�b�N���߂�TENSHOU.EXE�̃������ɏ���������
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeCastleBattleTaihouDefendHonmaruBushou), cmdOnSSRExeJumpFromCastleBattleTaihouDefendHonmaruBushou, 5, NULL); //5�o�C�g�̂ݏ�������
}

#pragma managed
