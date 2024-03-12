/*
���̂�����ɍU���������A�U�������̂ǂꂩ�̏�񂪂���͂������킩��Ȃ��B
00415D37   8D4424 24        LEA EAX,DWORD PTR SS:[ESP+24]
00415D3B   50               PUSH EAX
00415D3C   8BCE             MOV ECX,ESI
00415D3E   E8 6DCCFEFF      CALL Nobunaga.004029B0
00415D43   50               PUSH EAX
00415D44   55               PUSH EBP
00415D45   E8 51CD0E00      CALL Nobunaga.00502A9B
00415D4A   83C4 0C          ADD ESP,0C
00415D4D   8BCF             MOV ECX,EDI
00415D4F   E8 FCFBFFFF      CALL Nobunaga.00415950
00415D54   8B4C24 24        MOV ECX,DWORD PTR SS:[ESP+24]
00415D58   51               PUSH ECX
00415D59   8BCE             MOV ECX,ESI
00415D5B   E8 E0D8FEFF      CALL Nobunaga.00403640
00415D60   8BCE             MOV ECX,ESI
*/

/*
00415D60   8BCE             MOV ECX,ESI
00415D62   E8 99D8FEFF      CALL Nobunaga.00403600
00415D67   50               PUSH EAX                                 ���̎���EAX���U�����̌�����̖h��l�BECX+0xA�̃A�h���X�� EAX�̒l�Ɠ����l�����邱�ƁB
00415D68   53               PUSH EBX
00415D69   68 A80D5200      PUSH Nobunaga.00520DA8                   ; ASCII "�h��x : %d ---> %d"
00415D6E   68 D8A55D00      PUSH Nobunaga.005DA5D8                   ; ASCII "242"

*/


#include <windows.h>
#include <string>
#include "data_game_struct.h"
#include "data_bushou_struct.h"
#include "output_debug_stream.h"
#include "game_process.h"
#include "bushou_albedo.h"

using namespace std;

#pragma unmanaged

extern int iLastBushouIDOfBattleTaihouDefendDoorBushou; // �Ō�ɑ�C�Ńh�A�U����������


static int ECXOfCastleBattleTaihouDefendDoorDamage = 0;
static int EAXOfCastleBattleTaihouDefendDoorDamage = 0;
void OnSSRExeCastleBattleTaihouDefendDoorDamageExecute() {
	int* pRemainDoorPtr = (int*)((BYTE*)(ECXOfCastleBattleTaihouDefendDoorDamage)+0xA); // �����Ƀh�A�̖h��l�ւ̃|�C���^�������Ă���

	int iBushouID = iLastBushouIDOfBattleTaihouDefendDoorBushou;
	if (isValidBushouID(iBushouID)) {
		OutputDebugStream("�h�A�̎c��ϋv�x%d\n", *pRemainDoorPtr);
		OutputDebugStream("�U����" + getBushou����FromBushouID(iBushouID) + "\n");


		if (getBushou����FromBushouID(iBushouID) == getArubedoSeiMei()) {
			OutputDebugStream("�A���x�h�ɂ��h�A�̎c��ϋv�x�̏㏑��\n");
			*pRemainDoorPtr = 0;                            // �����Ŏc��h���0�ւƋ߂Â���
			EAXOfCastleBattleTaihouDefendDoorDamage = 0; // EAX�ɂ��c��h������Ă����B���ꂪ��ʂŕ\������p
		}

		// EAX �� *pReimainDoorPtr ���㏑������Ȃ炱���ŁB
	}

}

/*
00415D60   8BCE             MOV ECX,ESI
00415D62   E8 99D8FEFF      CALL Nobunaga.00403600
00415D67   50               PUSH EAX                                 ���̎���EAX���U�����̌�����̖h��l�BECX+0xA�̃A�h���X�� EAX�̒l�Ɠ����l�����邱�ƁB
00415D68   53               PUSH EBX
00415D69   68 A80D5200      PUSH Nobunaga.00520DA8                   ; ASCII "�h��x : %d ---> %d"
00415D6E   68 D8A55D00      PUSH Nobunaga.005DA5D8                   ; ASCII "242"
*/

int pSSRExeJumpFromToOnSSRExeCastleBattleTaihouDefendDoorDamage = 0x415D62; // �֐��͂��̃A�h���X����AOnSSRExeCastleBattleTaihouDefendDoorDamage�ւƃW�����v���Ă���B
int pSSRExeJumpCallFromToOnSSRExeCastleBattleTaihouDefendDoorDamage = 0x403600; // ���X������������Call��
int pSSRExeReturnLblFromOnSSRExeCastleBattleTaihouDefendDoorDamage = 0x415D67; // �֐����Ō�܂ł����ƁA����TENSHOU.EXE���ɒ��ڃW�����v����

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeCastleBattleTaihouDefendDoorDamage() {
	// �X�^�b�N�ɂ��߂Ă���
	__asm {

		mov ECXOfCastleBattleTaihouDefendDoorDamage, ecx

		call pSSRExeJumpCallFromToOnSSRExeCastleBattleTaihouDefendDoorDamage

		mov EAXOfCastleBattleTaihouDefendDoorDamage, eax

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeCastleBattleTaihouDefendDoorDamageExecute();

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

		mov eax, EAXOfCastleBattleTaihouDefendDoorDamage  // ������̎c��h���ύX����Ȃ炱���ŕύX���Ă����B
		jmp pSSRExeReturnLblFromOnSSRExeCastleBattleTaihouDefendDoorDamage
	}
}
#pragma warning(default: 4733) // ���[�j���O�̗}������������



char cmdOnSSRExeJumpFromCastleBattleTaihouDefendDoorDamage[6] = "\xE9";
// ���̖��߂�5�o�C�g�A�Ȍ�̊֐��Ő��܂�閽�߂����v�T�o�C�g�Ȃ̂Łc �Ō�P�g��Ȃ�


// �j�[���j�b�N���������p
void WriteAsmJumperOnSSRExeCastleBattleTaihouDefendDoorDamage() {

	// �܂��A�h���X�𐔎��Ƃ��Ĉ���
	int iAddress = (int)OnSSRExeCastleBattleTaihouDefendDoorDamage;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeCastleBattleTaihouDefendDoorDamage + 5);
	// �T�Ƃ����̂́A0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  �̖��߂ɕK�v�ȃo�C�g���B�v����ɂT�o�C�g�����Ǝ��̃j�[���j�b�N���ߌQ�Ɉړ�����̂��B�����Ă�������̍������W�����v����ۂ̖ړI�i�Ƃ��ė��p�����B
	memcpy(cmdOnSSRExeJumpFromCastleBattleTaihouDefendDoorDamage + 1, &SubAddress, 4); // +1 ��E9�̎�����4�o�C�g�����������邩��B

	// �\�z�����j�[���j�b�N���߂�TENSHOU.EXE�̃������ɏ���������
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeCastleBattleTaihouDefendDoorDamage), cmdOnSSRExeJumpFromCastleBattleTaihouDefendDoorDamage, 5, NULL); //5�o�C�g�̂ݏ�������
}

#pragma managed
