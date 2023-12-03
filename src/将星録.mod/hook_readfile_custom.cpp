#include <Windows.h>

#include <fstream>
#include <iostream>
#include <vector>
#include <windows.h>
#include "output_debug_stream.h"

// 顔の画像は幅が64, 高さが80。マジックナンバーになってしまうが、今後変更になったりは永久にしないため、そのまま埋め込む。(そっちの方が定数名使うよりわかりやすい)

struct KAO_PICLINE {
    BYTE at[64];
};
struct KAO_PICTURE {
    KAO_PICLINE line[80];
};

KAO_PICTURE picfileOrigin = { 0 };
KAO_PICTURE picflipSidePp = { 0 };

bool fileExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good(); // ファイルが存在すればtrueを返す
}
extern int nTargetKaoID;
BOOL Hook_ReadFileCustom(
    HANDLE hFile, // ファイルのハンドル
    LPVOID lpBuffer, // データの格納先
    DWORD nNumberOfBytesToRead, // 読み込むバイト数
    LPDWORD lpNumberOfBytesRead, // 実際に読み込んだバイト数
    LPOVERLAPPED lpOverlapped // オーバーラップ構造体のポインタ
) {

    char filenameBuf[512] = "";
    sprintf_s(filenameBuf, "KAODATA\\%04d.bmp", nTargetKaoID);
    OutputDebugStream("★★★はあるか？%s\n" ,filenameBuf);
    std::string filename = filenameBuf;
    if (!fileExists(filename)) {
        return FALSE;
    }

    std::ifstream file(filename, std::ios::binary);

    if (!file) {
        OutputDebugStream("ファイル" + filename + "を開くことができませんでした。\n");
        return FALSE;
    }

    file.seekg(-(64 * 80), std::ios::end);

    std::vector<char> buffer(64 * 80);
    file.read(buffer.data(), buffer.size());

    if (file.fail()) {
        OutputDebugStream("ファイル" + filename + "の読み込みに失敗しました。\n");
        return FALSE;
    }

    // 元の画像をコピー
    if (nNumberOfBytesToRead == buffer.size()) {
        memcpy(&picfileOrigin, buffer.data(), buffer.size());

        // 上下反転したものを picfileOrigin→picflipSidePp にコピー
        for (int i = 0; i < 80; i++) {
            memcpy(&(picflipSidePp.line[79 - i]), &(picfileOrigin.line[i]), 64);
        }

        memcpy(lpBuffer, &picflipSidePp, 64 * 80);
    }


    return TRUE;
}
