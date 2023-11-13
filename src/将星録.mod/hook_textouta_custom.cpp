#include <windows.h>
#include <string>

#include "window.h"

#include "hook_textouta_custom.h"

#include "bushou_retsuden.h"
#include "on_serihu_message.h"

using namespace std;


string bufferTextOut = "";
int nCheckTextOutYStart = -1;
int nCheckTextOutXStart = -1;

const string getBufferTextOut() {
	return bufferTextOut;
}

BOOL isNextStartOverride = false;  // 次にTextOutAが呼ばれたタイミングで isOverrideTextOutをTRUEにするためのフラグ
BOOL isOverrideTextOut = false;    // このフラグがONだと、TextOutは描画をスルーするようにする。
int nTextOutProceedCounter = 0;    // TextOutAの描画を順次上書きするためのカウンタ


extern string prevSerihuMessage;

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

	string message = (char*)(セリフメッセージアドレス); // on_serihu_message
	if (prevSerihuMessage != message) {
		onChangeSerifuMessage(message);
		prevSerihuMessage = message;
	}

	// 武将列伝用の特別なパッチ処理
	patchOfBushouRetsuden(hdc, nXStart, nYStart, lpString, cbString);

	// 武将セリフの特別なパッチ処理
	patchOfBushouMessage(hdc, nXStart, nYStart, lpString, cbString);

	return TRUE;
}
