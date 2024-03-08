#include <windows.h>
#include <string>
#include "data_game_struct.h"
#include "output_debug_stream.h"
#include "load_form_mod.h"

using namespace System;
using namespace System::Reflection;
using namespace System::Windows::Forms;
using namespace System::Collections::Generic;
using namespace 将星録;
ref class FormGlobalInstance {
public:
	static Dictionary<String^, Form^>^ formMap = gcnew Dictionary<String^, Form^>();
};

int Show_FormMod(String^ dllPath, String^ fullClassName) {
	try {
		auto assembly = Assembly::LoadFrom(dllPath);

		auto type = assembly->GetType(fullClassName);
		// 型(Type)を取得したら、Activator.CreateInstanceメソッドを使用してインスタンスを作成します。

		auto form = safe_cast<Form^>(Activator::CreateInstance(type));
		// 最後に、Showメソッドを呼び出すことでフォームを表示します。

		if (FormGlobalInstance::formMap->ContainsKey(dllPath)) {
			Form^ closeTargetForm = FormGlobalInstance::formMap[dllPath];
			closeTargetForm->Close();
			closeTargetForm = nullptr;
			FormGlobalInstance::formMap->Remove(dllPath);
		}
		// インスタンス確保という意味でMapにファイルパス対応するフォームを登録する
		FormGlobalInstance::formMap->Add(dllPath, form);

		form->ShowDialog();

		return 1;
	}
	catch (Exception^ ex) {
		System::Diagnostics::Trace::WriteLine(ex);
	}

	return 0;
}

int Close_FormMod() {
	try {
		for each (KeyValuePair<String^, Form^>^ pair in FormGlobalInstance::formMap) {
			Form^ form = pair->Value;
			form->Close();
			form = nullptr;
		}
		FormGlobalInstance::formMap->Clear();
		return 1;
	}
	catch (Exception^ ex) {
		System::Diagnostics::Trace::WriteLine(ex);
	}

	return 0;
}