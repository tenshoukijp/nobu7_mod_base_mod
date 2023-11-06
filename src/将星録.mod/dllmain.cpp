#include <windows.h>
#include <stdio.h>

#include "将星録.mod.h"

extern void onFontInitialize();

HANDLE hCurrentProcess = NULL;

extern "C" __declspec(dllexport) void WINAPI onInitialize(void* reserved) {
	hCurrentProcess = ::GetCurrentProcess();
    OutputDebugString("onInitialize\r\n");
    onFontInitialize();

}

/*
005056B5   68 04EE5300      PUSH Nobunaga.0053EE04
005056BA   53               PUSH EBX
005056BB   53               PUSH EBX
005056BC   53               PUSH EBX
005056BD   53               PUSH EBX
005056BE   68 80000000      PUSH 80
005056C3   53               PUSH EBX
005056C4   53               PUSH EBX
005056C5   53               PUSH EBX
005056C6   53               PUSH EBX
005056C7   53               PUSH EBX
005056C8   53               PUSH EBX
005056C9   6A 08            PUSH 8
005056CB   6A F0            PUSH -10
 */

char buffferFontName[50] = "ＭＳ 明朝";
int pszFontAddress = (int)(&buffferFontName[0]);

extern void WriteAsmJumperOnNb7FontnameAddressPush();
void onFontInitialize() {
    OutputDebugString("onFontInitialize\r\n");

    strcpy_s((char*)0x53EE04, 11, "ＭＳ 明朝");
	// WriteAsmJumperOnNb7FontnameAddressPush();
}


extern "C" __declspec(dllexport) void WINAPI onGameInitialize() {
    HMODULE baseAddress = GetModuleHandle(NULL);
    char buffer[256] = "";
    sprintf_s(buffer, _countof(buffer), "%x", baseAddress);
    OutputDebugString("onGameInitialize\r\n");
    OutputDebugString(buffer);
    OutputDebugString("\r\n");
}

extern "C" __declspec(dllexport) void WINAPI onFinalize() {
    OutputDebugString("onFinalize\r\n");
}





/*
005056B5   68 04EE5300      PUSH Nobunaga.0053EE04
005056BA   53               PUSH EBX
005056BB   53               PUSH EBX
005056BC   53               PUSH EBX
005056BD   53               PUSH EBX
005056BE   68 80000000      PUSH 80
005056C3   53               PUSH EBX
005056C4   53               PUSH EBX
005056C5   53               PUSH EBX
005056C6   53               PUSH EBX
005056C7   53               PUSH EBX
005056C8   53               PUSH EBX
005056C9   6A 08            PUSH 8
005056CB   6A F0            PUSH -10
 */

void onNB7FontnameAddressPushExecute() {
	OutputDebugString("フォント名アドレスを変更しました");
}

int pNB7JumpFromToOnNB7FontnameAddressPush = 0x5056B5; // 関数はこのアドレスから、onNB7FontnameAddressPushへとジャンプしてくる。
int pNB7ReturnLblFromOnNB7FontnameAddressPush = 0x5056BA; // 関数が最後までいくと、このアドレスに直接戻るというなんとも危険な行為w

__declspec(naked) void WINAPI onNB7FontnameAddressPush() {
	// スタックにためておく
	__asm {

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	// フォント名が要求される時
	onNB7FontnameAddressPushExecute();

	// スタックに引き出す
	__asm {
		pop edi
		pop esi
		pop ebp
		pop esp
		pop edx
		pop ecx
		pop ebx
		pop eax

		push 0x53EE04; // 元の PUSH Nobunaga.0053EE04 相当

		jmp pNB7ReturnLblFromOnNB7FontnameAddressPush; // 元の命令に戻る
	}
}

char cmdOBN7JumpFromNB7FontnameAddressPush[6] = "\xE9";
// 元の命令が5バイト、以後の関数で生まれる命令が合計５バイトなので… 最後１つ使わない


// ニーモニック書き換え用
void WriteAsmJumperOnNb7FontnameAddressPush() {
	// まずアドレスを数字として扱う
	int iAddress = (int)onNB7FontnameAddressPush;
	int SubAddress = iAddress - (pNB7JumpFromToOnNB7FontnameAddressPush + 5);
	// ５というのは、0046C194  -E9 ????????  JMP Mod.onNB7FontnameAddressPush  の命令に必要なバイト数。要するに５バイト足すと次のニーモニック命令群に移動するのだ。そしてそこからの差分がジャンプする際の目的格として利用される。
	memcpy(cmdOBN7JumpFromNB7FontnameAddressPush + 1, &SubAddress, 4); // +1 はE9の次から4バイト分書き換えるから。

	// 構築したニーモニック命令をTENSHOU.EXEのメモリに書き換える
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pNB7JumpFromToOnNB7FontnameAddressPush), cmdOBN7JumpFromNB7FontnameAddressPush, 5, NULL); //5バイトのみ書き込む
}






