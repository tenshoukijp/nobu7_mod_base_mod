/*
004348CE  |. 85C0           TEST EAX,EAX
004348D0  |. 8BCE           MOV ECX,ESI
004348D2  |. 74 07          JE SHORT Nobunaga.004348DB
004348D4  |. E8 37F4FFFF    CALL Nobunaga.00433D10         �� �v���C���[�^�[���̎��ɂ��������s�����
004348D9  |. EB 0F          JMP SHORT Nobunaga.004348EA
004348DB  |> E8 00FCFFFF    CALL Nobunaga.004344E0
004348E0  |. B9 80E95700    MOV ECX,Nobunaga.0057E980

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
#include "on_event.h"


using namespace std;

#pragma unmanaged

extern void onStrategyGameStart();

static int iTurnPlayerDaimyoPointerOfStrategy = -1;

extern BOOL isYasenBattle;
void OnSSRExeMainStrategyPlayerTurnExecute() {
	OutputDebugStream("���������v���C���[�^�[��(�t�b�N)�ɓ��B���܂���\n");
	int iDaimyoID = getDaimyoIDFromDaimyoPtr((int*)iTurnPlayerDaimyoPointerOfStrategy);
	if (isValidDaimyoID(iDaimyoID)) {
		int iBushouID = getBushouIDFromDaimyoID(iDaimyoID);

		OutputDebugStream(getBushou����FromBushouID(iBushouID) + "�̃v���C���[�^�[�����O�ł�\n");

		isYasenBattle = FALSE;
		onStrategyPlayerDaimyoTurn(iDaimyoID);

	}
}


/*
004348CE  |. 85C0           TEST EAX,EAX
004348D0  |. 8BCE           MOV ECX,ESI					   �� ESI���喼���̊Y���喼�|�C���^�B
004348D2  |. 74 07          JE SHORT Nobunaga.004348DB
004348D4  |. E8 37F4FFFF    CALL Nobunaga.00433D10         �� �v���C���[�^�[���̎��ɂ��������s�����
004348D9  |. EB 0F          JMP SHORT Nobunaga.004348EA
004348DB  |> E8 00FCFFFF    CALL Nobunaga.004344E0
004348E0  |. B9 80E95700    MOV ECX,Nobunaga.0057E980

*/

int pSSRExeJumpFromToOnSSRExeMainStrategyPlayerTurn = 0x4348D4; // �֐��͂��̃A�h���X����AOnSSRExeMainStrategyPlayerTurn�ւƃW�����v���Ă���B
int pSSRExeJumpCallFromToOnSSRExeMainStrategyPlayerTurn = 0x433D10; // ���X������������Call��
int pSSRExeReturnLblFromOnSSRExeMainStrategyPlayerTurn = 0x4348D9; // �֐����Ō�܂ł����ƁA����TENSHOU.EXE���ɒ��ڃW�����v����

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeMainStrategyPlayerTurn() {
	// �X�^�b�N�ɂ��߂Ă���
	__asm {

		mov iTurnPlayerDaimyoPointerOfStrategy, ESI

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeMainStrategyPlayerTurnExecute();

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

		call pSSRExeJumpCallFromToOnSSRExeMainStrategyPlayerTurn // ���̏���

		jmp pSSRExeReturnLblFromOnSSRExeMainStrategyPlayerTurn
	}
}
#pragma warning(default: 4733) // ���[�j���O�̗}������������



char cmdOnSSRExeJumpFromMainStrategyPlayerTurn[6] = "\xE9";
// ���̖��߂�5�o�C�g�A�Ȍ�̊֐��Ő��܂�閽�߂����v�T�o�C�g�Ȃ̂Łc �Ō�P�g��Ȃ�


// �j�[���j�b�N���������p
void WriteAsmJumperOnSSRExeMainStrategyPlayerTurn() {

	// �܂��A�h���X�𐔎��Ƃ��Ĉ���
	int iAddress = (int)OnSSRExeMainStrategyPlayerTurn;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeMainStrategyPlayerTurn + 5);
	// �T�Ƃ����̂́A0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  �̖��߂ɕK�v�ȃo�C�g���B�v����ɂT�o�C�g�����Ǝ��̃j�[���j�b�N���ߌQ�Ɉړ�����̂��B�����Ă�������̍������W�����v����ۂ̖ړI�i�Ƃ��ė��p�����B
	memcpy(cmdOnSSRExeJumpFromMainStrategyPlayerTurn + 1, &SubAddress, 4); // +1 ��E9�̎�����4�o�C�g�����������邩��B

	// �\�z�����j�[���j�b�N���߂�TENSHOU.EXE�̃������ɏ���������
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeMainStrategyPlayerTurn), cmdOnSSRExeJumpFromMainStrategyPlayerTurn, 5, NULL); //5�o�C�g�̂ݏ�������
}

#pragma managed
