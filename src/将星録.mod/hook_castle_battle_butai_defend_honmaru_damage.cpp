/*
00416E36   8BCF             MOV ECX,EDI
00416E38   E8 53BCFEFF      CALL Nobunaga.00402A90
00416E3D   50               PUSH EAX                             ���̎���EAX���U�����̌�����̖h��l�BECX+0x8�̃A�h���X�� EAX�̒l�Ɠ����l�����邱�ƁB
00416E3E   8B4424 40        MOV EAX,DWORD PTR SS:[ESP+40]        // ����͌����O�̖h��l
00416E42   50               PUSH EAX
00416E43   68 D80D5200      PUSH Nobunaga.00520DD8                   ; ASCII "�h��x : %d ---> %d
�U������ : %d ---> %d
�h�䋒�_ : %d ---> %d"
00416E48   68 D8A55D00      PUSH Nobunaga.005DA5D8                   ; ASCII "  ���q��   500"
00416E4D   E8 25B90E00      CALL Nobunaga.00502777

*/


#include <windows.h>
#include <string>
#include "data_game_struct.h"
#include "data_bushou_struct.h"
#include "output_debug_stream.h"
#include "game_screen.h"
#include "game_process.h"
#include "bushou_albedo.h"


using namespace std;

#pragma unmanaged

extern int iCastleBattleButaiHonmaruAttackBushou;


static int ECXOfCastleBattleButaiDefendHonmaruDamage = 0;
static int EAXOfCastleBattleButaiDefendHonmaruDamage = 0;
void OnSSRExeCastleBattleButaiDefendHonmaruDamageExecute() {
	int* pRemainHeisuPtr = (int*)((BYTE*)(ECXOfCastleBattleButaiDefendHonmaruDamage)+0x8); // �����ɍU�����������|�C���^�������Ă���

	int iBushouID = iCastleBattleButaiHonmaruAttackBushou;

	if (isValidBushouID(iBushouID)) {
		if (getBushou����FromBushouID(iBushouID) == getArubedoSeiMei()) {
			OutputDebugStream("�������A���x�h�U���Ȃ̂Ŏc�蕺����0\n");
			*pRemainHeisuPtr = 0;                            // �����Ŏc�蕺����0�ւƋ߂Â���
			EAXOfCastleBattleButaiDefendHonmaruDamage = 0; // EAX�ɂ��c�蕺�������Ă����B���ꂪ��ʂŕ\������p
		}
	}
}

/*
00416E36   8BCF             MOV ECX,EDI
00416E38   E8 53BCFEFF      CALL Nobunaga.00402A90
00416E3D   50               PUSH EAX                             ���̎���EAX���U�����̌�����̖h��l�BECX+0x8�̃A�h���X�� EAX�̒l�Ɠ����l�����邱�ƁB
00416E3E   8B4424 40        MOV EAX,DWORD PTR SS:[ESP+40]        // ����͌����O�̖h��l
00416E42   50               PUSH EAX
00416E43   68 D80D5200      PUSH Nobunaga.00520DD8                   ; ASCII "�h��x : %d ---> %d
�U������ : %d ---> %d
�h�䋒�_ : %d ---> %d"
00416E48   68 D8A55D00      PUSH Nobunaga.005DA5D8                   ; ASCII "  ���q��   500"
00416E4D   E8 25B90E00      CALL Nobunaga.00502777
*/

int pSSRExeJumpFromToOnSSRExeCastleBattleButaiDefendHonmaruDamage = 0x416E38; // �֐��͂��̃A�h���X����AOnSSRExeCastleBattleButaiDefendHonmaruDamage�ւƃW�����v���Ă���B
int pSSRExeJumpCallFromToOnSSRExeCastleBattleButaiDefendHonmaruDamage = 0x402A90; // ���X������������Call��
int pSSRExeReturnLblFromOnSSRExeCastleBattleButaiDefendHonmaruDamage = 0x416E3D; // �֐����Ō�܂ł����ƁA����TENSHOU.EXE���ɒ��ڃW�����v����

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeCastleBattleButaiDefendHonmaruDamage() {
	// �X�^�b�N�ɂ��߂Ă���
	__asm {
		call pSSRExeJumpCallFromToOnSSRExeCastleBattleButaiDefendHonmaruDamage

		mov ECXOfCastleBattleButaiDefendHonmaruDamage, ecx
		mov EAXOfCastleBattleButaiDefendHonmaruDamage, eax

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeCastleBattleButaiDefendHonmaruDamageExecute();

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

		mov eax, EAXOfCastleBattleButaiDefendHonmaruDamage  // ������̎c�蕺����ύX����Ȃ炱���ŕύX���Ă����B
		jmp pSSRExeReturnLblFromOnSSRExeCastleBattleButaiDefendHonmaruDamage
	}
}
#pragma warning(default: 4733) // ���[�j���O�̗}������������



char cmdOnSSRExeJumpFromCastleBattleButaiDefendHonmaruDamage[6] = "\xE9";
// ���̖��߂�5�o�C�g�A�Ȍ�̊֐��Ő��܂�閽�߂����v�T�o�C�g�Ȃ̂Łc �Ō�P�g��Ȃ�


// �j�[���j�b�N���������p
void WriteAsmJumperOnSSRExeCastleBattleButaiDefendHonmaruDamage() {

	// �܂��A�h���X�𐔎��Ƃ��Ĉ���
	int iAddress = (int)OnSSRExeCastleBattleButaiDefendHonmaruDamage;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeCastleBattleButaiDefendHonmaruDamage + 5);
	// �T�Ƃ����̂́A0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  �̖��߂ɕK�v�ȃo�C�g���B�v����ɂT�o�C�g�����Ǝ��̃j�[���j�b�N���ߌQ�Ɉړ�����̂��B�����Ă�������̍������W�����v����ۂ̖ړI�i�Ƃ��ė��p�����B
	memcpy(cmdOnSSRExeJumpFromCastleBattleButaiDefendHonmaruDamage + 1, &SubAddress, 4); // +1 ��E9�̎�����4�o�C�g�����������邩��B

	// �\�z�����j�[���j�b�N���߂�TENSHOU.EXE�̃������ɏ���������
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeCastleBattleButaiDefendHonmaruDamage), cmdOnSSRExeJumpFromCastleBattleButaiDefendHonmaruDamage, 5, NULL); //5�o�C�g�̂ݏ�������
}

#pragma managed

