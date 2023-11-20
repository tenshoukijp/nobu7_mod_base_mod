#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <tlhelp32.h>
#include <dbghelp.h>
#include <mmsystem.h>
#include <shellapi.h>
#include <string>

#include "output_debug_stream.h"
#include "game_font.h"
#include "game_process.h"
#include "game_window.h"
#include "onigwrap.h"
#include "on_event.h"
#include "hook_textouta_custom.h"

// ImageDirectoryEntryToData
#pragma comment(lib, "dbghelp.lib")


// ひとつのモジュールに対してAPIフックを行う関数
void ReplaceIATEntryInOneMod(
    PCSTR pszModuleName,
    PROC pfnCurrent,
    PROC pfnNew,
    HMODULE hmodCaller)
{
    ULONG ulSize;
    PIMAGE_IMPORT_DESCRIPTOR pImportDesc;
    pImportDesc = (PIMAGE_IMPORT_DESCRIPTOR)ImageDirectoryEntryToData(
        hmodCaller, TRUE, IMAGE_DIRECTORY_ENTRY_IMPORT, &ulSize);

    if (pImportDesc == NULL)
        return;

    while (pImportDesc->Name) {
        PSTR pszModName = (PSTR)((PBYTE)hmodCaller + pImportDesc->Name);
        if (lstrcmpiA(pszModName, pszModuleName) == 0)
            break;
        pImportDesc++;
    }

    if (pImportDesc->Name == 0)
        return;

    PIMAGE_THUNK_DATA pThunk = (PIMAGE_THUNK_DATA)
        ((PBYTE)hmodCaller + pImportDesc->FirstThunk);

    while (pThunk->u1.Function) {
        PROC* ppfn = (PROC*)&pThunk->u1.Function;
        BOOL fFound = (*ppfn == pfnCurrent);
        if (fFound) {
            DWORD dwDummy;
            VirtualProtect(ppfn, sizeof(ppfn), PAGE_EXECUTE_READWRITE, &dwDummy);
            WriteProcessMemory(
                hCurrentProcess, ppfn, &pfnNew, sizeof(pfnNew), NULL);
            return;
        }
        pThunk++;
    }
    return;
}

// すべてのモジュールに対してAPIフックを行う関数
void ReplaceIATEntryInAllMods(
    PCSTR pszModuleName,
    PROC pfnCurrent,
    PROC pfnNew)
{
    // モジュールリストを取得
    HANDLE hModuleSnap = CreateToolhelp32Snapshot(
        TH32CS_SNAPMODULE, GetCurrentProcessId());
    if (hModuleSnap == INVALID_HANDLE_VALUE)
        return;

    MODULEENTRY32 me;
    me.dwSize = sizeof(me);
    BOOL bModuleResult = Module32First(hModuleSnap, &me);
    // それぞれのモジュールに対してReplaceIATEntryInOneModを実行
    while (bModuleResult) {
        ReplaceIATEntryInOneMod(pszModuleName, pfnCurrent, pfnNew, me.hModule);
        bModuleResult = Module32Next(hModuleSnap, &me);
    }
    CloseHandle(hModuleSnap);
}


//---------------------------WindowProcA

// フックする関数のプロトタイプを定義
using PFNDEFWINDOWPROCA = LRESULT(WINAPI *)(HWND, UINT, WPARAM, LPARAM);

PROC pfnOrigDefWindowProcA = GetProcAddress(GetModuleHandleA("user32.dll"), "DefWindowProcA");

extern LRESULT Hook_DefWindowProcACustom( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );

LRESULT WINAPI Hook_DefWindowProcA(
	HWND hWnd,      // ウィンドウのハンドル
	UINT Msg,       // メッセージの識別子
	WPARAM wParam,  // メッセージの最初のパラメータ
	LPARAM lParam   // メッセージの 2 番目のパラメータ
)
{
	Hook_DefWindowProcACustom(hWnd, Msg, wParam, lParam);

	// スクリーンセイバーの起動を防止する。スクリーンセイバーになりそうな時に、起動しているアプリのいずれかが、1を返せば
	// スクリーンセイバーの起動は防止されるようだ。
	if (Msg == WM_SYSCOMMAND && wParam == SC_SCREENSAVE) {
			// スクリーンセイバーは起動しない。
			return 1;
	}

	//-------------------------------------------- ここから下はオリジナルを呼び出す処理
	// その後、元のものを呼び出す
	LRESULT LPResult = ((PFNDEFWINDOWPROCA)pfnOrigDefWindowProcA)(hWnd, Msg, wParam, lParam);

	return LPResult;
}



//---------------------------TextOutA

// フックする関数のプロトタイプを定義
using PFNTEXTOUTA = BOOL(WINAPI *)(HDC, int, int, LPCTSTR, int);

PROC pfnOrigTextOutA = GetProcAddress(GetModuleHandleA("gdi32.dll"), "TextOutA");

extern BOOL Hook_TextOutACustom(HDC hdc, int nXStart, int nYStart, LPCTSTR lpString, int cbString);

extern BOOL isOverrideTextOut;

BOOL WINAPI Hook_TextOutA(
    HDC hdc,           // デバイスコンテキストのハンドル
    int nXStart,       // 開始位置（基準点）の x 座標
    int nYStart,       // 開始位置（基準点）の y 座標
    LPCTSTR lpString,  // 文字列
    int cbString       // 文字数
) {
    // 先にカスタムの方を実行。
    Hook_TextOutACustom(hdc, nXStart, nYStart, lpString, cbString);
    BOOL nResult = FALSE;

    // Hook_TextOutACustom でオーバーライドフラグが立っていたら、テキストは描画せずにスルーする
    if (isOverrideTextOut) {
    }
    else {
        // 元のものを呼び出す
        nResult = ((PFNTEXTOUTA)pfnOrigTextOutA)(hdc, nXStart, nYStart, lpString, cbString);
    }

    return nResult;
}


//---------------------------CreateFontA
using PFNCREATEFONTA = HFONT (WINAPI *)(int, int, int, int, int, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, LPCSTR);

PROC pfnOrigCreateFontA = GetProcAddress(GetModuleHandleA("gdi32.dll"), "CreateFontA");

extern BOOL Hook_CreateFontACustom(int, int, int, int, int, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, LPCSTR);

HFONT WINAPI Hook_CreateFontA(
    int    cHeight,
    int    cWidth,
    int    cEscapement,
    int    cOrientation,
    int    cWeight,
    DWORD  bItalic,
    DWORD  bUnderline,
    DWORD  bStrikeOut,
    DWORD  iCharSet,
    DWORD  iOutPrecision,
    DWORD  iClipPrecision,
    DWORD  iQuality,
    DWORD  iPitchAndFamily,
    LPCSTR pszFaceName
) {
    char* pOverrideFontName = getNB7FontName();

    // フォントファミリーを指定のもので上書きする
    HFONT hFont = ((PFNCREATEFONTA)pfnOrigCreateFontA)(cHeight, cWidth, cEscapement, cOrientation, cWeight, bItalic, bUnderline, bStrikeOut, iCharSet, iOutPrecision, iClipPrecision, iQuality, iPitchAndFamily, pOverrideFontName);
    return hFont;
}

//---------------------------SetMenu
using PFNSETMENU = BOOL(WINAPI *)(HWND, HMENU);

PROC pfnOrigSetMenu = GetProcAddress(GetModuleHandleA("user32.dll"), "SetMenu");

extern BOOL Hook_SetMenuCustom(HWND hWnd, HMENU hMenu);

BOOL WINAPI Hook_SetMenu(HWND hWnd, HMENU hMenu) {

	// 元のものを呼び出す
	BOOL nResult = ((PFNSETMENU)pfnOrigSetMenu)(hWnd, hMenu);

    // 先にカスタムの方を実行。
    Hook_SetMenuCustom(hWnd, hMenu);

	return nResult;
}


//---------------------------ReleaseDC

using PFNRELEASEDC = int(WINAPI *)(HWND, HDC);

PROC pfnOrigReleaseDC = GetProcAddress(GetModuleHandleA("user32.dll"), "ReleaseDC");

extern int Hook_ReleaseDCCustom(HWND hWnd, HDC hDC);

int WINAPI Hook_ReleaseDC(
    HWND hWnd,  // ウィンドウのハンドル
    HDC hDC     // デバイスコンテキストのハンドル
) {
	// 先にカスタムの方を実行。
	Hook_ReleaseDCCustom(hWnd, hDC);

	// 元のものを呼び出す
	int nResult = ((PFNRELEASEDC)pfnOrigReleaseDC)(hWnd, hDC);

	return nResult;
}

//---------------------------EnableMenuItem

using PFNENABLEMENUITEM = BOOL(WINAPI *)(HMENU, UINT, UINT);

PROC pfnOrigEnableMenuItem = GetProcAddress(GetModuleHandleA("user32.dll"), "EnableMenuItem");

extern BOOL Hook_EnableMenuItemCustom(HMENU hMenu, UINT uIDEnableItem, UINT uEnable);

BOOL WINAPI Hook_EnableMenuItem(
    HMENU hMenu, // メニューのハンドル
    UINT uIDEnableItem, // メニュー項目の識別子または位置
    UINT uEnable // メニュー項目の状態
) {
	// 先にカスタムの方を実行。
	Hook_EnableMenuItemCustom(hMenu, uIDEnableItem, uEnable);

	// 元のものを呼び出す
	BOOL nResult = ((PFNENABLEMENUITEM)pfnOrigEnableMenuItem)(hMenu, uIDEnableItem, uEnable);

	return nResult;
}

//---------------------------BitBlt

using PFNBITBLT = BOOL(WINAPI *)(HDC, int, int, int, int, HDC, int, int, DWORD);

PROC pfnOrigBitBlt = GetProcAddress(GetModuleHandleA("gdi32.dll"), "BitBlt");

extern BOOL Hook_BitBltCustom(HDC hdcDest, int nXDest, int nYDest, int nWidth, int nHeight, HDC hdcSrc, int nXSrc, int nYSrc, DWORD dwRop);

BOOL WINAPI Hook_BitBlt(
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
	// 先にカスタムの方を実行。
    Hook_BitBltCustom(hdcDest, nXDest, nYDest, nWidth, nHeight, hdcSrc, nXSrc, nYSrc, dwRop);

	// 元のものを呼び出す
	BOOL nResult = ((PFNBITBLT)pfnOrigBitBlt)(hdcDest, nXDest, nYDest, nWidth, nHeight, hdcSrc, nXSrc, nYSrc, dwRop);

	return nResult;
}

//---------------------------CreateDIBitmap

using PFNCREATEDIBITMAP = HBITMAP(WINAPI *)(HDC, const BITMAPINFOHEADER *, DWORD, const void *, const BITMAPINFO *, UINT);

PROC pfnOrigCreateDIBitmap = GetProcAddress(GetModuleHandleA("gdi32.dll"), "CreateDIBitmap");

extern HBITMAP Hook_CreateDIBitmapCustom(HDC hdc, const BITMAPINFOHEADER *pbmih, DWORD flInit, const void *pjBits, const BITMAPINFO *pbmi, UINT iUsage);

HBITMAP WINAPI Hook_CreateDIBitmap(
    HDC hdc, // デバイスコンテキストのハンドル
    const BITMAPINFOHEADER* pbmih, // ビットマップ情報のポインタ
    DWORD flInit, // ビットマップの初期化方法
    const void* pjBits, // ビットマップの初期化データ
    const BITMAPINFO* pbmi, // ビットマップのカラーテーブル
    UINT iUsage // ビットマップの使用方法
) {
	// 先にカスタムの方を実行。
	Hook_CreateDIBitmapCustom(hdc, pbmih, flInit, pjBits, pbmi, iUsage);

	// 元のものを呼び出す
	HBITMAP nResult = ((PFNCREATEDIBITMAP)pfnOrigCreateDIBitmap)(hdc, pbmih, flInit, pjBits, pbmi, iUsage);

	return nResult;
}


//---------------------------CreateCompatibleDC

using PFNCREATECOMPATIBLEDC = HDC(WINAPI *)(HDC);

PROC pfnOrigCreateCompatibleDC = GetProcAddress(GetModuleHandleA("gdi32.dll"), "CreateCompatibleDC");

extern HDC Hook_CreateCompatibleDCCustom(HDC hdc);

HDC WINAPI Hook_CreateCompatibleDC(
    HDC hdc // デバイスコンテキストのハンドル
) {
	// 先にカスタムの方を実行。
	Hook_CreateCompatibleDCCustom(hdc);

	// 元のものを呼び出す
	HDC nResult = ((PFNCREATECOMPATIBLEDC)pfnOrigCreateCompatibleDC)(hdc);

	return nResult;
}

//---------------------------GetDIBits

using PFNGETDIBITS = int(WINAPI *)(HDC, HBITMAP, UINT, UINT, LPVOID, LPBITMAPINFO, UINT);

PROC pfnOrigGetDIBits = GetProcAddress(GetModuleHandleA("gdi32.dll"), "GetDIBits");

extern int Hook_GetDIBitsCustom(HDC hdc, HBITMAP hbm, UINT start, UINT cLines, LPVOID lpvBits, LPBITMAPINFO lpbmi, UINT usage);

int WINAPI Hook_GetDIBits(
    HDC hdc, // デバイスコンテキストのハンドル
    HBITMAP hbm, // ビットマップのハンドル
    UINT start, // スキャンラインの最初のインデックス
    UINT cLines, // スキャンラインの数
    LPVOID lpvBits, // ビットマップデータのポインタ
    LPBITMAPINFO lpbmi, // ビットマップ情報のポインタ
    UINT usage // ビットマップの使用方法
) {
	// 先にカスタムの方を実行。
	Hook_GetDIBitsCustom(hdc, hbm, start, cLines, lpvBits, lpbmi, usage);

	// 元のもの
    int nResult = ((PFNGETDIBITS)pfnOrigGetDIBits)(hdc, hbm, start, cLines, lpvBits, lpbmi, usage);

    return nResult;
}


//---------------------------IsDebuggerPresent

using PFNISDEBUGGERPRESENT = BOOL(WINAPI *)();

PROC pfnOrigIsDebuggerPresent = GetProcAddress(GetModuleHandleA("kernel32.dll"), "IsDebuggerPresent");

extern BOOL Hook_IsDebuggerPresentCustom();

BOOL WINAPI Hook_IsDebuggerPresent() {
	// 先にカスタムの方を実行。
	Hook_IsDebuggerPresentCustom();

	// 元のもの
	BOOL nResult = ((PFNISDEBUGGERPRESENT)pfnOrigIsDebuggerPresent)();

	return FALSE;
}




/*----------------------------------------------------------------*
 HOOK系処理
 *----------------------------------------------------------------*/
bool isHookDefWindowProcA = false;
bool isHookTextOutA = false;
bool isHookCreateFontA = false;
bool isHookSetMenu = false;
bool isHookReleaseDC = false;
bool isHookEnableMenuItem = false;
bool isHookBitBlt = false;
bool isHookCreateDIBitmap = false;
bool isHookCreateCompatibleDC = false;
bool isHookGetDIBits = false;
bool isHookIsDebuggerPresent = false;
bool isHookUnknown1 = false;

void hookFunctionsReplace() {

    PROC pfnOrig;
    if (!isHookDefWindowProcA) {
        isHookDefWindowProcA = true;
        pfnOrig = ::GetProcAddress(GetModuleHandleA("user32.dll"), "DefWindowProcA");
        ReplaceIATEntryInAllMods("user32.dll", pfnOrig, (PROC)Hook_DefWindowProcA);
    }
    if (!isHookTextOutA) {
        isHookTextOutA = true;
        pfnOrig = ::GetProcAddress(GetModuleHandleA("gdi32.dll"), "TextOutA");
        ReplaceIATEntryInAllMods("gdi32.dll", pfnOrig, (PROC)Hook_TextOutA);
    }
    if (!isHookCreateFontA) {
		isHookCreateFontA = true;
		pfnOrig = ::GetProcAddress(GetModuleHandleA("gdi32.dll"), "CreateFontA");
		ReplaceIATEntryInAllMods("gdi32.dll", pfnOrig, (PROC)Hook_CreateFontA);
    }
    if (!isHookSetMenu) {
        isHookSetMenu = true;
        pfnOrig = ::GetProcAddress(GetModuleHandleA("user32.dll"), "SetMenu");
        ReplaceIATEntryInAllMods("user32.dll", pfnOrig, (PROC)Hook_SetMenu);
    }
    if (!isHookReleaseDC) {
		isHookReleaseDC = true;
		pfnOrig = ::GetProcAddress(GetModuleHandleA("user32.dll"), "ReleaseDC");
		ReplaceIATEntryInAllMods("user32.dll", pfnOrig, (PROC)Hook_ReleaseDC);
	}
    if (!isHookEnableMenuItem) {
        isHookEnableMenuItem = true;
        pfnOrig = ::GetProcAddress(GetModuleHandleA("user32.dll"), "EnableMenuItem");
        ReplaceIATEntryInAllMods("user32.dll", pfnOrig, (PROC)Hook_EnableMenuItem);
    }
    if (!isHookBitBlt) {
		isHookBitBlt = true;
		pfnOrig = ::GetProcAddress(GetModuleHandleA("gdi32.dll"), "BitBlt");
		ReplaceIATEntryInAllMods("gdi32.dll", pfnOrig, (PROC)Hook_BitBlt);
	}
    if (!isHookCreateDIBitmap) {
		isHookCreateDIBitmap = true;
		pfnOrig = ::GetProcAddress(GetModuleHandleA("gdi32.dll"), "CreateDIBitmap");
		ReplaceIATEntryInAllMods("gdi32.dll", pfnOrig, (PROC)Hook_CreateDIBitmap);
	}
    if (!isHookCreateCompatibleDC) {
		isHookCreateCompatibleDC = true;
		pfnOrig = ::GetProcAddress(GetModuleHandleA("gdi32.dll"), "CreateCompatibleDC");
		ReplaceIATEntryInAllMods("gdi32.dll", pfnOrig, (PROC)Hook_CreateCompatibleDC);
	}
    if (!isHookGetDIBits) {
		isHookGetDIBits = true;
		pfnOrig = ::GetProcAddress(GetModuleHandleA("gdi32.dll"), "GetDIBits");
		ReplaceIATEntryInAllMods("gdi32.dll", pfnOrig, (PROC)Hook_GetDIBits);
	}
    if (!isHookIsDebuggerPresent) {
		isHookIsDebuggerPresent = true;
		pfnOrig = ::GetProcAddress(GetModuleHandleA("kernel32.dll"), "IsDebuggerPresent");
		ReplaceIATEntryInAllMods("kernel32.dll", pfnOrig, (PROC)Hook_IsDebuggerPresent);
	}
}