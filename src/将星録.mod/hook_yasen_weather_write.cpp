/*
00471430   833D 00525800 00 CMP DWORD PTR DS:[585200],0
00471437   56               PUSH ESI
00471438   8BF1             MOV ESI,ECX
0047143A   74 0A            JE SHORT Nobunaga.00471446
0047143C   E8 2FFAFFFF      CALL Nobunaga.00470E70
00471441   A3 04525800      MOV DWORD PTR DS:[585204],EAX // ����0x585204���V��̒l�B0:�� 1:�� 2:�J 3:��
00471446   8BCE             MOV ECX,ESI
00471448   E8 C3FCFFFF      CALL Nobunaga.00471110
0047144D   83BE 84000000 02 CMP DWORD PTR DS:[ESI+84],2
*/


extern int getYanseWeather();

extern void setYangseWeather(int nWeather);

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


void OnSSRExeYasenWeatherWriteExecute() {
	OutputDebugStream("�����������̓V�󏑂���������%d\n", getYanseWeather());

	// setYangseWeather(3);
	// �������� ���̓V���₢���킹��֐����쐬����Ȃ�΁A������JavaScript�̃R�[���o�b�N�쐬���邱�ƁB
}


/*
00471430   833D 00525800 00 CMP DWORD PTR DS:[585200],0
00471437   56               PUSH ESI
00471438   8BF1             MOV ESI,ECX
0047143A   74 0A            JE SHORT Nobunaga.00471446
0047143C   E8 2FFAFFFF      CALL Nobunaga.00470E70
00471441   A3 04525800      MOV DWORD PTR DS:[585204],EAX // ����0x585204���V��̒l�B0:�� 1:�� 2:�J 3:��
00471446   8BCE             MOV ECX,ESI
00471448   E8 C3FCFFFF      CALL Nobunaga.00471110
0047144D   83BE 84000000 02 CMP DWORD PTR DS:[ESI+84],2
*/
int pSSRExeJumpFromToOnSSRExeYasenWeatherWrite = 0x471448; // �֐��͂��̃A�h���X����AOnSSRExeYasenWeatherWrite�ւƃW�����v���Ă���B
int pSSRExeJumpCallFromToOnSSRExeYasenWeatherWrite = 0x471110; // ���X������������Call��
int pSSRExeReturnLblFromOnSSRExeYasenWeatherWrite = 0x47144D; // �֐����Ō�܂ł����ƁA����TENSHOU.EXE���ɒ��ڃW�����v����

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeYasenWeatherWrite() {
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

	OnSSRExeYasenWeatherWriteExecute();

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

		call pSSRExeJumpCallFromToOnSSRExeYasenWeatherWrite;

		jmp pSSRExeReturnLblFromOnSSRExeYasenWeatherWrite
	}
}
#pragma warning(default: 4733) // ���[�j���O�̗}������������



char cmdOnSSRExeJumpFromYasenWeatherWrite[6] = "\xE9";
// ���̖��߂�5�o�C�g�A�Ȍ�̊֐��Ő��܂�閽�߂����v�T�o�C�g�Ȃ̂Łc �Ō�P�g��Ȃ�

// �j�[���j�b�N���������p
void WriteAsmJumperOnSSRExeYasenWeatherWrite() {

	// �܂��A�h���X�𐔎��Ƃ��Ĉ���
	int iAddress = (int)OnSSRExeYasenWeatherWrite;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeYasenWeatherWrite + 5);
	// �T�Ƃ����̂́A0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  �̖��߂ɕK�v�ȃo�C�g���B�v����ɂT�o�C�g�����Ǝ��̃j�[���j�b�N���ߌQ�Ɉړ�����̂��B�����Ă�������̍������W�����v����ۂ̖ړI�i�Ƃ��ė��p�����B
	memcpy(cmdOnSSRExeJumpFromYasenWeatherWrite + 1, &SubAddress, 4); // +1 ��E9�̎�����4�o�C�g�����������邩��B

	// �\�z�����j�[���j�b�N���߂�TENSHOU.EXE�̃������ɏ���������
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeYasenWeatherWrite), cmdOnSSRExeJumpFromYasenWeatherWrite, 5, NULL); //5�o�C�g�̂ݏ�������
}

#pragma managed
