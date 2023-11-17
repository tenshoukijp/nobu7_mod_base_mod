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

using namespace std;


void WriteAsmJumperOnTenshouExeGetDaimyoKoukeishaBushouID();

void doGameTest() {

	OutputDebugStream("����%d", �^�[�����.����);
	OutputDebugStream("��%d", �^�[�����.��);

	for (int iBushouID = 0; iBushouID < �ő吔::�������::�z��; iBushouID++) {

		if (getBushou����FromBushouID(iBushouID) == "�D�c�M��") {
			OutputDebugStream("�D�c�M���̕����ԍ� %x\n", iBushouID);
		}
		if (getBushou����FromBushouID(iBushouID) == "����`��") {
			OutputDebugStream("����`���̕����ԍ� %x\n", iBushouID);
		}
		if (getBushou����FromBushouID(iBushouID) == "���c�M��") {
			OutputDebugStream("���c�M���̕����ԍ� %x\n", iBushouID);
		}

	}

	/*
	for (int iBushouID = 0; iBushouID < �ő吔::�������::�z��; iBushouID++) {
		OutputDebugStream(nb7�������[iBushouID].����);
		OutputDebugStream("\n");

		if (getBushou�c��FromBushouID(iBushouID) == "�ɑ�") {
			OutputDebugStream("����ID:" + getBushou����FromBushouID(iBushouID));
			OutputDebugStream("����:%d ", nb7�������[iBushouID].����);
			OutputDebugStream("�퓬:%d ", nb7�������[iBushouID].�퓬);
			OutputDebugStream("�m�d:%d ", nb7�������[iBushouID].�q�d);
			OutputDebugStream("�E��:%d ", nb7�������[iBushouID].�E��);
			OutputDebugStream("\n");

			for (int iKahouID = 0; iKahouID < �ő吔::�ƕ���::�z��; iKahouID++) {
				if (string(nb7�ƕ���[iKahouID].�ƕ�).find("����") != string::npos) {
					// strcpy(nb7�ƕ���[iKahouID].�ƕ�, "������������");
					// setBushouIDToKahouID(iKahouID, iBushouID);
				}
			}
		}

	}
	*/

	/*
	for (int iKahouID = 0; iKahouID < �ő吔::�ƕ���::�z��; iKahouID++) {
		OutputDebugStream("�ƕ�:%s ", nb7�ƕ���[iKahouID].�ƕ�);
		OutputDebugStream("���Ȍ���:%d ", nb7�ƕ���[iKahouID].���Ȍ���);
		OutputDebugStream("����:%d ", nb7�ƕ���[iKahouID].����);
		OutputDebugStream("�O���t�B�b�N�ԍ�:%d ", nb7�ƕ���[iKahouID].�O���t�B�b�N�ԍ�);
		OutputDebugStream("�㏸�\�͒l:%d ", nb7�ƕ���[iKahouID].�㏸�\�͒l);
		OutputDebugStream("�ƕ���:%d ", nb7�ƕ���[iKahouID].�ƕ���);
		int iBushouID = getBushouIDFromKahouID(iKahouID);
		if (0 <= iBushouID && iBushouID < �ő吔::�������::�z��) {
			OutputDebugStream("���L��:%s ", nb7�������[iBushouID].����);
		}
		OutputDebugStream("�ƕ�ԍ�:%d ", nb7�ƕ���[iKahouID].�ƕ�ԍ�);
		OutputDebugStream("�ƕ�ő吔:%d ", nb7�ƕ���[iKahouID].�ƕ�ő吔);
		OutputDebugStream("�\�͌���:%d ", (int)nb7�ƕ���[iKahouID].�\�͌���);
		OutputDebugStream("\n");
	}
		*/

		/*
		for (int iKanniID = 0; iKanniID < �ő吔::���ʏ��::�z��; iKanniID++) {
			OutputDebugStream("���ʖ�:%s ", nb7���ʏ��[iKanniID].���ʖ�);
			OutputDebugStream("���ʔԍ�:%d ", nb7���ʏ��[iKanniID].���ʔԍ�);
			OutputDebugStream("�K��:%d ", nb7���ʏ��[iKanniID].�K��);
			OutputDebugStream("\n");
			int iBushouID = getBushouIDFromKanniID(iKanniID);
			if (0 <= iBushouID && iBushouID < �ő吔::�������::�z��) {

				OutputDebugStream("���L��:%s ", nb7�������[iBushouID].����);
			}
		}
		*/

		/*
		for (int iYakusyokuID = 0; iYakusyokuID < �ő吔::��E���::�z��; iYakusyokuID++) {
			OutputDebugStream("��E��:%s ", nb7��E���[iYakusyokuID].��E��);
			OutputDebugStream("��E�ԍ�:%d ", nb7��E���[iYakusyokuID].��E�ԍ�);
			OutputDebugStream("����:%d ", nb7��E���[iYakusyokuID].����);
			int iBushouID = getBushouIDFromYakusyokuID(iYakusyokuID);
			OutputDebugStream("%d", iBushouID);
			if ( 0 <= iBushouID && iBushouID < �ő吔::�������::�z��) {

				OutputDebugStream("���L��:%s ", nb7�������[iBushouID].����);
			}
			OutputDebugStream("\n");
		}
		*/

		for (int iCastleID = 0; iCastleID < �ő吔::����::�z��; iCastleID++) {
			if (nb7����[iCastleID].�閼 == "�ߌÖ�"s) {
				nb7����[iCastleID].���l = 0x1;
			}

		}

		for (int iUnitID = 0; iUnitID < �ő吔::���j�b�g���::�z��; iUnitID++) {
			int iBushouID = getBushouIDFromUnitID(iUnitID);
			if (iBushouID != 0xFFFF) {
				OutputDebugStream("���j�b�g�ԍ�:%d ", nb7���j�b�g���[iUnitID].���j�b�g�ԍ�);
				OutputDebugStream("���j�b�g�x�z��:%s \n", (char *)(nb7���j�b�g���[iUnitID].p���j�b�g����));
				OutputDebugStream("���j�b�g��C:%d \n", nb7���j�b�g���[iUnitID].��C);
				OutputDebugStream("���j�b�g�S�b�D:%d \n", nb7���j�b�g���[iUnitID].�S�b�D);
			}
		}

	auto ret = get�Q�[����ʃX�e�[�^�X();
	OutputDebugStream("�Q�[����ʃX�e�[�^�X: %d", (int)ret);

	WriteAsmJumperOnTenshouExeGetDaimyoKoukeishaBushouID();

}





/*
�������̌Ăяo�����A���̇@
00496D8B   E8 80B20600      CALL Nobunaga.00502010
00496D90   83C4 0C          ADD ESP, 0C
00496D93   8B45 08          MOV EAX, DWORD PTR SS : [EBP + 8]
00496D96   E8 05F1FFFF      CALL Nobunaga.00495EA0
00496D9B   BE 01000000      MOV ESI, 1
00496DA0   66:891D 4C985D00 MOV WORD PTR DS : [5D984C] , BX
00496DA7   C705 88985D00 38 > MOV DWORD PTR DS : [5D9888] , Nobunaga.005D9 > ; ASCII "�������܃f�[�^�����[�h���Ă��܂�"
00496DB1   891D 44985D00    MOV DWORD PTR DS : [5D9844] , EBX
00496DB7   891D 48985D00    MOV DWORD PTR DS : [5D9848] , EBX
00496DBD   891D 50985D00    MOV DWORD PTR DS : [5D9850] , EBX
00496DC3   66:C705 38975D00 > MOV WORD PTR DS : [5D9738] , 0FFFF
00496DCC   66:8935 38985D00 MOV WORD PTR DS : [5D9838] , SI
00496DD3   B9 80E95700      MOV ECX, Nobunaga.0057E980
00496DD8   E8 6357FCFF      CALL Nobunaga.0045C540
00496DDD   8B08             MOV ECX, DWORD PTR DS : [EAX]
00496DDF   894D DC          MOV DWORD PTR SS : [EBP - 24] , ECX
00496DE2   8B50 04          MOV EDX, DWORD PTR DS : [EAX + 4]
00496DE5   8955 E0          MOV DWORD PTR SS : [EBP - 20] , EDX
00496DE8   8B48 08          MOV ECX, DWORD PTR DS : [EAX + 8]
00496DEB   894D E4          MOV DWORD PTR SS : [EBP - 1C] , ECX
00496DEE   8B50 0C          MOV EDX, DWORD PTR DS : [EAX + C]
00496DF1   8955 E8          MOV DWORD PTR SS : [EBP - 18] , EDX
00496DF4   0FB740 10        MOVZX EAX, WORD PTR DS : [EAX + 10]
00496DF8   66:8945 EC       MOV WORD PTR SS : [EBP - 14] , AX
00496DFC   66:A1 40985D00   MOV AX, WORD PTR DS : [5D9840]
00496E02   0FB7C8           MOVZX ECX, AX
*/


void OnTenshouExeGetDaimyoKoukeishaBushouIDExecute() {
	OutputDebugString("OnTenshouExeGetDaimyoKoukeishaBushouIDExecute\n");
	OutputDebugString("���l:");
	int* p = (int*)(0x5D984C);
	OutputDebugStream(*p);
	OutputDebugString("\n");
	OutputDebugString((char*)�Z���t���b�Z�[�W�A�h���X);
	OutputDebugString("\n");
}


/*
00496E24   8AD9             MOV BL,CL
00496E26   E8 C5FCFFFF      CALL Nobunaga.00496AF0
00496E2B   33DB             XOR EBX,EBX
*/
/*

00496DD3   B9 80E95700      MOV ECX, Nobunaga.0057E980
00496DD8   E8 6357FCFF      CALL Nobunaga.0045C540
				�������� CALL (dll���֐�)�ւƏ��������Ă����ۂ̏���
00496DDD   8B08             MOV ECX, DWORD PTR DS : [EAX]



*/
int pTenshouExeJumpFromToOnTenshouExeGetDaimyoKoukeishaBushouID = 0x496E24; // �֐��͂��̃A�h���X����AOnTenshouExeGetDaimyoKoukeishaBushouID�ւƃW�����v���Ă���B
int pTenshouExeJumpCallFromToOnTenshouExeGetDaimyoKoukeishaBushouID = 0x496AF0; // ���X������Call�L�q�̊֐��A�h���X
int pTenshouExeReturnLblFromOnTenshouExeGetDaimyoKoukeishaBushouID = 0x496E2B; // �֐����Ō�܂ł����ƁA����TENSHOU.EXE���ɒ��ڃW�����v����
// ���̊֐���TENSHOU.EXE�����b�Z�[�W��ǂ݂��I���邽�тɁA���ڎ��s�����B
// TENSHOU.EXE���Ń��b�Z�[�W���\�z�����^�C�~���O�ł���naked�֐����Ă΂��B
__declspec(naked) void WINAPI OnTenshouExeGetDaimyoKoukeishaBushouID() {
	// �X�^�b�N�ɂ��߂Ă���
	__asm {

		// ���Xtenshou.exe�ɂ�����������������
		call pTenshouExeJumpCallFromToOnTenshouExeGetDaimyoKoukeishaBushouID

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnTenshouExeGetDaimyoKoukeishaBushouIDExecute();

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

		jmp pTenshouExeReturnLblFromOnTenshouExeGetDaimyoKoukeishaBushouID
	}
}



char cmdOnTenshouExeJumpFromGetDaimyoKoukeishaBushouID[6] = "\xE9";
// ���̖��߂�5�o�C�g�A�Ȍ�̊֐��Ő��܂�閽�߂����v�T�o�C�g�Ȃ̂Łc �Ō�P�g��Ȃ�


// �j�[���j�b�N���������p
void WriteAsmJumperOnTenshouExeGetDaimyoKoukeishaBushouID() {

	// �܂��A�h���X�𐔎��Ƃ��Ĉ���
	int iAddress = (int)OnTenshouExeGetDaimyoKoukeishaBushouID;
	int SubAddress = iAddress - (pTenshouExeJumpFromToOnTenshouExeGetDaimyoKoukeishaBushouID + 5);
	// �T�Ƃ����̂́A0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  �̖��߂ɕK�v�ȃo�C�g���B�v����ɂT�o�C�g�����Ǝ��̃j�[���j�b�N���ߌQ�Ɉړ�����̂��B�����Ă�������̍������W�����v����ۂ̖ړI�i�Ƃ��ė��p�����B
	memcpy(cmdOnTenshouExeJumpFromGetDaimyoKoukeishaBushouID + 1, &SubAddress, 4); // +1 ��E9�̎�����4�o�C�g�����������邩��B

	// �\�z�����j�[���j�b�N���߂�TENSHOU.EXE�̃������ɏ���������
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pTenshouExeJumpFromToOnTenshouExeGetDaimyoKoukeishaBushouID), cmdOnTenshouExeJumpFromGetDaimyoKoukeishaBushouID, 5, NULL); //5�o�C�g�̂ݏ�������
}

