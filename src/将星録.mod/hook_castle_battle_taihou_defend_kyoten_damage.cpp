/*
004131E9   8BCE             MOV ECX,ESI
004131EB   E8 A0F8FEFF      CALL Nobunaga.00402A90
004131F0   50               PUSH EAX                                 ���̎���EAX���U�����̌�����̖h��l�BECX+0x8�̃A�h���X�� EAX�̒l�Ɠ����l�����邱�ƁB
004131F1   57               PUSH EDI
004131F2   68 B40C5200      PUSH Nobunaga.00520CB4                   ; ASCII "�h�䋒�_ : %d ---> %d"


*/


#include <windows.h>
#include <string>
#include "data_game_struct.h"
#include "data_bushou_struct.h"
#include "output_debug_stream.h"
#include "game_screen.h"
#include "game_process.h"
#include "bushou_albedo.h"
#include "usr_custom_mod.h"

using namespace std;


extern int iCastleBattleTaihouAttackBushou;
static int ECXOfCastleBattleTaihouDefendKyotenDamage = 0;
static int EAXOfCastleBattleTaihouDefendKyotenDamage = 0;
void OnSSRExeCastleBattleTaihouDefendKyotenDamageExecute() {
	int* pRemainKyotenPtr = (int*)((BYTE*)(ECXOfCastleBattleTaihouDefendKyotenDamage)+0x8); // �����ɋ��_�ւ̖h��l�ւ̃|�C���^�������Ă���

	int iDefendBushouID = get1stBushouIDFromMessageBushou();
	// ���ꂪ�������Ƃ������Ƃ́A�h�䑤�̕����̓Z���t�Ɠf���Ă��Ȃ��Ƃ������ƂȂ̂ŁA�h�䑤�͎w���������Ȃ�
	if (iCastleBattleTaihouAttackBushou == iDefendBushouID) {

	}
	else {
		// �قȂ�Ƃ������Ƃ́A�h�䑤�̕������Z���t�Ɠf�����Ƃ������ƂȂ̂ŁA�h�䑤�͎w����������
	}

	OutputDebugStream("��������C�̍U�����̕���" + getBushou����FromBushouID(iCastleBattleTaihouAttackBushou) + "\n");
	int iBushouID = iCastleBattleTaihouAttackBushou;
	if (isValidBushouID(iBushouID)) {
		OutputDebugStream("���_�̎c��ϋv�x%d\n", *pRemainKyotenPtr);
		OutputDebugStream("�U����" + getBushou����FromBushouID(iBushouID) + "\n");

		try {
			int ���_�h�� = *pRemainKyotenPtr;
			// C#��dll�Ń��[�U�[���J�X�^�������t�@�C�����w�肷�邩������Ȃ��B
			System::Collections::Generic::Dictionary<System::String^, System::Object^>^ dic = gcnew System::Collections::Generic::Dictionary<System::String^, System::Object^>(5);
			dic->Add("�U�������ԍ�", iBushouID);
			dic->Add("�U���^�C�v", "��C");
			dic->Add("�h��^�C�v", "���_");
			dic->Add("���_�h��", ���_�h��);
			System::Collections::Generic::Dictionary<System::String^, System::Object^>^ ret = InvokeUserMethod("on�ď��_���[�W���莞", dic);
			if (ret != nullptr) {
				if (ret->ContainsKey("���_�h��")) {
					int override���_�h�� = (int)ret["���_�h��"];
					*pRemainKyotenPtr = override���_�h��;// �����Ŏc��h���0�ɂ���
					EAXOfCastleBattleTaihouDefendKyotenDamage = override���_�h��; // EAX�ɂ��c��h������Ă����B���ꂪ��ʂŕ\������p
				}
			}
		}
		catch (System::Exception^) {
			OutputDebugStream("on�ď��_���[�W���莞�ŗ�O���������܂����B\n");
		}

		if (getBushou����FromBushouID(iBushouID) == getArubedoSeiMei()) {
			OutputDebugStream("�A���x�h�ɂ�鋒�_�̎c��ϋv�x�̏㏑��\n");
			*pRemainKyotenPtr = 0;                            // �����Ŏc��h���0�ɂ���
			EAXOfCastleBattleTaihouDefendKyotenDamage = 0; // EAX�ɂ��c��h������Ă����B���ꂪ��ʂŕ\������p
		}

		// EAX �� *pRemainKyotenPtr ���㏑������Ȃ炱���ŁB
	}

}

#pragma unmanaged

/*
004131E9   8BCE             MOV ECX,ESI
004131EB   E8 A0F8FEFF      CALL Nobunaga.00402A90
004131F0   50               PUSH EAX                                 ���̎���EAX���U�����̌�����̖h��l�BECX+0xA�̃A�h���X�� EAX�̒l�Ɠ����l�����邱�ƁB
004131F1   57               PUSH EDI
004131F2   68 B40C5200      PUSH Nobunaga.00520CB4                   ; ASCII "�h�䋒�_ : %d ---> %d"
*/

int pSSRExeJumpFromToOnSSRExeCastleBattleTaihouDefendKyotenDamage = 0x4131EB; // �֐��͂��̃A�h���X����AOnSSRExeCastleBattleTaihouDefendKyotenDamage�ւƃW�����v���Ă���B
int pSSRExeJumpCallFromToOnSSRExeCastleBattleTaihouDefendKyotenDamage = 0x402A90; // ���X������������Call��
int pSSRExeReturnLblFromOnSSRExeCastleBattleTaihouDefendKyotenDamage = 0x4131F0; // �֐����Ō�܂ł����ƁA���̎��sexe���ɒ��ڃW�����v����

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeCastleBattleTaihouDefendKyotenDamage() {
	// �X�^�b�N�ɂ��߂Ă���
	__asm {

		mov ECXOfCastleBattleTaihouDefendKyotenDamage, ecx

		call pSSRExeJumpCallFromToOnSSRExeCastleBattleTaihouDefendKyotenDamage

		mov EAXOfCastleBattleTaihouDefendKyotenDamage, eax

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeCastleBattleTaihouDefendKyotenDamageExecute();

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

		mov eax, EAXOfCastleBattleTaihouDefendKyotenDamage  // ������̎c��h���ύX����Ȃ炱���ŕύX���Ă����B
		jmp pSSRExeReturnLblFromOnSSRExeCastleBattleTaihouDefendKyotenDamage
	}
}
#pragma warning(default: 4733) // ���[�j���O�̗}������������



char cmdOnSSRExeJumpFromCastleBattleTaihouDefendKyotenDamage[6] = "\xE9";
// ���̖��߂�5�o�C�g�A�Ȍ�̊֐��Ő��܂�閽�߂����v�T�o�C�g�Ȃ̂Łc �Ō�P�g��Ȃ�


// �j�[���j�b�N���������p
void WriteAsmJumperOnSSRExeCastleBattleTaihouDefendKyotenDamage() {

	// �܂��A�h���X�𐔎��Ƃ��Ĉ���
	int iAddress = (int)OnSSRExeCastleBattleTaihouDefendKyotenDamage;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeCastleBattleTaihouDefendKyotenDamage + 5);
	// �T�Ƃ����̂́A0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  �̖��߂ɕK�v�ȃo�C�g���B�v����ɂT�o�C�g�����Ǝ��̃j�[���j�b�N���ߌQ�Ɉړ�����̂��B�����Ă�������̍������W�����v����ۂ̖ړI�i�Ƃ��ė��p�����B
	memcpy(cmdOnSSRExeJumpFromCastleBattleTaihouDefendKyotenDamage + 1, &SubAddress, 4); // +1 ��E9�̎�����4�o�C�g�����������邩��B

	// �\�z�����j�[���j�b�N���߂����sexe�̃������ɏ���������
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeCastleBattleTaihouDefendKyotenDamage), cmdOnSSRExeJumpFromCastleBattleTaihouDefendKyotenDamage, 5, NULL); //5�o�C�g�̂ݏ�������
}

#pragma managed
