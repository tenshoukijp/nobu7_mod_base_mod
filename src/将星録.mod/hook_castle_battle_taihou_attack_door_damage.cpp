/*
00415D60   8BCE             MOV ECX,ESI
00415D62   E8 99D8FEFF      CALL Nobunaga.00403600
00415D67   50               PUSH EAX                                 ‚±‚Ì‚ÌEAX‚ªUŒ‚‘¤‚ÌŒ¸­Œã‚Ì–hŒä’lBECX+0xA‚ÌƒAƒhƒŒƒX‚É EAX‚Ì’l‚Æ“¯‚¶’l‚ğ“ü‚ê‚é‚±‚ÆB
00415D68   53               PUSH EBX
00415D69   68 A80D5200      PUSH Nobunaga.00520DA8                   ; ASCII "–hŒä“x : %d ---> %d"
00415D6E   68 D8A55D00      PUSH Nobunaga.005DA5D8                   ; ASCII "242"

00540A22  06 00 00 00 07 00 00 00 01 00 00 00 B0 01 00 00  .........°..
00540A32  94 01 00 00 FF FF FF FF FF FF FF FF FF FF FF FF  E..ÿÿÿÿÿÿÿÿÿÿÿÿ
00540A42  FF FF FF FF FF FF FF FF FF FF FF FF 8C 94 56 00  ÿÿÿÿÿÿÿÿÿÿÿÿŒ”V.

*/


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
#include "castle_battle_attack_heisuu_sum.h"

using namespace std;

#pragma unmanaged


static int ECXOfCastleBattleTaihouDefendDoorDamage = 0;
static int EAXOfCastleBattleTaihouDefendDoorDamage = 0;
void OnSSRExeCastleBattleTaihouDefendDoorDamageExecute() {
	int* pRemainDoorPtr = (int*)((BYTE*)(ECXOfCastleBattleTaihouDefendDoorDamage)+0xA); // ‚±‚±‚ÉUŒ‚‚µ‚½•«ƒ|ƒCƒ“ƒ^‚ª“ü‚Á‚Ä‚¢‚é

	int nBushouAddress = (int)(ƒƒbƒZ[ƒW•«î•ñ.på‘Ì•«);
	int iBushouID = getBushouIDFromBushouPtr((int *)nBushouAddress);
	if (isValidBushouID(iBushouID)) {
		OutputDebugStream("ƒhƒA‚Ìc‚è‘Ï‹v“x%d\n", *pRemainDoorPtr);
		OutputDebugStream("UŒ‚Ò" + getBushou©–¼FromBushouID(iBushouID) + "\n");


		if (getBushou©–¼FromBushouID(iBushouID) == getArubedoSeiMei()) {
			*pRemainDoorPtr = 0;                            // ‚±‚±‚Åc‚è–hŒä‚ğ0‚É‚·‚é
			EAXOfCastleBattleTaihouDefendDoorDamage = 0; // EAX‚É‚àc‚è–hŒä‚ğ“ü‚ê‚Ä‚¨‚­B‚±‚ê‚ª‰æ–Ê‚Å•\¦‚·‚é—p
		}

		// EAX ‚â *pReimainDoorPtr ‚ğã‘‚«‚·‚é‚È‚ç‚±‚±‚ÅB
	}

}

/*
00415D60   8BCE             MOV ECX,ESI
00415D62   E8 99D8FEFF      CALL Nobunaga.00403600
00415D67   50               PUSH EAX                                 ‚±‚Ì‚ÌEAX‚ªUŒ‚‘¤‚ÌŒ¸­Œã‚Ì–hŒä’lBECX+0xA‚ÌƒAƒhƒŒƒX‚É EAX‚Ì’l‚Æ“¯‚¶’l‚ğ“ü‚ê‚é‚±‚ÆB
00415D68   53               PUSH EBX
00415D69   68 A80D5200      PUSH Nobunaga.00520DA8                   ; ASCII "–hŒä“x : %d ---> %d"
00415D6E   68 D8A55D00      PUSH Nobunaga.005DA5D8                   ; ASCII "242"
*/

int pSSRExeJumpFromToOnSSRExeCastleBattleTaihouDefendDoorDamage = 0x415D62; // ŠÖ”‚Í‚±‚ÌƒAƒhƒŒƒX‚©‚çAOnSSRExeCastleBattleTaihouDefendDoorDamage‚Ö‚ÆƒWƒƒƒ“ƒv‚µ‚Ä‚­‚éB
int pSSRExeJumpCallFromToOnSSRExeCastleBattleTaihouDefendDoorDamage = 0x403600; // Œ³X‚ ‚Á‚½ˆ—‚ÌCallæ
int pSSRExeReturnLblFromOnSSRExeCastleBattleTaihouDefendDoorDamage = 0x415D67; // ŠÖ”‚ªÅŒã‚Ü‚Å‚¢‚­‚ÆA‚±‚ÌTENSHOU.EXE“à‚É’¼ÚƒWƒƒƒ“ƒv‚·‚é

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeCastleBattleTaihouDefendDoorDamage() {
	// ƒXƒ^ƒbƒN‚É‚½‚ß‚Ä‚¨‚­
	__asm {

		mov ECXOfCastleBattleTaihouDefendDoorDamage, ecx

		call pSSRExeJumpCallFromToOnSSRExeCastleBattleTaihouDefendDoorDamage

		mov EAXOfCastleBattleTaihouDefendDoorDamage, eax

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeCastleBattleTaihouDefendDoorDamageExecute();

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

		mov eax, EAXOfCastleBattleTaihouDefendDoorDamage  // ç”õ‘¤‚Ìc‚è–hŒä‚ğ•ÏX‚·‚é‚È‚ç‚±‚±‚Å•ÏX‚µ‚Ä‚¨‚­B
		jmp pSSRExeReturnLblFromOnSSRExeCastleBattleTaihouDefendDoorDamage
	}
}
#pragma warning(default: 4733) // ƒ[ƒjƒ“ƒO‚Ì—}§‚ğ‰ğœ‚·‚é



char cmdOnSSRExeJumpFromCastleBattleTaihouDefendDoorDamage[6] = "\xE9";
// Œ³‚Ì–½—ß‚ª5ƒoƒCƒgAˆÈŒã‚ÌŠÖ”‚Å¶‚Ü‚ê‚é–½—ß‚ª‡Œv‚TƒoƒCƒg‚È‚Ì‚Åc ÅŒã‚P‚Âg‚í‚È‚¢


// ƒj[ƒ‚ƒjƒbƒN‘‚«Š·‚¦—p
void WriteAsmJumperOnSSRExeCastleBattleTaihouDefendDoorDamage() {

	// ‚Ü‚¸ƒAƒhƒŒƒX‚ğ”š‚Æ‚µ‚Äˆµ‚¤
	int iAddress = (int)OnSSRExeCastleBattleTaihouDefendDoorDamage;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeCastleBattleTaihouDefendDoorDamage + 5);
	// ‚T‚Æ‚¢‚¤‚Ì‚ÍA0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  ‚Ì–½—ß‚É•K—v‚ÈƒoƒCƒg”B—v‚·‚é‚É‚TƒoƒCƒg‘«‚·‚ÆŸ‚Ìƒj[ƒ‚ƒjƒbƒN–½—ßŒQ‚ÉˆÚ“®‚·‚é‚Ì‚¾B‚»‚µ‚Ä‚»‚±‚©‚ç‚Ì·•ª‚ªƒWƒƒƒ“ƒv‚·‚éÛ‚Ì–Ú“IŠi‚Æ‚µ‚Ä—˜—p‚³‚ê‚éB
	memcpy(cmdOnSSRExeJumpFromCastleBattleTaihouDefendDoorDamage + 1, &SubAddress, 4); // +1 ‚ÍE9‚ÌŸ‚©‚ç4ƒoƒCƒg•ª‘‚«Š·‚¦‚é‚©‚çB

	// \’z‚µ‚½ƒj[ƒ‚ƒjƒbƒN–½—ß‚ğTENSHOU.EXE‚Ìƒƒ‚ƒŠ‚É‘‚«Š·‚¦‚é
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeCastleBattleTaihouDefendDoorDamage), cmdOnSSRExeJumpFromCastleBattleTaihouDefendDoorDamage, 5, NULL); //5ƒoƒCƒg‚Ì‚İ‘‚«‚Ş
}

#pragma managed
