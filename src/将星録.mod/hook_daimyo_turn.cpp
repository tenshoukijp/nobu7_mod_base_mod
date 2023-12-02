

// ���̃t�@�C���͔����ɊO��Ă���H �ł��d�v�ȏ�񂪂���悤�ɂ��v����
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


using namespace std;

#pragma unmanaged

/*
�喼�^�[���̏�񂪂��邩������Ȃ��ꏊ
00569280  28 00 00 00 78 00 00 00 14 00 00 00 64 00 00 00  (...x......d...
00569290  00 00 00 00 00 00 00 00 A0 00 00 00 A0 00 00 00  ........�...�...
005692A0  [26 AB 56] 00 16 00 00 00 40 00 00 00 01 00 00 00  &�V....@......
005692B0  00 00 00 00 [26 AB 56] 00 58 27 CE 07 01 00 00 00  ....&�V.X'�...
005692C0  16 00 00 00 E8 6F D4 07 40 2E 00 00 7A A6 00 00  ...�o�@...z�..
005692D0  B6 3F 00 00 00 00 00 00 00 00 00 00 00 00 00 00  �?..............
005692E0  8C 5B 00 00 DA 1D 00 00 00 00 00 00 00 00 00 00  �[..�..........

0057EA74  78 A1 CE 07 01 00 00 00 [26 AB 56] 00 B8 8E 53 00  x��...&�V.��S. �A�h���X0x57EA7C = ������[ ] ���喼�^�[���̑喼�A�h���X�ւ̒��ڂ̃|�C���^ [B8 8E 53 00] ���ƁA�N���^�[�����ĂȂ��B
0057EA84  [26 AB 56] 00 B8 8E 53 00 B8 8E 53 00 B8 8E 53 00  &�V.��S.��S.��S.
0057EA94  B8 8E 53 00 B8 8E 53 00 B8 8E 53 00 B8 8E 53 00  ��S.��S.��S.��S.
0057EAA4  05 00 00 00 05 00 00 00 00 00 00 00 FF FF 00 00  ..........��..
*/#pragma once

/*
����0x57EA7C�ւƑ�����Ă���ӏ��͂����P�B
004C4F7A   8B15 F8915300    MOV EDX,DWORD PTR DS:[5391F8]            ; Nobunaga.00538EB8
004C4F80   8915 7CEA5700    MOV DWORD PTR DS:[57EA7C],EDX
004C4F86   837C24 1C 00     CMP DWORD PTR SS:[ESP+1C],0
004C4F8B   0F85 AB000000    JNZ Nobunaga.004C503C
004C4F91   33FF             XOR EDI,EDI
004C4F93   8D6B 08          LEA EBP,DWORD PTR DS:[EBX+8]
*/

/*
���̏�L���Ăяo���Ă���֐��͂������P��
0045F58B   B9 F0BF5E00      MOV ECX,Nobunaga.005EBFF0
0045F590   E8 5B590600      CALL Nobunaga.004C4EF0
0045F595   8B4C24 14        MOV ECX,DWORD PTR SS:[ESP+14]
0045F599   8D8424 44450000  LEA EAX,DWORD PTR SS:[ESP+4544]
0045F5A0   50               PUSH EAX
*/



void OnSSRExeDaimyoTurnExecute() {
	OutputDebugStream("�喼�^�[��������O��\n");
}

/*
����0x57EA7C�ւƑ�����Ă���ӏ��͂����P�B
004C4F7A   8B15 F8915300    MOV EDX,DWORD PTR DS:[5391F8]            ; Nobunaga.00538EB8
004C4F80   8915 7CEA5700    MOV DWORD PTR DS:[57EA7C],EDX <--- �������W�����v�ւƏ���������
004C4F86   837C24 1C 00     CMP DWORD PTR SS:[ESP+1C],0
004C4F8B   0F85 AB000000    JNZ Nobunaga.004C503C
004C4F91   33FF             XOR EDI,EDI
004C4F93   8D6B 08          LEA EBP,DWORD PTR DS:[EBX+8]
*/



int pSSRExeJumpFromToOnSSRExeDaimyoTurn = 0x4C4F80; // �֐��͂��̃A�h���X����AOnSSRExeDaimyoTurn�ւƃW�����v���Ă���B
// int pSSRExeJumpCallFromToOnSSRExeDaimyoTurn = 0x04C4EF0; // ���X������������Call��
int pSSRExeReturnLblFromOnSSRExeDaimyoTurn = 0x4C4F86; // �֐����Ō�܂ł����ƁA����TENSHOU.EXE���ɒ��ڃW�����v����

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeDaimyoTurn() {
	// �X�^�b�N�ɂ��߂Ă���
	__asm {

		MOV DWORD PTR DS : [0x57EA7C] , EDX

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeDaimyoTurnExecute();

	__asm {
		pop edi
		pop esi
		pop ebp
		pop esp
		pop edx
		pop ecx
		pop ebx
		pop eax

		jmp pSSRExeReturnLblFromOnSSRExeDaimyoTurn
	}
}
#pragma warning(default: 4733) // ���[�j���O�̗}������������



char cmdOnSSRExeJumpFromDaimyoTurn[6] = "\xE9";
// ���̖��߂�5�o�C�g�A�Ȍ�̊֐��Ő��܂�閽�߂����v�T�o�C�g�Ȃ̂Łc �Ō�P�g��Ȃ�


// �j�[���j�b�N���������p
void WriteAsmJumperOnSSRExeDaimyoTurn() {

	// �܂��A�h���X�𐔎��Ƃ��Ĉ���
	int iAddress = (int)OnSSRExeDaimyoTurn;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeDaimyoTurn + 5);
	// �T�Ƃ����̂́A0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  �̖��߂ɕK�v�ȃo�C�g���B�v����ɂT�o�C�g�����Ǝ��̃j�[���j�b�N���ߌQ�Ɉړ�����̂��B�����Ă�������̍������W�����v����ۂ̖ړI�i�Ƃ��ė��p�����B
	memcpy(cmdOnSSRExeJumpFromDaimyoTurn + 1, &SubAddress, 4); // +1 ��E9�̎�����4�o�C�g�����������邩��B

	// �\�z�����j�[���j�b�N���߂�TENSHOU.EXE�̃������ɏ���������
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeDaimyoTurn), cmdOnSSRExeJumpFromDaimyoTurn, 5, NULL); //5�o�C�g�̂ݏ�������
}

#pragma managed
