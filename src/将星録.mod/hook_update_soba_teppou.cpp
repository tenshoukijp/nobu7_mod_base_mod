/*
004C47CA   50               PUSH EAX
004C47CB   51               PUSH ECX
004C47CC   E8 DFBCF7FF      CALL Nobunaga.004404B0
004C47D1   83C4 08          ADD ESP,8
004C47D4   8946 42          MOV DWORD PTR DS:[ESI+42],EAX
004C47D7   5E               POP ESI
004C47D8   C2 0400          RETN 4

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

static int iUpdateSobaTeppouEAX = -1;
void OnSSRExeUpdateSobaTeppouExecute() {
	OutputDebugStream("���������S�C���ꂪ�X�V����܂���!!!:%d\n", iUpdateSobaTeppouEAX);
	onUpdateSobaTeppou(iUpdateSobaTeppouEAX);

	// ������ �����u�Ђƌ��Ɉ�x�������鏈���v�������̂ɓK���Ă���B
	// JavaScript�ȂǂŁu���ꂪ�ύX�ɂȂ������i�����ύX�ɂȂ������j�v�Ƃ�����������ǉ�����̂ɓK���Ă���B
}


/*
004C47CA   50               PUSH EAX
004C47CB   51               PUSH ECX
004C47CC   E8 DFBCF7FF      CALL Nobunaga.004404B0
004C47D1   83C4 08          ADD ESP,8
004C47D4   8946 42          MOV DWORD PTR DS:[ESI+42],EAX
004C47D7   5E               POP ESI
004C47D8   C2 0400          RETN 4

*/



int pSSRExeJumpFromToOnSSRExeUpdateSobaTeppou = 0x4C47CC; // �֐��͂��̃A�h���X����AOnSSRExeUpdateSobaTeppou�ւƃW�����v���Ă���B
int pSSRExeJumpCallFromToOnSSRExeUpdateSobaTeppou = 0x4404B0; // ���X������������Call��
int pSSRExeReturnLblFromOnSSRExeUpdateSobaTeppou = 0x4C47D1; // �֐����Ō�܂ł����ƁA����TENSHOU.EXE���ɒ��ڃW�����v����

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeUpdateSobaTeppou() {
	// �X�^�b�N�ɂ��߂Ă���
	__asm {

		call pSSRExeJumpCallFromToOnSSRExeUpdateSobaTeppou // ���̏���

		mov iUpdateSobaTeppouEAX, EAX

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeUpdateSobaTeppouExecute();

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

		jmp pSSRExeReturnLblFromOnSSRExeUpdateSobaTeppou
	}
}
#pragma warning(default: 4733) // ���[�j���O�̗}������������



char cmdOnSSRExeJumpFromUpdateSobaTeppou[6] = "\xE9";
// ���̖��߂�5�o�C�g�A�Ȍ�̊֐��Ő��܂�閽�߂����v�T�o�C�g�Ȃ̂Łc �Ō�P�g��Ȃ�


// �j�[���j�b�N���������p
void WriteAsmJumperOnSSRExeUpdateSobaTeppou() {

	// �܂��A�h���X�𐔎��Ƃ��Ĉ���
	int iAddress = (int)OnSSRExeUpdateSobaTeppou;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeUpdateSobaTeppou + 5);
	// �T�Ƃ����̂́A0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  �̖��߂ɕK�v�ȃo�C�g���B�v����ɂT�o�C�g�����Ǝ��̃j�[���j�b�N���ߌQ�Ɉړ�����̂��B�����Ă�������̍������W�����v����ۂ̖ړI�i�Ƃ��ė��p�����B
	memcpy(cmdOnSSRExeJumpFromUpdateSobaTeppou + 1, &SubAddress, 4); // +1 ��E9�̎�����4�o�C�g�����������邩��B

	// �\�z�����j�[���j�b�N���߂�TENSHOU.EXE�̃������ɏ���������
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeUpdateSobaTeppou), cmdOnSSRExeJumpFromUpdateSobaTeppou, 5, NULL); //5�o�C�g�̂ݏ�������
}

#pragma managed
