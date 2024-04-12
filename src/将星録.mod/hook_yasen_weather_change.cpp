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

#include <windows.h>
#include <string>
#include "output_debug_stream.h"
#include "game_process.h"

using namespace std;

#pragma unmanaged

int getYasenWeather() {
	return *(int*)0x585204;
}

void setYasenWeather(int nWeather) {
	if (0 <= nWeather && nWeather <= 3) {
		*(int*)0x585204 = nWeather;
	}
}





int nYasenWeather = -1;
void OnSSRExeYasenWeatherChangeExecute() {
	OutputDebugStream("�����������̓V��ύX����%d\n", nYasenWeather);

	// �����́u�V�󂪎��ۂɕύX�����������Ă΂�邽�߁A�����ł͏��������Ȃ����Ɓv�B
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
int pSSRExeJumpFromToOnSSRExeYasenWeatherChange = 0x471441; // �֐��͂��̃A�h���X����AOnSSRExeYasenWeatherChange�ւƃW�����v���Ă���B
int pSSRExeReturnLblFromOnSSRExeYasenWeatherChange = 0x471446; // �֐����Ō�܂ł����ƁA���̎��sexe���ɒ��ڃW�����v����

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeYasenWeatherChange() {
	// �X�^�b�N�ɂ��߂Ă���
	__asm {

		mov nYasenWeather, eax  // �����œV�C�̔ԍ����T���Ă���
		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeYasenWeatherChangeExecute();

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

		mov eax, nYasenWeather  // �����œV�C�̔ԍ����㏑��
		MOV DWORD PTR DS : [0x585204] , EAX

		jmp pSSRExeReturnLblFromOnSSRExeYasenWeatherChange
	}
}
#pragma warning(default: 4733) // ���[�j���O�̗}������������



char cmdOnSSRExeJumpFromYasenWeatherChange[6] = "\xE9";
// ���̖��߂�5�o�C�g�A�Ȍ�̊֐��Ő��܂�閽�߂����v�T�o�C�g�Ȃ̂Łc �Ō�P�g��Ȃ�

// �j�[���j�b�N���������p
void WriteAsmJumperOnSSRExeYasenWeatherChange() {

	// �܂��A�h���X�𐔎��Ƃ��Ĉ���
	int iAddress = (int)OnSSRExeYasenWeatherChange;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeYasenWeatherChange + 5);
	// �T�Ƃ����̂́A0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  �̖��߂ɕK�v�ȃo�C�g���B�v����ɂT�o�C�g�����Ǝ��̃j�[���j�b�N���ߌQ�Ɉړ�����̂��B�����Ă�������̍������W�����v����ۂ̖ړI�i�Ƃ��ė��p�����B
	memcpy(cmdOnSSRExeJumpFromYasenWeatherChange + 1, &SubAddress, 4); // +1 ��E9�̎�����4�o�C�g�����������邩��B

	// �\�z�����j�[���j�b�N���߂�TENSHOU.EXE�̃������ɏ���������
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeYasenWeatherChange), cmdOnSSRExeJumpFromYasenWeatherChange, 5, NULL); //5�o�C�g�̂ݏ�������
}

#pragma managed
