#include <windows.h>
#include <string>
#include <vector>

#include "data_game_struct.h"
#include "output_debug_stream.h"
#include "game_screen.h"
#include "game_process.h"
#include "on_serihu_message.h"
#include "bushou_albedo.h"
#include "game_screen.h"
#include "message_albedo.h"
#include "onigwrap.h"
#include "mng_�ƕ��.h"

using namespace std;
using namespace �����^;

extern void replaceMessage(string message);

BOOL isNextMessageIsKahouRetsuden = FALSE;

std::pair<string, string> getAlbedoKahouRetsuden(int iBushouID);


std::pair<string, string> getOverrideKahouRetsuden(int iKahouID) {
	if (isValidBushouID(iKahouID)) {
		auto [title, detail] = getAlbedoKahouRetsuden(iKahouID);
		if (title != "" || detail != "") {
			return { title, detail };
		}
	}

	return { "","" };
}

extern int isKahouRetsudenMode;
extern int iKahouIDShowBgn;
extern int isKahouRetsudenBeginning;
void checkReplaceKahouRetsuden() {
	// �ƕ��`�\���J�n���łȂ���΁A�������Ȃ�
	if (!isKahouRetsudenBeginning) {
		return;
	}

	// ��`�̏ڍׂ̒u�������������Ă���΁A�ڍׂ�u��������
	if (isNextMessageIsKahouRetsuden) {
		isNextMessageIsKahouRetsuden = FALSE;
		isKahouRetsudenMode = 0;
		int iRetsudenKahouID = iKahouIDShowBgn;
		if (isValidKahouID(iRetsudenKahouID)) {
			auto [title, detail] = getOverrideKahouRetsuden(iRetsudenKahouID);
			if (detail.size() > 0) {
				replaceMessage(detail);
			}
		}
	}

	int status = get�Q�[����ʃX�e�[�^�X();
	if (isKahouRetsudenMode > 0 && status == ��::�Q�[����ʃX�e�[�^�X::�헪��� || status == ��::�Q�[����ʃX�e�[�^�X::����� || status == ��::�Q�[����ʃX�e�[�^�X::�ď����) {

		int iRetsudenKahouID = iKahouIDShowBgn;
		if (isValidKahouID(iRetsudenKahouID)) {
			OutputDebugStream("���b�Z�[�W�i�K�Ń`�F�b�N���Ă���iRetsudenKahouID��%d\n", iRetsudenKahouID);
			// �ʏ�̉ƕ�� �u�ƕ󖼁@(���S�p��)ցv�̃t�H�[�}�b�g����� 
			string message = (char*)(�Z���t���b�Z�[�W�A�h���X); // on_serihu_message
			Matches ma;
			if (OnigMatch(message, "^(.+?)�@(.+?)$", &ma)) {
				// �ƕ��`�̃t�H�[�}�b�g�ł���B
				// ���Ƀ��b�Z�[�W������������A��`�̏ڍׂ�u��������
				isNextMessageIsKahouRetsuden = true;
				// ��`�p�̃^�C�g��������u��������
				auto [title, detail] = getOverrideKahouRetsuden(iRetsudenKahouID);
				if (title.size() > 0) {
					replaceMessage(title);
				}
			}
		}
	}
}

