#pragma once

#include <windows.h>

#define ƒ†ƒjƒbƒgî•ñƒAƒhƒŒƒX 0x5EDE10

// ‚±‚ê‚ÍƒZ[ƒuƒf[ƒ^ƒGƒfƒBƒ^‚Ìƒ†ƒjƒbƒgƒGƒfƒBƒ^‚ðŽg‚¦‚ÎA‚Ç‚ñ‚Ç‚ñÚ‚µ‚­‚í‚©‚Á‚Ä‚­‚é‚¾‚ë‚¤B

// 148ƒoƒCƒg
#pragma pack(1)
struct NB7ƒ†ƒjƒbƒgî•ñŒ^ {
	int pŠ‘®é; // [00 90 53]‚È‚ç‚Ç‚±‚Ìé‚É‚àŠ‘®‚µ‚Ä‚¢‚È‚¢
	int unknown1;
	int* pƒ†ƒjƒbƒg•«; // •«‚Ö‚Ìƒ|ƒCƒ“ƒ^(•«î•ñ‚Ì”z—ñ‚ÌŠY“–•«‚Ìî•ñ‚ÌˆÊ’u‚ð’¼ÚŽw‚µ‚Ä‚¢‚é)B‚±‚±‚ª[B0 56 94]‚È‚ç‚ÎA‚»‚à‚»‚àƒ†ƒjƒbƒg‚ð’N‚à—¦‚¢‚Ä‚¢‚È‚¢B•«î•ñ’†‚Ì744l‚É“ü‚Á‚Ä‚¢‚é‚©‚Ç‚¤‚©‚Å”»’è‚·‚é‚Ì‚ª—Ç‚¢‚¾‚ë‚¤B
	int ‹à‘K;
	int ‹à‘KMAX; // 50000=0xC350‚ªí‚É“ü‚Á‚Ä‚¢‚é
	int •º—Æ;
	int •º—ÆMAX; // 50000=0xC350‚ªí‚É“ü‚Á‚Ä‚¢‚é
	int ŒR”n;
	int ŒR”nMAX; // 50000=0xC350‚ªí‚É“ü‚Á‚Ä‚¢‚é
	int “S–C;
	int “S–CMAX; // 50000=0xC350‚ªí‚É“ü‚Á‚Ä‚¢‚é
	int —A‘—•ºŽm;    // —A‘——p‚Ì•ºŽmBŒR‘à—p•º”‚Å‚Í‚È‚¢B
	int —A‘—•ºŽmMAX; // 50000=0xC350‚ªí‚É“ü‚Á‚Ä‚¢‚é
	int —A‘—‘å–C;    // —A‘——p‚Ì‘å–CBŒR‘à—p•º”‚Å‚Í‚È‚¢B
	int —A‘—‘å–CMAX; // 50000=0xC350‚ªí‚É“ü‚Á‚Ä‚¢‚é
	int ƒ}ƒbƒvã‚Ì‚wÀ•W;
	int ƒ}ƒbƒvã‚Ì‚xÀ•W;
	int unknown9; // [0xffffffff] ‚ª‘½‚¢
	BYTE unknown98[26];
	/* wŒ`ˆÊ’u
	  „¡„Ÿ„¦„Ÿ„¦„Ÿ„¢
	  „ ‚Q„ ‚T„ ‚W„ 
	  „¥„Ÿ„©„Ÿ„©„Ÿ„§
	  „ ‚P„ ‚S„ ‚V„ 
	  „¥„Ÿ„©„Ÿ„©„Ÿ„§
	  „ ‚O„ ‚R„ ‚U„ 
	  „¤„Ÿ„¨„Ÿ„¨„Ÿ„£
	*/
	WORD ‘æ‚P•”‘à•ºŽí; // 0:‘«Œy 1:‹R”n 2:“S–C 3:‹R”n“S–C  •”‘à‚ª‚È‚¯‚ê‚ÎFFFF
	WORD ‘æ‚P•”‘à‚ÌwŒ`ˆÊ’u; // •”‘à‚ª‚È‚¯‚ê‚ÎFFFF
	int ‘æ‚P•”‘à•º”; // •”‘à‚ª‚È‚¯‚ê‚Î0
	WORD ‘æ‚Q•”‘à•ºŽí; // 0:‘«Œy 1:‹R”n 2:“S–C 3:‹R”n“S–C  •”‘à‚ª‚È‚¯‚ê‚ÎFFFF
	WORD ‘æ‚Q•”‘à‚ÌwŒ`ˆÊ’u; // •”‘à‚ª‚È‚¯‚ê‚ÎFFFF
	int ‘æ‚Q•”‘à•º”; // •”‘à‚ª‚È‚¯‚ê‚Î0
	WORD ‘æ‚R•”‘à•ºŽí; // 0:‘«Œy 1:‹R”n 2:“S–C 3:‹R”n“S–C  •”‘à‚ª‚È‚¯‚ê‚ÎFFFF
	WORD ‘æ‚R•”‘à‚ÌwŒ`ˆÊ’u; // •”‘à‚ª‚È‚¯‚ê‚ÎFFFF
	int ‘æ‚R•”‘à•º”; // •”‘à‚ª‚È‚¯‚ê‚Î0
	WORD ‘æ‚S•”‘à•ºŽí; // 0:‘«Œy 1:‹R”n 2:“S–C 3:‹R”n“S–C  •”‘à‚ª‚È‚¯‚ê‚ÎFFFF
	WORD ‘æ‚S•”‘à‚ÌwŒ`ˆÊ’u; // •”‘à‚ª‚È‚¯‚ê‚ÎFFFF
	int ‘æ‚S•”‘à•º”; // •”‘à‚ª‚È‚¯‚ê‚Î0
	WORD ‘æ‚T•”‘à•ºŽí; // 0:‘«Œy 1:‹R”n 2:“S–C 3:‹R”n“S–C  •”‘à‚ª‚È‚¯‚ê‚ÎFFFF
	WORD ‘æ‚T•”‘à‚ÌwŒ`ˆÊ’u; // •”‘à‚ª‚È‚¯‚ê‚ÎFFFF
	int ‘æ‚T•”‘à•º”; // •”‘à‚ª‚È‚¯‚ê‚Î0
	int ƒ†ƒjƒbƒg”Ô†;   // 1‚©‚ç‚Ì”Ô†‚ªU‚ç‚ê‚Ä‚¢‚éB
	int ƒ†ƒjƒbƒgl”MAX; // [E8 02] == 744 ‚Æ‚¢‚¤ƒ†ƒjƒbƒgÅ‘å”‚ªí‚É‚Í‚¢‚Á‚Ä‚¢‚éB‚±‚ê‚ÍExcel‚È‚Ç‚ðŒ©‚Ä‚à‚í‚©‚éB
	BYTE unused4;

	// ˆÈ‰º‚PƒoƒCƒg‚ð•ªŠ„‚µ‚½‚¢‚ë‚¢‚ë‚Èƒtƒ‰ƒOB // 0‚ÌŽž‚à‚ ‚ê‚ÎA[00 00 00 10]‚È‚Ç‚à‚ ‚é
	BYTE flag_unknown1 : 1;
	BYTE “Sb‘D : 1; // 
	BYTE ‘å–C : 1; // ‘å–C
	BYTE flag_unknown2 : 1; // •s–¾B0‚ÌŽž‚à‚ ‚ê‚ÎA[00 00 00 10]‚Ì‚Á‚Æ‹C‚à‚ ‚é
	BYTE flag_unknown3 : 1; // •s–¾B0‚ÌŽž‚à‚ ‚ê‚ÎA[00 00 00 10]‚Ì‚Á‚Æ‹C‚à‚ ‚é
	BYTE flag_unknown4 : 1; // •s–¾B0‚ÌŽž‚à‚ ‚ê‚ÎA[00 00 00 10]‚Ì‚Á‚Æ‹C‚à‚ ‚é
	BYTE flag_unknown5 : 1; // •s–¾B0‚ÌŽž‚à‚ ‚ê‚ÎA[00 00 00 10]‚Ì‚Á‚Æ‹C‚à‚ ‚é
	BYTE flag_unknown8 : 1; // •s–¾B

};
#pragma pack()

// ƒ†ƒjƒbƒgID‚©‚ç‚»‚ê‚ð—¦‚¢‚é•«ID‚ð“¾‚é
int getBushouIDFromUnitID(int iUnitID);

/*
1l–Ú‚Ìƒ†ƒjƒbƒgî•ñ
005EDE10  00 90 53 00 00 00 00 00 88 4C 54 00 00 00 00 00  .S.....ET.....
005EDE20  50 C3 00 00 B8 0B 00 00 B8 0B 00 00 00 00 00 00  PÃ..¸..¸......
005EDE30  50 C3 00 00 00 00 00 00 50 C3 00 00 00 00 00 00  PÃ......PÃ......
005EDE40  50 C3 00 00 00 00 00 00 50 C3 00 00 96 00 00 00  PÃ......PÃ..E..
005EDE50  47 00 00 00 FF FF FF FF 00 00 00 00 00 00 00 00  G...ÿÿÿÿ........
005EDE60  00 00 00 00 FF 0F 00 00 00 00 E8 70 5F 00 01 00  ....ÿ....èp_..
005EDE70  00 00 00 00 07 00 84 03 00 00 01 00 00 00 84 03  .....E.....E
005EDE80  00 00 01 00 01 00 84 03 00 00 01 00 02 00 84 03  ....E....E
005EDE90  00 00 00 00 04 00 84 03 00 00 01 00 00 00 E8 02  .....E.....E
005EDEA0  00 00 00 00 

‚Ql–Ú‚Ìƒ†ƒjƒbƒgî•ñ
@@@@@@@@@@@00 90 53 00 00 00 00 00 48 62 54 00  .....S.....HbT.
005EDEB0  00 00 00 00 50 C3 00 00 B8 0B 00 00 B8 0B 00 00  ....PÃ..¸..¸..
005EDEC0  00 00 00 00 50 C3 00 00 00 00 00 00 50 C3 00 00  ....PÃ......PÃ..
005EDED0  00 00 00 00 50 C3 00 00 00 00 00 00 50 C3 00 00  ....PÃ......PÃ..
005EDEE0  74 00 00 00 7E 00 00 00 FF FF FF FF 00 00 00 00  t...~...ÿÿÿÿ....
005EDEF0  00 00 00 00 00 00 00 00 FF 0F 00 00 00 00 E8 70  ........ÿ....èp
005EDF00  5F 00 01 00 00 00 00 00 07 00 84 03 00 00 01 00  _.......E...
005EDF10  00 00 84 03 00 00 01 00 01 00 84 03 00 00 01 00  ..E....E...
005EDF20  02                                               



23l–Ú‚Ìƒ†ƒjƒbƒgî•ñB
005EEAC8  00 90 53 00 0A 00 00 00 C8 89 55 00 00 00 00 00  .S.....È‰U.....
005EEAD8  50 C3 00 00 00 00 00 00 50 C3 00 00 00 00 00 00  PÃ......PÃ......
005EEAE8  50 C3 00 00 00 00 00 00 50 C3 00 00 00 00 00 00  PÃ......PÃ......
005EEAF8  50 C3 00 00 00 00 00 00 50 C3 00 00 3A 00 00 00  PÃ......PÃ..:...
005EEB08  54 00 00 00 FF FF FF FF 2C 00 00 00 05 00 00 00  T...ÿÿÿÿ,......
005EEB18  00 00 00 00 FF 0F 00 00 53 3E E8 70 5F 00 01 00  ....ÿ..S>èp_..
005EEB28  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................
005EEB38  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................
005EEB48  00 00 00 00 00 00 00 00 00 00 17 00 00 00 E8 02  .............E
005EEB58  00 00 00 00                                      ....



 
24l–Ú‚Ìƒ†ƒjƒbƒgî•ñBæ“ª‚ª‚Ç‚Ìé‚É‘®‚·‚é‚©A3”Ô–Ú‚ª‚»‚ê‚ª’N‚©
005EEB5C  98 CB 5D 00 09 00 00 00 48 3C 56 00 00 00 00 00  ˜Ë].....H<V.....
005EEB6C  50 C3 00 00 00 00 00 00 B8 0B 00 00 00 00 00 00  PÃ......¸......
005EEB7C  50 C3 00 00 00 00 00 00 50 C3 00 00 00 00 00 00  PÃ......PÃ......
005EEB8C  50 C3 00 00 00 00 00 00 50 C3 00 00 52 00 00 00  PÃ......PÃ..R...
005EEB9C  59 00 00 00 FF FF FF FF 2C 00 00 00 01 00 00 00  Y...ÿÿÿÿ,......
005EEBAC  00 00 00 00 FF 0F 00 00 20 00 E0 90 53 00 03 00  ....ÿ.. .àS..
005EEBBC  00 00 00 00 04 00 00 00 00 00 00 00 02 00 00 00  ..............
005EEBCC  00 00 00 00 00 00 00 00 00 00 00 00 05 00 00 00  ...............
005EEBDC  00 00 00 00 03 00 00 00 00 00 18 00 00 00 E8 02  ............E
005EEBEC  00 00 00 10                                    ....
*/