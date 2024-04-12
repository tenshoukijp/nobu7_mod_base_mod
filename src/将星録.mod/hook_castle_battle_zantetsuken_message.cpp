/*
004174B8   0F84 1E010000    JE Nobunaga.004175DC
004174BE   8BCB             MOV ECX,EBX
004174C0   E8 FBCAFEFF      CALL Nobunaga.00403FC0
004174C5   85C0             TEST EAX,EAX
004174C7   0F84 0F010000    JE Nobunaga.004175DC
004174CD   68 580E5200      PUSH Nobunaga.00520E58                   ; ASCII "斬鉄剣"
004174D2   68 D8A55D00      PUSH Nobunaga.005DA5D8
004174D7   E8 9BB20E00      CALL Nobunaga.00502777
004174DC   8B4C24 5C        MOV ECX,DWORD PTR SS:[ESP+5C]
004174E0   83C4 08          ADD ESP,8
*/




#include <windows.h>
#include <string>
#include <vector>
#include "data_game_struct.h"
#include "data_bushou_struct.h"
#include "output_debug_stream.h"
#include "game_process.h"
#include "on_serihu_message.h"
#include "bushou_albedo.h"
#include "usr_custom_mod.h"


using namespace std;


// 斬鉄剣を打った武将のBushouID
extern int iZantetsukenAttackBushouID;
extern vector<int> list話者BushouID;

static int DefaultZantetsukenMessagePtr = 0x520E58;  // 将星録のデフォルトとして斬鉄剣という文字列が存在するアドレス

char customZantetsukenMessage[256] = "";
static int CustomZantetsukenMessagePtr = (int)customZantetsukenMessage;

void OnSSRExeCastleBattleMessageZantetsukenExecute() {
	int iBushouID = iZantetsukenAttackBushouID;
	customZantetsukenMessage[0] = NULL;
	CustomZantetsukenMessagePtr = DefaultZantetsukenMessagePtr; // デフォルトでは斬鉄剣
	if (isValidBushouID(iBushouID)) {
		if (getBushou姓名FromBushouID(iBushouID) == getArubedoSeiMei()) {
			string message1 = "まるで紙のような脆き門ね\xA唸れ、バルディッシュ！";
			string message2 = "震えて死ぬのを待ちなさい\xA唸れ、バルディッシュ！";
			string message3 = "おんどりゃー！\xA虫けらが！";
			int rnd = rand() % 2;
			if (rnd == 2) {
				strcpy_s(customZantetsukenMessage, message1.c_str());
			}
			else if (rnd == 1) {
				strcpy_s(customZantetsukenMessage, message2.c_str());
			}
			else {
				strcpy_s(customZantetsukenMessage, message3.c_str());
			}
			CustomZantetsukenMessagePtr = (int)customZantetsukenMessage;
		}

		// C#のカスタム.mod.dllからの上書き
		try {
			System::Collections::Generic::Dictionary<System::String^, System::Object^>^ dic = gcnew System::Collections::Generic::Dictionary<System::String^, System::Object^>(5);
			dic->Add("メッセージ", gcnew System::String((char*)セリフメッセージアドレス));
			dic->Add("武将番号１人目", list話者BushouID[0]);
			dic->Add("武将番号２人目", list話者BushouID[1]);
			dic->Add("武将番号３人目", list話者BushouID[2]);
			dic->Add("武将番号４人目", list話者BushouID[3]);
			System::Collections::Generic::Dictionary<System::String^, System::Object^>^ ret = InvokeUserMethod("on武将メッセージ要求時", dic);
			if (ret != nullptr && ret->ContainsKey("メッセージ")) {
				System::String^ override_message = (System::String^)(ret["メッセージ"]);
				if (System::String::IsNullOrEmpty(override_message)) {
					;
				}
				else {
					strcpy_s(customZantetsukenMessage, to_native_string(override_message).c_str());
					CustomZantetsukenMessagePtr = (int)customZantetsukenMessage;
				}
			}

		}
		catch (System::Exception^ ) {
			OutputDebugStream("on武将メッセージ要求時でエラー");
		}

	}
}

#pragma unmanaged

/*
004174A1   0F85 F0000000    JNZ Nobunaga.00417597
004174A7   8B4424 54        MOV EAX,DWORD PTR SS:[ESP+54] // ここに攻撃した武将ポインタが入っている
004174AB   50               PUSH EAX
004174AC   B9 280F5400      MOV ECX,Nobunaga.00540F28
004174B1   E8 7A1BFFFF      CALL Nobunaga.00409030
004174B6   85C0             TEST EAX,EAX
004174B8   0F84 1E010000    JE Nobunaga.004175DC
004174BE   8BCB             MOV ECX,EBX
004174C0   E8 FBCAFEFF      CALL Nobunaga.00403FC0
004174C5   85C0             TEST EAX,EAX
004174C7   0F84 0F010000    JE Nobunaga.004175DC
004174CD   68 580E5200      PUSH Nobunaga.00520E58                   ; ASCII "斬鉄剣"
004174D2   68 D8A55D00      PUSH Nobunaga.005DA5D8
004174D7   E8 9BB20E00      CALL Nobunaga.00502777
004174DC   8B4C24 5C        MOV ECX,DWORD PTR SS:[ESP+5C]
004174E0   83C4 08          ADD ESP,8
*/


int pSSRExeJumpFromToOnSSRExeCastleBattleMessageZantetsuken = 0x4174CD; // 関数はこのアドレスから、OnSSRExeCastleBattleMessageZantetsukenへとジャンプしてくる。
int pSSRExeReturnLblFromOnSSRExeCastleBattleMessageZantetsuken = 0x4174D2; // 関数が最後までいくと、この実行exe内に直接ジャンプする

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeCastleBattleMessageZantetsuken() {
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

	OnSSRExeCastleBattleMessageZantetsukenExecute();

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

		PUSH CustomZantetsukenMessagePtr // 元の処理をここに記述する

		jmp pSSRExeReturnLblFromOnSSRExeCastleBattleMessageZantetsuken
	}
}
#pragma warning(default: 4733) // ワーニングの抑制を解除する



char cmdOnSSRExeJumpFromCastleBattleMessageZantetsuken[6] = "\xE9";
// 元の命令が5バイト、以後の関数で生まれる命令が合計５バイトなので… 最後１つ使わない


// ニーモニック書き換え用
void WriteAsmJumperOnSSRExeCastleBattleMessageZantetsuken() {

	// まずアドレスを数字として扱う
	int iAddress = (int)OnSSRExeCastleBattleMessageZantetsuken;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeCastleBattleMessageZantetsuken + 5);
	// ５というのは、0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  の命令に必要なバイト数。要するに５バイト足すと次のニーモニック命令群に移動するのだ。そしてそこからの差分がジャンプする際の目的格として利用される。
	memcpy(cmdOnSSRExeJumpFromCastleBattleMessageZantetsuken + 1, &SubAddress, 4); // +1 はE9の次から4バイト分書き換えるから。

	// 構築したニーモニック命令をTENSHOU.EXEのメモリに書き換える
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeCastleBattleMessageZantetsuken), cmdOnSSRExeJumpFromCastleBattleMessageZantetsuken, 5, NULL); //5バイトのみ書き込む
}

#pragma managed
