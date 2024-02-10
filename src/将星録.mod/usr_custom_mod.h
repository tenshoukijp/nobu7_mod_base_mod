#pragma once


bool LoadUserMod();

bool IsExistUserMethod(System::String^ methodname);

System::Reflection::MethodInfo^ GetUserMethod(System::String^ methodname);

System::Collections::Generic::Dictionary<System::String^, System::Object^>^ InvokeUserMethod(System::String^ methodname, System::Collections::Generic::Dictionary<System::String^, System::Object^>^ parameters);