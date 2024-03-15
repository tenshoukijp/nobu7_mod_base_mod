#pragma once

using namespace System;
using namespace System::Reflection;
using namespace System::Windows::Forms;
using namespace System::Collections::Generic;
using namespace System::Threading;


ref class FormGlobalInstance {
public:
	static Dictionary<String^, Form^>^ formMap = gcnew Dictionary<String^, Form^>();
	static Dictionary<String^, Thread^>^ threadMap = gcnew Dictionary<String^, Thread^>();
};



int Show_FormMod(System::String^ dllPath, System::String^ fullClassName);

int Close_FormMod();