/*
004C505C   50               PUSH EAX
004C505D   E8 4EB4F7FF      CALL Nobunaga.004404B0
004C5062   8946 32          MOV DWORD PTR DS:[ESI+32],EAX   // ���Ƃ̒l�i��������
004C5065   0FB783 9C000000  MOVZX EAX,WORD PTR DS:[EBX+9C]
004C506C   8B56 3E          MOV EDX,DWORD PTR DS:[ESI+3E]
004C506F   52               PUSH EDX

004C5070   50               PUSH EAX
004C5071   E8 3AB4F7FF      CALL Nobunaga.004404B0
004C5076   8946 3A          MOV DWORD PTR DS:[ESI+3A],EAX   // �R�n�̒l�i��������
004C5079   0FB783 9E000000  MOVZX EAX,WORD PTR DS:[EBX+9E]
004C5080   8B4E 46          MOV ECX,DWORD PTR DS:[ESI+46]

004C5083   51               PUSH ECX
004C5084   50               PUSH EAX
004C5085   E8 26B4F7FF      CALL Nobunaga.004404B0
004C508A   8D93 B0000000    LEA EDX,DWORD PTR DS:[EBX+B0]
004C5090   83C4 18          ADD ESP,18
004C5093   8946 42          MOV DWORD PTR DS:[ESI+42],EAX   // �S�C�̒l�i��������
004C5096   33FF             XOR EDI,EDI


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

static int iWriteSobaTeppouEAX = -1;
void OnSSRExeWriteSobaTeppouExecute() {
	OutputDebugStream("���������S�C�����������݂���܂���!!!:%d\n", iWriteSobaTeppouEAX);
	onWriteSobaTeppou(iWriteSobaTeppouEAX);
}


/*
004C5083   51               PUSH ECX
004C5084   50               PUSH EAX
004C5085   E8 26B4F7FF      CALL Nobunaga.004404B0
004C508A   8D93 B0000000    LEA EDX,DWORD PTR DS:[EBX+B0]
004C5090   83C4 18          ADD ESP,18
004C5093   8946 42          MOV DWORD PTR DS:[ESI+42],EAX   // �S�C�̒l�i��������
004C5096   33FF             XOR EDI,EDI
*/



int pSSRExeJumpFromToOnSSRExeWriteSobaTeppou = 0x4C5085; // �֐��͂��̃A�h���X����AOnSSRExeWriteSobaTeppou�ւƃW�����v���Ă���B
int pSSRExeJumpCallFromToOnSSRExeWriteSobaTeppou = 0x4404B0; // ���X������������Call��
int pSSRExeReturnLblFromOnSSRExeWriteSobaTeppou = 0x4C508A; // �֐����Ō�܂ł����ƁA����TENSHOU.EXE���ɒ��ڃW�����v����

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeWriteSobaTeppou() {
	// �X�^�b�N�ɂ��߂Ă���
	__asm {

		call pSSRExeJumpCallFromToOnSSRExeWriteSobaTeppou // ���̏���

		mov iWriteSobaTeppouEAX, EAX

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeWriteSobaTeppouExecute();

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

		jmp pSSRExeReturnLblFromOnSSRExeWriteSobaTeppou
	}
}
#pragma warning(default: 4733) // ���[�j���O�̗}������������



char cmdOnSSRExeJumpFromWriteSobaTeppou[6] = "\xE9";
// ���̖��߂�5�o�C�g�A�Ȍ�̊֐��Ő��܂�閽�߂����v�T�o�C�g�Ȃ̂Łc �Ō�P�g��Ȃ�


// �j�[���j�b�N���������p
void WriteAsmJumperOnSSRExeWriteSobaTeppou() {

	// �܂��A�h���X�𐔎��Ƃ��Ĉ���
	int iAddress = (int)OnSSRExeWriteSobaTeppou;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeWriteSobaTeppou + 5);
	// �T�Ƃ����̂́A0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  �̖��߂ɕK�v�ȃo�C�g���B�v����ɂT�o�C�g�����Ǝ��̃j�[���j�b�N���ߌQ�Ɉړ�����̂��B�����Ă�������̍������W�����v����ۂ̖ړI�i�Ƃ��ė��p�����B
	memcpy(cmdOnSSRExeJumpFromWriteSobaTeppou + 1, &SubAddress, 4); // +1 ��E9�̎�����4�o�C�g�����������邩��B

	// �\�z�����j�[���j�b�N���߂�TENSHOU.EXE�̃������ɏ���������
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeWriteSobaTeppou), cmdOnSSRExeJumpFromWriteSobaTeppou, 5, NULL); //5�o�C�g�̂ݏ�������
}

#pragma managed
