#pragma once

#include <string>

extern BOOL isTargetProcess;

BOOL IsWow64();

std::string GetCurrentProcessFullPath();

// ���ݎ��s���̎����̃v���Z�X�̃E�B���h�E�n���h���𓾂�B
HWND GetCurrentWindowHandle();

BOOL IsMatchCurrentClass(const char* programName);