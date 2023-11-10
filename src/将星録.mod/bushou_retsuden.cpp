#include <windows.h>
#include <string>

#include "output_debug_stream.h"
#include "onigwrap.h"

using namespace std;

/*
005D9638  0の娘。父の要請を受けて一軍の将となる。父親譲りの智謀と武勇を兼ね備える
005D967F  。.I択してください...........
*/

/*
ナザリック地下大墳墓の守護者統括。頭部からは２本の角、腰からは漆黒の翼を生やした妖艶なサキュバス。
「慈悲深き純白の悪魔」の異名を持つ絶世の美女。
*/

// フックする関数のプロトタイプを定義
using PFNTEXTOUTA = BOOL(WINAPI*)(HDC, int, int, LPCTSTR, int);
extern PROC pfnOrigTextOutA;


BOOL isNextStartOverride = false;  // 次にTextOutAが呼ばれたタイミングで isOverrideTextOutをTRUEにするためのフラグ
BOOL isOverrideTextOut = false;    // このフラグがONだと、TextOutは描画をスルーするようにする。

BOOL isAlbedoRetsuden = false; // アルベドの列伝を表示しなければならないことを検出するための専用フラグ

char AlbedoRetsuden[256] = "宰相。頭部からは２本の角、腰からは漆黒の翼を生やした妖艶なサキュバス。「慈悲深き純白の悪魔」の異名を持つ絶世の美女。　　　　　　　　　　　　　　　　　　　　";
int nTextOutProceedCounter = 0;

extern std::string bufferTextOut;

BOOL pathOfBushouRetsuden(
	HDC hdc,           // デバイスコンテキストのハンドル
	int nXStart,       // 開始位置（基準点）の x 座標
	int nYStart,       // 開始位置（基準点）の y 座標
	LPCTSTR lpString,  // 文字列
	int cbString       // 文字数
) {
	// オーバーライドフラグが立っていたら、オーバーライドする
	if (isNextStartOverride) {
		isOverrideTextOut = TRUE;
	}


	// アルベドの武将列伝の場合、アルベドモードにする。
	if (bufferTextOut.ends_with("武将列伝ΦΧΨ1535～????")) {
		// 次にここに来たらオーバーライドするというフラグ
		isNextStartOverride = TRUE;
		isAlbedoRetsuden = TRUE;
		OutputDebugStream("アルベドの武将列伝\r\n");
	}

	// アルベド列伝ではない。何も表示しないようにしておく
	if (!isAlbedoRetsuden) {

		if (OnigMatch(bufferTextOut, "武将列伝.+～\\?\\?\\?\\?あ$", NULL)) {
		// if (bufferTextOut.ends_with("～????あ")) {
			char checkDummyRetsuden[256] = { 0 };

			// 列伝の中身をコピーしてくる
			strcpy_s(checkDummyRetsuden, 255, (char*)0x5D9638);
			// 「ああああ」や「いいいい」が入っていたら、(アルベド以外は)何も表示しない。
			if (strstr(checkDummyRetsuden, "ああああああああああ")) {
				isOverrideTextOut = TRUE;
			}
			if (strstr(checkDummyRetsuden, "いいいいいいいいいい")) {
				isOverrideTextOut = TRUE;
			}
		}
	}

	// アルベドモードなら、列伝の描画を順次アルベドのもので上書き
	if (isOverrideTextOut && isAlbedoRetsuden) {
		// 将星録の描画は1文字ずつなので、1文字ずつ別の文字を描画する形となる。
		((PFNTEXTOUTA)pfnOrigTextOutA)(hdc, nXStart, nYStart, (char*)(AlbedoRetsuden + nTextOutProceedCounter), 2);
		nTextOutProceedCounter += 2;
	}

	return TRUE;
}