#pragma once

#include <windows.h>

BOOL loadNB7Mod();

void freeNB7Mod();

void Mod_onInitialize();

void Mod_onGameInitialize(HWND);

void Mod_onFinalize();
