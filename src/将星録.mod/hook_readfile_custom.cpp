#include <Windows.h>

#include <fstream>
#include <iostream>
#include <vector>
#include <windows.h>
#include "output_debug_stream.h"
#include "file_attribute.h"
#include "game_screen.h"

// 顔の画像は幅が64, 高さが80。マジックナンバーになってしまうが、今後変更になったりは永久にしないため、そのまま埋め込む。(そっちの方が定数名使うよりわかりやすい)

struct KAO_PICLINE {
    BYTE at[64];
};
struct KAO_PICTURE {
    KAO_PICLINE line[80];
};

KAO_PICTURE picKaoFileOrigin = { 0 };
KAO_PICTURE picKaoFlipSidePp = { 0 };

bool fileExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good(); // ファイルが存在すればtrueを返す
}
extern int nTargetKaoID;
BOOL Hook_ReadFileCustom_BushouKao(
    HANDLE hFile, // ファイルのハンドル
    LPVOID lpBuffer, // データの格納先
    DWORD nNumberOfBytesToRead, // 読み込むバイト数
    LPDWORD lpNumberOfBytesRead, // 実際に読み込んだバイト数
    LPOVERLAPPED lpOverlapped // オーバーラップ構造体のポインタ
) {
    if (nTargetKaoID < 0) {
        return FALSE;
    }

    char filenameBuf[512] = "";
    std::string filename = "";
    int status = getゲーム画面ステータス();

    // 戦闘中なら 0000_B.bmp のようなファイルが存在すればそちらを優先で使うことを試みる
    if (status == 将星録::列挙::ゲーム画面ステータス::野戦画面 || status == 将星録::列挙::ゲーム画面ステータス::籠城戦画面) {
        sprintf_s(filenameBuf, "OVERRIDE\\KAODATA\\%04d_B.bmp", nTargetKaoID);
        OutputDebugStream("★★★はあるか？%s\n", filenameBuf);
        if (isFileExists(filenameBuf)) {
            filename = filenameBuf;
        }
    }

    // 0000_Bファイルが存在しないか、もしくは戦闘中以外は、0000.bmp のようなファイルを使うことを試みる
    if (filename == "") {
        sprintf_s(filenameBuf, "OVERRIDE\\KAODATA\\%04d.bmp", nTargetKaoID);
        OutputDebugStream("★★★はあるか？%s\n", filenameBuf);
        if (isFileExists(filenameBuf)) {
            filename = filenameBuf;
        }
    }

    if (filename == "" || !isFileExists(filename)) {
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
        memcpy(&picKaoFileOrigin, buffer.data(), buffer.size());

        // 上下反転したものを picfileOrigin→picflipSidePp にコピー
        for (int i = 0; i < 80; i++) {
            memcpy(&(picKaoFlipSidePp.line[80-1 - i]), &(picKaoFileOrigin.line[i]), 64);
        }

        memcpy(lpBuffer, &picKaoFlipSidePp, (64 * 80));
    }


    return TRUE;
}






struct KAHOU_PICLINE {
    BYTE at[64];
};
struct KAHOU_PICTURE {
    KAHOU_PICLINE line[64];
};

KAHOU_PICTURE picItemFileOrigin = { 0 };
KAHOU_PICTURE picItemFlipSidePp = { 0 };

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

    char filenameBuf[512] = "";
    sprintf_s(filenameBuf, "OVERRIDE\\ITEMDATA\\%03d.bmp", nTargetKahouGazouID);
    OutputDebugStream("★★★はあるか？%s\n", filenameBuf);
    std::string filename = filenameBuf;
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
            memcpy(&(picItemFlipSidePp.line[64-1 - i]), &(picItemFileOrigin.line[i]), 64);
        }

        memcpy(lpBuffer, &picItemFlipSidePp, (64 * 64));
    }


    return TRUE;
}
