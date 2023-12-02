

// ‚±‚Ìƒtƒ@ƒCƒ‹‚Í”÷–­‚ÉŠO‚ê‚Ä‚¢‚éH ‚Å‚àd—v‚Èî•ñ‚ª‚ ‚é‚æ‚¤‚É‚àv‚¦‚é
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


using namespace std;

#pragma unmanaged

/*
‘å–¼ƒ^[ƒ“‚Ìî•ñ‚ª‚ ‚é‚©‚à‚µ‚ê‚È‚¢êŠ
00569280  28 00 00 00 78 00 00 00 14 00 00 00 64 00 00 00  (...x......d...
00569290  00 00 00 00 00 00 00 00 A0 00 00 00 A0 00 00 00  ........ ... ...
005692A0  [26 AB 56] 00 16 00 00 00 40 00 00 00 01 00 00 00  &«V....@......
005692B0  00 00 00 00 [26 AB 56] 00 58 27 CE 07 01 00 00 00  ....&«V.X'Î...
005692C0  16 00 00 00 E8 6F D4 07 40 2E 00 00 7A A6 00 00  ...èoÔ@...z¦..
005692D0  B6 3F 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ¶?..............
005692E0  8C 5B 00 00 DA 1D 00 00 00 00 00 00 00 00 00 00  Œ[..Ú..........

0057EA74  78 A1 CE 07 01 00 00 00 [26 AB 56] 00 B8 8E 53 00  x¡Î...&«V.¸S. ƒAƒhƒŒƒX0x57EA7C = ‚±‚±‚Ì[ ] ‚ª‘å–¼ƒ^[ƒ“‚Ì‘å–¼ƒAƒhƒŒƒX‚Ö‚Ì’¼Ú‚Ìƒ|ƒCƒ“ƒ^ [B8 8E 53 00] ‚¾‚ÆA’N‚àƒ^[ƒ“—ˆ‚Ä‚È‚¢B
0057EA84  [26 AB 56] 00 B8 8E 53 00 B8 8E 53 00 B8 8E 53 00  &«V.¸S.¸S.¸S.
0057EA94  B8 8E 53 00 B8 8E 53 00 B8 8E 53 00 B8 8E 53 00  ¸S.¸S.¸S.¸S.
0057EAA4  05 00 00 00 05 00 00 00 00 00 00 00 FF FF 00 00  ..........ÿÿ..
*/#pragma once

/*
‚±‚Ì0x57EA7C‚Ö‚Æ‘ã“ü‚µ‚Ä‚¢‚é‰ÓŠ‚Í‚½‚¾‚P‚ÂB
004C4F7A   8B15 F8915300    MOV EDX,DWORD PTR DS:[5391F8]            ; Nobunaga.00538EB8
004C4F80   8915 7CEA5700    MOV DWORD PTR DS:[57EA7C],EDX
004C4F86   837C24 1C 00     CMP DWORD PTR SS:[ESP+1C],0
004C4F8B   0F85 AB000000    JNZ Nobunaga.004C503C
004C4F91   33FF             XOR EDI,EDI
004C4F93   8D6B 08          LEA EBP,DWORD PTR DS:[EBX+8]
*/

/*
‚»‚Ìã‹L‚ğŒÄ‚Ño‚µ‚Ä‚¢‚éŠÖ”‚Í‚½‚Á‚½‚P‚Â
0045F58B   B9 F0BF5E00      MOV ECX,Nobunaga.005EBFF0
0045F590   E8 5B590600      CALL Nobunaga.004C4EF0
0045F595   8B4C24 14        MOV ECX,DWORD PTR SS:[ESP+14]
0045F599   8D8424 44450000  LEA EAX,DWORD PTR SS:[ESP+4544]
0045F5A0   50               PUSH EAX
*/



void OnSSRExeDaimyoTurnExecute() {
	OutputDebugStream("‘å–¼ƒ^[ƒ“—ˆ‚½‚æ‘Oš\n");
}

/*
‚±‚Ì0x57EA7C‚Ö‚Æ‘ã“ü‚µ‚Ä‚¢‚é‰ÓŠ‚Í‚½‚¾‚P‚ÂB
004C4F7A   8B15 F8915300    MOV EDX,DWORD PTR DS:[5391F8]            ; Nobunaga.00538EB8
004C4F80   8915 7CEA5700    MOV DWORD PTR DS:[57EA7C],EDX <--- ‚±‚±‚ğƒWƒƒƒ“ƒv‚Ö‚Æ‘‚«Š·‚¦‚é
004C4F86   837C24 1C 00     CMP DWORD PTR SS:[ESP+1C],0
004C4F8B   0F85 AB000000    JNZ Nobunaga.004C503C
004C4F91   33FF             XOR EDI,EDI
004C4F93   8D6B 08          LEA EBP,DWORD PTR DS:[EBX+8]
*/



int pSSRExeJumpFromToOnSSRExeDaimyoTurn = 0x4C4F80; // ŠÖ”‚Í‚±‚ÌƒAƒhƒŒƒX‚©‚çAOnSSRExeDaimyoTurn‚Ö‚ÆƒWƒƒƒ“ƒv‚µ‚Ä‚­‚éB
// int pSSRExeJumpCallFromToOnSSRExeDaimyoTurn = 0x04C4EF0; // Œ³X‚ ‚Á‚½ˆ—‚ÌCallæ
int pSSRExeReturnLblFromOnSSRExeDaimyoTurn = 0x4C4F86; // ŠÖ”‚ªÅŒã‚Ü‚Å‚¢‚­‚ÆA‚±‚ÌTENSHOU.EXE“à‚É’¼ÚƒWƒƒƒ“ƒv‚·‚é

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeDaimyoTurn() {
	// ƒXƒ^ƒbƒN‚É‚½‚ß‚Ä‚¨‚­
	__asm {

		MOV DWORD PTR DS : [0x57EA7C] , EDX

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeDaimyoTurnExecute();

	__asm {
		pop edi
		pop esi
		pop ebp
		pop esp
		pop edx
		pop ecx
		pop ebx
		pop eax

		jmp pSSRExeReturnLblFromOnSSRExeDaimyoTurn
	}
}
#pragma warning(default: 4733) // ƒ[ƒjƒ“ƒO‚Ì—}§‚ğ‰ğœ‚·‚é



char cmdOnSSRExeJumpFromDaimyoTurn[6] = "\xE9";
// Œ³‚Ì–½—ß‚ª5ƒoƒCƒgAˆÈŒã‚ÌŠÖ”‚Å¶‚Ü‚ê‚é–½—ß‚ª‡Œv‚TƒoƒCƒg‚È‚Ì‚Åc ÅŒã‚P‚Âg‚í‚È‚¢


// ƒj[ƒ‚ƒjƒbƒN‘‚«Š·‚¦—p
void WriteAsmJumperOnSSRExeDaimyoTurn() {

	// ‚Ü‚¸ƒAƒhƒŒƒX‚ğ”š‚Æ‚µ‚Äˆµ‚¤
	int iAddress = (int)OnSSRExeDaimyoTurn;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeDaimyoTurn + 5);
	// ‚T‚Æ‚¢‚¤‚Ì‚ÍA0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  ‚Ì–½—ß‚É•K—v‚ÈƒoƒCƒg”B—v‚·‚é‚É‚TƒoƒCƒg‘«‚·‚ÆŸ‚Ìƒj[ƒ‚ƒjƒbƒN–½—ßŒQ‚ÉˆÚ“®‚·‚é‚Ì‚¾B‚»‚µ‚Ä‚»‚±‚©‚ç‚Ì·•ª‚ªƒWƒƒƒ“ƒv‚·‚éÛ‚Ì–Ú“IŠi‚Æ‚µ‚Ä—˜—p‚³‚ê‚éB
	memcpy(cmdOnSSRExeJumpFromDaimyoTurn + 1, &SubAddress, 4); // +1 ‚ÍE9‚ÌŸ‚©‚ç4ƒoƒCƒg•ª‘‚«Š·‚¦‚é‚©‚çB

	// \’z‚µ‚½ƒj[ƒ‚ƒjƒbƒN–½—ß‚ğTENSHOU.EXE‚Ìƒƒ‚ƒŠ‚É‘‚«Š·‚¦‚é
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeDaimyoTurn), cmdOnSSRExeJumpFromDaimyoTurn, 5, NULL); //5ƒoƒCƒg‚Ì‚İ‘‚«‚Ş
}

#pragma managed
