#include <windows.h>
#include "menu.h"
#include "font.h"
#include "output_debug_stream.h"

HWND hNB7Wnd = NULL;

HWND* referenceOfNB7Wnd = NULL;

void onCreateWindow(HWND hWnd) {

	// �E�B���h�E�n���h����ۑ�
	hNB7Wnd = hWnd;

	// �Ăяo����(WinMM.dll)�ɁA�u����̋N���ł͂����ƃE�B���h�E���������ꂽ��v�Ɠ`����B����ăQ�[���{�̂��N�����ꂽ�B
	*referenceOfNB7Wnd = hWnd;

	OutputDebugStream("�E�B���h�E����\n");

	// ���j���[�����낱��ς��̂ŁA���j���[�̕ύX�����m���邽�߁B�ŏ��ɂ�������B���Hook_SetMenu�ŁA�g���Ă���B
	hNB7MenuCheckChange = GetMenu(hNB7Wnd);

	// changePopupString(GetMenu(hNB7Wnd), 0, "�t�@�C��(&F)");

	// ���j���[��ǉ�����
	addMenuItem(GetSystemMenu(hNB7Wnd, FALSE), "�������N��(&M)", RESOURCE_MENU_ID_EXIT, ADDITIONAL_MENU_ID_NOTEPAD);

	OutputDebugStream("���j���[��ǉ�����\n");

	OutputDebugStream("�����^�̊J�n\n");

	// onFontInitialize();
}


void onDestroyWindow() {
	OutputDebugStream("�E�B���h�E�j��\r\n");
}
