#pragma once

#include <windows.h>
#include <string>

#define �Z���t���b�Z�[�W�A�h���X 0x5D9638

extern BOOL isAlbedoYasenWeaponMessage;
extern BOOL isAlbedoYasenAttackMessage;

BOOL patchOfBushouMessage(HDC hdc, int nXStart, int nYStart, LPCTSTR lpString, int cbString);

BOOL onChangeSerifuMessage(std::string message);