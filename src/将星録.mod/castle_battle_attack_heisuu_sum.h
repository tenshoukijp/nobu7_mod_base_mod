#pragma once

#include <windows.h>

// 50バイト
struct 籠城戦攻撃側部隊情報 {
	int 部隊番号; // 1～25
	int unknown1;
	int 兵数;     // その部隊の現在の兵数
	int 兵数MAX;  // その部隊の部隊の兵数のMAX
	int unknown2; // 0 が入っているか？
	int	unknown3; // その部隊の部隊の兵数のMAXと同じ値のような
	int p不明ポインタ1; // 何かのポインタと思われるが不明。同じ武将なら同じポインタか？
	int	unknown4; // 不明 0が多い？
	int	unknown5; // 不明
	int	unknown6; // 不明
	int	p指揮武将; // その部隊を率いている武将情報へのポインタ
	int unknown7; // 00 90 53 00 (0x539000)という武将情報の番兵が入っているか？
	WORD unknown9; // 不明
};