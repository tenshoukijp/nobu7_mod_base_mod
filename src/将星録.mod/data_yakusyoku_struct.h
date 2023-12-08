#pragma once

#include <windows.h>

#define 役職情報アドレス 0x585398

#define 役職所有者なし 0x538EB8

#pragma pack(1)
struct NB7役職情報型 {
	char 役職名[12];  // 役職名
	int 役位;    // 6が征夷大将軍、 0は羽州探題
	int* p所有大名;      // 所有大名へのポインタ(大名情報の配列の該当大名の情報の位置を直接指している) [B8 8E 53] = 0x538EB8 なら誰も所持していない
	int 役職番号;      // 役職番号
	int 役職数;    // 官位の総数。7個なので、7という値が全てのデータに入っている。
};
#pragma pack()

BOOL isValidYakusyokuID(int iYakusyokuID);

// 役職IDからそれを所有している武将IDを取得する。もってなかったら0xFFFF
int getDaimyoIDFromYakusyokuID(int iYakusyokuID);

BOOL setDaimyoIDToYakusyokuID(int iYakusyokuID, int iBushouID);

BOOL setYakusyokuName(int iYakusyokuID, std::string strYakusyokuName);

/*
00585398  90 AA 88 CE 91 E5 8F AB 8C 52 00 00 06 00 00 00  征夷大将軍.....
005853A8  80 BB 56 00 01 00 00 00 07 00 00 00 8A C7 97 CC  �ｻV.......管領
005853B8  00 00 00 00 00 00 00 00 05 00 00 00 B8 8E 53 00  ...........ｸ惨.
005853C8  02 00 00 00 07 00 00 00 8A D6 93 8C 8A C7 97 CC  ......関東管領
005853D8  00 00 00 00 04 00 00 00 60 A7 56 00 03 00 00 00  .......`ｧV....
005853E8  07 00 00 00 89 9C 8F 42 92 54 91 E8 00 00 00 00  ...奥州探題....
005853F8  03 00 00 00 0E 9C 56 00 04 00 00 00 07 00 00 00  ...弖.......
00585408  90 BC 8D 91 92 54 91 E8 00 00 00 00 02 00 00 00  西国探題.......
00585418  B8 8E 53 00 05 00 00 00 07 00 00 00 8B E3 8F 42  ｸ惨.......九州
00585428  92 54 91 E8 00 00 00 00 01 00 00 00 B8 8E 53 00  探題.......ｸ惨.
00585438  06 00 00 00 07 00 00 00 89 48 8F 42 92 54 91 E8  ......羽州探題
00585448  00 00 00 00 00 00 00 00 B8 8E 53 00 07 00 00 00  ........ｸ惨....
00585458  07 00 00 00 00 00 00 00                          .......


*/