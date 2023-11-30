#include <string>
#include "output_debug_stream.h"
#include "data_game_struct.h"
#include <windows.h>
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
			Form^ closeTargefForm = FormGlobalInstance::formMap[dllPath];
			closeTargefForm->Close();
			closeTargefForm = nullptr;
			FormGlobalInstance::formMap->Remove(dllPath);
			FormGlobalInstance::formMap->Add(dllPath, form);
		}

		form->Show();

		return 1;
	}
	catch (Exception^ ex) {
		System::Diagnostics::Trace::WriteLine(ex);
	}

	return 0;
}