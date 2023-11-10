#include <windows.h>
#include <string>

#include "window.h"

#include "bushou_retsuden.h"

using namespace std;


string bufferTextOut = "";
int nCheckTextOutYStart = -1;



BOOL Hook_TextOutACustom(
	HDC hdc,           // デバイスコンテキストのハンドル
	int nXStart,       // 開始位置（基準点）の x 座標
	int nYStart,       // 開始位置（基準点）の y 座標
	LPCTSTR lpString,  // 文字列
	int cbString       // 文字数
) {
	// ゴミが入っているようなので、cbStringの指定分だけ綺麗にMemcpyする
	char buffer[1024] = { 0 };
	memcpy(buffer, lpString, cbString);
	bufferTextOut += buffer;

	// バッファーの途中でYが変わったら、改行を追加
	if (nCheckTextOutYStart != nYStart) {
		if (bufferTextOut != "") {
			OutputDebugString("Yの違いを検知した");
			nCheckTextOutYStart = nYStart;
			bufferTextOut += "\n";
		}
	}

	// 武将列伝用の特別なパッチ処理
	pathOfBushouRetsuden(hdc, nXStart, nYStart, lpString, cbString);

	return TRUE;
}
