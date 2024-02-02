/*
00415C1B   8BCF             MOV ECX,EDI
00415C1D   E8 6ECEFEFF      CALL Nobunaga.00402A90
00415C22   50               PUSH EAX                               ���̎���EAX���U�����̌�����̖h��l�BECX+0x8�̃A�h���X�� EAX�̒l�Ɠ����l�����邱�ƁB
00415C23   53               PUSH EBX                               �����͖h�䑤�̒l
00415C24   68 7C0D5200      PUSH Nobunaga.00520D7C                   ; ASCII "�h��x : %d ---> %d
�h�䋒�_ : %d ---> %d"
00415C29   68 D8A55D00      PUSH Nobunaga.005DA5D8                   ; ASCII "  ���q��   475"

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
#include "castle_battle_attack_heisuu_sum.h"

using namespace std;

#pragma unmanaged

extern int iCastleBattleTaihouAttackBushou;
static int ECXOfCastleBattleTaihouDefendHonmaruDamage = 0;
static int EAXOfCastleBattleTaihouDefendHonmaruDamage = 0;
void OnSSRExeCastleBattleTaihouDefendHonmaruDamageExecute() {
	int* pRemainHonmaruPtr = (int*)((BYTE*)(ECXOfCastleBattleTaihouDefendHonmaruDamage)+0x8); // �����ɋ��_�ւ̖h��l�ւ̃|�C���^�������Ă���

	int nBushouAddress = (int)(���b�Z�[�W�������.p��̕���);
	int iDefendBushouID = getBushouIDFromBushouPtr((int*)nBushouAddress);
	// ���ꂪ�������Ƃ������Ƃ́A�h�䑤�̕����̓Z���t�Ɠf���Ă��Ȃ��Ƃ������ƂȂ̂ŁA�h�䑤�͎w���������Ȃ�
	if (iCastleBattleTaihouAttackBushou == iDefendBushouID) {

	}
	else {
		// �قȂ�Ƃ������Ƃ́A�h�䑤�̕������Z���t�Ɠf�����Ƃ������ƂȂ̂ŁA�h�䑤�͎w����������
	}

	OutputDebugStream("��������C�̍U�����̕���" + getBushou����FromBushouID(iCastleBattleTaihouAttackBushou) + "\n");
	int iBushouID = iCastleBattleTaihouAttackBushou;
	if (isValidBushouID(iBushouID)) {
		OutputDebugStream("���_�̎c��ϋv�x%d\n", *pRemainHonmaruPtr);
		OutputDebugStream("�U����" + getBushou����FromBushouID(iBushouID) + "\n");


		if (getBushou����FromBushouID(iBushouID) == getArubedoSeiMei()) {
			OutputDebugStream("�A���x�h�ɂ�鋒�_�̎c��ϋv�x�̏㏑��\n");
			*pRemainHonmaruPtr = 0;                            // �����Ŏc��h���0�ɂ���
			EAXOfCastleBattleTaihouDefendHonmaruDamage = 0; // EAX�ɂ��c��h������Ă����B���ꂪ��ʂŕ\������p
		}

		// EAX �� *pRemainHonmaruPtr ���㏑������Ȃ炱���ŁB
	}

}

/*
00415C1B   8BCF             MOV ECX,EDI
00415C1D   E8 6ECEFEFF      CALL Nobunaga.00402A90
00415C22   50               PUSH EAX                               ���̎���EAX���U�����̌�����̖h��l�BECX+0x8�̃A�h���X�� EAX�̒l�Ɠ����l�����邱�ƁB
00415C23   53               PUSH EBX                               �����͖h�䑤�̒l
00415C24   68 7C0D5200      PUSH Nobunaga.00520D7C                   ; ASCII "�h��x : %d ---> %d
�h�䋒�_ : %d ---> %d"
00415C29   68 D8A55D00      PUSH Nobunaga.005DA5D8                   ; ASCII "  ���q��   475"
*/


int pSSRExeJumpFromToOnSSRExeCastleBattleTaihouDefendHonmaruDamage = 0x415C1D; // �֐��͂��̃A�h���X����AOnSSRExeCastleBattleTaihouDefendHonmaruDamage�ւƃW�����v���Ă���B
int pSSRExeJumpCallFromToOnSSRExeCastleBattleTaihouDefendHonmaruDamage = 0x402A90; // ���X������������Call��
int pSSRExeReturnLblFromOnSSRExeCastleBattleTaihouDefendHonmaruDamage = 0x415C22; // �֐����Ō�܂ł����ƁA����TENSHOU.EXE���ɒ��ڃW�����v����

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeCastleBattleTaihouDefendHonmaruDamage() {
	// �X�^�b�N�ɂ��߂Ă���
	__asm {

		mov ECXOfCastleBattleTaihouDefendHonmaruDamage, ecx

		call pSSRExeJumpCallFromToOnSSRExeCastleBattleTaihouDefendHonmaruDamage

		mov EAXOfCastleBattleTaihouDefendHonmaruDamage, eax

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeCastleBattleTaihouDefendHonmaruDamageExecute();

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

		mov eax, EAXOfCastleBattleTaihouDefendHonmaruDamage  // ������̎c��h���ύX����Ȃ炱���ŕύX���Ă����B
		jmp pSSRExeReturnLblFromOnSSRExeCastleBattleTaihouDefendHonmaruDamage
	}
}
#pragma warning(default: 4733) // ���[�j���O�̗}������������



char cmdOnSSRExeJumpFromCastleBattleTaihouDefendHonmaruDamage[6] = "\xE9";
// ���̖��߂�5�o�C�g�A�Ȍ�̊֐��Ő��܂�閽�߂����v�T�o�C�g�Ȃ̂Łc �Ō�P�g��Ȃ�


// �j�[���j�b�N���������p
void WriteAsmJumperOnSSRExeCastleBattleTaihouDefendHonmaruDamage() {

	// �܂��A�h���X�𐔎��Ƃ��Ĉ���
	int iAddress = (int)OnSSRExeCastleBattleTaihouDefendHonmaruDamage;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeCastleBattleTaihouDefendHonmaruDamage + 5);
	// �T�Ƃ����̂́A0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  �̖��߂ɕK�v�ȃo�C�g���B�v����ɂT�o�C�g�����Ǝ��̃j�[���j�b�N���ߌQ�Ɉړ�����̂��B�����Ă�������̍������W�����v����ۂ̖ړI�i�Ƃ��ė��p�����B
	memcpy(cmdOnSSRExeJumpFromCastleBattleTaihouDefendHonmaruDamage + 1, &SubAddress, 4); // +1 ��E9�̎�����4�o�C�g�����������邩��B

	// �\�z�����j�[���j�b�N���߂�TENSHOU.EXE�̃������ɏ���������
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeCastleBattleTaihouDefendHonmaruDamage), cmdOnSSRExeJumpFromCastleBattleTaihouDefendHonmaruDamage, 5, NULL); //5�o�C�g�̂ݏ�������
}

#pragma managed
