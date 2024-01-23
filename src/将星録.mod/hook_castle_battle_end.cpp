/*
0040C782   . E8 99110000    CALL Nobunaga.0040D920   �� �����ď��I���������ʉ߂���悤��
0040C787   . B9 380F5800    MOV ECX,Nobunaga.00580F38
0040C78C   . E8 3F7C0500    CALL Nobunaga.004643D0
0040C791   . 5F             POP EDI
0040C792   . 5E             POP ESI
0040C793   . 5B             POP EBX
0040C794   . C2 0800        RETN 8

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

extern void onCastleBattleEnd();

#pragma unmanaged

int iCastleBattleRemainTurn = -1;
int iLastBattleRemainTurn = -1;
bool isCastleBattleMode = false;
void resetCastleBattleInfo() {
	isCastleBattleMode = false;
	iCastleBattleRemainTurn = -1;
	iLastBattleRemainTurn = -1;
}

void OnSSRExeCastleBattleEndExecute() {
	OutputDebugStream("�������ď��I��(�t�b�N)������\n");
	onCastleBattleEnd();

	resetCastleBattleInfo();
}

/*
0040C782   . E8 99110000    CALL Nobunaga.0040D920   �� �����ď��I���������ʉ߂���悤��
0040C787   . B9 380F5800    MOV ECX,Nobunaga.00580F38
0040C78C   . E8 3F7C0500    CALL Nobunaga.004643D0
0040C791   . 5F             POP EDI
0040C792   . 5E             POP ESI
0040C793   . 5B             POP EBX
0040C794   . C2 0800        RETN 8

*/


int pSSRExeJumpFromToOnSSRExeCastleBattleEnd = 0x40C782; // �֐��͂��̃A�h���X����AOnSSRExeCastleBattleEnd�ւƃW�����v���Ă���B
int pSSRExeJumpCallFromToOnSSRExeCastleBattleEnd = 0x40D920; // ���X������������Call��
int pSSRExeReturnLblFromOnSSRExeCastleBattleEnd = 0x40C787; // �֐����Ō�܂ł����ƁA����TENSHOU.EXE���ɒ��ڃW�����v����

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeCastleBattleEnd() {
	// �X�^�b�N�ɂ��߂Ă���
	__asm {
		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeCastleBattleEndExecute();

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

		call pSSRExeJumpCallFromToOnSSRExeCastleBattleEnd // ���̏���

		jmp pSSRExeReturnLblFromOnSSRExeCastleBattleEnd
	}
}
#pragma warning(default: 4733) // ���[�j���O�̗}������������



char cmdOnSSRExeJumpFromCastleBattleEnd[6] = "\xE9";
// ���̖��߂�5�o�C�g�A�Ȍ�̊֐��Ő��܂�閽�߂����v�T�o�C�g�Ȃ̂Łc �Ō�P�g��Ȃ�


// �j�[���j�b�N���������p
void WriteAsmJumperOnSSRExeCastleBattleEnd() {

	// �܂��A�h���X�𐔎��Ƃ��Ĉ���
	int iAddress = (int)OnSSRExeCastleBattleEnd;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeCastleBattleEnd + 5);
	// �T�Ƃ����̂́A0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  �̖��߂ɕK�v�ȃo�C�g���B�v����ɂT�o�C�g�����Ǝ��̃j�[���j�b�N���ߌQ�Ɉړ�����̂��B�����Ă�������̍������W�����v����ۂ̖ړI�i�Ƃ��ė��p�����B
	memcpy(cmdOnSSRExeJumpFromCastleBattleEnd + 1, &SubAddress, 4); // +1 ��E9�̎�����4�o�C�g�����������邩��B

	// �\�z�����j�[���j�b�N���߂�TENSHOU.EXE�̃������ɏ���������
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeCastleBattleEnd), cmdOnSSRExeJumpFromCastleBattleEnd, 5, NULL); //5�o�C�g�̂ݏ�������
}

#pragma managed
