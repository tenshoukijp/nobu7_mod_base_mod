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
#include "file_attribute.h"

using namespace std;

#pragma unmanaged


/*
ƒ€[ƒr[ƒtƒ@ƒCƒ‹–¼‚Ìƒ|ƒCƒ“ƒ^”z—ñ‚ğQÆ‚µ‚Ä‚¢‚é‚Æ‚±‚ë
00419AF9   77 07            JA SHORT Nobunaga.00419B02
00419AFB   8B048D 2C855300  MOV EAX,DWORD PTR DS:[ECX*4+53852C]
00419B02   C3               RETN
00419B03   CC               INT3
00419B04   CC               INT3


ƒ€[ƒr[ƒtƒ@ƒCƒ‹ŒQ‚Ö‚Ìƒ|ƒCƒ“ƒ^‚Ì”z—ñ
00538520  00 00 00 00 00 00 00 00 00 00 00 00 3C 10 52 00  ............<R.
00538530  28 10 52 00 14 10 52 00 00 10 52 00 EC 0F 52 00  (R.R..R.ER.
00538540  D8 0F 52 00 C4 0F 52 00 B0 0F 52 00 9C 0F 52 00  ØR.ÄR.°R.ER.
00538550  88 0F 52 00 08 9A 52 00 00 00 00 00              ER.šR......?



ƒ€[ƒr[‚Ìƒtƒ@ƒCƒ‹ŒQ‚Ì”z—ñ
00520F88  4D 6F 76 69 65 5C 45 6E 64 69 6E 67 2E 61 76 69  Movie\Ending.avi
00520F98  00 00 00 00 4D 6F 76 69 65 5C 4F 70 65 6E 69 6E  ....Movie\Openin
00520FA8  67 2E 61 76 69 00 00 00 4D 6F 76 69 65 5C 54 65  g.avi...Movie\Te
00520FB8  70 70 6F 75 2E 61 76 69 00 00 00 00 4D 6F 76 69  ppou.avi....Movi
00520FC8  65 5C 43 68 72 69 73 74 2E 61 76 69 00 00 00 00  e\Christ.avi....
00520FD8  4D 6F 76 69 65 5C 53 61 6E 73 68 69 2E 61 76 69  Movie\Sanshi.avi
00520FE8  00 00 00 00 4D 6F 76 69 65 5C 4B 61 69 6D 65 69  ....Movie\Kaimei
00520FF8  2E 61 76 69 00 00 00 00 4D 6F 76 69 65 5C 4B 69  .avi....Movie\Ki
00521008  79 6F 73 75 2E 61 76 69 00 00 00 00 4D 6F 76 69  yosu.avi....Movi
00521018  65 5C 48 41 66 74 65 72 32 2E 61 76 69 00 00 00  e\HAfter2.avi...
00521028  4D 6F 76 69 65 5C 48 41 66 74 65 72 31 2E 61 76  Movie\HAfter1.av
00521038  69 00 00 00 4D 6F 76 69 65 5C 48 6F 6E 6E 6F 75  i...Movie\Honnou
00521048  6A 69 2E 61 76 69                                ji.avi
*/


int iMovieFileNameCharPointer = NULL;

char bufOverrideMovieName[512] = "";

void OnSSRExeMovieFileNameExecute() {
	OutputDebugStream("ƒ€[ƒr[ƒtƒ@ƒCƒ‹–¼‚Ìæ“¾:");
	OutputDebugStream("’l %x\n", iMovieFileNameCharPointer);
	OutputDebugStream("’l %s\n", iMovieFileNameCharPointer);

	if (iMovieFileNameCharPointer != NULL) {
		string overrideMovieName = string("OVERRIDE\\") + string((char*)iMovieFileNameCharPointer);
		if (isFileExists(overrideMovieName)) {
			OutputDebugStream("ƒI[ƒo[ƒ‰ƒCƒhƒtƒ@ƒCƒ‹‚ª‘¶İ‚·‚é‚Ì‚ÅA‚»‚ê‚ğg‚¤\n");
			strcpy_s(bufOverrideMovieName, overrideMovieName.c_str());
			iMovieFileNameCharPointer = (int)bufOverrideMovieName;
		}
	}
}


/*
00419AF9   77 07            JA SHORT Nobunaga.00419B02
00419AFB   8B048D 2C855300  MOV EAX,DWORD PTR DS:[ECX*4+53852C]
00419B02   C3               RETN
*/

int pSSRExeJumpFromToOnSSRExeMovieFileName = 0x419AFB; // ŠÖ”‚Í‚±‚ÌƒAƒhƒŒƒX‚©‚çAOnSSRExeMovieFileName‚Ö‚ÆƒWƒƒƒ“ƒv‚µ‚Ä‚­‚éB
int pSSRExeReturnLblFromOnSSRExeMovieFileName = 0x419B02; // ŠÖ”‚ªÅŒã‚Ü‚Å‚¢‚­‚ÆA‚±‚ÌTENSHOU.EXE“à‚É’¼ÚƒWƒƒƒ“ƒv‚·‚é

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeMovieFileName() {
	// ƒXƒ^ƒbƒN‚É‚½‚ß‚Ä‚¨‚­
	__asm {
		MOV EAX, DWORD PTR DS : [ECX*4 + 0x53852C] // Œ³X‚Ìˆ—‚ğ‚±‚±‚É
		mov iMovieFileNameCharPointer, EAX // ƒtƒ@ƒCƒ‹–¼‚Ö‚Ìƒ|ƒCƒ“ƒ^‚ğ•Û‘¶‚µ‚Ä‚¨‚­
		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeMovieFileNameExecute();

	// ƒXƒ^ƒbƒN‚Éˆø‚«o‚·
	__asm {
		pop edi
		pop esi
		pop ebp
		pop esp
		pop edx
		pop ecx
		pop ebx
		pop eax

		MOV EAX, iMovieFileNameCharPointer; // ƒtƒ@ƒCƒ‹ƒ|ƒCƒ“ƒ^‚ğã‘‚«‚µ‚Ä‚¢‚é‚©‚à‚µ‚ê‚È‚¢‚Ì‚ÅEAX‚É“]Ê(ã‘‚«‚µ‚Ä‚È‚¯‚ê‚ÎŒ³XEAX‚Æ“¯‚¶’l‚ª“ü‚Á‚Ä‚¢‚é)

		jmp pSSRExeReturnLblFromOnSSRExeMovieFileName
	}
}
#pragma warning(default: 4733) // ƒ[ƒjƒ“ƒO‚Ì—}§‚ğ‰ğœ‚·‚é



char cmdOnSSRExeJumpFromMovieFileName[8] = "\xE9\x90\x90\x90\x90\x90\x90";
// Œ³‚Ì–½—ß‚ª5ƒoƒCƒgAˆÈŒã‚ÌŠÖ”‚Å¶‚Ü‚ê‚é–½—ß‚ª‡Œv‚TƒoƒCƒg‚È‚Ì‚Åc ÅŒã‚P‚Âg‚í‚È‚¢


// ƒj[ƒ‚ƒjƒbƒN‘‚«Š·‚¦—p
void WriteAsmJumperOnSSRExeMovieFileName() {

	// ‚Ü‚¸ƒAƒhƒŒƒX‚ğ”š‚Æ‚µ‚Äˆµ‚¤
	int iAddress = (int)OnSSRExeMovieFileName;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeMovieFileName + 5);
	// ‚T‚Æ‚¢‚¤‚Ì‚ÍA0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  ‚Ì–½—ß‚É•K—v‚ÈƒoƒCƒg”B—v‚·‚é‚É‚TƒoƒCƒg‘«‚·‚ÆŸ‚Ìƒj[ƒ‚ƒjƒbƒN–½—ßŒQ‚ÉˆÚ“®‚·‚é‚Ì‚¾B‚»‚µ‚Ä‚»‚±‚©‚ç‚Ì·•ª‚ªƒWƒƒƒ“ƒv‚·‚éÛ‚Ì–Ú“IŠi‚Æ‚µ‚Ä—˜—p‚³‚ê‚éB
	memcpy(cmdOnSSRExeJumpFromMovieFileName + 1, &SubAddress, 4); // +1 ‚ÍE9‚ÌŸ‚©‚ç4ƒoƒCƒg•ª‘‚«Š·‚¦‚é‚©‚çB

	// \’z‚µ‚½ƒj[ƒ‚ƒjƒbƒN–½—ß‚ğTENSHOU.EXE‚Ìƒƒ‚ƒŠ‚É‘‚«Š·‚¦‚é
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeMovieFileName), cmdOnSSRExeJumpFromMovieFileName, 7, NULL);
	//7ƒoƒCƒg‚Ì‚İ‘‚«‚Ş
	// 00419AFB   8B048D 2C855300  MOV EAX,DWORD PTR DS:[ECX*4+53852C]@‚ª 7ƒoƒCƒg‚ ‚é‚Ì‚ÅãY—í‚É‘‚«Š·‚¦‚Ä‚¨‚­
}

#pragma managed
