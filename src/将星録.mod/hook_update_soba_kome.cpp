/*
004C455A   50               PUSH EAX
004C455B   51               PUSH ECX
004C455C   E8 4FBFF7FF      CALL Nobunaga.004404B0
004C4561   83C4 08          ADD ESP,8
004C4564   8946 32          MOV DWORD PTR DS:[ESI+32],EAX  // ���ꂪ�X�V���ꂽ��
004C4567   5E               POP ESI

*/





#include <windows.h>
#include <string>
#include <map>
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


static int iUpdateSobaKomeEAX = -1;
void OnSSRExeUpdateSobaKomeExecute() {
	OutputDebugStream("���������đ��ꂪ�X�V����܂���!!!:%d\n", iUpdateSobaKomeEAX);
	onUpdateSobaKome(iUpdateSobaKomeEAX);

	resetAlbedoKoudouCounter();
}


/*
004C455A   50               PUSH EAX
004C455B   51               PUSH ECX
004C455C   E8 4FBFF7FF      CALL Nobunaga.004404B0
004C4561   83C4 08          ADD ESP,8
004C4564   8946 32          MOV DWORD PTR DS:[ESI+32],EAX  // ���ꂪ�X�V���ꂽ��
004C4567   5E               POP ESI
*/



int pSSRExeJumpFromToOnSSRExeUpdateSobaKome = 0x4C455C; // �֐��͂��̃A�h���X����AOnSSRExeUpdateSobaKome�ւƃW�����v���Ă���B
int pSSRExeJumpCallFromToOnSSRExeUpdateSobaKome = 0x4404B0; // ���X������������Call��
int pSSRExeReturnLblFromOnSSRExeUpdateSobaKome = 0x4C4561; // �֐����Ō�܂ł����ƁA����TENSHOU.EXE���ɒ��ڃW�����v����

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeUpdateSobaKome() {
	// �X�^�b�N�ɂ��߂Ă���
	__asm {

		call pSSRExeJumpCallFromToOnSSRExeUpdateSobaKome // ���̏���

		mov iUpdateSobaKomeEAX, EAX

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeUpdateSobaKomeExecute();

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

		jmp pSSRExeReturnLblFromOnSSRExeUpdateSobaKome
	}
}
#pragma warning(default: 4733) // ���[�j���O�̗}������������



char cmdOnSSRExeJumpFromUpdateSobaKome[6] = "\xE9";
// ���̖��߂�5�o�C�g�A�Ȍ�̊֐��Ő��܂�閽�߂����v�T�o�C�g�Ȃ̂Łc �Ō�P�g��Ȃ�


// �j�[���j�b�N���������p
void WriteAsmJumperOnSSRExeUpdateSobaKome() {

	// �܂��A�h���X�𐔎��Ƃ��Ĉ���
	int iAddress = (int)OnSSRExeUpdateSobaKome;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeUpdateSobaKome + 5);
	// �T�Ƃ����̂́A0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  �̖��߂ɕK�v�ȃo�C�g���B�v����ɂT�o�C�g�����Ǝ��̃j�[���j�b�N���ߌQ�Ɉړ�����̂��B�����Ă�������̍������W�����v����ۂ̖ړI�i�Ƃ��ė��p�����B
	memcpy(cmdOnSSRExeJumpFromUpdateSobaKome + 1, &SubAddress, 4); // +1 ��E9�̎�����4�o�C�g�����������邩��B

	// �\�z�����j�[���j�b�N���߂�TENSHOU.EXE�̃������ɏ���������
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeUpdateSobaKome), cmdOnSSRExeJumpFromUpdateSobaKome, 5, NULL); //5�o�C�g�̂ݏ�������
}

#pragma managed
