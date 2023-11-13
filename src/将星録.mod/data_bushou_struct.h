#pragma once



#define 武将情報アドレス 0x542348

#pragma pack(1)
struct NB7武将情報型
{
	char 苗字[7];	// 苗字
	char 名前[7];	// 名前
	char 姓名[14];	// 苗字＋名前
	int* p居城;      // 拠点メモリデータへのポインタ(城配列への特定のindexの場所を直接さしている。
	int 身分;      // 5:大名、4:宿老、3:家老、2:部将、1:侍大将、0:足軽頭   (浪人や未登場でも0が入っている、ただし、状態で調べるのが確実)
	int 生年;      // 西暦で
	int 元服年;    // 西暦で
	int 仕官;      // 西暦で (未士官だと0が入っている。ただし、士官してるかは0ではなく状態で調べるのが確実)
	int 寿命;      // 0〜7
	int 義理;      // 0x00〜0x0F (0〜15)
	int 相性;      // 0x00〜0x15 (0〜21)
	int 勲功;      // 大名、宿老:500以上、家老:300以上、部将:150以上、侍大将:50以上、足軽頭:0以上
	int 最大勲功;  // 基本的に500(=0x1F4)。という数値が入っている。
	int 忠誠;      // 0〜100
	int 最大忠誠;  // 基本100が入っている?
	int 政治;      // 0〜110
	int 最大政治;  // 110が入っている?
	int 戦闘;      // 0〜110
	int 最大戦闘;  // 110が入っている?
	int 智謀;      // 0〜110
	int 最大智謀;  // 110が入っている?
	int 足軽適性;  // 01〜06 "E"〜"S"
	int 騎馬適性;  // 01〜06 "E"〜"S"
	int 鉄砲適性;  // 01〜06 "E"〜"S"
	int 水軍適性;  // 01〜06 "E"〜"S"
	int 顔番号;    // 顔グラID。Excelより1つ小さな値。0オリジン。信長が0、秀吉が5といった値となる。
	int 状態;      // 未登場武将は登場城の城ID　0:大名、1:現役、2:独立勢力、3:浪人、4:歴史上の姫・婚姻用の姫、5:未登場の武将・姫、 6:一向一揆勢力、7:一揆勢力、8:待機・死亡
	int 性別;      // 0:男、1:女
	int 職業;      // 0:忍者、1:茶人、2:剣豪、3:僧侶、4:切支丹、-1:無職  たとえ-1でも「修行」で忍者になっている場合もある。
	int 一門;      // 一門衆�ａi例：子供・兄弟武将などのコードを参照すると良い）。255は特別な血縁がない番号。
	int unknown8;   // 謎
	int unknown9;   // 謎
	int unknown10;  // 謎
	int* pUnknown1; // 謎のポインタ1
	int* pUnknown2; // 謎のポインタ2
	int unknown11;  // 謎
	WORD unknown12; // 謎
	bool 内技農業 : 1;      // 内政特技
	bool 内技商業 : 1;      // 内政特技
	bool 内技建設 : 1;      // 内政特技
	bool 内技外交 : 1;      // 内政特技
	bool 内技登用 : 1;      // 内政特技
	bool 戦技抜穴 : 1;      // 内政特技
	bool unused3 : 1;      // 内政特技
	bool unused4 : 1;      // 内政特技
	BYTE unused5;
	bool 戦技騎突 : 1;      // 戦闘特技
	bool 戦技三段 : 1;      // 戦闘特技
	bool 戦技焙烙 : 1;      // 戦闘特技
	bool 戦技騎鉄 : 1;      // 戦闘特技
	bool unused6 : 1;      // 戦闘特技
	bool unused7 : 1;      // 戦闘特技
	bool unused8 : 1;      // 戦闘特技
	bool unused9 : 1;      // 戦闘特技
	BYTE unused2;
	/*
	*/
	WORD 農経;      // 農業の経験値、一定値で技能習得，高いと期間短縮
	WORD 商経;      // 商業の経験値、一定値で技能習得，高いと期間短縮
	WORD 建経;      // 建設の経験値、一定値で技能習得，高いと期間短縮
	int 武将番号;   // 武将配列の番号+1。1オリジン。この値は変更するべきではない。
	int 最大武将番号; // 0x2E8 = 744が全ての武将で入っていると思われる。農民なども含まれるので、通常ではこの値は利用せず、最大数::武将情報::配列数(=732)を利用すること
	int unknown15;  // 謎
	int 最大武将番号2; // 0x2E8 = 744が全ての武将で入っていると思われる。農民なども含まれるので、通常ではこの値は利用せず、最大数::武将情報::配列数(=732)を利用すること
	int *p次の武将; // 次の武将へのポインタ。最後の武将の場合は0x5694B0が入っている。全武将が綺麗に繋がっているというわけではないので、この値は利用しないこと。
	/*
	
	
	int 番号;      // ユニット�ａｨ（移動ユニット，農業ユニット）
	int 夫婦;      // 夫には妻の、妻には夫の武将�ｂ�入れる
	int 父親;      // 父親の武将�ａi例：武田信玄：DB.07）
	int 序列;      // 居城での在城武将の順番
	int 怨恨;      // 勧誘を受けても絶対に仕官しない勢力�ａi滅亡させられた勢力�ａj
	int 口調;      // 本人の口調（0〜7）→（0:無口、1:礼儀、2:粗暴、3:高貴、4:生意気、5:威厳、6:饒舌、7:一般）
	int 所属;      // お家再興ｲﾍﾞﾝﾄ時の旧主の武将��(一門衆:大名武将��)
	int unknown1;  // 謎のデータ
	int 移動力増加;  // ※参照
	int unknown2;  // 謎のデータ
	*/
};
#pragma pack()

/*
0000〜0007,0080〜0087に設定すると未行動となる。
0008〜000F,0088〜008Fに設定すると行動済みとなる。
0010〜0017,0090〜0097に設定すると修業中で未行動となる。
0018〜001F,0098〜009Fに設定すると修業中で行動済みとなる。
0020〜0027,00A0〜00A7に設定すると移動力増加済みで未行動となる。
0028〜002F,00A8〜00AFに設定すると移動力増加済みで行動済みとなる。
0030〜0037,00B0〜00B7に設定すると移動力増加済み・修業中で未行動となる。
0038〜003F,00B8〜00BFに設定すると移動力増加済み・修業中で行動済みとなる。
0040〜0047,00C0〜00C7に設定すると忍者修業済みで未行動となる。
0048〜004F,00C8〜00CFに設定すると忍者修業済みで行動済みとなる。
0050〜0057,00D0〜00D7に設定すると忍者修業済み・修業中で未行動となる。
0058〜005F,00D8〜00DFに設定すると忍者修業済み・修業中で行動済みとなる。
0060〜0067,00E0〜00E7に設定すると移動力増加・忍者修業済みで未行動となる。
0068〜006F,00E8〜00EFに設定すると移動力増加・忍者修業済みで行動済みとなる。
0070〜0077,00F0〜00F7に設定すると移動力増加・忍者修業済み・修業中で未行動となる。
0078〜007F,00F8〜00FFに設定すると移動力増加・忍者修業済み・修業中で行動済みとなる。
*/

/*
0054D808  89 48 8E C4 00 00 00 8F 47 8B 67 00 00 00 89 48  羽柴...秀吉...羽
0054D818  8E C4 8F 47 8B 67 00 00 00 00 00 00 98 CB 5D 00  柴秀吉......侏].
0054D828  00 00 00 00 00 06 00 00 13 06 00 00 00 00 00 00  .............
0054D838  03 00 00 00 09 00 00 00 00 00 00 00 00 00 00 00  ...............
0054D848  F4 01 00 00 32 00 00 00 64 00 00 00 64 00 00 00  ・..2...d...d...
0054D858  6E 00 00 00 50 00 00 00 6E 00 00 00 5E 00 00 00  n...P...n...^...
0054D868  6E 00 00 00 05 00 00 00 03 00 00 00 04 00 00 00  n............
0054D878  01 00 00 00 05 00 00 00 05 00 00 00 00 00 00 00  .............
0054D888  FF FF FF FF 1A 00 00 00 D8 07 00 00 00 00 00 00  ����...ﾘ......
0054D898  06 00 00 00 B8 8E 53 00 B0 94 56 00 1B 00 00 00  ...ｸ惨.ｰ之....
0054D8A8  00 00 3F 00 02 00 00 00 00 00 00 00 F2 00 00 00  ..?........・..
0054D8B8  E8 02 00 00 00 00 00 00 E8 02 00 00 B0 94 56 00  ・......・..ｰ之.
0054D8C8  89 48 8E C4 00 00 00 8F 47 92 B7 00 00 00 89 48  羽柴...秀長...羽
0054D8D8  8E C4 8F 47 92 B7 00 00 00 00 00 00 98 CB 5D 00  柴秀長......侏].
0054D8E8  00 00 00 00 04 06 00 00 17 06 00 00 00 00 00 00  ............
0054D8F8  02 00 00 00 0D 00 00 00 00 00 00 00 00 00 00 00  ...............
0054D908  F4 01 00 00 32 00 00 00 64 00 00 00 5C 00 00 00  ・..2...d...\...
0054D918  6E 00 00 00 4B 00 00 00 6E 00 00 00 54 00 00 00  n...K...n...T...
0054D928  6E 00 00 00 04 00 00 00 03 00 00 00 04 00 00 00  n............
0054D938  03 00 00 00 63 00 00 00 05 00 00 00 00 00 00 00  ...c..........
0054D948  FF FF FF FF 1A 00 00 00 D8 07 00 00 00 00 00 00  ����...ﾘ......
0054D958  01 00 00 00 B8 8E 53 00 B0 94 56 00 1B 00 00 00  ...ｸ惨.ｰ之....
0054D968  00 00 3D 00 02 00 00 00 00 00 00 00 F3 00 00 00  ..=........・..
0054D978  E8 02 00 00 00 00 00 00 E8 02 00 00 B0 94 56 00  ・......・..ｰ之.
0054D988  89 48 8E C4 00 00 00 8F 47 8E 9F 00 00 00 89 48  羽柴...秀次...羽
0054D998  8E C4 8F 47 8E 9F 00 00 00 00 00 00 98 CB 5D 00  柴秀次......侏].
0054D9A8  00 00 00 00 20 06 00 00 33 06 00 00 00 00 00 00  .... ..3......
0054D9B8  03 00 00 00 06 00 00 00 00 00 00 00 00 00 00 00  ..............
0054D9C8  F4 01 00 00 32 00 00 00 64 00 00 00 3B 00 00 00  ・..2...d...;...
0054D9D8  6E 00 00 00 3F 00 00 00 6E 00 00 00 23 00 00 00  n...?...n...#...
0054D9E8  6E 00 00 00 03 00 00 00 02 00 00 00 03 00 00 00  n............
0054D9F8  01 00 00 00 2C 01 00 00 05 00 00 00 00 00 00 00  ...,.........
0054DA08  FF FF FF FF 1A 00 00 00 00 00 00 00 00 00 00 00  ����...........
0054DA18  02 00 00 00 B8 8E 53 00 B0 94 56 00 1B 00 00 00  ...ｸ惨.ｰ之....
0054DA28  00 00 24 00 00 00 00 00 00 00 00 00 F4 00 00 00  ..$.........・..
0054DA38  E8 02 00 00 00 00 00 00 E8 02 00 00 B0 94 56 00  ・......・..ｰ之.
0054DA48  96 4C 90 62 00 00 00 8F 47 97 8A 00 00 00 96 4C  豊臣...秀頼...豊
0054DA58  90 62 8F 47 97 8A 00 00 00 00 00 00 98 CB 5D 00  臣秀頼......侏].
0054DA68  00 00 00 00 39 06 00 00 4C 06 00 00 00 00 00 00  ....9..L......
0054DA78  03 00 00 00 0A 00 00 00 00 00 00 00 00 00 00 00  ...............
0054DA88  F4 01 00 00 32 00 00 00 64 00 00 00 46 00 00 00  ・..2...d...F...
0054DA98  6E 00 00 00 32 00 00 00 6E 00 00 00 3C 00 00 00  n...2...n...<...
0054DAA8  6E 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00  n............
0054DAB8  01 00 00 00 B2 00 00 00 05 00 00 00 00 00 00 00  ...ｲ..........
0054DAC8  FF FF FF FF 1A 00 00 00 F2 00 00 00 00 00 00 00  ����...・......
0054DAD8  00 00 00 00 B8 8E 53 00 B0 94 56 00 1B 00 00 00  ....ｸ惨.ｰ之....
0054DAE8  00 00 30 00 00 00 00 00 00 00 00 00 F5 00 00 00  ..0.........・..
0054DAF8  E8 02 00 00 00 00 00 00 E8 02 00 00 B0 94 56 00  ・......・..ｰ之.
0054DB08  96 D8 89 BA 00 00 00 8F 9F 8F 72 00 00 00 96 D8  木下...勝俊...木
0054DB18  89 BA 8F 9F 8F 72 00 00 00 00 00 00 98 CB 5D 00  下勝俊......侏].
0054DB28  00 00 00 00 21 06 00 00 34 06 00 00 00 00 00 00  ....!..4......
0054DB38  05 00 00 00 04 00 00 00 0B 00 00 00 00 00 00 00  .............
0054DB48  F4 01 00 00 32 00 00 00 64 00 00 00 3D 00 00 00  ・..2...d...=...
0054DB58  6E 00 00 00 1A 00 00 00 6E 00 00 00 2D 00 00 00  n......n...-...
0054DB68  6E 00 00 00 02 00 00 00 01 00 00 00 01 00 00 00  n............
0054DB78  01 00 00 00 DA 01 00 00 05 00 00 00 00 00 00 00  ...ﾚ.........
0054DB88  FF FF FF FF 1A 00 00 00 D9 07 00 00 00 00 00 00  ����...ﾙ......
0054DB98  06 00 00 00 B8 8E 53 00 B0 94 56 00 0B 00 00 00  ...ｸ惨.ｰ之....
0054DBA8  00 00 02 00 00 00 00 00 00 00 00 00 F6 00 00 00  ...........・..
0054DBB8  E8 02 00 00 00 00 00 00 E8 02 00 00 B0 94 56 00  ・......・..ｰ之.
0054DBC8  8F AC 91 81 90 EC 00 8F 47 8F 48 00 00 00 8F AC  小早川.秀秋...小
0054DBD8  91 81 90 EC 8F 47 8F 48 00 00 00 00 98 CB 5D 00  早川秀秋....侏].
0054DBE8  00 00 00 00 2E 06 00 00 41 06 00 00 00 00 00 00  .......A......
0054DBF8  00 00 00 00 06 00 00 00 0B 00 00 00 00 00 00 00  ..............
0054DC08  F4 01 00 00 32 00 00 00 64 00 00 00 35 00 00 00  ・..2...d...5...
0054DC18  6E 00 00 00 43 00 00 00 6E 00 00 00 2D 00 00 00  n...C...n...-...
0054DC28  6E 00 00 00 03 00 00 00 02 00 00 00 02 00 00 00  n............
0054DC38  01 00 00 00 82 00 00 00 05 00 00 00 00 00 00 00  ...・.........
0054DC48  FF FF FF FF 1A 00 00 00 D9 07 00 00 00 00 00 00  ����...ﾙ......
0054DC58  00 00 00 00 B8 8E 53 00 B0 94 56 00 0B 00 00 00  ....ｸ惨.ｰ之....
0054DC68  00 00 04 00 00 00 00 00 00 00 00 00 F7 00 00 00  ...........・..
*/

/*

00542348  蠣崎...季広...蠣崎季広......俤]....・..・..・...........・..
00542388  ・..d...d...M...n...8...n...J...n...............W...........
005423C8  ����...............ｸ惨.ｰ之..................・......・..ｰ之.
00542408  松前...慶広...松前慶広......俤].........................
00542448  ・..X...d...T...n...2...n...U...n...............ﾎ..........
*/

/*
00552908  92 B7 94 F6 00 00 00 8C 69 8C D5 00 00 00 92 B7  長尾...景虎...長
00552918  94 F6 8C 69 8C D5 00 00 00 00 00 00 28 D5 5D 00  尾景虎......(ﾕ].
00552928  05 00 00 00 FA 05 00 00 08 06 00 00 08 06 00 00  ...・......
00552938  02 00 00 00 0F 00 00 00 0E 00 00 00 F4 01 00 00  .........・..
00552948  F4 01 00 00 64 00 00 00 64 00 00 00 46 00 00 00  ・..d...d...F...
00552958  6E 00 00 00 69 00 00 00 6E 00 00 00 48 00 00 00  n...i...n...H...
00552968  6E 00 00 00 04 00 00 00 06 00 00 00 02 00 00 00  n............
00552978  01 00 00 00 1A 00 00 00 00 00 00 00 00 00 00 00  ..............
00552988  FF FF FF FF 21 00 00 00 00 00 00 00 00 00 00 00  ����!...........
00552998  00 00 00 00 B8 8E 53 00 B0 94 56 00 17 00 00 00  ....ｸ惨.ｰ之....
005529A8  00 04 36 00 01 00 00 00 00 00 00 00 5E 01 00 00  .6........^..
005529B8  E8 02 00 00 00 00 00 00 E8 02 00 00 C8 29 55 00  ・......・..ﾈ)U.
005529C8  8F E3 90 99 00 00 00 8C 69 90 4D 00 00 00 8F E3  上杉...景信...上
005529D8  90 99 8C 69 90 4D 00 00 00 00 00 00 28 D5 5D 00  杉景信......(ﾕ].
005529E8  01 00 00 00 F7 05 00 00 05 06 00 00 05 06 00 00  ...・......
005529F8  03 00 00 00 06 00 00 00 0A 00 00 00 32 00 00 00  ..........2...
00552A08  F4 01 00 00 5C 00 00 00 64 00 00 00 42 00 00 00  ・..\...d...B...
00552A18  6E 00 00 00 2F 00 00 00 6E 00 00 00 3B 00 00 00  n.../...n...;...
00552A28  6E 00 00 00 02 00 00 00 03 00 00 00 01 00 00 00  n............
00552A38  01 00 00 00 08 02 00 00 01 00 00 00 00 00 00 00  ............
00552A48  FF FF FF FF 21 00 00 00 00 00 00 00 00 00 00 00  ����!...........
00552A58  06 00 00 00 B8 8E 53 00 08 29 55 00 07 00 00 00  ...ｸ惨.)U....
00552A68  00 00 22 00 01 00 00 00 00 00 00 00 5F 01 00 00  .."........_..
00552A78  E8 02 00 00 00 00 00 00 E8 02 00 00 88 2A 55 00  ・......・..・U.
00552A88  8A 60 8D E8 00 00 00 8C 69 89 C6 00 00 00 8A 60  柿崎...景家...柿
00552A98  8D E8 8C 69 89 C6 00 00 00 00 00 00 28 D5 5D 00  崎景家......(ﾕ].
00552AA8  02 00 00 00 E9 05 00 00 F7 05 00 00 F7 05 00 00  ...・..・..・..
00552AB8  04 00 00 00 07 00 00 00 0E 00 00 00 96 00 00 00  .........・..
00552AC8  F4 01 00 00 50 00 00 00 64 00 00 00 22 00 00 00  ・..P...d..."...
00552AD8  6E 00 00 00 60 00 00 00 6E 00 00 00 0A 00 00 00  n...`...n.......
00552AE8  6E 00 00 00 02 00 00 00 05 00 00 00 01 00 00 00  n............
00552AF8  01 00 00 00 F2 00 00 00 01 00 00 00 00 00 00 00  ...・.........
00552B08  FF FF FF FF FF 00 00 00 00 00 00 00 00 00 00 00  �����...........
00552B18  02 00 00 00 B8 8E 53 00 08 29 55 00 17 00 00 00  ...ｸ惨.)U....
00552B28  00 04 00 00 01 00 00 00 00 00 00 00 60 01 00 00  ..........`..
00552B38  E8 02 00 00 00 00 00 00 E8 02 00 00 C8 2F 55 00  ・......・..ﾈ/U.
00552B48  89 46 8D B2 94 FC 00 92 E8 96 9E 00 00 00 89 46  宇佐美.定満...宇
*/

/*
00563048  8D D6 93 A1 00 00 00 8B 41 92 B1 00 00 00 8D D6  斎藤...帰蝶...斎
00563058  93 A1 8B 41 92 B1 00 00 00 00 00 00 98 CB 5D 00  藤帰蝶......侏].
00563068  00 00 00 00 FF 05 00 00 0A 06 00 00 0A 06 00 00  ....�........
00563078  05 00 00 00 0C 00 00 00 00 00 00 00 00 00 00 00  ...............
00563088  F4 01 00 00 52 00 00 00 64 00 00 00 32 00 00 00  ・..R...d...2...
00563098  6E 00 00 00 32 00 00 00 6E 00 00 00 32 00 00 00  n...2...n...2...
005630A8  6E 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00  n............
005630B8  01 00 00 00 BC 02 00 00 04 00 00 00 01 00 00 00  ...ｼ........
005630C8  FF FF FF FF 1B 00 00 00 0C 01 00 00 C7 00 00 00  ����......ﾇ...
005630D8  01 00 00 00 B8 8E 53 00 C8 B7 54 00 0F 00 00 00  ...ｸ惨.ﾈｷT....
005630E8  00 00 00 00 00 00 00 00 00 00 00 00 BD 02 00 00  ............ｽ..
005630F8  E8 02 00 00 00 00 00 00 E8 02 00 00 B0 94 56 00  ・......・..ｰ之.
00563108  90 44 93 63 00 00 00 8E 73 00 00 00 00 00 90 44  織田...市.....織
00563118  93 63 8E 73 00 00 00 00 00 00 00 00 98 CB 5D 00  田市........侏].
00563128  00 00 00 00 0C 06 00 00 17 06 00 00 17 06 00 00  ...........
00563138  03 00 00 00 0C 00 00 00 00 00 00 00 00 00 00 00  ...............
00563148  F4 01 00 00 52 00 00 00 64 00 00 00 32 00 00 00  ・..R...d...2...
00563158  6E 00 00 00 32 00 00 00 6E 00 00 00 32 00 00 00  n...2...n...2...
00563168  6E 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00  n............
00563178  01 00 00 00 BD 02 00 00 05 00 00 00 01 00 00 00  ...ｽ........
00563188  FF FF FF FF 00 00 00 00 D7 07 00 00 00 00 00 00  ����....ﾗ......
00563198  01 00 00 00 B8 8E 53 00 B0 94 56 00 0F 00 00 00  ...ｸ惨.ｰ之....
005631A8  00 00 00 00 00 00 00 00 00 00 00 00 BE 02 00 00  ............ｾ..
005631B8  E8 02 00 00 00 00 00 00 E8 02 00 00 B0 94 56 00  ・......・..ｰ之.
005631C8  90 44 93 63 00 00 00 8C DC 93 BF 00 00 00 90 44  織田...五徳...織
005631D8  93 63 8C DC 93 BF 00 00 00 00 00 00 98 CB 5D 00  田五徳......侏].
005631E8  00 00 00 00 17 06 00 00 22 06 00 00 22 06 00 00  ......".."..
005631F8  05 00 00 00 0C 00 00 00 00 00 00 00 00 00 00 00  ...............
00563208  F4 01 00 00 52 00 00 00 64 00 00 00 32 00 00 00  ・..R...d...2...
00563218  6E 00 00 00 32 00 00 00 6E 00 00 00 32 00 00 00  n...2...n...2...
00563228  6E 00 00 00 01 00 00 00 01 00 00 00 01 00 00 00  n............
*/


/*
00563C48  8D C9 91 8A 00 F1 00 83 B3 83 B4 83 B5 00 8D C9  宰相.・ΦΧΨ.宰
00563C58  91 8A 83 B3 83 B4 83 B5 00 00 00 00 98 CB 5D 00  相ΦΧΨ....侏].
00563C68  00 00 00 00 FF 05 00 00 11 06 00 00 0D 06 00 00  ....�.......
00563C78  02 00 00 00 08 00 00 00 00 00 00 00 00 00 00 00  ..............
00563C88  F4 01 00 00 32 00 00 00 64 00 00 00 6A 00 00 00  ・..2...d...j...
00563C98  6E 00 00 00 6E 00 00 00 6E 00 00 00 6A 00 00 00  n...n...n...j...
00563CA8  6E 00 00 00 06 00 00 00 06 00 00 00 06 00 00 00  n............
00563CB8  06 00 00 00 CC 02 00 00 01 00 00 00 01 00 00 00  ...ﾌ........
00563CC8  FF FF FF FF FF 00 00 00 00 00 00 00 00 00 00 00  �����...........
00563CD8  01 00 00 00 B8 8E 53 00 B0 94 56 00 06 00 00 00  ...ｸ惨.ｰ之....
00563CE8  00 40 3F 00 0F 00 03 98 02 30 02 6C CD 02 00 00  .@?..・0lﾍ..
00563CF8  E8 02 00 00 00 00 00 00 E8 02 00 00 B0 94 56 00  ・......・..ｰ之.
00563D08  95 50 82 E0 82 F1 00 93 F1 00 00 00 00 00 95 50  姫もん.二.....姫
00563D18  82 E0 82 F1 93 F1 00 00 00 00 00 00 00 90 53 00  もん二.......心.
00563D28  00 00 00 00 0F 06 00 00 1A 06 00 00 00 00 00 00  ............
00563D38  02 00 00 00 08 00 00 00 00 00 00 00 00 00 00 00  ..............
*/

