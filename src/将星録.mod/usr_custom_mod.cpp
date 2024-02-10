/*
    // DLL�̃p�X���w��
    System::String^ dllPath = "�J�X�^��mod.dll";

    // DLL�����[�h
    System::Reflection::Assembly^ assembly = System::Reflection::Assembly::LoadFrom(dllPath);

    // �ÓI�N���X��Type�I�u�W�F�N�g���擾�i"Namespace.ClassName"�Ŏw��j
    Type^ type = assembly->GetType("�J�X�^��mod");

    // �ÓI���\�b�h��MethodInfo�I�u�W�F�N�g���擾
    System::Reflection::MethodInfo^ methodInfo = type->GetMethod("������");
*/
#include "output_debug_stream.h"
#include "mng_������ϊ�.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Reflection;


private ref class GlobalAssemblyCache {
public:
    static Assembly^ user_custom_assembly = nullptr;
	static Type^ user_custom_type = nullptr;
    static Dictionary<String^, MethodInfo^>^ user_custom_methods = gcnew Dictionary<String^, MethodInfo^>(100);
};

bool LoadUserMod() {
	try {
		// DLL�̃p�X���w��
		String^ dllPath = "�J�X�^��.mod.dll";

		// DLL�����[�h
		GlobalAssemblyCache::user_custom_assembly = Assembly::LoadFrom(dllPath);

		if (GlobalAssemblyCache::user_custom_assembly == nullptr) {
			return false;
		}

		// �ÓI�N���X��Type�I�u�W�F�N�g���擾�i"Namespace.ClassName"�Ŏw��j
		GlobalAssemblyCache::user_custom_type = GlobalAssemblyCache::user_custom_assembly->GetType("�����^.�J�X�^��");

		if (GlobalAssemblyCache::user_custom_type == nullptr) {
			return false;
		}

		return true;
	}
	catch (Exception^) {
		return false;
	}

	return false;
}

bool IsExistUserMethod(String^ methodname) {

	try {
		if (String::IsNullOrEmpty(methodname)) {
			return false;
		}
		if (GlobalAssemblyCache::user_custom_assembly == nullptr) {
			return false;
		}
		if (GlobalAssemblyCache::user_custom_type == nullptr) {
			return false;
		}

		// �ÓI���\�b�h��MethodInfo�I�u�W�F�N�g���擾
		MethodInfo^ methodInfo = GlobalAssemblyCache::user_custom_type->GetMethod(methodname);

		if (methodInfo == nullptr) {
			return false;
		}

		if (GlobalAssemblyCache::user_custom_methods->ContainsKey(methodname)) {
			return true;
		}
		else {
			GlobalAssemblyCache::user_custom_methods->Add(methodname, methodInfo);
		}

		return true;
	} 
	catch (Exception^ e) {
		System::Diagnostics::Trace::WriteLine("InvokeUserMethod Error" + e->Message);
		return false;
	}

	return false;
}

System::Reflection::MethodInfo^ GetUserMethod(System::String^ methodname) {
	try {
		if (IsExistUserMethod(methodname)) {
			MethodInfo^ methodinfo;
			GlobalAssemblyCache::user_custom_methods->TryGetValue(methodname, methodinfo);
			return methodinfo;
		}
		else {
			return nullptr;
		}
	}
	catch (Exception^) {
		return nullptr;
	}

	return nullptr;
}

System::Collections::Generic::Dictionary<System::String^, System::Object^>^ InvokeUserMethod(String^ methodname, System::Collections::Generic::Dictionary<System::String^, System::Object^>^ dic) {
	try {
		MethodInfo^ methodinfo = GetUserMethod(methodname);
		if (methodinfo == nullptr) {
			OutputDebugStream(to_native_string(methodname + "�͖���\n"));
			return nullptr;
		}

		array<Object^>^ parameters = gcnew array<Object^> { dic };

		Object^ result = methodinfo->Invoke(nullptr, parameters);
		Dictionary<String^, Object^>^ resultDic = (Dictionary<String^, Object^>^)result;
		return resultDic;

	} catch (Exception^ e) {
		OutputDebugStream(to_native_string(methodname + "���s�G���[ Error" + e->Message + "\n"));
		return nullptr;
	}

	return nullptr;
}