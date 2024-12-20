#include <windows.h>
#include <string>
#include <tlhelp32.h>
#include <dbghelp.h>
#include <string>
#include <algorithm>
#include <cctype>
#include <map>

#include "hook_setfilepointer_custom_winframe.h"
#include "output_debug_stream.h"
#include "game_font.h"
#include "game_process.h"
#include "file_attribute.h"

#include "usr_custom_mod.h"
#include "mng_文字列変換.h"

// ImageDirectoryEntryToData
#pragma comment(lib, "dbghelp.lib")

using namespace std;

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

    // 元のものを呼び出す
    BOOL nResult = ((PFNTEXTOUTA)pfnOrigTextOutA)(hdc, nXStart, nYStart, lpString, cbString);

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
    const char* pOverrideFontName = getNB7FontName();

    HFONT hFont = NULL;

    // フォントの指定があるならば
    if (pOverrideFontName) {
        // フォントファミリーを指定のもので上書きする
        hFont = ((PFNCREATEFONTA)pfnOrigCreateFontA)(cHeight, cWidth, cEscapement, cOrientation, cWeight, bItalic, bUnderline, bStrikeOut, iCharSet, iOutPrecision, iClipPrecision, iQuality, iPitchAndFamily, pOverrideFontName);
        if (hFont == NULL) {
            OutputDebugString("フォントがインストールされていない\n");
        	// 上書きできなかった場合は、元のパラメータのままで委譲
			hFont = ((PFNCREATEFONTA)pfnOrigCreateFontA)(cHeight, cWidth, cEscapement, cOrientation, cWeight, bItalic, bUnderline, bStrikeOut, iCharSet, iOutPrecision, iClipPrecision, iQuality, iPitchAndFamily, pszFaceName);
		
        }

    }

    // そうでなければ、元のパラメータのままで委譲
	else {
		hFont = ((PFNCREATEFONTA)pfnOrigCreateFontA)(cHeight, cWidth, cEscapement, cOrientation, cWeight, bItalic, bUnderline, bStrikeOut, iCharSet, iOutPrecision, iClipPrecision, iQuality, iPitchAndFamily, pszFaceName);
	}

    return hFont;
}

//---------------------------LoadMenuA
int lastLoadMenuID = 0;
using PFNLOADMENUA = HMENU(WINAPI *)(HINSTANCE, LPCSTR);

PROC pfnOrigLoadMenuA = GetProcAddress(GetModuleHandleA("user32.dll"), "LoadMenuA");
extern HMODULE h将星録ModDLL;
// extern HMENU Hook_LoadMenuACustom(HINSTANCE hInstance, LPCSTR lpMenuName);
HMENU WINAPI Hook_LoadMenuA(
    HINSTANCE hInstance, // インスタンスのハンドル
    LPCSTR lpMenuName // メニュー名
) {
	// 先にカスタムの方を実行。
	// Hook_LoadMenuACustom(hInstance, lpMenuName);

    // OutputDebugStream("Hook_LoadMenuA\n");
    lastLoadMenuID = (int)lpMenuName;
	// 元のものを呼び出す
	// HMENU nResult = ((PFNLOADMENUA)pfnOrigLoadMenuA)(hInstance, lpMenuName);
    HANDLE hModule = GetModuleHandle(NULL); //このdll自信のハンドル
    OutputDebugStream("モジュール%x", h将星録ModDLL);
    HMENU nResult = ((PFNLOADMENUA)pfnOrigLoadMenuA)((HINSTANCE)h将星録ModDLL, lpMenuName);

	return nResult;
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

//---------------------------CreateFileA

using PFNCREATEFILEA = HANDLE(WINAPI*)(LPCSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE);

PROC pfnOrigCreateFileA = GetProcAddress(GetModuleHandleA("kernel32.dll"), "CreateFileA");
int nTargetKaoID = -1;
int nTargetKahouGazouID = -1;
int nTargetKamonID = -1;

static map<HANDLE, string> handleMap;

// extern HANDLE Hook_CreateFileACustom(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);
HANDLE hFileKAODATA = NULL;
HANDLE hFileITEMDATA = NULL;
HANDLE hFileWINFRAME = NULL;
HANDLE hFileKAMON = NULL;
HANDLE WINAPI Hook_CreateFileA(
    LPCSTR lpFileName, // ファイル名
    DWORD dwDesiredAccess, // アクセス方法
    DWORD dwShareMode, // 共有方法
    LPSECURITY_ATTRIBUTES lpSecurityAttributes, // セキュリティ記述子
    DWORD dwCreationDisposition, // 作成方法
    DWORD dwFlagsAndAttributes, // ファイル属性
    HANDLE hTemplateFile // テンプレートファイルのハンドル
) {

    HANDLE nResult;

    // 将星録.mod.dllの層では、「OVERRIDE」にあるファイルを対象とする。
    string overrideFileName = string("OVERRIDE\\") + lpFileName;

    try {
        // C#のdllでユーザーがカスタムしたファイルを指定するかもしれない。
        System::Collections::Generic::Dictionary<System::String^, System::Object^>^ dic = gcnew System::Collections::Generic::Dictionary<System::String^, System::Object^>(5);
        dic->Add("ファイル名", gcnew System::String(lpFileName));
        System::Collections::Generic::Dictionary<System::String^, System::Object^>^ ret = InvokeUserMethod("onファイル要求時", dic);
        if (ret != nullptr) {
            if (ret->ContainsKey("ファイル名")) {
                System::String^ mng_filename = (System::String^)ret["ファイル名"];
                if (mng_filename != nullptr) {
					overrideFileName = to_native_string(mng_filename);
				}
            }
        }
    }
    catch (System::Exception^ ) {
        OutputDebugStream("onファイル要求時に例外が発生しました。\n");
    }

    if (isFileExists(overrideFileName)) {
        // 元のもの
        nResult = ((PFNCREATEFILEA)pfnOrigCreateFileA)(overrideFileName.c_str(), dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
    }
    else {
        // 元のもの
        nResult = ((PFNCREATEFILEA)pfnOrigCreateFileA)(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
    }
    // 先にカスタムの方を実行。
    // Hook_CreateFileACustom(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
    nTargetKaoID = -1;
    nTargetKahouGazouID = -1;
    nTargetKamonID = -1;

    string filename = string(lpFileName);
    std::transform(filename.begin(), filename.end(), filename.begin(), [](unsigned char c) { return std::toupper(c); });
    if (filename == "KAODATA.NB7") {
        OutputDebugStream("CreateFileA:" + std::string(lpFileName) + "\n");
        hFileKAODATA = nResult;
    }
    else if (filename == "ITEMDATA.NB7") {
        OutputDebugStream("CreateFileA:" + std::string(lpFileName) + "\n");
        hFileITEMDATA = nResult;
    }
    else if (filename == "KAMON.NB7") {
		OutputDebugStream("CreateFileA:" + std::string(lpFileName) + "\n");
        hFileKAMON = nResult;
	}
    /*
    else if (filename == "WINFRAME.NB7") {
        OutputDebugStream("CreateFileA:" + std::string(lpFileName) + "\n");
        hFileWINFRAME = nResult;

    }
    */

    // handleMap[nResult] = lpFileName;

    return nResult;
}

//---------------------------SetFilePointer

using PFNSETFILEPOINTER = DWORD(WINAPI *)(HANDLE, LONG, PLONG, DWORD);
BOOL IsNextWinFrameHeader = FALSE;
extern BOOL WinFrameHeaderCopied;
PROC pfnOrigSetFilePointer = GetProcAddress(GetModuleHandleA("kernel32.dll"), "SetFilePointer");
// extern DWORD Hook_SetFilePointerCustom(HANDLE hFile, LONG lDistanceToMove, PLONG lpDistanceToMoveHigh, DWORD dwMoveMethod);
DWORD WINAPI Hook_SetFilePointer(
	HANDLE hFile, // ファイルのハンドル
	LONG lDistanceToMove, // 移動量
	PLONG lpDistanceToMoveHigh, // 移動量の上位 32 ビット
	DWORD dwMoveMethod // 移動方法
) {
	// 先にカスタムの方を実行。
	// Hook_SetFilePointerCustom(hFile, lDistanceToMove, lpDistanceToMoveHigh, dwMoveMethod);

    nTargetKaoID = -1;
    nTargetKahouGazouID = -1;
    nTargetKamonID = -1;
    IsNextWinFrameHeader = FALSE;
	// 元のもの
	DWORD nResult = ((PFNSETFILEPOINTER)pfnOrigSetFilePointer)(hFile, lDistanceToMove, lpDistanceToMoveHigh, dwMoveMethod);
    if (hFileKAODATA == hFile) {
        const int pic_data_size = (64 * 80) * 769; // 769個の顔画像が入っている
        const int file_org_size = 3949588; // KAODATA.NB7のファイルサイズ
        const int header_size = file_org_size - pic_data_size;
        nTargetKaoID = (lDistanceToMove - header_size) / (64 * 80);
        OutputDebugStream("顔SetFilePointer:" + std::to_string(lDistanceToMove) + "\n");
    }
    else if (hFileITEMDATA == hFile) {
        const int pic_data_size = (64 * 64) * 27; // 27個の家宝画像が入っている
        const int file_org_size = 111028; // ITEMDATA.NB7のファイルサイズ
        const int header_size = file_org_size - pic_data_size;
        nTargetKahouGazouID = (lDistanceToMove - header_size) / (64 * 64);
        OutputDebugStream("家宝SetFilePointer:" + std::to_string(lDistanceToMove) + "\n");
    }
    else if (hFileKAMON == hFile) {
        const int pic_data_size = (24 * 24) * 147; // 147個の家宝画像が入っている
        const int file_org_size = 87028; // KAMON.NB7のファイルサイズ
        const int header_size = file_org_size - pic_data_size;
        nTargetKamonID = (lDistanceToMove - header_size) / (24 * 24);
        OutputDebugStream("家紋SetFilePointer:" + std::to_string(lDistanceToMove) + "\n");
    }

    /*
    else if (hFileWINFRAME == hFile) {
        OutputDebugStream("フレームSetFilePointer:" + std::to_string(lDistanceToMove) + "\n");
        if (lDistanceToMove == 0) { // 最初の４バイトはヘッダーがいくつのデータで構成されるかの個数が入っている。
            IsNextWinFrameHeader = FALSE;
        }
        else if (lDistanceToMove == 4) { // 次からヘッダーが入っている。
            IsNextWinFrameHeader = TRUE;
        }
        else if (WinFrameHeaderCopied) {
            int 差し引きAddress = lDistanceToMove - WINFRAME_NB7_ALL_HEADER_SIZE;
            for (int i = 0; i < WINFRAME_NB7_CHUNK_COUNT; i++) {
                if (差し引きAddress == winframe_nb7_header->chunk[i].start_address) {
					OutputDebugStream("フレーム番号:" + std::to_string(i) + "\n");
				}
			}
        }
    }
    */
    /*
    if (handleMap.contains(hFile)) {
        OutputDebugStream(handleMap[hFile] + " SetFilePointer:" + std::to_string(lDistanceToMove) + "\n");
    }
    */

	return nResult;
}


//---------------------------ReadFile

using PFNREADFILE = BOOL(WINAPI *)(HANDLE, LPVOID, DWORD, LPDWORD, LPOVERLAPPED);

PROC pfnOrigReadFile = GetProcAddress(GetModuleHandleA("kernel32.dll"), "ReadFile");

extern void hook_setfilepointer_custom_winframe(LPVOID lpBuffer, DWORD nNumberOfBytesToRead);
extern BOOL Hook_ReadFileCustom_BushouKao(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped);
extern BOOL Hook_ReadFileCustom_KahouPic(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped);
extern BOOL Hook_ReadFileCustom_KamonPic(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped);
BOOL WINAPI Hook_ReadFile(
	HANDLE hFile, // ファイルのハンドル
	LPVOID lpBuffer, // データの格納先
	DWORD nNumberOfBytesToRead, // 読み込むバイト数
	LPDWORD lpNumberOfBytesRead, // 実際に読み込んだバイト数
	LPOVERLAPPED lpOverlapped // オーバーラップ構造体のポインタ
) {

	// 元のもの
	BOOL nResult = ((PFNREADFILE)pfnOrigReadFile)(hFile, lpBuffer, nNumberOfBytesToRead, lpNumberOfBytesRead, lpOverlapped);

    if (hFileKAODATA == hFile) {
        OutputDebugStream("読み込むバイト数%d\n", nNumberOfBytesToRead);
        Hook_ReadFileCustom_BushouKao(hFile, lpBuffer, nNumberOfBytesToRead, lpNumberOfBytesRead, lpOverlapped);
    }
    else if (hFileITEMDATA == hFile) {
        OutputDebugStream("読み込むバイト数%d\n", nNumberOfBytesToRead);
        Hook_ReadFileCustom_KahouPic(hFile, lpBuffer, nNumberOfBytesToRead, lpNumberOfBytesRead, lpOverlapped);
    }
    else if (hFileITEMDATA == hFile) {
        OutputDebugStream("読み込むバイト数%d\n", nNumberOfBytesToRead);
        Hook_ReadFileCustom_KahouPic(hFile, lpBuffer, nNumberOfBytesToRead, lpNumberOfBytesRead, lpOverlapped);
    }
    else if (hFileKAMON == hFile) {
        OutputDebugStream("読み込むバイト数%d\n", nNumberOfBytesToRead);
        Hook_ReadFileCustom_KamonPic(hFile, lpBuffer, nNumberOfBytesToRead, lpNumberOfBytesRead, lpOverlapped);
    }
    /*
    else if (hFileWINFRAME == hFile) {
        if (IsNextWinFrameHeader) {
            // WINFRAME.NB7のヘッダー情報を読み取り。これは画像ごとに画素サイズが異なるため、単純に割り算などで求めることができないため。
            if (nNumberOfBytesToRead == sizeof(WINFRAME_NB7_HEADER)) {
                hook_setfilepointer_custom_winframe(lpBuffer, nNumberOfBytesToRead);
            }
            IsNextWinFrameHeader = FALSE;
        }
        OutputDebugStream("フレーム読み込むバイト数%d:\n", nNumberOfBytesToRead);
    }
    */
    nTargetKaoID = -1;
    nTargetKahouGazouID = -1;
    nTargetKamonID = -1;
  
    return nResult;
}

//---------------------------CloseHandle

using PFNCLOSEHANDLE = BOOL(WINAPI *)(HANDLE);

PROC pfnOrigCloseHandle = GetProcAddress(GetModuleHandleA("kernel32.dll"), "CloseHandle");

BOOL WINAPI Hook_CloseHandle(
    HANDLE hObject // オブジェクトのハンドル
) {

    if (hFileKAODATA == hObject) {
        // OutputDebugStream("CloseHandle:KAODATA\n");
        hFileKAODATA = NULL;
    }
    else if (hFileITEMDATA == hObject) {
        // OutputDebugStream("CloseHandle:ITEMDATA\n");
        hFileITEMDATA = NULL;
    }
    else if (hFileKAMON == hObject) {
		// OutputDebugStream("CloseHandle:KAMON\n");
		hFileKAMON = NULL;
	}
    /*
    else if (hFileWINFRAME == hObject) {
        hFileWINFRAME = NULL;
    }
    */
    else {
        // OutputDebugStream("CloseHandle:その他\n");
    }

	// 元のもの
	BOOL nResult = ((PFNCLOSEHANDLE)pfnOrigCloseHandle)(hObject);

	return nResult;
}


//---------------------------SelectObject

using PFNSELECTOBJECT = HGDIOBJ(WINAPI *)(HDC, HGDIOBJ);

PROC pfnOrigSelectObject = GetProcAddress(GetModuleHandleA("gdi32.dll"), "SelectObject");

// extern HGDIOBJ Hook_SelectObjectCustom(HDC hdc, HGDIOBJ h);

HGDIOBJ WINAPI Hook_SelectObject(
    HDC hdc, // デバイスコンテキストのハンドル
    HGDIOBJ h // オブジェクトのハンドル
) {
    // 元のもの
	HGDIOBJ nResult = ((PFNSELECTOBJECT)pfnOrigSelectObject)(hdc, h);

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

//---------------------------MessageBoxA

using PFNMESSAGEBOXA = int(WINAPI *)(HWND, LPCSTR, LPCSTR, UINT);

PROC pfnOrigMessageBoxA = GetProcAddress(GetModuleHandleA("user32.dll"), "MessageBoxA");

// extern int Hook_MessageBoxACustom(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType);

int WINAPI Hook_MessageBoxA(
	HWND hWnd, // ウィンドウのハンドル
	LPCSTR lpText, // メッセージ ボックスに表示するテキスト
	LPCSTR lpCaption, // メッセージ ボックスのタイトル バーに表示するテキスト
	UINT uType // メッセージ ボックスのスタイル
) {
	// 先にカスタムの方を実行。
	// Hook_MessageBoxACustom(hWnd, lpText, lpCaption, uType);


    /*
    004FDAE3   68 94965200      PUSH Nobunaga.00529694                   ; ASCII "信長の野望･将星録 パワーアップキット の終了"
    004FDAE8   68 60965200      PUSH Nobunaga.00529660                   ; ASCII "信長の野望･将星録 パワーアップキット を終了します。"
    */
    // 終了ダイアログである。
    if ((int)lpCaption == 0x529694 && (int)lpText == 0x529660) {
		return IDOK;
	}

	// 元のもの
	int nResult = ((PFNMESSAGEBOXA)pfnOrigMessageBoxA)(hWnd, lpText, lpCaption, uType);

	return nResult;
}

/*----------------------------------------------------------------*
 HOOK系処理
 *----------------------------------------------------------------*/
bool isHookDefWindowProcA = false;
bool isHookTextOutA = false;
bool isHookCreateFontA = false;
bool isHookSetMenu = false;
bool isHookLoadMenuA = false;
bool isHookReleaseDC = false;
bool isHookEnableMenuItem = false;
bool isHookBitBlt = false;
bool isHookCreateDIBitmap = false;
bool isHookCreateCompatibleDC = false;
bool isHookGetDIBits = false;
bool isHookIsDebuggerPresent = false;
bool isHookCreateFileA = false;
bool isHookSetFilePointer = false;
bool isHookReadFile = false;
bool isHookSelectObject = false;
bool isHookCloseHandle = false;
bool isHookMessageBoxA = false;

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
    if (!isHookLoadMenuA) {
        isHookLoadMenuA = true;
        pfnOrig = ::GetProcAddress(GetModuleHandleA("user32.dll"), "LoadMenuA");
        ReplaceIATEntryInAllMods("user32.dll", pfnOrig, (PROC)Hook_LoadMenuA);
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

    /*
    * 不要
    if (!isHookEnableMenuItem) {
        isHookEnableMenuItem = true;
        pfnOrig = ::GetProcAddress(GetModuleHandleA("user32.dll"), "EnableMenuItem");
        ReplaceIATEntryInAllMods("user32.dll", pfnOrig, (PROC)Hook_EnableMenuItem);
    }
    */

    /*
    * 不要
    if (!isHookBitBlt) {
		isHookBitBlt = true;
		pfnOrig = ::GetProcAddress(GetModuleHandleA("gdi32.dll"), "BitBlt");
		ReplaceIATEntryInAllMods("gdi32.dll", pfnOrig, (PROC)Hook_BitBlt);
	}
    */

    /*
    * 不要
    if (!isHookCreateDIBitmap) {
		isHookCreateDIBitmap = true;
		pfnOrig = ::GetProcAddress(GetModuleHandleA("gdi32.dll"), "CreateDIBitmap");
		ReplaceIATEntryInAllMods("gdi32.dll", pfnOrig, (PROC)Hook_CreateDIBitmap);
	}
    */
    /*
    * 不要
    if (!isHookCreateCompatibleDC) {
		isHookCreateCompatibleDC = true;
		pfnOrig = ::GetProcAddress(GetModuleHandleA("gdi32.dll"), "CreateCompatibleDC");
		ReplaceIATEntryInAllMods("gdi32.dll", pfnOrig, (PROC)Hook_CreateCompatibleDC);
	}
    */

    /*
    * 不要
    if (!isHookGetDIBits) {
		isHookGetDIBits = true;
		pfnOrig = ::GetProcAddress(GetModuleHandleA("gdi32.dll"), "GetDIBits");
		ReplaceIATEntryInAllMods("gdi32.dll", pfnOrig, (PROC)Hook_GetDIBits);
	}
    */

    if (!isHookCreateFileA) {
		isHookCreateFileA = true;
		pfnOrig = ::GetProcAddress(GetModuleHandleA("kernel32.dll"), "CreateFileA");
		ReplaceIATEntryInAllMods("kernel32.dll", pfnOrig, (PROC)Hook_CreateFileA);
	}
    if (!isHookSetFilePointer) {
        isHookSetFilePointer = true;
        pfnOrig = ::GetProcAddress(GetModuleHandleA("kernel32.dll"), "SetFilePointer");
        ReplaceIATEntryInAllMods("kernel32.dll", pfnOrig, (PROC)Hook_SetFilePointer);
    }
    if (!isHookReadFile) {
        isHookReadFile = true;
        pfnOrig = ::GetProcAddress(GetModuleHandleA("kernel32.dll"), "ReadFile");
        ReplaceIATEntryInAllMods("kernel32.dll", pfnOrig, (PROC)Hook_ReadFile);
    }
    if (!isHookCloseHandle) {
		isHookCloseHandle = true;
		pfnOrig = ::GetProcAddress(GetModuleHandleA("kernel32.dll"), "CloseHandle");
		ReplaceIATEntryInAllMods("kernel32.dll", pfnOrig, (PROC)Hook_CloseHandle);
	}


    /*
	* 不要
    if (!isHookSelectObject) {
		isHookSelectObject = true;
		pfnOrig = ::GetProcAddress(GetModuleHandleA("gdi32.dll"), "SelectObject");
		ReplaceIATEntryInAllMods("gdi32.dll", pfnOrig, (PROC)Hook_SelectObject);
	}
    */

    if (!isHookIsDebuggerPresent) {
		isHookIsDebuggerPresent = true;
		pfnOrig = ::GetProcAddress(GetModuleHandleA("kernel32.dll"), "IsDebuggerPresent");
		ReplaceIATEntryInAllMods("kernel32.dll", pfnOrig, (PROC)Hook_IsDebuggerPresent);
	}

    if (!isHookMessageBoxA) {
		isHookMessageBoxA = true;
		pfnOrig = ::GetProcAddress(GetModuleHandleA("user32.dll"), "MessageBoxA");
		ReplaceIATEntryInAllMods("user32.dll", pfnOrig, (PROC)Hook_MessageBoxA);
	}
}