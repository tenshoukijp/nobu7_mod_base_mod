#include <windows.h>
#include "menu.h"
#include "font.h"

HWND hNB7Wnd = NULL;

HWND* referenceOfNB7Wnd = NULL;

void onCreateWindow(HWND hWnd) {

	hNB7Wnd = hWnd;

	*referenceOfNB7Wnd = hWnd; // �Ăяo�����ɁA�u����̋N���ł͂����ƃE�B���h�E���������ꂽ��v�Ɠ`����B����ăQ�[���{�̂��N�����ꂽ�B

	OutputDebugString("�E�B���h�E����\n");

	hNB7MenuCheckChange = GetMenu(hNB7Wnd);

	// changePopupString(GetMenu(hNB7Wnd), 0, "�t�@�C��(&F)");

	// ���j���[��ǉ�����
	addMenuItem(GetSystemMenu(hNB7Wnd, FALSE), "�������N��(&M)", RESOURCE_MENU_ID_EXIT, ADDITIONAL_MENU_ID_NOTEPAD);

	OutputDebugString("���j���[��ǉ�����\n");

	OutputDebugString("�����^�̊J�n\n");

	// onFontInitialize();
}


void onDestroyWindow() {
	OutputDebugString("�E�B���h�E�j��\r\n");
}
