#include <windows.h>
#include <string>
#include <vector>

#include "data_game_struct.h"
#include "output_debug_stream.h"
#include "game_screen.h"
#include "game_process.h"
#include "on_serihu_message.h"
#include "bushou_albedo.h"
#include "game_screen.h"
#include "message_albedo.h"
#include "onigwrap.h"
#include "mng_家宝列挙.h"
#include "usr_custom_mod.h"

using namespace std;
using namespace 将星録;

extern void replaceMessage(string message);


std::pair<string, string> getAlbedoKahouRetsuden(int iBushouID);


std::pair<string, string> getOverrideKahouRetsuden(int iKahouID) {
	if (isValidBushouID(iKahouID)) {
		auto [title, detail] = getAlbedoKahouRetsuden(iKahouID);
		if (title != "" || detail != "") {
			return { title, detail };
		}

		// C#によるオーバーライド
		try {
			System::Collections::Generic::Dictionary<System::String^, System::Object^>^ dic = gcnew System::Collections::Generic::Dictionary<System::String^, System::Object^>(5);
			dic->Add("家宝番号", iKahouID);
			System::Collections::Generic::Dictionary<System::String^, System::Object^>^ ret = InvokeUserMethod("on家宝列伝要求時", dic);

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

	return { "","" };
}

