/*
0A7E0C74   FFD2             CALL NEAR EDX
0A7E0C76   C646 08 01       MOV BYTE PTR DS:[ESI+8],1
0A7E0C7A   833D 4840D473 00 CMP DWORD PTR DS:[73D44048],0

ReadFile�̊֐�
0050347E   FF15 B4015200    CALL NEAR DWORD PTR DS:[<&KERNEL32.ReadFile>]                ; �����^_m.7C07182B
00503484   8B45 FC          MOV EAX,DWORD PTR SS:[EBP-4]
00503487   8BE5             MOV ESP,EBP
00503489   5D               POP EBP

ReadFile�̌Ăяo����
00459EB4   51               PUSH ECX
00459EB5   E8 AF950A00      CALL Nobunaga.00503469
00459EBA   83C4 18          ADD ESP,18
00459EBD   837E 14 00       CMP DWORD PTR DS:[ESI+14],0

459EB4��ʉ߂��鏈���̌Ăяo����
0045A566   52               PUSH EDX
0045A567   50               PUSH EAX
0045A568   E8 F3F8FFFF      CALL Nobunaga.00459E60
0045A56D   C2 0800          RETN 8

0045A540   8379 28 00       CMP DWORD PTR DS:[ECX+28],0
0045A544   75 05            JNZ SHORT Nobunaga.0045A54B
0045A546   33C0             XOR EAX,EAX
0045A548   C2 0800          RETN 8
0045A54B   8B4424 04        MOV EAX,DWORD PTR SS:[ESP+4]
0045A54F   3B41 20          CMP EAX,DWORD PTR DS:[ECX+20]
0045A552  ^73 90            JNB SHORT Nobunaga.0045A4E4
0045A554   8B51 24          MOV EDX,DWORD PTR DS:[ECX+24]

���̂R���摜�̃L���b�V���Ɋւ���Ă���B
�Q�ƃf�[�^ �F Nobunaga:.text -> 0045A540
���ڽ      �ި�������                                ����
00463945   CALL Nobunaga.0045A540
00465355   CALL Nobunaga.0045A540                    �ƕ�Ȃǂ͂���2�Ԗڂ̂悤��
00467F15   CALL Nobunaga.0045A540


�L���b�V��������Ƃ����ŃW�����v���Ă��܂��Ă���
00465324   E8 07FCFFFF      CALL Nobunaga.00464F30
00465329   85C0             TEST EAX,EAX
0046532B  ^75 90            JNZ SHORT Nobunaga.004652BD   ����ŃW�����v���Ă���B���EAX�𑀍삷��̂���
0046532D   8B6C24 1C        MOV EBP,DWORD PTR SS:[ESP+1C]
00465331   8D4424 10        LEA EAX,DWORD PTR SS:[ESP+10]

*/


#include <windows.h>
#include "game_process.h"

using namespace std;

#pragma unmanaged

static int ECXOfCheckPicCache = -1;
void OnSSRExeCheckPicCacheExecute() {
	// �摜�̃L���b�V���͂��Ȃ��B
	ECXOfCheckPicCache = 0;
}

/*
�L���b�V��������Ƃ����ŃW�����v���Ă��܂��Ă���
00465324   E8 07FCFFFF      CALL Nobunaga.00464F30
00465329   85C0             TEST EAX,EAX
0046532B  ^75 90            JNZ SHORT Nobunaga.004652BD   ����ŃW�����v���Ă���B���EAX�𑀍삷��̂���
0046532D   8B6C24 1C        MOV EBP,DWORD PTR SS:[ESP+1C]
00465331   8D4424 10        LEA EAX,DWORD PTR SS:[ESP+10]
*/

int pSSRExeJumpFromToOnSSRExeCheckPicCache = 0x465324; // �֐��͂��̃A�h���X����AOnSSRExeCheckPicCache�ւƃW�����v���Ă���B
int pSSRExeJumpCallFromToOnSSRExeCheckPicCache = 0x464F30; // ���X������������Call��
int pSSRExeReturnLblFromOnSSRExeCheckPicCache = 0x465329; // �֐����Ō�܂ł����ƁA����TENSHOU.EXE���ɒ��ڃW�����v����

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeCheckPicCache() {
	// �X�^�b�N�ɂ��߂Ă���
	__asm {

		mov ECXOfCheckPicCache, ecx

		call pSSRExeJumpCallFromToOnSSRExeCheckPicCache

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeCheckPicCacheExecute();

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

		mov eax, ECXOfCheckPicCache  // �L���b�V�����̃R���g���[�����ʂ��㏑��

		jmp pSSRExeReturnLblFromOnSSRExeCheckPicCache
	}
}
#pragma warning(default: 4733) // ���[�j���O�̗}������������



char cmdOnSSRExeJumpFromCheckPicCache[6] = "\xE9";
// ���̖��߂�5�o�C�g�A�Ȍ�̊֐��Ő��܂�閽�߂����v�T�o�C�g�Ȃ̂Łc �Ō�P�g��Ȃ�


// �j�[���j�b�N���������p
void WriteAsmJumperOnSSRExeCheckPicCache() {

	// �܂��A�h���X�𐔎��Ƃ��Ĉ���
	int iAddress = (int)OnSSRExeCheckPicCache;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeCheckPicCache + 5);
	// �T�Ƃ����̂́A0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  �̖��߂ɕK�v�ȃo�C�g���B�v����ɂT�o�C�g�����Ǝ��̃j�[���j�b�N���ߌQ�Ɉړ�����̂��B�����Ă�������̍������W�����v����ۂ̖ړI�i�Ƃ��ė��p�����B
	memcpy(cmdOnSSRExeJumpFromCheckPicCache + 1, &SubAddress, 4); // +1 ��E9�̎�����4�o�C�g�����������邩��B

	// �\�z�����j�[���j�b�N���߂�TENSHOU.EXE�̃������ɏ���������
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeCheckPicCache), cmdOnSSRExeJumpFromCheckPicCache, 5, NULL); //5�o�C�g�̂ݏ�������
}

#pragma managed
