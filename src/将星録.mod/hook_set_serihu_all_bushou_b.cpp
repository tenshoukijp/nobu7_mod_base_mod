/*
�Q�ƃf�[�^ �F Nobunaga:.text -> 00496070
���ڽ      �ި�������                                ����
00496070   PUSH ECX                                  (CPU����޳�ł̑I���ӏ�)
00496238   CALL Nobunaga.00496070
004962F8   CALL Nobunaga.00496070
*/

/*
004962F6   51               PUSH ECX
004962F7   50               PUSH EAX
004962F8   E8 73FDFFFF      CALL Nobunaga.00496070
004962FD   83C4 08          ADD ESP,8

*/



#include <windows.h>
#include <string>
#include <vector>
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

extern vector<int> list�b��BushouID;

void OnSSRExeSetSerifuAllButhouLocBExecute() {
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
		list�b��BushouID[1] = iBushouID_1st;
		OutputDebugStream("2�l�ڂ̘b�҂�" + getBushou����FromBushouID(iBushouID_2nd) + "�ł��B\n");
	}

	int iBushouPtr_3rd = *((int*)0x5D9894);
	int iBushouID_3rd = getBushouIDFromBushouPtr((int*)iBushouPtr_3rd);
	if (isValidBushouID(iBushouID_3rd)) {
		list�b��BushouID[2] = iBushouID_1st;
		OutputDebugStream("3�l�ڂ̘b�҂�" + getBushou����FromBushouID(iBushouID_3rd) + "�ł��B\n");
	}

	int iBushouPtr_4th = *((int*)0x5D9898);
	int iBushouID_4th = getBushouIDFromBushouPtr((int*)iBushouPtr_4th);
	if (isValidBushouID(iBushouID_4th)) {
		list�b��BushouID[3] = iBushouID_1st;
		OutputDebugStream("4�l�ڂ̘b�҂�" + getBushou����FromBushouID(iBushouID_4th) + "�ł��B\n");
	}

}

/*
004962F6   51               PUSH ECX
004962F7   50               PUSH EAX
004962F8   E8 73FDFFFF      CALL Nobunaga.00496070
004962FD   83C4 08          ADD ESP,8
*/
int pSSRExeJumpFromToOnSSRExeSetSerifuAllButhouLocB = 0x4962F8; // �֐��͂��̃A�h���X����AOnSSRExeSetSerifuAllButhouLocB�ւƃW�����v���Ă���B
int pSSRExeJumpCallFromToOnSSRExeSetSerifuAllButhouLocB = 0x496070; // ���X������������Call��
int pSSRExeReturnLblFromOnSSRExeSetSerifuAllButhouLocB = 0x4962FD; // �֐����Ō�܂ł����ƁA����TENSHOU.EXE���ɒ��ڃW�����v����

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeSetSerifuAllButhouLocB() {
	// �X�^�b�N�ɂ��߂Ă���
	__asm {

		call pSSRExeJumpCallFromToOnSSRExeSetSerifuAllButhouLocB

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeSetSerifuAllButhouLocBExecute();

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

		jmp pSSRExeReturnLblFromOnSSRExeSetSerifuAllButhouLocB
	}
}
#pragma warning(default: 4733) // ���[�j���O�̗}������������



char cmdOnSSRExeJumpFromSetSerifuAllButhouLocB[6] = "\xE9";
// ���̖��߂�5�o�C�g�A�Ȍ�̊֐��Ő��܂�閽�߂����v�T�o�C�g�Ȃ̂Łc �Ō�P�g��Ȃ�


// �j�[���j�b�N���������p
void WriteAsmJumperOnSSRExeSetSerifuAllButhouLocB() {

	// �܂��A�h���X�𐔎��Ƃ��Ĉ���
	int iAddress = (int)OnSSRExeSetSerifuAllButhouLocB;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeSetSerifuAllButhouLocB + 5);
	// �T�Ƃ����̂́A0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  �̖��߂ɕK�v�ȃo�C�g���B�v����ɂT�o�C�g�����Ǝ��̃j�[���j�b�N���ߌQ�Ɉړ�����̂��B�����Ă�������̍������W�����v����ۂ̖ړI�i�Ƃ��ė��p�����B
	memcpy(cmdOnSSRExeJumpFromSetSerifuAllButhouLocB + 1, &SubAddress, 4); // +1 ��E9�̎�����4�o�C�g�����������邩��B

	// �\�z�����j�[���j�b�N���߂�TENSHOU.EXE�̃������ɏ���������
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeSetSerifuAllButhouLocB), cmdOnSSRExeJumpFromSetSerifuAllButhouLocB, 5, NULL); //5�o�C�g�̂ݏ�������
}

#pragma managed
