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

#include "usr_custom_mod.h"

// 家宝の画像は幅が24, 高さが24。マジックナンバーになってしまうが、今後変更になったりは永久にしないため、そのまま埋め込む。(そっちの方が定数名使うよりわかりやすい)

#pragma pack(1)
struct KAMON_PICLINE {
    BYTE at[24];
};
#pragma pack()

#pragma pack(1)
struct KAMON_PICTURE {
    KAMON_PICLINE line[24];
};
#pragma pack()

extern int nTargetKamonID;
BOOL Hook_ReadFileCustom_KamonPic(
    HANDLE hFile, // ファイルのハンドル
    LPVOID lpBuffer, // データの格納先
    DWORD nNumberOfBytesToRead, // 読み込むバイト数
    LPDWORD lpNumberOfBytesRead, // 実際に読み込んだバイト数
    LPOVERLAPPED lpOverlapped // オーバーラップ構造体のポインタ
) {
    if (nTargetKamonID < 0) {
        return FALSE;
    }

    std::unique_ptr<KAMON_PICTURE> pickamonFileOrigin(new KAMON_PICTURE);
    std::unique_ptr<KAMON_PICTURE> pickamonFlipSidePp(new KAMON_PICTURE);
    /*
    KAMON_PICTURE pickamonFileOrigin = { 0 };
    KAMON_PICTURE pickamonFlipSidePp = { 0 };
    */
    std::string filename = "";

    // C#のカスタム.mod.dllからの上書き
    try {
        System::Collections::Generic::Dictionary<System::String^, System::Object^>^ dic = gcnew System::Collections::Generic::Dictionary<System::String^, System::Object^>(5);
        dic->Add("家紋番号", nTargetKamonID);
        System::Collections::Generic::Dictionary<System::String^, System::Object^>^ ret = InvokeUserMethod("on家紋画像要求時", dic);
        if (ret != nullptr && ret->ContainsKey("ファイル名")) {
            System::String^ override_filename = (System::String^)(ret["ファイル名"]);
            if (System::String::IsNullOrEmpty(override_filename)) {
                ;
            }
            else {
                filename = to_native_string(override_filename);
            }
        }

    }
    catch (System::Exception^) {
        OutputDebugStream("on家紋画像要求時でエラー");
    }


    if (filename == "") {
        char filenameBuf[512] = "";
        sprintf_s(filenameBuf, "OVERRIDE\\KAMON\\%03d.bmp", nTargetKamonID);
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

    file.seekg(-(24 * 24), std::ios::end);

    std::vector<char> buffer(24 * 24);
    file.read(buffer.data(), buffer.size());

    if (file.fail()) {
        OutputDebugStream("ファイル" + filename + "の読み込みに失敗しました。\n");
        return FALSE;
    }

    // 元の画像をコピー
    if (nNumberOfBytesToRead == buffer.size()) {
        memcpy(pickamonFileOrigin.get(), buffer.data(), buffer.size());

        // 上下反転したものを picfileOrigin→picflipSidePp にコピー
        for (int i = 0; i < 24; i++) {
            memcpy(&(pickamonFlipSidePp->line[24 - 1 - i]), &(pickamonFileOrigin->line[i]), 24);
        }

        memcpy(lpBuffer, pickamonFlipSidePp.get(), (24 * 24));
    }


    return TRUE;
}
