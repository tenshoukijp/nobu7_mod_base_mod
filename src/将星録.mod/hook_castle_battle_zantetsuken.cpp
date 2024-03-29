/*
004174B8   0F84 1E010000    JE Nobunaga.004175DC
004174BE   8BCB             MOV ECX,EBX
004174C0   E8 FBCAFEFF      CALL Nobunaga.00403FC0
004174C5   85C0             TEST EAX,EAX
004174C7   0F84 0F010000    JE Nobunaga.004175DC
004174CD   68 580E5200      PUSH Nobunaga.00520E58                   ; ASCII "�a�S��"
004174D2   68 D8A55D00      PUSH Nobunaga.005DA5D8                   ; ASCII "�c15���"
*/




#include <windows.h>
#include <string>
#include "data_game_struct.h"
#include "data_bushou_struct.h"
#include "output_debug_stream.h"
#include "game_process.h"
#include "bushou_albedo.h"
#include "usr_custom_mod.h"


using namespace std;


int iZantetsukenAttackBushouID = -1;
static int AttackBushouPtrOfCastleBattleZantetsuken = 0;
static int EspOfCastleBattleZantetsuken = 0;
static int EaxOfCastleBattleZantetsuken = 0;
void OnSSRExeCastleBattleZantetsukenExecute() {
	iZantetsukenAttackBushouID = -1;
	BYTE* pBushouPtr = (BYTE*)(EspOfCastleBattleZantetsuken)+0x54; // �����ɍU�����������|�C���^�������Ă���
	int AttackBushouPtrOfCastleBattleZantetsuken = *((int *)(pBushouPtr));

	int iBushouID = getBushouIDFromBushouPtr((int*)AttackBushouPtrOfCastleBattleZantetsuken);
	iZantetsukenAttackBushouID = iBushouID;
	if (isValidBushouID(iBushouID)) {
		OutputDebugStream("����%d", iBushouID);
		OutputDebugStream("�������a�S��������\n");
		OutputDebugStream(getBushou����FromBushouID(iBushouID) + "\n");

		try {
			int �a�S������ = EaxOfCastleBattleZantetsuken;
			// C#��dll�Ń��[�U�[���J�X�^�������t�@�C�����w�肷�邩������Ȃ��B
			System::Collections::Generic::Dictionary<System::String^, System::Object^>^ dic = gcnew System::Collections::Generic::Dictionary<System::String^, System::Object^>(5);
			dic->Add("�U�������ԍ�", iBushouID);
			dic->Add("�U���^�C�v", "�a�S��");
			dic->Add("�h��^�C�v", "��");
			dic->Add("�a�S������", �a�S������);
			System::Collections::Generic::Dictionary<System::String^, System::Object^>^ ret = InvokeUserMethod("on�ď��_���[�W���莞", dic);
			if (ret != nullptr) {
				if (ret->ContainsKey("����")) {
					int override�a�S������ = (int)ret["�a�S������"];
					EaxOfCastleBattleZantetsuken = override�a�S������;
				}
			}
		}
		catch (System::Exception^) {
			OutputDebugStream("on�ď��_���[�W���莞�ŗ�O���������܂����B\n");
		}

		if (getBushou����FromBushouID(iBushouID) == getArubedoSeiMei()) {
			OutputDebugStream("�������a�S1, %d������\n", EaxOfCastleBattleZantetsuken);
			// �a�S���̋�������
			EaxOfCastleBattleZantetsuken = 1;
		}
		else {
			OutputDebugStream("�������a�S0, %d������\n", EaxOfCastleBattleZantetsuken);
		}
	}
}

#pragma unmanaged

/*
004174A1   0F85 F0000000    JNZ Nobunaga.00417597
004174A7   8B4424 54        MOV EAX,DWORD PTR SS:[ESP+54] // �����ɍU�����������|�C���^�������Ă���
004174AB   50               PUSH EAX
004174AC   B9 280F5400      MOV ECX,Nobunaga.00540F28
004174B1   E8 7A1BFFFF      CALL Nobunaga.00409030
004174B6   85C0             TEST EAX,EAX
004174B8   0F84 1E010000    JE Nobunaga.004175DC
004174BE   8BCB             MOV ECX,EBX
004174C0   E8 FBCAFEFF      CALL Nobunaga.00403FC0
004174C5   85C0             TEST EAX,EAX
004174C7   0F84 0F010000    JE Nobunaga.004175DC
004174CD   68 580E5200      PUSH Nobunaga.00520E58                   ; ASCII "�a�S��"
004174D2   68 D8A55D00      PUSH Nobunaga.005DA5D8                   ; ASCII "�c15���"
*/


int pSSRExeJumpFromToOnSSRExeCastleBattleZantetsuken = 0x4174C0; // �֐��͂��̃A�h���X����AOnSSRExeCastleBattleZantetsuken�ւƃW�����v���Ă���B
int pSSRExeJumpCallFromToOnSSRExeCastleBattleZantetsuken = 0x403FC0; // ���X������������Call��
int pSSRExeReturnLblFromOnSSRExeCastleBattleZantetsuken = 0x4174C5; // �֐����Ō�܂ł����ƁA����TENSHOU.EXE���ɒ��ڃW�����v����

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeCastleBattleZantetsuken() {
	// �X�^�b�N�ɂ��߂Ă���
	__asm {
		mov EspOfCastleBattleZantetsuken, esp

		call pSSRExeJumpCallFromToOnSSRExeCastleBattleZantetsuken

		mov EaxOfCastleBattleZantetsuken, eax

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeCastleBattleZantetsukenExecute();

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

		mov eax, EaxOfCastleBattleZantetsuken

		jmp pSSRExeReturnLblFromOnSSRExeCastleBattleZantetsuken
	}
}
#pragma warning(default: 4733) // ���[�j���O�̗}������������



char cmdOnSSRExeJumpFromCastleBattleZantetsuken[6] = "\xE9";
// ���̖��߂�5�o�C�g�A�Ȍ�̊֐��Ő��܂�閽�߂����v�T�o�C�g�Ȃ̂Łc �Ō�P�g��Ȃ�


// �j�[���j�b�N���������p
void WriteAsmJumperOnSSRExeCastleBattleZantetsuken() {

	// �܂��A�h���X�𐔎��Ƃ��Ĉ���
	int iAddress = (int)OnSSRExeCastleBattleZantetsuken;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeCastleBattleZantetsuken + 5);
	// �T�Ƃ����̂́A0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  �̖��߂ɕK�v�ȃo�C�g���B�v����ɂT�o�C�g�����Ǝ��̃j�[���j�b�N���ߌQ�Ɉړ�����̂��B�����Ă�������̍������W�����v����ۂ̖ړI�i�Ƃ��ė��p�����B
	memcpy(cmdOnSSRExeJumpFromCastleBattleZantetsuken + 1, &SubAddress, 4); // +1 ��E9�̎�����4�o�C�g�����������邩��B

	// �\�z�����j�[���j�b�N���߂�TENSHOU.EXE�̃������ɏ���������
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeCastleBattleZantetsuken), cmdOnSSRExeJumpFromCastleBattleZantetsuken, 5, NULL); //5�o�C�g�̂ݏ�������
}

#pragma managed
