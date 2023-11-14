#include <windows.h>
#include "output_debug_stream.h"

int Hook_GetDIBitsCustom(
    HDC hdc, // デバイスコンテキストのハンドル
    HBITMAP hbm, // ビットマップのハンドル
    UINT start, // スキャンラインの最初のインデックス
    UINT cLines, // スキャンラインの数
    LPVOID lpvBits, // ビットマップデータのポインタ
    LPBITMAPINFO lpbmi, // ビットマップ情報のポインタ
    UINT usage // ビットマップの使用方法
) {

    return 1;
}