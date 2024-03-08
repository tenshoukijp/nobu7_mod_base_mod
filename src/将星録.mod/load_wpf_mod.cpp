#include <windows.h>
#include <string>
#include "data_game_struct.h"
#include "output_debug_stream.h"
using namespace System;
using namespace System::Reflection;
using namespace System::Windows;
using namespace System::Collections::Generic;
using namespace �����^;
ref class WPFGlobalInstance {
public:
	static Dictionary<String^, System::Windows::Window^>^ wpfMap = gcnew Dictionary<String^, System::Windows::Window^>();
};

[STAThread]
int Show_WpfMod(String^ dllPath, String^ fullClassName) {
	try {
		auto assembly = Assembly::LoadFrom(dllPath);

		auto type = assembly->GetType(fullClassName);
		// �^(Type)���擾������AActivator.CreateInstance���\�b�h���g�p���ăC���X�^���X���쐬���܂��B

		auto wpf = safe_cast<System::Windows::Window^>(Activator::CreateInstance(type));
		// �Ō�ɁAShow���\�b�h���Ăяo�����ƂŃt�H�[����\�����܂��B

		if (WPFGlobalInstance::wpfMap->ContainsKey(dllPath)) {
			System::Windows::Window^ closeTargetWPF = WPFGlobalInstance::wpfMap[dllPath];
			closeTargetWPF->Close();
			closeTargetWPF = nullptr;
			WPFGlobalInstance::wpfMap->Remove(dllPath);
		}
		// �C���X�^���X�m�ۂƂ����Ӗ���Map�Ƀt�@�C���p�X�Ή�����t�H�[����o�^����
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