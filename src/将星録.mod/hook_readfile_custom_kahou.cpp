#include <Windows.h>

#include <fstream>
#include <iostream>
#include <vector>
#include <windows.h>
#include <string>
#include "output_debug_stream.h"
#include "file_attribute.h"
#include "game_screen.h"
#include "data_game_struct.h"

// 家宝の画像は幅が64, 高さが64。マジックナンバーになってしまうが、今後変更になったりは永久にしないため、そのまま埋め込む。(そっちの方が定数名使うよりわかりやすい)

struct KAHOU_PICLINE {
    BYTE at[64];
};
struct KAHOU_PICTURE {
    KAHOU_PICLINE line[64];
};

extern int iKahouIDOfLastShowKahouID;
extern int nTargetKahouGazouID;
BOOL Hook_ReadFileCustom_KahouPic(
    HANDLE hFile, // ファイルのハンドル
    LPVOID lpBuffer, // データの格納先
    DWORD nNumberOfBytesToRead, // 読み込むバイト数
    LPDWORD lpNumberOfBytesRead, // 実際に読み込んだバイト数
    LPOVERLAPPED lpOverlapped // オーバーラップ構造体のポインタ
) {
    if (nTargetKahouGazouID < 0) {
        return FALSE;
    }

    KAHOU_PICTURE picItemFileOrigin = { 0 };
    KAHOU_PICTURE picItemFlipSidePp = { 0 };

    std::string filename = "";

    if (isValidKahouID(iKahouIDOfLastShowKahouID)) {
        char filenameBuf[512] = "";
        sprintf_s(filenameBuf, "OVERRIDE\\ITEMDATA\\%s.bmp", nb7家宝情報[iKahouIDOfLastShowKahouID].家宝名);
        OutputDebugStream("★★★はあるか？%s\n", filenameBuf);
        if (isFileExists(filenameBuf)) {
            filename = filenameBuf;
        }
    }

    if (filename == "") {
        char filenameBuf[512] = "";
        sprintf_s(filenameBuf, "OVERRIDE\\ITEMDATA\\%03d.bmp", nTargetKahouGazouID);
        OutputDebugStream("★★★はあるか？%s\n", filenameBuf);
        if (isFileExists(filenameBuf)) {
            filename = filenameBuf;
        }
    }

    if (filename == "") {
        return FALSE;
    }

    if (!isFileExists(filename)) {
        return FALSE;
    }

    std::ifstream file(filename, std::ios::binary);

    if (!file) {
        OutputDebugStream("ファイル" + filename + "を開くことができませんでした。\n");
        return FALSE;
    }

    file.seekg(-(64 * 64), std::ios::end);

    std::vector<char> buffer(64 * 64);
    file.read(buffer.data(), buffer.size());

    if (file.fail()) {
        OutputDebugStream("ファイル" + filename + "の読み込みに失敗しました。\n");
        return FALSE;
    }

    // 元の画像をコピー
    if (nNumberOfBytesToRead == buffer.size()) {
        memcpy(&picItemFileOrigin, buffer.data(), buffer.size());

        // 上下反転したものを picfileOrigin→picflipSidePp にコピー
        for (int i = 0; i < 64; i++) {
            memcpy(&(picItemFlipSidePp.line[64 - 1 - i]), &(picItemFileOrigin.line[i]), 64);
        }

        memcpy(lpBuffer, &picItemFlipSidePp, (64 * 64));
    }


    return TRUE;
}
