/*
0047E7E0   892D E0ED5300    MOV DWORD PTR DS:[53EDE0],EBP
0047E7E6   892D 88C86000    MOV DWORD PTR DS:[60C888],EBP
0047E7EC   C705 8CC86000 94>MOV DWORD PTR DS:[60C88C],94
0047E7F6   E8 F5840100      CALL Nobunaga.00496CF0                    // �ƕ�������̕�����\�z
0047E7FB   50               PUSH EAX                                 ; Nobunaga.005D9638
0047E7FC   68 0C0A5200      PUSH Nobunaga.00520A0C                   ; ASCII "%s"
0047E801   68 A8C86000      PUSH Nobunaga.0060C8A8                   ; ASCII "��R"
*/


// ���̃t�@�C���͒������s�B���ɗ����Ȃ��B�R���p�C���Ώۂ���O��Ă���

#include <windows.h>
#include <string>
#include "data_game_struct.h"
#include "output_debug_stream.h"
#include "data_kahou_struct.h"
#include "game_process.h"


using namespace std;

#pragma unmanaged

extern void replaceMessage(string message);
extern std::pair<string, string> getOverrideKahouRetsuden(int iKahouID);


extern int iKahouIDShowBgn;

extern string strOnKahouDetailRequest;
void OnSSRExeKahouDetailExecute() {
	int iKahouID = iKahouIDShowBgn;
	if (isValidKahouID(iKahouID)) {
		string detail = strOnKahouDetailRequest;
		if (detail.size() > 0) {
			replaceMessage(detail);
		}
	}
}

/*
0047E7E0   892D E0ED5300    MOV DWORD PTR DS:[53EDE0],EBP
0047E7E6   892D 88C86000    MOV DWORD PTR DS:[60C888],EBP
0047E7EC   C705 8CC86000 94>MOV DWORD PTR DS:[60C88C],94
0047E7F6   E8 F5840100      CALL Nobunaga.00496CF0                    // �ƕ�������̕�����\�z
0047E7FB   50               PUSH EAX                                 ; Nobunaga.005D9638
0047E7FC   68 0C0A5200      PUSH Nobunaga.00520A0C                   ; ASCII "%s"
0047E801   68 A8C86000      PUSH Nobunaga.0060C8A8                   ; ASCII "��R"
*/
int pSSRExeJumpFromToOnSSRExeKahouDetail = 0x47E7F6; // �֐��͂��̃A�h���X����AOnSSRExeKahouDetail�ւƃW�����v���Ă���B
int pSSRExeJumpCallFromToOnSSRExeKahouDetail = 0x496CF0; // ���X������������Call��
int pSSRExeReturnLblFromOnSSRExeKahouDetail = 0x47E7FB; // �֐����Ō�܂ł����ƁA����TENSHOU.EXE���ɒ��ڃW�����v����

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeKahouDetail() {
	// �X�^�b�N�ɂ��߂Ă���
	__asm {

		call pSSRExeJumpCallFromToOnSSRExeKahouDetail // ���̏���

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeKahouDetailExecute();

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

		jmp pSSRExeReturnLblFromOnSSRExeKahouDetail
	}
}
#pragma warning(default: 4733) // ���[�j���O�̗}������������



char cmdOnSSRExeJumpFromKahouDetail[6] = "\xE9";
// ���̖��߂�5�o�C�g�A�Ȍ�̊֐��Ő��܂�閽�߂����v�T�o�C�g�Ȃ̂Łc �Ō�P�g��Ȃ�


// �j�[���j�b�N���������p
void WriteAsmJumperOnSSRExeKahouDetail() {

	// �܂��A�h���X�𐔎��Ƃ��Ĉ���
	int iAddress = (int)OnSSRExeKahouDetail;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeKahouDetail + 5);
	// �T�Ƃ����̂́A0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  �̖��߂ɕK�v�ȃo�C�g���B�v����ɂT�o�C�g�����Ǝ��̃j�[���j�b�N���ߌQ�Ɉړ�����̂��B�����Ă�������̍������W�����v����ۂ̖ړI�i�Ƃ��ė��p�����B
	memcpy(cmdOnSSRExeJumpFromKahouDetail + 1, &SubAddress, 4); // +1 ��E9�̎�����4�o�C�g�����������邩��B

	// �\�z�����j�[���j�b�N���߂�TENSHOU.EXE�̃������ɏ���������
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeKahouDetail), cmdOnSSRExeJumpFromKahouDetail, 5, NULL); //5�o�C�g�̂ݏ�������
}

#pragma managed
