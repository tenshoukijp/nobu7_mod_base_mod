


/*
0047E7A7   892D E0ED5300    MOV DWORD PTR DS:[53EDE0],EBP
0047E7AD   892D 88C86000    MOV DWORD PTR DS:[60C888],EBP
0047E7B3   C705 8CC86000 20>MOV DWORD PTR DS:[60C88C],20
0047E7BD   E8 2E850100      CALL Nobunaga.00496CF0                   // �ƕ�^�C�g�� (�ƕ󖼁@���p��݁j�̕�����\�z
0047E7C2   50               PUSH EAX                                 ; Nobunaga.005D9638
0047E7C3   68 0C0A5200      PUSH Nobunaga.00520A0C                   ; ASCII "%s"
0047E7C8   68 A8C86000      PUSH Nobunaga.0060C8A8                   ; ASCII "��R"
0047E7CD   E8 005E0800      CALL Nobunaga.005045D2

*/

// ���̃t�@�C���͒������s�B���ɗ����Ȃ��B�R���p�C���Ώۂ���O��Ă���

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

extern void replaceMessage(string message);
extern std::pair<string, string> getOverrideKahouRetsuden(int iKahouID);


extern int iKahouIDShowBgn;
string strOnKahouDetailRequest = "";
void OnSSRExeKahouTitleExecute() {
	int iKahouID = iKahouIDShowBgn;
	strOnKahouDetailRequest = "";
	if (isValidKahouID(iKahouID)) {
		auto [title, detail] = getOverrideKahouRetsuden(iKahouID);
		if (title.size() > 0) {
			replaceMessage(title);
			strOnKahouDetailRequest = detail;
		}
	}
}

/*
0047E7A7   892D E0ED5300    MOV DWORD PTR DS:[53EDE0],EBP
0047E7AD   892D 88C86000    MOV DWORD PTR DS:[60C888],EBP
0047E7B3   C705 8CC86000 20>MOV DWORD PTR DS:[60C88C],20
0047E7BD   E8 2E850100      CALL Nobunaga.00496CF0                   // �ƕ�^�C�g�� (�ƕ󖼁@���p��݁j�̕�����\�z
0047E7C2   50               PUSH EAX                                 ; Nobunaga.005D9638
0047E7C3   68 0C0A5200      PUSH Nobunaga.00520A0C                   ; ASCII "%s"
0047E7C8   68 A8C86000      PUSH Nobunaga.0060C8A8                   ; ASCII "��R"
0047E7CD   E8 005E0800      CALL Nobunaga.005045D2

*/
int pSSRExeJumpFromToOnSSRExeKahouTitle = 0x47E7BD; // �֐��͂��̃A�h���X����AOnSSRExeKahouTitle�ւƃW�����v���Ă���B
int pSSRExeJumpCallFromToOnSSRExeKahouTitle = 0x496CF0; // ���X������������Call��
int pSSRExeReturnLblFromOnSSRExeKahouTitle = 0x47E7C2; // �֐����Ō�܂ł����ƁA����TENSHOU.EXE���ɒ��ڃW�����v����

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeKahouTitle() {
	// �X�^�b�N�ɂ��߂Ă���
	__asm {

		call pSSRExeJumpCallFromToOnSSRExeKahouTitle // ���̏���

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeKahouTitleExecute();

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

		jmp pSSRExeReturnLblFromOnSSRExeKahouTitle
	}
}
#pragma warning(default: 4733) // ���[�j���O�̗}������������



char cmdOnSSRExeJumpFromKahouTitle[6] = "\xE9";
// ���̖��߂�5�o�C�g�A�Ȍ�̊֐��Ő��܂�閽�߂����v�T�o�C�g�Ȃ̂Łc �Ō�P�g��Ȃ�


// �j�[���j�b�N���������p
void WriteAsmJumperOnSSRExeKahouTitle() {

	// �܂��A�h���X�𐔎��Ƃ��Ĉ���
	int iAddress = (int)OnSSRExeKahouTitle;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeKahouTitle + 5);
	// �T�Ƃ����̂́A0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  �̖��߂ɕK�v�ȃo�C�g���B�v����ɂT�o�C�g�����Ǝ��̃j�[���j�b�N���ߌQ�Ɉړ�����̂��B�����Ă�������̍������W�����v����ۂ̖ړI�i�Ƃ��ė��p�����B
	memcpy(cmdOnSSRExeJumpFromKahouTitle + 1, &SubAddress, 4); // +1 ��E9�̎�����4�o�C�g�����������邩��B

	// �\�z�����j�[���j�b�N���߂�TENSHOU.EXE�̃������ɏ���������
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeKahouTitle), cmdOnSSRExeJumpFromKahouTitle, 5, NULL); //5�o�C�g�̂ݏ�������
}

#pragma managed
