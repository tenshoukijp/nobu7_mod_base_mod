#include <windows.h>
#include "menu.h"
#include "font.h"

HWND hNB7Wnd = NULL;

HWND* referenceOfNB7Wnd = NULL;

void onCreateWindow(HWND hWnd) {

	hNB7Wnd = hWnd;

	*referenceOfNB7Wnd = hWnd; // �Ăяo�����ɁA�u����̋N���ł͂����ƃE�B���h�E���������ꂽ��v�Ɠ`����B����ăQ�[���{�̂��N�����ꂽ�B

	OutputDebugString("�E�B���h�E����\n");

	hNB7Menu = getNB7MenuHandle(hWnd);

	// ���j���[��ǉ�����
	addMenuItem("�������G�f�B�^�N��(&M)", RESOURCE_MENU_ID_EXIT, ADDITIONAL_MENU_ID_MEMORYEDITOR); // Position 1 �Ƀ��j���[��ǉ�����BID��59000

	OutputDebugString("���j���[��ǉ�����\n");

	OutputDebugString("�����^�̊J�n\n");

	onFontInitialize();
}
