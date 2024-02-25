#pragma once

#include <windows.h>


#define 官位情報アドレス 0x585460

#define 官位所有者なし (int *)0x5694B0

#pragma pack(1)
struct NB7官位情報型 {
	char 官位名[14];  // 官位名
	int 階位;    // 22が関白、 0は主膳佑  22が正一位、0が従八位下
	int* p所有者;      // 所有武将へのポインタ(武将情報の配列の該当武将の情報の位置を直接指している) [B0 94 56]= 0x05694B0 だと誰も所有してない
	int 官位番号;      // 官位番号
	int 官位数;    // 官位の総数。FA000000 = (250)が全てのデータに入っている。
};
#pragma pack()

BOOL isValidKanniID(int iKanniID);

BOOL setKanniName(int iKanniID, std::string strKanniName);

// 官位IDからそれを所有している武将IDを取得する。もってなかったら0xFFFF
int getBushouIDFromKanniID(int iKanniID);

// 特定の武将に官位をセットする。(能力の変動は伴わない)。iBushouIDに0xFFFFをセットした場合は朝廷を所有者とする（ようする所有者なし）とする。
BOOL setBushouIDToKanniID(int iKanniID, int iBushouID);

/*
00585460  8A D6 94 92 00 00 00 00 00 00 00 00 00 00 16 00  関白...........
00585470  00 00 B0 94 56 00 01 00 00 00 FA 00 00 00 91 BE  ..ｰ之....・..太
00585480  90 AD 91 E5 90 62 00 00 00 00 00 00 15 00 00 00  政大臣.........
00585490  B0 94 56 00 02 00 00 00 FA 00 00 00 8D B6 91 E5  ｰ之....・..左大
005854A0  90 62 00 00 00 00 00 00 00 00 14 00 00 00 B0 94  臣...........ｰ・
005854B0  56 00 03 00 00 00 FA 00 00 00 89 45 91 E5 90 62  V....・..右大臣
005854C0  00 00 00 00 00 00 00 00 14 00 00 00 B0 94 56 00  ...........ｰ之.
005854D0  04 00 00 00 FA 00 00 00 93 E0 91 E5 90 62 00 00  ...・..内大臣..
005854E0  00 00 00 00 00 00 13 00 00 00 B0 94 56 00 05 00  .........ｰ之..
005854F0  00 00 FA 00 00 00 91 E5 94 5B 8C BE 00 00 00 00  ..・..大納言....
00585500  00 00 00 00 12 00 00 00 B0 94 56 00 06 00 00 00  .......ｰ之....
00585510  FA 00 00 00 8C A0 91 E5 94 5B 8C BE 00 00 00 00  ・..権大納言....
00585520  00 00 12 00 00 00 B0 94 56 00 07 00 00 00 FA 00  .....ｰ之....・
00585530  00 00 8C A0 91 E5 94 5B 8C BE 00 00 00 00 00 00  ..権大納言......
00585540  12 00 00 00 B0 94 56 00 08 00 00 00 FA 00 00 00  ...ｰ之....・..
00585550  92 86 94 5B 8C BE 00 00 00 00 00 00 00 00 11 00  中納言.........
00585560  00 00 B0 94 56 00 09 00 00 00 FA 00 00 00 92 86  ..ｰ之.....・..中
00585570  94 5B 8C BE 00 00 00 00 00 00 00 00 11 00 00 00  納言...........
00585580  B0 94 56 00 0A 00 00 00 FA 00 00 00 8C A0 92 86  ｰ之.....・..権中
00585590  94 5B 8C BE 00 00 00 00 00 00 11 00 00 00 B0 94  納言.........ｰ・
005855A0  56 00 0B 00 00 00 FA 00 00 00 8C A0 92 86 94 5B  V....・..権中納
005855B0  8C BE 00 00 00 00 00 00 11 00 00 00 B0 94 56 00  言.........ｰ之.
005855C0  0C 00 00 00 FA 00 00 00 8C A0 92 86 94 5B 8C BE  ....・..権中納言
005855D0  00 00 00 00 00 00 11 00 00 00 B0 94 56 00 0D 00  .........ｰ之...
005855E0  00 00 FA 00 00 00 92 65 90 B3 9B 9A 00 00 00 00  ..・..弾正尹....
005855F0  00 00 00 00 11 00 00 00 B0 94 56 00 0E 00 00 00  .......ｰ之....
00585600  FA 00 00 00 8D B6 8B DF 89 71 91 E5 8F AB 00 00  ・..左近衛大将..
00585610  00 00 11 00 00 00 B0 94 56 00 0F 00 00 00 FA 00  .....ｰ之....・
00585620  00 00 89 45 8B DF 89 71 91 E5 8F AB 00 00 00 00  ..右近衛大将....
00585630  11 00 00 00 B0 94 56 00 10 00 00 00 FA 00 00 00  ...ｰ之....・..
00585640  91 BE 8D C9 90 83 00 00 00 00 00 00 00 00 11 00  太宰帥.........
00585650  00 00 B0 94 56 00 11 00 00 00 FA 00 00 00 92 86  ..ｰ之....・..中
00585660  96 B1 8B A8 00 00 00 00 00 00 00 00 10 00 00 00  務卿...........
00585670  B0 94 56 00 12 00 00 00 FA 00 00 00 8E 51 8B 63  ｰ之....・..参議
00585680  00 00 00 00 00 00 00 00 00 00 0F 00 00 00 C8 62  .............ﾈb
00585690  55 00 13 00 00 00 FA 00 00 00 8E 51 8B 63 00 00  U....・..参議..
005856A0  00 00 00 00 00 00 00 00 0F 00 00 00 B0 94 56 00  ...........ｰ之.
005856B0  14 00 00 00 FA 00 00 00 8E 51 8B 63 00 00 00 00  ...・..参議....
005856C0  00 00 00 00 00 00 0F 00 00 00 B0 94 56 00 15 00  .........ｰ之..
005856D0  00 00 FA 00 00 00 8E 51 8B 63 00 00 00 00 00 00  ..・..参議......
005856E0  00 00 00 00 0F 00 00 00 B0 94 56 00 16 00 00 00  .......ｰ之....
005856F0  FA 00 00 00 8E AE 95 94 8B A8 00 00 00 00 00 00  ・..式部卿......
00585700  00 00 0F 00 00 00 B0 94 56 00 17 00 00 00 FA 00  .....ｰ之....・
00585710  00 00 8E A1 95 94 8B A8 00 00 00 00 00 00 00 00  ..治部卿........
00585720  0F 00 00 00 B0 94 56 00 18 00 00 00 FA 00 00 00  ...ｰ之....・..
00585730  96 AF 95 94 8B A8 00 00 00 00 00 00 00 00 0F 00  民部卿.........
00585740  00 00 B0 94 56 00 19 00 00 00 FA 00 00 00 95 BA  ..ｰ之....・..兵
00585750  95 94 8B A8 00 00 00 00 00 00 00 00 0F 00 00 00  部卿...........
00585760  48 CA 55 00 1A 00 00 00 FA 00 00 00 8C 59 95 94  HﾊU....・..刑部
00585770  8B A8 00 00 00 00 00 00 00 00 0F 00 00 00 B0 94  卿...........ｰ・
00585780  56 00 1B 00 00 00 FA 00 00 00 91 E5 91 A0 8B A8  V....・..大蔵卿
00585790  00 00 00 00 00 00 00 00 0F 00 00 00 B0 94 56 00  ...........ｰ之.
005857A0  1C 00 00 00 FA 00 00 00 8B 7B 93 E0 8B A8 00 00  ...・..宮内卿..
005857B0  00 00 00 00 00 00 0F 00 00 00 B0 94 56 00 1D 00  .........ｰ之..
005857C0  00 00 FA 00 00 00 8F 43 97 9D 91 E5 95 76 00 00  ..・..修理大夫..
005857D0  00 00 00 00 0E 00 00 00 C8 6E 55 00 1E 00 00 00  .......ﾈnU....
005857E0  FA 00 00 00 8D B6 8B 9E 91 E5 95 76 00 00 00 00  ・..左京大夫....
005857F0  00 00 0E 00 00 00 08 30 54 00 1F 00 00 00 FA 00  .....0T....・
00585800  00 00 89 45 8B 9E 91 E5 95 76 00 00 00 00 00 00  ..右京大夫......
00585810  0E 00 00 00 08 5A 54 00 20 00 00 00 FA 00 00 00  ...ZT. ...・..
00585820  92 65 90 B3 91 E5 95 4A 00 00 00 00 00 00 0E 00  弾正大弼.......
00585830  00 00 48 44 54 00 21 00 00 00 FA 00 00 00 8D B6  ..HDT.!...・..左
00585840  8B DF 89 71 92 86 8F AB 00 00 00 00 0E 00 00 00  近衛中将.......
00585850  C8 F3 54 00 22 00 00 00 FA 00 00 00 8D B6 8B DF  ﾈ�T."...・..左近
00585860  89 71 92 86 8F AB 00 00 00 00 0E 00 00 00 B0 94  衛中将.......ｰ・
00585870  56 00 23 00 00 00 FA 00 00 00 8D B6 8B DF 89 71  V.#...・..左近衛
00585880  8C A0 92 86 8F AB 00 00 0E 00 00 00 B0 94 56 00  権中将.....ｰ之.
00585890  24 00 00 00 FA 00 00 00 8D B6 8B DF 89 71 8C A0  $...・..左近衛権
005858A0  92 86 8F AB 00 00 0E 00 00 00 B0 94 56 00 25 00  中将.....ｰ之.%.
005858B0  00 00 FA 00 00 00 89 45 8B DF 89 71 92 86 8F AB  ..・..右近衛中将
005858C0  00 00 00 00 0E 00 00 00 B0 94 56 00 26 00 00 00  .......ｰ之.&...
005858D0  FA 00 00 00 89 45 8B DF 89 71 92 86 8F AB 00 00  ・..右近衛中将..
005858E0  00 00 0E 00 00 00 B0 94 56 00 27 00 00 00 FA 00  .....ｰ之.'...・
005858F0  00 00 89 45 8B DF 89 71 8C A0 92 86 8F AB 00 00  ..右近衛権中将..
00585900  0E 00 00 00 B0 94 56 00 28 00 00 00 FA 00 00 00  ...ｰ之.(...・..
00585910  89 45 8B DF 89 71 8C A0 92 86 8F AB 00 00 0E 00  右近衛権中将...
00585920  00 00 B0 94 56 00 29 00 00 00 FA 00 00 00 8D B6  ..ｰ之.)...・..左
00585930  89 71 96 E5 93 C2 00 00 00 00 00 00 0E 00 00 00  衛門督.........
00585940  48 EE 55 00 2A 00 00 00 FA 00 00 00 89 45 89 71  H�q.*...・..右衛
00585950  96 E5 93 C2 00 00 00 00 00 00 0E 00 00 00 C8 8F  門督.........ﾈ・
00585960  55 00 2B 00 00 00 FA 00 00 00 8D B6 95 BA 89 71  U.+...・..左兵衛
00585970  93 C2 00 00 00 00 00 00 0E 00 00 00 B0 94 56 00  督.........ｰ之.
00585980  2C 00 00 00 FA 00 00 00 89 45 95 BA 89 71 93 C2  ,...・..右兵衛督
00585990  00 00 00 00 00 00 0E 00 00 00 B0 94 56 00 2D 00  .........ｰ之.-.
005859A0  00 00 FA 00 00 00 91 BE 8D C9 91 E5 93 F3 00 00  ..・..太宰大弐..
005859B0  00 00 00 00 0E 00 00 00 48 CA 55 00 2E 00 00 00  .......HﾊU.....
005859C0  FA 00 00 00 8A A8 89 F0 97 52 92 B7 8A AF 00 00  ・..勘解由長官..
005859D0  00 00 0E 00 00 00 B0 94 56 00 2F 00 00 00 FA 00  .....ｰ之./...・
005859E0  00 00 92 86 96 B1 91 E5 95 E3 00 00 00 00 00 00  ..中務大輔......
005859F0  0D 00 00 00 B0 94 56 00 30 00 00 00 FA 00 00 00  ....ｰ之.0...・..
00585A00  91 E5 91 56 91 E5 95 76 00 00 00 00 00 00 0D 00  大膳大夫........
00585A10  00 00 88 FD 54 00 31 00 00 00 FA 00 00 00 91 BE  ..・T.1...・..太
00585A20  8D C9 8F AD 93 F3 00 00 00 00 00 00 0D 00 00 00  宰少弐..........
00585A30  B0 94 56 00 32 00 00 00 FA 00 00 00 8E AE 95 94  ｰ之.2...・..式部
00585A40  91 E5 95 E3 00 00 00 00 00 00 0C 00 00 00 88 8A  大輔..........・
00585A50  55 00 33 00 00 00 FA 00 00 00 8E A1 95 94 91 E5  U.3...・..治部大
00585A60  95 E3 00 00 00 00 00 00 0C 00 00 00 48 92 54 00  輔..........H探.
00585A70  34 00 00 00 FA 00 00 00 96 AF 95 94 91 E5 95 E3  4...・..民部大輔
00585A80  00 00 00 00 00 00 0C 00 00 00 B0 94 56 00 35 00  ..........ｰ之.5.
00585A90  00 00 FA 00 00 00 95 BA 95 94 91 E5 95 E3 00 00  ..・..兵部大輔..
00585AA0  00 00 00 00 0C 00 00 00 08 65 55 00 36 00 00 00  ........eU.6...
00585AB0  FA 00 00 00 8C 59 95 94 91 E5 95 E3 00 00 00 00  ・..刑部大輔....
00585AC0  00 00 0C 00 00 00 B0 94 56 00 37 00 00 00 FA 00  ......ｰ之.7...・
00585AD0  00 00 91 E5 91 A0 91 E5 95 E3 00 00 00 00 00 00  ..大蔵大輔......
00585AE0  0C 00 00 00 B0 94 56 00 38 00 00 00 FA 00 00 00  ....ｰ之.8...・..
00585AF0  8B 7B 93 E0 91 E5 95 E3 00 00 00 00 00 00 0C 00  宮内大輔........
00585B00  00 00 B0 94 56 00 39 00 00 00 FA 00 00 00 92 65  ..ｰ之.9...・..弾
00585B10  90 B3 8F AD 95 4A 00 00 00 00 00 00 0C 00 00 00  正少弼..........
00585B20  08 29 55 00 3A 00 00 00 FA 00 00 00 8D B6 8B DF  )U.:...・..左近
00585B30  89 71 8F AD 8F AB 00 00 00 00 0C 00 00 00 88 EA  衛少将........一
00585B40  55 00 3B 00 00 00 FA 00 00 00 8D B6 8B DF 89 71  U.;...・..左近衛
00585B50  8F AD 8F AB 00 00 00 00 0C 00 00 00 B0 94 56 00  少将........ｰ之.
00585B60  3C 00 00 00 FA 00 00 00 8D B6 8B DF 89 71 8C A0  <...・..左近衛権
00585B70  8F AD 8F AB 00 00 0C 00 00 00 B0 94 56 00 3D 00  少将......ｰ之.=.
00585B80  00 00 FA 00 00 00 8D B6 8B DF 89 71 8C A0 8F AD  ..・..左近衛権少
00585B90  8F AB 00 00 0C 00 00 00 B0 94 56 00 3E 00 00 00  将......ｰ之.>...
00585BA0  FA 00 00 00 89 45 8B DF 89 71 8F AD 8F AB 00 00  ・..右近衛少将..
00585BB0  00 00 0C 00 00 00 B0 94 56 00 3F 00 00 00 FA 00  ......ｰ之.?...・
00585BC0  00 00 89 45 8B DF 89 71 8F AD 8F AB 00 00 00 00  ..右近衛少将....
00585BD0  0C 00 00 00 B0 94 56 00 40 00 00 00 FA 00 00 00  ....ｰ之.@...・..
00585BE0  89 45 8B DF 89 71 8C A0 8F AD 8F AB 00 00 0C 00  右近衛権少将....
00585BF0  00 00 B0 94 56 00 41 00 00 00 FA 00 00 00 89 45  ..ｰ之.A...・..右
00585C00  8B DF 89 71 8C A0 8F AD 8F AB 00 00 0C 00 00 00  近衛権少将......
00585C10  B0 94 56 00 42 00 00 00 FA 00 00 00 91 E5 98 61  ｰ之.B...・..大和
00585C20  8E E7 00 00 00 00 00 00 00 00 0B 00 00 00 48 25  守...........H%
00585C30  55 00 43 00 00 00 FA 00 00 00 89 CD 93 E0 8E E7  U.C...・..河内守
00585C40  00 00 00 00 00 00 00 00 0B 00 00 00 88 1D 56 00  ...........・V.
00585C50  44 00 00 00 FA 00 00 00 88 C9 90 A8 8E E7 00 00  D...・..伊勢守..
00585C60  00 00 00 00 00 00 0B 00 00 00 B0 94 56 00 45 00  .........ｰ之.E.
00585C70  00 00 FA 00 00 00 95 90 91 A0 8E E7 00 00 00 00  ..・..武蔵守....
00585C80  00 00 00 00 0B 00 00 00 B0 94 56 00 46 00 00 00  .......ｰ之.F...
00585C90  FA 00 00 00 89 BA 91 8D 8E E7 00 00 00 00 00 00  ・..下総守......
00585CA0  00 00 0B 00 00 00 88 82 54 00 47 00 00 00 FA 00  .....・T.G...・
00585CB0  00 00 8B DF 8D 5D 8E E7 00 00 00 00 00 00 00 00  ..近江守........
00585CC0  0B 00 00 00 B0 94 56 00 48 00 00 00 FA 00 00 00  ...ｰ之.H...・..
00585CD0  97 A4 89 9C 8E E7 00 00 00 00 00 00 00 00 0B 00  陸奥守.........
00585CE0  00 00 48 21 56 00 49 00 00 00 FA 00 00 00 89 7A  ..H!V.I...・..越
00585CF0  91 4F 8E E7 00 00 00 00 00 00 00 00 0B 00 00 00  前守...........
00585D00  88 24 55 00 4A 00 00 00 FA 00 00 00 94 64 96 81  ・U.J...・..播磨
00585D10  8E E7 00 00 00 00 00 00 00 00 0B 00 00 00 48 79  守...........Hy
00585D20  55 00 4B 00 00 00 FA 00 00 00 94 EC 8C E3 8E E7  U.K...・..肥後守
00585D30  00 00 00 00 00 00 00 00 0B 00 00 00 B0 94 56 00  ...........ｰ之.
00585D40  4C 00 00 00 FA 00 00 00 8F AD 94 5B 8C BE 00 00  L...・..少納言..
00585D50  00 00 00 00 00 00 0B 00 00 00 B0 94 56 00 4D 00  .........ｰ之.M.
00585D60  00 00 FA 00 00 00 8C A0 8F AD 94 5B 8C BE 00 00  ..・..権少納言..
00585D70  00 00 00 00 0B 00 00 00 B0 94 56 00 4E 00 00 00  .......ｰ之.N...
00585D80  FA 00 00 00 92 86 96 B1 8F AD 95 E3 00 00 00 00  ・..中務少輔....
00585D90  00 00 0B 00 00 00 08 8F 55 00 4F 00 00 00 FA 00  .....酋.O...・
00585DA0  00 00 90 7D 8F 91 93 AA 00 00 00 00 00 00 00 00  ..図書頭........
00585DB0  0B 00 00 00 B0 94 56 00 50 00 00 00 FA 00 00 00  ...ｰ之.P...・..
00585DC0  89 EB 8A 79 93 AA 00 00 00 00 00 00 00 00 0B 00  雅楽頭.........
00585DD0  00 00 B0 94 56 00 51 00 00 00 FA 00 00 00 8C BA  ..ｰ之.Q...・..玄
00585DE0  94 D7 93 AA 00 00 00 00 00 00 00 00 0B 00 00 00  蕃頭...........
00585DF0  B0 94 56 00 52 00 00 00 FA 00 00 00 8E E5 8C 76  ｰ之.R...・..主計
00585E00  93 AA 00 00 00 00 00 00 00 00 0B 00 00 00 B0 94  頭...........ｰ・
00585E10  56 00 53 00 00 00 FA 00 00 00 96 D8 8D 48 93 AA  V.S...・..木工頭
00585E20  00 00 00 00 00 00 00 00 0B 00 00 00 B0 94 56 00  ...........ｰ之.
00585E30  54 00 00 00 FA 00 00 00 8D B6 94 6E 93 AA 00 00  T...・..左馬頭..
00585E40  00 00 00 00 00 00 0B 00 00 00 48 64 55 00 55 00  .........HdU.U.
00585E50  00 00 FA 00 00 00 89 45 94 6E 93 AA 00 00 00 00  ..・..右馬頭....
00585E60  00 00 00 00 0B 00 00 00 C8 B9 55 00 56 00 00 00  .......ﾈｹU.V...
00585E70  FA 00 00 00 95 BA 8C C9 93 AA 00 00 00 00 00 00  ・..兵庫頭......
00585E80  00 00 0B 00 00 00 B0 94 56 00 57 00 00 00 FA 00  .....ｰ之.W...・
00585E90  00 00 8D B6 89 71 96 E5 8D B2 00 00 00 00 00 00  ..左衛門佐......
00585EA0  0B 00 00 00 C8 35 55 00 58 00 00 00 FA 00 00 00  ...ﾈ5U.X...・..
00585EB0  89 45 89 71 96 E5 8D B2 00 00 00 00 00 00 0B 00  右衛門佐.......
00585EC0  00 00 B0 94 56 00 59 00 00 00 FA 00 00 00 8D B6  ..ｰ之.Y...・..左
00585ED0  95 BA 89 71 8D B2 00 00 00 00 00 00 0B 00 00 00  兵衛佐.........
00585EE0  B0 94 56 00 5A 00 00 00 FA 00 00 00 89 45 95 BA  ｰ之.Z...・..右兵
00585EF0  89 71 8D B2 00 00 00 00 00 00 0B 00 00 00 08 13  衛佐.........
00585F00  56 00 5B 00 00 00 FA 00 00 00 8E 52 8F E9 8E E7  V.[...・..山城守
00585F10  00 00 00 00 00 00 00 00 0A 00 00 00 88 EB 54 00  ............壱T.
00585F20  5C 00 00 00 FA 00 00 00 90 DB 92 C3 8E E7 00 00  \...・..摂津守..
00585F30  00 00 00 00 00 00 0A 00 00 00 08 D1 55 00 5D 00  ..........ﾑU.].
00585F40  00 00 FA 00 00 00 94 F6 92 A3 8E E7 00 00 00 00  ..・..尾張守....
00585F50  00 00 00 00 0A 00 00 00 C8 CB 55 00 5E 00 00 00  ........ﾈﾋU.^...
00585F60  FA 00 00 00 8E 4F 89 CD 8E E7 00 00 00 00 00 00  ・..三河守......
00585F70  00 00 0A 00 00 00 B0 94 56 00 5F 00 00 00 FA 00  ......ｰ之._...・
00585F80  00 00 89 93 8D 5D 8E E7 00 00 00 00 00 00 00 00  ..遠江守........
00585F90  0A 00 00 00 C8 FB 55 00 60 00 00 00 FA 00 00 00  ....ﾈ�U.`...・..
00585FA0  8F 78 89 CD 8E E7 00 00 00 00 00 00 00 00 0A 00  駿河守..........
00585FB0  00 00 48 2B 55 00 61 00 00 00 FA 00 00 00 8D 62  ..H+U.a...・..甲
00585FC0  94 E3 8E E7 00 00 00 00 00 00 00 00 0A 00 00 00  斐守............
00585FD0  B0 94 56 00 62 00 00 00 FA 00 00 00 91 8A 96 CD  ｰ之.b...・..相模
00585FE0  8E E7 00 00 00 00 00 00 00 00 0A 00 00 00 48 86  守............H・
00585FF0  54 00 63 00 00 00 FA 00 00 00 94 FC 94 5A 8E E7  T.c...・..美濃守
00586000  00 00 00 00 00 00 00 00 0A 00 00 00 C8 FF 54 00  ............ﾈ�T.
00586010  64 00 00 00 FA 00 00 00 90 4D 94 5A 8E E7 00 00  d...・..信濃守..
00586020  00 00 00 00 00 00 0A 00 00 00 88 DE 55 00 65 00  ..........萎U.e.
00586030  00 00 FA 00 00 00 89 BA 96 EC 8E E7 00 00 00 00  ..・..下野守....
00586040  00 00 00 00 0A 00 00 00 48 71 54 00 66 00 00 00  ........HqT.f...
00586050  FA 00 00 00 8F 6F 89 48 8E E7 00 00 00 00 00 00  ・..出羽守......
00586060  00 00 0A 00 00 00 08 51 54 00 67 00 00 00 FA 00  ......QT.g...・
00586070  00 00 89 C1 89 EA 8E E7 00 00 00 00 00 00 00 00  ..加賀守........
00586080  0A 00 00 00 B0 94 56 00 68 00 00 00 FA 00 00 00  ....ｰ之.h...・..
00586090  89 7A 92 86 8E E7 00 00 00 00 00 00 00 00 0A 00  越中守..........
005860A0  00 00 C8 32 55 00 69 00 00 00 FA 00 00 00 89 7A  ..ﾈ2U.i...・..越
005860B0  8C E3 8E E7 00 00 00 00 00 00 00 00 0A 00 00 00  後守............
005860C0  B0 94 56 00 6A 00 00 00 FA 00 00 00 92 4F 94 67  ｰ之.j...・..丹波
005860D0  8E E7 00 00 00 00 00 00 00 00 0A 00 00 00 B0 94  守............ｰ・
005860E0  56 00 6B 00 00 00 FA 00 00 00 92 41 94 6E 8E E7  V.k...・..但馬守
005860F0  00 00 00 00 00 00 00 00 0A 00 00 00 48 77 54 00  ............HwT.
00586100  6C 00 00 00 FA 00 00 00 88 F6 94 A6 8E E7 00 00  l...・..因幡守..
00586110  00 00 00 00 00 00 0A 00 00 00 B0 94 56 00 6D 00  ..........ｰ之.m.
00586120  00 00 FA 00 00 00 94 8C E3 CB 8E E7 00 00 00 00  ..・..伯耆守....
00586130  00 00 00 00 0A 00 00 00 C8 EC 55 00 6E 00 00 00  ........ﾈ・.n...
00586140  FA 00 00 00 8F 6F 89 5F 8E E7 00 00 00 00 00 00  ・..出雲守......
00586150  00 00 0A 00 00 00 B0 94 56 00 6F 00 00 00 FA 00  ......ｰ之.o...・
00586160  00 00 94 FC 8D EC 8E E7 00 00 00 00 00 00 00 00  ..美作守........
00586170  0A 00 00 00 88 A8 55 00 70 00 00 00 FA 00 00 00  ....葵U.p...・..
00586180  94 F5 91 4F 8E E7 00 00 00 00 00 00 00 00 0A 00  備前守..........
00586190  00 00 B0 94 56 00 71 00 00 00 FA 00 00 00 94 F5  ..ｰ之.q...・..備
005861A0  92 86 8E E7 00 00 00 00 00 00 00 00 0A 00 00 00  中守............
005861B0  C8 BC 55 00 72 00 00 00 FA 00 00 00 94 F5 8C E3  ﾈｼU.r...・..備後
005861C0  8E E7 00 00 00 00 00 00 00 00 0A 00 00 00 B0 94  守............ｰ・
005861D0  56 00 73 00 00 00 FA 00 00 00 88 C0 8C 7C 8E E7  V.s...・..安芸守
005861E0  00 00 00 00 00 00 00 00 0A 00 00 00 B0 94 56 00  ............ｰ之.
005861F0  74 00 00 00 FA 00 00 00 8E FC 96 68 8E E7 00 00  t...・..周防守..
00586200  00 00 00 00 00 00 0A 00 00 00 C8 17 55 00 75 00  ..........ﾈU.u.
00586210  00 00 FA 00 00 00 8B 49 88 C9 8E E7 00 00 00 00  ..・..紀伊守....
00586220  00 00 00 00 0A 00 00 00 C8 95 55 00 76 00 00 00  ........ﾈ俵.v...
00586230  FA 00 00 00 88 A2 94 67 8E E7 00 00 00 00 00 00  ・..阿波守......
00586240  00 00 0A 00 00 00 B0 94 56 00 77 00 00 00 FA 00  ......ｰ之.w...・
00586250  00 00 8E 5D 8A F2 8E E7 00 00 00 00 00 00 00 00  ..讃岐守........
00586260  0A 00 00 00 48 62 54 00 78 00 00 00 FA 00 00 00  ....HbT.x...・..
00586270  88 C9 97 5C 8E E7 00 00 00 00 00 00 00 00 0A 00  伊予守..........
00586280  00 00 C8 D7 55 00 79 00 00 00 FA 00 00 00 92 7D  ..ﾈﾗU.y...・..筑
00586290  91 4F 8E E7 00 00 00 00 00 00 00 00 0A 00 00 00  前守............
005862A0  B0 94 56 00 7A 00 00 00 FA 00 00 00 92 7D 8C E3  ｰ之.z...・..筑後
005862B0  8E E7 00 00 00 00 00 00 00 00 0A 00 00 00 B0 94  守............ｰ・
005862C0  56 00 7B 00 00 00 FA 00 00 00 94 EC 91 4F 8E E7  V.{...・..肥前守
005862D0  00 00 00 00 00 00 00 00 0A 00 00 00 B0 94 56 00  ............ｰ之.
005862E0  7C 00 00 00 FA 00 00 00 96 4C 91 4F 8E E7 00 00  |...・..豊前守..
005862F0  00 00 00 00 00 00 0A 00 00 00 48 D0 55 00 7D 00  ..........HﾐU.}.
00586300  00 00 FA 00 00 00 96 4C 8C E3 8E E7 00 00 00 00  ..・..豊後守....
00586310  00 00 00 00 0A 00 00 00 48 FA 55 00 7E 00 00 00  ........H�U.~...
00586320  FA 00 00 00 8E 98 8F 5D 00 00 00 00 00 00 00 00  ・..侍従........
00586330  00 00 0A 00 00 00 B0 94 56 00 7F 00 00 00 FA 00  ......ｰ之....・
00586340  00 00 8E 98 8F 5D 00 00 00 00 00 00 00 00 00 00  ..侍従..........
00586350  0A 00 00 00 B0 94 56 00 80 00 00 00 FA 00 00 00  ....ｰ之.�...・..
00586360  8E 98 8F 5D 00 00 00 00 00 00 00 00 00 00 0A 00  侍従............
00586370  00 00 B0 94 56 00 81 00 00 00 FA 00 00 00 8E 98  ..ｰ之.・..・..侍
00586380  8F 5D 00 00 00 00 00 00 00 00 00 00 0A 00 00 00  従..............
00586390  B0 94 56 00 82 00 00 00 FA 00 00 00 8E AE 95 94  ｰ之.・..・..式部
005863A0  8F AD 95 E3 00 00 00 00 00 00 0A 00 00 00 B0 94  少輔..........ｰ・
005863B0  56 00 83 00 00 00 FA 00 00 00 8E A1 95 94 8F AD  V.・..・..治部少
005863C0  95 E3 00 00 00 00 00 00 0A 00 00 00 B0 94 56 00  輔..........ｰ之.
005863D0  84 00 00 00 FA 00 00 00 96 AF 95 94 8F AD 95 E3  ・..・..民部少輔
005863E0  00 00 00 00 00 00 0A 00 00 00 08 95 55 00 85 00  ..........俵.・
005863F0  00 00 FA 00 00 00 95 BA 95 94 8F AD 95 E3 00 00  ..・..兵部少輔..
00586400  00 00 00 00 0A 00 00 00 88 76 54 00 86 00 00 00  ........・T.・..
00586410  FA 00 00 00 8C 59 95 94 8F AD 95 E3 00 00 00 00  ・..刑部少輔....
00586420  00 00 0A 00 00 00 C8 69 54 00 87 00 00 00 FA 00  ......ﾈiT.・..・
00586430  00 00 91 E5 91 A0 8F AD 95 E3 00 00 00 00 00 00  ..大蔵少輔......
00586440  0A 00 00 00 B0 94 56 00 88 00 00 00 FA 00 00 00  ....ｰ之.・..・..
00586450  8B 7B 93 E0 8F AD 95 E3 00 00 00 00 00 00 0A 00  宮内少輔........
00586460  00 00 B0 94 56 00 89 00 00 00 FA 00 00 00 91 E5  ..ｰ之.・..・..大
00586470  91 56 97 BA 00 00 00 00 00 00 00 00 0A 00 00 00  膳亮............
00586480  08 3C 54 00 8A 00 00 00 FA 00 00 00 8D B6 8B 9E  <T.・..・..左京
00586490  97 BA 00 00 00 00 00 00 00 00 0A 00 00 00 C8 2D  亮............ﾈ-
005864A0  54 00 8B 00 00 00 FA 00 00 00 89 45 8B 9E 97 BA  T.・..・..右京亮
005864B0  00 00 00 00 00 00 00 00 0A 00 00 00 C8 ED 54 00  ............ﾈ�p.
005864C0  8C 00 00 00 FA 00 00 00 8F 43 97 9D 97 BA 00 00  ・..・..修理亮..
005864D0  00 00 00 00 00 00 0A 00 00 00 08 B6 55 00 8D 00  ..........ｶU.・
005864E0  00 00 FA 00 00 00 93 E0 91 A0 93 AA 00 00 00 00  ..・..内蔵頭....
005864F0  00 00 00 00 0A 00 00 00 B0 94 56 00 8E 00 00 00  ........ｰ之.・..
00586500  FA 00 00 00 96 44 93 61 93 AA 00 00 00 00 00 00  ・..縫殿頭......
00586510  00 00 0A 00 00 00 B0 94 56 00 8F 00 00 00 FA 00  ......ｰ之.・..・
00586520  00 00 93 E0 8F A0 93 AA 00 00 00 00 00 00 00 00  ..内匠頭........
00586530  0A 00 00 00 B0 94 56 00 90 00 00 00 FA 00 00 00  ....ｰ之.・..・..
00586540  91 E5 90 86 93 AA 00 00 00 00 00 00 00 00 0A 00  大炊頭..........
00586550  00 00 B0 94 56 00 91 00 00 00 FA 00 00 00 8E E5  ..ｰ之.・..・..主
00586560  93 61 93 AA 00 00 00 00 00 00 00 00 0A 00 00 00  殿頭............
00586570  B0 94 56 00 92 00 00 00 FA 00 00 00 91 7C 95 94  ｰ之.・..・..掃部
00586580  93 AA 00 00 00 00 00 00 00 00 0A 00 00 00 B0 94  頭............ｰ・
00586590  56 00 93 00 00 00 FA 00 00 00 8A A8 89 F0 97 52  V.・..・..勘解由
005865A0  8E 9F 8A AF 00 00 00 00 0A 00 00 00 B0 94 56 00  次官........ｰ之.
005865B0  94 00 00 00 FA 00 00 00 92 86 96 B1 91 E5 8F E5  ・..・..中務大丞
005865C0  00 00 00 00 00 00 09 00 00 00 88 CC 55 00 95 00  ..........偉U.・
005865D0  00 00 FA 00 00 00 93 E0 91 56 90 B3 00 00 00 00  ..・..内膳正....
005865E0  00 00 00 00 09 00 00 00 B0 94 56 00 96 00 00 00  ........ｰ之.・..
005865F0  FA 00 00 00 93 8C 8E 73 90 B3 00 00 00 00 00 00  ・..東市正......
00586600  00 00 09 00 00 00 B0 94 56 00 97 00 00 00 FA 00  ......ｰ之.・..・
00586610  00 00 90 BC 8E 73 90 B3 00 00 00 00 00 00 00 00  ..西市正........
00586620  09 00 00 00 B0 94 56 00 98 00 00 00 FA 00 00 00  ....ｰ之.・..・..
00586630  92 65 90 B3 91 E5 92 89 00 00 00 00 00 00 09 00  弾正大忠........
00586640  00 00 08 59 55 00 99 00 00 00 FA 00 00 00 8D B6  ..YU.・..・..左
00586650  8B DF 8F AB 8A C4 00 00 00 00 00 00 09 00 00 00  近将監..........
00586660  C8 5A 54 00 9A 00 00 00 FA 00 00 00 8D B6 8B DF  ﾈZT.・..・..左近
00586670  8F AB 8A C4 00 00 00 00 00 00 09 00 00 00 B0 94  将監..........ｰ・
00586680  56 00 9B 00 00 00 FA 00 00 00 89 45 8B DF 8F AB  V.・..・..右近将
00586690  8A C4 00 00 00 00 00 00 09 00 00 00 B0 94 56 00  監..........ｰ之.
005866A0  9C 00 00 00 FA 00 00 00 89 45 8B DF 8F AB 8A C4  ・..・..右近将監
005866B0  00 00 00 00 00 00 09 00 00 00 B0 94 56 00 9D 00  ..........ｰ之.・
005866C0  00 00 FA 00 00 00 8F E3 91 8D 89 EE 00 00 00 00  ..・..上総介....
005866D0  00 00 00 00 08 00 00 00 C8 B7 54 00 9E 00 00 00  .......ﾈｷT.・..
005866E0  FA 00 00 00 8F ED 97 A4 89 EE 00 00 00 00 00 00  ・..常陸介......
005866F0  00 00 08 00 00 00 48 32 54 00 9F 00 00 00 FA 00  .....H2T.・..・
00586700  00 00 8F E3 96 EC 89 EE 00 00 00 00 00 00 00 00  ..上野介........
00586710  08 00 00 00 B0 94 56 00 A0 00 00 00 FA 00 00 00  ...ｰ之.�...・..
00586720  88 C0 96 5B 8E E7 00 00 00 00 00 00 00 00 08 00  安房守.........
00586730  00 00 B0 94 56 00 A1 00 00 00 FA 00 00 00 8E E1  ..ｰ之.｡...・..若
00586740  8B B7 8E E7 00 00 00 00 00 00 00 00 08 00 00 00  狭守...........
00586750  B0 94 56 00 A2 00 00 00 FA 00 00 00 94 5C 93 6F  ｰ之.｢...・..能登
00586760  8E E7 00 00 00 00 00 00 00 00 08 00 00 00 B0 94  守...........ｰ・
00586770  56 00 A3 00 00 00 FA 00 00 00 8D B2 93 6E 8E E7  V.｣...・..佐渡守
00586780  00 00 00 00 00 00 00 00 08 00 00 00 88 B8 54 00  ...........虻T.
00586790  A4 00 00 00 FA 00 00 00 92 4F 8C E3 8E E7 00 00  ､...・..丹後守..
005867A0  00 00 00 00 00 00 08 00 00 00 08 2C 55 00 A5 00  .........,U.･.
005867B0  00 00 FA 00 00 00 90 CE 8C A9 8E E7 00 00 00 00  ..・..石見守....
005867C0  00 00 00 00 08 00 00 00 48 2C 54 00 A6 00 00 00  .......H,T.ｦ...
005867D0  FA 00 00 00 92 B7 96 E5 8E E7 00 00 00 00 00 00  ・..長門守......
005867E0  00 00 08 00 00 00 88 63 55 00 A7 00 00 00 FA 00  .....・U.ｧ...・
005867F0  00 00 93 79 8D B2 8E E7 00 00 00 00 00 00 00 00  ..土佐守........
00586800  08 00 00 00 B0 94 56 00 A8 00 00 00 FA 00 00 00  ...ｰ之.ｨ...・..
00586810  93 FA 8C FC 8E E7 00 00 00 00 00 00 00 00 08 00  日向守.........
00586820  00 00 48 70 55 00 A9 00 00 00 FA 00 00 00 91 E5  ..HpU.ｩ...・..大
00586830  8B F7 8E E7 00 00 00 00 00 00 00 00 08 00 00 00  隅守...........
00586840  88 94 54 00 AA 00 00 00 FA 00 00 00 8E 46 96 80  ・T.ｪ...・..薩摩
00586850  8E E7 00 00 00 00 00 00 00 00 08 00 00 00 B0 94  守...........ｰ・
00586860  56 00 AB 00 00 00 FA 00 00 00 8E AE 95 94 91 E5  V.ｫ...・..式部大
00586870  8F E5 00 00 00 00 00 00 08 00 00 00 B0 94 56 00  丞.........ｰ之.
00586880  AC 00 00 00 FA 00 00 00 8E A1 95 94 91 E5 8F E5  ｬ...・..治部大丞
00586890  00 00 00 00 00 00 08 00 00 00 B0 94 56 00 AD 00  .........ｰ之.ｭ.
005868A0  00 00 FA 00 00 00 96 AF 95 94 91 E5 8F E5 00 00  ..・..民部大丞..
005868B0  00 00 00 00 08 00 00 00 B0 94 56 00 AE 00 00 00  .......ｰ之.ｮ...
005868C0  FA 00 00 00 95 BA 95 94 91 E5 8F E5 00 00 00 00  ・..兵部大丞....
005868D0  00 00 08 00 00 00 B0 94 56 00 AF 00 00 00 FA 00  .....ｰ之.ｯ...・
005868E0  00 00 8C 59 95 94 91 E5 8F E5 00 00 00 00 00 00  ..刑部大丞......
005868F0  08 00 00 00 B0 94 56 00 B0 00 00 00 FA 00 00 00  ...ｰ之.ｰ...・..
00586900  91 E5 91 A0 91 E5 8F E5 00 00 00 00 00 00 08 00  大蔵大丞.......
00586910  00 00 48 97 55 00 B1 00 00 00 FA 00 00 00 8B 7B  ..H誘.ｱ...・..宮
00586920  93 E0 91 E5 8F E5 00 00 00 00 00 00 08 00 00 00  内大丞.........
00586930  B0 94 56 00 B2 00 00 00 FA 00 00 00 90 7D 8F 91  ｰ之.ｲ...・..図書
00586940  8F 95 00 00 00 00 00 00 00 00 08 00 00 00 B0 94  助...........ｰ・
00586950  56 00 B3 00 00 00 FA 00 00 00 89 EB 8A 79 8F 95  V.ｳ...・..雅楽助
00586960  00 00 00 00 00 00 00 00 08 00 00 00 88 79 54 00  ...........・T.
00586970  B4 00 00 00 FA 00 00 00 8C BA 94 D7 8F 95 00 00  ｴ...・..玄蕃助..
00586980  00 00 00 00 00 00 08 00 00 00 B0 94 56 00 B5 00  .........ｰ之.ｵ.
00586990  00 00 FA 00 00 00 8E E5 8C 76 8F 95 00 00 00 00  ..・..主計助....
005869A0  00 00 00 00 08 00 00 00 B0 94 56 00 B6 00 00 00  .......ｰ之.ｶ...
005869B0  FA 00 00 00 96 D8 8D 48 8F 95 00 00 00 00 00 00  ・..木工助......
005869C0  00 00 08 00 00 00 B0 94 56 00 B7 00 00 00 FA 00  .....ｰ之.ｷ...・
005869D0  00 00 8D B6 94 6E 8F 95 00 00 00 00 00 00 00 00  ..左馬助........
005869E0  08 00 00 00 48 FE 54 00 B8 00 00 00 FA 00 00 00  ...H�T.ｸ...・..
005869F0  89 45 94 6E 8F 95 00 00 00 00 00 00 00 00 08 00  右馬助.........
00586A00  00 00 88 25 54 00 B9 00 00 00 FA 00 00 00 95 BA  ..・T.ｹ...・..兵
00586A10  8C C9 8F 95 00 00 00 00 00 00 00 00 08 00 00 00  庫助...........
00586A20  48 37 55 00 BA 00 00 00 FA 00 00 00 94 B9 90 6C  H7U.ｺ...・..隼人
00586A30  90 B3 00 00 00 00 00 00 00 00 08 00 00 00 B0 94  正...........ｰ・
00586A40  56 00 BB 00 00 00 FA 00 00 00 90 44 95 94 90 B3  V.ｻ...・..織部正
00586A50  00 00 00 00 00 00 00 00 08 00 00 00 B0 94 56 00  ...........ｰ之.
00586A60  BC 00 00 00 FA 00 00 00 94 CE 8F 97 90 B3 00 00  ｼ...・..釆女正..
00586A70  00 00 00 00 00 00 08 00 00 00 B0 94 56 00 BD 00  .........ｰ之.ｽ.
00586A80  00 00 FA 00 00 00 92 65 90 B3 8F AD 92 89 00 00  ..・..弾正少忠..
00586A90  00 00 00 00 08 00 00 00 88 6F 55 00 BE 00 00 00  .......・U.ｾ...
00586AA0  FA 00 00 00 8F 48 93 63 8F E9 89 EE 00 00 00 00  ・..秋田城介....
00586AB0  00 00 08 00 00 00 C8 48 54 00 BF 00 00 00 FA 00  .....ﾈHT.ｿ...・
00586AC0  00 00 92 86 96 B1 8F AD 8F E5 00 00 00 00 00 00  ..中務少丞......
00586AD0  07 00 00 00 48 B9 54 00 C0 00 00 00 FA 00 00 00  ...HｹT.ﾀ...・..
00586AE0  8E AE 95 94 8F AD 8F E5 00 00 00 00 00 00 07 00  式部少丞.......
00586AF0  00 00 B0 94 56 00 C1 00 00 00 FA 00 00 00 8E A1  ..ｰ之.ﾁ...・..治
00586B00  95 94 8F AD 8F E5 00 00 00 00 00 00 07 00 00 00  部少丞.........
00586B10  B0 94 56 00 C2 00 00 00 FA 00 00 00 96 AF 95 94  ｰ之.ﾂ...・..民部
00586B20  8F AD 8F E5 00 00 00 00 00 00 07 00 00 00 B0 94  少丞.........ｰ・
00586B30  56 00 C3 00 00 00 FA 00 00 00 95 BA 95 94 8F AD  V.ﾃ...・..兵部少
00586B40  8F E5 00 00 00 00 00 00 07 00 00 00 B0 94 56 00  丞.........ｰ之.
00586B50  C4 00 00 00 FA 00 00 00 8C 59 95 94 8F AD 8F E5  ﾄ...・..刑部少丞
00586B60  00 00 00 00 00 00 07 00 00 00 B0 94 56 00 C5 00  .........ｰ之.ﾅ.
00586B70  00 00 FA 00 00 00 91 E5 91 A0 8F AD 8F E5 00 00  ..・..大蔵少丞..
00586B80  00 00 00 00 07 00 00 00 B0 94 56 00 C6 00 00 00  .......ｰ之.ﾆ...
00586B90  FA 00 00 00 8B 7B 93 E0 8F AD 8F E5 00 00 00 00  ・..宮内少丞....
00586BA0  00 00 07 00 00 00 B0 94 56 00 C7 00 00 00 FA 00  .....ｰ之.ﾇ...・
00586BB0  00 00 93 E0 91 A0 8F 95 00 00 00 00 00 00 00 00  ..内蔵助........
00586BC0  07 00 00 00 08 AD 55 00 C8 00 00 00 FA 00 00 00  ...ｭU.ﾈ...・..
00586BD0  96 44 93 61 8F 95 00 00 00 00 00 00 00 00 07 00  縫殿助.........
00586BE0  00 00 B0 94 56 00 C9 00 00 00 FA 00 00 00 93 E0  ..ｰ之.ﾉ...・..内
00586BF0  8F A0 8F 95 00 00 00 00 00 00 00 00 07 00 00 00  匠助...........
00586C00  B0 94 56 00 CA 00 00 00 FA 00 00 00 91 E5 90 86  ｰ之.ﾊ...・..大炊
00586C10  8F 95 00 00 00 00 00 00 00 00 07 00 00 00 B0 94  助...........ｰ・
00586C20  56 00 CB 00 00 00 FA 00 00 00 8E E5 93 61 8F 95  V.ﾋ...・..主殿助
00586C30  00 00 00 00 00 00 00 00 07 00 00 00 B0 94 56 00  ...........ｰ之.
00586C40  CC 00 00 00 FA 00 00 00 91 7C 95 94 8F 95 00 00  ﾌ...・..掃部助..
00586C50  00 00 00 00 00 00 07 00 00 00 B0 94 56 00 CD 00  .........ｰ之.ﾍ.
00586C60  00 00 FA 00 00 00 8E E5 90 85 90 B3 00 00 00 00  ..・..主水正....
00586C70  00 00 00 00 07 00 00 00 B0 94 56 00 CE 00 00 00  .......ｰ之.ﾎ...
00586C80  FA 00 00 00 8E E5 91 56 90 B3 00 00 00 00 00 00  ・..主膳正......
00586C90  00 00 07 00 00 00 B0 94 56 00 CF 00 00 00 FA 00  .....ｰ之.ﾏ...・
00586CA0  00 00 98 61 90 F2 8E E7 00 00 00 00 00 00 00 00  ..和泉守........
00586CB0  06 00 00 00 88 2A 55 00 D0 00 00 00 FA 00 00 00  ...・U.ﾐ...・..
00586CC0  88 C9 89 EA 8E E7 00 00 00 00 00 00 00 00 06 00  伊賀守.........
00586CD0  00 00 48 67 55 00 D1 00 00 00 FA 00 00 00 8E 75  ..HgU.ﾑ...・..志
00586CE0  96 80 8E E7 00 00 00 00 00 00 00 00 06 00 00 00  摩守...........
00586CF0  B0 94 56 00 D2 00 00 00 FA 00 00 00 88 C9 93 A4  ｰ之.ﾒ...・..伊豆
00586D00  8E E7 00 00 00 00 00 00 00 00 06 00 00 00 B0 94  守...........ｰ・
00586D10  56 00 D3 00 00 00 FA 00 00 00 94 F2 91 CB 8E E7  V.ﾓ...・..飛騨守
00586D20  00 00 00 00 00 00 00 00 06 00 00 00 B0 94 56 00  ...........ｰ之.
00586D30  D4 00 00 00 FA 00 00 00 89 42 8A F2 8E E7 00 00  ﾔ...・..隠岐守..
00586D40  00 00 00 00 00 00 06 00 00 00 88 90 55 00 D5 00  .........・U.ﾕ.
00586D50  00 00 FA 00 00 00 92 57 98 48 8E E7 00 00 00 00  ..・..淡路守....
00586D60  00 00 00 00 06 00 00 00 B0 94 56 00 D6 00 00 00  .......ｰ之.ﾖ...
00586D70  FA 00 00 00 88 EB 8A F2 8E E7 00 00 00 00 00 00  ・..壱岐守......
00586D80  00 00 06 00 00 00 B0 94 56 00 D7 00 00 00 FA 00  .....ｰ之.ﾗ...・
00586D90  00 00 91 CE 94 6E 8E E7 00 00 00 00 00 00 00 00  ..対馬守........
00586DA0  06 00 00 00 88 36 55 00 D8 00 00 00 FA 00 00 00  ...・U.ﾘ...・..
00586DB0  8D B6 89 71 96 E5 91 E5 88 D1 00 00 00 00 06 00  左衛門大尉.....
00586DC0  00 00 48 43 55 00 D9 00 00 00 FA 00 00 00 8D B6  ..HCU.ﾙ...・..左
00586DD0  89 71 96 E5 91 E5 88 D1 00 00 00 00 06 00 00 00  衛門大尉.......
00586DE0  88 D5 55 00 DA 00 00 00 FA 00 00 00 8D B6 89 71  易U.ﾚ...・..左衛
00586DF0  96 E5 91 E5 88 D1 00 00 00 00 06 00 00 00 B0 94  門大尉.......ｰ・
00586E00  56 00 DB 00 00 00 FA 00 00 00 89 45 89 71 96 E5  V.ﾛ...・..右衛門
00586E10  91 E5 88 D1 00 00 00 00 06 00 00 00 B0 94 56 00  大尉.......ｰ之.
00586E20  DC 00 00 00 FA 00 00 00 89 45 89 71 96 E5 91 E5  ﾜ...・..右衛門大
00586E30  88 D1 00 00 00 00 06 00 00 00 B0 94 56 00 DD 00  尉.......ｰ之.ﾝ.
00586E40  00 00 FA 00 00 00 89 45 89 71 96 E5 91 E5 88 D1  ..・..右衛門大尉
00586E50  00 00 00 00 06 00 00 00 B0 94 56 00 DE 00 00 00  .......ｰ之.ﾞ...
00586E60  FA 00 00 00 8E E5 94 6E 8E F1 00 00 00 00 00 00  ・..主馬首......
00586E70  00 00 06 00 00 00 B0 94 56 00 DF 00 00 00 FA 00  .....ｰ之.ﾟ...・
00586E80  00 00 8A A8 89 F0 97 52 94 BB 8A AF 00 00 00 00  ..勘解由判官....
00586E90  06 00 00 00 B0 94 56 00 E0 00 00 00 FA 00 00 00  ...ｰ之.・..・..
00586EA0  8D B6 89 71 96 E5 8F AD 88 D1 00 00 00 00 05 00  左衛門少尉.....
00586EB0  00 00 08 CB 55 00 E1 00 00 00 FA 00 00 00 8D B6  ..ﾋU.・..・..左
00586EC0  89 71 96 E5 8F AD 88 D1 00 00 00 00 05 00 00 00  衛門少尉.......
00586ED0  B0 94 56 00 E2 00 00 00 FA 00 00 00 8D B6 89 71  ｰ之.・..・..左衛
00586EE0  96 E5 8F AD 88 D1 00 00 00 00 05 00 00 00 B0 94  門少尉.......ｰ・
00586EF0  56 00 E3 00 00 00 FA 00 00 00 89 45 89 71 96 E5  V.・..・..右衛門
00586F00  8F AD 88 D1 00 00 00 00 05 00 00 00 B0 94 56 00  少尉.......ｰ之.
00586F10  E4 00 00 00 FA 00 00 00 89 45 89 71 96 E5 8F AD  ・..・..右衛門少
00586F20  88 D1 00 00 00 00 05 00 00 00 B0 94 56 00 E5 00  尉.......ｰ之.・
00586F30  00 00 FA 00 00 00 89 45 89 71 96 E5 8F AD 88 D1  ..・..右衛門少尉
00586F40  00 00 00 00 05 00 00 00 B0 94 56 00 E6 00 00 00  .......ｰ之.・..
00586F50  FA 00 00 00 8D B6 95 BA 89 71 91 E5 88 D1 00 00  ・..左兵衛大尉..
00586F60  00 00 04 00 00 00 B0 94 56 00 E7 00 00 00 FA 00  .....ｰ之.・..・
00586F70  00 00 8D B6 95 BA 89 71 91 E5 88 D1 00 00 00 00  ..左兵衛大尉....
00586F80  04 00 00 00 B0 94 56 00 E8 00 00 00 FA 00 00 00  ...ｰ之.・..・..
00586F90  8D B6 95 BA 89 71 91 E5 88 D1 00 00 00 00 04 00  左兵衛大尉.....
00586FA0  00 00 B0 94 56 00 E9 00 00 00 FA 00 00 00 89 45  ..ｰ之.・..・..右
00586FB0  95 BA 89 71 91 E5 88 D1 00 00 00 00 04 00 00 00  兵衛大尉.......
00586FC0  C8 41 55 00 EA 00 00 00 FA 00 00 00 89 45 95 BA  ﾈAU.・..・..右兵
00586FD0  89 71 91 E5 88 D1 00 00 00 00 04 00 00 00 B0 94  衛大尉.......ｰ・
00586FE0  56 00 EB 00 00 00 FA 00 00 00 89 45 95 BA 89 71  V.・..・..右兵衛
00586FF0  91 E5 88 D1 00 00 00 00 04 00 00 00 B0 94 56 00  大尉.......ｰ之.
00587000  EC 00 00 00 FA 00 00 00 8D B6 95 BA 89 71 8F AD  ・..・..左兵衛少
00587010  88 D1 00 00 00 00 03 00 00 00 B0 94 56 00 ED 00  尉.......ｰ之.・
00587020  00 00 FA 00 00 00 8D B6 95 BA 89 71 8F AD 88 D1  ..・..左兵衛少尉
00587030  00 00 00 00 03 00 00 00 B0 94 56 00 EE 00 00 00  .......ｰ之.・..
00587040  FA 00 00 00 8D B6 95 BA 89 71 8F AD 88 D1 00 00  ・..左兵衛少尉..
00587050  00 00 03 00 00 00 B0 94 56 00 EF 00 00 00 FA 00  .....ｰ之.・..・
00587060  00 00 89 45 95 BA 89 71 8F AD 88 D1 00 00 00 00  ..右兵衛少尉....
00587070  03 00 00 00 B0 94 56 00 F0 00 00 00 FA 00 00 00  ...ｰ之.・..・..
00587080  89 45 95 BA 89 71 8F AD 88 D1 00 00 00 00 03 00  右兵衛少尉.....
00587090  00 00 B0 94 56 00 F1 00 00 00 FA 00 00 00 89 45  ..ｰ之.・..・..右
005870A0  95 BA 89 71 8F AD 88 D1 00 00 00 00 03 00 00 00  兵衛少尉.......
005870B0  B0 94 56 00 F2 00 00 00 FA 00 00 00 93 54 91 56  ｰ之.・..・..典膳
005870C0  00 00 00 00 00 00 00 00 00 00 02 00 00 00 B0 94  .............ｰ・
005870D0  56 00 F3 00 00 00 FA 00 00 00 93 8C 8E 73 97 43  V.・..・..東市佑
005870E0  00 00 00 00 00 00 00 00 02 00 00 00 B0 94 56 00  ...........ｰ之.
005870F0  F4 00 00 00 FA 00 00 00 90 BC 8E 73 97 43 00 00  ・..・..西市佑..
00587100  00 00 00 00 00 00 02 00 00 00 B0 94 56 00 F5 00  .........ｰ之.・
00587110  00 00 FA 00 00 00 94 B9 90 6C 97 43 00 00 00 00  ..・..隼人佑....
00587120  00 00 00 00 01 00 00 00 B0 94 56 00 F6 00 00 00  .......ｰ之.・..
00587130  FA 00 00 00 90 44 95 94 97 43 00 00 00 00 00 00  ・..織部佑......
00587140  00 00 01 00 00 00 B0 94 56 00 F7 00 00 00 FA 00  .....ｰ之.・..・
00587150  00 00 94 CE 8F 97 97 43 00 00 00 00 00 00 00 00  ..釆女佑........
00587160  01 00 00 00 B0 94 56 00 F8 00 00 00 FA 00 00 00  ...ｰ之.・..・..
00587170  8E E5 90 85 97 43 00 00 00 00 00 00 00 00 00 00  主水佑..........
00587180  00 00 B0 94 56 00 F9 00 00 00 FA 00 00 00 8E E5  ..ｰ之.・..・..主
00587190  91 56 97 43 00 00 00 00 00 00 00 00 00 00 00 00  膳佑............
005871A0  B0 94 56 00 FA 00 00 00 FA 00 00 00              ｰ之.・..・.....


*/