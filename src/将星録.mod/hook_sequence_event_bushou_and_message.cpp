/*
�����ԂȂǂ̃C�x���g�̍ۂ̃��b�Z�[�W�B�Z���t���Œ�ł��邽�߁A�{���̗���(hook_set_serihu_busyou_a �� _b)�ł͕������ݒ肳��Ȃ��B
(�ʉ߂͂��Ă��邪�������ݒ肳��Ă��Ȃ�)
0044B930   83EC 20          SUB ESP,20
0044B933   53               PUSH EBX
0044B934   55               PUSH EBP
0044B935   8BE9             MOV EBP,ECX
0044B937   837D 0C 00       CMP DWORD PTR SS:[EBP+C],0
0044B93B   56               PUSH ESI
0044B93C   57               PUSH EDI

EAX 005D9638 ASCII "��c�c ���b�Z�[�W���e
���Ă�c�c"
ECX 0019FBD8
EDX 00000003
EBX 00000000
ESP 0019FAF8
EBP 0019FBD8
ESI 0019FBD8
EDI 0054B7C8 ASCII "�D�c"   �� �����|�C���^

*/

// ���̏����͐��������A���݂��̏����ł̓^�C�~���O�I�ɊԂɍ���Ȃ��B

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
static int EDIOfSetSerifuAllButhouLocC = 0xFFFF;
void OnSSRExeSetSerifuAllButhouLocCExecute() {
	OutputDebugStream("�b�҂̍X�V�ꏊ C\n");

	list�b��BushouID[0] = 0xFFFF;
	list�b��BushouID[1] = 0xFFFF;
	list�b��BushouID[2] = 0xFFFF;
	list�b��BushouID[3] = 0xFFFF;

	int iBushouID_1st = getBushouIDFromBushouPtr((int *)EDIOfSetSerifuAllButhouLocC);
	if (isValidBushouID(iBushouID_1st)) {
		list�b��BushouID[0] = iBushouID_1st;
		OutputDebugStream("1�l�ڂ̘b�҂�" + getBushou����FromBushouID(iBushouID_1st) + "�ł��B\n");
	}
}

/*
0044B930   83EC 20          SUB ESP,20
0044B933   53               PUSH EBX
0044B934   55               PUSH EBP
0044B935   8BE9             MOV EBP,ECX
0044B937   837D 0C 00       CMP DWORD PTR SS:[EBP+C],0
0044B93B   56               PUSH ESI
0044B93C   57               PUSH EDI
*/
int pSSRExeJumpFromToOnSSRExeSetSerifuAllButhouLocC = 0x44B930; // �֐��͂��̃A�h���X����AOnSSRExeSetSerifuAllButhouLocC�ւƃW�����v���Ă���B
int pSSRExeReturnLblFromOnSSRExeSetSerifuAllButhouLocC = 0x44B935; // �֐����Ō�܂ł����ƁA����TENSHOU.EXE���ɒ��ڃW�����v����

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeSetSerifuAllButhouLocC() {
	// �X�^�b�N�ɂ��߂Ă���
	__asm {

		SUB ESP, 0x20	// ���̏���
		PUSH EBX		// ���̏���
		PUSH EBP		// ���̏���

		mov EDIOfSetSerifuAllButhouLocC, EDI // EDI�͘b�҂̑�P�b�҂ւ̕����|�C���^������

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeSetSerifuAllButhouLocCExecute();

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

		jmp pSSRExeReturnLblFromOnSSRExeSetSerifuAllButhouLocC
	}
}
#pragma warning(default: 4733) // ���[�j���O�̗}������������



char cmdOnSSRExeJumpFromSetSerifuAllButhouLocC[6] = "\xE9";
// ���̖��߂�5�o�C�g�A�Ȍ�̊֐��Ő��܂�閽�߂����v�T�o�C�g�Ȃ̂Łc �Ō�P�g��Ȃ�


// �j�[���j�b�N���������p
void WriteAsmJumperOnSSRExeSetSerifuAllButhouLocC() {

	// �܂��A�h���X�𐔎��Ƃ��Ĉ���
	int iAddress = (int)OnSSRExeSetSerifuAllButhouLocC;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeSetSerifuAllButhouLocC + 5);
	// �T�Ƃ����̂́A0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  �̖��߂ɕK�v�ȃo�C�g���B�v����ɂT�o�C�g�����Ǝ��̃j�[���j�b�N���ߌQ�Ɉړ�����̂��B�����Ă�������̍������W�����v����ۂ̖ړI�i�Ƃ��ė��p�����B
	memcpy(cmdOnSSRExeJumpFromSetSerifuAllButhouLocC + 1, &SubAddress, 4); // +1 ��E9�̎�����4�o�C�g�����������邩��B

	// �\�z�����j�[���j�b�N���߂�TENSHOU.EXE�̃������ɏ���������
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeSetSerifuAllButhouLocC), cmdOnSSRExeJumpFromSetSerifuAllButhouLocC, 5, NULL); //5�o�C�g�̂ݏ�������
}

#pragma managed
