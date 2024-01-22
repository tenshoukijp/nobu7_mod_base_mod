/*
0047E720   . 55             PUSH EBP
0047E721   . 56             PUSH ESI
0047E722   . 8BF1           MOV ESI,ECX                              
0047E724   . 8B8E 80000000  MOV ECX,DWORD PTR DS:[ESI+80]          // ECXが該当家宝への家宝情報ポインタ
0047E72A   . 57             PUSH EDI
0047E72B   . E8 80DCFFFF    CALL Nobunaga.0047C3B0
0047E730   . 8BCE           MOV ECX,ESI
0047E732   . 8BF8           MOV EDI,EAX
0047E734   . E8 97F60100    CALL Nobunaga.0049DDD0
0047E739   . 6A 04          PUSH 4                                   ; /Arg3 = 00000004
0047E73B   . 6A 17          PUSH 17                                  ; |Arg2 = 00000017
0047E73D   . 6A 10          PUSH 10                                  ; |Arg1 = 00000010
0047E73F   . B9 A8C86000    MOV ECX,Nobunaga.0060C8A8                ; |ASCII "儚"
0047E744   . E8 CB5B0800    CALL Nobunaga.00504314                   ; \Nobunaga.00504314
0047E749   . 8B8E 80000000  MOV ECX,DWORD PTR DS:[ESI+80]
0047E74F   . 6A 38          PUSH 38
0047E751   . BD 08000000    MOV EBP,8
0047E756   . 55             PUSH EBP
0047E757   . E8 04DCFFFF    CALL Nobunaga.0047C360
0047E75C   . 8B8E 80000000  MOV ECX,DWORD PTR DS:[ESI+80]
0047E762   . 6A 01          PUSH 1
0047E764   . E8 F7DCFFFF    CALL Nobunaga.0047C460
0047E769   . 50             PUSH EAX                                 ; |Arg1
0047E76A   . E8 1C350800    CALL Nobunaga.00501C8B                   ; \Nobunaga.00501C8B
0047E76F   . 8BC8           MOV ECX,EAX
0047E771   . 83C4 08        ADD ESP,8
0047E774   . 81F9 C8000000  CMP ECX,0C8
0047E77A   . 0F83 5E020000  JNB Nobunaga.0047E9DE
0047E780   . B8 1F85EB51    MOV EAX,51EB851F
0047E785   . F7E1           MUL ECX
0047E787   . 53             PUSH EBX
0047E788   . C1EA 04        SHR EDX,4
0047E78B   . 8BDA           MOV EBX,EDX
0047E78D   . 69DB C2010000  IMUL EBX,EBX,1C2
0047E793   . 6A 00          PUSH 0
0047E795   . 6A 00          PUSH 0
0047E797   . 6A 00          PUSH 0
0047E799   . 03D9           ADD EBX,ECX
0047E79B   . 6A 00          PUSH 0
0047E79D   . 8D9C1B 007D000>LEA EBX,DWORD PTR DS:[EBX+EBX+7D00]
0047E7A4   . 6A 00          PUSH 0
0047E7A6   . 53             PUSH EBX
0047E7A7   . 892D E0ED5300  MOV DWORD PTR DS:[53EDE0],EBP
0047E7AD   . 892D 88C86000  MOV DWORD PTR DS:[60C888],EBP
0047E7B3   . C705 8CC86000 >MOV DWORD PTR DS:[60C88C],20
0047E7BD   . E8 2E850100    CALL Nobunaga.00496CF0
0047E7C2   . 50             PUSH EAX
0047E7C3   . 68 0C0A5200    PUSH Nobunaga.00520A0C                   ;  ASCII "%s"
0047E7C8   . 68 A8C86000    PUSH Nobunaga.0060C8A8                   ;  ASCII "儚"
0047E7CD   . E8 005E0800    CALL Nobunaga.005045D2
0047E7D2   . 6A 00          PUSH 0
0047E7D4   . 6A 00          PUSH 0
0047E7D6   . 6A 00          PUSH 0
0047E7D8   . 6A 00          PUSH 0
0047E7DA   . 6A 00          PUSH 0
0047E7DC   . 83C3 01        ADD EBX,1
0047E7DF   . 53             PUSH EBX
0047E7E0   . 892D E0ED5300  MOV DWORD PTR DS:[53EDE0],EBP
0047E7E6   . 892D 88C86000  MOV DWORD PTR DS:[60C888],EBP
0047E7EC   . C705 8CC86000 >MOV DWORD PTR DS:[60C88C],94
0047E7F6   . E8 F5840100    CALL Nobunaga.00496CF0
0047E7FB   . 50             PUSH EAX
0047E7FC   . 68 0C0A5200    PUSH Nobunaga.00520A0C                   ;  ASCII "%s"
0047E801   . 68 A8C86000    PUSH Nobunaga.0060C8A8                   ;  ASCII "儚"
0047E806   . E8 C75D0800    CALL Nobunaga.005045D2
0047E80B   . 83C4 48        ADD ESP,48
0047E80E   . 6A 09          PUSH 9
0047E810   . B8 E4000000    MOV EAX,0E4
0047E815   . 68 68A65800    PUSH Nobunaga.0058A668
0047E81A   . A3 E0ED5300    MOV DWORD PTR DS:[53EDE0],EAX
0047E81F   . A3 88C86000    MOV DWORD PTR DS:[60C888],EAX
0047E824   . C705 8CC86000 >MOV DWORD PTR DS:[60C88C],40
0047E82E   . 8B8E 80000000  MOV ECX,DWORD PTR DS:[ESI+80]
0047E834   . 6A 01          PUSH 1
0047E836   . E8 85E1FFFF    CALL Nobunaga.0047C9C0
0047E83B   . 50             PUSH EAX                                 ; /Arg3
0047E83C   . 68 0C0A5200    PUSH Nobunaga.00520A0C                   ; |Arg2 = 00520A0C ASCII "%s"
0047E841   . 68 A8C86000    PUSH Nobunaga.0060C8A8                   ; |Arg1 = 0060C8A8
0047E846   . E8 875D0800    CALL Nobunaga.005045D2                   ; \Nobunaga.005045D2
0047E84B   . 83C4 0C        ADD ESP,0C
0047E84E   . 6A 07          PUSH 7
0047E850   . B8 EC000000    MOV EAX,0EC
0047E855   . 68 68A65800    PUSH Nobunaga.0058A668
0047E85A   . A3 E0ED5300    MOV DWORD PTR DS:[53EDE0],EAX
0047E85F   . A3 88C86000    MOV DWORD PTR DS:[60C888],EAX
0047E864   . C705 8CC86000 >MOV DWORD PTR DS:[60C88C],60
0047E86E   . 8B8E 80000000  MOV ECX,DWORD PTR DS:[ESI+80]
0047E874   . 6A 02          PUSH 2
0047E876   . E8 45E1FFFF    CALL Nobunaga.0047C9C0
0047E87B   . 50             PUSH EAX
0047E87C   . 68 70415200    PUSH Nobunaga.00524170                   ;  ASCII "%6s"
0047E881   . 68 A8C86000    PUSH Nobunaga.0060C8A8                   ;  ASCII "儚"
0047E886   . E8 475D0800    CALL Nobunaga.005045D2
0047E88B   . BB 54000000    MOV EBX,54
0047E890   . 891D E0ED5300  MOV DWORD PTR DS:[53EDE0],EBX
0047E896   . 891D 88C86000  MOV DWORD PTR DS:[60C888],EBX
0047E89C   . C705 8CC86000 >MOV DWORD PTR DS:[60C88C],38
0047E8A6   . 8B8E 80000000  MOV ECX,DWORD PTR DS:[ESI+80]
0047E8AC   . 83C4 0C        ADD ESP,0C
0047E8AF   . E8 0CDCFFFF    CALL Nobunaga.0047C4C0
0047E8B4   . F7D8           NEG EAX
0047E8B6   . 1BC0           SBB EAX,EAX
0047E8B8   . 23C7           AND EAX,EDI
0047E8BA   . 50             PUSH EAX                                 ; /Arg3
0047E8BB   . 68 64415200    PUSH Nobunaga.00524164                   ; |Arg2 = 00524164
0047E8C0   . 68 A8C86000    PUSH Nobunaga.0060C8A8                   ; |Arg1 = 0060C8A8
0047E8C5   . E8 085D0800    CALL Nobunaga.005045D2                   ; \Nobunaga.005045D2
0047E8CA   . 83C4 0C        ADD ESP,0C
0047E8CD   . 891D E0ED5300  MOV DWORD PTR DS:[53EDE0],EBX
0047E8D3   . 891D 88C86000  MOV DWORD PTR DS:[60C888],EBX
0047E8D9   . C705 8CC86000 >MOV DWORD PTR DS:[60C88C],50
0047E8E3   . 8B8E 80000000  MOV ECX,DWORD PTR DS:[ESI+80]
0047E8E9   . E8 F2DBFFFF    CALL Nobunaga.0047C4E0
0047E8EE   . F7D8           NEG EAX
0047E8F0   . 1BC0           SBB EAX,EAX
0047E8F2   . 23C7           AND EAX,EDI
0047E8F4   . 50             PUSH EAX
0047E8F5   . 68 58415200    PUSH Nobunaga.00524158                   ;  ASCII "戦闘 +%2d"
0047E8FA   . 68 A8C86000    PUSH Nobunaga.0060C8A8                   ;  ASCII "儚"
0047E8FF   . E8 CE5C0800    CALL Nobunaga.005045D2
0047E904   . 891D E0ED5300  MOV DWORD PTR DS:[53EDE0],EBX
0047E90A   . 891D 88C86000  MOV DWORD PTR DS:[60C888],EBX
0047E910   . C705 8CC86000 >MOV DWORD PTR DS:[60C88C],68
0047E91A   . 8B8E 80000000  MOV ECX,DWORD PTR DS:[ESI+80]
0047E920   . 83C4 0C        ADD ESP,0C
0047E923   . E8 D8DBFFFF    CALL Nobunaga.0047C500
0047E928   . F7D8           NEG EAX
0047E92A   . 1BC0           SBB EAX,EAX
0047E92C   . 23C7           AND EAX,EDI
0047E92E   . 50             PUSH EAX                                 ; /Arg3
0047E92F   . 68 4C415200    PUSH Nobunaga.0052414C                   ; |Arg2 = 0052414C
0047E934   . 68 A8C86000    PUSH Nobunaga.0060C8A8                   ; |Arg1 = 0060C8A8
0047E939   . E8 945C0800    CALL Nobunaga.005045D2                   ; \Nobunaga.005045D2
0047E93E   . 83C4 0C        ADD ESP,0C
0047E941   . 33FF           XOR EDI,EDI
0047E943   . BB 38000000    MOV EBX,38
0047E948   . EB 06          JMP SHORT Nobunaga.0047E950
0047E94A     8D9B 00000000  LEA EBX,DWORD PTR DS:[EBX]
0047E950   > B8 98000000    MOV EAX,98
0047E955   . A3 E0ED5300    MOV DWORD PTR DS:[53EDE0],EAX
0047E95A   . A3 88C86000    MOV DWORD PTR DS:[60C888],EAX
0047E95F   . 891D 8CC86000  MOV DWORD PTR DS:[60C88C],EBX
0047E965   . 8B8E 80000000  MOV ECX,DWORD PTR DS:[ESI+80]
0047E96B   . E8 80D6FFFF    CALL Nobunaga.0047BFF0
0047E970   . 3BC7           CMP EAX,EDI
0047E972   . B8 44415200    MOV EAX,Nobunaga.00524144                ;  ASCII "上昇"
0047E977   . 74 05          JE SHORT Nobunaga.0047E97E
0047E979   . B8 780B5200    MOV EAX,Nobunaga.00520B78                ;  ASCII "－－"
0047E97E   > 50             PUSH EAX                                 ; /Arg4
0047E97F   . 8B04BD 68AA530>MOV EAX,DWORD PTR DS:[EDI*4+53AA68]      ; |
0047E986   . 50             PUSH EAX                                 ; |Arg3
0047E987   . 68 3C415200    PUSH Nobunaga.0052413C                   ; |Arg2 = 0052413C ASCII "%4s %4s"
0047E98C   . 68 A8C86000    PUSH Nobunaga.0060C8A8                   ; |Arg1 = 0060C8A8
0047E991   . E8 3C5C0800    CALL Nobunaga.005045D2                   ; \Nobunaga.005045D2
0047E996   . 83C3 10        ADD EBX,10
0047E999   . 83C4 10        ADD ESP,10
0047E99C   . 83C7 01        ADD EDI,1
0047E99F   . 83FB 78        CMP EBX,78
0047E9A2   .^7C AC          JL SHORT Nobunaga.0047E950
0047E9A4   . 892D E0ED5300  MOV DWORD PTR DS:[53EDE0],EBP
0047E9AA   . 892D 88C86000  MOV DWORD PTR DS:[60C888],EBP
0047E9B0   . C705 8CC86000 >MOV DWORD PTR DS:[60C88C],7C
0047E9BA   . 8B8E 80000000  MOV ECX,DWORD PTR DS:[ESI+80]
0047E9C0   . E8 ABD6FFFF    CALL Nobunaga.0047C070
0047E9C5   . 50             PUSH EAX
0047E9C6   . 68 A8C86000    PUSH Nobunaga.0060C8A8                   ;  ASCII "儚"
0047E9CB   . E8 025C0800    CALL Nobunaga.005045D2
0047E9D0   . 68 EC130000    PUSH 13EC
0047E9D5   . E8 86EB0700    CALL Nobunaga.004FD560
0047E9DA   . 83C4 0C        ADD ESP,0C
0047E9DD   . 5B             POP EBX
0047E9DE   > 5F             POP EDI
0047E9DF   . 5E             POP ESI
0047E9E0   . 5D             POP EBP
0047E9E1   . C3             RETN

*/


// このファイルは調査失敗。役に立たない。コンパイル対象から外れている

#include <windows.h>
#include <string>
#include "data_game_struct.h"
#include "data_bushou_struct.h"
#include "output_debug_stream.h"
#include "data_kahou_struct.h"
#include "data_kanni_struct.h"
#include "data_yakusyoku_struct.h"
#include "data_castle_struct.h"
#include "data_turn_struct.h"
#include "game_screen.h"
#include "game_process.h"
#include "on_serihu_message.h"
#include "bushou_albedo.h"
#include "game_screen.h"
#include "message_albedo.h"


using namespace std;

#pragma unmanaged

int isKahouRetsudenBeginning = false;
int iKahouIDShowBgn = -1;
static int iKahouShowBgnECX = -1; // 対象家宝へのポインタ。家宝配列への特定のポインタ
void OnSSRExeKahouShowBgnExecute() {
	isKahouRetsudenBeginning = true;
	OutputDebugStream("KahouShowBgn:%x", iKahouShowBgnECX);
	int iKahouID = (iKahouShowBgnECX - 家宝情報アドレス) / sizeof(NB7家宝情報型);
	if (isValidKahouID(iKahouID)) {
		iKahouIDShowBgn = iKahouID;
		OutputDebugStream("★★★★家宝ID:%d!!!★\n", iKahouID);
	}
}

/*
0047E720   . 55             PUSH EBP
0047E721   . 56             PUSH ESI
0047E722   . 8BF1           MOV ESI,ECX
0047E724   . 8B8E 80000000  MOV ECX,DWORD PTR DS:[ESI+80]
0047E72A   . 57             PUSH EDI
0047E72B   . E8 80DCFFFF    CALL Nobunaga.0047C3B0
0047E730   . 8BCE           MOV ECX,ESI
0047E732   . 8BF8           MOV EDI,EAX
*/
int pSSRExeJumpFromToOnSSRExeKahouShowBgn = 0x47E72B; // 関数はこのアドレスから、OnSSRExeKahouShowBgnへとジャンプしてくる。
int pSSRExeJumpCallFromToOnSSRExeKahouShowBgn = 0x47C3B0; // 元々あった処理のCall先
int pSSRExeReturnLblFromOnSSRExeKahouShowBgn = 0x47E730; // 関数が最後までいくと、このTENSHOU.EXE内に直接ジャンプする

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeKahouShowBgn() {
	// スタックにためておく
	__asm {
		mov iKahouShowBgnECX, ecx
		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeKahouShowBgnExecute();

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

		call pSSRExeJumpCallFromToOnSSRExeKahouShowBgn // 元の処理

		jmp pSSRExeReturnLblFromOnSSRExeKahouShowBgn
	}
}
#pragma warning(default: 4733) // ワーニングの抑制を解除する



char cmdOnSSRExeJumpFromKahouShowBgn[6] = "\xE9";
// 元の命令が5バイト、以後の関数で生まれる命令が合計５バイトなので… 最後１つ使わない


// ニーモニック書き換え用
void WriteAsmJumperOnSSRExeKahouShowBgn() {

	// まずアドレスを数字として扱う
	int iAddress = (int)OnSSRExeKahouShowBgn;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeKahouShowBgn + 5);
	// ５というのは、0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  の命令に必要なバイト数。要するに５バイト足すと次のニーモニック命令群に移動するのだ。そしてそこからの差分がジャンプする際の目的格として利用される。
	memcpy(cmdOnSSRExeJumpFromKahouShowBgn + 1, &SubAddress, 4); // +1 はE9の次から4バイト分書き換えるから。

	// 構築したニーモニック命令をTENSHOU.EXEのメモリに書き換える
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeKahouShowBgn), cmdOnSSRExeJumpFromKahouShowBgn, 5, NULL); //5バイトのみ書き込む
}

#pragma managed
