#pragma once

#include <string>
#include <vector>

void callJSModCreateWindow(HWND hWnd);

std::string callJSModRequestFont();

void callJSModMmioOpenA(char* pszFileName, char* bufOverrideFileName);

void callJSModRequestSound(char* pszFileName, char* bufOverrideFileName);
void callJSModRequestBGM(char* pszFileName, char* bufOverrideFileName);

void callJSModDestroyWindow();

std::string callJSModRequestFile(const char* pszFileName);

std::string callJSModRequestBushouKaoID(int iKaoID);

std::string callJSModRequestKahouPicID(int iPicID);

std::string callJSModRequestBushouMessage(std::string message, std::vector<int> bushou_list);

