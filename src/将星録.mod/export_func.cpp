#include <windows.h>
#include <winuser.h>
#include <stdio.h>

#include "game_process.h"
#include "game_window.h"
#include "game_menu.h"
#include "game_font.h"

#include "hook_functions_replace.h"
#include "hook_functions_direct.h"

#include "output_debug_stream.h"
#include "mng_文字列変換.h"
#include "usr_custom_mod.h"

#include <time.h>

#pragma comment(lib, "user32.lib")

// WinMM.dllから呼ばれる関数。概ね初期時に呼ばれる。
extern "C" __declspec(dllexport) void WINAPI onInitialize(void* bufOfNB7Wnd) {

	srand((unsigned int)time(NULL)); // 現在時刻の情報で初期化

	// 本当に将星録本体のゲームが始まり、ウィンドウが描画されたのかのチェック。同じEXEでもランチャーへとバイパスされたりなど、色々あるためこのチェックが欠かせない。
	referenceOfNB7Wnd = (HWND *)bufOfNB7Wnd;

	hookFunctionsReplace();

	char buffer[256] = "";
	sprintf_s(buffer, _countof(buffer), "%x", nBaseAddress);
	OutputDebugStream(buffer);

	OutputDebugStream("onInitialize\r\n");

	onFontInitialize();
}

extern "C" __declspec(dllexport) void WINAPI onMmioOpenA(char* pszFileName, char* bufOverrideFileName) {
	System::String^ filepath = gcnew System::String(pszFileName);
	if (filepath->ToLower()->StartsWith("bgm\\")) {
		try {

			System::Collections::Generic::Dictionary<System::String^, System::Object^>^ dic = gcnew System::Collections::Generic::Dictionary<System::String^, System::Object^>(5);
			dic->Add("ファイル名", filepath);
			System::Collections::Generic::Dictionary<System::String^, System::Object^>^ ret = InvokeUserMethod("on音楽要求時", dic);
			if (ret != nullptr && ret->ContainsKey("ファイル名")) {
				System::String^ override_filename = (System::String^)(ret["ファイル名"]);
				if (System::String::IsNullOrEmpty(override_filename) == false) {
					strcpy_s(bufOverrideFileName, 512, to_native_string(override_filename).c_str());
				}
			}
		}
		catch (System::Exception^) {
			OutputDebugStream("on音楽要求時 でエラーが発声しました。");
		}
	}
	else {
		try {

			System::Collections::Generic::Dictionary<System::String^, System::Object^>^ dic = gcnew System::Collections::Generic::Dictionary<System::String^, System::Object^>(5);
			dic->Add("ファイル名", filepath);
			System::Collections::Generic::Dictionary<System::String^, System::Object^>^ ret = InvokeUserMethod("on効果音要求時", dic);
			if (ret != nullptr && ret->ContainsKey("ファイル名")) {
				System::String^ override_filename = (System::String^)(ret["ファイル名"]);
				if (System::String::IsNullOrEmpty(override_filename) == false) {
					strcpy_s(bufOverrideFileName, 512, to_native_string(override_filename).c_str());
				}
			}
		}
		catch (System::Exception^) {
			OutputDebugStream("on効果音要求時 でエラーが発声しました。");
		}
	}
}