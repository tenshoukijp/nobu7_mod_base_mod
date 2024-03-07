#pragma once

/*
#include <windows.h>
#include <memory>

struct WINFRAME_NB7_CHUNK {
	int start_address;
	int byte_length;
	int width;
	int height;
};

struct WINFRAME_NB7_HEADER
{
	WINFRAME_NB7_CHUNK chunk[0x1D4]; // WINFRAME.NB7は全部で468個の画像
};

#define WINFRAME_NB7_CHUNK_COUNT 0x1D4

#define WINFRAME_NB7_ALL_HEADER_SIZE (sizeof(WINFRAME_NB7_HEADER) + 4) // 最初の４バイト分、CHUNKの数が入っている

extern std::unique_ptr<WINFRAME_NB7_HEADER> winframe_nb7_header;

*/