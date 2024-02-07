/*
00523F44  8D 81 96 D8 00 00 00 00 92 BF 95 69 00 00 00 00  –Ø....’¿•i....
00523F54  8F 5C 8E 9A 89 CB 00 00 8E 5A 94 D5 00 00 00 00  \š‰Ë..Z”Õ....
00523F64  93 EC 94 D8 8E 9E 8C 76 00 00 00 00 97 85 90 6A  “ì”ØŒv....—…j
00523F74  94 D5 00 00 92 6E 90 7D 00 00 00 00 8A 47 89 E6  ”Õ..’n}....ŠG‰æ
00523F84  00 00 00 00 8F A4 8B C6 8F 91 00 00 8C 52 8B 4C  ....¤‹Æ‘..ŒR‹L
00523F94  95 A8 8C EA 00 00 00 00 95 A7 8B B3 8F 91 00 00  •¨Œê....•§‹³‘..
00523FA4  95 B6 8A 77 8F 91 00 00 8F 40 8B B3 8F 91 00 00  •¶Šw‘..@‹³‘..
00523FB4  97 F0 8E 6A 8F 91 00 00 8C 9A 92 7A 8F 91 00 00  —ğj‘..Œš’z‘..
00523FC4  8D 7A 8F 70 8F 91 00 00 8A 4F 8C F0 8F 91 00 00  zp‘..ŠOŒğ‘..
00523FD4  94 5F 90 AD 8F 91 00 00 92 6D 8E AF 8F 91 00 00  ”_­‘..’m¯‘..
00523FE4  94 45 8F 70 8F 91 00 00 88 E3 8F 70 8F 91 00 00  ”Ep‘..ˆãp‘..
00523FF4  95 BA 96 40 8F 91 00 00 96 43 8F 70 8F 91 00 00  •º–@‘..–Cp‘..
00524004  94 6E 8F 70 8F 91 00 00 8C 95 8F 70 8F 91 00 00  ”np‘..Œ•p‘..
00524014  92 5A 93 9B 00 00 00 00 96 BC 94 6E 00 00 00 00  ’Z“›....–¼”n....
00524024  95 BA 91 95 95 69 00 00 95 90 8A ED 00 00 00 00  •º‘••i..•Ší....
00524034  92 83 93 B9 93 B9 8B EF                          ’ƒ“¹“¹‹ï....

*/

/*
ã‚Ìƒ|ƒCƒ“ƒ^‚Ì”z—ñ
0053A8B8  34 40 52 00 2C 40 52 00 24 40 52 00 1C 40 52 00  4@R.,@R.$@R.@R.
0053A8C8  14 40 52 00 0C 40 52 00 04 40 52 00 FC 3F 52 00  @R..@R.@R.ER.
0053A8D8  F4 3F 52 00 EC 3F 52 00 E4 3F 52 00 DC 3F 52 00  ER.ER.ER.Ü?R.
0053A8E8  D4 3F 52 00 CC 3F 52 00 C4 3F 52 00 BC 3F 52 00  Ô?R.Ì?R.Ä?R.¼?R.
0053A8F8  B4 3F 52 00 AC 3F 52 00 A4 3F 52 00 9C 3F 52 00  ´?R.¬?R.¤?R.ER.
0053A908  90 3F 52 00 88 3F 52 00 80 3F 52 00 78 3F 52 00  ER.ER.€?R.x?R.
0053A918  70 3F 52 00 64 3F 52 00 5C 3F 52 00 54 3F 52 00  p?R.d?R.\?R.T?R.
0053A928  4C 3F 52 00 44 3F 52 00                          L?R.D?R.

*/

/*
0047C9C0  /$ 51             PUSH ECX
0047C9C1  |. 56             PUSH ESI
0047C9C2  |. 8BF1           MOV ESI,ECX
0047C9C4  |. 57             PUSH EDI
0047C9C5  |. 8D4C24 08      LEA ECX,DWORD PTR SS:[ESP+8]

*/

/*
ã‚Ìƒ|ƒCƒ“ƒ^‚ğ—˜—p‚µ‚Ä‚¢‚é‰ÓŠ‚Í1‰ÓŠ‚¾‚¯B‚±‚ÌECX‚ÍAŠY“–‚Ì‰Æ•óî•ñ‚Ö‚Ì‰Æ•óƒ|ƒCƒ“ƒ^‚ª“ü‚Á‚Ä‚¢‚éB
EAX‚Í‚à‚¿‚ë‚ñ‰Æ•óí—Ş”Ô†
0047CA24  |. 0F8D E3010000          JGE Nobunaga.0047CC0D
0047CA2A  |. 8B3485 B8A85300        MOV ESI,DWORD PTR DS:[EAX*4+53A8B8]                         ;  Nobunaga.00523F4C
0047CA31  |. E9 DD010000            JMP Nobunaga.0047CC13

*/



#include <windows.h>
#include <string>
#include <cstdlib>
#include <memory>
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
#include "mng_‰Æ•ó—ñ‹“.h"


using namespace std;


static int ECXOfKahouTypeName = -1;
static int EAXOfKahouTypeName = -1;
static int ESIOfKahouTypeName = -1;

struct TKahouTypeName {
	char name[9]; // ‘SŠp4•¶š‚Ü‚Å
};

//TKahouTypeName listKahouType[Å‘å”::‰Æ•óî•ñ::”z—ñ”] = { 0 };
std::unique_ptr<TKahouTypeName[]> listKahouType(new TKahouTypeName[Å‘å”::‰Æ•óî•ñ::”z—ñ”]());

void OnSSRExeKahouTypeNameExecute() {

	int iKahouID = getKahouIDFromKahouPtr((int*)ECXOfKahouTypeName);
	if (isValidKahouID(iKahouID)) {

		// ‰Æ•ó‚ÌƒfƒtƒHƒ‹ƒg‚Ìí—Ş–¼‚ğ“¾‚é
		int iKahouType = nb7‰Æ•óî•ñ[iKahouID].í—Ş;
		int iKahouTypeNameLocation = 4 * iKahouType + 0x53A8B8;
		int pKahouName = *((int*)iKahouTypeNameLocation);
		// OutputDebugStream("í—Ş–¼‚Í%s\n", pKahouName);

		// ‚»‚ê‚ğ200ŒÂ‚Ìƒoƒbƒtƒ@[‚ÉŠi”[‚µ‚Ä‚¨‚­
		strcpy_s(listKahouType[iKahouID].name, (char*)pKahouName);

		// ‰Æ•óí—Ş–¼‚ğæ“¾‚·‚é
		// OutputDebugStream("‰Æ•ó:"s + nb7‰Æ•óî•ñ[iKahouID].‰Æ•ó–¼);
		// OutputDebugStream("êŠ‚Í%x‚¾‚æ", ESIOfKahouTypeName);
		
		// ššš‚±‚±‚Å‘ÎÛ‚Ì‰Æ•ó‚Ìí—Ş–¼‚ğ•ÏX‚·‚é
		int iKahouImageType = nb7‰Æ•óî•ñ[iKahouID].‰æ‘œ;
		if (iKahouImageType == —ñ‹“::‰Æ•ó::‰æ‘œ::‹ï‘«) {
			strcpy_s(listKahouType[iKahouID].name, "‹ï‘«");
		}
		else if (iKahouImageType == —ñ‹“::‰Æ•ó::‰æ‘œ::“Œ•) {
			strcpy_s(listKahouType[iKahouID].name, "“Œ•");
		}
		else if (iKahouImageType == —ñ‹“::‰Æ•ó::‰æ‘œ::w‰HD) {
			strcpy_s(listKahouType[iKahouID].name, "w‰HD");
		}
		else if (iKahouImageType == —ñ‹“::‰Æ•ó::‰æ‘œ::‘„) {
			strcpy_s(listKahouType[iKahouID].name, "‘„");
		}
		else if (iKahouImageType == —ñ‹“::‰Æ•ó::‰æ‘œ::ˆÆ) {
			strcpy_s(listKahouType[iKahouID].name, "ˆÆ");
		}
		else if (iKahouImageType == —ñ‹“::‰Æ•ó::‰æ‘œ::ç’¹) {
			strcpy_s(listKahouType[iKahouID].name, "ç’¹");
		}
		else if (iKahouImageType == —ñ‹“::‰Æ•ó::‰æ‘œ::‰Ô“ü) {
			strcpy_s(listKahouType[iKahouID].name, "‰Ô“ü");
		}
		else if (iKahouImageType == —ñ‹“::‰Æ•ó::‰æ‘œ::’ƒ“ü) {
			strcpy_s(listKahouType[iKahouID].name, "’ƒ“ü");
		}
		else if (iKahouImageType == —ñ‹“::‰Æ•ó::‰æ‘œ::’ƒšâ) {
			strcpy_s(listKahouType[iKahouID].name, "’ƒšâ");
		}
		else if (iKahouImageType == —ñ‹“::‰Æ•ó::‰æ‘œ::’ƒ˜q) {
			strcpy_s(listKahouType[iKahouID].name, "’ƒ˜q");
		}
		else if (iKahouImageType == —ñ‹“::‰Æ•ó::‰æ‘œ::’ƒŠ˜) {
			strcpy_s(listKahouType[iKahouID].name, "’ƒŠ˜");
		}
		else if (iKahouImageType == —ñ‹“::‰Æ•ó::‰æ‘œ::—mŠyŠí) {
			strcpy_s(listKahouType[iKahouID].name, "—mŠyŠí");
		}
		else if (iKahouImageType == —ñ‹“::‰Æ•ó::‰æ‘œ::‰“Šá‹¾) {
			strcpy_s(listKahouType[iKahouID].name, "‰“Šá‹¾");
		}
		else if (iKahouImageType == —ñ‹“::‰Æ•ó::‰æ‘œ::—V‹Y‹ï) {
			strcpy_s(listKahouType[iKahouID].name, "—V‹Y‹ï");
		}
		else if (iKahouImageType == —ñ‹“::‰Æ•ó::‰æ‘œ::‰Œ‘) {
			strcpy_s(listKahouType[iKahouID].name, "‰Œ‘");
		}

		// ššš‚±‚±‚ÅJavaScriptMod‚â“Á•Ê‚Èí—Ş‚Ì’u‚«Š·‚¦‚ğs‚¤

		// ƒoƒ‹ƒfƒBƒbƒVƒ…‚È‚ç•€
		if (nb7‰Æ•óî•ñ[iKahouID].‰Æ•ó–¼ == "ƒoƒ ƒ¡ƒ¢ƒ£ƒ¤"s) {
			strcpy_s(listKahouType[iKahouID].name, "•€");
		}
		else if (nb7‰Æ•óî•ñ[iKahouID].‰Æ•ó–¼ == "ƒM„F„G„H„Iƒv"s) {
			strcpy_s(listKahouType[iKahouID].name, "”é•ó");
		}
		else if (nb7‰Æ•óî•ñ[iKahouID].‰Æ•ó–¼ == "ƒ¨ƒ¥ƒ¦ƒ©ƒ§ƒª"s) {
			strcpy_s(listKahouType[iKahouID].name, "‹ï‘«");
		}

		// ‘ÎÛ‚Ì–¼‘O‚Ö‚Ìƒ|ƒCƒ“ƒ^‚ğ‘ã“ü‚µ‚Ä‚¨‚­B
		ESIOfKahouTypeName = (int)(listKahouType[iKahouID].name);
	}

}

#pragma unmanaged

/*
ã‚Ìƒ|ƒCƒ“ƒ^‚ğ—˜—p‚µ‚Ä‚¢‚é‰ÓŠ‚Í1‰ÓŠ‚¾‚¯B‚±‚ÌECX‚ÍAŠY“–‚Ì‰Æ•óî•ñ‚Ö‚Ì‰Æ•óƒ|ƒCƒ“ƒ^‚ª“ü‚Á‚Ä‚¢‚éB
EAX‚Í‚à‚¿‚ë‚ñ‰Æ•óí—Ş”Ô†
0047CA24  |. 0F8D E3010000          JGE Nobunaga.0047CC0D
0047CA2A  |. 8B3485 B8A85300        MOV ESI,DWORD PTR DS:[EAX*4+53A8B8]                         ;  Nobunaga.00523F4C
0047CA31  |. E9 DD010000            JMP Nobunaga.0047CC13

*/

int pSSRExeJumpFromToOnSSRExeKahouTypeName = 0x47CA2A; // ŠÖ”‚Í‚±‚ÌƒAƒhƒŒƒX‚©‚çAOnSSRExeKahouTypeName‚Ö‚ÆƒWƒƒƒ“ƒv‚µ‚Ä‚­‚éB
int pSSRExeReturnLblFromOnSSRExeKahouTypeName = 0x47CA31; // ŠÖ”‚ªÅŒã‚Ü‚Å‚¢‚­‚ÆA‚±‚ÌTENSHOU.EXE“à‚É’¼ÚƒWƒƒƒ“ƒv‚·‚é

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeKahouTypeName() {
	// ƒXƒ^ƒbƒN‚É‚½‚ß‚Ä‚¨‚­
	__asm {

		MOV ESI, DWORD PTR DS : [EAX * 4 + 0x53A8B8]

		mov ECXOfKahouTypeName, ecx
		mov EAXOfKahouTypeName, eax
		mov ESIOfKahouTypeName, esi
		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeKahouTypeNameExecute();

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

		MOV ESI, ESIOfKahouTypeName

		jmp pSSRExeReturnLblFromOnSSRExeKahouTypeName
	}
}
#pragma warning(default: 4733) // ƒ[ƒjƒ“ƒO‚Ì—}§‚ğ‰ğœ‚·‚é



char cmdOnSSRExeJumpFromKahouTypeName[8] = "\xE9\x90\x90\x90\x90\x90\x90";
// Œ³‚Ì–½—ß‚ª5ƒoƒCƒgAˆÈŒã‚ÌŠÖ”‚Å¶‚Ü‚ê‚é–½—ß‚ª‡Œv‚TƒoƒCƒg‚È‚Ì‚Åc ÅŒã‚P‚Âg‚í‚È‚¢


// ƒj[ƒ‚ƒjƒbƒN‘‚«Š·‚¦—p
void WriteAsmJumperOnSSRExeKahouTypeName() {

	// ‚Ü‚¸ƒAƒhƒŒƒX‚ğ”š‚Æ‚µ‚Äˆµ‚¤
	int iAddress = (int)OnSSRExeKahouTypeName;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeKahouTypeName + 5);
	// ‚T‚Æ‚¢‚¤‚Ì‚ÍA0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  ‚Ì–½—ß‚É•K—v‚ÈƒoƒCƒg”B—v‚·‚é‚É‚TƒoƒCƒg‘«‚·‚ÆŸ‚Ìƒj[ƒ‚ƒjƒbƒN–½—ßŒQ‚ÉˆÚ“®‚·‚é‚Ì‚¾B‚»‚µ‚Ä‚»‚±‚©‚ç‚Ì·•ª‚ªƒWƒƒƒ“ƒv‚·‚éÛ‚Ì–Ú“IŠi‚Æ‚µ‚Ä—˜—p‚³‚ê‚éB
	memcpy(cmdOnSSRExeJumpFromKahouTypeName + 1, &SubAddress, 4); // +1 ‚ÍE9‚ÌŸ‚©‚ç4ƒoƒCƒg•ª‘‚«Š·‚¦‚é‚©‚çB

	// \’z‚µ‚½ƒj[ƒ‚ƒjƒbƒN–½—ß‚ğTENSHOU.EXE‚Ìƒƒ‚ƒŠ‚É‘‚«Š·‚¦‚é
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeKahouTypeName), cmdOnSSRExeJumpFromKahouTypeName, 7, NULL); //7ƒoƒCƒg‚Ì‚İ‘‚«‚Ş
}

#pragma managed
