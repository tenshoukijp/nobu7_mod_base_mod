/*
004C4EE1   57               PUSH EDI
004C4EE2   E8 C9B5F7FF      CALL Nobunaga.004404B0
004C4EE7   83C4 08          ADD ESP,8
004C4EEA   5F               POP EDI
004C4EEB   8946 1E          MOV DWORD PTR DS:[ESI+1E],EAX // �����������Ă�̂������ȁH
004C4EEE   5E               POP ESI

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

static int iUpdateMonthEAX = -1;
void OnSSRExeUpdateMonthExecute() {
	OutputDebugStream("�������������X�V����܂���!!!:%d\n", iUpdateMonthEAX);
	onUpdateMonth(iUpdateMonthEAX);
}


/*
004C4EE1   57               PUSH EDI
004C4EE2   E8 C9B5F7FF      CALL Nobunaga.004404B0
004C4EE7   83C4 08          ADD ESP,8
004C4EEA   5F               POP EDI
004C4EEB   8946 1E          MOV DWORD PTR DS:[ESI+1E],EAX // �����������Ă�̂������ȁH
004C4EEE   5E               POP ESI
*/



int pSSRExeJumpFromToOnSSRExeUpdateMonth = 0x4C4EE2; // �֐��͂��̃A�h���X����AOnSSRExeUpdateMonth�ւƃW�����v���Ă���B
int pSSRExeJumpCallFromToOnSSRExeUpdateMonth = 0x4404B0; // ���X������������Call��
int pSSRExeReturnLblFromOnSSRExeUpdateMonth = 0x4C4EE7; // �֐����Ō�܂ł����ƁA����TENSHOU.EXE���ɒ��ڃW�����v����

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeUpdateMonth() {
	// �X�^�b�N�ɂ��߂Ă���
	__asm {

		call pSSRExeJumpCallFromToOnSSRExeUpdateMonth // ���̏���

		mov iUpdateMonthEAX, EAX

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeUpdateMonthExecute();

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

		jmp pSSRExeReturnLblFromOnSSRExeUpdateMonth
	}
}
#pragma warning(default: 4733) // ���[�j���O�̗}������������



char cmdOnSSRExeJumpFromUpdateMonth[6] = "\xE9";
// ���̖��߂�5�o�C�g�A�Ȍ�̊֐��Ő��܂�閽�߂����v�T�o�C�g�Ȃ̂Łc �Ō�P�g��Ȃ�


// �j�[���j�b�N���������p
void WriteAsmJumperOnSSRExeUpdateMonth() {

	// �܂��A�h���X�𐔎��Ƃ��Ĉ���
	int iAddress = (int)OnSSRExeUpdateMonth;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeUpdateMonth + 5);
	// �T�Ƃ����̂́A0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  �̖��߂ɕK�v�ȃo�C�g���B�v����ɂT�o�C�g�����Ǝ��̃j�[���j�b�N���ߌQ�Ɉړ�����̂��B�����Ă�������̍������W�����v����ۂ̖ړI�i�Ƃ��ė��p�����B
	memcpy(cmdOnSSRExeJumpFromUpdateMonth + 1, &SubAddress, 4); // +1 ��E9�̎�����4�o�C�g�����������邩��B

	// �\�z�����j�[���j�b�N���߂�TENSHOU.EXE�̃������ɏ���������
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeUpdateMonth), cmdOnSSRExeJumpFromUpdateMonth, 5, NULL); //5�o�C�g�̂ݏ�������
}

#pragma managed
