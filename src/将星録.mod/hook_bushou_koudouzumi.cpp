/*
EAX 00000800
ECX 00563C48 ASCII "宰相"
EDX 005DC328 ASCII "岡山"
EBX 000000C8
ESP 0019FC68 ASCII "ﾑNM"
EBP 00000000
ESI 00563C48 ASCII "宰相"
EDI 005F0310 Nobunaga.005F0310
EIP 0041ECBC Nobunaga.0041ECBC

ESIが武将情報の該当武将へのポインタ
0041ECB6   66:A1 9C865300   MOV AX,WORD PTR DS:[53869C]
0041ECBC   66:0981 A0000000 OR WORD PTR DS:[ECX+A0],AX
0041ECC3   833D 40235400 00 CMP DWORD PTR DS:[542340],0
0041ECCA   75 06            JNZ SHORT Nobunaga.0041ECD2
0041ECCC   8079 0E 00       CMP BYTE PTR DS:[ECX+E],0
0041ECD0  ^74 E1            JE SHORT Nobunaga.0041ECB3
0041ECD2   66:8B81 A0000000 MOV AX,WORD PTR DS:[ECX+A0]
0041ECD9   66:2305 9C865300 AND AX,WORD PTR DS:[53869C]
0041ECE0   66:F7D8          NEG AX
0041ECE3   1BC0             SBB EAX,EAX
0041ECE5   F7D8             NEG EAX
0041ECE7   C3               RETN
*/





#include <windows.h>
#include <map>

#include "data_game_struct.h"
#include "data_bushou_struct.h"
#include "output_debug_stream.h"
#include "game_process.h"
#include "bushou_albedo.h"
#include "usr_custom_mod.h"

using namespace std;


static int iBushouKoudouzumiECX = -1;
static int iPrevisouBushouIDKoudouzumi = -1;
static int iPreviousTimeGetTime = timeGetTime();

// 行動済みのキャッシュ。0.2秒だけ有効。これは行動済みのこのフックが複数回実行されてしまうため。
static const int iCacheTime = 200;
map<int, int> mapBushouKoudouzumiCacheInMonth;
void resetMapBushouKoudouzumiCacheInMonth() {
	mapBushouKoudouzumiCacheInMonth.clear();
}

void OnSSRExeBushouKoudouzumiExecute() {

	int iBushouID = getBushouIDFromBushouPtr((int *)iBushouKoudouzumiECX);

	int iCurrentTimeGetTime = timeGetTime();

	if (isValidBushouID(iBushouID)) {

		// 前回の武将IDと同じでかつ、200ミリ秒以内だとすると、前回フックした人だよ。
		if (iPrevisouBushouIDKoudouzumi == iBushouID && (iCurrentTimeGetTime - iPreviousTimeGetTime) < iCacheTime) {
			// その武将の特別な行動済み要件がキャッシュとして登録されている
			if (mapBushouKoudouzumiCacheInMonth.find(iBushouID) != mapBushouKoudouzumiCacheInMonth.end()) {
				OutputDebugStream(getBushou姓名FromBushouID(iBushouID) + "のキャッシュを利用しました\n");
				nb7武将情報[iBushouID].行動済 = mapBushouKoudouzumiCacheInMonth[iBushouID];

			}
			return;
		}
		// 異なる人、もしくは時間経過しすぎでキャッシュ無効
		else {
			iPrevisouBushouIDKoudouzumi = iBushouID;
			iPreviousTimeGetTime = iCurrentTimeGetTime;
			resetMapBushouKoudouzumiCacheInMonth();
		}

		// 新たにフック
		OutputDebugStream(getBushou姓名FromBushouID(iBushouID) + "、は行動済みのフックを通過しました\n");

		if (getBushou姓名FromBushouID(iBushouID) == getArubedoSeiMei()) {
			// アルベドの行動カウンタを減らす
			int 行動済 = decreaseAlbedoKoudouCounter(iBushouID);
			mapBushouKoudouzumiCacheInMonth[iBushouID] = 行動済;

			// アルベドが「使者」ならお金を最低金額維持
			アルベド使者ユニット時のお金が復活();
		}

		// C#のカスタム.mod.dllからの上書き
		try {
			System::Collections::Generic::Dictionary<System::String^, System::Object^>^ dic = gcnew System::Collections::Generic::Dictionary<System::String^, System::Object^>(5);
			dic->Add("武将番号", iBushouID);
			System::Collections::Generic::Dictionary<System::String^, System::Object^>^ ret = InvokeUserMethod("on武将行動済時", dic);

			if (ret != nullptr && ret->ContainsKey("行動済")) {
				int 行動済 = (int)(ret["行動済"]);
				mapBushouKoudouzumiCacheInMonth[iBushouID] = 行動済;
			}
		}
		catch (System::Exception^ ) {
			OutputDebugStream("on武将行動済時でエラーが発生しました。");
		}

		// ★★★ここでJavaScriptのメソッドを実行して、返り値を取得して、それが特別ならば、
		// 登録する。undefinedの返り値(要するに返り値を返していないならば)、登録しない
	}
}

#pragma unmanaged

/*
EAX 00000800
ECX 00563C48 ASCII "宰相"
EDX 005DC328 ASCII "岡山"
EBX 000000C8
ESP 0019FC68 ASCII "ﾑNM"
EBP 00000000
ESI 00563C48 ASCII "宰相"
EDI 005F0310 Nobunaga.005F0310
EIP 0041ECBC Nobunaga.0041ECBC

ESIが武将情報の該当武将へのポインタ
0041ECB6   66:A1 9C865300   MOV AX,WORD PTR DS:[53869C]
0041ECBC   66:0981 A0000000 OR WORD PTR DS:[ECX+A0],AX   ← この行の書き換え
0041ECC3   833D 40235400 00 CMP DWORD PTR DS:[542340],0
0041ECCA   75 06            JNZ SHORT Nobunaga.0041ECD2
0041ECCC   8079 0E 00       CMP BYTE PTR DS:[ECX+E],0
0041ECD0  ^74 E1            JE SHORT Nobunaga.0041ECB3
0041ECD2   66:8B81 A0000000 MOV AX,WORD PTR DS:[ECX+A0]
0041ECD9   66:2305 9C865300 AND AX,WORD PTR DS:[53869C]
0041ECE0   66:F7D8          NEG AX
0041ECE3   1BC0             SBB EAX,EAX
0041ECE5   F7D8             NEG EAX
0041ECE7   C3               RETN
*/



int pSSRExeJumpFromToOnSSRExeBushouKoudouzumi = 0x41ECBC; // 関数はこのアドレスから、OnSSRExeBushouKoudouzumiへとジャンプしてくる。
int pSSRExeReturnLblFromOnSSRExeBushouKoudouzumi = 0x41ECC3; // 関数が最後までいくと、このTENSHOU.EXE内に直接ジャンプする

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeBushouKoudouzumi() {
	// スタックにためておく
	__asm {

		mov iBushouKoudouzumiECX, ECX

		OR WORD PTR DS: [ECX + 0xA0] , AX // 行動済みを立てる

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeBushouKoudouzumiExecute();

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

		jmp pSSRExeReturnLblFromOnSSRExeBushouKoudouzumi
	}
}
#pragma warning(default: 4733) // ワーニングの抑制を解除する



char cmdOnSSRExeJumpFromBushouKoudouzumi[6] = "\xE9";
// 元の命令が5バイト、以後の関数で生まれる命令が合計５バイトなので… 最後１つ使わない


// ニーモニック書き換え用
void WriteAsmJumperOnSSRExeBushouKoudouzumi() {

	// まずアドレスを数字として扱う
	int iAddress = (int)OnSSRExeBushouKoudouzumi;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeBushouKoudouzumi + 5);
	// ５というのは、0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  の命令に必要なバイト数。要するに５バイト足すと次のニーモニック命令群に移動するのだ。そしてそこからの差分がジャンプする際の目的格として利用される。
	memcpy(cmdOnSSRExeJumpFromBushouKoudouzumi + 1, &SubAddress, 4); // +1 はE9の次から4バイト分書き換えるから。

	// 構築したニーモニック命令をTENSHOU.EXEのメモリに書き換える
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeBushouKoudouzumi), cmdOnSSRExeJumpFromBushouKoudouzumi, 5, NULL); //5バイトのみ書き込む
}

#pragma managed
