/*
�Q�ƃf�[�^ �F Nobunaga:.text -> 00496070
���ڽ      �ި�������                                ����
00496070   PUSH ECX                                  (CPU����޳�ł̑I���ӏ�)
00496238   CALL Nobunaga.00496070
004962F8   CALL Nobunaga.00496070
*/

/*
00496233   A3 A0985D00      MOV DWORD PTR DS:[5D98A0],EAX
00496238   E8 33FEFFFF      CALL Nobunaga.00496070
0049623D   83C4 08          ADD ESP,8
00496240   5E               POP ESI
00496241   59               POP ECX
*/



#include <windows.h>
#include <string>
#include <vector>
#include "data_bushou_struct.h"
#include "output_debug_stream.h"
#include "game_process.h"


using namespace std;

#pragma unmanaged

vector<int> list�b��BushouID = { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF };

void OnSSRExeSetSerifuAllButhouLocAExecute() {
	OutputDebugStream("�b�҂̍X�V�ꏊ A\n");

	list�b��BushouID[0] = 0xFFFF;
	list�b��BushouID[1] = 0xFFFF;
	list�b��BushouID[2] = 0xFFFF;
	list�b��BushouID[3] = 0xFFFF;

	int iBushouPtr_1st = *((int*)0x5D988C);
	int iBushouID_1st = getBushouIDFromBushouPtr((int*)iBushouPtr_1st);
	if (isValidBushouID(iBushouID_1st)) {
		list�b��BushouID[0] = iBushouID_1st;
		OutputDebugStream("1�l�ڂ̘b�҂�" + getBushou����FromBushouID(iBushouID_1st) + "�ł��B\n");
	}

	int iBushouPtr_2nd = *((int*)0x5D9890);
	int iBushouID_2nd = getBushouIDFromBushouPtr((int*)iBushouPtr_2nd);
	if (isValidBushouID(iBushouID_2nd)) {
		list�b��BushouID[1] = iBushouID_2nd;
		OutputDebugStream("2�l�ڂ̘b�҂�" + getBushou����FromBushouID(iBushouID_2nd) + "�ł��B\n");
	}

	int iBushouPtr_3rd = *((int*)0x5D9894);
	int iBushouID_3rd = getBushouIDFromBushouPtr((int*)iBushouPtr_3rd);
	if (isValidBushouID(iBushouID_3rd)) {
		list�b��BushouID[2] = iBushouID_3rd;
		OutputDebugStream("3�l�ڂ̘b�҂�" + getBushou����FromBushouID(iBushouID_3rd) + "�ł��B\n");
	}

	int iBushouPtr_4th = *((int*)0x5D9898);
	int iBushouID_4th = getBushouIDFromBushouPtr((int*)iBushouPtr_4th);
	if (isValidBushouID(iBushouID_4th)) {
		list�b��BushouID[3] = iBushouID_4th;
		OutputDebugStream("4�l�ڂ̘b�҂�" + getBushou����FromBushouID(iBushouID_4th) + "�ł��B\n");
	}

}

/*
00496233   A3 A0985D00      MOV DWORD PTR DS:[5D98A0],EAX
00496238   E8 33FEFFFF      CALL Nobunaga.00496070
0049623D   83C4 08          ADD ESP,8
00496240   5E               POP ESI
00496241   59               POP ECX
*/
int pSSRExeJumpFromToOnSSRExeSetSerifuAllButhouLocA = 0x496238; // �֐��͂��̃A�h���X����AOnSSRExeSetSerifuAllButhouLocA�ւƃW�����v���Ă���B
int pSSRExeJumpCallFromToOnSSRExeSetSerifuAllButhouLocA = 0x496070; // ���X������������Call��
int pSSRExeReturnLblFromOnSSRExeSetSerifuAllButhouLocA = 0x49623D; // �֐����Ō�܂ł����ƁA���̎��sexe���ɒ��ڃW�����v����

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeSetSerifuAllButhouLocA() {
	// �X�^�b�N�ɂ��߂Ă���
	__asm {

		call pSSRExeJumpCallFromToOnSSRExeSetSerifuAllButhouLocA

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeSetSerifuAllButhouLocAExecute();

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

		jmp pSSRExeReturnLblFromOnSSRExeSetSerifuAllButhouLocA
	}
}
#pragma warning(default: 4733) // ���[�j���O�̗}������������



char cmdOnSSRExeJumpFromSetSerifuAllButhouLocA[6] = "\xE9";
// ���̖��߂�5�o�C�g�A�Ȍ�̊֐��Ő��܂�閽�߂����v�T�o�C�g�Ȃ̂Łc �Ō�P�g��Ȃ�


// �j�[���j�b�N���������p
void WriteAsmJumperOnSSRExeSetSerifuAllButhouLocA() {

	// �܂��A�h���X�𐔎��Ƃ��Ĉ���
	int iAddress = (int)OnSSRExeSetSerifuAllButhouLocA;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeSetSerifuAllButhouLocA + 5);
	// �T�Ƃ����̂́A0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  �̖��߂ɕK�v�ȃo�C�g���B�v����ɂT�o�C�g�����Ǝ��̃j�[���j�b�N���ߌQ�Ɉړ�����̂��B�����Ă�������̍������W�����v����ۂ̖ړI�i�Ƃ��ė��p�����B
	memcpy(cmdOnSSRExeJumpFromSetSerifuAllButhouLocA + 1, &SubAddress, 4); // +1 ��E9�̎�����4�o�C�g�����������邩��B

	// �\�z�����j�[���j�b�N���߂����sexe�̃������ɏ���������
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeSetSerifuAllButhouLocA), cmdOnSSRExeJumpFromSetSerifuAllButhouLocA, 5, NULL); //5�o�C�g�̂ݏ�������
}

#pragma managed
