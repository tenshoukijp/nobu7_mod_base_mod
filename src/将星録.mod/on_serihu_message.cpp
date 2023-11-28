#include <windows.h>
#include <string>

#include "output_debug_stream.h"
#include "bushou_retsuden.h"
#include "hook_textouta_custom.h"
#include "on_serihu_message.h"
#include "bushou_albedo.h"
#include "onigwrap.h"
#include <time.h>

using namespace std;

// フックする関数のプロトタイプを定義
using PFNTEXTOUTA = BOOL(WINAPI*)(HDC, int, int, LPCTSTR, int);
extern PROC pfnOrigTextOutA;


/*
005D9638  8C 95 90 E6 82 A9 82 E7 89 CE 89 8A 82 AA 8F 6F  剣先から火炎が出
005D9648  82 E9 82 C6 0A 82 A2 82 ED 82 EA 82 E9 82 ED 82  ると.いわれるわ・
005D9658  B5 82 CC 8C 95 82 F0 0A 8E F3 82 AF 82 C4 8C A9  ｵの剣を.受けて見
005D9668  82 E6 81 49 81 49 00 9F 82 C2 82 C1 82 C1 81 49  よ！！.氓ﾂっっ！
005D9678  81 49 81 49 00 EA 82 E9 82 ED 81 49 00 82 B5 82  ！！.黷驍增I.し・
005D9688  C4 82 AD 82 BE 82 B3 82 A2 00                    ﾄください.....
*/


extern std::string bufferTextOut;


char pszBufferYasenWeaponMessage1[256] = "命を奪われる時を感謝しながら待ちなさいハァーッ！　　　　　　　　　　　　";
char pszBufferYasenWeaponMessage2[256] = "この私に歯向かうなど身の程を知りなさいハァーッ！　　　　　　　　　　　　";
char pszBufferYasenWeaponMessage3[256] = "□□□□□□□□□□おんどりゃー！□□□□□□□　　　　　　　　　　　　";
char pszBufferYasenWeaponMessage[256] = "";
// char pszBufferYasenWeaponMessage[256] = "バルディッシュの一撃、受けとめてみよ！ハァーッ！　　　　　　　　　　　　";


//                                                     
char pszBufferYasenAttackMessage1[256] = "下等な人間風情が　バルディッシュの錆になりたいのかしら？虫けらは死になさい！　　　　　　　";
char pszBufferYasenAttackMessage2[256] = "人間は脆弱な生き物、下等生物虫のように踏み潰したら少しはキレイになるかしら　　　　　　　　";
char pszBufferYasenAttackMessage[256] = "";

char pszBufferYasenDefendMessage[256] = "そんなに死にたいのかしら？　愚劣で下等な足掻きを　　　　わたくしに見せてごらんなさい　　　　　　";


BOOL isNextSerifuStartOverride = false;  // 次にTextOutAが呼ばれたタイミングで isOverrideTextOutをTRUEにするためのフラグ
BOOL isOverrideSerifuTextOut = false;    // このフラグがONだと、TextOutは描画をスルーするようにする。

BOOL isAlbedoSerifu = false; // アルベドのセリフを表示しなければならないことを検出するための専用フラグ

BOOL isAlbedoYasenWeaponMessage = FALSE;
BOOL isAlbedoYasenAttackMessage = FALSE;
BOOL isAlbedoYasenDefendMessage = FALSE;

string prevSerihuMessage = "";


BOOL patchOfBushouMessage(HDC hdc, int nXStart, int nYStart, LPCTSTR lpString, int cbString) {

	// アルベドが野戦中に会心の一撃を出した場合、アルベドモードにする。
	if (bufferTextOut.ends_with(getArubedoMei() + "剣")) {

		string message = (char*)(セリフメッセージアドレス); // on_serihu_message
		if (message.find("剣先から火炎が出") != string::npos) {
			if (!isAlbedoYasenWeaponMessage) {
				// 次にここに来たらオーバーライドするというフラグ
				isOverrideTextOut = TRUE;
				isAlbedoYasenWeaponMessage = TRUE;

				// 半部の確率で、アルベドのセリフを変更する
				int rnd = rand();
				if (rnd % 3 == 0) {
					strcpy_s(pszBufferYasenWeaponMessage, pszBufferYasenWeaponMessage1);
				}
				else if (rnd % 3 == 1) {
					strcpy_s(pszBufferYasenWeaponMessage, pszBufferYasenWeaponMessage2);
				}
				else {
					strcpy_s(pszBufferYasenWeaponMessage, pszBufferYasenWeaponMessage3);
				}
			}
		}
	}


	// アルベドが野戦をしかけた場合のセリフで、アルベドモードにする。
	if (bufferTextOut.ends_with(getArubedoMei() + "腕")) {

		string message = (char*)(セリフメッセージアドレス); // on_serihu_message
		if (message.find("腕にはいささか自信があります") != string::npos) {

			if (!isAlbedoYasenAttackMessage) {
				// 次にここに来たらオーバーライドするというフラグ
				isOverrideTextOut = TRUE;
				isAlbedoYasenAttackMessage = TRUE;

				// 半部の確率で、アルベドのセリフを変更する
				if (rand() % 2 == 0) {
					strcpy_s(pszBufferYasenAttackMessage, pszBufferYasenAttackMessage1);
				}
				else {
					strcpy_s(pszBufferYasenAttackMessage, pszBufferYasenAttackMessage2);
				}

			}
		}
	}

	// アルベドが野戦中に会心の一撃を出した場合、アルベドモードにする。
	if (bufferTextOut.ends_with(getArubedoMei() + "手")) {

		string message = (char*)(セリフメッセージアドレス); // on_serihu_message
		if (message.find("私をおなごと思わずに") != string::npos) {

			if (!isAlbedoYasenDefendMessage) {
				// 次にここに来たらオーバーライドするというフラグ
				isOverrideTextOut = TRUE;
				isAlbedoYasenDefendMessage = TRUE;
			}
		}
	}


	if (isOverrideTextOut && isAlbedoYasenAttackMessage) {
		// 将星録の描画は1文字ずつなので、1文字ずつ別の文字を描画する形となる。
		((PFNTEXTOUTA)pfnOrigTextOutA)(hdc, nXStart, nYStart, (char*)(pszBufferYasenAttackMessage + nTextOutProceedCounter), 2);
		nTextOutProceedCounter += 2;
	}

	// アルベドモードなら、列伝の描画を順次アルベドのもので上書き
	else if (isOverrideTextOut && isAlbedoYasenWeaponMessage) {
		// 将星録の描画は1文字ずつなので、1文字ずつ別の文字を描画する形となる。
		((PFNTEXTOUTA)pfnOrigTextOutA)(hdc, nXStart, nYStart, (char*)(pszBufferYasenWeaponMessage + nTextOutProceedCounter), 2);
		nTextOutProceedCounter += 2;
	}

	else if (isOverrideTextOut && isAlbedoYasenDefendMessage) {
		// 将星録の描画は1文字ずつなので、1文字ずつ別の文字を描画する形となる。
		((PFNTEXTOUTA)pfnOrigTextOutA)(hdc, nXStart, nYStart, (char*)(pszBufferYasenDefendMessage + nTextOutProceedCounter), 2);
		nTextOutProceedCounter += 2;
	}

	else {

		// 参りますぞ、といっているならば、「ぞ」を「よ」に変更する
		if (bufferTextOut.ends_with(getArubedoMei() + "参りますぞ")) {
			// 次にここに来たらオーバーライドするというフラグ
			isOverrideTextOut = TRUE;
			// 将星録の描画は1文字ずつなので、1文字ずつ別の文字を描画する形となる。
			((PFNTEXTOUTA)pfnOrigTextOutA)(hdc, nXStart, nYStart, "よ", 2);
		}

	}

	return TRUE;
}

// セリフ系や詳細説明系のメッセージが変更になった時に呼ばれる
BOOL onChangeSerifuMessage(std::string message) {
	OutputDebugStream("メッセージが変更になりました:");
	OutputDebugStream(message);
	OutputDebugStream("\r\n");
	return TRUE;
}