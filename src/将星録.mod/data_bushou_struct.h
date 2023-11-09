#pragma once

/*
BaseAddress 0x400000Žž

00542348  åyè...‹GL...åyè‹GL......˜Ý]....E..E..E...........E..
00542388  E..d...d...M...n...8...n...J...n...............W...........
005423C8  ÿÿÿÿ...............¸ŽS.°”V..................E......E..°”V.
00542408  ¼‘O...ŒcL...¼‘OŒcL......˜Ý].........................
00542448  E..X...d...T...n...2...n...U...n...............Î..........
*/

#pragma pack(1)
struct NB7•«î•ñŒ^
{
	char •cŽš[8];	// •cŽš
	char –¼‘O[8];	// –¼‘O
	WORD ¶”N;      // ¼—ï‚Å
	WORD Œ³•ž”N;    // ¼—ï‚Å
	WORD Žõ–½;      // 0`7
	WORD ­Ž¡;      // 0`100
	WORD í“¬;      // 0`100
	WORD ’m–d;      // 0`100
	WORD ŠçID;      // ŠçƒOƒ‰ID
	WORD ’‰½;      // 0`64
	WORD ó‘Ô;      // –¢“oê•«‚Í“oêé‚ÌéID@0:‘å–¼A1:Œ»–ðA2:“Æ—§¨—ÍA3:˜QlA4:—ðŽjã‚Ì•PE¥ˆ÷—p‚Ì•PA5:–¢“oê‚Ì•«E•PA 6:ˆêŒüˆê„¨—ÍA7:ˆê„¨—ÍA8:‘Ò‹@EŽ€–S
	WORD E‹Æ;      // 0:”EŽÒA1:’ƒlA2:Œ•‹A3:‘m—µA4:ØŽx’O
	WORD g•ª;      // 5:‘å–¼A4:h˜VA3:‰Æ˜VA2:•”«A1:Ž˜‘å«A0:‘«Œy“ª
	WORD ŒMŒ÷;      // ‘å–¼Ah˜V:500ˆÈãA‰Æ˜V:300ˆÈãA•”«:150ˆÈãAŽ˜‘å«:50ˆÈãA‘«Œy“ª:0ˆÈã
	WORD ‹`—;      // 0x00`0x0F (0`15)
	WORD ‘Š«;      // 0x00`0x15 (0`21)
	WORD ˆê–å;      // ˆê–åO‡‚i—áFŽq‹ŸEŒZ’í•«‚È‚Ç‚ÌƒR[ƒh‚ðŽQÆ‚·‚é‚Æ—Ç‚¢j
	WORD ‹é;      // ‹’“_‚Æ‚µ‚Ä‚¢‚éé‡‚
	WORD ‘«Œy;      // 01`06 "E"`"S"
	WORD ‹R”n;      // 01`06 "E"`"S"
	WORD “S–C;      // 01`06 "E"`"S"
	WORD …ŒR;      // 01`06 "E"`"S"
	WORD ŽdŠ¯;      // ¼—ï‚Å
	WORD ”Ô†;      // ƒ†ƒjƒbƒg‡‚¨iˆÚ“®ƒ†ƒjƒbƒgC”_‹Æƒ†ƒjƒbƒgj
	WORD •v•w;      // •v‚É‚ÍÈ‚ÌAÈ‚É‚Í•v‚Ì•«‡‚‚ð“ü‚ê‚é
	WORD •ƒe;      // •ƒe‚Ì•«‡‚i—áF•“cMŒºFDB.07j
	WORD ˜—ñ;      // ‹é‚Å‚ÌÝé•«‚Ì‡”Ô
	WORD ‰…¦;      // Š©—U‚ðŽó‚¯‚Ä‚àâ‘Î‚ÉŽdŠ¯‚µ‚È‚¢¨—Í‡‚i–Å–S‚³‚¹‚ç‚ê‚½¨—Í‡‚j
	WORD “à‹Z;      // “à­“Á‹Z
	WORD í‹Z;      // í“¬“Á‹Z
	WORD ”_Œo;      // ”_‹Æ‚ÌŒoŒ±’lAˆê’è’l‚Å‹Z”\K“¾C‚‚¢‚ÆŠúŠÔ’Zk
	WORD ¤Œo;      // ¤‹Æ‚ÌŒoŒ±’lAˆê’è’l‚Å‹Z”\K“¾C‚‚¢‚ÆŠúŠÔ’Zk
	WORD ŒšŒo;      // ŒšÝ‚ÌŒoŒ±’lAˆê’è’l‚Å‹Z”\K“¾C‚‚¢‚ÆŠúŠÔ’Zk
	WORD Œû’²;      // –{l‚ÌŒû’²i0`7j¨i0:–³ŒûA1:—ç‹VA2:‘e–\A3:‚‹MA4:¶ˆÓ‹CA5:ˆÐŒµA6:é`ãA7:ˆê”Êj
	WORD •«;      // –{l‚Ì•«‡‚
	WORD Š‘®;      // ‚¨‰ÆÄ‹»²ÍÞÝÄŽž‚Ì‹ŒŽå‚Ì•«‡‚(ˆê–åO:‘å–¼•«‡‚)
	WORD «•Ê;      // 0:’jA1:—
	WORD unknown1;  // “ä‚Ìƒf[ƒ^
	WORD ˆÚ“®—Í‘‰Á;  // ¦ŽQÆ
	WORD unknown2;  // “ä‚Ìƒf[ƒ^
};

/*
0000`0007,0080`0087‚ÉÝ’è‚·‚é‚Æ–¢s“®‚Æ‚È‚éB
0008`000F,0088`008F‚ÉÝ’è‚·‚é‚Æs“®Ï‚Ý‚Æ‚È‚éB
0010`0017,0090`0097‚ÉÝ’è‚·‚é‚ÆC‹Æ’†‚Å–¢s“®‚Æ‚È‚éB
0018`001F,0098`009F‚ÉÝ’è‚·‚é‚ÆC‹Æ’†‚Ås“®Ï‚Ý‚Æ‚È‚éB
0020`0027,00A0`00A7‚ÉÝ’è‚·‚é‚ÆˆÚ“®—Í‘‰ÁÏ‚Ý‚Å–¢s“®‚Æ‚È‚éB
0028`002F,00A8`00AF‚ÉÝ’è‚·‚é‚ÆˆÚ“®—Í‘‰ÁÏ‚Ý‚Ås“®Ï‚Ý‚Æ‚È‚éB
0030`0037,00B0`00B7‚ÉÝ’è‚·‚é‚ÆˆÚ“®—Í‘‰ÁÏ‚ÝEC‹Æ’†‚Å–¢s“®‚Æ‚È‚éB
0038`003F,00B8`00BF‚ÉÝ’è‚·‚é‚ÆˆÚ“®—Í‘‰ÁÏ‚ÝEC‹Æ’†‚Ås“®Ï‚Ý‚Æ‚È‚éB
0040`0047,00C0`00C7‚ÉÝ’è‚·‚é‚Æ”EŽÒC‹ÆÏ‚Ý‚Å–¢s“®‚Æ‚È‚éB
0048`004F,00C8`00CF‚ÉÝ’è‚·‚é‚Æ”EŽÒC‹ÆÏ‚Ý‚Ås“®Ï‚Ý‚Æ‚È‚éB
0050`0057,00D0`00D7‚ÉÝ’è‚·‚é‚Æ”EŽÒC‹ÆÏ‚ÝEC‹Æ’†‚Å–¢s“®‚Æ‚È‚éB
0058`005F,00D8`00DF‚ÉÝ’è‚·‚é‚Æ”EŽÒC‹ÆÏ‚ÝEC‹Æ’†‚Ås“®Ï‚Ý‚Æ‚È‚éB
0060`0067,00E0`00E7‚ÉÝ’è‚·‚é‚ÆˆÚ“®—Í‘‰ÁE”EŽÒC‹ÆÏ‚Ý‚Å–¢s“®‚Æ‚È‚éB
0068`006F,00E8`00EF‚ÉÝ’è‚·‚é‚ÆˆÚ“®—Í‘‰ÁE”EŽÒC‹ÆÏ‚Ý‚Ås“®Ï‚Ý‚Æ‚È‚éB
0070`0077,00F0`00F7‚ÉÝ’è‚·‚é‚ÆˆÚ“®—Í‘‰ÁE”EŽÒC‹ÆÏ‚ÝEC‹Æ’†‚Å–¢s“®‚Æ‚È‚éB
0078`007F,00F8`00FF‚ÉÝ’è‚·‚é‚ÆˆÚ“®—Í‘‰ÁE”EŽÒC‹ÆÏ‚ÝEC‹Æ’†‚Ås“®Ï‚Ý‚Æ‚È‚éB
*/

#pragma pack()
