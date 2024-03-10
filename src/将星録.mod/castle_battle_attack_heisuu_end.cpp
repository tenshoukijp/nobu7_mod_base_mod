/*
�U�����̑喼�|�C���^�⑍�����̏W�v
00407960  /$ 51             PUSH ECX                                 ;  Nobunaga.00540F28
00407961  |. 53             PUSH EBX
00407962  |. 56             PUSH ESI
00407963  |. 57             PUSH EDI
00407964  |. 33DB           XOR EBX,EBX
00407966  |. 33F6           XOR ESI,ESI
00407968  |. 8DB9 A8000000  LEA EDI,DWORD PTR DS:[ECX+A8]
0040796E  |. 8BFF           MOV EDI,EDI
00407970  |> 56             /PUSH ESI
00407971  |. 8D4424 10      |LEA EAX,DWORD PTR SS:[ESP+10]
00407975  |. 50             |PUSH EAX
00407976  |. 8BCF           |MOV ECX,EDI
00407978  |. E8 23DAFFFF    |CALL Nobunaga.004053A0
0040797D  |. 8B4C24 0C      |MOV ECX,DWORD PTR SS:[ESP+C]             // ���̎���ECX���A�Y���̕������̈ʒu�B��������50�o�C�g���𕔑����Ƃ��čT���Ă���
00407981  |. 3B0D 30925300  |CMP ECX,DWORD PTR DS:[539230]           ;  Nobunaga.005695C4
00407987  |. 74 07          |JE SHORT Nobunaga.00407990
00407989  |. E8 02B1FFFF    |CALL Nobunaga.00402A90
0040798E  |. 03D8           |ADD EBX,EAX                               // �Y���̕����̕���
00407990  |> 83C6 01        |ADD ESI,1                                 // ESI�̓J�E���^�B0-0x19
00407993  |. 83FE 19        |CMP ESI,19                                // 25�����ɂȂ�����I��
00407996  |.^7C D8          \JL SHORT Nobunaga.00407970
00407998  |. 5F             POP EDI
00407999  |. 5E             POP ESI
0040799A  |. 8BC3           MOV EAX,EBX
0040799C  |. 5B             POP EBX
0040799D  |. 59             POP ECX
0040799E  \. C3             RETN

*/

/*
005401A0  [01 00 00 00 19 00 00 00 84 03 00 00 84 03 00 00  ......�E..�E..
005401B0  00 00 00 00 84 03 00 00 C8 0F 5F 00 00 00 00 00  ....�E..�_.....
005401C0  94 01 00 00 D4 01 00 00 48 3C 56 00 00 90 53 00  �E..�..H<V..�S.
005401D0  A8 01] [02 00 00 00 19 00 00 00 84 03 00 00 84 03  �......�E..�E
005401E0  00 00 00 00 00 00 84 03 00 00 C8 0F 5F 00 01 00  ......�E..�_..
005401F0  00 00 BC 01 00 00 C0 01 00 00 48 3C 56 00 00 90  ..�..�..H<V..�E
00540200  53 00 08 00] [03 00 00 00 19 00 00 00 84 03 00 00  S........�E..
00540210  84 03 00 00 00 00 00 00 84 03 00 00 C8 0F 5F 00  �E......�E..�_.
00540220  02 00 00 00 E4 01 00 00 AC 01 00 00 48 3C 56 00  ...�E..�..H<V.
00540230  00 90 53 00 08 00] [04 00 00 00 19 00 00 00 84 03  .�S........�E
00540240  00 00 84 03 00 00 00 00 00 00 84 03 00 00 C8 0F  ..�E......�E..�
00540250  5F 00 03 00 00 00 E4 01 00 00 D4 01 00 00 48 3C  _....�E..�..H<
00540260  56 00 00 90 53 00 08 00] [05 00 00 00 19 00 00 00  V..�S........
00540270  84 03 00 00 84 03 00 00 00 00 00 00 84 03 00 00  �E..�E......�E..
00540280  C8 0F 5F 00 04 00 00 00 0C 02 00 00 98 01 00 00  �_.......�E..
00540290  48 3C 56 00 00 90 53 00 00 00]                     H<V..�S...
�ȍ~�A�U�` ���B�S�̂ōő�ł�20�����Ǝv����B(�P�����T�����ŁA�ő�ł��S�����B�Ȃ̂�5x4=20)
*/

#include <windows.h>
#include <string>
#include <vector>
#include "data_game_struct.h"
#include "data_bushou_struct.h"
#include "output_debug_stream.h"
#include "game_process.h"
#include "castle_battle_attack_heisuu_sum.h"


extern std::vector<�ď��U�����������> list�U�����������;
std::vector<�ď��U�����������> prev�U�����������;

using namespace std;



void OnSSRExeCastleBattleAttackHeisuuEndExecute() {

	bool isMustDifferSend = false;
	if (prev�U�����������.size() != list�U�����������.size()) {
		isMustDifferSend = true;
		OutputDebugStream("�U���E�ȈՒ����őO��ƈقȂ�B���M\n");
	}

	else if (prev�U�����������.size() == list�U�����������.size()) {
		// �Ⴄ���������������ǂ������`�F�b�N
		for (int ix = 0; ix < (int)list�U�����������.size(); ix++) {
			int differ = memcmp(&list�U�����������[ix], &prev�U�����������[ix], sizeof(�ď��U�����������));
			if (differ) {
				isMustDifferSend = true;

				/*
				if (list�U�����������[ix].unknown_14 != prev�U�����������[ix].unknown_14) {
					OutputDebugStream("nunknown_14%d\n", prev�U�����������[ix].unknown_14);
					OutputDebugStream("nunknown_14%d\n" ,list�U�����������[ix].unknown_14);
				}

				if (prev�U�����������[ix].unknown2 != prev�U�����������[ix].unknown2) {
					OutputDebugStream("unknown2 prev %d\n", prev�U�����������[ix].unknown2);
					OutputDebugStream("unknown2 list %d\n", list�U�����������[ix].unknown2);
				}

				if (list�U�����������[ix].unknown1 != prev�U�����������[ix].unknown1) {
					OutputDebugStream("unknown1 prev %d\n", prev�U�����������[ix].unknown1);
					OutputDebugStream("unknown1 list %d\n", list�U�����������[ix].unknown1);
				}
				*/

				/*
				int iBushouID = getBushouIDFromBushouPtr((int*)list�U�����������[ix].p�w������);
				if (isValidBushouID(iBushouID) && list�U�����������[ix].���� > 0 && list�U�����������[ix].�����ԍ� > 0) {
					OutputDebugStream("�w����" + getBushou����FromBushouID(iBushouID) + "\n");
					OutputDebugStream("�����ԍ� %d\n", list�U�����������[ix].�����ԍ�);
					OutputDebugStream("�������� %d\n", list�U�����������[ix].����);
				}
				*/

				OutputDebugStream("�U���E�ڍג����őO��ƈقȂ�B���M\n");
			}
		}
	}

	// list����prev�փR�s�[
	if (isMustDifferSend) {
		prev�U�����������.clear();
		for (auto item : list�U�����������) {
			prev�U�����������.push_back(item);
		}
	}

	if (isMustDifferSend) {
		OutputDebugStream("list�U������������C#Mod�ւƑ��M����");
	}

}

/*
00407998  |. 5F             POP EDI
00407999  |. 5E             POP ESI
0040799A  |. 8BC3           MOV EAX,EBX
0040799C  |. 5B             POP EBX
0040799D  |. 59             POP ECX
0040799E  \. C3             RETN
*/

#pragma unmanaged

int pSSRExeJumpFromToOnSSRExeCastleBattleAttackHeisuuEnd = 0x407998; // �֐��͂��̃A�h���X����AOnSSRExeCastleBattleAttackHeisuuEnd�ւƃW�����v���Ă���B
int pSSRExeReturnLblFromOnSSRExeCastleBattleAttackHeisuuEnd = 0x40799E; // �֐����Ō�܂ł����ƁA����TENSHOU.EXE���ɒ��ڃW�����v����

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeCastleBattleAttackHeisuuEnd() {
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

	OnSSRExeCastleBattleAttackHeisuuEndExecute();

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

		// ���̏����������ɋL�q
		POP EDI
		POP ESI
		MOV EAX, EBX
		POP EBX
		POP ECX

		jmp pSSRExeReturnLblFromOnSSRExeCastleBattleAttackHeisuuEnd
	}
}
#pragma warning(default: 4733) // ���[�j���O�̗}������������



char cmdOnSSRExeJumpFromCastleBattleAttackHeisuuEnd[7] = "\xE9\x90\x90\x90\x90\x90";
// ���̖��߂�5�o�C�g�A�Ȍ�̊֐��Ő��܂�閽�߂����v�T�o�C�g�Ȃ̂Łc �Ō�P�g��Ȃ�


// �j�[���j�b�N���������p
void WriteAsmJumperOnSSRExeCastleBattleAttackHeisuuEnd() {

	// �܂��A�h���X�𐔎��Ƃ��Ĉ���
	int iAddress = (int)OnSSRExeCastleBattleAttackHeisuuEnd;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeCastleBattleAttackHeisuuEnd + 5);
	// �T�Ƃ����̂́A0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  �̖��߂ɕK�v�ȃo�C�g���B�v����ɂT�o�C�g�����Ǝ��̃j�[���j�b�N���ߌQ�Ɉړ�����̂��B�����Ă�������̍������W�����v����ۂ̖ړI�i�Ƃ��ė��p�����B
	memcpy(cmdOnSSRExeJumpFromCastleBattleAttackHeisuuEnd + 1, &SubAddress, 4); // +1 ��E9�̎�����4�o�C�g�����������邩��B

	// �\�z�����j�[���j�b�N���߂�TENSHOU.EXE�̃������ɏ���������
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeCastleBattleAttackHeisuuEnd), cmdOnSSRExeJumpFromCastleBattleAttackHeisuuEnd, 6, NULL); //6�o�C�g�̂ݏ�������
}

#pragma managed
