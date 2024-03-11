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

// 顔の画像は幅が64, 高さが80。マジックナンバーになってしまうが、今後変更になったりは永久にしないため、そのまま埋め込む。(そっちの方が定数名使うよりわかりやすい)

#pragma pack(1)
struct KAO_PICLINE {
    BYTE at[64];
};
#pragma pack()

#pragma pack(1)
struct KAO_PICTURE {
    KAO_PICLINE line[80];
};
#pragma pack()


bool isBattleFaceCondition(int iTargetKaoID) {
    int status = getゲーム画面ステータス();
    if (status == 将星録::列挙::ゲーム画面ステータス::野戦画面 ||
        status == 将星録::列挙::ゲーム画面ステータス::籠城戦画面) {
        return true;
    }

    for (int iUnitID = 0; iUnitID < 最大数::ユニット情報::配列数; iUnitID++) {
        // ユニット種別は軍勢、もしくは、軍船である
        int iBushouID = getBushouIDFromUnitID(iUnitID);
        if (isValidBushouID(iBushouID)) {
            if (nb7ユニット情報[iUnitID].種別 == 列挙::ユニット::種別::軍勢 || nb7ユニット情報[iUnitID].種別 == 列挙::ユニット::種別::軍船) {
                int iKaoID = nb7武将情報[iBushouID].顔番号;
                if (iKaoID == iTargetKaoID) {
					return true;
				}
            }
        }
    }

    return false;
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

    std::unique_ptr<KAO_PICTURE> picKaoFileOrigin(new KAO_PICTURE);
    std::unique_ptr<KAO_PICTURE> picKaoFlipSidePp(new KAO_PICTURE);

    char filenameBuf[512] = "";
    std::string filename = "";

    // C#のカスタム.mod.dllからの上書き
    try {
        System::Collections::Generic::Dictionary<System::String^, System::Object^>^ dic = gcnew System::Collections::Generic::Dictionary<System::String^, System::Object^>(5);
        dic->Add("顔番号", nTargetKaoID);
        System::Collections::Generic::Dictionary<System::String^, System::Object^>^ ret = InvokeUserMethod("on顔画像要求時", dic);
        if (ret != nullptr && ret->ContainsKey("ファイル名")) {
            System::String^ override_filename = (System::String^)(ret["ファイル名"]);
            if (System::String::IsNullOrEmpty(override_filename)) {
                OutputDebugStream("AAAAAA\n");
                ;
            }
            else {
                OutputDebugStream("BBBBBB\n");
                filename = to_native_string(override_filename);
            }
        }

    }
    catch (System::Exception^) {
        OutputDebugStream("on顔画像要求時でエラー");
    }


    // 戦闘中なら 0000_B.bmp のようなファイルが存在すればそちらを優先で使うことを試みる
    if (filename == "" && isBattleFaceCondition(nTargetKaoID)) {
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
        memcpy(picKaoFileOrigin.get(), buffer.data(), buffer.size());

        // 上下反転したものを picfileOrigin→picflipSidePp にコピー
        for (int i = 0; i < 80; i++) {
            memcpy(&(picKaoFlipSidePp->line[80-1 - i]), &(picKaoFileOrigin->line[i]), 64);
        }

        memcpy(lpBuffer, picKaoFlipSidePp.get(), (64 * 80));
    }


    return TRUE;
}





