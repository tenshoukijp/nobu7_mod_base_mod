#include <windows.h>
#include "game_menu.h"
#include "game_font.h"
#include "output_debug_stream.h"
#include "load_form_mod.h"
#include "usr_custom_mod.h"

HWND hNB7Wnd = NULL;

HWND* referenceOfNB7Wnd = NULL;

extern void ���[�U�J�X�^�����j���[();

extern void AddBushouGaijiConvertMap();

void onCreateWindow(HWND hWnd) {

	// �E�B���h�E�n���h����ۑ�
	hNB7Wnd = hWnd;

	// �Ăяo����(WinMM.dll)�ɁA�u����̋N���ł͂����ƃE�B���h�E���������ꂽ��v�Ɠ`����B����ăQ�[���{�̂��N�����ꂽ�B
	*referenceOfNB7Wnd = hWnd;

	OutputDebugStream("�E�B���h�E����\n");

	AddBushouGaijiConvertMap();

	// ���j���[�����낱��ς��̂ŁA���j���[�̕ύX�����m���邽�߁B�ŏ��ɂ�������B���Hook_SetMenu�ŁA�g���Ă���B
	hNB7MenuCheckChange = GetMenu(hNB7Wnd);

#ifndef SUPER_RELEASE
	// ���j���[��ǉ�����
	insertMenuItem(GetSystemMenu(hNB7Wnd, FALSE), "�������N��(&M)", RESOURCE_MENU_ID_EXIT, ADDITIONAL_MENU_ID_NOTEPAD);
#endif

	OutputDebugStream("���j���[��ǉ�����\n");

	LoadUserMod();

	{
		System::Collections::Generic::Dictionary<System::String^, System::Object^>^ dic = gcnew System::Collections::Generic::Dictionary<System::String^, System::Object^>(5);
		dic->Add("�E�B���h�E�n���h��", (int)hWnd);
		auto ret = InvokeUserMethod("on���C���E�B���h�E������", dic);
	}


	OutputDebugStream("�����^�̊J�n\n");

}

BOOL doneDestroyWindow = FALSE;
void onDestroyWindow() {
	if (!doneDestroyWindow) {
		Close_FormMod();

		System::Collections::Generic::Dictionary<System::String^, System::Object^>^ dic = gcnew System::Collections::Generic::Dictionary<System::String^, System::Object^>(5);
		auto ret = InvokeUserMethod("on���C���E�B���h�E�j���O", dic);

		OutputDebugStream("�E�B���h�E�j��\r\n");
	}

	doneDestroyWindow = TRUE;
}
