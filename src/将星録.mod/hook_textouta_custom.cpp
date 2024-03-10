#include <windows.h>
#include <string>

#include <memory>

#include "game_window.h"

#include "hook_textouta_custom.h"

#include "on_serihu_message.h"

using namespace std;


string bufferTextOut = "";
int nCheckTextOutYStart = -1;
int nCheckTextOutXStart = -1;

const string getBufferTextOut() {
	return bufferTextOut;
}


extern string prevSerihuMessage;

BOOL Hook_TextOutACustom(
	HDC hdc,           // デバイスコンテキストのハンドル
	int nXStart,       // 開始位置（基準点）の x 座標
	int nYStart,       // 開始位置（基準点）の y 座標
	LPCTSTR lpString,  // 文字列
	int cbString       // 文字数
) {
	// ゴミが入っているようなので、cbStringの指定分だけ綺麗にMemcpyする
	std::unique_ptr<char[]> buffer(new char[cbString + 2]);
	memset(buffer.get(), 0, cbString + 2);

	memcpy(buffer.get(), lpString, cbString);
	bufferTextOut += buffer.get();

	return TRUE;
}
