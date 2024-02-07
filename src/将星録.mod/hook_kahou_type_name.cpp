/*
00523F44  8D 81 96 D8 00 00 00 00 92 BF 95 69 00 00 00 00  ����....���i....
00523F54  8F 5C 8E 9A 89 CB 00 00 8E 5A 94 D5 00 00 00 00  �\����..�Z��....
00523F64  93 EC 94 D8 8E 9E 8C 76 00 00 00 00 97 85 90 6A  ��؎��v....���j
00523F74  94 D5 00 00 92 6E 90 7D 00 00 00 00 8A 47 89 E6  ��..�n�}....�G��
00523F84  00 00 00 00 8F A4 8B C6 8F 91 00 00 8C 52 8B 4C  ....���Ə�..�R�L
00523F94  95 A8 8C EA 00 00 00 00 95 A7 8B B3 8F 91 00 00  ����....������..
00523FA4  95 B6 8A 77 8F 91 00 00 8F 40 8B B3 8F 91 00 00  ���w��..�@����..
00523FB4  97 F0 8E 6A 8F 91 00 00 8C 9A 92 7A 8F 91 00 00  ���j��..���z��..
00523FC4  8D 7A 8F 70 8F 91 00 00 8A 4F 8C F0 8F 91 00 00  �z�p��..�O����..
00523FD4  94 5F 90 AD 8F 91 00 00 92 6D 8E AF 8F 91 00 00  �_����..�m����..
00523FE4  94 45 8F 70 8F 91 00 00 88 E3 8F 70 8F 91 00 00  �E�p��..��p��..
00523FF4  95 BA 96 40 8F 91 00 00 96 43 8F 70 8F 91 00 00  ���@��..�C�p��..
00524004  94 6E 8F 70 8F 91 00 00 8C 95 8F 70 8F 91 00 00  �n�p��..���p��..
00524014  92 5A 93 9B 00 00 00 00 96 BC 94 6E 00 00 00 00  �Z��....���n....
00524024  95 BA 91 95 95 69 00 00 95 90 8A ED 00 00 00 00  �����i..����....
00524034  92 83 93 B9 93 B9 8B EF                          ��������....

*/

/*
��̃|�C���^�̔z��
0053A8B8  34 40 52 00 2C 40 52 00 24 40 52 00 1C 40 52 00  4@R.,@R.$@R.@R.
0053A8C8  14 40 52 00 0C 40 52 00 04 40 52 00 FC 3F 52 00  @R..@R.@R.�ER.
0053A8D8  F4 3F 52 00 EC 3F 52 00 E4 3F 52 00 DC 3F 52 00  �ER.�ER.�ER.�?R.
0053A8E8  D4 3F 52 00 CC 3F 52 00 C4 3F 52 00 BC 3F 52 00  �?R.�?R.�?R.�?R.
0053A8F8  B4 3F 52 00 AC 3F 52 00 A4 3F 52 00 9C 3F 52 00  �?R.�?R.�?R.�ER.
0053A908  90 3F 52 00 88 3F 52 00 80 3F 52 00 78 3F 52 00  �ER.�ER.�?R.x?R.
0053A918  70 3F 52 00 64 3F 52 00 5C 3F 52 00 54 3F 52 00  p?R.d?R.\?R.T?R.
0053A928  4C 3F 52 00 44 3F 52 00                          L?R.D?R.

*/

/*
0047C9C0  /$ 51             PUSH ECX
0047C9C1  |. 56             PUSH ESI
0047C9C2  |. 8BF1           MOV ESI,ECX
0047C9C4  |. 57             PUSH EDI
0047C9C5  |. 8D4C24 08      LEA ECX,DWORD PTR SS:[ESP+8]

*/

/*
��̃|�C���^�𗘗p���Ă���ӏ���1�ӏ������B���̎�ECX�́A�Y���̉ƕ���ւ̉ƕ�|�C���^�������Ă���B
EAX�͂������ƕ��ޔԍ�
0047CA24  |. 0F8D E3010000          JGE Nobunaga.0047CC0D
0047CA2A  |. 8B3485 B8A85300        MOV ESI,DWORD PTR DS:[EAX*4+53A8B8]                         ;  Nobunaga.00523F4C
0047CA31  |. E9 DD010000            JMP Nobunaga.0047CC13

*/



#include <windows.h>
#include <string>
#include <cstdlib>
#include <memory>
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
#include "mng_�ƕ��.h"


using namespace std;


static int ECXOfKahouTypeName = -1;
static int EAXOfKahouTypeName = -1;
static int ESIOfKahouTypeName = -1;

struct TKahouTypeName {
	char name[9]; // �S�p4�����܂�
};

//TKahouTypeName listKahouType[�ő吔::�ƕ���::�z��] = { 0 };
std::unique_ptr<TKahouTypeName[]> listKahouType(new TKahouTypeName[�ő吔::�ƕ���::�z��]());

void OnSSRExeKahouTypeNameExecute() {

	int iKahouID = getKahouIDFromKahouPtr((int*)ECXOfKahouTypeName);
	if (isValidKahouID(iKahouID)) {

		// �ƕ�̃f�t�H���g�̎�ޖ��𓾂�
		int iKahouType = nb7�ƕ���[iKahouID].���;
		int iKahouTypeNameLocation = 4 * iKahouType + 0x53A8B8;
		int pKahouName = *((int*)iKahouTypeNameLocation);
		// OutputDebugStream("��ޖ���%s\n", pKahouName);

		// �����200�̃o�b�t�@�[�Ɋi�[���Ă���
		strcpy_s(listKahouType[iKahouID].name, (char*)pKahouName);

		// �ƕ��ޖ����擾����
		// OutputDebugStream("�ƕ�:"s + nb7�ƕ���[iKahouID].�ƕ�);
		// OutputDebugStream("�ꏊ��%x����", ESIOfKahouTypeName);
		
		// �����������őΏۂ̉ƕ�̎�ޖ���ύX����
		int iKahouImageType = nb7�ƕ���[iKahouID].�摜;
		if (iKahouImageType == ��::�ƕ�::�摜::�) {
			strcpy_s(listKahouType[iKahouID].name, "�");
		}
		else if (iKahouImageType == ��::�ƕ�::�摜::����) {
			strcpy_s(listKahouType[iKahouID].name, "����");
		}
		else if (iKahouImageType == ��::�ƕ�::�摜::�w�H�D) {
			strcpy_s(listKahouType[iKahouID].name, "�w�H�D");
		}
		else if (iKahouImageType == ��::�ƕ�::�摜::��) {
			strcpy_s(listKahouType[iKahouID].name, "��");
		}
		else if (iKahouImageType == ��::�ƕ�::�摜::��) {
			strcpy_s(listKahouType[iKahouID].name, "��");
		}
		else if (iKahouImageType == ��::�ƕ�::�摜::�璹) {
			strcpy_s(listKahouType[iKahouID].name, "�璹");
		}
		else if (iKahouImageType == ��::�ƕ�::�摜::�ԓ�) {
			strcpy_s(listKahouType[iKahouID].name, "�ԓ�");
		}
		else if (iKahouImageType == ��::�ƕ�::�摜::����) {
			strcpy_s(listKahouType[iKahouID].name, "����");
		}
		else if (iKahouImageType == ��::�ƕ�::�摜::����) {
			strcpy_s(listKahouType[iKahouID].name, "����");
		}
		else if (iKahouImageType == ��::�ƕ�::�摜::���q) {
			strcpy_s(listKahouType[iKahouID].name, "���q");
		}
		else if (iKahouImageType == ��::�ƕ�::�摜::����) {
			strcpy_s(listKahouType[iKahouID].name, "����");
		}
		else if (iKahouImageType == ��::�ƕ�::�摜::�m�y��) {
			strcpy_s(listKahouType[iKahouID].name, "�m�y��");
		}
		else if (iKahouImageType == ��::�ƕ�::�摜::���ዾ) {
			strcpy_s(listKahouType[iKahouID].name, "���ዾ");
		}
		else if (iKahouImageType == ��::�ƕ�::�摜::�V�Y��) {
			strcpy_s(listKahouType[iKahouID].name, "�V�Y��");
		}
		else if (iKahouImageType == ��::�ƕ�::�摜::����) {
			strcpy_s(listKahouType[iKahouID].name, "����");
		}

		// ������������JavaScriptMod����ʂȎ�ނ̒u���������s��

		// �o���f�B�b�V���Ȃ畀
		if (nb7�ƕ���[iKahouID].�ƕ� == "�o����������"s) {
			strcpy_s(listKahouType[iKahouID].name, "��");
		}
		else if (nb7�ƕ���[iKahouID].�ƕ� == "�M�F�G�H�I�v"s) {
			strcpy_s(listKahouType[iKahouID].name, "���");
		}
		else if (nb7�ƕ���[iKahouID].�ƕ� == "������������"s) {
			strcpy_s(listKahouType[iKahouID].name, "�");
		}

		// �Ώۂ̖��O�ւ̃|�C���^�������Ă����B
		ESIOfKahouTypeName = (int)(listKahouType[iKahouID].name);
	}

}

#pragma unmanaged

/*
��̃|�C���^�𗘗p���Ă���ӏ���1�ӏ������B���̎�ECX�́A�Y���̉ƕ���ւ̉ƕ�|�C���^�������Ă���B
EAX�͂������ƕ��ޔԍ�
0047CA24  |. 0F8D E3010000          JGE Nobunaga.0047CC0D
0047CA2A  |. 8B3485 B8A85300        MOV ESI,DWORD PTR DS:[EAX*4+53A8B8]                         ;  Nobunaga.00523F4C
0047CA31  |. E9 DD010000            JMP Nobunaga.0047CC13

*/

int pSSRExeJumpFromToOnSSRExeKahouTypeName = 0x47CA2A; // �֐��͂��̃A�h���X����AOnSSRExeKahouTypeName�ւƃW�����v���Ă���B
int pSSRExeReturnLblFromOnSSRExeKahouTypeName = 0x47CA31; // �֐����Ō�܂ł����ƁA����TENSHOU.EXE���ɒ��ڃW�����v����

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeKahouTypeName() {
	// �X�^�b�N�ɂ��߂Ă���
	__asm {

		MOV ESI, DWORD PTR DS : [EAX * 4 + 0x53A8B8]

		mov ECXOfKahouTypeName, ecx
		mov EAXOfKahouTypeName, eax
		mov ESIOfKahouTypeName, esi
		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeKahouTypeNameExecute();

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

		MOV ESI, ESIOfKahouTypeName

		jmp pSSRExeReturnLblFromOnSSRExeKahouTypeName
	}
}
#pragma warning(default: 4733) // ���[�j���O�̗}������������



char cmdOnSSRExeJumpFromKahouTypeName[8] = "\xE9\x90\x90\x90\x90\x90\x90";
// ���̖��߂�5�o�C�g�A�Ȍ�̊֐��Ő��܂�閽�߂����v�T�o�C�g�Ȃ̂Łc �Ō�P�g��Ȃ�


// �j�[���j�b�N���������p
void WriteAsmJumperOnSSRExeKahouTypeName() {

	// �܂��A�h���X�𐔎��Ƃ��Ĉ���
	int iAddress = (int)OnSSRExeKahouTypeName;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeKahouTypeName + 5);
	// �T�Ƃ����̂́A0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  �̖��߂ɕK�v�ȃo�C�g���B�v����ɂT�o�C�g�����Ǝ��̃j�[���j�b�N���ߌQ�Ɉړ�����̂��B�����Ă�������̍������W�����v����ۂ̖ړI�i�Ƃ��ė��p�����B
	memcpy(cmdOnSSRExeJumpFromKahouTypeName + 1, &SubAddress, 4); // +1 ��E9�̎�����4�o�C�g�����������邩��B

	// �\�z�����j�[���j�b�N���߂�TENSHOU.EXE�̃������ɏ���������
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeKahouTypeName), cmdOnSSRExeJumpFromKahouTypeName, 7, NULL); //7�o�C�g�̂ݏ�������
}

#pragma managed
