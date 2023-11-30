#include <windows.h>
#include <winuser.h>
#include <stdio.h>
#include <vector>
#include <string>
#include "data_game_struct.h"
#include "game_window.h"
#include "process.h"
#include "output_debug_stream.h"

using namespace System;
using namespace Microsoft::Win32;
using namespace System::Drawing;
using namespace System::Windows::Forms;
/*
005056B5   68 04EE5300      PUSH Nobunaga.0053EE04
005056BA   53               PUSH EBX
005056BB   53               PUSH EBX
005056BC   53               PUSH EBX
005056BD   53               PUSH EBX
005056BE   68 80000000      PUSH 80
005056C3   53               PUSH EBX
005056C4   53               PUSH EBX
005056C5   53               PUSH EBX
005056C6   53               PUSH EBX
005056C7   53               PUSH EBX
005056C8   53               PUSH EBX
005056C9   6A 08            PUSH 8
005056CB   6A F0            PUSH -10
 */

// フォントチェックをしてしまうと起動が重くなりすぎて正常に起動できなくなってしまうようだ。
BOOL fontExistCheck();
bool isFontExist = false;
void onFontInitialize() {
	isFontExist = fontExistCheck();
}




//------------------------------------------------
// 上書き用のフォント名。長いフォント名も可能。将来はJavaScriptか何か外部テキストから変更できるようにしたい。
//------------------------------------------------
char bufferCustomFontName[32] = "将星 明朝";
char bufferDefaultFontName[32] = "ＭＳ 明朝";
const char* getNB7FontName() {
	if (isFontExist) {
		return bufferCustomFontName;
	}
	OutputDebugStream("指定のフォントは存在しないため、デフォルトのフォントを使用します。\n");
	// そのまま返す
	return bufferDefaultFontName;
}


ref class FontGlobal {
public:
	static System::Drawing::Text::PrivateFontCollection^ pfc;
};

BOOL fontExistCheck() {

	// システムではなく、プライベートフォントとして、ユーザー専用としてインストールしたフォントを検索する
	FontGlobal::pfc = gcnew System::Drawing::Text::PrivateFontCollection();
	RegistryKey^ key = nullptr;
	// 比較対象のフォント。
	String^ targetFontName = gcnew String(bufferCustomFontName);
	try
	{
		key = Registry::CurrentUser->OpenSubKey(R"(Software\Microsoft\Windows NT\CurrentVersion\Fonts)");
		array<String^>^ valueNames = key == nullptr ? nullptr : key->GetValueNames();
		if (valueNames != nullptr)
		{
			for each (String ^ valueName in valueNames)
			{
				String^ path = key->GetValue(valueName)->ToString();
				FontGlobal::pfc->AddFontFile(path);
			}

			// 独自フォント一覧に指定のフォントが存在するかどうかをチェックする
			for (int i = 0; FontGlobal::pfc->Families->Length; i++) {
				System::Drawing::FontFamily^ font = FontGlobal::pfc->Families[i];
				if (font->Name == targetFontName) {
					isFontExist = true;
					return TRUE;
				}
			}
		}
	}
	catch (Exception^ /*ex1*/) {

	}
	finally
	{
		if (key != nullptr) {
			key->Close();
		}
	}

	try {
		// 独自フォントではなく最初からウィンドウズに入っているフォントを指定しているかもしれない。
		System::Drawing::Text::InstalledFontCollection^ fonts = gcnew System::Drawing::Text::InstalledFontCollection();

		for (int i = 0; fonts->Families->Length; i++) {
			System::Drawing::FontFamily^ font = FontGlobal::pfc->Families[i];
			if (font->Name == targetFontName) {
				isFontExist = true;
				return TRUE;
			}
		}
	}
	catch (Exception^ /*ex2*/) {

	}
	finally {
	}

	return FALSE;
}