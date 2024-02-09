/*
00417A61   8B4C24 54        MOV ECX,DWORD PTR SS:[ESP+54]
00417A65   E8 26B0FEFF      CALL Nobunaga.00402A90
00417A6A   50               PUSH EAX
00417A6B   8B4424 20        MOV EAX,DWORD PTR SS:[ESP+20]
00417A6F   50               PUSH EAX
00417A70   8BCE             MOV ECX,ESI
00417A72   E8 19B0FEFF      CALL Nobunaga.00402A90
00417A77   8B4C24 28        MOV ECX,DWORD PTR SS:[ESP+28]            ����ECX�͖h��l
00417A7B   50               PUSH EAX                                 ���̎���EAX���U�����̌�����̕����l�BECX+0x8�̃A�h���X�� EAX�̒l�Ɠ����l�����邱�ƁB
00417A7C   51               PUSH ECX
00417A7D   68 180E5200      PUSH Nobunaga.00520E18                   ; ASCII "�U������ : %d ---> %d �h�䋒�_ : %d ---> %d"
00417A82   68 D8A55D00      PUSH Nobunaga.005DA5D8                   ; ASCII "�c14���"

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

extern int iCastleBattleButaiKyotenAttackBushou;
static int ECXOfCastleBattleButaiSyototsuKyotenDamage = 0;
static int ESPOfCastleBattleButaiSyototsuKyotenDamage = 0;
static int EAXOfCastleBattleButaiSyototsuKyotenDamage = 0;
void OnSSRExeCastleBattleButaiSyototsuKyotenDamageExecute() {
	int* pRemainKyotenPtr = (int*)((BYTE*)(ECXOfCastleBattleButaiSyototsuKyotenDamage)+0x8); // �����ɋ��_�ւ̖h��l�ւ̃|�C���^�������Ă���

	int iDefendBushouID = get1stBushouIDFromMessageBushou();
	// ���ꂪ�������Ƃ������Ƃ́A�h�䑤�̕����̓Z���t�Ɠf���Ă��Ȃ��Ƃ������ƂȂ̂ŁA�h�䑤�͎w���������Ȃ�
	if (iCastleBattleButaiKyotenAttackBushou == iDefendBushouID) {

	}
	else {
		// �قȂ�Ƃ������Ƃ́A�h�䑤�̕������Z���t�Ɠf�����Ƃ������ƂȂ̂ŁA�h�䑤�͎w����������
	}

	int iBushouID = iCastleBattleButaiKyotenAttackBushou;
	if (isValidBushouID(iBushouID)) {
		OutputDebugStream("�U����" + getBushou����FromBushouID(iBushouID) + "\n");


		if (getBushou����FromBushouID(iBushouID) == getArubedoSeiMei()) {
			OutputDebugStream("�A���x�h�ɂ�鋒�_�̎c��ϋv�x�̏㏑��\n");
			*pRemainKyotenPtr = 0;                            // �����Ŏc�蕺����0�ɂ���
			EAXOfCastleBattleButaiSyototsuKyotenDamage = 0; // EAX�ɂ��c��h������Ă����B���ꂪ��ʂŕ\������p

		}

		// EAX �� *pRemainKyotenPtr ���㏑������Ȃ炱���ŁB
	}

}

/*
00417A61   8B4C24 54        MOV ECX,DWORD PTR SS:[ESP+54]
00417A65   E8 26B0FEFF      CALL Nobunaga.00402A90
00417A6A   50               PUSH EAX
*/

int pSSRExeJumpFromToOnSSRExeCastleBattleButaiSyototsuKyotenDamage = 0x417A65; // �֐��͂��̃A�h���X����AOnSSRExeCastleBattleButaiSyototsuKyotenDamage�ւƃW�����v���Ă���B
int pSSRExeJumpCallFromToOnSSRExeCastleBattleButaiSyototsuKyotenDamage = 0x402A90; // ���X������������Call��
int pSSRExeReturnLblFromOnSSRExeCastleBattleButaiSyototsuKyotenDamage = 0x417A6A; // �֐����Ō�܂ł����ƁA����TENSHOU.EXE���ɒ��ڃW�����v����

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeCastleBattleButaiSyototsuKyotenDamage() {
	// �X�^�b�N�ɂ��߂Ă���
	__asm {

		mov ECXOfCastleBattleButaiSyototsuKyotenDamage, ecx

		call pSSRExeJumpCallFromToOnSSRExeCastleBattleButaiSyototsuKyotenDamage

		mov EAXOfCastleBattleButaiSyototsuKyotenDamage, eax

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeCastleBattleButaiSyototsuKyotenDamageExecute();

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

		mov eax, EAXOfCastleBattleButaiSyototsuKyotenDamage  // ������̎c��h���ύX����Ȃ炱���ŕύX���Ă����B
		jmp pSSRExeReturnLblFromOnSSRExeCastleBattleButaiSyototsuKyotenDamage
	}
}
#pragma warning(default: 4733) // ���[�j���O�̗}������������



char cmdOnSSRExeJumpFromCastleBattleButaiSyototsuKyotenDamage[6] = "\xE9";
// ���̖��߂�5�o�C�g�A�Ȍ�̊֐��Ő��܂�閽�߂����v�T�o�C�g�Ȃ̂Łc �Ō�P�g��Ȃ�


// �j�[���j�b�N���������p
void WriteAsmJumperOnSSRExeCastleBattleButaiSyototsuKyotenDamage() {

	// �܂��A�h���X�𐔎��Ƃ��Ĉ���
	int iAddress = (int)OnSSRExeCastleBattleButaiSyototsuKyotenDamage;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeCastleBattleButaiSyototsuKyotenDamage + 5);
	// �T�Ƃ����̂́A0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  �̖��߂ɕK�v�ȃo�C�g���B�v����ɂT�o�C�g�����Ǝ��̃j�[���j�b�N���ߌQ�Ɉړ�����̂��B�����Ă�������̍������W�����v����ۂ̖ړI�i�Ƃ��ė��p�����B
	memcpy(cmdOnSSRExeJumpFromCastleBattleButaiSyototsuKyotenDamage + 1, &SubAddress, 4); // +1 ��E9�̎�����4�o�C�g�����������邩��B

	// �\�z�����j�[���j�b�N���߂�TENSHOU.EXE�̃������ɏ���������
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeCastleBattleButaiSyototsuKyotenDamage), cmdOnSSRExeJumpFromCastleBattleButaiSyototsuKyotenDamage, 5, NULL); //5�o�C�g�̂ݏ�������
}

#pragma managed
