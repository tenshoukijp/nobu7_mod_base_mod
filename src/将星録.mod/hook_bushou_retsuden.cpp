// ���̃t�@�C���͒������s�B���ɗ����Ȃ��B�R���p�C���Ώۂ���O��Ă���

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
������`�����ۂɎ��s�����ꏊ
0042EBA0   A1 2C495200      MOV EAX,DWORD PTR DS:[52492C]
0042EBA5   56               PUSH ESI
0042EBA6   6A 10            PUSH 10
0042EBA8   68 64215200      PUSH Nobunaga.00522164                   ; ASCII "������`"
0042EBAD   68 11110000      PUSH 1111
0042EBB2   6A 00            PUSH 0
0042EBB4   68 A8000000      PUSH 0A8
0042EBB9   68 50010000      PUSH 150
0042EBBE   50               PUSH EAX
0042EBBF   6A 00            PUSH 0
0042EBC1   8BF1             MOV ESI,ECX
0042EBC3   E8 38070700      CALL Nobunaga.0049F300
0042EBC8   8B46 50          MOV EAX,DWORD PTR DS:[ESI+50]
0042EBCB   C740 08 90000000 MOV DWORD PTR DS:[EAX+8],90
0042EBD2   C740 0C 88000000 MOV DWORD PTR DS:[EAX+C],88
0042EBD9   8B4E 50          MOV ECX,DWORD PTR DS:[ESI+50]
0042EBDC   C741 2C 97000000 MOV DWORD PTR DS:[ECX+2C],97
0042EBE3   8B15 00925300    MOV EDX,DWORD PTR DS:[539200]            ; Nobunaga.005694B0
0042EBE9   8996 80000000    MOV DWORD PTR DS:[ESI+80],EDX
0042EBEF   5E               POP ESI
0042EBF0   C3               RETN
*/



void OnSSRExeBushouRetsudenExecute() {
	OutputDebugStream("��`�����恚\n");
}


/*
������`�����s����鎞

0042EBC1   8BF1             MOV ESI,ECX
0042EBC3   E8 38070700      CALL Nobunaga.0049F300
0042EBC8   8B46 50          MOV EAX,DWORD PTR DS:[ESI+50]
*/
/*



*/
int pSSRExeJumpFromToOnSSRExeBushouRetsuden = 0x42EBC3; // �֐��͂��̃A�h���X����AOnSSRExeBushouRetsuden�ւƃW�����v���Ă���B
int pSSRExeJumpCallFromToOnSSRExeBushouRetsuden = 0x0049F300; // ���X������������Call��
int pSSRExeReturnLblFromOnSSRExeBushouRetsuden = 0x42EBC8; // �֐����Ō�܂ł����ƁA����TENSHOU.EXE���ɒ��ڃW�����v����

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeBushouRetsuden() {
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

	OnSSRExeBushouRetsudenExecute();

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

		call pSSRExeJumpCallFromToOnSSRExeBushouRetsuden // ���̏���

		jmp pSSRExeReturnLblFromOnSSRExeBushouRetsuden
	}
}
#pragma warning(default: 4733) // ���[�j���O�̗}������������



char cmdOnSSRExeJumpFromBushouRetsuden[6] = "\xE9";
// ���̖��߂�5�o�C�g�A�Ȍ�̊֐��Ő��܂�閽�߂����v�T�o�C�g�Ȃ̂Łc �Ō�P�g��Ȃ�


// �j�[���j�b�N���������p
void WriteAsmJumperOnSSRExeBushouRetsuden() {

	// �܂��A�h���X�𐔎��Ƃ��Ĉ���
	int iAddress = (int)OnSSRExeBushouRetsuden;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeBushouRetsuden + 5);
	// �T�Ƃ����̂́A0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  �̖��߂ɕK�v�ȃo�C�g���B�v����ɂT�o�C�g�����Ǝ��̃j�[���j�b�N���ߌQ�Ɉړ�����̂��B�����Ă�������̍������W�����v����ۂ̖ړI�i�Ƃ��ė��p�����B
	memcpy(cmdOnSSRExeJumpFromBushouRetsuden + 1, &SubAddress, 4); // +1 ��E9�̎�����4�o�C�g�����������邩��B

	// �\�z�����j�[���j�b�N���߂�TENSHOU.EXE�̃������ɏ���������
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeBushouRetsuden), cmdOnSSRExeJumpFromBushouRetsuden, 5, NULL); //5�o�C�g�̂ݏ�������
}

#pragma managed
