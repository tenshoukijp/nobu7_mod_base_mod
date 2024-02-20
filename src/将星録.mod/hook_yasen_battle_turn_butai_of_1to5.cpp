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

/*
���̃^�[���ؕς���
00477BAB   894C24 24        MOV DWORD PTR SS:[ESP+24],ECX
00477BAF   8B50 04          MOV EDX,DWORD PTR DS:[EAX+4]
00477BB2   83EC 08          SUB ESP,8
00477BB5   8D4424 2C        LEA EAX,DWORD PTR SS:[ESP+2C]
00477BB9   8BCC             MOV ECX,ESP
00477BBB   50               PUSH EAX
00477BBC   895424 34        MOV DWORD PTR SS:[ESP+34],EDX
00477BC0   E8 6FAE0800      CALL Nobunaga.00502A34
00477BC5   81C3 F7030000    ADD EBX,3F7
00477BCB   53               PUSH EBX
00477BCC   B9 380F5800      MOV ECX,Nobunaga.00580F38
00477BD1   E8 4ADAFEFF      CALL Nobunaga.00465620
00477BD6   B8 B8000000      MOV EAX,0B8
00477BDB   A3 E0ED5300      MOV DWORD PTR DS:[53EDE0],EAX
00477BE0   A3 88C86000      MOV DWORD PTR DS:[60C888],EAX
00477BE5   893D 8CC86000    MOV DWORD PTR DS:[60C88C],EDI
00477BEB   8B8E 60010000    MOV ECX,DWORD PTR DS:[ESI+160]
00477BF1   2B8E 80000000    SUB ECX,DWORD PTR DS:[ESI+80]
00477BF7   51               PUSH ECX                                �@�@// ������ECX������΁A�^�[�����킩��B
00477BF8   68 FC095200      PUSH Nobunaga.005209FC                   ; ASCII "�c��%2d�^�[��"
00477BFD   68 A8C86000      PUSH Nobunaga.0060C8A8                   ; ASCII "��R"
00477C02   E8 CBC90800      CALL Nobunaga.005045D2
00477C07   8D5424 1C        LEA EDX,DWORD PTR SS:[ESP+1C]
00477C0B   6A 00            PUSH 0
00477C0D   52               PUSH EDX
00477C0E   E8 0DECFFFF      CALL Nobunaga.00476820
00477C13   8B08             MOV ECX,DWORD PTR DS:[EAX]
00477C15   894C24 2C        MOV DWORD PTR SS:[ESP+2C],ECX
00477C19   8B40 04          MOV EAX,DWORD PTR DS:[EAX+4]
00477C1C   894424 30        MOV DWORD PTR SS:[ESP+30],EAX
00477C20   B8 28010000      MOV EAX,128
00477C25   83C4 14          ADD ESP,14
00477C28   83F9 18          CMP ECX,18
00477C2B   A3 E0ED5300      MOV DWORD PTR DS:[53EDE0],EAX
00477C30   A3 88C86000      MOV DWORD PTR DS:[60C888],EAX
00477C35   893D 8CC86000    MOV DWORD PTR DS:[60C88C],EDI
00477C3B   75 0E            JNZ SHORT Nobunaga.00477C4B
00477C3D   8B8E 48010000    MOV ECX,DWORD PTR DS:[ESI+148]
00477C43   8B9E 4C010000    MOV EBX,DWORD PTR DS:[ESI+14C]
00477C49   EB 0C            JMP SHORT Nobunaga.00477C57
00477C4B   8B8E 4C010000    MOV ECX,DWORD PTR DS:[ESI+14C]
00477C51   8B9E 48010000    MOV EBX,DWORD PTR DS:[ESI+148]
00477C57   E8 44AF0500      CALL Nobunaga.004D2BA0                 �@�@�@�@������ECX��EBX������΁A�N�ƒN���키���킩��B
00477C5C   50               PUSH EAX
00477C5D   8BCB             MOV ECX,EBX
00477C5F   E8 3CAF0500      CALL Nobunaga.004D2BA0
00477C64   50               PUSH EAX
00477C65   68 BC3D5200      PUSH Nobunaga.00523DBC                   ; ASCII "%12s �� %-12s"
00477C6A   68 A8C86000      PUSH Nobunaga.0060C8A8                   ; ASCII "��R"
00477C6F   E8 5EC90800      CALL Nobunaga.005045D2
00477C74   8B8E 94000000    MOV ECX,DWORD PTR DS:[ESI+94]
00477C7A   83C4 10          ADD ESP,10
00477C7D   390D 14925300    CMP DWORD PTR DS:[539214],ECX
00477C83   74 52            JE SHORT Nobunaga.00477CD7
00477C85   8D5424 10        LEA EDX,DWORD PTR SS:[ESP+10]
00477C89   52               PUSH EDX
00477C8A   E8 91380000      CALL Nobunaga.0047B520
00477C8F   8B00             MOV EAX,DWORD PTR DS:[EAX]
00477C91   B9 18020000      MOV ECX,218
00477C96   890D E0ED5300    MOV DWORD PTR DS:[53EDE0],ECX
00477C9C   890D 88C86000    MOV DWORD PTR DS:[60C888],ECX
00477CA2   893D 8CC86000    MOV DWORD PTR DS:[60C88C],EDI
00477CA8   8B8E 94000000    MOV ECX,DWORD PTR DS:[ESI+94]
00477CAE   894424 0C        MOV DWORD PTR SS:[ESP+C],EAX
00477CB2   8BF0             MOV ESI,EAX
00477CB4   E8 57310000      CALL Nobunaga.0047AE10
00477CB9   83C0 01          ADD EAX,1
00477CBC   50               PUSH EAX
00477CBD   8BCE             MOV ECX,ESI
00477CBF   E8 5C59FAFF      CALL Nobunaga.0041D620
00477CC4   50               PUSH EAX
00477CC5   68 A43D5200      PUSH Nobunaga.00523DA4                   ; ASCII "%12s�R ��%d�����̐�p"
00477CCA   68 A8C86000      PUSH Nobunaga.0060C8A8                   ; ASCII "��R"
00477CCF   E8 FEC80800      CALL Nobunaga.005045D2
00477CD4   83C4 10          ADD ESP,10
00477CD7   5F               POP EDI
00477CD8   5E               POP ESI
00477CD9   5B               POP EBX
00477CDA   83C4 14          ADD ESP,14
00477CDD   C3               RETN
00477CDE   CC               INT3
00477CDF   CC               INT3
00477CE0   83EC 2C          SUB ESP,2C
*/

extern void do�A���x�h�����^�[��������(int iAttackBushouID, int iButaiID);

static int YasenCurrentAttackBushouPointer = -1; // ���ݍU�����Ă�����̕����|�C���^
static int iYasenTurnButaiOf1to5 = -1; // �����̂P�`�T�̂ǂꂪ�U�����Ă���̂�

int iPreviousAttackBushouIDOfYasenTurnButaiOf1to5 = -1;
int iPreviousAttackButaiIDOfYasenTurnButaiOf1to5 = -1;

extern int iLastAttackBushouID;
extern int iLastDefendBushouID;


void resetYasenTurnButaiOf1to5() {
	iPreviousAttackBushouIDOfYasenTurnButaiOf1to5 = -1;
	iPreviousAttackButaiIDOfYasenTurnButaiOf1to5 = -1;
}

extern void onYasenButaiAttack(int iRemainTurn, int iAttackBushouID, int iButaiID, int iDefendBushouID);
extern int nRemainYasenTurn; // �c��^�[����

void OnSSRExeYasenTurnButaiOf1to5Execute() {

	int iAttackBushouID = getBushouIDFromBushouPtr((int *)YasenCurrentAttackBushouPointer);
	if (isValidBushouID(iAttackBushouID)) {

		if (iPreviousAttackBushouIDOfYasenTurnButaiOf1to5 != iAttackBushouID || iPreviousAttackButaiIDOfYasenTurnButaiOf1to5 != iYasenTurnButaiOf1to5) {
			OutputDebugStream("�����V�����̍U����������\n");

			// ���J�n���̍U�����i���݂̃^�[���Ƃ������݂ł͂Ȃ��A�����������j�b�g���u�Ƃ����Ӗ��ł̃A�^�b�N���j
			if (iLastAttackBushouID == iAttackBushouID) {
				onYasenButaiAttack(nRemainYasenTurn, iAttackBushouID, iYasenTurnButaiOf1to5, iLastDefendBushouID);
			}
			// ���J�n���ł͖h�䑤(�������A���݂̃^�[���ł͍U�����j
			else {
				onYasenButaiAttack(nRemainYasenTurn, iAttackBushouID, iYasenTurnButaiOf1to5, iLastAttackBushouID);
			}

			do�A���x�h�����^�[��������(iAttackBushouID, iYasenTurnButaiOf1to5);

			iPreviousAttackBushouIDOfYasenTurnButaiOf1to5 = iAttackBushouID;
			iPreviousAttackButaiIDOfYasenTurnButaiOf1to5 = iYasenTurnButaiOf1to5;
		}
	}


	/*
	int* a = (int*)0x53EDE0;
	OutputDebugStream("0x53EDE0:%d\n", *a);

	int* b = (int*)0x60C888;
	OutputDebugStream("0x60C888:%d\n", *b);

	int* c = (int*)0x60C88C;
	OutputDebugStream("0x60C88C:%d\n", *c);
	*/

}


/*
00477C96   890D E0ED5300    MOV DWORD PTR DS:[53EDE0],ECX
00477C9C   890D 88C86000    MOV DWORD PTR DS:[60C888],ECX
00477CA2   893D 8CC86000    MOV DWORD PTR DS:[60C88C],EDI
00477CA8   8B8E 94000000    MOV ECX,DWORD PTR DS:[ESI+94]
00477CAE   894424 0C        MOV DWORD PTR SS:[ESP+C],EAX
00477CB2   8BF0             MOV ESI,EAX
00477CB4   E8 57310000      CALL Nobunaga.0047AE10
00477CB9   83C0 01          ADD EAX,1
00477CBC   50               PUSH EAX
00477CBD   8BCE             MOV ECX,ESI
00477CBF   E8 5C59FAFF      CALL Nobunaga.0041D620
00477CC4   50               PUSH EAX
00477CC5   68 A43D5200      PUSH Nobunaga.00523DA4                   ; ASCII "%12s�R ��%d�����̐�p"
00477CCA   68 A8C86000      PUSH Nobunaga.0060C8A8                   ; ASCII "��R"
00477CCF   E8 FEC80800      CALL Nobunaga.005045D2
00477CD4   83C4 10          ADD ESP,10
*/

int pSSRExeJumpFromToOnSSRExeYasenTurnButaiOf1to5 = 0x477CBF; // �֐��͂��̃A�h���X����AOnSSRExeYasenTurnButaiOf1to5�ւƃW�����v���Ă���B
int pSSRExeJumpCallFromToOnSSRExeYasenTurnButaiOf1to5 = 0x41D620; // ���X������������Call��
int pSSRExeReturnLblFromOnSSRExeYasenTurnButaiOf1to5 = 0x477CC4; // �֐����Ō�܂ł����ƁA����TENSHOU.EXE���ɒ��ڃW�����v����

#pragma warning(disable:4733)


__declspec(naked) void WINAPI OnSSRExeYasenTurnButaiOf1to5() {
	// �X�^�b�N�ɂ��߂Ă���
	__asm {
		mov YasenCurrentAttackBushouPointer, ecx
		mov iYasenTurnButaiOf1to5, eax
		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeYasenTurnButaiOf1to5Execute();

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

		call pSSRExeJumpCallFromToOnSSRExeYasenTurnButaiOf1to5 // ���̏���

		jmp pSSRExeReturnLblFromOnSSRExeYasenTurnButaiOf1to5
	}
}
#pragma warning(default: 4733) // ���[�j���O�̗}������������



char cmdOnSSRExeJumpFromYasenTurnButaiOf1to5[6] = "\xE9";
// ���̖��߂�5�o�C�g�A�Ȍ�̊֐��Ő��܂�閽�߂����v�T�o�C�g�Ȃ̂Łc �Ō�P�g��Ȃ�

// �j�[���j�b�N���������p
void WriteAsmJumperOnSSRExeYasenTurnButaiOf1to5() {

	// �܂��A�h���X�𐔎��Ƃ��Ĉ���
	int iAddress = (int)OnSSRExeYasenTurnButaiOf1to5;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeYasenTurnButaiOf1to5 + 5);
	// �T�Ƃ����̂́A0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  �̖��߂ɕK�v�ȃo�C�g���B�v����ɂT�o�C�g�����Ǝ��̃j�[���j�b�N���ߌQ�Ɉړ�����̂��B�����Ă�������̍������W�����v����ۂ̖ړI�i�Ƃ��ė��p�����B
	memcpy(cmdOnSSRExeJumpFromYasenTurnButaiOf1to5 + 1, &SubAddress, 4); // +1 ��E9�̎�����4�o�C�g�����������邩��B

	// �\�z�����j�[���j�b�N���߂�TENSHOU.EXE�̃������ɏ���������
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeYasenTurnButaiOf1to5), cmdOnSSRExeJumpFromYasenTurnButaiOf1to5, 5, NULL); //5�o�C�g�̂ݏ�������
}

#pragma managed
