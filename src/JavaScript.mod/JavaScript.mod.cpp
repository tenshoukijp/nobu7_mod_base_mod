#include <windows.h>

#include "JavaScript.mod.h"
#include "output_debug_stream.h"

using namespace System;

// �����^.mod.dll����Ă΂��֐��B�T�ˏ������ɌĂ΂��B
extern "C" __declspec(dllexport) void WINAPI onInitialize() {
	OutputDebugStream("JavaScript/onInitialize\r\n");
}

// �����^.mod.dll����Ă΂��֐��B�t�H���g�v����
extern "C" __declspec(dllexport) void WINAPI onRequestFont() {
	OutputDebugStream("JavaScript/onFontInitialize\r\n");
}

// �����^.mod.dll����Ă΂��֐��B�t�H���g�v����
extern "C" __declspec(dllexport) void WINAPI onRequestBGM() {
	OutputDebugStream("JavaScript/onRequestBGM\r\n");
}

// �����^.mod.dll����Ă΂��֐��B�t�H���g�v����
extern "C" __declspec(dllexport) void WINAPI onRequestSound() {
	OutputDebugStream("JavaScript/onRequestSound\r\n");
}

// �����^.mod.dll����Ă΂��֐��B�T�ˍŌ�ɌĂ΂��B
extern "C" __declspec(dllexport) void WINAPI onFinalize() {
	OutputDebugStream("JavaScript/onFinalize\r\n");
}
