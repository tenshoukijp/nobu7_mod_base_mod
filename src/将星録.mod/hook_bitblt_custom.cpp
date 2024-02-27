#include <windows.h>
#include "output_debug_stream.h"


BOOL Hook_BitBltCustom(
    HDC hdcDest, // 出力デバイスコンテキストのハンドル
    int nXDest,  // 出力先の長方形の左上隅の x 座標
    int nYDest,  // 出力先の長方形の左上隅の y 座標
    int nWidth,  // 出力先の長方形の幅（ピクセル単位）
    int nHeight, // 出力先の長方形の高さ（ピクセル単位）
    HDC hdcSrc,  // 入力デバイスコンテキストのハンドル
    int nXSrc,   // 入力元の長方形の左上隅の x 座標
    int nYSrc,   // 入力元の長方形の左上隅の y 座標
    DWORD dwRop  // ラスタオペレーションコード
) {
    /*
    OutputDebugStream("BitBlt\n");
    */
    return TRUE;
}


