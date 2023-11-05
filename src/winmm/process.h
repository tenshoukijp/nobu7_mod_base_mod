#pragma once

#include <string>

extern BOOL isTargetProcess;

BOOL IsWow64();

std::string GetCurrentProcessFullPath();

// 現在実行中の自分のプロセスのウィンドウハンドルを得る。
HWND GetCurrentWindowHandle();

BOOL IsMatchCurrentClass(const char* programName);