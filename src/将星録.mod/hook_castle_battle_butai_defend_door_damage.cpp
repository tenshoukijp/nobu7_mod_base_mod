/*
00417662   8BCE             MOV ECX,ESI
00417664   E8 97BFFEFF      CALL Nobunaga.00403600
00417669   85C0             TEST EAX,EAX                             // EAX��ECX+0xA�̃A�h���X�̒l������B���ꂪ������̖h��l
*/
/*
00417693   85C0             TEST EAX,EAX
00417695   74 53            JE SHORT Nobunaga.004176EA
00417697   8BCE             MOV ECX,ESI
00417699   E8 62BFFEFF      CALL Nobunaga.00403600                   // EAX��ECX+0xA�̃A�h���X�̒l������B���ꂪ������̖h��l
0041769E   8B5424 58        MOV EDX,DWORD PTR SS:[ESP+58]
004176A2   50               PUSH EAX                                 ���̎���EAX���U�����̌�����̖h��l�BECX+0xA�̃A�h���X�� EAX�̒l�Ɠ����l�����邱�ƁB
004176A3   52               PUSH EDX
004176A4   68 A80D5200      PUSH Nobunaga.00520DA8                   ; ASCII "�h��x : %d ---> %d"
004176A9   68 D8A55D00      PUSH Nobunaga.005DA5D8                   ; ASCII "  0"
004176AE   E8 C4B00E00      CALL Nobunaga.00502777

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

static int ESPOfCastleBattleButaiDefendDoorDamage = 0;
static int ECXOfCastleBattleButaiDefendDoorDamage = 0;
static int EAXOfCastleBattleButaiDefendDoorDamage = 0;
void OnSSRExeCastleBattleButaiDefendDoorDamageExecute() {
	int* pRemainDoorPtr = (int*)((BYTE*)(ECXOfCastleBattleButaiDefendDoorDamage)+0xA); // �����Ƀh�A�̖h��l�ւ̃|�C���^�������Ă���
	int* pp�U�������|�C���^ = (int*)ESPOfCastleBattleButaiDefendDoorDamage;
	�ď��U�����������* p�U����������� = (�ď��U�����������*)(*pp�U�������|�C���^);
	int iBushouID = getBushouIDFromBushouPtr((int*)p�U�����������->p�w������);
	if (isValidBushouID(iBushouID)) {
		OutputDebugStream("�h�A�̎c��ϋv�x%d\n", *pRemainDoorPtr);
		OutputDebugStream("�U����" + getBushou����FromBushouID(iBushouID) + "\n");

		if (getBushou����FromBushouID(iBushouID) == getArubedoSeiMei()) {
			OutputDebugStream("�A���x�h�ɂ��h�A�̎c��ϋv�x�̏㏑��\n");
			*pRemainDoorPtr = 0;                            // �����Ŏc��h���0�ւƋ߂Â���
			EAXOfCastleBattleButaiDefendDoorDamage = 0; // EAX�ɂ��c��h������Ă����B���ꂪ��ʂŕ\������p
		}

		// EAX �� *pReimainDoorPtr ���㏑������Ȃ炱���ŁB
	}

}

/*
00417662   8BCE             MOV ECX,ESI
00417664   E8 97BFFEFF      CALL Nobunaga.00403600
00417669   85C0             TEST EAX,EAX                             // EAX��ECX+0xA�̃A�h���X�̒l������B���ꂪ������̖h��l
*/

int pSSRExeJumpFromToOnSSRExeCastleBattleButaiDefendDoorDamage = 0x417664; // �֐��͂��̃A�h���X����AOnSSRExeCastleBattleButaiDefendDoorDamage�ւƃW�����v���Ă���B
int pSSRExeJumpCallFromToOnSSRExeCastleBattleButaiDefendDoorDamage = 0x403600; // ���X������������Call��
int pSSRExeReturnLblFromOnSSRExeCastleBattleButaiDefendDoorDamage = 0x417669; // �֐����Ō�܂ł����ƁA����TENSHOU.EXE���ɒ��ڃW�����v����

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeCastleBattleButaiDefendDoorDamage() {
	// �X�^�b�N�ɂ��߂Ă���
	__asm {

		mov ECXOfCastleBattleButaiDefendDoorDamage, ecx

		mov ESPOfCastleBattleButaiDefendDoorDamage, esp

		call pSSRExeJumpCallFromToOnSSRExeCastleBattleButaiDefendDoorDamage

		mov EAXOfCastleBattleButaiDefendDoorDamage, eax

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeCastleBattleButaiDefendDoorDamageExecute();

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

		mov eax, EAXOfCastleBattleButaiDefendDoorDamage  // ������̎c��h���ύX����Ȃ炱���ŕύX���Ă����B
		jmp pSSRExeReturnLblFromOnSSRExeCastleBattleButaiDefendDoorDamage
	}
}
#pragma warning(default: 4733) // ���[�j���O�̗}������������



char cmdOnSSRExeJumpFromCastleBattleButaiDefendDoorDamage[6] = "\xE9";
// ���̖��߂�5�o�C�g�A�Ȍ�̊֐��Ő��܂�閽�߂����v�T�o�C�g�Ȃ̂Łc �Ō�P�g��Ȃ�


// �j�[���j�b�N���������p
void WriteAsmJumperOnSSRExeCastleBattleButaiDefendDoorDamage() {

	// �܂��A�h���X�𐔎��Ƃ��Ĉ���
	int iAddress = (int)OnSSRExeCastleBattleButaiDefendDoorDamage;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeCastleBattleButaiDefendDoorDamage + 5);
	// �T�Ƃ����̂́A0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  �̖��߂ɕK�v�ȃo�C�g���B�v����ɂT�o�C�g�����Ǝ��̃j�[���j�b�N���ߌQ�Ɉړ�����̂��B�����Ă�������̍������W�����v����ۂ̖ړI�i�Ƃ��ė��p�����B
	memcpy(cmdOnSSRExeJumpFromCastleBattleButaiDefendDoorDamage + 1, &SubAddress, 4); // +1 ��E9�̎�����4�o�C�g�����������邩��B

	// �\�z�����j�[���j�b�N���߂�TENSHOU.EXE�̃������ɏ���������
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeCastleBattleButaiDefendDoorDamage), cmdOnSSRExeJumpFromCastleBattleButaiDefendDoorDamage, 5, NULL); //5�o�C�g�̂ݏ�������
}

#pragma managed
