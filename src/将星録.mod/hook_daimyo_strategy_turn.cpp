/*
�P�����̐헪��ʂŁA�喼���Ƃɂ��͈̔͂����[�v����B
00434CC0   8B8E FC000000    /MOV ECX,DWORD PTR DS:[ESI+FC]
00434CC6   E8 85DB0000      |CALL Nobunaga.00442850
00434CCB   85C0             |TEST EAX,EAX
00434CCD   0F84 E7000000    |JE Nobunaga.00434DBA
00434CD3   B9 D8AA5800      |MOV ECX,Nobunaga.0058AAD8               ; ASCII "LCR"
00434CD8   E8 53F30400      |CALL Nobunaga.00484030
00434CDD   8B8E FC000000    |MOV ECX,DWORD PTR DS:[ESI+FC]
00434CE3   E8 18FBFFFF      |CALL Nobunaga.00434800
00434CE8   8B8E FC000000    |MOV ECX,DWORD PTR DS:[ESI+FC]
00434CEE   E8 5DDB0000      |CALL Nobunaga.00442850
00434CF3   B9 80E95700      |MOV ECX,Nobunaga.0057E980
00434CF8   E8 737A0200      |CALL Nobunaga.0045C770
00434CFD   85C0             |TEST EAX,EAX
00434CFF   0F85 F4000000    |JNZ Nobunaga.00434DF9
00434D05   8B8E FC000000    |MOV ECX,DWORD PTR DS:[ESI+FC]
00434D0B   E8 70DB0000      |CALL Nobunaga.00442880
00434D10   85C0             |TEST EAX,EAX
00434D12   0F84 86000000    |JE Nobunaga.00434D9E
00434D18   B9 F0BF5E00      |MOV ECX,Nobunaga.005EBFF0
00434D1D   E8 EEFD0800      |CALL Nobunaga.004C4B10
00434D22   85C0             |TEST EAX,EAX
00434D24   75 0E            |JNZ SHORT Nobunaga.00434D34
00434D26   B9 F0BF5E00      |MOV ECX,Nobunaga.005EBFF0
00434D2B   E8 40FE0800      |CALL Nobunaga.004C4B70
00434D30   85C0             |TEST EAX,EAX
00434D32   74 6A            |JE SHORT Nobunaga.00434D9E
00434D34   57               |PUSH EDI
00434D35   8D5424 1C        |LEA EDX,DWORD PTR SS:[ESP+1C]
00434D39   52               |PUSH EDX
00434D3A   8BCB             |MOV ECX,EBX
00434D3C   E8 4F620000      |CALL Nobunaga.0043AF90
00434D41   A1 F8915300      |MOV EAX,DWORD PTR DS:[5391F8]
00434D46   394424 18        |CMP DWORD PTR SS:[ESP+18],EAX
00434D4A   74 19            |JE SHORT Nobunaga.00434D65
00434D4C   57               |PUSH EDI
00434D4D   8D4424 20        |LEA EAX,DWORD PTR SS:[ESP+20]
00434D51   50               |PUSH EAX
00434D52   8BCB             |MOV ECX,EBX
00434D54   E8 37620000      |CALL Nobunaga.0043AF90
00434D59   8B4C24 1C        |MOV ECX,DWORD PTR SS:[ESP+1C]
00434D5D   898E FC000000    |MOV DWORD PTR DS:[ESI+FC],ECX
00434D63   EB 06            |JMP SHORT Nobunaga.00434D6B
00434D65   8986 FC000000    |MOV DWORD PTR DS:[ESI+FC],EAX
00434D6B   83EC 10          |SUB ESP,10
00434D6E   8BFC             |MOV EDI,ESP
00434D70   68 E0AA5800      |PUSH Nobunaga.0058AAE0
00434D75   8BCF             |MOV ECX,EDI
00434D77   E8 B8DC0C00      |CALL Nobunaga.00502A34
00434D7C   68 E8AA5800      |PUSH Nobunaga.0058AAE8
00434D81   8D4F 08          |LEA ECX,DWORD PTR DS:[EDI+8]
00434D84   E8 ABDC0C00      |CALL Nobunaga.00502A34
00434D89   8B15 D8AA5800    |MOV EDX,DWORD PTR DS:[58AAD8]           ; Nobunaga.0052434C
00434D8F   8B42 44          |MOV EAX,DWORD PTR DS:[EDX+44]
00434D92   68 D8AA5800      |PUSH Nobunaga.0058AAD8                  ; ASCII "LCR"
00434D97   B9 D8AA5800      |MOV ECX,Nobunaga.0058AAD8               ; ASCII "LCR"
00434D9C   FFD0             |CALL NEAR EAX
00434D9E   B9 80E95700      |MOV ECX,Nobunaga.0057E980
00434DA3   E8 08880200      |CALL Nobunaga.0045D5B0
00434DA8   85C0             |TEST EAX,EAX
00434DAA   74 0E            |JE SHORT Nobunaga.00434DBA
00434DAC   E8 3F580700      |CALL Nobunaga.004AA5F0
00434DB1   85C0             |TEST EAX,EAX
00434DB3   74 05            |JE SHORT Nobunaga.00434DBA
00434DB5   E8 66FBFFFF      |CALL Nobunaga.00434920
00434DBA   8B7C24 14        |MOV EDI,DWORD PTR SS:[ESP+14]
00434DBE   83C5 01          |ADD EBP,1
00434DC1   55               |PUSH EBP
00434DC2   8D4C24 14        |LEA ECX,DWORD PTR SS:[ESP+14]
00434DC6   51               |PUSH ECX
00434DC7   83C7 01          |ADD EDI,1
00434DCA   8BCB             |MOV ECX,EBX
00434DCC   897C24 1C        |MOV DWORD PTR SS:[ESP+1C],EDI
00434DD0   E8 BB610000      |CALL Nobunaga.0043AF90
00434DD5   8B4424 10        |MOV EAX,DWORD PTR SS:[ESP+10]
00434DD9   8986 FC000000    |MOV DWORD PTR DS:[ESI+FC],EAX
00434DDF   3B05 F8915300    |CMP EAX,DWORD PTR DS:[5391F8]           ; Nobunaga.00538EB8
00434DE5  ^0F85 D5FEFFFF    \JNZ Nobunaga.00434CC0

*/




/*
00434CC0   8B8E FC000000    /MOV ECX,DWORD PTR DS:[ESI+FC]         ECX�͑喼���̊Y���喼�ւ̃|�C���^
00434CC6   E8 85DB0000      |CALL Nobunaga.00442850
00434CCB   85C0             |TEST EAX,EAX
*/




#include <windows.h>
#include <string>
#include "data_game_struct.h"
#include "data_bushou_struct.h"
#include "output_debug_stream.h"
#include "game_screen.h"
#include "game_process.h"


using namespace std;

#pragma unmanaged

extern void onStrategyDaimyoTurnChanged(int iDaimyoID);

static int iTurnDaimyoPointerOfStrategy = -1;

void OnSSRExeMainStrategyDaimyoTurnExecute() {
	OutputDebugStream("���������喼�^�[��(�t�b�N)�ɓ��B���܂���\n");
	int iDaimyoID = getDaimyoIDFromDaimyoPtr((int*)iTurnDaimyoPointerOfStrategy);
	if (isValidDaimyoID(iDaimyoID)) {
		int iBushouID = getBushouIDFromDaimyoID(iDaimyoID);

		OutputDebugStream(getBushou����FromBushouID(iBushouID) + "�̑喼�^�[�����O�ł�\n");

		onStrategyDaimyoTurnChanged(iDaimyoID);

	}
}


/*
00434CC0   8B8E FC000000    /MOV ECX,DWORD PTR DS:[ESI+FC]         ECX�͑喼���̊Y���喼�ւ̃|�C���^
00434CC6   E8 85DB0000      |CALL Nobunaga.00442850
00434CCB   85C0             |TEST EAX,EAX
*/

int pSSRExeJumpFromToOnSSRExeMainStrategyDaimyoTurn = 0x434CC6; // �֐��͂��̃A�h���X����AOnSSRExeMainStrategyDaimyoTurn�ւƃW�����v���Ă���B
int pSSRExeJumpCallFromToOnSSRExeMainStrategyDaimyoTurn = 0x442850; // ���X������������Call��
int pSSRExeReturnLblFromOnSSRExeMainStrategyDaimyoTurn = 0x434CCB; // �֐����Ō�܂ł����ƁA���̎��sexe���ɒ��ڃW�����v����

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeMainStrategyDaimyoTurn() {
	// �X�^�b�N�ɂ��߂Ă���
	__asm {

		mov iTurnDaimyoPointerOfStrategy, ECX

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeMainStrategyDaimyoTurnExecute();

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

		call pSSRExeJumpCallFromToOnSSRExeMainStrategyDaimyoTurn // ���̏���

		jmp pSSRExeReturnLblFromOnSSRExeMainStrategyDaimyoTurn
	}
}
#pragma warning(default: 4733) // ���[�j���O�̗}������������



char cmdOnSSRExeJumpFromMainStrategyDaimyoTurn[6] = "\xE9";
// ���̖��߂�5�o�C�g�A�Ȍ�̊֐��Ő��܂�閽�߂����v�T�o�C�g�Ȃ̂Łc �Ō�P�g��Ȃ�


// �j�[���j�b�N���������p
void WriteAsmJumperOnSSRExeMainStrategyDaimyoTurn() {

	// �܂��A�h���X�𐔎��Ƃ��Ĉ���
	int iAddress = (int)OnSSRExeMainStrategyDaimyoTurn;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeMainStrategyDaimyoTurn + 5);
	// �T�Ƃ����̂́A0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  �̖��߂ɕK�v�ȃo�C�g���B�v����ɂT�o�C�g�����Ǝ��̃j�[���j�b�N���ߌQ�Ɉړ�����̂��B�����Ă�������̍������W�����v����ۂ̖ړI�i�Ƃ��ė��p�����B
	memcpy(cmdOnSSRExeJumpFromMainStrategyDaimyoTurn + 1, &SubAddress, 4); // +1 ��E9�̎�����4�o�C�g�����������邩��B

	// �\�z�����j�[���j�b�N���߂����sexe�̃������ɏ���������
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeMainStrategyDaimyoTurn), cmdOnSSRExeJumpFromMainStrategyDaimyoTurn, 5, NULL); //5�o�C�g�̂ݏ�������
}

#pragma managed
