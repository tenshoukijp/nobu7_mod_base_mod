#include <windows.h>

#include "javascript_mod.h"
#include "output_debug_stream.h"
#include "mng_������ϊ�.h"

using namespace System;
using namespace System::Collections::Generic;




void callJSModMmioOpenA(char* pszFileName, char* bufOverrideFileName) {
	System::String^ filepath = gcnew System::String(pszFileName);
	System::String^ ret = IJavaScriptMod::onRequestSound(filepath->ToLower());
	if (!System::String::IsNullOrEmpty(ret)) {
		strcpy_s(bufOverrideFileName, 512, to_native_string(ret).c_str());
	}
}


void callJSModRequestBGM(char* pszFileName, char* bufOverrideFileName) {
	System::String^ filepath = gcnew System::String(pszFileName);
	System::String^ ret = IJavaScriptMod::onRequestBGM(filepath->ToLower());
	if (!System::String::IsNullOrEmpty(ret)) {
		strcpy_s(bufOverrideFileName, 512, to_native_string(ret).c_str());
	}
}

void callJSModRequestSound(char* pszFileName, char* bufOverrideFileName) {
	System::String^ filepath = gcnew System::String(pszFileName);
	System::String^ ret = IJavaScriptMod::onRequestSound(filepath->ToLower());
	if (!System::String::IsNullOrEmpty(ret)) {
		strcpy_s(bufOverrideFileName, 512, to_native_string(ret).c_str());
	}
}



std::string callJSModRequestBushouKaoID(int iKaoID) {
	System::String^ filepath = IJavaScriptMod::onRequestKaoID(iKaoID);
	if (System::String::IsNullOrEmpty(filepath)) { return ""; }
	return to_native_string(filepath);
}

std::string callJSModRequestKahouPicID(int iPicID) {
	System::String^ filepath = IJavaScriptMod::onRequestKahouPicID(iPicID);
	if (System::String::IsNullOrEmpty(filepath)) { return ""; }
	return to_native_string(filepath);
}


std::string callJSModRequestFile(const char* pszFileName) {
	System::String^ filepath = IJavaScriptMod::onRequestFile(gcnew System::String(pszFileName));
	if (System::String::IsNullOrEmpty(filepath)) { return ""; }
	return to_native_string(filepath);
}

std::string callJSModRequestBushouMessage(std::string message, std::vector<int> bushou_list) {
	System::Collections::Generic::List<int>^ gc_list = gcnew System::Collections::Generic::List<int>(0);
	for(int b : bushou_list) {
		gc_list->Add(b);
	}
	System::String^ ret = IJavaScriptMod::onRequestBushouMessage(gcnew System::String(message.c_str()), gc_list);
	if (System::String::IsNullOrEmpty(ret)) { return ""; }
	return to_native_string(ret);
}

