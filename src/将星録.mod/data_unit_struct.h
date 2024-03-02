#pragma once

#include <windows.h>
#include "mng_ユニット情報.h"

#define ユニット情報アドレス 0x5EDE10

#define 次のユニット無し     0x5390E0

#define ユニット所属城なし   0x539000

#define ユニット指揮武将なし 0x5694B0

// これはセーブデータエディタのユニットエディタを使えば、どんどん詳しくわかってくるだろう。

// 148バイト
#pragma pack(1)
struct NB7ユニット情報型 {
	int* p所属城; // [00 90 53]ならどこの城にも所属していない
	int 種別; // 0=軍勢 1=軍船 2=輸送 3=開墾 4=商業 5=建設 6=間者 7=忍者 8=使者 9=移動 10=浪人
	int* p指揮武将; // 武将へのポインタ(武将情報の配列の該当武将の情報の位置を直接指している)。ここが[B0 94 56]ならば、そもそもユニットを誰も率いていない。武将情報中の744人に入っているかどうかで判定するのが良いだろう。
	int 金銭;
	int 金銭MAX; // 50000=0xC350が常に入っている
	int 兵糧;
	int 兵糧MAX; // 50000=0xC350が常に入っている
	int 軍馬;
	int 軍馬MAX; // 50000=0xC350が常に入っている
	int 鉄砲;
	int 鉄砲MAX; // 50000=0xC350が常に入っている
	int 輸送兵士;    // 輸送用の兵士。軍隊用兵数ではない。
	int 輸送兵士MAX; // 50000=0xC350が常に入っている
	int 輸送大砲;    // 輸送用の大砲。軍隊用兵数ではない。
	int 輸送大砲MAX; // 50000=0xC350が常に入っている
	int 現在Ｘ座標;
	int 現在Ｙ座標;
	int unknown9; // [0xffffffff] が多い
	int unknown10; //
	int unknown11;
	int unknown12; // 0x00000000 が多い
	int unknown13; // [ff 0f 00 00] が多い。
	BYTE 移動目標Ｙ座標;
	BYTE 移動目標Ｘ座標;
	int* p次のユニット; // 次のユニットへのポインタ。ユニット情報の配列の該当ユニットの情報の位置を直接指している。これが[E0 90 53 00] = 0x5390E0ならば、次のユニットは存在しない。
	int unknown14; // 0x00000000 が多い
	/* 陣形位置
	  ┌─┬─┬─┐
	  │２│５│８│
	  ├─┼─┼─┤
	  │１│４│７│
	  ├─┼─┼─┤
	  │０│３│６│
	  └─┴─┴─┘
	*/
	BYTE 第１部隊兵種; // 0:足軽 1:騎馬 2:鉄砲 3:騎馬鉄砲  部隊がなければ0
	BYTE 第１部隊混乱; // 1なら混乱 0なら普通
	WORD 第１部隊の陣形位置; // 部隊がなければFFFF
	int 第１部隊兵数; // 部隊がなければ0
	BYTE 第２部隊兵種; // 0:足軽 1:騎馬 2:鉄砲 3:騎馬鉄砲  部隊がなければ0
	BYTE 第２部隊混乱; // 1なら混乱 0なら普通
	WORD 第２部隊の陣形位置; // 部隊がなければFFFF
	int 第２部隊兵数; // 部隊がなければ0
	BYTE 第３部隊兵種; // 0:足軽 1:騎馬 2:鉄砲 3:騎馬鉄砲  部隊がなければ0
	BYTE 第３部隊混乱; // 1なら混乱 0なら普通
	WORD 第３部隊の陣形位置; // 部隊がなければFFFF
	int 第３部隊兵数; // 部隊がなければ0
	BYTE 第４部隊兵種; // 0:足軽 1:騎馬 2:鉄砲 3:騎馬鉄砲  部隊がなければ0
	BYTE 第４部隊混乱; // 1なら混乱 0なら普通
	WORD 第４部隊の陣形位置; // 部隊がなければFFFF
	int 第４部隊兵数; // 部隊がなければ0
	BYTE 第５部隊兵種; // 0:足軽 1:騎馬 2:鉄砲 3:騎馬鉄砲  部隊がなければ0
	BYTE 第５部隊混乱; // 1なら混乱 0なら普通
	WORD 第５部隊の陣形位置; // 部隊がなければFFFF
	int 第５部隊兵数; // 部隊がなければ0
	int ユニット番号;   // 1からの番号が振られている。
	int ユニット番号MAX; // [E8 02] == 744 というユニット最大数が常にはいっている。これはExcelなどを見てもわかる。
	BYTE unused4;

	// 以下１バイトを分割したいろいろなフラグ。 // 0の時もあれば、[00 00 00 10]などもある
	BYTE flag_unknown1 : 1;
	BYTE 鉄甲船 : 1; // 
	BYTE 大砲 : 1; // 大砲
	BYTE flag_unknown2 : 1; // 不明。0の時もあれば、[00 00 00 10]のっと気もある
	BYTE flag_unknown3 : 1; // 不明。0の時もあれば、[00 00 00 10]のっと気もある
	BYTE flag_unknown4 : 1; // 不明。0の時もあれば、[00 00 00 10]のっと気もある
	BYTE flag_unknown5 : 1; // 不明。0の時もあれば、[00 00 00 10]のっと気もある
	BYTE flag_unknown8 : 1; // 不明。

};
#pragma pack()

#pragma pack(1)
struct NB7ユニット軍勢型 {
	WORD 兵種; // 0:足軽 1:騎馬 2:鉄砲 3:騎馬鉄砲  部隊がなければ0
	WORD 部隊の陣形位置; // 部隊がなければFFFF
	int 部隊兵数; // 部隊がなければ0
};
#pragma pack()

int get軍勢ユニット部隊最大兵数FromUnitID(int iUnitID);

int get軍勢ユニット部隊最大兵数FromBushouID(int iBushouID);


BOOL isValidUnitID(int iUnitID);

// ユニットIDからそれを率いる武将IDを得る
int getBushouIDFromUnitID(int iUnitID);

// 武将IDからそれを率いるユニットIDを得る
int getUnitIDFromBushouID(int iBushouID);

// ユニットポインタからユニットIDを取得する
int getUnitIDFromUnitPtr(int* iUnitPtr);


int* getUnitPtrFromUnitID(int iUnitID);

/*
1人目のユニット情報
005EDE10  00 90 53 00 00 00 00 00 88 4C 54 00 00 00 00 00  .心.....・T.....
005EDE20  50 C3 00 00 B8 0B 00 00 B8 0B 00 00 00 00 00 00  Pﾃ..ｸ..ｸ......
005EDE30  50 C3 00 00 00 00 00 00 50 C3 00 00 00 00 00 00  Pﾃ......Pﾃ......
005EDE40  50 C3 00 00 00 00 00 00 50 C3 00 00 96 00 00 00  Pﾃ......Pﾃ..・..
005EDE50  47 00 00 00 FF FF FF FF 00 00 00 00 00 00 00 00  G...����........
005EDE60  00 00 00 00 FF 0F 00 00 00 00 E8 70 5F 00 01 00  ....�....鑵_..
005EDE70  00 00 00 00 07 00 84 03 00 00 01 00 00 00 84 03  .....・.....・
005EDE80  00 00 01 00 01 00 84 03 00 00 01 00 02 00 84 03  ....・....・
005EDE90  00 00 00 00 04 00 84 03 00 00 01 00 00 00 E8 02  .....・.....・
005EDEA0  00 00 00 00 

２人目のユニット情報
　　　　　　　　　　　00 90 53 00 00 00 00 00 48 62 54 00  .....心.....HbT.
005EDEB0  00 00 00 00 50 C3 00 00 B8 0B 00 00 B8 0B 00 00  ....Pﾃ..ｸ..ｸ..
005EDEC0  00 00 00 00 50 C3 00 00 00 00 00 00 50 C3 00 00  ....Pﾃ......Pﾃ..
005EDED0  00 00 00 00 50 C3 00 00 00 00 00 00 50 C3 00 00  ....Pﾃ......Pﾃ..
005EDEE0  74 00 00 00 7E 00 00 00 FF FF FF FF 00 00 00 00  t...~...����....
005EDEF0  00 00 00 00 00 00 00 00 FF 0F 00 00 00 00 E8 70  ........�....鑵
005EDF00  5F 00 01 00 00 00 00 00 07 00 84 03 00 00 01 00  _.......・...
005EDF10  00 00 84 03 00 00 01 00 01 00 84 03 00 00 01 00  ..・....・...
005EDF20  02                                               



23人目のユニット情報。
005EEAC8  00 90 53 00 0A 00 00 00 C8 89 55 00 00 00 00 00  .心.....ﾈ蔚.....
005EEAD8  50 C3 00 00 00 00 00 00 50 C3 00 00 00 00 00 00  Pﾃ......Pﾃ......
005EEAE8  50 C3 00 00 00 00 00 00 50 C3 00 00 00 00 00 00  Pﾃ......Pﾃ......
005EEAF8  50 C3 00 00 00 00 00 00 50 C3 00 00 3A 00 00 00  Pﾃ......Pﾃ..:...
005EEB08  54 00 00 00 FF FF FF FF 2C 00 00 00 05 00 00 00  T...����,......
005EEB18  00 00 00 00 FF 0F 00 00 53 3E E8 70 5F 00 01 00  ....�..S>鑵_..
005EEB28  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................
005EEB38  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................
005EEB48  00 00 00 00 00 00 00 00 00 00 17 00 00 00 E8 02  .............・
005EEB58  00 00 00 00                                      ....



 
24人目のユニット情報。先頭がどの城に属するか、3番目がそれが誰か
005EEB5C  98 CB 5D 00 09 00 00 00 48 3C 56 00 00 00 00 00  侏].....H<V.....
005EEB6C  50 C3 00 00 00 00 00 00 B8 0B 00 00 00 00 00 00  Pﾃ......ｸ......
005EEB7C  50 C3 00 00 00 00 00 00 50 C3 00 00 00 00 00 00  Pﾃ......Pﾃ......
005EEB8C  50 C3 00 00 00 00 00 00 50 C3 00 00 52 00 00 00  Pﾃ......Pﾃ..R...
005EEB9C  59 00 00 00 FF FF FF FF 2C 00 00 00 01 00 00 00  Y...����,......
005EEBAC  00 00 00 00 FF 0F 00 00 20 00 E0 90 53 00 03 00  ....�.. .熕S..
005EEBBC  00 00 00 00 04 00 00 00 00 00 00 00 02 00 00 00  ..............
005EEBCC  00 00 00 00 00 00 00 00 00 00 00 00 05 00 00 00  ...............
005EEBDC  00 00 00 00 03 00 00 00 00 00 18 00 00 00 E8 02  ............・
005EEBEC  00 00 00 10                                    ....
*/

/*
第5部隊が混乱している時
005EEAC8  C8 DA 5D 00 00 00 00 00 48 3C 56 00 00 00 00 00  ﾈﾚ].....H<V.....
005EEAD8  50 C3 00 00 B8 0B 00 00 B8 0B 00 00 00 00 00 00  Pﾃ..ｸ..ｸ......
005EEAE8  50 C3 00 00 00 00 00 00 50 C3 00 00 00 00 00 00  Pﾃ......Pﾃ......
005EEAF8  50 C3 00 00 00 00 00 00 50 C3 00 00 9B 00 00 00  Pﾃ......Pﾃ..・..
005EEB08  47 00 00 00 FF FF FF FF FF FF FF FF FF FF FF FF  G...������������
005EEB18  00 00 00 00 FF 0F 00 00 00 00 20 21 5F 00 03 00  ....�.... !_..
005EEB28  00 00 03 00 04 00 84 03 00 00 03 00 02 00 84 03  ....・....・
005EEB38  00 00 03 00 00 00 84 03 00 00 03 00 01 00 84 03  .....・....・
005EEB48  00 00 00 00 03 00 84 03 01 00 17 00 00 00 E8 02  .....・....・
005EEB58  00 00 00 06                                      ...
*/