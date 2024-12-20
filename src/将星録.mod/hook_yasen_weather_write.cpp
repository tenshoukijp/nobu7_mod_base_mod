/*
00471430   833D 00525800 00 CMP DWORD PTR DS:[585200],0
00471437   56               PUSH ESI
00471438   8BF1             MOV ESI,ECX
0047143A   74 0A            JE SHORT Nobunaga.00471446
0047143C   E8 2FFAFFFF      CALL Nobunaga.00470E70
00471441   A3 04525800      MOV DWORD PTR DS:[585204],EAX // この0x585204が天候の値。0:晴 1:曇 2:雨 3:雪
00471446   8BCE             MOV ECX,ESI
00471448   E8 C3FCFFFF      CALL Nobunaga.00471110
0047144D   83BE 84000000 02 CMP DWORD PTR DS:[ESI+84],2
*/


extern int getYasenWeather();

extern void setYasenWeather(int nWeather);

#include <windows.h>
#include <string>
#include "output_debug_stream.h"
#include "game_process.h"


using namespace std;

#pragma unmanaged

bool isWriteYasenWeather = false;
void OnSSRExeYasenWeatherWriteExecute() {
	isWriteYasenWeather = true;
	OutputDebugStream("★★★★野戦の天候書き換え時★%d\n", getYasenWeather());

	// setYangseWeather(3);
	// ★★★★ 野戦の天候を問い合わせる関数を作成するならば、ここでJavaScriptのコールバック作成すること。
}


/*
00471430   833D 00525800 00 CMP DWORD PTR DS:[585200],0
00471437   56               PUSH ESI
00471438   8BF1             MOV ESI,ECX
0047143A   74 0A            JE SHORT Nobunaga.00471446
0047143C   E8 2FFAFFFF      CALL Nobunaga.00470E70
00471441   A3 04525800      MOV DWORD PTR DS:[585204],EAX // この0x585204が天候の値。0:晴 1:曇 2:雨 3:雪
00471446   8BCE             MOV ECX,ESI
00471448   E8 C3FCFFFF      CALL Nobunaga.00471110
0047144D   83BE 84000000 02 CMP DWORD PTR DS:[ESI+84],2
*/
int pSSRExeJumpFromToOnSSRExeYasenWeatherWrite = 0x471448; // 関数はこのアドレスから、OnSSRExeYasenWeatherWriteへとジャンプしてくる。
int pSSRExeJumpCallFromToOnSSRExeYasenWeatherWrite = 0x471110; // 元々あった処理のCall先
int pSSRExeReturnLblFromOnSSRExeYasenWeatherWrite = 0x47144D; // 関数が最後までいくと、この実行exe内に直接ジャンプする

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeYasenWeatherWrite() {
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

	OnSSRExeYasenWeatherWriteExecute();

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

		call pSSRExeJumpCallFromToOnSSRExeYasenWeatherWrite;

		jmp pSSRExeReturnLblFromOnSSRExeYasenWeatherWrite
	}
}
#pragma warning(default: 4733) // ワーニングの抑制を解除する



char cmdOnSSRExeJumpFromYasenWeatherWrite[6] = "\xE9";
// 元の命令が5バイト、以後の関数で生まれる命令が合計５バイトなので… 最後１つ使わない

// ニーモニック書き換え用
void WriteAsmJumperOnSSRExeYasenWeatherWrite() {

	// まずアドレスを数字として扱う
	int iAddress = (int)OnSSRExeYasenWeatherWrite;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeYasenWeatherWrite + 5);
	// ５というのは、0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  の命令に必要なバイト数。要するに５バイト足すと次のニーモニック命令群に移動するのだ。そしてそこからの差分がジャンプする際の目的格として利用される。
	memcpy(cmdOnSSRExeJumpFromYasenWeatherWrite + 1, &SubAddress, 4); // +1 はE9の次から4バイト分書き換えるから。

	// 構築したニーモニック命令を実行exeのメモリに書き換える
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeYasenWeatherWrite), cmdOnSSRExeJumpFromYasenWeatherWrite, 5, NULL); //5バイトのみ書き込む
}

#pragma managed
