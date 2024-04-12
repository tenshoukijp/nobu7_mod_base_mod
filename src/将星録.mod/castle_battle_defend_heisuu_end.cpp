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
#include "game_process.h"

#include "castle_battle_defend_heisuu_sum.h"

#include "mng_�ď�핔����.h"
#include "usr_custom_mod.h"

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


extern BOOL isCustomModBeginCalled;
extern std::vector<NB7�ď��h�䑤�������^> list�h�䑤�������;
std::vector<NB7�ď��h�䑤�������^> prev�h�䑤�������;


using namespace std;

NB7�ď��h�䑤�������^ �h�䑤�������T��[�ő吔::�ď��::�h�䕔�����::�z��] = { 0 };

extern int iLastBattleRemainTurn;

void OnSSRExeCastleBattleDefendHeisuuEndExecute() {

	bool isMustDifferSend = false;

	int differ = memcmp(&�h�䑤�������T��, (void*)�ď��h�䑤�������A�h���X, sizeof(�h�䑤�������T��));
	if (differ) {
		isMustDifferSend = true;
	}

	/*
	if (prev�h�䑤�������.size() != list�h�䑤�������.size()) {
		isMustDifferSend = true;
		OutputDebugStream("�h��E�ȈՒ����őO��ƈقȂ�B���M\n");
	}

	else if (prev�h�䑤�������.size() == list�h�䑤�������.size()) {
		// �Ⴄ���������������ǂ������`�F�b�N
		for (int ix = 0; ix < (int)list�h�䑤�������.size(); ix++) {
			int differ = memcmp(&list�h�䑤�������[ix], &prev�h�䑤�������[ix], sizeof(NB7�ď��h�䑤�������^));
			if (differ) {
				isMustDifferSend = true;

				if (list�h�䑤�������[ix].unknown8 != prev�h�䑤�������[ix].unknown8) {
					OutputDebugStream("unknown8 prev %d\n", prev�h�䑤�������[ix].unknown8);
					OutputDebugStream("unknown8 list %d\n", list�h�䑤�������[ix].unknown8);
				}

				if (list�h�䑤�������[ix].unknown6 != prev�h�䑤�������[ix].unknown6) {
					OutputDebugStream("unknown6 prev %d\n", prev�h�䑤�������[ix].unknown6);
					OutputDebugStream("unknown6 list %d\n", list�h�䑤�������[ix].unknown6);
				}

				if (list�h�䑤�������[ix].unknown5 != prev�h�䑤�������[ix].unknown5) {
					OutputDebugStream("unknown5 prev %d\n", prev�h�䑤�������[ix].unknown5);
					OutputDebugStream("unknown5 list %d\n", list�h�䑤�������[ix].unknown5);
				}

				if (list�h�䑤�������[ix].unknown7 != prev�h�䑤�������[ix].unknown7) {
					OutputDebugStream("unknown7 prev %d\n", prev�h�䑤�������[ix].unknown7);
					OutputDebugStream("unknown7 list %d\n", list�h�䑤�������[ix].unknown7);
				}

				if (list�h�䑤�������[ix].unknown4 != prev�h�䑤�������[ix].unknown4) {
					OutputDebugStream("unknown4 prev %d\n", prev�h�䑤�������[ix].unknown4);
					OutputDebugStream("unknown4 list %d\n", list�h�䑤�������[ix].unknown4);
				}

				if (list�h�䑤�������[ix].unknown2 != prev�h�䑤�������[ix].unknown2) {
					OutputDebugStream("unknown2 prev %d\n", prev�h�䑤�������[ix].unknown2);
					OutputDebugStream("unknown2 list %d\n", list�h�䑤�������[ix].unknown2);
				}

				if (list�h�䑤�������[ix].unknown1 != prev�h�䑤�������[ix].unknown1) {
					OutputDebugStream("unknown1 prev %d\n", prev�h�䑤�������[ix].unknown1);
					OutputDebugStream("unknown1 list %d\n", list�h�䑤�������[ix].unknown1);
				}

				int iBushouID = getBushouIDFromBushouPtr((int*)list�h�䑤�������[ix].p�w������);
				if (isValidBushouID(iBushouID) && list�h�䑤�������[ix].���� > 0 && list�h�䑤�������[ix].�����ԍ� > 0) {
					OutputDebugStream("�w����" + getBushou����FromBushouID(iBushouID) + "\n");
					OutputDebugStream("�����ԍ� %d\n", list�h�䑤�������[ix].�����ԍ�);
					OutputDebugStream("�������� %d\n", list�h�䑤�������[ix].����);
				}
				else if (list�h�䑤�������[ix].���� > 0 && list�h�䑤�������[ix].�����ԍ� > 0) {
					OutputDebugStream("�w�����Ȃ�\n");
					OutputDebugStream("�����ԍ� %d\n", list�h�䑤�������[ix].�����ԍ�);
					OutputDebugStream("�������� %d\n", list�h�䑤�������[ix].����);
				}

				OutputDebugStream("�h��E�ڍג����őO��ƈقȂ�B���M\n");
			}
		}
	}
	*/

	// list����prev�փR�s�[
	if (isMustDifferSend) {
		/*
		prev�h�䑤�������.clear();
		for (auto item : list�h�䑤�������) {
			prev�h�䑤�������.push_back(item);
		}
		*/
		memcpy(&�h�䑤�������T��, (void*)�ď��h�䑤�������A�h���X, sizeof(�h�䑤�������T��));

		/*
		for (int ix = 0; ix < �ő吔::�ď��::�h�䕔�����::�z��; ix++) {
			int iBushouID = getBushouIDFromBushouPtr(nb7�ď��h�䑤�������[ix].p�w������);
			if (isValidBushouID(iBushouID) && nb7�ď��h�䑤�������[ix].���� > 0 && nb7�ď��h�䑤�������[ix].�����ԍ� > 0) {
				OutputDebugStream("�w����" + getBushou����FromBushouID(iBushouID) + "\n");
				OutputDebugStream("�����ԍ� %d\n", nb7�ď��h�䑤�������[ix].�����ԍ�);
				OutputDebugStream("�������� %d\n", nb7�ď��h�䑤�������[ix].����);
				OutputDebugStream("�������� %d\n", nb7�ď��h�䑤�������[ix].����);
				OutputDebugStream("�������� %d\n", nb7�ď��h�䑤�������[ix].����);
			}
		}
		*/

	}

	if (isMustDifferSend && isCustomModBeginCalled) {
		OutputDebugStream("�h��E�ڍג����őO��ƈقȂ�B���M\n");
		// C#�̃J�X�^��.mod.dll����̏㏑��
		try {
			System::Collections::Generic::Dictionary<System::String^, System::Object^>^ dic = gcnew System::Collections::Generic::Dictionary<System::String^, System::Object^>(5);
			dic->Add("�c��^�[��", iLastBattleRemainTurn);
			System::Collections::Generic::Dictionary<System::String^, System::Object^>^ ret = InvokeUserMethod("on�ď��h�䕔���X�V��", dic);
		}
		catch (System::Exception^) {
			OutputDebugStream("on�ď��h�䕔���X�V��ɃG���[���������܂���");
		}

	}
}

/*
004076F5  |. 5F             POP EDI
004076F6  |. 5E             POP ESI
004076F7  |. 8BC5           MOV EAX,EBP
004076F9  |. 5D             POP EBP
004076FA  |. 5B             POP EBX
004076FB  |. 59             POP ECX
004076FC  \. C3             RETN
*/

#pragma unmanaged

int pSSRExeJumpFromToOnSSRExeCastleBattleDefendHeisuuEnd = 0x4076F5; // �֐��͂��̃A�h���X����AOnSSRExeCastleBattleDefendHeisuuEnd�ւƃW�����v���Ă���B
int pSSRExeReturnLblFromOnSSRExeCastleBattleDefendHeisuuEnd = 0x4076FC; // �֐����Ō�܂ł����ƁA���̎��sexe���ɒ��ڃW�����v����

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeCastleBattleDefendHeisuuEnd() {
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

	OnSSRExeCastleBattleDefendHeisuuEndExecute();

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

		POP EDI
		POP ESI
		MOV EAX, EBP
		POP EBP
		POP EBX
		POP ECX

		jmp pSSRExeReturnLblFromOnSSRExeCastleBattleDefendHeisuuEnd
	}
}
#pragma warning(default: 4733) // ���[�j���O�̗}������������



char cmdOnSSRExeJumpFromCastleBattleDefendHeisuuEnd[8] = "\xE9";
// ���̖��߂�5�o�C�g�A�Ȍ�̊֐��Ő��܂�閽�߂����v�T�o�C�g�Ȃ̂Łc �Ō�P�g��Ȃ�


// �j�[���j�b�N���������p
void WriteAsmJumperOnSSRExeCastleBattleDefendHeisuuEnd() {

	// �܂��A�h���X�𐔎��Ƃ��Ĉ���
	int iAddress = (int)OnSSRExeCastleBattleDefendHeisuuEnd;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeCastleBattleDefendHeisuuEnd + 5);
	// �T�Ƃ����̂́A0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  �̖��߂ɕK�v�ȃo�C�g���B�v����ɂT�o�C�g�����Ǝ��̃j�[���j�b�N���ߌQ�Ɉړ�����̂��B�����Ă�������̍������W�����v����ۂ̖ړI�i�Ƃ��ė��p�����B
	memcpy(cmdOnSSRExeJumpFromCastleBattleDefendHeisuuEnd + 1, &SubAddress, 4); // +1 ��E9�̎�����4�o�C�g�����������邩��B

	// �\�z�����j�[���j�b�N���߂����sexe�̃������ɏ���������
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeCastleBattleDefendHeisuuEnd), cmdOnSSRExeJumpFromCastleBattleDefendHeisuuEnd, 7, NULL); //7�o�C�g�̂ݏ�������
}

#pragma managed
