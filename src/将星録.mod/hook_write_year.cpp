/*
004C4F1B   50               PUSH EAX
004C4F1C   E8 8FB5F7FF      CALL Nobunaga.004404B0
004C4F21   8946 16          MOV DWORD PTR DS:[ESI+16],EAX   // 現在の年を書いているか？
004C4F24   0FBF43 02        MOVSX EAX,WORD PTR DS:[EBX+2]
004C4F28   8B56 22          MOV EDX,DWORD PTR DS:[ESI+22]
004C4F2B   52               PUSH EDX
004C4F2C   50               PUSH EAX
004C4F2D   E8 7EB5F7FF      CALL Nobunaga.004404B0
004C4F32   8946 1E          MOV DWORD PTR DS:[ESI+1E],EAX  // 現在の月を書いているか？
004C4F35   0FBF43 04        MOVSX EAX,WORD PTR DS:[EBX+4]
004C4F39   33C9             XOR ECX,ECX
004C4F3B   83C4 1C          ADD ESP,1C
004C4F3E   85C0             TEST EAX,EAX
004C4F40   0F9CC1           SETL CL
004C4F43   83E9 01          SUB ECX,1
004C4F46   23C8             AND ECX,EAX
004C4F48   890E             MOV DWORD PTR DS:[ESI],ECX
004C4F4A   0FB743 06        MOVZX EAX,WORD PTR DS:[EBX+6]
004C4F4E   66:85C0          TEST AX,AX
004C4F51   7E 27            JLE SHORT Nobunaga.004C4F7A
004C4F53   66:3D 4000       CMP AX,40
004C4F57   7F 21            JG SHORT Nobunaga.004C4F7A

*/





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
#include "on_event.h"


using namespace std;

#pragma unmanaged

static int iWriteYearEAX = -1;
void OnSSRExeWriteYearExecute() {
	OutputDebugStream("★★★★年が初書き込みされました!!!:%d\n", iWriteYearEAX);
	onWriteYear();
}


/*
004C4F1B   50               PUSH EAX
004C4F1C   E8 8FB5F7FF      CALL Nobunaga.004404B0
004C4F21   8946 16          MOV DWORD PTR DS:[ESI+16],EAX   // 現在の年を書いているか？
004C4F24   0FBF43 02        MOVSX EAX,WORD PTR DS:[EBX+2]
*/



int pSSRExeJumpFromToOnSSRExeWriteYear = 0x4C4F1C; // 関数はこのアドレスから、OnSSRExeWriteYearへとジャンプしてくる。
int pSSRExeJumpCallFromToOnSSRExeWriteYear = 0x4404B0; // 元々あった処理のCall先
int pSSRExeReturnLblFromOnSSRExeWriteYear = 0x4C4F21; // 関数が最後までいくと、このTENSHOU.EXE内に直接ジャンプする

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeWriteYear() {
	// スタックにためておく
	__asm {

		call pSSRExeJumpCallFromToOnSSRExeWriteYear // 元の処理

		mov iWriteYearEAX, EAX

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeWriteYearExecute();

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

		jmp pSSRExeReturnLblFromOnSSRExeWriteYear
	}
}
#pragma warning(default: 4733) // ワーニングの抑制を解除する



char cmdOnSSRExeJumpFromWriteYear[6] = "\xE9";
// 元の命令が5バイト、以後の関数で生まれる命令が合計５バイトなので… 最後１つ使わない


// ニーモニック書き換え用
void WriteAsmJumperOnSSRExeWriteYear() {

	// まずアドレスを数字として扱う
	int iAddress = (int)OnSSRExeWriteYear;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeWriteYear + 5);
	// ５というのは、0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  の命令に必要なバイト数。要するに５バイト足すと次のニーモニック命令群に移動するのだ。そしてそこからの差分がジャンプする際の目的格として利用される。
	memcpy(cmdOnSSRExeJumpFromWriteYear + 1, &SubAddress, 4); // +1 はE9の次から4バイト分書き換えるから。

	// 構築したニーモニック命令をTENSHOU.EXEのメモリに書き換える
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeWriteYear), cmdOnSSRExeJumpFromWriteYear, 5, NULL); //5バイトのみ書き込む
}

#pragma managed
