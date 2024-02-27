#include <windows.h>
#include <string>

#include "data_game_struct.h"
#include "output_debug_stream.h"
#include "game_screen.h"
#include "on_serihu_message.h"
#include "bushou_albedo.h"
#include "game_screen.h"
#include "onigwrap.h"
#include "usr_custom_mod.h"

using namespace std;
using namespace ��;
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

extern void replaceMessage(string message);
extern void checkReplaceBushouSerifuMessage();

BOOL isNextMessageIsRekishiBushouRetsuden = FALSE;
BOOL isNextMessageIsRekishiHimeRetsuden = FALSE;
BOOL isNextMessageIsKasouHimeRetsuden = FALSE;

/*
005D9638  0�̖��B���̗v�����󂯂Ĉ�R�̏��ƂȂ�B���e����̒q�d�ƕ��E�����˔�����
005D967F  �B.I�����Ă�������...........
*/

std::pair<string, string> getAlbedoRetsuden(int iBushouID);

std::pair<string, string> getOverrideBushouRetsuden(int iBushouID) {
	if (isValidBushouID(iBushouID)) {
		// �A���x�h�Ȃ�A���x�h��`
		if (nb7�������[iBushouID].���� == getArubedoSeiMei()) {
			auto [title, detail] = getAlbedoRetsuden(iBushouID);
			if (title != "" || detail != "") {
				return { title, detail };
			}
		}
		else {

			// C#�ɂ��I�[�o�[���C�h
			try {
				System::Collections::Generic::Dictionary<System::String^, System::Object^>^ dic = gcnew System::Collections::Generic::Dictionary<System::String^, System::Object^>(5);
				dic->Add("�����ԍ�", iBushouID);
				System::Collections::Generic::Dictionary<System::String^, System::Object^>^ ret = InvokeUserMethod("on������`�v����", dic);

				string title = "";
				string detail = "";
				if (ret != nullptr && ret->ContainsKey("���x��")) {
					System::String^ mng_title = (System::String^)(ret["���x��"]);
					if (System::String::IsNullOrEmpty(mng_title)) {
						title = "";
					}
					else {
						title = to_native_string(mng_title);
					}
				}
				if (ret != nullptr && ret->ContainsKey("�ڍ�")) {
					System::String^ mng_detail = (System::String^)(ret["�ڍ�"]);
					if (System::String::IsNullOrEmpty(mng_detail)) {
						detail = "";
					}
					else {
						detail = to_native_string(mng_detail);
					}
				}
				if (title != "" || detail != "") {
					return { title, detail };
				}

			}
			catch (System::Exception^ ) {

			}

		}
	}

	return { "","" };
}

void checkReplaceBushouRetsuden() {

	// ��`�̏ڍׂ̒u�������������Ă���΁A�ڍׂ�u��������
	if (isNextMessageIsRekishiBushouRetsuden) {
		isNextMessageIsRekishiBushouRetsuden = FALSE;
		int iRetsudenBushouID = getRetsudenBushouID();
		if (isValidBushouID(iRetsudenBushouID)) {
			auto [title, detail] = getOverrideBushouRetsuden(iRetsudenBushouID);
			if (detail.size() > 0) {
				replaceMessage(detail);
			}
		}
	}
	// ��`�̏ڍׂ̒u�������������Ă���΁A�ڍׂ�u��������
	if (isNextMessageIsRekishiHimeRetsuden) {
		isNextMessageIsRekishiHimeRetsuden = FALSE;
		int iRetsudenBushouID = getRetsudenBushouID();
		if (isValidBushouID(iRetsudenBushouID)) {
			auto [title, detail] = getOverrideBushouRetsuden(iRetsudenBushouID);
			if (detail.size() > 0) {
				replaceMessage(detail);
			}
		}
	}
	// ��`�̏ڍׂ̒u�������������Ă���΁A�ڍׂ�u��������
	if (isNextMessageIsKasouHimeRetsuden) {
		isNextMessageIsKasouHimeRetsuden = FALSE;
		int iRetsudenBushouID = getRetsudenBushouID();
		if (isValidBushouID(iRetsudenBushouID)) {
			auto [title, detail] = getOverrideBushouRetsuden(iRetsudenBushouID);
			if (detail.size() > 0) {
				replaceMessage(detail);
			}
		}
	}

	int status = get�Q�[����ʃX�e�[�^�X();
	if (status == �Q�[����ʃX�e�[�^�X::�헪��� || status == �Q�[����ʃX�e�[�^�X::����� || status == �Q�[����ʃX�e�[�^�X::�ď����) {
		checkReplaceBushouSerifuMessage();

		int iRetsudenBushouID = getRetsudenBushouID();
		if (isValidBushouID(iRetsudenBushouID)) {
			OutputDebugStream("���b�Z�[�W�i�K�Ń`�F�b�N���Ă���iRetsudenBushouID��%d\n", iRetsudenBushouID);
			// �ʏ�̕����� �u���� �� ????�`????�v�̃t�H�[�}�b�g����� 
			if (0 <= iRetsudenBushouID && iRetsudenBushouID < 700) {
				string message = (char*)(�Z���t���b�Z�[�W�A�h���X); // on_serihu_message
				Matches ma;
				if (OnigMatch(message, "^(.+?) (.+?) [0-9\\?]{4}�`[0-9\\?]{4}$", &ma)) {
					// 0�`699�Ԃ̒ʏ�̕����B�́A������������Ă���
					// ���Ƀ��b�Z�[�W������������A��`�̏ڍׂ�u��������
					isNextMessageIsRekishiBushouRetsuden = true;
					// ��`�p�̃^�C�g��������u��������
					auto [title, detail] = getOverrideBushouRetsuden(iRetsudenBushouID);
					if (title.size() > 0) {
						replaceMessage(title);
					}
				}
			}
			// ���j�P�́A�u�� �� ????�`????�v�̃t�H�[�}�b�g�����
			else if (700 <= iRetsudenBushouID && iRetsudenBushouID < 716) {
				string message = (char*)(�Z���t���b�Z�[�W�A�h���X); // on_serihu_message
				Matches ma;
				if (OnigMatch(message, "^(.+?) (.+?) [0-9\\?]{4}�`[0-9\\?]{4}$", &ma)) {
					// ���Ƀ��b�Z�[�W������������A��`�̏ڍׂ�u��������
					isNextMessageIsRekishiHimeRetsuden = true;
					// ��`�p�̃^�C�g��������u��������
					auto [title, detail] = getOverrideBushouRetsuden(iRetsudenBushouID);
					if (title.size() > 0) {
						replaceMessage(title);
					}
				}
			}
			// ���z�P�́A�u�� ????�`????�v�̃t�H�[�}�b�g�����
			else if (716 <= iRetsudenBushouID && iRetsudenBushouID < 732) {
				string message = (char*)(�Z���t���b�Z�[�W�A�h���X); // on_serihu_message
				Matches ma;
				if (OnigMatch(message, "^(.+?) [0-9\\?]{4}�`[0-9\\?]{4}$", &ma)) {
					// ���Ƀ��b�Z�[�W������������A��`�̏ڍׂ�u��������
					isNextMessageIsKasouHimeRetsuden = true;
					// ��`�p�̃^�C�g��������u��������
					auto [title, detail] = getOverrideBushouRetsuden(iRetsudenBushouID);
					if (title.size() > 0) {
						replaceMessage(title);
					}
				}
			}
		}

	}
}

