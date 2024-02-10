/*
    // DLLのパスを指定
    System::String^ dllPath = "カスタムmod.dll";

    // DLLをロード
    System::Reflection::Assembly^ assembly = System::Reflection::Assembly::LoadFrom(dllPath);

    // 静的クラスのTypeオブジェクトを取得（"Namespace.ClassName"で指定）
    Type^ type = assembly->GetType("カスタムmod");

    // 静的メソッドのMethodInfoオブジェクトを取得
    System::Reflection::MethodInfo^ methodInfo = type->GetMethod("あいう");
*/


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
		// DLLのパスを指定
		String^ dllPath = "カスタム.mod.dll";

		// DLLをロード
		GlobalAssemblyCache::user_custom_assembly = Assembly::LoadFrom(dllPath);

		if (GlobalAssemblyCache::user_custom_assembly == nullptr) {
			return false;
		}

		// 静的クラスのTypeオブジェクトを取得（"Namespace.ClassName"で指定）
		GlobalAssemblyCache::user_custom_type = GlobalAssemblyCache::user_custom_assembly->GetType("将星録.カスタム");

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

		// 静的メソッドのMethodInfoオブジェクトを取得
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
			System::Diagnostics::Trace::WriteLine("メソッドはnullptr");
			return nullptr;
		}

		array<Object^>^ parameters = gcnew array<Object^> { dic };

		System::Diagnostics::Trace::WriteLine("★呼び出し前");
		Object^ result = methodinfo->Invoke(nullptr, parameters);
		System::Diagnostics::Trace::WriteLine("★返り値キャスト前");
		Dictionary<String^, Object^>^ resultDic = (Dictionary<String^, Object^>^)result;
		System::Diagnostics::Trace::WriteLine("★返り値を返す前");
		return resultDic;

	} catch (Exception^ e) {
		System::Diagnostics::Trace::WriteLine("★InvokeUserMethod Error" + e->Message);
		return nullptr;
	}

	return nullptr;
}