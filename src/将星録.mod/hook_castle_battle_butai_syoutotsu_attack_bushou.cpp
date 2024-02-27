/*
0041713D   8BCE             MOV ECX,ESI
0041713F   33FF             XOR EDI,EDI
00417141   E8 4AB9FEFF      CALL Nobunaga.00402A90�@�@�@�@�@�@�@�@�@�@�@�@�@����CALL���ESP+0x10 �ɍU�����̕������̊Y�������ւ̃|�C���^�������Ă���
00417146   8B4C24 58        MOV ECX,DWORD PTR SS:[ESP+58]            ; Nobunaga.0053FF38
0041714A   8BE8             MOV EBP,EAX


EAX 0019FA60
ECX 00541500 Nobunaga.00541500
EDX 00000128
EBX 005409D0 Nobunaga.005409D0
ESP 0019FA5C ASCII "�	"      ESP��
EBP 00541500 Nobunaga.00541500
ESI 005401D2 Nobunaga.005401D2
EDI 00000000
EIP 0041712A Nobunaga.0041712A
*/


/*
004171C7   E8 C4B8FEFF      CALL Nobunaga.00402A90                    ��������s������AECX+8�̃A�h���X�� EAX�̒l�Ɠ����l�����邱�ƁB
004171CC   8B5424 54        MOV EDX,DWORD PTR SS:[ESP+54]
004171D0   50               PUSH EAX                                  ���̎���EAX���h�䑤�̌�����̕���
004171D1   52               PUSH EDX                                  �����͖h�䑤�̍ő啺�� 
004171D2   8BCE             MOV ECX,ESI


004171D4   E8 B7B8FEFF      CALL Nobunaga.00402A90
004171D9   50               PUSH EAX                                  ���̎���EAX���U�����̌�����̕���
004171DA   55               PUSH EBP                                  EBP�̃A�h���X�ɂ�EAX�Ɠ����l�����邽�߁A�����������������K�v������
004171DB   68 180E5200      PUSH Nobunaga.00520E18                   ; ASCII "�U������ : %d ---> %d
�h�䋒�_ : %d ---> %d"
004171E0   68 D8A55D00      PUSH Nobunaga.005DA5D8                   ; ASCII "  ���q��  1490"
004171E5   E8 8DB50E00      CALL Nobunaga.00502777
004171EA   83C4 18          ADD ESP,18

EAX 0000037A
ECX 00540204 Nobunaga.00540204
EDX 00000046
EBX 005408DA Nobunaga.005408DA
ESP 0019FA60
EBP 00000384
ESI 00540204 Nobunaga.00540204
EDI 0000000A
EIP 004171DA Nobunaga.004171DA

005401FC                          03 00 00 00 19 00 00 00          ......
0054020C  7A 03 00 00 84 03 00 00 07 00 00 00 84 03        z..�E.....�E..

*/



#include <windows.h>
#include <string>
#include "data_game_struct.h"
#include "data_bushou_struct.h"
#include "output_debug_stream.h"
#include "game_process.h"


using namespace std;

#pragma unmanaged

int iCastleBattleButaishoutotsuAttackBushouID = -1;
static int EspOfCastleBattleButaisyoutotsuAttackBushou = 0;
void OnSSRExeCastleBattleButaisyoutotsuAttackBushouExecute() {
	iCastleBattleButaishoutotsuAttackBushouID = -1;
	OutputDebugStream("�������ď��E�����ՓˁE�U������������\n");
	BYTE* pBushouPtr = (BYTE*)(EspOfCastleBattleButaisyoutotsuAttackBushou)+0x10; // �����ɍU�����������|�C���^�������Ă���
	int AttackBushouPtrOfCastleBattleButaishoutotsu = *((int*)(pBushouPtr));
	OutputDebugStream("�U�������|�C���^%x\n", pBushouPtr);
	OutputDebugStream("�U�������|�C���^�f���t�@�����X%x\n", AttackBushouPtrOfCastleBattleButaishoutotsu);

	int iBushouID = getBushouIDFromBushouPtr((int*)AttackBushouPtrOfCastleBattleButaishoutotsu);
	OutputDebugStream("�U������ID%d", iBushouID);
	OutputDebugStream("iCastleBattleButaishoutotsuAttackBushouID �ւ̑��\n");
	iCastleBattleButaishoutotsuAttackBushouID = iBushouID;
	if (isValidBushouID(iBushouID)) {
		OutputDebugStream("����%d\n", iBushouID);
		OutputDebugStream("�������U����������\n");
		OutputDebugStream(getBushou����FromBushouID(iBushouID) + "\n");
	}
}

/*
0041713D   8BCE             MOV ECX,ESI
0041713F   33FF             XOR EDI,EDI
00417141   E8 4AB9FEFF      CALL Nobunaga.00402A90�@�@�@�@�@�@�@�@�@�@�@�@�@����CALL���ESP+0x8 �ɍU�����̕������̊Y�������ւ̃|�C���^�������Ă���
00417146   8B4C24 58        MOV ECX,DWORD PTR SS:[ESP+58]            ; Nobunaga.0053FF38
0041714A   8BE8             MOV EBP,EAX


EAX 0019FA60
ECX 00541500 Nobunaga.00541500
EDX 00000128
EBX 005409D0 Nobunaga.005409D0
ESP 0019FA5C ASCII "�	"      ESP��
EBP 00541500 Nobunaga.00541500
ESI 005401D2 Nobunaga.005401D2
EDI 00000000
EIP 0041712A Nobunaga.0041712A
*/

int pSSRExeJumpFromToOnSSRExeCastleBattleButaisyoutotsuAttackBushou = 0x417141; // �֐��͂��̃A�h���X����AOnSSRExeCastleBattleButaisyoutotsuAttackBushou�ւƃW�����v���Ă���B
int pSSRExeJumpCallFromToOnSSRExeCastleBattleButaisyoutotsuAttackBushou = 0x402A90; // ���X������������Call��
int pSSRExeReturnLblFromOnSSRExeCastleBattleButaisyoutotsuAttackBushou = 0x417146; // �֐����Ō�܂ł����ƁA����TENSHOU.EXE���ɒ��ڃW�����v����

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeCastleBattleButaisyoutotsuAttackBushou() {
	// �X�^�b�N�ɂ��߂Ă���
	__asm {
		call pSSRExeJumpCallFromToOnSSRExeCastleBattleButaisyoutotsuAttackBushou

		mov EspOfCastleBattleButaisyoutotsuAttackBushou, esp

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeCastleBattleButaisyoutotsuAttackBushouExecute();

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

		jmp pSSRExeReturnLblFromOnSSRExeCastleBattleButaisyoutotsuAttackBushou
	}
}
#pragma warning(default: 4733) // ���[�j���O�̗}������������



char cmdOnSSRExeJumpFromCastleBattleButaisyoutotsuAttackBushou[6] = "\xE9";
// ���̖��߂�5�o�C�g�A�Ȍ�̊֐��Ő��܂�閽�߂����v�T�o�C�g�Ȃ̂Łc �Ō�P�g��Ȃ�


// �j�[���j�b�N���������p
void WriteAsmJumperOnSSRExeCastleBattleButaisyoutotsuAttackBushou() {

	// �܂��A�h���X�𐔎��Ƃ��Ĉ���
	int iAddress = (int)OnSSRExeCastleBattleButaisyoutotsuAttackBushou;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeCastleBattleButaisyoutotsuAttackBushou + 5);
	// �T�Ƃ����̂́A0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  �̖��߂ɕK�v�ȃo�C�g���B�v����ɂT�o�C�g�����Ǝ��̃j�[���j�b�N���ߌQ�Ɉړ�����̂��B�����Ă�������̍������W�����v����ۂ̖ړI�i�Ƃ��ė��p�����B
	memcpy(cmdOnSSRExeJumpFromCastleBattleButaisyoutotsuAttackBushou + 1, &SubAddress, 4); // +1 ��E9�̎�����4�o�C�g�����������邩��B

	// �\�z�����j�[���j�b�N���߂�TENSHOU.EXE�̃������ɏ���������
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeCastleBattleButaisyoutotsuAttackBushou), cmdOnSSRExeJumpFromCastleBattleButaisyoutotsuAttackBushou, 5, NULL); //5�o�C�g�̂ݏ�������
}

#pragma managed
