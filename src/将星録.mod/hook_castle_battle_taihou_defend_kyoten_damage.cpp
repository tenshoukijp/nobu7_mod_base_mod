/*
004131E9   8BCE             MOV ECX,ESI
004131EB   E8 A0F8FEFF      CALL Nobunaga.00402A90
004131F0   50               PUSH EAX                                 ���̎���EAX���U�����̌�����̖h��l�BECX+0xA�̃A�h���X�� EAX�̒l�Ɠ����l�����邱�ƁB
004131F1   57               PUSH EDI
004131F2   68 B40C5200      PUSH Nobunaga.00520CB4                   ; ASCII "�h�䋒�_ : %d ---> %d"


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


static int ECXOfCastleBattleTaihouDefendKyotenDamage = 0;
static int EAXOfCastleBattleTaihouDefendKyotenDamage = 0;
void OnSSRExeCastleBattleTaihouDefendKyotenDamageExecute() {
	int* pRemainKyotenPtr = (int*)((BYTE*)(ECXOfCastleBattleTaihouDefendKyotenDamage)+0x8); // �����ɋ��_�ւ̖h��l�ւ̃|�C���^�������Ă���

	int nBushouAddress = (int)(���b�Z�[�W�������.p��̕���);
	int iBushouID = getBushouIDFromBushouPtr((int*)nBushouAddress);
	if (isValidBushouID(iBushouID)) {
		OutputDebugStream("���_�̎c��ϋv�x%d\n", *pRemainKyotenPtr);
		OutputDebugStream("�U����" + getBushou����FromBushouID(iBushouID) + "\n");


		if (getBushou����FromBushouID(iBushouID) == getArubedoSeiMei()) {
			OutputDebugStream("�A���x�h�ɂ�鋒�_�̎c��ϋv�x�̏㏑��\n");
			*pRemainKyotenPtr = 0;                            // �����Ŏc��h���0�ɂ���
			EAXOfCastleBattleTaihouDefendKyotenDamage = 0; // EAX�ɂ��c��h������Ă����B���ꂪ��ʂŕ\������p
		}

		// EAX �� *pRemainKyotenPtr ���㏑������Ȃ炱���ŁB
	}

}

/*
004131E9   8BCE             MOV ECX,ESI
004131EB   E8 A0F8FEFF      CALL Nobunaga.00402A90
004131F0   50               PUSH EAX                                 ���̎���EAX���U�����̌�����̖h��l�BECX+0xA�̃A�h���X�� EAX�̒l�Ɠ����l�����邱�ƁB
004131F1   57               PUSH EDI
004131F2   68 B40C5200      PUSH Nobunaga.00520CB4                   ; ASCII "�h�䋒�_ : %d ---> %d"
*/

int pSSRExeJumpFromToOnSSRExeCastleBattleTaihouDefendKyotenDamage = 0x4131EB; // �֐��͂��̃A�h���X����AOnSSRExeCastleBattleTaihouDefendKyotenDamage�ւƃW�����v���Ă���B
int pSSRExeJumpCallFromToOnSSRExeCastleBattleTaihouDefendKyotenDamage = 0x402A90; // ���X������������Call��
int pSSRExeReturnLblFromOnSSRExeCastleBattleTaihouDefendKyotenDamage = 0x4131F0; // �֐����Ō�܂ł����ƁA����TENSHOU.EXE���ɒ��ڃW�����v����

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeCastleBattleTaihouDefendKyotenDamage() {
	// �X�^�b�N�ɂ��߂Ă���
	__asm {

		mov ECXOfCastleBattleTaihouDefendKyotenDamage, ecx

		call pSSRExeJumpCallFromToOnSSRExeCastleBattleTaihouDefendKyotenDamage

		mov EAXOfCastleBattleTaihouDefendKyotenDamage, eax

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeCastleBattleTaihouDefendKyotenDamageExecute();

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

		mov eax, EAXOfCastleBattleTaihouDefendKyotenDamage  // ������̎c��h���ύX����Ȃ炱���ŕύX���Ă����B
		jmp pSSRExeReturnLblFromOnSSRExeCastleBattleTaihouDefendKyotenDamage
	}
}
#pragma warning(default: 4733) // ���[�j���O�̗}������������



char cmdOnSSRExeJumpFromCastleBattleTaihouDefendKyotenDamage[6] = "\xE9";
// ���̖��߂�5�o�C�g�A�Ȍ�̊֐��Ő��܂�閽�߂����v�T�o�C�g�Ȃ̂Łc �Ō�P�g��Ȃ�


// �j�[���j�b�N���������p
void WriteAsmJumperOnSSRExeCastleBattleTaihouDefendKyotenDamage() {

	// �܂��A�h���X�𐔎��Ƃ��Ĉ���
	int iAddress = (int)OnSSRExeCastleBattleTaihouDefendKyotenDamage;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeCastleBattleTaihouDefendKyotenDamage + 5);
	// �T�Ƃ����̂́A0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  �̖��߂ɕK�v�ȃo�C�g���B�v����ɂT�o�C�g�����Ǝ��̃j�[���j�b�N���ߌQ�Ɉړ�����̂��B�����Ă�������̍������W�����v����ۂ̖ړI�i�Ƃ��ė��p�����B
	memcpy(cmdOnSSRExeJumpFromCastleBattleTaihouDefendKyotenDamage + 1, &SubAddress, 4); // +1 ��E9�̎�����4�o�C�g�����������邩��B

	// �\�z�����j�[���j�b�N���߂�TENSHOU.EXE�̃������ɏ���������
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeCastleBattleTaihouDefendKyotenDamage), cmdOnSSRExeJumpFromCastleBattleTaihouDefendKyotenDamage, 5, NULL); //5�o�C�g�̂ݏ�������
}

#pragma managed
