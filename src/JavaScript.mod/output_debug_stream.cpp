#include <windows.h>

using namespace System;

void OutputDebugStream(Object^ obj) {
	System::Diagnostics::Trace::WriteLine(obj->ToString() + "\n");
}

void OutputDebugStream(String^ obj) {
	System::Diagnostics::Trace::WriteLine(obj + "\n");
}

