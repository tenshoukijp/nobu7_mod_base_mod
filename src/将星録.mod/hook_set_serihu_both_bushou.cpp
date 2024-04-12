/*
�b�҂Ƃ��Ă̕�����񂪍X�V�����^�C�~���O
1�l�ڂ� 0x5D988C�A
2�l�ڂ� 0x5D9890�A
*/

/*
0051DE30   A1 00925300      MOV EAX,DWORD PTR DS:[539200]
0051DE35   56               PUSH ESI
0051DE36   57               PUSH EDI
0051DE37   A3 8C985D00      MOV DWORD PTR DS:[5D988C],EAX
0051DE3C   BE 90985D00      MOV ESI,Nobunaga.005D9890                ; ASCII "��V"
0051DE41   BF 08000000      MOV EDI,8
0051DE46   8BCE             MOV ECX,ESI
0051DE48   E8 5325F2FF      CALL Nobunaga.004403A0
0051DE4D   83C6 04          ADD ESI,4
0051DE50   83EF 01          SUB EDI,1
0051DE53  ^79 F1            JNS SHORT Nobunaga.0051DE46
0051DE55   5F               POP EDI
0051DE56   5E               POP ESI
0051DE57   C3               RETN
*/




#include <windows.h>
#include <string>
#include "data_bushou_struct.h"
#include "output_debug_stream.h"
#include "game_screen.h"


using namespace std;

#pragma unmanaged

int iBushouID_1st_OfSetSerihuBothBushou = -1;
int iBushouID_2nd_OfSetSerihuBothBushou = -1;
int iBushouID_3rd_OfSetSerihuBothBushou = -1;
int iBushouID_4th_OfSetSerihuBothBushou = -1;
void OnSSRExeSetSerihuBothBushouExecute() {
	iBushouID_1st_OfSetSerihuBothBushou = -1;
	iBushouID_2nd_OfSetSerihuBothBushou = -1;
	iBushouID_3rd_OfSetSerihuBothBushou = -1;
	iBushouID_4th_OfSetSerihuBothBushou = -1;

	int iBushouPtr_1st = *((int*)0x5D988C);
	int iBushouID_1st = getBushouIDFromBushouPtr((int *)iBushouPtr_1st);
	if (isValidBushouID(iBushouID_1st)) {
		iBushouID_1st_OfSetSerihuBothBushou = iBushouID_1st;
		OutputDebugStream("1�l�ڂ̘b�҂�" + getBushou����FromBushouID(iBushouID_1st) + "�ł��B\n");
	}

	int iBushouPtr_2nd = *((int*)0x5D9890);
	int iBushouID_2nd = getBushouIDFromBushouPtr((int *)iBushouPtr_2nd);
	if (isValidBushouID(iBushouID_2nd)) {
		iBushouID_2nd_OfSetSerihuBothBushou = iBushouID_2nd;
		OutputDebugStream("2�l�ڂ̘b�҂�" + getBushou����FromBushouID(iBushouID_2nd) + "�ł��B\n");
	}

	int iBushouPtr_3rd = *((int*)0x5D9894);
	int iBushouID_3rd = getBushouIDFromBushouPtr((int *)iBushouPtr_3rd);
	if (isValidBushouID(iBushouID_3rd)) {
		iBushouID_3rd_OfSetSerihuBothBushou = iBushouID_3rd;
		OutputDebugStream("3�l�ڂ̘b�҂�" + getBushou����FromBushouID(iBushouID_3rd) + "�ł��B\n");
	}

	int iBushouPtr_4th = *((int*)0x5D9898);
	int iBushouID_4th = getBushouIDFromBushouPtr((int *)iBushouPtr_4th);
	if (isValidBushouID(iBushouID_4th)) {
		iBushouID_4th_OfSetSerihuBothBushou = iBushouID_4th;
		OutputDebugStream("4�l�ڂ̘b�҂�" + getBushou����FromBushouID(iBushouID_4th) + "�ł��B\n");
	}
}

/*
0051DE30   A1 00925300      MOV EAX,DWORD PTR DS:[539200]
0051DE35   56               PUSH ESI
0051DE36   57               PUSH EDI
0051DE37   A3 8C985D00      MOV DWORD PTR DS:[5D988C],EAX
0051DE3C   BE 90985D00      MOV ESI,Nobunaga.005D9890                ; ASCII "��V"
0051DE41   BF 08000000      MOV EDI,8
0051DE46   8BCE             MOV ECX,ESI
0051DE48   E8 5325F2FF      CALL Nobunaga.004403A0
0051DE4D   83C6 04          ADD ESI,4
0051DE50   83EF 01          SUB EDI,1
0051DE53  ^79 F1            JNS SHORT Nobunaga.0051DE46
0051DE55   5F               POP EDI
0051DE56   5E               POP ESI
0051DE57   C3               RETN
*/


int pSSRExeJumpFromToOnSSRExeSetSerihuBothBushou = 0x51DE46; // �֐��͂��̃A�h���X����AOnSSRExeSetSerihuBothBushou�ւƃW�����v���Ă���B
int pSSRExeJumpCallFromToOnSSRExeSetSerihuBothBushou = 0x4403A0; // ���X������������Call��
int pSSRExeReturnLblFromOnSSRExeSetSerihuBothBushou = 0x51DE55; // �֐����Ō�܂ł����ƁA���̎��sexe���ɒ��ڃW�����v����

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeSetSerihuBothBushou() {
	// �X�^�b�N�ɂ��߂Ă���
	__asm {

/*
0051DE46   8BCE             MOV ECX,ESI
0051DE48   E8 5325F2FF      CALL Nobunaga.004403A0
0051DE4D   83C6 04          ADD ESI,4
0051DE50   83EF 01          SUB EDI,1
0051DE53  ^79 F1            JNS SHORT Nobunaga.0051DE46
*/
		other_bushou_loop:

			mov ecx, esi
			call pSSRExeJumpCallFromToOnSSRExeSetSerihuBothBushou
			add esi, 4
			sub edi, 1
			jns other_bushou_loop

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeSetSerihuBothBushouExecute();

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

		jmp pSSRExeReturnLblFromOnSSRExeSetSerihuBothBushou
	}
}
#pragma warning(default: 4733) // ���[�j���O�̗}������������



char cmdOnSSRExeJumpFromSetSerihuBothBushou[8] = "\xE9\x90\x90\x90\x90\x90\x90";
// ���̖��߂�5�o�C�g�A�Ȍ�̊֐��Ő��܂�閽�߂����v�T�o�C�g�Ȃ̂Łc �Ō�P�g��Ȃ�


// �j�[���j�b�N���������p
void WriteAsmJumperOnSSRExeSetSerihuBothBushou() {

	// �܂��A�h���X�𐔎��Ƃ��Ĉ���
	int iAddress = (int)OnSSRExeSetSerihuBothBushou;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeSetSerihuBothBushou + 5);
	// �T�Ƃ����̂́A0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  �̖��߂ɕK�v�ȃo�C�g���B�v����ɂT�o�C�g�����Ǝ��̃j�[���j�b�N���ߌQ�Ɉړ�����̂��B�����Ă�������̍������W�����v����ۂ̖ړI�i�Ƃ��ė��p�����B
	memcpy(cmdOnSSRExeJumpFromSetSerihuBothBushou + 1, &SubAddress, 4); // +1 ��E9�̎�����4�o�C�g�����������邩��B

	// �\�z�����j�[���j�b�N���߂����sexe�̃������ɏ���������
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeSetSerihuBothBushou), cmdOnSSRExeJumpFromSetSerihuBothBushou, 7, NULL); //7�o�C�g�̂ݏ�������
/*
�ȉ��̕��𖄂߂�̂łV�o�C�g��������
0051DE46   8BCE             MOV ECX,ESI
0051DE48   E8 5325F2FF      CALL Nobunaga.004403A0
*/

}

#pragma managed
