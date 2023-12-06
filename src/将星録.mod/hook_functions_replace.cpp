#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <tlhelp32.h>
#include <dbghelp.h>
#include <mmsystem.h>
#include <shellapi.h>
#include <string>
#include <algorithm>
#include <cctype>

#include "output_debug_stream.h"
#include "game_font.h"
#include "game_process.h"
#include "game_window.h"
#include "onigwrap.h"
#include "on_event.h"
#include "hook_textouta_custom.h"
#include "file_attribute.h"

// ImageDirectoryEntryToData
#pragma comment(lib, "dbghelp.lib")


// �ЂƂ̃��W���[���ɑ΂���API�t�b�N���s���֐�
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

// ���ׂẴ��W���[���ɑ΂���API�t�b�N���s���֐�
void ReplaceIATEntryInAllMods(
    PCSTR pszModuleName,
    PROC pfnCurrent,
    PROC pfnNew)
{
    // ���W���[�����X�g���擾
    HANDLE hModuleSnap = CreateToolhelp32Snapshot(
        TH32CS_SNAPMODULE, GetCurrentProcessId());
    if (hModuleSnap == INVALID_HANDLE_VALUE)
        return;

    MODULEENTRY32 me;
    me.dwSize = sizeof(me);
    BOOL bModuleResult = Module32First(hModuleSnap, &me);
    // ���ꂼ��̃��W���[���ɑ΂���ReplaceIATEntryInOneMod�����s
    while (bModuleResult) {
        ReplaceIATEntryInOneMod(pszModuleName, pfnCurrent, pfnNew, me.hModule);
        bModuleResult = Module32Next(hModuleSnap, &me);
    }
    CloseHandle(hModuleSnap);
}


//---------------------------WindowProcA

// �t�b�N����֐��̃v���g�^�C�v���`
using PFNDEFWINDOWPROCA = LRESULT(WINAPI *)(HWND, UINT, WPARAM, LPARAM);

PROC pfnOrigDefWindowProcA = GetProcAddress(GetModuleHandleA("user32.dll"), "DefWindowProcA");

extern LRESULT Hook_DefWindowProcACustom( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );

LRESULT WINAPI Hook_DefWindowProcA(
	HWND hWnd,      // �E�B���h�E�̃n���h��
	UINT Msg,       // ���b�Z�[�W�̎��ʎq
	WPARAM wParam,  // ���b�Z�[�W�̍ŏ��̃p�����[�^
	LPARAM lParam   // ���b�Z�[�W�� 2 �Ԗڂ̃p�����[�^
)
{
	Hook_DefWindowProcACustom(hWnd, Msg, wParam, lParam);

	// �X�N���[���Z�C�o�[�̋N����h�~����B�X�N���[���Z�C�o�[�ɂȂ肻���Ȏ��ɁA�N�����Ă���A�v���̂����ꂩ���A1��Ԃ���
	// �X�N���[���Z�C�o�[�̋N���͖h�~�����悤���B
	if (Msg == WM_SYSCOMMAND && wParam == SC_SCREENSAVE) {
			// �X�N���[���Z�C�o�[�͋N�����Ȃ��B
			return 1;
	}

	//-------------------------------------------- �������牺�̓I���W�i�����Ăяo������
	// ���̌�A���̂��̂��Ăяo��
	LRESULT LPResult = ((PFNDEFWINDOWPROCA)pfnOrigDefWindowProcA)(hWnd, Msg, wParam, lParam);

	return LPResult;
}



//---------------------------TextOutA

// �t�b�N����֐��̃v���g�^�C�v���`
using PFNTEXTOUTA = BOOL(WINAPI *)(HDC, int, int, LPCTSTR, int);

PROC pfnOrigTextOutA = GetProcAddress(GetModuleHandleA("gdi32.dll"), "TextOutA");

extern BOOL Hook_TextOutACustom(HDC hdc, int nXStart, int nYStart, LPCTSTR lpString, int cbString);

extern BOOL isOverrideTextOut;

BOOL WINAPI Hook_TextOutA(
    HDC hdc,           // �f�o�C�X�R���e�L�X�g�̃n���h��
    int nXStart,       // �J�n�ʒu�i��_�j�� x ���W
    int nYStart,       // �J�n�ʒu�i��_�j�� y ���W
    LPCTSTR lpString,  // ������
    int cbString       // ������
) {
    // ��ɃJ�X�^���̕������s�B
    Hook_TextOutACustom(hdc, nXStart, nYStart, lpString, cbString);

    // ���̂��̂��Ăяo��
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

    // �t�H���g�̎w�肪����Ȃ��
    if (pOverrideFontName) {
        // �t�H���g�t�@�~���[���w��̂��̂ŏ㏑������
        hFont = ((PFNCREATEFONTA)pfnOrigCreateFontA)(cHeight, cWidth, cEscapement, cOrientation, cWeight, bItalic, bUnderline, bStrikeOut, iCharSet, iOutPrecision, iClipPrecision, iQuality, iPitchAndFamily, pOverrideFontName);
        if (hFont == NULL) {
            OutputDebugString("�t�H���g���C���X�g�[������Ă��Ȃ�\n");
        	// �㏑���ł��Ȃ������ꍇ�́A���̃p�����[�^�̂܂܂ňϏ�
			hFont = ((PFNCREATEFONTA)pfnOrigCreateFontA)(cHeight, cWidth, cEscapement, cOrientation, cWeight, bItalic, bUnderline, bStrikeOut, iCharSet, iOutPrecision, iClipPrecision, iQuality, iPitchAndFamily, pszFaceName);
		
        }

    }

    // �����łȂ���΁A���̃p�����[�^�̂܂܂ňϏ�
	else {
		hFont = ((PFNCREATEFONTA)pfnOrigCreateFontA)(cHeight, cWidth, cEscapement, cOrientation, cWeight, bItalic, bUnderline, bStrikeOut, iCharSet, iOutPrecision, iClipPrecision, iQuality, iPitchAndFamily, pszFaceName);
	}

    return hFont;
}

//---------------------------SetMenu
using PFNSETMENU = BOOL(WINAPI *)(HWND, HMENU);

PROC pfnOrigSetMenu = GetProcAddress(GetModuleHandleA("user32.dll"), "SetMenu");

extern BOOL Hook_SetMenuCustom(HWND hWnd, HMENU hMenu);

BOOL WINAPI Hook_SetMenu(HWND hWnd, HMENU hMenu) {

	// ���̂��̂��Ăяo��
	BOOL nResult = ((PFNSETMENU)pfnOrigSetMenu)(hWnd, hMenu);

    // ��ɃJ�X�^���̕������s�B
    Hook_SetMenuCustom(hWnd, hMenu);

	return nResult;
}


//---------------------------ReleaseDC

using PFNRELEASEDC = int(WINAPI *)(HWND, HDC);

PROC pfnOrigReleaseDC = GetProcAddress(GetModuleHandleA("user32.dll"), "ReleaseDC");

extern int Hook_ReleaseDCCustom(HWND hWnd, HDC hDC);

int WINAPI Hook_ReleaseDC(
    HWND hWnd,  // �E�B���h�E�̃n���h��
    HDC hDC     // �f�o�C�X�R���e�L�X�g�̃n���h��
) {
	// ��ɃJ�X�^���̕������s�B
	Hook_ReleaseDCCustom(hWnd, hDC);

	// ���̂��̂��Ăяo��
	int nResult = ((PFNRELEASEDC)pfnOrigReleaseDC)(hWnd, hDC);

	return nResult;
}

//---------------------------EnableMenuItem

using PFNENABLEMENUITEM = BOOL(WINAPI *)(HMENU, UINT, UINT);

PROC pfnOrigEnableMenuItem = GetProcAddress(GetModuleHandleA("user32.dll"), "EnableMenuItem");

extern BOOL Hook_EnableMenuItemCustom(HMENU hMenu, UINT uIDEnableItem, UINT uEnable);

BOOL WINAPI Hook_EnableMenuItem(
    HMENU hMenu, // ���j���[�̃n���h��
    UINT uIDEnableItem, // ���j���[���ڂ̎��ʎq�܂��͈ʒu
    UINT uEnable // ���j���[���ڂ̏��
) {
	// ��ɃJ�X�^���̕������s�B
	Hook_EnableMenuItemCustom(hMenu, uIDEnableItem, uEnable);

	// ���̂��̂��Ăяo��
	BOOL nResult = ((PFNENABLEMENUITEM)pfnOrigEnableMenuItem)(hMenu, uIDEnableItem, uEnable);

	return nResult;
}

//---------------------------BitBlt

using PFNBITBLT = BOOL(WINAPI *)(HDC, int, int, int, int, HDC, int, int, DWORD);

PROC pfnOrigBitBlt = GetProcAddress(GetModuleHandleA("gdi32.dll"), "BitBlt");

extern BOOL Hook_BitBltCustom(HDC hdcDest, int nXDest, int nYDest, int nWidth, int nHeight, HDC hdcSrc, int nXSrc, int nYSrc, DWORD dwRop);

BOOL WINAPI Hook_BitBlt(
    HDC hdcDest, // �o�̓f�o�C�X�R���e�L�X�g�̃n���h��
    int nXDest,  // �o�͐�̒����`�̍������ x ���W
    int nYDest,  // �o�͐�̒����`�̍������ y ���W
    int nWidth,  // �o�͐�̒����`�̕��i�s�N�Z���P�ʁj
    int nHeight, // �o�͐�̒����`�̍����i�s�N�Z���P�ʁj
    HDC hdcSrc,  // ���̓f�o�C�X�R���e�L�X�g�̃n���h��
    int nXSrc,   // ���͌��̒����`�̍������ x ���W
    int nYSrc,   // ���͌��̒����`�̍������ y ���W
    DWORD dwRop  // ���X�^�I�y���[�V�����R�[�h
) {
	// ��ɃJ�X�^���̕������s�B
    Hook_BitBltCustom(hdcDest, nXDest, nYDest, nWidth, nHeight, hdcSrc, nXSrc, nYSrc, dwRop);

	// ���̂��̂��Ăяo��
	BOOL nResult = ((PFNBITBLT)pfnOrigBitBlt)(hdcDest, nXDest, nYDest, nWidth, nHeight, hdcSrc, nXSrc, nYSrc, dwRop);

	return nResult;
}

//---------------------------CreateDIBitmap

using PFNCREATEDIBITMAP = HBITMAP(WINAPI *)(HDC, const BITMAPINFOHEADER *, DWORD, const void *, const BITMAPINFO *, UINT);

PROC pfnOrigCreateDIBitmap = GetProcAddress(GetModuleHandleA("gdi32.dll"), "CreateDIBitmap");

extern HBITMAP Hook_CreateDIBitmapCustom(HDC hdc, const BITMAPINFOHEADER *pbmih, DWORD flInit, const void *pjBits, const BITMAPINFO *pbmi, UINT iUsage);

HBITMAP WINAPI Hook_CreateDIBitmap(
    HDC hdc, // �f�o�C�X�R���e�L�X�g�̃n���h��
    const BITMAPINFOHEADER* pbmih, // �r�b�g�}�b�v���̃|�C���^
    DWORD flInit, // �r�b�g�}�b�v�̏��������@
    const void* pjBits, // �r�b�g�}�b�v�̏������f�[�^
    const BITMAPINFO* pbmi, // �r�b�g�}�b�v�̃J���[�e�[�u��
    UINT iUsage // �r�b�g�}�b�v�̎g�p���@
) {
	// ��ɃJ�X�^���̕������s�B
	Hook_CreateDIBitmapCustom(hdc, pbmih, flInit, pjBits, pbmi, iUsage);

	// ���̂��̂��Ăяo��
	HBITMAP nResult = ((PFNCREATEDIBITMAP)pfnOrigCreateDIBitmap)(hdc, pbmih, flInit, pjBits, pbmi, iUsage);

	return nResult;
}


//---------------------------CreateCompatibleDC

using PFNCREATECOMPATIBLEDC = HDC(WINAPI *)(HDC);

PROC pfnOrigCreateCompatibleDC = GetProcAddress(GetModuleHandleA("gdi32.dll"), "CreateCompatibleDC");

extern HDC Hook_CreateCompatibleDCCustom(HDC hdc);

HDC WINAPI Hook_CreateCompatibleDC(
    HDC hdc // �f�o�C�X�R���e�L�X�g�̃n���h��
) {
	// ��ɃJ�X�^���̕������s�B
	Hook_CreateCompatibleDCCustom(hdc);

	// ���̂��̂��Ăяo��
	HDC nResult = ((PFNCREATECOMPATIBLEDC)pfnOrigCreateCompatibleDC)(hdc);

	return nResult;
}

//---------------------------GetDIBits

using PFNGETDIBITS = int(WINAPI *)(HDC, HBITMAP, UINT, UINT, LPVOID, LPBITMAPINFO, UINT);

PROC pfnOrigGetDIBits = GetProcAddress(GetModuleHandleA("gdi32.dll"), "GetDIBits");

extern int Hook_GetDIBitsCustom(HDC hdc, HBITMAP hbm, UINT start, UINT cLines, LPVOID lpvBits, LPBITMAPINFO lpbmi, UINT usage);

int WINAPI Hook_GetDIBits(
    HDC hdc, // �f�o�C�X�R���e�L�X�g�̃n���h��
    HBITMAP hbm, // �r�b�g�}�b�v�̃n���h��
    UINT start, // �X�L�������C���̍ŏ��̃C���f�b�N�X
    UINT cLines, // �X�L�������C���̐�
    LPVOID lpvBits, // �r�b�g�}�b�v�f�[�^�̃|�C���^
    LPBITMAPINFO lpbmi, // �r�b�g�}�b�v���̃|�C���^
    UINT usage // �r�b�g�}�b�v�̎g�p���@
) {
	// ��ɃJ�X�^���̕������s�B
	Hook_GetDIBitsCustom(hdc, hbm, start, cLines, lpvBits, lpbmi, usage);

	// ���̂���
    int nResult = ((PFNGETDIBITS)pfnOrigGetDIBits)(hdc, hbm, start, cLines, lpvBits, lpbmi, usage);

    return nResult;
}

//---------------------------CreateFileA

using PFNCREATEFILEA = HANDLE(WINAPI*)(LPCSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE);

PROC pfnOrigCreateFileA = GetProcAddress(GetModuleHandleA("kernel32.dll"), "CreateFileA");
int nTargetKaoID = -1;
int nTargetKahouGazouID = -1;
// extern HANDLE Hook_CreateFileACustom(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);
HANDLE hFileKAODATA = NULL;
HANDLE hFileITEMDATA = NULL;
HANDLE WINAPI Hook_CreateFileA(
    LPCSTR lpFileName, // �t�@�C����
    DWORD dwDesiredAccess, // �A�N�Z�X���@
    DWORD dwShareMode, // ���L���@
    LPSECURITY_ATTRIBUTES lpSecurityAttributes, // �Z�L�����e�B�L�q�q
    DWORD dwCreationDisposition, // �쐬���@
    DWORD dwFlagsAndAttributes, // �t�@�C������
    HANDLE hTemplateFile // �e���v���[�g�t�@�C���̃n���h��
) {

    HANDLE nResult;

    string overrideFileName = string("OVERRIDE\\") + lpFileName;
    if (isFileExists(overrideFileName)) {
        // ���̂���
        nResult = ((PFNCREATEFILEA)pfnOrigCreateFileA)(overrideFileName.c_str(), dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
    }
    else {
        // ���̂���
        nResult = ((PFNCREATEFILEA)pfnOrigCreateFileA)(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
    }
    // ��ɃJ�X�^���̕������s�B
    // Hook_CreateFileACustom(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
    nTargetKaoID = -1;
    nTargetKahouGazouID = -1;

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
    return nResult;
}

//---------------------------SetFilePointer

using PFNSETFILEPOINTER = DWORD(WINAPI *)(HANDLE, LONG, PLONG, DWORD);

PROC pfnOrigSetFilePointer = GetProcAddress(GetModuleHandleA("kernel32.dll"), "SetFilePointer");
// extern DWORD Hook_SetFilePointerCustom(HANDLE hFile, LONG lDistanceToMove, PLONG lpDistanceToMoveHigh, DWORD dwMoveMethod);
DWORD WINAPI Hook_SetFilePointer(
	HANDLE hFile, // �t�@�C���̃n���h��
	LONG lDistanceToMove, // �ړ���
	PLONG lpDistanceToMoveHigh, // �ړ��ʂ̏�� 32 �r�b�g
	DWORD dwMoveMethod // �ړ����@
) {
	// ��ɃJ�X�^���̕������s�B
	// Hook_SetFilePointerCustom(hFile, lDistanceToMove, lpDistanceToMoveHigh, dwMoveMethod);

    nTargetKaoID = -1;
    nTargetKahouGazouID = -1;
	// ���̂���
	DWORD nResult = ((PFNSETFILEPOINTER)pfnOrigSetFilePointer)(hFile, lDistanceToMove, lpDistanceToMoveHigh, dwMoveMethod);
    if (hFileKAODATA == hFile) {
        const int pic_data_size = (64 * 80) * 769; // 769�̊�摜�������Ă���
        const int file_org_size = 3949588; // KAODATA.NB7�̃t�@�C���T�C�Y
        const int header_size = file_org_size - pic_data_size;
        nTargetKaoID = (lDistanceToMove - header_size) / (64 * 80);
        OutputDebugStream("��SetFilePointer:" + std::to_string(lDistanceToMove) + "\n");
    }
    else if (hFileITEMDATA == hFile) {
        const int pic_data_size = (64 * 64) * 27; // 27�̉ƕ�摜�������Ă���
        const int file_org_size = 111028; // ITEMDATA.NB7�̃t�@�C���T�C�Y
        const int header_size = file_org_size - pic_data_size;
        nTargetKahouGazouID = (lDistanceToMove - header_size) / (64 * 64);
        OutputDebugStream("�ƕ�SetFilePointer:" + std::to_string(lDistanceToMove) + "\n");
    }
	return nResult;
}


//---------------------------ReadFile

using PFNREADFILE = BOOL(WINAPI *)(HANDLE, LPVOID, DWORD, LPDWORD, LPOVERLAPPED);

PROC pfnOrigReadFile = GetProcAddress(GetModuleHandleA("kernel32.dll"), "ReadFile");

extern BOOL Hook_ReadFileCustom_BushouKao(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped);
extern BOOL Hook_ReadFileCustom_KahouPic(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped);

BOOL WINAPI Hook_ReadFile(
	HANDLE hFile, // �t�@�C���̃n���h��
	LPVOID lpBuffer, // �f�[�^�̊i�[��
	DWORD nNumberOfBytesToRead, // �ǂݍ��ރo�C�g��
	LPDWORD lpNumberOfBytesRead, // ���ۂɓǂݍ��񂾃o�C�g��
	LPOVERLAPPED lpOverlapped // �I�[�o�[���b�v�\���̂̃|�C���^
) {

	// ���̂���
	BOOL nResult = ((PFNREADFILE)pfnOrigReadFile)(hFile, lpBuffer, nNumberOfBytesToRead, lpNumberOfBytesRead, lpOverlapped);

    if (hFileKAODATA == hFile) {
        OutputDebugStream("�ǂݍ��ރo�C�g��%d", nNumberOfBytesToRead);
        Hook_ReadFileCustom_BushouKao(hFile, lpBuffer, nNumberOfBytesToRead, lpNumberOfBytesRead, lpOverlapped);
    }
    else if (hFileITEMDATA == hFile) {
        OutputDebugStream("�ǂݍ��ރo�C�g��%d", nNumberOfBytesToRead);
        Hook_ReadFileCustom_KahouPic(hFile, lpBuffer, nNumberOfBytesToRead, lpNumberOfBytesRead, lpOverlapped);
    }

    nTargetKaoID = -1;
    nTargetKahouGazouID = -1;
  
    return nResult;
}

//---------------------------CloseHandle

using PFNCLOSEHANDLE = BOOL(WINAPI *)(HANDLE);

PROC pfnOrigCloseHandle = GetProcAddress(GetModuleHandleA("kernel32.dll"), "CloseHandle");

BOOL WINAPI Hook_CloseHandle(
    HANDLE hObject // �I�u�W�F�N�g�̃n���h��
) {

    if (hFileKAODATA == hObject) {
        OutputDebugStream("CloseHandle:KAODATA\n");
        hFileKAODATA = NULL;
    }
    else if (hFileITEMDATA == hObject) {
        OutputDebugStream("CloseHandle:ITEMDATA\n");
        hFileITEMDATA = NULL;
    }
    else {
        // OutputDebugStream("CloseHandle:���̑�\n");
    }

	// ���̂���
	BOOL nResult = ((PFNCLOSEHANDLE)pfnOrigCloseHandle)(hObject);

	return nResult;
}


//---------------------------SelectObject

using PFNSELECTOBJECT = HGDIOBJ(WINAPI *)(HDC, HGDIOBJ);

PROC pfnOrigSelectObject = GetProcAddress(GetModuleHandleA("gdi32.dll"), "SelectObject");

// extern HGDIOBJ Hook_SelectObjectCustom(HDC hdc, HGDIOBJ h);

HGDIOBJ WINAPI Hook_SelectObject(
    HDC hdc, // �f�o�C�X�R���e�L�X�g�̃n���h��
    HGDIOBJ h // �I�u�W�F�N�g�̃n���h��
) {
	// ��ɃJ�X�^���̕������s�B
    // Hook_SelectObjectCustom(hdc, h);

	// ���̂���
	HGDIOBJ nResult = ((PFNSELECTOBJECT)pfnOrigSelectObject)(hdc, h);

	return nResult;
}

//---------------------------IsDebuggerPresent

using PFNISDEBUGGERPRESENT = BOOL(WINAPI *)();

PROC pfnOrigIsDebuggerPresent = GetProcAddress(GetModuleHandleA("kernel32.dll"), "IsDebuggerPresent");

extern BOOL Hook_IsDebuggerPresentCustom();

BOOL WINAPI Hook_IsDebuggerPresent() {
	// ��ɃJ�X�^���̕������s�B
	Hook_IsDebuggerPresentCustom();

	// ���̂���
	BOOL nResult = ((PFNISDEBUGGERPRESENT)pfnOrigIsDebuggerPresent)();

	return FALSE;
}




/*----------------------------------------------------------------*
 HOOK�n����
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
bool isHookCreateFileA = false;
bool isHookSetFilePointer = false;
bool isHookReadFile = false;
bool isHookSelectObject = false;
bool isHookCloseHandle = false;

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
    if (!isHookSelectObject) {
		isHookSelectObject = true;
		pfnOrig = ::GetProcAddress(GetModuleHandleA("gdi32.dll"), "SelectObject");
		ReplaceIATEntryInAllMods("gdi32.dll", pfnOrig, (PROC)Hook_SelectObject);
	}
    if (!isHookIsDebuggerPresent) {
		isHookIsDebuggerPresent = true;
		pfnOrig = ::GetProcAddress(GetModuleHandleA("kernel32.dll"), "IsDebuggerPresent");
		ReplaceIATEntryInAllMods("kernel32.dll", pfnOrig, (PROC)Hook_IsDebuggerPresent);
	}
}