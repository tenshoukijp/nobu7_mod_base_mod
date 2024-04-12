/*
004171D4   E8 B7B8FEFF      CALL Nobunaga.00402A90
004171D9   50               PUSH EAX                                  ���̎���EAX���U�����̌�����̕����B��������s������AECX+8�̃A�h���X�� EAX�̒l�Ɠ����l�����邱�ƁB
004171DA   55               PUSH EBP
004171DB   68 180E5200      PUSH Nobunaga.00520E18                   ; ASCII "�U������ : %d ---> %d
�h�䋒�_ : %d ---> %d"
004171E0   68 D8A55D00      PUSH Nobunaga.005DA5D8                   ; ASCII "  ���q��  1490"
004171E5   E8 8DB50E00      CALL Nobunaga.00502777
004171EA   83C4 18          ADD ESP,18
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


extern int iCastleBattleButaishoutotsuAttackBushouID;


static int ECXOfCastleBattleButaisyoutotsuAttackDamage = 0;
static int EAXOfCastleBattleButaisyoutotsuAttackDamage = 0;  // ���̎���EAX���U�����̌�����̕����B
void OnSSRExeCastleBattleButaisyoutotsuAttackDamageExecute() {
	int* pRemainHeisuPtr = (int*)((BYTE*)(ECXOfCastleBattleButaisyoutotsuAttackDamage)+0x8); // �����ɍU�����������|�C���^�������Ă���

	int iBushouID = iCastleBattleButaishoutotsuAttackBushouID;

	if (isValidBushouID(iBushouID)) {

		try {
			int �U���������� = *pRemainHeisuPtr;
			// C#��dll�Ń��[�U�[���J�X�^�������t�@�C�����w�肷�邩������Ȃ��B
			System::Collections::Generic::Dictionary<System::String^, System::Object^>^ dic = gcnew System::Collections::Generic::Dictionary<System::String^, System::Object^>(5);
			dic->Add("�U�������ԍ�", iBushouID);
			dic->Add("�U���^�C�v", "����");
			dic->Add("�h��^�C�v", "����");
			dic->Add("�U����������", �U����������);
			System::Collections::Generic::Dictionary<System::String^, System::Object^>^ ret = InvokeUserMethod("on�ď��_���[�W���莞", dic);
			if (ret != nullptr) {
				if (ret->ContainsKey("�U����������")) {
					int override�U���������� = (int)ret["�U����������"];
					*pRemainHeisuPtr = override�U����������;  // �����Ŏc�蕺�������Ă���
					EAXOfCastleBattleButaisyoutotsuAttackDamage = override�U����������; // EAX�ɂ��c�蕺�������Ă����B���ꂪ��ʂŕ\������p
				}
			}
		}
		catch (System::Exception^) {
			OutputDebugStream("on�ď��_���[�W���莞�ŗ�O���������܂����B\n");
		}

		if (getBushou����FromBushouID(iBushouID) == getArubedoSeiMei()) {
			OutputDebugStream("�������A���x�h�U���Ȃ̂ŕ������ێ�\n");
			int reimainMax = get�R�����j�b�g�����ő啺��FromBushouID(iBushouID);
			int value = (reimainMax + *pRemainHeisuPtr) / 2;
			*pRemainHeisuPtr = value;                            // �����Ŏc�蕺�����ő�ɋ߂Â���
			EAXOfCastleBattleButaisyoutotsuAttackDamage = value; // EAX�ɂ��c�蕺�������Ă����B���ꂪ��ʂŕ\������p
		}
	}
}

#pragma unmanaged

/*
004171D4   E8 B7B8FEFF      CALL Nobunaga.00402A90
004171D9   50               PUSH EAX                                  ���̎���EAX���U�����̌�����̕����B��������s������AECX+8�̃A�h���X�� EAX�̒l�Ɠ����l�����邱�ƁB
004171DA   55               PUSH EBP                                  
004171DB   68 180E5200      PUSH Nobunaga.00520E18                   ; ASCII "�U������ : %d ---> %d
�h�䋒�_ : %d ---> %d"
004171E0   68 D8A55D00      PUSH Nobunaga.005DA5D8                   ; ASCII "  ���q��  1490"
004171E5   E8 8DB50E00      CALL Nobunaga.00502777
004171EA   83C4 18          ADD ESP,18


EAX 0000037A
ECX 00540204 Nobunaga.00540204
EDX 00000046
EBX 005408DA Nobunaga.005408DA
ESP 0019FA60
EBP 00000384
ESI 00540204 Nobunaga.00540204
EDI 0000000A
EIP 004171DA Nobunaga.004171DA
*/

int pSSRExeJumpFromToOnSSRExeCastleBattleButaisyoutotsuAttackDamage = 0x4171D4; // �֐��͂��̃A�h���X����AOnSSRExeCastleBattleButaisyoutotsuAttackDamage�ւƃW�����v���Ă���B
int pSSRExeJumpCallFromToOnSSRExeCastleBattleButaisyoutotsuAttackDamage = 0x402A90; // ���X������������Call��
int pSSRExeReturnLblFromOnSSRExeCastleBattleButaisyoutotsuAttackDamage = 0x4171D9; // �֐����Ō�܂ł����ƁA���̎��sexe���ɒ��ڃW�����v����

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeCastleBattleButaisyoutotsuAttackDamage() {
	// �X�^�b�N�ɂ��߂Ă���
	__asm {
		call pSSRExeJumpCallFromToOnSSRExeCastleBattleButaisyoutotsuAttackDamage

		mov ECXOfCastleBattleButaisyoutotsuAttackDamage, ecx
		mov EAXOfCastleBattleButaisyoutotsuAttackDamage, eax

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeCastleBattleButaisyoutotsuAttackDamageExecute();

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

		mov eax, EAXOfCastleBattleButaisyoutotsuAttackDamage  // ������̎c�蕺����ύX����Ȃ炱���ŕύX���Ă����B
		jmp pSSRExeReturnLblFromOnSSRExeCastleBattleButaisyoutotsuAttackDamage
	}
}
#pragma warning(default: 4733) // ���[�j���O�̗}������������



char cmdOnSSRExeJumpFromCastleBattleButaisyoutotsuAttackDamage[6] = "\xE9";
// ���̖��߂�5�o�C�g�A�Ȍ�̊֐��Ő��܂�閽�߂����v�T�o�C�g�Ȃ̂Łc �Ō�P�g��Ȃ�


// �j�[���j�b�N���������p
void WriteAsmJumperOnSSRExeCastleBattleButaisyoutotsuAttackDamage() {

	// �܂��A�h���X�𐔎��Ƃ��Ĉ���
	int iAddress = (int)OnSSRExeCastleBattleButaisyoutotsuAttackDamage;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeCastleBattleButaisyoutotsuAttackDamage + 5);
	// �T�Ƃ����̂́A0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  �̖��߂ɕK�v�ȃo�C�g���B�v����ɂT�o�C�g�����Ǝ��̃j�[���j�b�N���ߌQ�Ɉړ�����̂��B�����Ă�������̍������W�����v����ۂ̖ړI�i�Ƃ��ė��p�����B
	memcpy(cmdOnSSRExeJumpFromCastleBattleButaisyoutotsuAttackDamage + 1, &SubAddress, 4); // +1 ��E9�̎�����4�o�C�g�����������邩��B

	// �\�z�����j�[���j�b�N���߂�TENSHOU.EXE�̃������ɏ���������
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeCastleBattleButaisyoutotsuAttackDamage), cmdOnSSRExeJumpFromCastleBattleButaisyoutotsuAttackDamage, 5, NULL); //5�o�C�g�̂ݏ�������
}

#pragma managed
