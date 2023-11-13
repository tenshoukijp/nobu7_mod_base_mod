
#include <windows.h>
#include <string>
#include "data_game_struct.h"
#include "data_bushou_struct.h"
#include "output_debug_stream.h"
#include "data_kahou_struct.h"

using namespace std;

NB7•«î•ñŒ^* nb7•«î•ñ = (NB7•«î•ñŒ^*)(•«î•ñƒAƒhƒŒƒX); // data_bushou_struct‚É‚±‚ÌƒAƒhƒŒƒX‚Ì——R‚ª‚ ‚é
NB7‰Æ•óî•ñŒ^* nb7‰Æ•óî•ñ = (NB7‰Æ•óî•ñŒ^*)(0x5871B0); // data_kahou_struct‚É‚±‚ÌƒAƒhƒŒƒX‚Ì——R‚ª‚ ‚é

void setGameDataStructPointer() {

	for (int iBushouID = 0; iBushouID < Å‘å”::•«î•ñ::”z—ñ”; iBushouID++) {
		if (string(nb7•«î•ñ[iBushouID].•cš) == string("É‘Š")) {
			OutputDebugStream("ššš\n");
			OutputDebugStream("“à‹Z1:%d\n", nb7•«î•ñ[iBushouID].“à‹Z”_‹Æ);
			OutputDebugStream("“à‹Z2:%d\n", nb7•«î•ñ[iBushouID].“à‹Z¤‹Æ);
			OutputDebugStream("“à‹Z3:%d\n", nb7•«î•ñ[iBushouID].“à‹ZŒšİ);
			OutputDebugStream("“à‹Z4:%d\n", nb7•«î•ñ[iBushouID].“à‹ZŠOŒğ);	
			OutputDebugStream("“à‹Z5:%d\n", nb7•«î•ñ[iBushouID].“à‹Z“o—p);
			OutputDebugStream("“à‹Z6:%d\n", nb7•«î•ñ[iBushouID].í‹Z”²ŒŠ);

			OutputDebugStream("í‹Z1:%d\n", nb7•«î•ñ[iBushouID].í‹Z‹R“Ë);
			OutputDebugStream("í‹Z2:%d\n", nb7•«î•ñ[iBushouID].í‹ZO’i);
			OutputDebugStream("í‹Z3:%d\n", nb7•«î•ñ[iBushouID].í‹Zà„à€);
			OutputDebugStream("í‹Z4:%d\n", nb7•«î•ñ[iBushouID].í‹Z‹R“S);
		}
		/*
		OutputDebugStream("•«ID:%s ", nb7•«î•ñ[iBushouID].–¼‘O);
		OutputDebugStream("­¡:%d ", nb7•«î•ñ[iBushouID].­¡);
		OutputDebugStream("í“¬:%d ", nb7•«î•ñ[iBushouID].í“¬);
		OutputDebugStream("’m–d:%d ", nb7•«î•ñ[iBushouID].’q–d);
		OutputDebugStream("E‹Æ:%d ", nb7•«î•ñ[iBushouID].E‹Æ);
		OutputDebugStream("«•Ê:%s ", nb7•«î•ñ[iBushouID].«•Ê ? "—":"’j");
		OutputDebugStream("\n");
		*/
	}


	/*
	for (int iKahouID = 0; iKahouID < Å‘å”::‰Æ•óî•ñ::”z—ñ”; iKahouID++) {
		OutputDebugStream("‰Æ•ó–¼:%s ", nb7‰Æ•óî•ñ[iKahouID].‰Æ•ó–¼);
		OutputDebugStream("•º‰ÈŒø‰Ê:%d ", nb7‰Æ•óî•ñ[iKahouID].•º‰ÈŒø‰Ê);
		OutputDebugStream("“™‹‰:%d ", nb7‰Æ•óî•ñ[iKahouID].“™‹‰);
		OutputDebugStream("ƒOƒ‰ƒtƒBƒbƒN”Ô†:%d ", nb7‰Æ•óî•ñ[iKahouID].ƒOƒ‰ƒtƒBƒbƒN”Ô†);
		OutputDebugStream("ã¸”\—Í’l:%d ", nb7‰Æ•óî•ñ[iKahouID].ã¸”\—Í’l);
		OutputDebugStream("‰Æ•óí—Ş:%d ", nb7‰Æ•óî•ñ[iKahouID].‰Æ•óí—Ş);
		int iBushouID = getBushouIDFromKahouID(iKahouID);
		if (0 <= iBushouID && iBushouID < Å‘å”::•«î•ñ::”z—ñ”) {
			OutputDebugStream("Š—LÒ:%s ", nb7•«î•ñ[iBushouID].©–¼);
		}
		OutputDebugStream("‰Æ•ó”Ô†:%d ", nb7‰Æ•óî•ñ[iKahouID].‰Æ•ó”Ô†);
		OutputDebugStream("‰Æ•óÅ‘å”:%d ", nb7‰Æ•óî•ñ[iKahouID].‰Æ•óÅ‘å”);
		OutputDebugStream("”\—ÍŒø‰Ê:%d ", (int)nb7‰Æ•óî•ñ[iKahouID].”\—ÍŒø‰Ê);
		OutputDebugStream("\n");
	}
	*/
}

