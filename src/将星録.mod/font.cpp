#include <windows.h>
#include <winuser.h>
#include <stdio.h>

#include "window.h"
#include "process.h"


/*
005056B5   68 04EE5300      PUSH Nobunaga.0053EE04
005056BA   53               PUSH EBX
005056BB   53               PUSH EBX
005056BC   53               PUSH EBX
005056BD   53               PUSH EBX
005056BE   68 80000000      PUSH 80
005056C3   53               PUSH EBX
005056C4   53               PUSH EBX
005056C5   53               PUSH EBX
005056C6   53               PUSH EBX
005056C7   53               PUSH EBX
005056C8   53               PUSH EBX
005056C9   6A 08            PUSH 8
005056CB   6A F0            PUSH -10
 */

char buffferFontName[50] = "�l�r ����";
int pszFontAddress = (int)(&buffferFontName[0]);

extern void WriteAsmJumperOnNb7FontnameAddressPush();
void onFontInitialize() {
    OutputDebugString("onFontInitialize\r\n");
    strcpy_s((char*)0x53EE04, 11, "���� ����");

	// WriteAsmJumperOnNb7FontnameAddressPush();
}


/*
005056B5   68 04EE5300      PUSH Nobunaga.0053EE04
005056BA   53               PUSH EBX
005056BB   53               PUSH EBX
005056BC   53               PUSH EBX
005056BD   53               PUSH EBX
005056BE   68 80000000      PUSH 80
005056C3   53               PUSH EBX
005056C4   53               PUSH EBX
005056C5   53               PUSH EBX
005056C6   53               PUSH EBX
005056C7   53               PUSH EBX
005056C8   53               PUSH EBX
005056C9   6A 08            PUSH 8
005056CB   6A F0            PUSH -10
 */

void onNB7FontnameAddressPushExecute() {
	OutputDebugString("�t�H���g���A�h���X��ύX���܂���");
}

int pNB7JumpFromToOnNB7FontnameAddressPush = 0x5056B5; // �֐��͂��̃A�h���X����AonNB7FontnameAddressPush�ւƃW�����v���Ă���B
int pNB7ReturnLblFromOnNB7FontnameAddressPush = 0x5056BA; // �֐����Ō�܂ł����ƁA���̃A�h���X�ɒ��ږ߂�Ƃ����Ȃ�Ƃ��댯�ȍs��w

__declspec(naked) void WINAPI onNB7FontnameAddressPush() {
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

	// �t�H���g�����v������鎞
	onNB7FontnameAddressPushExecute();

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

		push 0x53EE04; // ���� PUSH Nobunaga.0053EE04 ����

		jmp pNB7ReturnLblFromOnNB7FontnameAddressPush; // ���̖��߂ɖ߂�
	}
}

char cmdOBN7JumpFromNB7FontnameAddressPush[6] = "\xE9";
// ���̖��߂�5�o�C�g�A�Ȍ�̊֐��Ő��܂�閽�߂����v�T�o�C�g�Ȃ̂Łc �Ō�P�g��Ȃ�


// �j�[���j�b�N���������p
void WriteAsmJumperOnNb7FontnameAddressPush() {
	// �܂��A�h���X�𐔎��Ƃ��Ĉ���
	int iAddress = (int)onNB7FontnameAddressPush;
	int SubAddress = iAddress - (pNB7JumpFromToOnNB7FontnameAddressPush + 5);
	// �T�Ƃ����̂́A0046C194  -E9 ????????  JMP Mod.onNB7FontnameAddressPush  �̖��߂ɕK�v�ȃo�C�g���B�v����ɂT�o�C�g�����Ǝ��̃j�[���j�b�N���ߌQ�Ɉړ�����̂��B�����Ă�������̍������W�����v����ۂ̖ړI�i�Ƃ��ė��p�����B
	memcpy(cmdOBN7JumpFromNB7FontnameAddressPush + 1, &SubAddress, 4); // +1 ��E9�̎�����4�o�C�g�����������邩��B

	// �\�z�����j�[���j�b�N���߂�TENSHOU.EXE�̃������ɏ���������
	BOOL ret = WriteProcessMemory(hCurrentProcess, (LPVOID)(pNB7JumpFromToOnNB7FontnameAddressPush), cmdOBN7JumpFromNB7FontnameAddressPush, 5, NULL); //5�o�C�g�̂ݏ�������
	if (ret) {
		OutputDebugString("������������\n");
	}
	else {
		OutputDebugString("�����������s\n");
	}
}


