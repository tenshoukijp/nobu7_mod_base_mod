/*
004171C7   E8 C4B8FEFF      CALL Nobunaga.00402A90                    ��������s������AECX+8�̃A�h���X�� EAX�̒l�Ɠ����l�����邱�ƁB
004171CC   8B5424 54        MOV EDX,DWORD PTR SS:[ESP+54]
004171D0   50               PUSH EAX                                  ���̎���EAX���h�䑤�̌�����̕���
004171D1   52               PUSH EDX                                  �����͖h�䑤�̍ő啺��
004171D2   8BCE             MOV ECX,ESI
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


using namespace std;

#pragma unmanaged

extern int iCastleBattleButaishoutotsuAttackBushouID;


static int ECXOfCastleBattleButaisyoutotsuDefendDamage = 0;
static int EAXOfCastleBattleButaisyoutotsuDefendDamage = 0;
void OnSSRExeCastleBattleButaisyoutotsuDefendDamageExecute() {
	int* pRemainHeisuPtr = (int *)((BYTE*)(ECXOfCastleBattleButaisyoutotsuDefendDamage)+0x8); // �����ɍU�����������|�C���^�������Ă���

	int iBushouID = iCastleBattleButaishoutotsuAttackBushouID;

	if (isValidBushouID(iBushouID)) {
		if (getBushou����FromBushouID(iBushouID) == getArubedoSeiMei()) {
			OutputDebugStream("�������A���x�h�U���Ȃ̂Ŏc�蕺����0\n");
			*pRemainHeisuPtr = 0;                            // �����Ŏc�蕺����0�ւƋ߂Â���
			EAXOfCastleBattleButaisyoutotsuDefendDamage = 0; // EAX�ɂ��c�蕺�������Ă����B���ꂪ��ʂŕ\������p
		}
	}
}

/*
004171C7   E8 C4B8FEFF      CALL Nobunaga.00402A90                    ��������s������AECX+8�̃A�h���X�� EAX�̒l�Ɠ����l�����邱�ƁB
004171CC   8B5424 54        MOV EDX,DWORD PTR SS:[ESP+54]
004171D0   50               PUSH EAX                                  ���̎���EAX���h�䑤�̌�����̕���
004171D1   52               PUSH EDX                                  �����͖h�䑤�̍ő啺��
004171D2   8BCE             MOV ECX,ESI


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

int pSSRExeJumpFromToOnSSRExeCastleBattleButaisyoutotsuDefendDamage = 0x4171C7; // �֐��͂��̃A�h���X����AOnSSRExeCastleBattleButaisyoutotsuDefendDamage�ւƃW�����v���Ă���B
int pSSRExeJumpCallFromToOnSSRExeCastleBattleButaisyoutotsuDefendDamage = 0x402A90; // ���X������������Call��
int pSSRExeReturnLblFromOnSSRExeCastleBattleButaisyoutotsuDefendDamage = 0x4171CC; // �֐����Ō�܂ł����ƁA����TENSHOU.EXE���ɒ��ڃW�����v����

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeCastleBattleButaisyoutotsuDefendDamage() {
	// �X�^�b�N�ɂ��߂Ă���
	__asm {
		call pSSRExeJumpCallFromToOnSSRExeCastleBattleButaisyoutotsuDefendDamage

		mov ECXOfCastleBattleButaisyoutotsuDefendDamage, ecx
		mov EAXOfCastleBattleButaisyoutotsuDefendDamage, eax

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeCastleBattleButaisyoutotsuDefendDamageExecute();

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

		mov eax, EAXOfCastleBattleButaisyoutotsuDefendDamage  // ������̎c�蕺����ύX����Ȃ炱���ŕύX���Ă����B
		jmp pSSRExeReturnLblFromOnSSRExeCastleBattleButaisyoutotsuDefendDamage
	}
}
#pragma warning(default: 4733) // ���[�j���O�̗}������������



char cmdOnSSRExeJumpFromCastleBattleButaisyoutotsuDefendDamage[6] = "\xE9";
// ���̖��߂�5�o�C�g�A�Ȍ�̊֐��Ő��܂�閽�߂����v�T�o�C�g�Ȃ̂Łc �Ō�P�g��Ȃ�


// �j�[���j�b�N���������p
void WriteAsmJumperOnSSRExeCastleBattleButaisyoutotsuDefendDamage() {

	// �܂��A�h���X�𐔎��Ƃ��Ĉ���
	int iAddress = (int)OnSSRExeCastleBattleButaisyoutotsuDefendDamage;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeCastleBattleButaisyoutotsuDefendDamage + 5);
	// �T�Ƃ����̂́A0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  �̖��߂ɕK�v�ȃo�C�g���B�v����ɂT�o�C�g�����Ǝ��̃j�[���j�b�N���ߌQ�Ɉړ�����̂��B�����Ă�������̍������W�����v����ۂ̖ړI�i�Ƃ��ė��p�����B
	memcpy(cmdOnSSRExeJumpFromCastleBattleButaisyoutotsuDefendDamage + 1, &SubAddress, 4); // +1 ��E9�̎�����4�o�C�g�����������邩��B

	// �\�z�����j�[���j�b�N���߂�TENSHOU.EXE�̃������ɏ���������
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeCastleBattleButaisyoutotsuDefendDamage), cmdOnSSRExeJumpFromCastleBattleButaisyoutotsuDefendDamage, 5, NULL); //5�o�C�g�̂ݏ�������
}

#pragma managed
