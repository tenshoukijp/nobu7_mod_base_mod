#include <windows.h>
#include <string>
#include <vector>

#include "data_game_struct.h"
#include "output_debug_stream.h"
#include "usr_custom_mod.h"

using namespace std;
using namespace 将星録;

extern void replaceMessage(string message);


std::pair<string, string> getAlbedoCastleRetsuden(int iBushouID);


std::pair<string, string> getOverrideCastleRetsuden(int iCastleID) {
	if (isValidCastleID(iCastleID)) {
		auto [title, detail] = getAlbedoCastleRetsuden(iCastleID);
		if (title != "" || detail != "") {
			return { title, detail };
		}

		// C#によるオーバーライド
		try {
			System::Collections::Generic::Dictionary<System::String^, System::Object^>^ dic = gcnew System::Collections::Generic::Dictionary<System::String^, System::Object^>(5);
			dic->Add("城番号", iCastleID);
			System::Collections::Generic::Dictionary<System::String^, System::Object^>^ ret = InvokeUserMethod("on城列伝要求時", dic);

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
		catch (System::Exception^) {

		}

	}

	return { "","" };
}

