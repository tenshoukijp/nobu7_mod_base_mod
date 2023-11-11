#include <windows.h>
#include <string>

#include "window.h"

#include "bushou_retsuden.h"

using namespace std;


string bufferTextOut = "";
int nCheckTextOutYStart = -1;
int nCheckTextOutXStart = -1;

const string getBufferTextOut() {
	return bufferTextOut;
}


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

	// 武将列伝用の特別なパッチ処理
	pathOfBushouRetsuden(hdc, nXStart, nYStart, lpString, cbString);

	return TRUE;
}
