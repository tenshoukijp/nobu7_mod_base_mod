#include <windows.h>
#include <string>

#include "data_game_struct.h"
#include "output_debug_stream.h"
#include "onigwrap.h"
#include "hook_textouta_custom.h"
#include "bushou_albedo.h"
#include "on_serihu_message.h"
#include "hook_textouta_custom.h"

using namespace std;



// �t�b�N����֐��̃v���g�^�C�v���`
using PFNTEXTOUTA = BOOL(WINAPI*)(HDC, int, int, LPCTSTR, int);
extern PROC pfnOrigTextOutA;





