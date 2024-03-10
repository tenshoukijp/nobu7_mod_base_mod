#pragma once

/*
#include <windows.h>
#include <memory>

#pragma pack(1)
struct WINFRAME_NB7_CHUNK {
	int start_address;
	int byte_length;
	int width;
	int height;
};
#pragma pack()

#pragma pack(1)
struct WINFRAME_NB7_HEADER
{
	WINFRAME_NB7_CHUNK chunk[0x1D4]; // WINFRAME.NB7は全部で468個の画像
};
#pragma pack()


#define WINFRAME_NB7_CHUNK_COUNT 0x1D4

#define WINFRAME_NB7_ALL_HEADER_SIZE (sizeof(WINFRAME_NB7_HEADER) + 4) // 最初の４バイト分、CHUNKの数が入っている

extern std::unique_ptr<WINFRAME_NB7_HEADER> winframe_nb7_header;

*/