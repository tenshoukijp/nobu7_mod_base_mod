#include <windows.h>
#include <string>

#include "data_game_struct.h"
#include "output_debug_stream.h"
#include "game_screen.h"
#include "on_serihu_message.h"
#include "bushou_albedo.h"
#include "game_screen.h"
#include "onigwrap.h"
#include "usr_custom_mod.h"

using namespace std;
using namespace 列挙;
/*
メモリの呼び出し元、その①
00496D8B   E8 80B20600      CALL Nobunaga.00502010
00496D90   83C4 0C          ADD ESP, 0C
00496D93   8B45 08          MOV EAX, DWORD PTR SS : [EBP + 8]
00496D96   E8 05F1FFFF      CALL Nobunaga.00495EA0
00496D9B   BE 01000000      MOV ESI, 1
00496DA0   66:891D 4C985D00 MOV WORD PTR DS : [5D984C] , BX
00496DA7   C705 88985D00 38 > MOV DWORD PTR DS : [5D9888] , Nobunaga.005D9 > ; ASCII "ただいまデータをロードしています"
00496DB1   891D 44985D00    MOV DWORD PTR DS : [5D9844] , EBX
00496DB7   891D 48985D00    MOV DWORD PTR DS : [5D9848] , EBX
00496DBD   891D 50985D00    MOV DWORD PTR DS : [5D9850] , EBX
00496DC3   66:C705 38975D00 > MOV WORD PTR DS : [5D9738] , 0FFFF
00496DCC   66:8935 38985D00 MOV WORD PTR DS : [5D9838] , SI
00496DD3   B9 80E95700      MOV ECX, Nobunaga.0057E980
00496DD8   E8 6357FCFF      CALL Nobunaga.0045C540
00496DDD   8B08             MOV ECX, DWORD PTR DS : [EAX]
00496DDF   894D DC          MOV DWORD PTR SS : [EBP - 24] , ECX
00496DE2   8B50 04          MOV EDX, DWORD PTR DS : [EAX + 4]
00496DE5   8955 E0          MOV DWORD PTR SS : [EBP - 20] , EDX
00496DE8   8B48 08          MOV ECX, DWORD PTR DS : [EAX + 8]
00496DEB   894D E4          MOV DWORD PTR SS : [EBP - 1C] , ECX
00496DEE   8B50 0C          MOV EDX, DWORD PTR DS : [EAX + C]
00496DF1   8955 E8          MOV DWORD PTR SS : [EBP - 18] , EDX
00496DF4   0FB740 10        MOVZX EAX, WORD PTR DS : [EAX + 10]
00496DF8   66:8945 EC       MOV WORD PTR SS : [EBP - 14] , AX
00496DFC   66:A1 40985D00   MOV AX, WORD PTR DS : [5D9840]
00496E02   0FB7C8           MOVZX ECX, AX
*/

extern void replaceMessage(string message);
extern void checkReplaceBushouSerifuMessage();

BOOL isNextMessageIsRekishiBushouRetsuden = FALSE;
BOOL isNextMessageIsRekishiHimeRetsuden = FALSE;
BOOL isNextMessageIsKasouHimeRetsuden = FALSE;

/*
005D9638  0の娘。父の要請を受けて一軍の将となる。父親譲りの智謀と武勇を兼ね備える
005D967F  。.I択してください...........
*/

std::pair<string, string> getAlbedoRetsuden(int iBushouID);

std::pair<string, string> getOverrideBushouRetsuden(int iBushouID) {
	if (isValidBushouID(iBushouID)) {
		// アルベドならアルベド列伝
		if (nb7武将情報[iBushouID].姓名 == getArubedoSeiMei()) {
			auto [title, detail] = getAlbedoRetsuden(iBushouID);
			if (title != "" || detail != "") {
				return { title, detail };
			}
		}
		else {

			// C#によるオーバーライド
			try {
				System::Collections::Generic::Dictionary<System::String^, System::Object^>^ dic = gcnew System::Collections::Generic::Dictionary<System::String^, System::Object^>(5);
				dic->Add("武将番号", iBushouID);
				System::Collections::Generic::Dictionary<System::String^, System::Object^>^ ret = InvokeUserMethod("on武将列伝要求時", dic);

				string title = "";
				string detail = "";
				if (ret != nullptr && ret->ContainsKey("ラベル")) {
					System::String^ mng_title = (System::String^)(ret["ラベル"]);
					if (System::String::IsNullOrEmpty(mng_title)) {
						title = "";
					}
					else {
						title = to_native_string(mng_title);
					}
				}
				if (ret != nullptr && ret->ContainsKey("詳細")) {
					System::String^ mng_detail = (System::String^)(ret["詳細"]);
					if (System::String::IsNullOrEmpty(mng_detail)) {
						detail = "";
					}
					else {
						detail = to_native_string(mng_detail);
					}
				}
				if (title != "" || detail != "") {
					return { title, detail };
				}

			}
			catch (System::Exception^ ) {

			}

		}
	}

	return { "","" };
}

void checkReplaceBushouRetsuden() {

	// 列伝の詳細の置き換えが立っていれば、詳細を置き換える
	if (isNextMessageIsRekishiBushouRetsuden) {
		isNextMessageIsRekishiBushouRetsuden = FALSE;
		int iRetsudenBushouID = getRetsudenBushouID();
		if (isValidBushouID(iRetsudenBushouID)) {
			auto [title, detail] = getOverrideBushouRetsuden(iRetsudenBushouID);
			if (detail.size() > 0) {
				replaceMessage(detail);
			}
		}
	}
	// 列伝の詳細の置き換えが立っていれば、詳細を置き換える
	if (isNextMessageIsRekishiHimeRetsuden) {
		isNextMessageIsRekishiHimeRetsuden = FALSE;
		int iRetsudenBushouID = getRetsudenBushouID();
		if (isValidBushouID(iRetsudenBushouID)) {
			auto [title, detail] = getOverrideBushouRetsuden(iRetsudenBushouID);
			if (detail.size() > 0) {
				replaceMessage(detail);
			}
		}
	}
	// 列伝の詳細の置き換えが立っていれば、詳細を置き換える
	if (isNextMessageIsKasouHimeRetsuden) {
		isNextMessageIsKasouHimeRetsuden = FALSE;
		int iRetsudenBushouID = getRetsudenBushouID();
		if (isValidBushouID(iRetsudenBushouID)) {
			auto [title, detail] = getOverrideBushouRetsuden(iRetsudenBushouID);
			if (detail.size() > 0) {
				replaceMessage(detail);
			}
		}
	}

	int status = getゲーム画面ステータス();
	if (status == ゲーム画面ステータス::戦略画面 || status == ゲーム画面ステータス::野戦画面 || status == ゲーム画面ステータス::籠城戦画面) {
		checkReplaceBushouSerifuMessage();

		int iRetsudenBushouID = getRetsudenBushouID();
		if (isValidBushouID(iRetsudenBushouID)) {
			OutputDebugStream("メッセージ段階でチェックしているiRetsudenBushouIDは%d\n", iRetsudenBushouID);
			// 通常の武将は 「姓名 ﾖﾐ ????～????」のフォーマットを取る 
			if (0 <= iRetsudenBushouID && iRetsudenBushouID < 700) {
				string message = (char*)(セリフメッセージアドレス); // on_serihu_message
				Matches ma;
				if (OnigMatch(message, "^(.+?) (.+?) [0-9\\?]{4}～[0-9\\?]{4}$", &ma)) {
					// 0～699番の通常の武将達は、姓名がそろっている
					// 次にメッセージ部分が来たら、列伝の詳細を置き換える
					isNextMessageIsRekishiBushouRetsuden = true;
					// 列伝用のタイトル部分を置き換える
					auto [title, detail] = getOverrideBushouRetsuden(iRetsudenBushouID);
					if (title.size() > 0) {
						replaceMessage(title);
					}
				}
			}
			// 歴史姫は、「名 ﾖﾐ ????～????」のフォーマットを取る
			else if (700 <= iRetsudenBushouID && iRetsudenBushouID < 716) {
				string message = (char*)(セリフメッセージアドレス); // on_serihu_message
				Matches ma;
				if (OnigMatch(message, "^(.+?) (.+?) [0-9\\?]{4}～[0-9\\?]{4}$", &ma)) {
					// 次にメッセージ部分が来たら、列伝の詳細を置き換える
					isNextMessageIsRekishiHimeRetsuden = true;
					// 列伝用のタイトル部分を置き換える
					auto [title, detail] = getOverrideBushouRetsuden(iRetsudenBushouID);
					if (title.size() > 0) {
						replaceMessage(title);
					}
				}
			}
			// 仮想姫は、「名 ????～????」のフォーマットを取る
			else if (716 <= iRetsudenBushouID && iRetsudenBushouID < 732) {
				string message = (char*)(セリフメッセージアドレス); // on_serihu_message
				Matches ma;
				if (OnigMatch(message, "^(.+?) [0-9\\?]{4}～[0-9\\?]{4}$", &ma)) {
					// 次にメッセージ部分が来たら、列伝の詳細を置き換える
					isNextMessageIsKasouHimeRetsuden = true;
					// 列伝用のタイトル部分を置き換える
					auto [title, detail] = getOverrideBushouRetsuden(iRetsudenBushouID);
					if (title.size() > 0) {
						replaceMessage(title);
					}
				}
			}
		}

	}
}

