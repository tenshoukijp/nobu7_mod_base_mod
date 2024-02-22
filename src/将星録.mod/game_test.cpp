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
#include "hook_functions_direct.h"
#include "bushou_albedo.h"

#include "mng_éî•ñ.h"

using namespace std;

int testFlag = 0;

void doGameTest() {
	testFlag = 1;

	using namespace System::Collections::Generic;
	List<éî•ñŒ^^>^ list = gcnew List<éî•ñŒ^^>(Å‘å”::éî•ñ::”z—ñ”);
	for (int i = 0; i < Å‘å”::éî•ñ::”z—ñ”; i++) {
		list->Add(gcnew éî•ñŒ^(i));
	}

	auto rlist = list->AsReadOnly();

	for each (auto r in rlist) {
		if (r->”z—ñIX == Å‘å”::éî•ñ::”z—ñ” - 1) {
			auto n1 = r->é–¼;
			r->é–¼ = n1;
			auto n2 = r->é–¼;
			if (n1 == n2) {
				OutputDebugStream("é–¼‚Æé–¼‚ªˆê’v\n");
			}
			else {
				OutputDebugStream("é–¼‚Æé–¼‚ª•sˆê’v\n");
			}

			auto h1 = r->•º”;
			r->•º” = h1;
			auto h2 = r->•º”;

			if (h1 == h2) {
				OutputDebugStream("•º”‚Æ•º”‚ªˆê’v\n");
			}
			else {
				OutputDebugStream("•º”‚Æ•º”‚ª•sˆê’v\n");
			}

			auto h2_a = r->•º—Æ;
			r->•º—Æ = h2_a;
			auto h2_b = r->•º—Æ;

			if (h2_a == h2_b) {
				OutputDebugStream("•º—Æ‚Æ•º—Æ‚ªˆê’v\n");
			}
			else {
				OutputDebugStream("•º—Æ‚Æ•º—Æ‚ª•sˆê’v\n");
			}

			auto h3_a = r->¤l;
			r->¤l = h3_a;
			auto h3_b = r->¤l;

			if (h3_a == h3_b) {
				OutputDebugStream("¤l‚Æ¤l‚ªˆê’v\n");
			}
			else {
				OutputDebugStream("¤l‚Æ¤l‚ª•sˆê’v\n");
			}

			auto h4_a = r->‹K–Í;
			r->‹K–Í = h4_a;
			auto h4_b = r->‹K–Í;

			if (h4_a == h4_b) {
				OutputDebugStream("é‹K–Í‚Æé‹K–Í‚ªˆê’v\n");
			}
			else {
				OutputDebugStream("é‹K–Í‚Æé‹K–Í‚ª•sˆê’v\n");
			}

			auto h5_a = r->‘å–C;
			r->‘å–C = h5_a;
			auto h5_b = r->‘å–C;

			if (h5_a == h5_b) {
				OutputDebugStream("‘å–C‚Æ‘å–C‚ªˆê’v\n");
			}
			else {
				OutputDebugStream("‘å–C‚Æ‘å–C‚ª•sˆê’v\n");
			}

			auto h6_a = r->ˆÏ”CUŒ‚;
			r->ˆÏ”CUŒ‚ = h6_a;
			auto h6_b = r->ˆÏ”CUŒ‚;

			if (h6_a == h6_b) {
				OutputDebugStream("ˆÏ”CUŒ‚‚ÆˆÏ”CUŒ‚‚ªˆê’v\n");
			}
			else {
				OutputDebugStream("ˆÏ”CUŒ‚‚ÆˆÏ”CUŒ‚‚ª•sˆê’v\n");
			}

			auto h7_a = r->ˆÏ”Có‘Ô;
			r->ˆÏ”Có‘Ô = h7_a;
			auto h7_b = r->ˆÏ”Có‘Ô;

			if (h7_a == h7_b) {
				OutputDebugStream("ˆÏ”Có‘Ô‚ÆˆÏ”Có‘Ô‚ªˆê’v\n");
			}
			else {
				OutputDebugStream("ˆÏ”Có‘Ô‚ÆˆÏ”Có‘Ô‚ª•sˆê’v\n");
			}

			auto h8_a = r->•‰•º”;
			r->•‰•º” = h8_a;
			auto h8_b = r->•‰•º”;

			if (h8_a == h8_b) {
				OutputDebugStream("•‰•º”‚Æ•‰•º”‚ªˆê’v\n");
			}
			else {
				OutputDebugStream("•‰•º”‚Æ•‰•º”‚ª•sˆê’v\n");
			}

			auto h9_a = r->ŒR”n;
			r->ŒR”n = h9_a;
			auto h9_b = r->ŒR”n;

			if (h9_a == h9_b) {
				OutputDebugStream("ŒR”n‚ÆŒR”n‚ªˆê’v\n");
			}
			else {
				OutputDebugStream("ŒR”n‚ÆŒR”n‚ª•sˆê’v\n");
			}

			auto h10_a = r->‹à‘K;
			r->‹à‘K = h10_a;
			auto h10_b = r->‹à‘K;

			if (h10_a == h10_b) {
				OutputDebugStream("‹à‘K‚Æ‹à‘K‚ªˆê’v\n");
			}
			else {
				OutputDebugStream("‹à‘K‚Æ‹à‘K‚ª•sˆê’v\n");
			}

			auto h11_a = r->“S–C;
			r->“S–C = h11_a;
			auto h11_b = r->“S–C;

			if (h11_a == h11_b) {
				OutputDebugStream("“S–C‚Æ“S–C‚ªˆê’v\n");
			}
			else {
				OutputDebugStream("“S–C‚Æ“S–C‚ª•sˆê’v\n");
			}

			auto h12_a = r->–hŒä;
			r->–hŒä = h12_a;
			auto h12_b = r->–hŒä;

			if (h12_a == h12_b) {
				OutputDebugStream("–hŒä‚Æ–hŒä‚ªˆê’v\n");
			}
			else {
				OutputDebugStream("–hŒä‚Æ–hŒä‚ª•sˆê’v\n");
			}

			auto h13_a = r->ˆÏ”CUŒ‚–Ú•Wé”z—ñIX;
			r->ˆÏ”CUŒ‚–Ú•Wé”z—ñIX = h13_a;
			auto h13_b = r->ˆÏ”CUŒ‚–Ú•Wé”z—ñIX;

			if (h13_a == h13_b) {
				OutputDebugStream("ˆÏ”CUŒ‚–Ú•Wé”z—ñIX‚ÆˆÏ”CUŒ‚–Ú•Wé”z—ñIX‚ªˆê’v\n");
			}
			else {
				OutputDebugStream("ˆÏ”CUŒ‚–Ú•Wé”z—ñIX‚ÆˆÏ”CUŒ‚–Ú•Wé”z—ñIX‚ª•sˆê’v\n");
			}

			r->ˆÏ”CUŒ‚–Ú•Wé”z—ñIX = 0xFFFF;
			auto h13_c = r->ˆÏ”CUŒ‚–Ú•Wé”z—ñIX;

			if (h13_c == 0xFFFF) {
				OutputDebugStream("ˆÏ”CUŒ‚–Ú•Wé”z—ñIX‚Æ0xFFFF‚ªˆê’v\n");
			}
			else {
				OutputDebugStream("ˆÏ”CUŒ‚–Ú•Wé”z—ñIX‚Æ0xFFFF‚ª•sˆê’v\n");
			}

			auto h14_a = r->Š‘®‘å–¼”z—ñIX;
			r->Š‘®‘å–¼”z—ñIX = h14_a;
			auto h14_b = r->Š‘®‘å–¼”z—ñIX;

			if (h14_a == h14_b) {
				OutputDebugStream("Š‘®‘å–¼”z—ñIX‚ÆŠ‘®‘å–¼”z—ñIX‚ªˆê’v\n");
			}
			else {
				OutputDebugStream("Š‘®‘å–¼”z—ñIX‚ÆŠ‘®‘å–¼”z—ñIX‚ª•sˆê’v\n");
			}

			r->Š‘®‘å–¼”z—ñIX = 0xFFFF;
			auto h14_c = r->Š‘®‘å–¼”z—ñIX;

			if (h14_c == 0xFFFF) {
				OutputDebugStream("Š‘®‘å–¼”z—ñIX‚Æ0xFFFF‚ªˆê’v\n");
			}
			else {
				OutputDebugStream("Š‘®‘å–¼”z—ñIX‚Æ0xFFFF‚ª•sˆê’v\n");
			}


			auto h15_a = r->ŠJnƒ†ƒjƒbƒg”z—ñIX;
			r->ŠJnƒ†ƒjƒbƒg”z—ñIX = h15_a;
			auto h15_b = r->ŠJnƒ†ƒjƒbƒg”z—ñIX;

			if (h15_a == h15_b) {
				OutputDebugStream("ŠJnƒ†ƒjƒbƒg”z—ñIX‚ÆŠJnƒ†ƒjƒbƒg”z—ñIX‚ªˆê’v\n");
			}
			else {
				OutputDebugStream("ŠJnƒ†ƒjƒbƒg”z—ñIX‚ÆŠJnƒ†ƒjƒbƒg”z—ñIX‚ª•sˆê’v\n");
			}
		}

	}
	/*
	for (int iCastleID = 0; iCastleID < Å‘å”::éî•ñ::”z—ñ”; iCastleID++) {
		if (nb7éî•ñ[iCastleID].é–¼ == "•l¼"s) {
			OutputDebugStream("•l¼‚ÌˆÏ”C:%d\n", (int)nb7éî•ñ[iCastleID].ˆÏ”Có‘Ô);
			OutputDebugStream("•l¼‚ÌˆÏ”CUŒ‚:%d\n", (int)nb7éî•ñ[iCastleID].ˆÏ”CUŒ‚);
			OutputDebugStream("•l¼‚ÌˆÏ”CH:%d\n", (int)nb7éî•ñ[iCastleID].unused1);
		}
	}
	*/

	/*
	for (int iBushouID = 0; iBushouID < Å‘å”::•«î•ñ::”z—ñ”; iBushouID++) {

		if (getBushou©–¼FromBushouID(iBushouID) == "D“cM’·") {
			OutputDebugStream("D“cM’·‚Ì•«”Ô† %x\n", iBushouID);
		}
		if (getBushou©–¼FromBushouID(iBushouID) == "¡ì‹`Œ³") {
			OutputDebugStream("¡ì‹`Œ³‚Ì•«”Ô† %x\n", iBushouID);
		}
		if (getBushou©–¼FromBushouID(iBushouID) == "•“cMŒº") {
			OutputDebugStream("•“cMŒº‚Ì•«”Ô† %x\n", iBushouID);
		}
	}
	*/

	/*
	for (int iBushouID = 0; iBushouID < Å‘å”::•«î•ñ::”z—ñ”; iBushouID++) {
		OutputDebugStream(nb7•«î•ñ[iBushouID].©–¼);
		OutputDebugStream("\n");

		if (getBushou•cšFromBushouID(iBushouID) == "É‘Š") {
			OutputDebugStream("•«ID:" + getBushou©–¼FromBushouID(iBushouID));
			OutputDebugStream("­¡:%d ", nb7•«î•ñ[iBushouID].­¡);
			OutputDebugStream("í“¬:%d ", nb7•«î•ñ[iBushouID].í“¬);
			OutputDebugStream("’m–d:%d ", nb7•«î•ñ[iBushouID].’q–d);
			OutputDebugStream("E‹Æ:%d ", nb7•«î•ñ[iBushouID].E‹Æ);
			OutputDebugStream("\n");

			for (int iKahouID = 0; iKahouID < Å‘å”::‰Æ•óî•ñ::”z—ñ”; iKahouID++) {
				if (string(nb7‰Æ•óî•ñ[iKahouID].‰Æ•ó–¼).find("ƒ¥ƒ¦") != string::npos) {
					// strcpy(nb7‰Æ•óî•ñ[iKahouID].‰Æ•ó–¼, "ƒ¨ƒ¥ƒ¦ƒ©ƒ§ƒª");
					// setBushouIDToKahouID(iKahouID, iBushouID);
				}
			}
		}

	}
	*/

	/*
	for (int iKahouID = 0; iKahouID < Å‘å”::‰Æ•óî•ñ::”z—ñ”; iKahouID++) {
		OutputDebugStream("‰Æ•ó–¼:%s ", nb7‰Æ•óî•ñ[iKahouID].‰Æ•ó–¼);
		// OutputDebugStream("•º‰ÈŒø‰Ê:%d ", nb7‰Æ•óî•ñ[iKahouID].•º‰ÈŒø‰Ê);
		// OutputDebugStream("“™‹‰:%d ", nb7‰Æ•óî•ñ[iKahouID].“™‹‰);
		// OutputDebugStream("‰æ‘œ:%d ", nb7‰Æ•óî•ñ[iKahouID].‰æ‘œ);
		// OutputDebugStream("ã¸”\—Í’l:%d ", nb7‰Æ•óî•ñ[iKahouID].”\—Íã¸);
		// OutputDebugStream("‰Æ•óí—Ş:%d", nb7‰Æ•óî•ñ[iKahouID].í—Ş);
		// if (nb7‰Æ•óî•ñ[iKahouID].“ì”Ø) OutputDebugStream("•s–¾3:%d", nb7‰Æ•óî•ñ[iKahouID].“ì”Ø);
		int iBushouID = getBushouIDFromKahouID(iKahouID);
		if (0 <= iBushouID && iBushouID < Å‘å”::•«î•ñ::”z—ñ”) {
			// OutputDebugStream("Š—LÒ:%s ", nb7•«î•ñ[iBushouID].©–¼);
		} else {
			OutputDebugStream("Š—LÒ:%x\n", nb7‰Æ•óî•ñ[iKahouID].pŠ—LÒ);
		}	
		// OutputDebugStream("‰Æ•ó”Ô†:%d ", nb7‰Æ•óî•ñ[iKahouID].‰Æ•ó”Ô†);
		// OutputDebugStream("‰Æ•óÅ‘å”:%d ", nb7‰Æ•óî•ñ[iKahouID].‰Æ•ó”Ô†MAX);
		// OutputDebugStream("\n");
	}
	*/

	/*
	for (int iKanniID = 0; iKanniID < Å‘å”::Š¯ˆÊî•ñ::”z—ñ”; iKanniID++) {
		OutputDebugStream("%s", nb7Š¯ˆÊî•ñ[iKanniID].Š¯ˆÊ–¼);
		OutputDebugStream("ŠKˆÊ:%d\n", nb7Š¯ˆÊî•ñ[iKanniID].ŠKˆÊ);
		OutputDebugStream("Š¯ˆÊ”Ô†:%d ", nb7Š¯ˆÊî•ñ[iKanniID].Š¯ˆÊ”Ô†);
		OutputDebugStream("\n");
		int iBushouID = getBushouIDFromKanniID(iKanniID);
		if (0 <= iBushouID && iBushouID < Å‘å”::•«î•ñ::”z—ñ”) {

			OutputDebugStream("Š—LÒ:%s ", nb7•«î•ñ[iBushouID].©–¼);
		}
	}
	*/

	/*
	for (int iYakusyokuID = 0; iYakusyokuID < Å‘å”::–ğEî•ñ::”z—ñ”; iYakusyokuID++) {
		OutputDebugStream("–ğE–¼:%s ", nb7–ğEî•ñ[iYakusyokuID].–ğE–¼);
		OutputDebugStream("–ğE”Ô†:%d ", nb7–ğEî•ñ[iYakusyokuID].–ğE”Ô†);
		OutputDebugStream("–ğˆÊ:%d ", nb7–ğEî•ñ[iYakusyokuID].–ğˆÊ);
		int iBushouID = getBushouIDFromYakusyokuID(iYakusyokuID);
		OutputDebugStream("%d", iBushouID);
		if ( 0 <= iBushouID && iBushouID < Å‘å”::•«î•ñ::”z—ñ”) {

			OutputDebugStream("Š—LÒ:%s ", nb7•«î•ñ[iBushouID].©–¼);
		}
		OutputDebugStream("\n");
	}
	*/

	/*
	for (int iCastleID = 0; iCastleID < Å‘å”::éî•ñ::”z—ñ”; iCastleID++) {
		OutputDebugStream("é–¼:%s", nb7éî•ñ[iCastleID].é–¼);
		OutputDebugStream(getéÌ(iCastleID) + "\n");
	}
	*/

	/*

	for (int iUnitID = 0; iUnitID < Å‘å”::ƒ†ƒjƒbƒgî•ñ::”z—ñ”; iUnitID++) {
		int iBushouID = getBushouIDFromUnitID(iUnitID);
		if (iBushouID != 0xFFFF) {
			OutputDebugStream("ƒ†ƒjƒbƒg”Ô†:%d ", nb7ƒ†ƒjƒbƒgî•ñ[iUnitID].ƒ†ƒjƒbƒg”Ô†);
			int iBushouID = getBushouIDFromUnitID(iUnitID);
			if (isValidBushouID(iBushouID)) {
				OutputDebugStream("%s", nb7•«î•ñ[iBushouID].©–¼);
				OutputDebugStream("ƒ†ƒjƒbƒg‘å–C:%d \n", nb7ƒ†ƒjƒbƒgî•ñ[iUnitID].‘å–C);
				OutputDebugStream("ƒ†ƒjƒbƒg“Sb‘D:%d \n", nb7ƒ†ƒjƒbƒgî•ñ[iUnitID].“Sb‘D);
				OutputDebugStream("ƒ†ƒjƒbƒg‹à‘K:%d \n", nb7ƒ†ƒjƒbƒgî•ñ[iUnitID].‹à‘K);
				OutputDebugStream("ƒ†ƒjƒbƒg•º—Æ:%d \n", nb7ƒ†ƒjƒbƒgî•ñ[iUnitID].•º—Æ);
				int pNextUnit = (int)nb7ƒ†ƒjƒbƒgî•ñ[iUnitID].pŸ‚Ìƒ†ƒjƒbƒg;
				int iNextUnitID = getUnitIDFromUnitPtr(nb7ƒ†ƒjƒbƒgî•ñ[iUnitID].pŸ‚Ìƒ†ƒjƒbƒg);
				if (isValidUnitID(iNextUnitID)) {
					OutputDebugStream("Ÿ‚Ìƒ†ƒjƒbƒg:%d \n", getUnitIDFromUnitPtr(nb7ƒ†ƒjƒbƒgî•ñ[iUnitID].pŸ‚Ìƒ†ƒjƒbƒg));
				} else {
					OutputDebugStream("šŸ‚Ìƒ†ƒjƒbƒg‚Í‚È‚µ:%x\n", nb7ƒ†ƒjƒbƒgî•ñ[iUnitID].pŸ‚Ìƒ†ƒjƒbƒg);
				}
			}
		}
	}
	*/

	/*
	auto ret = getƒQ[ƒ€‰æ–ÊƒXƒe[ƒ^ƒX();
	OutputDebugStream("ƒQ[ƒ€‰æ–ÊƒXƒe[ƒ^ƒX: %d", (int)ret);

	for (int iUnitID = 0; iUnitID < Å‘å”::ƒ†ƒjƒbƒgî•ñ::”z—ñ”; iUnitID++) {
		int iBushouID = getBushouIDFromUnitID(iUnitID);
		if (0 <= iBushouID && iBushouID < Å‘å”::•«î•ñ::”z—ñ”) {
			if (getBushou©–¼FromBushouID(iBushouID) == getArubedoSeiMei()) {

				nb7ƒ†ƒjƒbƒgî•ñ[iUnitID].“Sb‘D = 1;
			}
		}
	}
	*/

	/*
	for (int iDaimyoID = 0; iDaimyoID < Å‘å”::ƒ†ƒjƒbƒgî•ñ::”z—ñ”; iDaimyoID++) {
		int iBushouID = getBushouIDFromDaimyoID(iDaimyoID);
		if ( isValidBushouID(iBushouID) ) {
			OutputDebugStream("©–¼:%s\n", nb7•«î•ñ[iBushouID].©–¼);
		}
	}
	*/

	/*
	for (int iDaimyouID = 0; iDaimyouID < Å‘å”::‘å–¼î•ñ::”z—ñ”; iDaimyouID++) {
		// if (nb7‘å–¼î•ñ[iDaimyouID].ƒvƒŒƒCƒ„’S“– > 0) {
		if (nb7‘å–¼î•ñ[iDaimyouID].unknown17) {
			OutputDebugStream("”Ô†:%d\t", iDaimyouID);
			OutputDebugStream("‘å–¼:%s\n", nb7‘å–¼î•ñ[iDaimyouID].p‘å–¼•«);
			OutputDebugStream("unknown17:%d\n", nb7‘å–¼î•ñ[iDaimyouID].unknown17);
		}
		if (nb7‘å–¼î•ñ[iDaimyouID].unknown18) {
			OutputDebugStream("”Ô†:%d\t", iDaimyouID);
			OutputDebugStream("‘å–¼:%s\n", nb7‘å–¼î•ñ[iDaimyouID].p‘å–¼•«);
			OutputDebugStream("unknown18:%d\n", nb7‘å–¼î•ñ[iDaimyouID].unknown18);
		}
	}
	*/
}

