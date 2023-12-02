#include <windows.h>
#include <string>
#include <vector>

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
#include "onigwrap.h"
using namespace std;

#pragma unmanaged
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

void replaceMessage(string message) {
#pragma warning(disable:4996)
	strcpy((char*)(�Z���t���b�Z�[�W�A�h���X), message.c_str());
#pragma warning(default: 4996) // ���[�j���O�̗}������������
}


BOOL isNextMessageIsRekishiBushouRetsuden = FALSE;
BOOL isNextMessageIsRekishiHimeRetsuden = FALSE;
BOOL isNextMessageIsKasouHimeRetsuden = FALSE;

/*
005D9638  0�̖��B���̗v�����󂯂Ĉ�R�̏��ƂȂ�B���e����̒q�d�ƕ��E�����˔�����
005D967F  �B.I�����Ă�������...........
*/


/*
�i�U���b�N�n���啭��̎��ғ����B���������
�Q�{�̊p�A������͎����̗��𐶂₵
���d���ȃT�L���o�X�B�u���ߐ[������
�̈����v�ٖ̈������␢�̔����B*/

vector<string> getOverrideBushouRetsuden(int iBushouID) {
	vector<string> ret;
	if (isValidBushouID(iBushouID)) {
		if (nb7�������[iBushouID].���� == getArubedoSeiMei()) {
			ret.push_back("�A���x�h ���ғ��� ????�`????");
			ret.push_back("�i�U���b�N�n���啭��̎��ғ����B��\xA"
				          "������͂Q�{�̊p�A������͎����̗���\xA"
			              "���₵���d���ȃT�L���o�X�B�u���ߐ[��\xA"
			              "�����̈����v�ٖ̈������␢�̔����B"
			);
			return ret;
		}
	}

	return ret;
}

void OnSSRExeMessageDetailExecute() {

	// ��`�̏ڍׂ̒u�������������Ă���΁A�ڍׂ�u��������
	if (isNextMessageIsRekishiBushouRetsuden) {
		isNextMessageIsRekishiBushouRetsuden = FALSE;
		int iRetsudenBushouID = getRetsudenBushouID();
		if (isValidBushouID(iRetsudenBushouID)) {
			auto ret = getOverrideBushouRetsuden(iRetsudenBushouID);
			if (ret.size() == 2) {
				string detail = ret[1];
				if (detail.size() > 0) {
					replaceMessage(detail);
				}
			}
		}
	}
	// ��`�̏ڍׂ̒u�������������Ă���΁A�ڍׂ�u��������
	if (isNextMessageIsRekishiHimeRetsuden) {
		isNextMessageIsRekishiHimeRetsuden = FALSE;
		int iRetsudenBushouID = getRetsudenBushouID();
		if (isValidBushouID(iRetsudenBushouID)) {
			auto ret = getOverrideBushouRetsuden(iRetsudenBushouID);
			if (ret.size() == 2) {
				string detail = ret[1];
				if (detail.size() > 0) {
					replaceMessage(detail);
				}
			}
		}
	}
	// ��`�̏ڍׂ̒u�������������Ă���΁A�ڍׂ�u��������
	if (isNextMessageIsKasouHimeRetsuden) {
		isNextMessageIsKasouHimeRetsuden = FALSE;
		int iRetsudenBushouID = getRetsudenBushouID();
		if (isValidBushouID(iRetsudenBushouID)) {
			auto ret = getOverrideBushouRetsuden(iRetsudenBushouID);
			if (ret.size() == 2) {
				string detail = ret[1];
				if (detail.size() > 0) {
					replaceMessage(detail);
				}
			}
		}
	}

	�Q�[����ʃX�e�[�^�X status = get�Q�[����ʃX�e�[�^�X();
	if (status == �Q�[����ʃX�e�[�^�X::�헪��� || status == �Q�[����ʃX�e�[�^�X::����� || status == �Q�[����ʃX�e�[�^�X::�ď����) {
		// ��̕����Ƒ��蕐�������߂�B�l�͗L���ł���̕������̑O��̂��̂��c���Ă��邾����������Ȃ��B�����������o����b�Ȃ̂ł���Ύ�̕����͕K���Z�b�g�����B
		int i���BushouID = get���BushouIDFromMessageBushou();
		if (isValidBushouID(i���BushouID)) {
			OutputDebugStream("����̂�%s��\n", nb7�������[i���BushouID].����);
			string message = (char*)(�Z���t���b�Z�[�W�A�h���X); // on_serihu_message
			if (nb7�������[i���BushouID].���� == getArubedoSeiMei()) {
				changeAlbedoMessage(i���BushouID, message);
			}

		}

		int i����BushouID = get����BushouIDFromMessageBushou();
		if (isValidBushouID(i����BushouID)) {
			OutputDebugStream("�������%s��\n", nb7�������[i����BushouID].����);
		}

		int iRetsudenBushouID = getRetsudenBushouID();
		if (isValidBushouID(iRetsudenBushouID)) {
			OutputDebugStream("���b�Z�[�W�i�K�Ń`�F�b�N���Ă���iRetsudenBushouID��%d\n", iRetsudenBushouID);
			// �ʏ�̕����� �u���� �� ????�`????�v�̃t�H�[�}�b�g����� 
			if (0 <= iRetsudenBushouID && iRetsudenBushouID < 700) {
				string message = (char*)(�Z���t���b�Z�[�W�A�h���X); // on_serihu_message
				Matches ma;
				if (OnigMatch(message, "^(.+?) (.+?) [0-9\\?]{4}�`[0-9\\?]{4}$", &ma)) {
					OutputDebugStream("�}�b�v������!!");
					// 0�`699�Ԃ̒ʏ�̕����B�́A������������Ă���
					if (ma[1] == nb7�������[iRetsudenBushouID].����) {
						// ���Ƀ��b�Z�[�W������������A��`�̏ڍׂ�u��������
						isNextMessageIsRekishiBushouRetsuden = true;
						// ��`�p�̃^�C�g��������u��������
						auto ret = getOverrideBushouRetsuden(iRetsudenBushouID);
						if (ret.size() == 2) {
							string title = ret[0];
							if (title.size() > 0) {
								replaceMessage(title);
							}
						}
					}
				}
			}
			// ���j�P�́A�u�� �� ????�`????�v�̃t�H�[�}�b�g�����
			else if (700 <= iRetsudenBushouID && iRetsudenBushouID < 716) {
				string message = (char*)(�Z���t���b�Z�[�W�A�h���X); // on_serihu_message
				Matches ma;
				if (OnigMatch(message, "^(.+?) (.+?) [0-9\\?]{4}�`[0-9\\?]{4}$", &ma)) {
					// 700�`715�Ԃ̗��j�P�B�́A���̂�
					if (ma[1] == nb7�������[iRetsudenBushouID].���O) {
						// ���Ƀ��b�Z�[�W������������A��`�̏ڍׂ�u��������
						isNextMessageIsRekishiHimeRetsuden = true;
						// ��`�p�̃^�C�g��������u��������
						auto ret = getOverrideBushouRetsuden(iRetsudenBushouID);
						if (ret.size() == 2) {
							string title = ret[0];
							if (title.size() > 0) {
								replaceMessage(title);
							}
						}
					}
				}
			}
			// ���z�P�́A�u�� ????�`????�v�̃t�H�[�}�b�g�����
			else if (716 <= iRetsudenBushouID && iRetsudenBushouID < 732) {
				string message = (char*)(�Z���t���b�Z�[�W�A�h���X); // on_serihu_message
				Matches ma;
				if (OnigMatch(message, "^(.+?) [0-9\\?]{4}�`[0-9\\?]{4}$", &ma)) {
					// 716�`731�Ԃ̉��z�P�B�́A���̂�
					if (ma[1] == nb7�������[iRetsudenBushouID].���O) {
						// ���Ƀ��b�Z�[�W������������A��`�̏ڍׂ�u��������
						isNextMessageIsKasouHimeRetsuden = true;
						// ��`�p�̃^�C�g��������u��������
						auto ret = getOverrideBushouRetsuden(iRetsudenBushouID);
						if (ret.size() == 2) {
							string title = ret[0];
							if (title.size() > 0) {
								replaceMessage(title);
							}
						}
					}
				}
			}
		}

	}

	OutputDebugStream("������");
	OutputDebugStream((char*)�Z���t���b�Z�[�W�A�h���X);
	OutputDebugStream("\n");
}


/*
���b�Z�[�W�Ȃǂ��������ɏ������܂�鎞
 
00496E67   8B4D F4          MOV ECX,DWORD PTR SS:[EBP-C]
00496E6A   64:890D 00000000 MOV DWORD PTR FS:[0],ECX
00496E71   59               POP ECX
00496E72   5F               POP EDI
00496E73   5E               POP ESI
00496E74   5B               POP EBX
*/
/*



*/
int pSSRExeJumpFromToOnSSRExeMessageDetail = 0x496E6A; // �֐��͂��̃A�h���X����AOnSSRExeMessageDetail�ւƃW�����v���Ă���B
int pSSRExeReturnLblFromOnSSRExeMessageDetail = 0x496E71; // �֐����Ō�܂ł����ƁA����TENSHOU.EXE���ɒ��ڃW�����v����
#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeMessageDetail() {
	// �X�^�b�N�ɂ��߂Ă���
	__asm {

		MOV DWORD PTR FS : [0] , ECX

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeMessageDetailExecute();

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

		jmp pSSRExeReturnLblFromOnSSRExeMessageDetail
	}
}
#pragma warning(default: 4733) // ���[�j���O�̗}������������



char cmdOnSSRExeJumpFromMessageDetail[6] = "\xE9";
// ���̖��߂�5�o�C�g�A�Ȍ�̊֐��Ő��܂�閽�߂����v�T�o�C�g�Ȃ̂Łc �Ō�P�g��Ȃ�


// �j�[���j�b�N���������p
void WriteAsmJumperOnSSRExeMessageDetail() {

	// �܂��A�h���X�𐔎��Ƃ��Ĉ���
	int iAddress = (int)OnSSRExeMessageDetail;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeMessageDetail + 5);
	// �T�Ƃ����̂́A0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  �̖��߂ɕK�v�ȃo�C�g���B�v����ɂT�o�C�g�����Ǝ��̃j�[���j�b�N���ߌQ�Ɉړ�����̂��B�����Ă�������̍������W�����v����ۂ̖ړI�i�Ƃ��ė��p�����B
	memcpy(cmdOnSSRExeJumpFromMessageDetail + 1, &SubAddress, 4); // +1 ��E9�̎�����4�o�C�g�����������邩��B

	// �\�z�����j�[���j�b�N���߂�TENSHOU.EXE�̃������ɏ���������
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeMessageDetail), cmdOnSSRExeJumpFromMessageDetail, 5, NULL); //5�o�C�g�̂ݏ�������
}

#pragma managed
