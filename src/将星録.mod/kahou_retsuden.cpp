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
#include "mng_‰Æ•ó—ñ‹“.h"

using namespace std;
using namespace «¯˜^;

extern void replaceMessage(string message);


std::pair<string, string> getAlbedoKahouRetsuden(int iBushouID);


std::pair<string, string> getOverrideKahouRetsuden(int iKahouID) {
	if (isValidBushouID(iKahouID)) {
		auto [title, detail] = getAlbedoKahouRetsuden(iKahouID);
		if (title != "" || detail != "") {
			return { title, detail };
		}
	}

	return { "","" };
}

