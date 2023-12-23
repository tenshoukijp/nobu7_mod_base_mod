/*
004C4F1B   50               PUSH EAX
004C4F1C   E8 8FB5F7FF      CALL Nobunaga.004404B0
004C4F21   8946 16          MOV DWORD PTR DS:[ESI+16],EAX   // ���݂̔N�������Ă��邩�H
004C4F24   0FBF43 02        MOVSX EAX,WORD PTR DS:[EBX+2]
004C4F28   8B56 22          MOV EDX,DWORD PTR DS:[ESI+22]
004C4F2B   52               PUSH EDX
004C4F2C   50               PUSH EAX
004C4F2D   E8 7EB5F7FF      CALL Nobunaga.004404B0
004C4F32   8946 1E          MOV DWORD PTR DS:[ESI+1E],EAX  // ���݂̌��������Ă��邩�H
004C4F35   0FBF43 04        MOVSX EAX,WORD PTR DS:[EBX+4]
004C4F39   33C9             XOR ECX,ECX
004C4F3B   83C4 1C          ADD ESP,1C
004C4F3E   85C0             TEST EAX,EAX
004C4F40   0F9CC1           SETL CL
004C4F43   83E9 01          SUB ECX,1
004C4F46   23C8             AND ECX,EAX
004C4F48   890E             MOV DWORD PTR DS:[ESI],ECX
004C4F4A   0FB743 06        MOVZX EAX,WORD PTR DS:[EBX+6]
004C4F4E   66:85C0          TEST AX,AX
004C4F51   7E 27            JLE SHORT Nobunaga.004C4F7A
004C4F53   66:3D 4000       CMP AX,40
004C4F57   7F 21            JG SHORT Nobunaga.004C4F7A

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

static int iWriteYearEAX = -1;
void OnSSRExeWriteYearExecute() {
	OutputDebugStream("���������N�����������݂���܂���!!!:%d\n", iWriteYearEAX);
	onWriteYear();
}


/*
004C4F1B   50               PUSH EAX
004C4F1C   E8 8FB5F7FF      CALL Nobunaga.004404B0
004C4F21   8946 16          MOV DWORD PTR DS:[ESI+16],EAX   // ���݂̔N�������Ă��邩�H
004C4F24   0FBF43 02        MOVSX EAX,WORD PTR DS:[EBX+2]
*/



int pSSRExeJumpFromToOnSSRExeWriteYear = 0x4C4F1C; // �֐��͂��̃A�h���X����AOnSSRExeWriteYear�ւƃW�����v���Ă���B
int pSSRExeJumpCallFromToOnSSRExeWriteYear = 0x4404B0; // ���X������������Call��
int pSSRExeReturnLblFromOnSSRExeWriteYear = 0x4C4F21; // �֐����Ō�܂ł����ƁA����TENSHOU.EXE���ɒ��ڃW�����v����

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeWriteYear() {
	// �X�^�b�N�ɂ��߂Ă���
	__asm {

		call pSSRExeJumpCallFromToOnSSRExeWriteYear // ���̏���

		mov iWriteYearEAX, EAX

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeWriteYearExecute();

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

		jmp pSSRExeReturnLblFromOnSSRExeWriteYear
	}
}
#pragma warning(default: 4733) // ���[�j���O�̗}������������



char cmdOnSSRExeJumpFromWriteYear[6] = "\xE9";
// ���̖��߂�5�o�C�g�A�Ȍ�̊֐��Ő��܂�閽�߂����v�T�o�C�g�Ȃ̂Łc �Ō�P�g��Ȃ�


// �j�[���j�b�N���������p
void WriteAsmJumperOnSSRExeWriteYear() {

	// �܂��A�h���X�𐔎��Ƃ��Ĉ���
	int iAddress = (int)OnSSRExeWriteYear;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeWriteYear + 5);
	// �T�Ƃ����̂́A0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  �̖��߂ɕK�v�ȃo�C�g���B�v����ɂT�o�C�g�����Ǝ��̃j�[���j�b�N���ߌQ�Ɉړ�����̂��B�����Ă�������̍������W�����v����ۂ̖ړI�i�Ƃ��ė��p�����B
	memcpy(cmdOnSSRExeJumpFromWriteYear + 1, &SubAddress, 4); // +1 ��E9�̎�����4�o�C�g�����������邩��B

	// �\�z�����j�[���j�b�N���߂�TENSHOU.EXE�̃������ɏ���������
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeWriteYear), cmdOnSSRExeJumpFromWriteYear, 5, NULL); //5�o�C�g�̂ݏ�������
}

#pragma managed
