/*
0047C360   85C9             TEST ECX,ECX                     ECX���ƕ���ł̊Y���ƕ�ւ̃|�C���^
0047C362  ^74 90            JE SHORT Nobunaga.0047C2F4
0047C364   833D 88535800 00 CMP DWORD PTR DS:[585388],0
0047C36B   75 06            JNZ SHORT Nobunaga.0047C373
0047C36D   8A01             MOV AL,BYTE PTR DS:[ECX]
0047C36F   84C0             TEST AL,AL

*/


#include <windows.h>
#include <string>
#include "data_game_struct.h"
#include "output_debug_stream.h"
#include "data_kahou_struct.h"
#include "game_process.h"


using namespace std;

#pragma unmanaged

int iKahouIDOfLastShowKahouID = -1;   // ���̏u�ԕ\�����悤�Ƃ��Ă���ƕ��iKahouID
static int ECXOfLastShowKahouID = -1;
void OnSSRExeLastShowKahouIDExecute() {
	iKahouIDOfLastShowKahouID = -1;

	int iKahouID = getKahouIDFromKahouPtr((int*)ECXOfLastShowKahouID);
	if (isValidKahouID(iKahouID)) {
		iKahouIDOfLastShowKahouID = iKahouID;
		OutputDebugStream("LastShowKahouID");
	}
}

/*
0047C360   85C9             TEST ECX,ECX                     ECX���ƕ���ł̊Y���ƕ�ւ̃|�C���^
0047C362  ^74 90            JE SHORT Nobunaga.0047C2F4
0047C364   833D 88535800 00 CMP DWORD PTR DS:[585388],0
0047C36B   75 06            JNZ SHORT Nobunaga.0047C373
0047C36D   8A01             MOV AL,BYTE PTR DS:[ECX]
0047C36F   84C0             TEST AL,AL
*/
int pSSRExeJumpFromToOnSSRExeLastShowKahouID = 0x47C364; // �֐��͂��̃A�h���X����AOnSSRExeLastShowKahouID�ւƃW�����v���Ă���B
int pSSRExeReturnLblFromOnSSRExeLastShowKahouID = 0x47C36B; // �֐����Ō�܂ł����ƁA���̎��sexe���ɒ��ڃW�����v����

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeLastShowKahouID() {
	// �X�^�b�N�ɂ��߂Ă���
	__asm {
		mov ECXOfLastShowKahouID, ecx
		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi

	}

	OnSSRExeLastShowKahouIDExecute();

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

		CMP DWORD PTR DS : [0x585388],0

		jmp pSSRExeReturnLblFromOnSSRExeLastShowKahouID
	}
}
#pragma warning(default: 4733) // ���[�j���O�̗}������������



char cmdOnSSRExeJumpFromLastShowKahouID[6] = "\xE9";
// ���̖��߂�5�o�C�g�A�Ȍ�̊֐��Ő��܂�閽�߂����v�T�o�C�g�Ȃ̂Łc �Ō�P�g��Ȃ�


// �j�[���j�b�N���������p
void WriteAsmJumperOnSSRExeLastShowKahouID() {

	// �܂��A�h���X�𐔎��Ƃ��Ĉ���
	int iAddress = (int)OnSSRExeLastShowKahouID;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeLastShowKahouID + 5);
	// �T�Ƃ����̂́A0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  �̖��߂ɕK�v�ȃo�C�g���B�v����ɂT�o�C�g�����Ǝ��̃j�[���j�b�N���ߌQ�Ɉړ�����̂��B�����Ă�������̍������W�����v����ۂ̖ړI�i�Ƃ��ė��p�����B
	memcpy(cmdOnSSRExeJumpFromLastShowKahouID + 1, &SubAddress, 4); // +1 ��E9�̎�����4�o�C�g�����������邩��B

	// �\�z�����j�[���j�b�N���߂����sexe�̃������ɏ���������
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeLastShowKahouID), cmdOnSSRExeJumpFromLastShowKahouID, 5, NULL); //5�o�C�g�̂ݏ�������
}

#pragma managed
