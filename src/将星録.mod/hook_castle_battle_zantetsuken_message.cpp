/*
004174B8   0F84 1E010000    JE Nobunaga.004175DC
004174BE   8BCB             MOV ECX,EBX
004174C0   E8 FBCAFEFF      CALL Nobunaga.00403FC0
004174C5   85C0             TEST EAX,EAX
004174C7   0F84 0F010000    JE Nobunaga.004175DC
004174CD   68 580E5200      PUSH Nobunaga.00520E58                   ; ASCII "�a�S��"
004174D2   68 D8A55D00      PUSH Nobunaga.005DA5D8
004174D7   E8 9BB20E00      CALL Nobunaga.00502777
004174DC   8B4C24 5C        MOV ECX,DWORD PTR SS:[ESP+5C]
004174E0   83C4 08          ADD ESP,8
*/




#include <windows.h>
#include <string>
#include <vector>
#include "data_game_struct.h"
#include "data_bushou_struct.h"
#include "output_debug_stream.h"
#include "game_process.h"
#include "on_serihu_message.h"
#include "bushou_albedo.h"
#include "usr_custom_mod.h"


using namespace std;


// �a�S����ł���������BushouID
extern int iZantetsukenAttackBushouID;
extern vector<int> list�b��BushouID;

static int DefaultZantetsukenMessagePtr = 0x520E58;  // �����^�̃f�t�H���g�Ƃ��Ďa�S���Ƃ��������񂪑��݂���A�h���X

char customZantetsukenMessage[256] = "";
static int CustomZantetsukenMessagePtr = (int)customZantetsukenMessage;

void OnSSRExeCastleBattleMessageZantetsukenExecute() {
	int iBushouID = iZantetsukenAttackBushouID;
	customZantetsukenMessage[0] = NULL;
	CustomZantetsukenMessagePtr = DefaultZantetsukenMessagePtr; // �f�t�H���g�ł͎a�S��
	if (isValidBushouID(iBushouID)) {
		if (getBushou����FromBushouID(iBushouID) == getArubedoSeiMei()) {
			string message1 = "�܂�Ŏ��̂悤�ȐƂ����\xA�X��A�o���f�B�b�V���I";
			string message2 = "�k���Ď��ʂ̂�҂��Ȃ���\xA�X��A�o���f�B�b�V���I";
			string message3 = "����ǂ��[�I\xA�����炪�I";
			int rnd = rand() % 2;
			if (rnd == 2) {
				strcpy_s(customZantetsukenMessage, message1.c_str());
			}
			else if (rnd == 1) {
				strcpy_s(customZantetsukenMessage, message2.c_str());
			}
			else {
				strcpy_s(customZantetsukenMessage, message3.c_str());
			}
			CustomZantetsukenMessagePtr = (int)customZantetsukenMessage;
		}

		// C#�̃J�X�^��.mod.dll����̏㏑��
		try {
			System::Collections::Generic::Dictionary<System::String^, System::Object^>^ dic = gcnew System::Collections::Generic::Dictionary<System::String^, System::Object^>(5);
			dic->Add("���b�Z�[�W", gcnew System::String((char*)�Z���t���b�Z�[�W�A�h���X));
			dic->Add("�����ԍ��P�l��", list�b��BushouID[0]);
			dic->Add("�����ԍ��Q�l��", list�b��BushouID[1]);
			dic->Add("�����ԍ��R�l��", list�b��BushouID[2]);
			dic->Add("�����ԍ��S�l��", list�b��BushouID[3]);
			System::Collections::Generic::Dictionary<System::String^, System::Object^>^ ret = InvokeUserMethod("on�������b�Z�[�W�v����", dic);
			if (ret != nullptr && ret->ContainsKey("���b�Z�[�W")) {
				System::String^ override_message = (System::String^)(ret["���b�Z�[�W"]);
				if (System::String::IsNullOrEmpty(override_message)) {
					;
				}
				else {
					strcpy_s(customZantetsukenMessage, to_native_string(override_message).c_str());
					CustomZantetsukenMessagePtr = (int)customZantetsukenMessage;
				}
			}

		}
		catch (System::Exception^ ) {
			OutputDebugStream("on�������b�Z�[�W�v�����ŃG���[");
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
004174D2   68 D8A55D00      PUSH Nobunaga.005DA5D8
004174D7   E8 9BB20E00      CALL Nobunaga.00502777
004174DC   8B4C24 5C        MOV ECX,DWORD PTR SS:[ESP+5C]
004174E0   83C4 08          ADD ESP,8
*/


int pSSRExeJumpFromToOnSSRExeCastleBattleMessageZantetsuken = 0x4174CD; // �֐��͂��̃A�h���X����AOnSSRExeCastleBattleMessageZantetsuken�ւƃW�����v���Ă���B
int pSSRExeReturnLblFromOnSSRExeCastleBattleMessageZantetsuken = 0x4174D2; // �֐����Ō�܂ł����ƁA���̎��sexe���ɒ��ڃW�����v����

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeCastleBattleMessageZantetsuken() {
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

	OnSSRExeCastleBattleMessageZantetsukenExecute();

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

		PUSH CustomZantetsukenMessagePtr // ���̏����������ɋL�q����

		jmp pSSRExeReturnLblFromOnSSRExeCastleBattleMessageZantetsuken
	}
}
#pragma warning(default: 4733) // ���[�j���O�̗}������������



char cmdOnSSRExeJumpFromCastleBattleMessageZantetsuken[6] = "\xE9";
// ���̖��߂�5�o�C�g�A�Ȍ�̊֐��Ő��܂�閽�߂����v�T�o�C�g�Ȃ̂Łc �Ō�P�g��Ȃ�


// �j�[���j�b�N���������p
void WriteAsmJumperOnSSRExeCastleBattleMessageZantetsuken() {

	// �܂��A�h���X�𐔎��Ƃ��Ĉ���
	int iAddress = (int)OnSSRExeCastleBattleMessageZantetsuken;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeCastleBattleMessageZantetsuken + 5);
	// �T�Ƃ����̂́A0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  �̖��߂ɕK�v�ȃo�C�g���B�v����ɂT�o�C�g�����Ǝ��̃j�[���j�b�N���ߌQ�Ɉړ�����̂��B�����Ă�������̍������W�����v����ۂ̖ړI�i�Ƃ��ė��p�����B
	memcpy(cmdOnSSRExeJumpFromCastleBattleMessageZantetsuken + 1, &SubAddress, 4); // +1 ��E9�̎�����4�o�C�g�����������邩��B

	// �\�z�����j�[���j�b�N���߂�TENSHOU.EXE�̃������ɏ���������
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeCastleBattleMessageZantetsuken), cmdOnSSRExeJumpFromCastleBattleMessageZantetsuken, 5, NULL); //5�o�C�g�̂ݏ�������
}

#pragma managed
