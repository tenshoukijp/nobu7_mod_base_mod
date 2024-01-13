/*
EAX 00000800
ECX 00563C48 ASCII "�ɑ�"
EDX 005DC328 ASCII "���R"
EBX 000000C8
ESP 0019FC68 ASCII "�NM"
EBP 00000000
ESI 00563C48 ASCII "�ɑ�"
EDI 005F0310 Nobunaga.005F0310
EIP 0041ECBC Nobunaga.0041ECBC

ESI���������̊Y�������ւ̃|�C���^
0041ECB6   66:A1 9C865300   MOV AX,WORD PTR DS:[53869C]
0041ECBC   66:0981 A0000000 OR WORD PTR DS:[ECX+A0],AX
0041ECC3   833D 40235400 00 CMP DWORD PTR DS:[542340],0
0041ECCA   75 06            JNZ SHORT Nobunaga.0041ECD2
0041ECCC   8079 0E 00       CMP BYTE PTR DS:[ECX+E],0
0041ECD0  ^74 E1            JE SHORT Nobunaga.0041ECB3
0041ECD2   66:8B81 A0000000 MOV AX,WORD PTR DS:[ECX+A0]
0041ECD9   66:2305 9C865300 AND AX,WORD PTR DS:[53869C]
0041ECE0   66:F7D8          NEG AX
0041ECE3   1BC0             SBB EAX,EAX
0041ECE5   F7D8             NEG EAX
0041ECE7   C3               RETN
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

static int iBushouKoudouzumiESI = -1;
void OnSSRExeBushouKoudouzumiExecute() {

	int iBushouID = getBushouIDFromBushouPtr((int *)iBushouKoudouzumiESI);
	if (isValidBushouID(iBushouID)) {
		// �܂��u���G�v�͂��̃t�b�N��ʉ߂������Ƃ��Ȃ�
		OutputDebugStream(getBushou����FromBushouID(iBushouID) + "�A�͍s���ς݂̃t�b�N��ʉ߂��܂���\n");

		// �A���x�h�̍s���J�E���^�����炷
		decreaseAlbedoKoudouCounter(iBushouID);
	}
}


/*
EAX 00000800
ECX 00563C48 ASCII "�ɑ�"
EDX 005DC328 ASCII "���R"
EBX 000000C8
ESP 0019FC68 ASCII "�NM"
EBP 00000000
ESI 00563C48 ASCII "�ɑ�"
EDI 005F0310 Nobunaga.005F0310
EIP 0041ECBC Nobunaga.0041ECBC

ESI���������̊Y�������ւ̃|�C���^
0041ECB6   66:A1 9C865300   MOV AX,WORD PTR DS:[53869C]
0041ECBC   66:0981 A0000000 OR WORD PTR DS:[ECX+A0],AX   �� ���̍s�̏�������
0041ECC3   833D 40235400 00 CMP DWORD PTR DS:[542340],0
0041ECCA   75 06            JNZ SHORT Nobunaga.0041ECD2
0041ECCC   8079 0E 00       CMP BYTE PTR DS:[ECX+E],0
0041ECD0  ^74 E1            JE SHORT Nobunaga.0041ECB3
0041ECD2   66:8B81 A0000000 MOV AX,WORD PTR DS:[ECX+A0]
0041ECD9   66:2305 9C865300 AND AX,WORD PTR DS:[53869C]
0041ECE0   66:F7D8          NEG AX
0041ECE3   1BC0             SBB EAX,EAX
0041ECE5   F7D8             NEG EAX
0041ECE7   C3               RETN
*/



int pSSRExeJumpFromToOnSSRExeBushouKoudouzumi = 0x41ECBC; // �֐��͂��̃A�h���X����AOnSSRExeBushouKoudouzumi�ւƃW�����v���Ă���B
int pSSRExeReturnLblFromOnSSRExeBushouKoudouzumi = 0x41ECC3; // �֐����Ō�܂ł����ƁA����TENSHOU.EXE���ɒ��ڃW�����v����

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeBushouKoudouzumi() {
	// �X�^�b�N�ɂ��߂Ă���
	__asm {

		mov iBushouKoudouzumiESI, ESI

		OR WORD PTR DS: [ECX + 0xA0] , AX // �s���ς݂𗧂Ă�

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeBushouKoudouzumiExecute();

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

		jmp pSSRExeReturnLblFromOnSSRExeBushouKoudouzumi
	}
}
#pragma warning(default: 4733) // ���[�j���O�̗}������������



char cmdOnSSRExeJumpFromBushouKoudouzumi[6] = "\xE9";
// ���̖��߂�5�o�C�g�A�Ȍ�̊֐��Ő��܂�閽�߂����v�T�o�C�g�Ȃ̂Łc �Ō�P�g��Ȃ�


// �j�[���j�b�N���������p
void WriteAsmJumperOnSSRExeBushouKoudouzumi() {

	// �܂��A�h���X�𐔎��Ƃ��Ĉ���
	int iAddress = (int)OnSSRExeBushouKoudouzumi;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeBushouKoudouzumi + 5);
	// �T�Ƃ����̂́A0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  �̖��߂ɕK�v�ȃo�C�g���B�v����ɂT�o�C�g�����Ǝ��̃j�[���j�b�N���ߌQ�Ɉړ�����̂��B�����Ă�������̍������W�����v����ۂ̖ړI�i�Ƃ��ė��p�����B
	memcpy(cmdOnSSRExeJumpFromBushouKoudouzumi + 1, &SubAddress, 4); // +1 ��E9�̎�����4�o�C�g�����������邩��B

	// �\�z�����j�[���j�b�N���߂�TENSHOU.EXE�̃������ɏ���������
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeBushouKoudouzumi), cmdOnSSRExeJumpFromBushouKoudouzumi, 5, NULL); //5�o�C�g�̂ݏ�������
}

#pragma managed
