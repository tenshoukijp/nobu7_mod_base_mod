#include <windows.h>
#include <string>
#include "output_debug_stream.h"
#include "game_menu.h"
#include "on_event.h"
#include "game_screen.h"
#include "hook_functions_direct.h"

int nCheckMenuCount = 0;

int prevMenuCount = 0;


BOOL Hook_SetMenuCustom(HWND hWnd, HMENU hMenu) {
	if (hMenu == NULL) {
		return FALSE;
	}

	int menu_count = GetMenuItemCount(hMenu);

	if (menu_count >= 8) {
		// �u���j�b�g�v�̃��j���[�A�C�e����S�p�ɕύX
		changeMenuItemString(hMenu, 226, "���j�b�g(&U)"); // 226�̓��\�[�X�G�f�B�^�ł킩��u���j�b�g�v�̃��j���[ID

	}

	// �u�t�@�C���v��POPUP��S�p�ɕύX
	changePopupString(hMenu, 0, "�t�@�C��(&F)");

	menu_count = GetMenuItemCount(hMenu); // �ꉞ�ς��Ȃ��͂������Ǎēx�擾���Ă����B

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
			addMenuItem(GetMenu(hWnd), "�����G�f�B�^", RESOURCE_MENU_ID_BUSHOUEDIT_ORIGINAL, ADDITIONAL_MENU_ID_BUSYOUEDIT_KAI);
			addMenuItem(GetMenu(hWnd), "���j�b�g�G�f�B�^", RESOURCE_MENU_ID_BUSHOUEDIT_ORIGINAL, ADDITIONAL_MENU_ID_UNITEDIT_KAI);
			addMenuItem(GetMenu(hWnd), "�喼�G�f�B�^", RESOURCE_MENU_ID_BUSHOUEDIT_ORIGINAL, ADDITIONAL_MENU_ID_DAIMYOEDIT_KAI);
			addMenuItem(GetMenu(hWnd), "�ƕ�G�f�B�^", RESOURCE_MENU_ID_BUSHOUEDIT_ORIGINAL, ADDITIONAL_MENU_ID_KAHOUEDIT_KAI);
			addMenuItem(GetMenu(hWnd), "���ʃG�f�B�^", RESOURCE_MENU_ID_BUSHOUEDIT_ORIGINAL, ADDITIONAL_MENU_ID_KANNIEDIT_KAI);
			addMenuItem(GetMenu(hWnd), "��E�G�f�B�^", RESOURCE_MENU_ID_BUSHOUEDIT_ORIGINAL, ADDITIONAL_MENU_ID_YAKUSYOKUEDIT_KAI);
			addMenuItem(GetMenu(hWnd), "�N���G�f�B�^", RESOURCE_MENU_ID_BUSHOUEDIT_ORIGINAL, ADDITIONAL_MENU_ID_NENNGETSUEDIT_KAI);
			addMenuItem(GetMenu(hWnd), "---", RESOURCE_MENU_ID_BUSHOUEDIT_ORIGINAL, NULL);
		}
	}

	if (prevMenuCount != menu_count) {

		if (menu_count == 3) {
			if (prevMenuCount == 9) {
				onCastleBattlePreStart();
			}
			OutputDebugStream("�ď��X�N���[�����ł���\n");
		}

		if (menu_count == 4) {
			if (prevMenuCount == 9) {
				onYasenBattlePreStart();
			}
			OutputDebugStream("�퓬�X�N���[�����ł���\n");
		}

		if (menu_count == 9) {


			if (prevMenuCount == 4) {
				onYasenBattleEnd();
			}
			else if (prevMenuCount == 3) {
				onCastleBattleEnd();
			}

			// �������
			else {
				onStrategyScreen();
			}

			OutputDebugStream("��p�X�N���[�����ł���\n");
		}

		prevMenuCount = menu_count;

	}

	return true;
}
