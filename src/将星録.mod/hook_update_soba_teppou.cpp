/*
004C47CA   50               PUSH EAX
004C47CB   51               PUSH ECX
004C47CC   E8 DFBCF7FF      CALL Nobunaga.004404B0
004C47D1   83C4 08          ADD ESP,8
004C47D4   8946 42          MOV DWORD PTR DS:[ESI+42],EAX
004C47D7   5E               POP ESI
004C47D8   C2 0400          RETN 4

*/





#include <windows.h>
#include "data_game_struct.h"
#include "output_debug_stream.h"
#include "game_process.h"
#include "on_event.h"
#include "usr_custom_mod.h"


using namespace std;


int iUpdateSobaTeppouEAX = -1;
void OnSSRExeUpdateSobaTeppouExecute() {
	OutputDebugStream("���������S�C���ꂪ�X�V����܂���!!!:%d\n", iUpdateSobaTeppouEAX);
	onUpdateSobaTeppou(iUpdateSobaTeppouEAX);

	nb7�^�[�����.����S�C = iUpdateSobaTeppouEAX; // �ǂ������ɏ����^�{�̏����ő������邽�߁A�����ő�����Ă����B

	try {

		System::Collections::Generic::Dictionary<System::String^, System::Object^>^ dic = gcnew System::Collections::Generic::Dictionary<System::String^, System::Object^>(5);
		dic->Add("����", nb7�^�[�����.���ꕺ��);
		dic->Add("�R�n", nb7�^�[�����.����R�n);
		dic->Add("�S�C", nb7�^�[�����.����S�C);
		System::Collections::Generic::Dictionary<System::String^, System::Object^>^ ret = InvokeUserMethod("on����v����", dic);
		if (ret != nullptr) {
			if (ret->ContainsKey("����")) {
				nb7�^�[�����.���ꕺ�� = (int)(ret["����"]);
			}
			if (ret->ContainsKey("�R�n")) {
				nb7�^�[�����.����R�n = (int)(ret["�R�n"]);
			}
			if (ret->ContainsKey("�S�C")) {
				nb7�^�[�����.����S�C = (int)(ret["�S�C"]);
			}
		}

		iUpdateSobaTeppouEAX = nb7�^�[�����.����S�C; // ���ꂩ�珫���^�{�̂ł͒l�̑�����s����̂ŁA���q�����킹�Ă����B
	}
	catch (System::Exception^) {
		OutputDebugStream("on����v���� �ŃG���[���������܂����B");
	}

}

#pragma unmanaged

/*
004C47CA   50               PUSH EAX
004C47CB   51               PUSH ECX
004C47CC   E8 DFBCF7FF      CALL Nobunaga.004404B0
004C47D1   83C4 08          ADD ESP,8
004C47D4   8946 42          MOV DWORD PTR DS:[ESI+42],EAX
004C47D7   5E               POP ESI
004C47D8   C2 0400          RETN 4

*/



int pSSRExeJumpFromToOnSSRExeUpdateSobaTeppou = 0x4C47CC; // �֐��͂��̃A�h���X����AOnSSRExeUpdateSobaTeppou�ւƃW�����v���Ă���B
int pSSRExeJumpCallFromToOnSSRExeUpdateSobaTeppou = 0x4404B0; // ���X������������Call��
int pSSRExeReturnLblFromOnSSRExeUpdateSobaTeppou = 0x4C47D1; // �֐����Ō�܂ł����ƁA���̎��sexe���ɒ��ڃW�����v����

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeUpdateSobaTeppou() {
	// �X�^�b�N�ɂ��߂Ă���
	__asm {

		call pSSRExeJumpCallFromToOnSSRExeUpdateSobaTeppou // ���̏���

		mov iUpdateSobaTeppouEAX, EAX

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeUpdateSobaTeppouExecute();

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

		mov EAX, iUpdateSobaTeppouEAX

		jmp pSSRExeReturnLblFromOnSSRExeUpdateSobaTeppou
	}
}
#pragma warning(default: 4733) // ���[�j���O�̗}������������



char cmdOnSSRExeJumpFromUpdateSobaTeppou[6] = "\xE9";
// ���̖��߂�5�o�C�g�A�Ȍ�̊֐��Ő��܂�閽�߂����v�T�o�C�g�Ȃ̂Łc �Ō�P�g��Ȃ�


// �j�[���j�b�N���������p
void WriteAsmJumperOnSSRExeUpdateSobaTeppou() {

	// �܂��A�h���X�𐔎��Ƃ��Ĉ���
	int iAddress = (int)OnSSRExeUpdateSobaTeppou;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeUpdateSobaTeppou + 5);
	// �T�Ƃ����̂́A0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  �̖��߂ɕK�v�ȃo�C�g���B�v����ɂT�o�C�g�����Ǝ��̃j�[���j�b�N���ߌQ�Ɉړ�����̂��B�����Ă�������̍������W�����v����ۂ̖ړI�i�Ƃ��ė��p�����B
	memcpy(cmdOnSSRExeJumpFromUpdateSobaTeppou + 1, &SubAddress, 4); // +1 ��E9�̎�����4�o�C�g�����������邩��B

	// �\�z�����j�[���j�b�N���߂�TENSHOU.EXE�̃������ɏ���������
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeUpdateSobaTeppou), cmdOnSSRExeJumpFromUpdateSobaTeppou, 5, NULL); //5�o�C�g�̂ݏ�������
}

#pragma managed
