// ���̃t�@�C���͒������s�B���ɗ����Ȃ��B�R���p�C���Ώۂ���O��Ă���

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

#pragma unmanaged

/*
005D986C  B8 D5 5D 00 B8 8E 53 00 B8 8E 53 00 B8 8E 53 00  ��].��S.��S.��S.
005D987C  B8 8E 53 00 B8 8E 53 00 26 AB 56 00 [C0 96 5D] 00  ��S.��S.&�V.��]. �� ������[ ] �ɗ�`�̑Ώێ҂̕������ւ̃|�C���^������Ǝv���邪������͐��x���Ⴂ�B���ɗ����Ȃ��B
005D988C  48 3C 56 00 B0 94 56 00 DA F0 42 00 F8 91 56 00  H<V.��V.��B.��V.
*/

/*
00569278  [B0 94 56] 00 00 00 00 00 28 00 00 00 78 00 00 00  ��V.....(...x...   �� ������[ ] �ɗ�`�̑Ώێ҂̕������ւ̃|�C���^������Ǝv����B����͐��x�������B0x5694B0�̎��͉����Ȃ�
00569288  14 00 00 00 64 00 00 00 00 00 00 00 00 00 00 00  ...d...........
00569298  A0 00 00 00 A0 00 00 00 26 AB 56 00 16 00 00 00  �...�...&�V....
005692A8  40 00 00 00 01 00 00 00 00 00 00 00 26 AB 56 00  @..........&�V.

����0x569278 ���Q�Ƃ��Ă��āA�������݂��Ă���̂�3����
�Q�ƃf�[�^ �F Nobunaga:.text -> 00569278..00569278
���ڽ      �ި�������                                ����
0042FE1E   MOV DWORD PTR DS:[569278],ESI
00432113   MOV DWORD PTR DS:[569278],EAX
004322F6   MOV DWORD PTR DS:[569278],ESI
*/


/*
1������
0042FE19   B9 F8915600      MOV ECX,Nobunaga.005691F8
0042FE1E   8935 78925600    MOV DWORD PTR DS:[569278],ESI
0042FE24   E8 47CBFFFF      CALL Nobunaga.0042C970
0042FE29   F605 1C925600 02 TEST BYTE PTR DS:[56921C],2
*/

/*
2������
00432113   A3 78925600      MOV DWORD PTR DS:[569278],EAX
00432118   E8 53A8FFFF      CALL Nobunaga.0042C970
0043211D   B9 F8915600      MOV ECX,Nobunaga.005691F8
/

/*
3������
004322F6   8935 78925600    MOV DWORD PTR DS:[569278],ESI
004322FC   E8 6FA6FFFF      CALL Nobunaga.0042C970
00432301   B9 F8915600      MOV ECX,Nobunaga.005691F8
*/

void OnSSRExeUnknownDialog2Execute() {
	OutputDebugStream("���������s���ȃ_�C�A���O2��������!!!��\n");
}


/*
�s���ȃ_�C�A���O�����s����鎞

2������
00432113   A3 78925600      MOV DWORD PTR DS:[569278],EAX
00432118   E8 53A8FFFF      CALL Nobunaga.0042C970
0043211D   B9 F8915600      MOV ECX,Nobunaga.005691F8
*/
/*



*/
int pSSRExeJumpFromToOnSSRExeUnknownDialog2 = 0x432118; // �֐��͂��̃A�h���X����AOnSSRExeUnknownDialog2�ւƃW�����v���Ă���B
int pSSRExeJumpCallFromToOnSSRExeUnknownDialog2 = 0x42C970; // ���X������������Call��
int pSSRExeReturnLblFromOnSSRExeUnknownDialog2 = 0x43211D; // �֐����Ō�܂ł����ƁA����TENSHOU.EXE���ɒ��ڃW�����v����

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeUnknownDialog2() {
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

	OnSSRExeUnknownDialog2Execute();

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

		call pSSRExeJumpCallFromToOnSSRExeUnknownDialog2 // ���̏���

		jmp pSSRExeReturnLblFromOnSSRExeUnknownDialog2
	}
}
#pragma warning(default: 4733) // ���[�j���O�̗}������������



char cmdOnSSRExeJumpFromUnknownDialog2[6] = "\xE9";
// ���̖��߂�5�o�C�g�A�Ȍ�̊֐��Ő��܂�閽�߂����v�T�o�C�g�Ȃ̂Łc �Ō�P�g��Ȃ�


// �j�[���j�b�N���������p
void WriteAsmJumperOnSSRExeUnknownDialog2() {

	// �܂��A�h���X�𐔎��Ƃ��Ĉ���
	int iAddress = (int)OnSSRExeUnknownDialog2;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeUnknownDialog2 + 5);
	// �T�Ƃ����̂́A0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  �̖��߂ɕK�v�ȃo�C�g���B�v����ɂT�o�C�g�����Ǝ��̃j�[���j�b�N���ߌQ�Ɉړ�����̂��B�����Ă�������̍������W�����v����ۂ̖ړI�i�Ƃ��ė��p�����B
	memcpy(cmdOnSSRExeJumpFromUnknownDialog2 + 1, &SubAddress, 4); // +1 ��E9�̎�����4�o�C�g�����������邩��B

	// �\�z�����j�[���j�b�N���߂�TENSHOU.EXE�̃������ɏ���������
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeUnknownDialog2), cmdOnSSRExeJumpFromUnknownDialog2, 5, NULL); //5�o�C�g�̂ݏ�������
}

#pragma managed
