/*
0045F1A2   B9 380F5800      MOV ECX,Nobunaga.00580F38
0045F1A7   E8 E44D0000      CALL Nobunaga.00463F90								// �� ���ꂪ���s�����Ə����ݒ��ʂ��\�������B
0045F1AC   E8 9FF40300      CALL Nobunaga.0049E650
0045F1B1   B9 80DE5D00      MOV ECX,Nobunaga.005DDE80                              ; ASCII "�xR"
0045F1B6   E8 B5A40500      CALL Nobunaga.004B9670
0045F1BB   833D 80E55D00 00 CMP DWORD PTR DS:[5DE580],0
0045F1C2   74 09            JE SHORT Nobunaga.0045F1CD

*/




#include <windows.h>
#include "output_debug_stream.h"
#include "game_process.h"


using namespace std;

extern void onInitialGameMenu();

#pragma unmanaged

void OnSSRExeInitalGameSettingsExecute() {
	OutputDebugStream("�������������(�t�b�N)������\n");
	onInitialGameMenu();
}

/*
0045F1A2   B9 380F5800      MOV ECX,Nobunaga.00580F38
0045F1A7   E8 E44D0000      CALL Nobunaga.00463F90								// �� ���ꂪ���s�����Ə����ݒ��ʂ��\�������B
0045F1AC   E8 9FF40300      CALL Nobunaga.0049E650
0045F1B1   B9 80DE5D00      MOV ECX,Nobunaga.005DDE80                              ; ASCII "�xR"
0045F1B6   E8 B5A40500      CALL Nobunaga.004B9670
0045F1BB   833D 80E55D00 00 CMP DWORD PTR DS:[5DE580],0
0045F1C2   74 09            JE SHORT Nobunaga.0045F1CD

*/


int pSSRExeJumpFromToOnSSRExeInitalGameSettings = 0x45F1A7; // �֐��͂��̃A�h���X����AOnSSRExeInitalGameSettings�ւƃW�����v���Ă���B
int pSSRExeJumpCallFromToOnSSRExeInitalGameSettings = 0x463F90; // ���X������������Call��
int pSSRExeReturnLblFromOnSSRExeInitalGameSettings = 0x45F1AC; // �֐����Ō�܂ł����ƁA����TENSHOU.EXE���ɒ��ڃW�����v����

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeInitalGameSettings() {
	// �X�^�b�N�ɂ��߂Ă���
	__asm {

		call pSSRExeJumpCallFromToOnSSRExeInitalGameSettings // ���̏���

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeInitalGameSettingsExecute();

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

		jmp pSSRExeReturnLblFromOnSSRExeInitalGameSettings
	}
}
#pragma warning(default: 4733) // ���[�j���O�̗}������������



char cmdOnSSRExeJumpFromInitalGameSettings[6] = "\xE9";
// ���̖��߂�5�o�C�g�A�Ȍ�̊֐��Ő��܂�閽�߂����v�T�o�C�g�Ȃ̂Łc �Ō�P�g��Ȃ�


// �j�[���j�b�N���������p
void WriteAsmJumperOnSSRExeInitalGameSettings() {

	// �܂��A�h���X�𐔎��Ƃ��Ĉ���
	int iAddress = (int)OnSSRExeInitalGameSettings;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeInitalGameSettings + 5);
	// �T�Ƃ����̂́A0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  �̖��߂ɕK�v�ȃo�C�g���B�v����ɂT�o�C�g�����Ǝ��̃j�[���j�b�N���ߌQ�Ɉړ�����̂��B�����Ă�������̍������W�����v����ۂ̖ړI�i�Ƃ��ė��p�����B
	memcpy(cmdOnSSRExeJumpFromInitalGameSettings + 1, &SubAddress, 4); // +1 ��E9�̎�����4�o�C�g�����������邩��B

	// �\�z�����j�[���j�b�N���߂�TENSHOU.EXE�̃������ɏ���������
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeInitalGameSettings), cmdOnSSRExeJumpFromInitalGameSettings, 5, NULL); //5�o�C�g�̂ݏ�������
}

#pragma managed
