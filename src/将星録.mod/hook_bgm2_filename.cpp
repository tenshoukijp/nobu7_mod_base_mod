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

// ����I��BGM�͂���(��1)
0041995C   57               PUSH EDI
0041995D   8906             MOV DWORD PTR DS:[ESI],EAX
0041995F   894E 04          MOV DWORD PTR DS:[ESI+4],ECX
00419962   8956 08          MOV DWORD PTR DS:[ESI+8],EDX
00419965   C746 0C 00000000 MOV DWORD PTR DS:[ESI+C],0
0041996C   C746 10 00000000 MOV DWORD PTR DS:[ESI+10],0
00419973   C746 14 01000000 MOV DWORD PTR DS:[ESI+14],1
0041997A   C746 28 FFFFFFFF MOV DWORD PTR DS:[ESI+28],-1
00419981   BF 02000000      MOV EDI,2
00419986   8D47 FE          LEA EAX,DWORD PTR DS:[EDI-2]
00419989   83F8 12          CMP EAX,12                               0x12 = 18 �Ƃ�������͓�BBGM��BGM\BGM19.wav �Ȃǂ����ʂɂ��邵...
0041998C   77 12            JA SHORT Nobunaga.004199A0
0041998E   57               PUSH EDI
0041998F   8D4C24 10        LEA ECX,DWORD PTR SS:[ESP+10]
00419993   68 4C0F5200      PUSH Nobunaga.00520F4C                   ; ASCII "BGM\%02d.wav"
00419998   51               PUSH ECX
00419999   E8 D98D0E00      CALL Nobunaga.00502777
*/

/*
����I��BGM�Đ��֐��Ăяo���t��
0045CD88   57               PUSH EDI
0045CD89   57               PUSH EDI
0045CD8A   57               PUSH EDI
0045CD8B   B9 A0815300      MOV ECX,Nobunaga.005381A0
0045CD90   E8 9BCBFBFF      CALL Nobunaga.00419930
0045CD95   85C0             TEST EAX,EAX
*/




static int nPlayBGM2EDI = -1;
void OnSSRExePlayBGM2Execute() {
	OutputDebugStream("BGM2�̍Đ��֐����Ă΂ꂽ��!!");
	OutputDebugStream("EDI��%d\n", nPlayBGM2EDI);
}


/*
����I��BGM�Đ��֐��Ăяo���t��
0045CD88   57               PUSH EDI
0045CD89   57               PUSH EDI
0045CD8A   57               PUSH EDI
0045CD8B   B9 A0815300      MOV ECX,Nobunaga.005381A0
0045CD90   E8 9BCBFBFF      CALL Nobunaga.00419930
0045CD95   85C0             TEST EAX,EAX
*/

int pSSRExeJumpFromToOnSSRExePlayBGM2 = 0x45CD90; // �֐��͂��̃A�h���X����AOnSSRExePlayBGM2�ւƃW�����v���Ă���B
int pSSRExeJumpCallFromToOnSSRExePlayBGM2 = 0x419930; // ���X������������Call��
int pSSRExeReturnLblFromOnSSRExePlayBGM2 = 0x45CD95; // �֐����Ō�܂ł����ƁA����TENSHOU.EXE���ɒ��ڃW�����v����

#pragma warning(disable:4733)


__declspec(naked) void WINAPI OnSSRExePlayBGM2() {
	// �X�^�b�N�ɂ��߂Ă���
	__asm {
		mov nPlayBGM2EDI, edi
		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExePlayBGM2Execute();

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

		call pSSRExeJumpCallFromToOnSSRExePlayBGM2 // ���̏���

		jmp pSSRExeReturnLblFromOnSSRExePlayBGM2
	}
}
#pragma warning(default: 4733) // ���[�j���O�̗}������������



char cmdOnSSRExeJumpFromPlayBGM2[6] = "\xE9";
// ���̖��߂�5�o�C�g�A�Ȍ�̊֐��Ő��܂�閽�߂����v�T�o�C�g�Ȃ̂Łc �Ō�P�g��Ȃ�

// �j�[���j�b�N���������p
void WriteAsmJumperOnSSRExePlayBGM2() {

	// �܂��A�h���X�𐔎��Ƃ��Ĉ���
	int iAddress = (int)OnSSRExePlayBGM2;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExePlayBGM2 + 5);
	// �T�Ƃ����̂́A0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  �̖��߂ɕK�v�ȃo�C�g���B�v����ɂT�o�C�g�����Ǝ��̃j�[���j�b�N���ߌQ�Ɉړ�����̂��B�����Ă�������̍������W�����v����ۂ̖ړI�i�Ƃ��ė��p�����B
	memcpy(cmdOnSSRExeJumpFromPlayBGM2 + 1, &SubAddress, 4); // +1 ��E9�̎�����4�o�C�g�����������邩��B

	// �\�z�����j�[���j�b�N���߂�TENSHOU.EXE�̃������ɏ���������
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExePlayBGM2), cmdOnSSRExeJumpFromPlayBGM2, 5, NULL); //5�o�C�g�̂ݏ�������
}

#pragma managed
