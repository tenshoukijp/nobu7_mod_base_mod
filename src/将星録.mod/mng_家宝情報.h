#pragma once

using namespace System;

namespace 将星録 {

	public ref class 家宝情報型 {
	protected:
		int iKahouID;
	public:

		家宝情報型(int 家宝配列IX);

		property int 配列IX {
			int get() { return iKahouID; }
		}

		property String^ 家宝名 {
			String^ get();
			void set(String^ value);
		}
		/// <summary>家宝種類 0=茶道道具 1=武器 2=兵装品 3=名馬 4=短筒 5=剣術所 6=馬術書 7=砲術書 8=兵法書 9=医術書 10=忍術書 11=知識書 12=農政書 13=外交書 14=鉱術書 15=建築書 16=歴史書 17=宗教書 18=文学書 19=仏教書 20=軍記物語 21=商業書 22=絵画 23=地図 24=羅針盤 25=南蛮時計 26=算盤 27=十字架 28=珍品 29=香木</summary>
		property int 種類 {
			int get();
			void set(int value);
		}

		/// <summary>1～10</summary>
		property int 等級 {
			int get();
			void set(int value);
		}

		/// <summary>0～10</summary>
		property int 能力上昇 {
			int get();
			void set(int value);
		}

		/// <summary>0-26。グラフィック番号 0:茶碗、1:茶壺、2:茶入、3:茶釜、4:花入、5:千鳥、6:刀剣、7:槍、8:具足、9:鞍、10:陣羽織、11:馬、12:綴本、13:巻子本、14:掛絵、15:巻絵、16:地図、17:羅針盤、18:南蛮時計、19:算盤、20:十字架、21:遠眼鏡、22:煙管、23:洋楽器、24:遊戯具、25:香木、26:短筒、</summary>
		property int 画像 {
			int get();
			void set(int value);
		}

		property int 所有武将配列IX {
			int get();
			void set(int value);
		}

		/// <summary>
		///  1なら兵科効果あり、0ならなし。ただこれで判断するまでもなく「種類」で判断するのが良い。
		/// </summary>
		property int 兵科効果 {
			int get();
			void set(int value);
		}

		// この家宝は政治上昇効果がある。1ならあり、0ならなし。
		property int 政治 {
			int get();
			void set(int value);
		}

		// この家宝は戦闘上昇効果がある。1ならあり、0ならなし。
		property int 戦闘 {
			int get();
			void set(int value);
		}

		// この家宝は智謀上昇効果がある1ならあり、0ならなし。
		property int 智謀 {
			int get();
			void set(int value);
		}

		// この家宝購入は基督布教後の南蛮商人を条件とする。1なら条件とする。0なら無関係。
		property int 南蛮 {
			int get();
			void set(int value);
		}

		// この家宝は特殊なイベントを条件とし、抑制が1だとこの家宝は世に出ていない状態。消滅後の平蜘蛛釜で１となり、また信長の蘭奢待のイベント前でも蘭奢待家宝の抑制は１であり、イベント後は０となる。
		property int 抑制 {
			int get();
			void set(int value);
		}
	};

};


