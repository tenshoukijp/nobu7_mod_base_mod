/*
00403C80   8B49 18          MOV ECX,DWORD PTR DS:[ECX+18]            ; Nobunaga.005EEB5C
00403C83   8B4424 04        MOV EAX,DWORD PTR SS:[ESP+4]
00403C87   8908             MOV DWORD PTR DS:[EAX],ECX
00403C89   C2 0400          RETN 4
*/

// ���̊֐��́A�ď�펞�ɍU�����̕����|�C���^����U�����̕����|�C���^���擾����֐��ł��B
// ���̊֐������s����邱�Ƃ��t�b�N����΁A�ł����߂Ŏ擾���ꂽ�����𓾂邱�Ƃ��o����




#include <windows.h>
#include <string>
#include "data_game_struct.h"
#include "data_bushou_struct.h"
#include "output_debug_stream.h"
#include "game_process.h"
#include "bushou_albedo.h"

using namespace std;

#pragma unmanaged

int iLastBushouIDOfCastleBattleAttackBushou = 0xFFFF; // �Ō�ɃA�N�Z�X�����ď��̍U��BushouID

int iLastBushouPtrOfCastleBattleAttackBushou = 0; // �Ō�ɃA�N�Z�X�����ď��̍U�������|�C���^

void OnSSRExeCastleBattleAttackBushouExecute() {

	int iBushouID = getBushouIDFromBushouPtr((int *)iLastBushouPtrOfCastleBattleAttackBushou);
	if (isValidBushouID(iBushouID)) {
		iLastBushouIDOfCastleBattleAttackBushou = iBushouID;
		OutputDebugStream("�����U��������ID%d\n", iBushouID);
	}
}

/*
00403C80   8B49 18          MOV ECX,DWORD PTR DS:[ECX+18]            ; Nobunaga.005EEB5C
00403C83   8B4424 04        MOV EAX,DWORD PTR SS:[ESP+4]
00403C87   8908             MOV DWORD PTR DS:[EAX],ECX
00403C89   C2 0400          RETN 4
*/

int pSSRExeJumpFromToOnSSRExeCastleBattleAttackBushou = 0x403C80; // �֐��͂��̃A�h���X����AOnSSRExeCastleBattleAttackBushou�ւƃW�����v���Ă���B
int pSSRExeReturnLblFromOnSSRExeCastleBattleAttackBushou = 0x403C87; // �֐����Ō�܂ł����ƁA���̎��sexe���ɒ��ڃW�����v����

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeCastleBattleAttackBushou() {
	// �X�^�b�N�ɂ��߂Ă���
	__asm {

		MOV ECX, DWORD PTR DS : [ECX + 0x18]
		MOV EAX, DWORD PTR SS : [ESP + 0x4]

		mov iLastBushouPtrOfCastleBattleAttackBushou, ecx


		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeCastleBattleAttackBushouExecute();

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

		jmp pSSRExeReturnLblFromOnSSRExeCastleBattleAttackBushou
	}
}
#pragma warning(default: 4733) // ���[�j���O�̗}������������



char cmdOnSSRExeJumpFromCastleBattleAttackBushou[8] = "\xE9\x90\x90\x90\x90\x90\x90";
// ���̖��߂�5�o�C�g�A�Ȍ�̊֐��Ő��܂�閽�߂����v�T�o�C�g�Ȃ̂Łc �Ō�P�g��Ȃ�


// �j�[���j�b�N���������p
void WriteAsmJumperOnSSRExeCastleBattleAttackBushou() {

	// �܂��A�h���X�𐔎��Ƃ��Ĉ���
	int iAddress = (int)OnSSRExeCastleBattleAttackBushou;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeCastleBattleAttackBushou + 5);
	// �T�Ƃ����̂́A0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  �̖��߂ɕK�v�ȃo�C�g���B�v����ɂT�o�C�g�����Ǝ��̃j�[���j�b�N���ߌQ�Ɉړ�����̂��B�����Ă�������̍������W�����v����ۂ̖ړI�i�Ƃ��ė��p�����B
	memcpy(cmdOnSSRExeJumpFromCastleBattleAttackBushou + 1, &SubAddress, 4); // +1 ��E9�̎�����4�o�C�g�����������邩��B

	// �\�z�����j�[���j�b�N���߂����sexe�̃������ɏ���������
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeCastleBattleAttackBushou), cmdOnSSRExeJumpFromCastleBattleAttackBushou, 7, NULL); //7�o�C�g�̂ݏ�������
}

#pragma managed
