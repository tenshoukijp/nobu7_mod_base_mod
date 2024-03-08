#include <windows.h>
#include <string>
#include "data_game_struct.h"
#include "output_debug_stream.h"
using namespace System;
using namespace System::Reflection;
using namespace System::Windows;
using namespace System::Collections::Generic;
using namespace 将星録;
ref class WPFGlobalInstance {
public:
	static Dictionary<String^, System::Windows::Window^>^ wpfMap = gcnew Dictionary<String^, System::Windows::Window^>();
};

[STAThread]
int Show_WpfMod(String^ dllPath, String^ fullClassName) {
	try {
		auto assembly = Assembly::LoadFrom(dllPath);

		auto type = assembly->GetType(fullClassName);
		// 型(Type)を取得したら、Activator.CreateInstanceメソッドを使用してインスタンスを作成します。

		auto wpf = safe_cast<System::Windows::Window^>(Activator::CreateInstance(type));
		// 最後に、Showメソッドを呼び出すことでフォームを表示します。

		if (WPFGlobalInstance::wpfMap->ContainsKey(dllPath)) {
			System::Windows::Window^ closeTargetWPF = WPFGlobalInstance::wpfMap[dllPath];
			closeTargetWPF->Close();
			closeTargetWPF = nullptr;
			WPFGlobalInstance::wpfMap->Remove(dllPath);
		}
		// インスタンス確保という意味でMapにファイルパス対応するフォームを登録する
		WPFGlobalInstance::wpfMap->Add(dllPath, wpf);

		wpf->ShowDialog();

		return 1;
	}
	catch (Exception^ ex) {
		System::Diagnostics::Trace::WriteLine(ex);
	}

	return 0;
}

[STAThread]
int Close_WpfMod() {
	try {
		for each (KeyValuePair<String^, System::Windows::Window^> ^ pair in WPFGlobalInstance::wpfMap) {
			System::Windows::Window^ wpf = pair->Value;
			wpf->Close();
			wpf = nullptr;
		}
		WPFGlobalInstance::wpfMap->Clear();
		return 1;
	}
	catch (Exception^ ex) {
		System::Diagnostics::Trace::WriteLine(ex);
	}

	return 0;
}