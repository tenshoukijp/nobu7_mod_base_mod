#include <windows.h>

#include "output_debug_stream.h"

HDC Hook_CreateCompatibleDCCustom(
	HDC hdc // デバイスコンテキストのハンドル
) {

	// OutputDebugStream("CreateCompatibleDC\n");

	return NULL;
}

