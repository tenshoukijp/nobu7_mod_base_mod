/*
004076B0  /$ 51             PUSH ECX
004076B1  |. 53             PUSH EBX
004076B2  |. 55             PUSH EBP
004076B3  |. 56             PUSH ESI
004076B4  |. 33ED           XOR EBP,EBP
004076B6  |. 57             PUSH EDI
004076B7  |. 33F6           XOR ESI,ESI
004076B9  |. 8D99 8C000000  LEA EBX,DWORD PTR DS:[ECX+8C]
004076BF  |. 90             NOP
004076C0  |> 56             /PUSH ESI
004076C1  |. 8D4424 14      |LEA EAX,DWORD PTR SS:[ESP+14]
004076C5  |. 50             |PUSH EAX
004076C6  |. 8BCB           |MOV ECX,EBX
004076C8  |. E8 43DCFFFF    |CALL Nobunaga.00405310
004076CD  |. 8B4C24 10      |MOV ECX,DWORD PTR SS:[ESP+10]           // ���̎���ECX���A�Y���̕������̈ʒu�B��������34�o�C�g���𕔑����Ƃ��čT���Ă���
004076D1  |. 3B0D 2C925300  |CMP ECX,DWORD PTR DS:[53922C]           ;  Nobunaga.0056948C
004076D7  |. 8BF9           |MOV EDI,ECX
004076D9  |. 74 12          |JE SHORT Nobunaga.004076ED
004076DB  |. E8 B0C2FFFF    |CALL Nobunaga.00403990
004076E0  |. 85C0           |TEST EAX,EAX
004076E2  |. 75 09          |JNZ SHORT Nobunaga.004076ED
004076E4  |. 8BCF           |MOV ECX,EDI
004076E6  |. E8 A5B3FFFF    |CALL Nobunaga.00402A90
004076EB  |. 03E8           |ADD EBP,EAX
004076ED  |> 83C6 01        |ADD ESI,1                                 // ESI�̓J�E���^�B0-0x16
004076F0  |. 83FE 16        |CMP ESI,16                                // 23�����ɂȂ�����I��   
004076F3  |.^7C CB          \JL SHORT Nobunaga.004076C0
004076F5  |. 5F             POP EDI
004076F6  |. 5E             POP ESI
004076F7  |. 8BC5           MOV EAX,EBP
004076F9  |. 5D             POP EBP
004076FA  |. 5B             POP EBX
004076FB  |. 59             POP ECX
004076FC  \. C3             RETN

*/

#include <windows.h>
#include <string>
#include <vector>
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

/*
0053FEB0  [01 00 00 00 16 00 00 00 F4 01 00 00 F4 01 00 00  ......�E..�E..
0053FEC0  00 00 08 41 55 00 00 00 00 00 01 00 00 00 06 00  ..AU.........
0053FED0  00 00] [02 00 00 00 16 00 00 00 F4 01 00 00 F4 01  ........�E..�E
0053FEE0  00 00 00 00 C8 44 55 00 01 00 00 00 01 00 00 00  ....�DU.......
0053FEF0  06 00 00 00] [03 00 00 00 16 00 00 00 F4 01 00 00  .........�E..
0053FF00  F4 01 00 00 00 00 08 44 55 00 03 00 00 00 01 00  �E....DU.....
0053FF10  00 00 06 00 00 00] [04 00 00 00 16 00 00 00 F4 01  ...........�E
0053FF20  00 00 F4 01 00 00 00 00 B0 94 56 00 05 00 00 00  ..�E....��V....
0053FF30  01 00 00 00] [06 00 00 00 05 00 00 00 16 00 00 00  ............
0053FF40  F4 01 00 00 F4 01 00 00 00 00 B0 94 56           �E..�E....��V..

*/

// 34�o�C�g
struct �ď��h�䑤������� {
	int �����ԍ�; // 1�`25
	int unknown1;
	int ����;     // ���̕����̌��݂̕���
	int ����MAX;  // ���̕����̕����̕�����MAX
	WORD unknown2; // 0 �������Ă��邩�H
	int	p�w������; // ���̕����𗦂��Ă��镐�����ւ̃|�C���^�B[B0 94 56]�Ȃ�w���������Ȃ��B�������A����������Ȃ�A�w�����Ȃ��̕���������B
	int	unknown4; // �s�� 0�������H
	int	unknown5; // �s��
	int	unknown6; // �s��
};

std::vector<�ď��h�䑤�������> list�h�䑤�������;


using namespace std;


#pragma unmanaged

static int ECXOfCastleBattleDefendHeisuuSum = -1; // �������ւ̃|�C���^�B�������͏��struct��50�o�C�g�\��
static int ESIOfCastleBattleDefendHeisuuSum = -1; // ���Ԗڂ̕����Ȃ̂��B0-25
void OnSSRExeCastleBattleDefendHeisuuSumExecute() {


	int index = ESIOfCastleBattleDefendHeisuuSum;

	// index��0�̎��́A��������S������������
	if (index == 0) {
		list�h�䑤�������.clear();
		for (int i = 0; i < 0x16; i++) { // 0x16=22
			�ď��h�䑤������� info;
			ZeroMemory(&info, sizeof(info));
			list�h�䑤�������.push_back(info);
		}
	}

	if (index < (int)list�h�䑤�������.size()) {
		�ď��h�䑤�������* p������� = (�ď��h�䑤�������*)ECXOfCastleBattleDefendHeisuuSum;
		int differ = memcmp(&list�h�䑤�������[index], p�������, sizeof(�ď��h�䑤�������));
		if (differ) {
			list�h�䑤�������[index] = *p�������; // ���������P�R�s�[�B
			int iBushouID = getBushouIDFromBushouPtr((int*)list�h�䑤�������[index].p�w������);
			if (isValidBushouID(iBushouID) && list�h�䑤�������[index].���� > 0 && list�h�䑤�������[index].�����ԍ� > 0) {
				OutputDebugStream("�w����" + getBushou����FromBushouID(iBushouID) + "\n");
				OutputDebugStream("�����ԍ� %d\n", list�h�䑤�������[index].�����ԍ�);
				OutputDebugStream("�������� %d\n", list�h�䑤�������[index].����);
			}
			else if (list�h�䑤�������[index].���� > 0 && list�h�䑤�������[index].�����ԍ� > 0) {
				OutputDebugStream("�w�����Ȃ�\n");
				OutputDebugStream("�����ԍ� %d\n", list�h�䑤�������[index].�����ԍ�);
				OutputDebugStream("�������� %d\n", list�h�䑤�������[index].����);
			}
		}
	}

}

/*
004076C0  |> 56             /PUSH ESI
004076C1  |. 8D4424 14      |LEA EAX,DWORD PTR SS:[ESP+14]
004076C5  |. 50             |PUSH EAX
004076C6  |. 8BCB           |MOV ECX,EBX
004076C8  |. E8 43DCFFFF    |CALL Nobunaga.00405310
004076CD  |. 8B4C24 10      |MOV ECX,DWORD PTR SS:[ESP+10]           // ���̎���ECX���A�Y���̕������̈ʒu�B��������34�o�C�g���𕔑����Ƃ��čT���Ă���
004076D1  |. 3B0D 2C925300  |CMP ECX,DWORD PTR DS:[53922C]           ;  Nobunaga.0056948C
004076D7  |. 8BF9           |MOV EDI,ECX
*/


int pSSRExeJumpFromToOnSSRExeCastleBattleDefendHeisuuSum = 0x4076C8; // �֐��͂��̃A�h���X����AOnSSRExeCastleBattleDefendHeisuuSum�ւƃW�����v���Ă���B
int pSSRExeJumpCallFromToOnSSRExeCastleBattleDefendHeisuuSum = 0x405310; // ���X������������Call��
int pSSRExeReturnLblFromOnSSRExeCastleBattleDefendHeisuuSum = 0x4076CD; // �֐����Ō�܂ł����ƁA����TENSHOU.EXE���ɒ��ڃW�����v����

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeCastleBattleDefendHeisuuSum() {
	// �X�^�b�N�ɂ��߂Ă���
	__asm {

		call pSSRExeJumpCallFromToOnSSRExeCastleBattleDefendHeisuuSum // ���̏���

		MOV ECX, DWORD PTR SS : [ESP + 0x10] // ���̏����Ɠ�������

		MOV ESIOfCastleBattleDefendHeisuuSum, ESI // �J�E���^�������Ă���

		MOV ECXOfCastleBattleDefendHeisuuSum, ECX // ECX�ɂ͕������ւ̃|�C���^�������Ă���

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeCastleBattleDefendHeisuuSumExecute();

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

		jmp pSSRExeReturnLblFromOnSSRExeCastleBattleDefendHeisuuSum
	}
}
#pragma warning(default: 4733) // ���[�j���O�̗}������������



char cmdOnSSRExeJumpFromCastleBattleDefendHeisuuSum[6] = "\xE9";
// ���̖��߂�5�o�C�g�A�Ȍ�̊֐��Ő��܂�閽�߂����v�T�o�C�g�Ȃ̂Łc �Ō�P�g��Ȃ�


// �j�[���j�b�N���������p
void WriteAsmJumperOnSSRExeCastleBattleDefendHeisuuSum() {

	// �܂��A�h���X�𐔎��Ƃ��Ĉ���
	int iAddress = (int)OnSSRExeCastleBattleDefendHeisuuSum;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeCastleBattleDefendHeisuuSum + 5);
	// �T�Ƃ����̂́A0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  �̖��߂ɕK�v�ȃo�C�g���B�v����ɂT�o�C�g�����Ǝ��̃j�[���j�b�N���ߌQ�Ɉړ�����̂��B�����Ă�������̍������W�����v����ۂ̖ړI�i�Ƃ��ė��p�����B
	memcpy(cmdOnSSRExeJumpFromCastleBattleDefendHeisuuSum + 1, &SubAddress, 4); // +1 ��E9�̎�����4�o�C�g�����������邩��B

	// �\�z�����j�[���j�b�N���߂�TENSHOU.EXE�̃������ɏ���������
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeCastleBattleDefendHeisuuSum), cmdOnSSRExeJumpFromCastleBattleDefendHeisuuSum, 5, NULL); //5�o�C�g�̂ݏ�������
}

#pragma managed
