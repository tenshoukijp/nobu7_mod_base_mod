#include <windows.h>
#include <string>
#include "output_debug_stream.h"
#include "menu.h"
#include "on_event.h"

int nCheckMenuCount = 0;

int prevMenuCount = 0;

BOOL Hook_SetMenuCustom(HWND hWnd, HMENU hMenu) {
	if (hMenu == NULL) {
		return FALSE;
	}

	int count = GetMenuItemCount(hMenu);

	if (count >= 8) {
		// �u���j�b�g�v�̃��j���[�A�C�e����S�p�ɕύX
		changeMenuItemString(hMenu, 226, "���j�b�g(&U)"); // 226�̓��\�[�X�G�f�B�^�ł킩��u���j�b�g�v�̃��j���[ID

	}

	// �u�t�@�C���v��POPUP��S�p�ɕύX
	changePopupString(hMenu, 0, "�t�@�C��(&F)");

	int menu_count = GetMenuItemCount(hMenu);

	// ���j���[�̃C���X�^���X���ύX����Ă���
	if (hMenu != hNB7MenuCheckChange) {
		hNB7MenuCheckChange = hMenu;

		// OutputDebugStream(std::to_string(count).c_str());
		// OutputDebugStream("���j���[���ݒ肳��܂�\r\n");
		// OutputDebugStream("���j���[���ς��܂���\r\n");

		// OpeningMovie���̃��j���[��2��
		if (menu_count == 2) {
			changePopupString(hMenu, 1, "���[�r�[���~(&M)");
			if (nCheckMenuCount != menu_count) {
				nCheckMenuCount = menu_count;
				onOpeningMovie();
			}
		}

		// �Q�[�����o�����ԂɂȂ�ƁA���j���[��9�ɂȂ�B�ꉞ8�ȏ�Ŕ���B
		if (menu_count == 9) {
			// ���j���[��ǉ�����
			addMenuItem(GetMenu(hWnd), "�������G�f�B�^�N��(&M)", RESOURCE_MENU_ID_BUSHOUEDIT, ADDITIONAL_MENU_ID_MEMORYEDITOR);
			addMenuItem(GetMenu(hWnd), "---", RESOURCE_MENU_ID_BUSHOUEDIT, NULL);

			OutputDebugStream("���j���[��ǉ�����\n");
		}
	}

	if (prevMenuCount != menu_count) {

		if (menu_count == 3) {
			OutputDebugStream("�ď��X�N���[�����ł���\n");
		}

		if (menu_count == 4) {
			OutputDebugStream("�퓬�X�N���[�����ł���\n");
		}

		if (menu_count == 9) {
			if (prevMenuCount == 4) {
				onYasenBattleEnd();
			}
			if (prevMenuCount == 3) {
				onCastleBattleEnd();
			}
			OutputDebugStream("��p�X�N���[�����ł���\n");
		}

		prevMenuCount = menu_count;

	}

	return true;
}
