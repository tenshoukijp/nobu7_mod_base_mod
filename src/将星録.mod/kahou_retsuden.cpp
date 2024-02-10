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
#include "mng_�ƕ��.h"
#include "usr_custom_mod.h"

using namespace std;
using namespace �����^;

extern void replaceMessage(string message);


std::pair<string, string> getAlbedoKahouRetsuden(int iBushouID);


std::pair<string, string> getOverrideKahouRetsuden(int iKahouID) {
	if (isValidBushouID(iKahouID)) {
		auto [title, detail] = getAlbedoKahouRetsuden(iKahouID);
		if (title != "" || detail != "") {
			return { title, detail };
		}

		// C#�ɂ��I�[�o�[���C�h
		try {
			System::Collections::Generic::Dictionary<System::String^, System::Object^>^ dic = gcnew System::Collections::Generic::Dictionary<System::String^, System::Object^>(5);
			dic->Add("�ƕ�ԍ�", iKahouID);
			System::Collections::Generic::Dictionary<System::String^, System::Object^>^ ret = InvokeUserMethod("on�ƕ��`�v����", dic);

			string title = "";
			string detail = "";
			if (ret != nullptr && ret->ContainsKey("���x��")) {
				System::String^ mng_title = (System::String^)(ret["���x��"]);
				if (System::String::IsNullOrEmpty(mng_title)) {
					title = "";
				}
				else {
					title = to_native_string(mng_title);
				}
			}
			if (ret != nullptr && ret->ContainsKey("�ڍ�")) {
				System::String^ mng_detail = (System::String^)(ret["�ڍ�"]);
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

