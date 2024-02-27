#include <windows.h>
#include <string>
#include "output_debug_stream.h"

#include "mng_文字列変換.h"
#include "usr_custom_mod.h"

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

	System::Collections::Generic::Dictionary<System::String^, System::Object^>^ dic = gcnew System::Collections::Generic::Dictionary<System::String^, System::Object^>(5);
	System::Collections::Generic::Dictionary<System::String^, System::Object^>^ ret = InvokeUserMethod("onフォント要求時", dic);

	try {
		if (ret != nullptr && ret->ContainsKey("フォント名")) {
			System::String^ filename = (System::String^)(ret["フォント名"]);
			std::string native_fontname = to_native_string(filename);

			if (native_fontname != "") {
				// フォント名を上書きする
				strcpy_s(bufferCustomFontName, native_fontname.c_str());
				return bufferCustomFontName;
			}
		}

		else if (isFontExist) {
			return bufferCustomFontName;
		}
	}
	catch (Exception^ /*ex*/) {
		OutputDebugStream("onフォント要求時 にエラーが発生しました");
	}

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
				if (valueName->Contains(targetFontName)) {
					// フォント名が指定のフォント名を含んでいる場合は、フォントを追加する
					FontGlobal::pfc->AddFontFile(path);
				}
				FontGlobal::pfc->AddFontFile(path);
			}

			// 独自フォント一覧に指定のフォントが存在するかどうかをチェックする
			for each (System::Drawing::FontFamily^ font in FontGlobal::pfc->Families) {
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

		for each (System::Drawing::FontFamily^ font in fonts->Families) {
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