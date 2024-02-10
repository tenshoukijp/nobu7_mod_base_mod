#pragma once

#include <string>
#include <vector>


void callJSModMmioOpenA(char* pszFileName, char* bufOverrideFileName);

void callJSModRequestSound(char* pszFileName, char* bufOverrideFileName);
void callJSModRequestBGM(char* pszFileName, char* bufOverrideFileName);


std::string callJSModRequestFile(const char* pszFileName);

std::string callJSModRequestBushouKaoID(int iKaoID);

std::string callJSModRequestKahouPicID(int iPicID);

std::string callJSModRequestBushouMessage(std::string message, std::vector<int> bushou_list);

