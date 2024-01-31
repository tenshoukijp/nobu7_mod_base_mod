/*
UŒ‚‘¤‚Ì‘å–¼ƒ|ƒCƒ“ƒ^‚â‘•º”‚ÌWŒv
00407960  /$ 51             PUSH ECX                                 ;  Nobunaga.00540F28
00407961  |. 53             PUSH EBX
00407962  |. 56             PUSH ESI
00407963  |. 57             PUSH EDI
00407964  |. 33DB           XOR EBX,EBX
00407966  |. 33F6           XOR ESI,ESI
00407968  |. 8DB9 A8000000  LEA EDI,DWORD PTR DS:[ECX+A8]
0040796E  |. 8BFF           MOV EDI,EDI
00407970  |> 56             /PUSH ESI
00407971  |. 8D4424 10      |LEA EAX,DWORD PTR SS:[ESP+10]
00407975  |. 50             |PUSH EAX
00407976  |. 8BCF           |MOV ECX,EDI
00407978  |. E8 23DAFFFF    |CALL Nobunaga.004053A0
0040797D  |. 8B4C24 0C      |MOV ECX,DWORD PTR SS:[ESP+C]             // ‚±‚Ì‚ÌECX‚ªAŠY“–‚Ì•”‘àî•ñ‚ÌˆÊ’uB‚»‚±‚©‚ç50ƒoƒCƒg•ª‚ğ•”‘àî•ñ‚Æ‚µ‚ÄT‚¦‚Ä‚¨‚­
00407981  |. 3B0D 30925300  |CMP ECX,DWORD PTR DS:[539230]           ;  Nobunaga.005695C4
00407987  |. 74 07          |JE SHORT Nobunaga.00407990
00407989  |. E8 02B1FFFF    |CALL Nobunaga.00402A90
0040798E  |. 03D8           |ADD EBX,EAX                               // ŠY“–‚Ì•”‘à‚Ì•º”
00407990  |> 83C6 01        |ADD ESI,1                                 // ESI‚ÍƒJƒEƒ“ƒ^B0-0x19
00407993  |. 83FE 19        |CMP ESI,19                                // 25•”‘à‚É‚È‚Á‚½‚çI—¹
00407996  |.^7C D8          \JL SHORT Nobunaga.00407970
00407998  |. 5F             POP EDI
00407999  |. 5E             POP ESI
0040799A  |. 8BC3           MOV EAX,EBX
0040799C  |. 5B             POP EBX
0040799D  |. 59             POP ECX
0040799E  \. C3             RETN

*/

/*
005401A0  [01 00 00 00 19 00 00 00 84 03 00 00 84 03 00 00  ......E..E..
005401B0  00 00 00 00 84 03 00 00 C8 0F 5F 00 00 00 00 00  ....E..È_.....
005401C0  94 01 00 00 D4 01 00 00 48 3C 56 00 00 90 53 00  E..Ô..H<V..S.
005401D0  A8 01] [02 00 00 00 19 00 00 00 84 03 00 00 84 03  ¨......E..E
005401E0  00 00 00 00 00 00 84 03 00 00 C8 0F 5F 00 01 00  ......E..È_..
005401F0  00 00 BC 01 00 00 C0 01 00 00 48 3C 56 00 00 90  ..¼..À..H<V..E
00540200  53 00 08 00] [03 00 00 00 19 00 00 00 84 03 00 00  S........E..
00540210  84 03 00 00 00 00 00 00 84 03 00 00 C8 0F 5F 00  E......E..È_.
00540220  02 00 00 00 E4 01 00 00 AC 01 00 00 48 3C 56 00  ...E..¬..H<V.
00540230  00 90 53 00 08 00] [04 00 00 00 19 00 00 00 84 03  .S........E
00540240  00 00 84 03 00 00 00 00 00 00 84 03 00 00 C8 0F  ..E......E..È
00540250  5F 00 03 00 00 00 E4 01 00 00 D4 01 00 00 48 3C  _....E..Ô..H<
00540260  56 00 00 90 53 00 08 00] [05 00 00 00 19 00 00 00  V..S........
00540270  84 03 00 00 84 03 00 00 00 00 00 00 84 03 00 00  E..E......E..
00540280  C8 0F 5F 00 04 00 00 00 0C 02 00 00 98 01 00 00  È_.......E..
00540290  48 3C 56 00 00 90 53 00 00 00]                     H<V..S...
ˆÈ~A‚U` ‚àB‘S‘Ì‚ÅÅ‘å‚Å‚à20•”‘à‚Æv‚í‚ê‚éB(‚P•«‚T•”‘à‚ÅAÅ‘å‚Å‚à‚S•«B‚È‚Ì‚Å5x4=20)
*/

#include <windows.h>
#include <string>
#include <vector>
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
#include "castle_battle_attack_heisuu_sum.h"


std::vector<âÄéíUŒ‚‘¤•”‘àî•ñ> listUŒ‚‘¤•”‘àî•ñ;


using namespace std;


#pragma unmanaged

static int ECXOfCastleBattleAttackHeisuuSum = -1; // •”‘àî•ñ‚Ö‚Ìƒ|ƒCƒ“ƒ^B•”‘àî•ñ‚Íã‚Ìstruct‚Ì50ƒoƒCƒg\¬
static int ESIOfCastleBattleAttackHeisuuSum = -1; // ‰½”Ô–Ú‚Ì•”‘à‚È‚Ì‚©B0-25
void OnSSRExeCastleBattleAttackHeisuuSumExecute() {

	int index = ESIOfCastleBattleAttackHeisuuSum;

	// index‚ª0‚Ì‚ÍA•”‘àî•ñ‚ğ‘S•”‰Šú‰»‚·‚é
	if (index == 0) {
		listUŒ‚‘¤•”‘àî•ñ.clear();
		for (int i = 0; i < 0x19; i++) { // 0x19=25
			âÄéíUŒ‚‘¤•”‘àî•ñ info;
			ZeroMemory(&info, sizeof(info));
			listUŒ‚‘¤•”‘àî•ñ.push_back(info);
		}
	}

	if (index < (int)listUŒ‚‘¤•”‘àî•ñ.size()) {
		âÄéíUŒ‚‘¤•”‘àî•ñ* p•”‘àî•ñ = (âÄéíUŒ‚‘¤•”‘àî•ñ*)ECXOfCastleBattleAttackHeisuuSum;
		int differ = memcmp(&listUŒ‚‘¤•”‘àî•ñ[index], p•”‘àî•ñ, sizeof(âÄéíUŒ‚‘¤•”‘àî•ñ));
		if (differ) {
			listUŒ‚‘¤•”‘àî•ñ[index] = *p•”‘àî•ñ; // •”‘àî•ñ‚ğ‚P‚ÂƒRƒs[B
			int iBushouID = getBushouIDFromBushouPtr((int*)listUŒ‚‘¤•”‘àî•ñ[index].pwŠö•«);
			if (isValidBushouID(iBushouID) && listUŒ‚‘¤•”‘àî•ñ[index].•º” > 0 && listUŒ‚‘¤•”‘àî•ñ[index].•”‘à”Ô† > 0) {
				OutputDebugStream("wŠöŠ¯" + getBushou©–¼FromBushouID(iBushouID) + "\n");
				OutputDebugStream("•”‘à”Ô† %d\n", listUŒ‚‘¤•”‘àî•ñ[index].•”‘à”Ô†);
				OutputDebugStream("•”‘à•º” %d\n", listUŒ‚‘¤•”‘àî•ñ[index].•º”);
			}
		}
	}

}

/*
00407976  |. 8BCF           |MOV ECX,EDI
00407978  |. E8 23DAFFFF    |CALL Nobunaga.004053A0
0040797D  |. 8B4C24 0C      |MOV ECX,DWORD PTR SS:[ESP+C]             // ‚±‚Ì‚ÌECX‚ªAŠY“–‚Ì•”‘àî•ñ‚ÌˆÊ’uB‚»‚±‚©‚ç50ƒoƒCƒg•ª‚ğ•”‘àî•ñ‚Æ‚µ‚ÄT‚¦‚Ä‚¨‚­
00407981  |. 3B0D 30925300  |CMP ECX,DWORD PTR DS:[539230]           ;  Nobunaga.005695C4
00407987  |. 74 07          |JE SHORT Nobunaga.00407990
00407989  |. E8 02B1FFFF    |CALL Nobunaga.00402A90
0040798E  |. 03D8           |ADD EBX,EAX                               // ŠY“–‚Ì•”‘à‚Ì•º”
00407990  |> 83C6 01        |ADD ESI,1                                 // ESI‚ÍƒJƒEƒ“ƒ^B0-19
00407993  |. 83FE 19        |CMP ESI,19                                // 20•”‘à‚É‚È‚Á‚½‚çI—¹
*/


int pSSRExeJumpFromToOnSSRExeCastleBattleAttackHeisuuSum = 0x407978; // ŠÖ”‚Í‚±‚ÌƒAƒhƒŒƒX‚©‚çAOnSSRExeCastleBattleAttackHeisuuSum‚Ö‚ÆƒWƒƒƒ“ƒv‚µ‚Ä‚­‚éB
int pSSRExeJumpCallFromToOnSSRExeCastleBattleAttackHeisuuSum = 0x4053A0; // Œ³X‚ ‚Á‚½ˆ—‚ÌCallæ
int pSSRExeReturnLblFromOnSSRExeCastleBattleAttackHeisuuSum = 0x40797D; // ŠÖ”‚ªÅŒã‚Ü‚Å‚¢‚­‚ÆA‚±‚ÌTENSHOU.EXE“à‚É’¼ÚƒWƒƒƒ“ƒv‚·‚é

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeCastleBattleAttackHeisuuSum() {
	// ƒXƒ^ƒbƒN‚É‚½‚ß‚Ä‚¨‚­
	__asm {

		call pSSRExeJumpCallFromToOnSSRExeCastleBattleAttackHeisuuSum // Œ³‚Ìˆ—

		MOV ECX, DWORD PTR SS : [ESP + 0xC] // Œ³‚Ìˆ—‚Æ“¯‚¶‚à‚Ì

		MOV ESIOfCastleBattleAttackHeisuuSum, ESI // ƒJƒEƒ“ƒ^‚ª“ü‚Á‚Ä‚¢‚é

		MOV ECXOfCastleBattleAttackHeisuuSum, ECX // ECX‚É‚Í•”‘àî•ñ‚Ö‚Ìƒ|ƒCƒ“ƒ^‚ª“ü‚Á‚Ä‚¢‚é

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeCastleBattleAttackHeisuuSumExecute();

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

		jmp pSSRExeReturnLblFromOnSSRExeCastleBattleAttackHeisuuSum
	}
}
#pragma warning(default: 4733) // ƒ[ƒjƒ“ƒO‚Ì—}§‚ğ‰ğœ‚·‚é



char cmdOnSSRExeJumpFromCastleBattleAttackHeisuuSum[6] = "\xE9";
// Œ³‚Ì–½—ß‚ª5ƒoƒCƒgAˆÈŒã‚ÌŠÖ”‚Å¶‚Ü‚ê‚é–½—ß‚ª‡Œv‚TƒoƒCƒg‚È‚Ì‚Åc ÅŒã‚P‚Âg‚í‚È‚¢


// ƒj[ƒ‚ƒjƒbƒN‘‚«Š·‚¦—p
void WriteAsmJumperOnSSRExeCastleBattleAttackHeisuuSum() {

	// ‚Ü‚¸ƒAƒhƒŒƒX‚ğ”š‚Æ‚µ‚Äˆµ‚¤
	int iAddress = (int)OnSSRExeCastleBattleAttackHeisuuSum;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeCastleBattleAttackHeisuuSum + 5);
	// ‚T‚Æ‚¢‚¤‚Ì‚ÍA0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  ‚Ì–½—ß‚É•K—v‚ÈƒoƒCƒg”B—v‚·‚é‚É‚TƒoƒCƒg‘«‚·‚ÆŸ‚Ìƒj[ƒ‚ƒjƒbƒN–½—ßŒQ‚ÉˆÚ“®‚·‚é‚Ì‚¾B‚»‚µ‚Ä‚»‚±‚©‚ç‚Ì·•ª‚ªƒWƒƒƒ“ƒv‚·‚éÛ‚Ì–Ú“IŠi‚Æ‚µ‚Ä—˜—p‚³‚ê‚éB
	memcpy(cmdOnSSRExeJumpFromCastleBattleAttackHeisuuSum + 1, &SubAddress, 4); // +1 ‚ÍE9‚ÌŸ‚©‚ç4ƒoƒCƒg•ª‘‚«Š·‚¦‚é‚©‚çB

	// \’z‚µ‚½ƒj[ƒ‚ƒjƒbƒN–½—ß‚ğTENSHOU.EXE‚Ìƒƒ‚ƒŠ‚É‘‚«Š·‚¦‚é
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeCastleBattleAttackHeisuuSum), cmdOnSSRExeJumpFromCastleBattleAttackHeisuuSum, 5, NULL); //5ƒoƒCƒg‚Ì‚İ‘‚«‚Ş
}

#pragma managed
