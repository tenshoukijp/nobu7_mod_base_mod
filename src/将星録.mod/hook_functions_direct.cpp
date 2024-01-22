extern void WriteAsmJumperOnSSRExeMessageDetail();
extern void WriteAsmJumperOnSSRExeYasenTurnChange();
extern void WriteAsmJumperOnSSRExeYasenTurnBothBushou();
extern void WriteAsmJumperOnSSRExeYasenTurnButaiOf1to5();
extern void WriteAsmJumperOnSSRExeCastleBattleTurnBgn();
extern void WriteAsmJumperOnSSRExeCastleBattleTurn();
extern void WriteAsmJumperOnSSRExeCastleBattleTurnDaimyoA();
extern void WriteAsmJumperOnSSRExeCastleBattleTurnDaimyoB();
extern void WriteAsmJumperOnSSRExeMovieFileName();
extern void WriteAsmJumperOnSSRExePlayBGM();
extern void WriteAsmJumperOnSSRExePlayBGM2();
extern void WriteAsmJumperOnSSRExePlayBGM3();
extern void WriteAsmJumperOnSSRExeKahouShowBgn();
extern void WriteAsmJumperOnSSRExeKahouShowPic();
extern void WriteAsmJumperOnSSRExeKahouShowEnd();
extern void WriteAsmJumperOnSSRExeUnknownDialog1();
extern void WriteAsmJumperOnSSRExeUnknownDialog2();
extern void WriteAsmJumperOnSSRExeUnknownDialog3();
extern void WriteAsmJumperOnSSRExeShowDIBitmap();
extern void WriteAsmJumperOnSSRExeGetYasenHeisuu1();
extern void WriteAsmJumperOnSSRExeWriteYear();
extern void WriteAsmJumperOnSSRExeWriteMonth();
extern void WriteAsmJumperOnSSRExeWriteSobaKome();
extern void WriteAsmJumperOnSSRExeWriteSobaUma();
extern void WriteAsmJumperOnSSRExeWriteSobaTeppou();
extern void WriteAsmJumperOnSSRExeUpdateMonth();
extern void WriteAsmJumperOnSSRExeUpdateSobaKome();
extern void WriteAsmJumperOnSSRExeUpdateSobaUma();
extern void WriteAsmJumperOnSSRExeUpdateSobaTeppou();
extern void WriteAsmJumperOnSSRExeBushouKoudouzumi();
extern void WriteAsmJumperOnSSRExeYasenWeatherChange();
extern void WriteAsmJumperOnSSRExeYasenWeatherWrite();
extern void WriteAsmJumperOnSSRExeKahouTitle();
extern void WriteAsmJumperOnSSRExeKahouDetail();


bool isWriteAsmJumperOnSSRExeMessageDetail = false;
bool isWriteAsmJumperOnSSRExeYasenTurnChange = false;
bool isWriteAsmJumperOnSSRExeYasenTurnBothBushou = false;
bool isWriteAsmJumperOnSSRExeYasenTurnButaiOf1to5 = false;
bool isWriteAsmJumperOnSSRExeCastleBattleTurnBgn = false;
bool isWriteAsmJumperOnSSRExeCastleBattleTurn = false;
bool isWriteAsmJumperOnSSRExeCastleBattleTurnDaimyoA = false;
bool isWriteAsmJumperOnSSRExeCastleBattleTurnDaimyoB = false;
bool isWriteAsmJumperOnSSRExeMovieFileName = false;
bool isWriteAsmJumperOnSSRExePlayBGM = false;
bool isWriteAsmJumperOnSSRExePlayBGM2 = false;
bool isWriteAsmJumperOnSSRExePlayBGM3 = false;
bool isWriteAsmJumperOnSSRExeKahouShowBgn = false;
bool isWriteAsmJumperOnSSRExeKahouShowPic = false;
bool isWriteAsmJumperOnSSRExeKahouShowEnd = false;
bool isWriteAsmJumperOnSSRExeUnknownDialog1 = false;
bool isWriteAsmJumperOnSSRExeUnknownDialog2 = false;
bool isWriteAsmJumperOnSSRExeUnknownDialog3 = false;
bool isWriteAsmJumperOnSSRExeLoadDataResource = false;
bool isWriteAsmJumperOnSSRExeGetYasenHeisuu1 = false;
bool isWriteAsmJumperOnSSRExeWriteYear = false;
bool isWriteAsmJumperOnSSRExeWriteMonth = false;
bool isWriteAsmJumperOnSSRExeWriteSobaKome = false;
bool isWriteAsmJumperOnSSRExeWriteSobaUma = false;
bool isWriteAsmJumperOnSSRExeWriteSobaTeppou = false;
bool isWriteAsmJumperOnSSRExeUpdateMonth = false;
bool isWriteAsmJumperOnSSRExeUpdateSobaKome = false;
bool isWriteAsmJumperOnSSRExeUpdateSobaUma = false;
bool isWriteAsmJumperOnSSRExeUpdateSobaTeppou = false;
bool isWriteAsmJumperOnSSRExeBushouKoudouzumi = false;
bool isWriteAsmJumperOnSSRExeYasenWeatherChange = false;
bool isWriteAsmJumperOnSSRExeYasenWeatherWrite = false;
bool isWriteAsmJumperOnSSRExeKahouTitle = false;
bool isWriteAsmJumperOnSSRExeKahouDetail = false;



void hookFunctionsDirect() {

	if (!isWriteAsmJumperOnSSRExeMessageDetail) {
		isWriteAsmJumperOnSSRExeMessageDetail = true;
		WriteAsmJumperOnSSRExeMessageDetail();
	}

	if (!isWriteAsmJumperOnSSRExeYasenTurnChange) {
		isWriteAsmJumperOnSSRExeYasenTurnChange = true;
		WriteAsmJumperOnSSRExeYasenTurnChange();
	}

	if (!isWriteAsmJumperOnSSRExeYasenTurnBothBushou) {
		isWriteAsmJumperOnSSRExeYasenTurnBothBushou = true;
		WriteAsmJumperOnSSRExeYasenTurnBothBushou();
	}

	if (!isWriteAsmJumperOnSSRExeYasenTurnButaiOf1to5) {
		isWriteAsmJumperOnSSRExeYasenTurnButaiOf1to5 = true;
		WriteAsmJumperOnSSRExeYasenTurnButaiOf1to5();
	}

	if (!isWriteAsmJumperOnSSRExeCastleBattleTurnBgn) {
		isWriteAsmJumperOnSSRExeCastleBattleTurnBgn = true;
		WriteAsmJumperOnSSRExeCastleBattleTurnBgn();
	}

	if (!isWriteAsmJumperOnSSRExeCastleBattleTurn) {
		isWriteAsmJumperOnSSRExeCastleBattleTurn = true;
		WriteAsmJumperOnSSRExeCastleBattleTurn();
	}

	if (!isWriteAsmJumperOnSSRExeCastleBattleTurnDaimyoA) {
		isWriteAsmJumperOnSSRExeCastleBattleTurnDaimyoA = true;
		WriteAsmJumperOnSSRExeCastleBattleTurnDaimyoA();
	}

	if (!isWriteAsmJumperOnSSRExeCastleBattleTurnDaimyoB) {
		isWriteAsmJumperOnSSRExeCastleBattleTurnDaimyoB = true;
		WriteAsmJumperOnSSRExeCastleBattleTurnDaimyoB();
	}

	if (!isWriteAsmJumperOnSSRExeMovieFileName) {
		isWriteAsmJumperOnSSRExeMovieFileName = true;
		WriteAsmJumperOnSSRExeMovieFileName();
	}

	if (!isWriteAsmJumperOnSSRExePlayBGM) {
		isWriteAsmJumperOnSSRExePlayBGM = true;
		WriteAsmJumperOnSSRExePlayBGM();
	}

	if (!isWriteAsmJumperOnSSRExePlayBGM2) {
		isWriteAsmJumperOnSSRExePlayBGM2 = true;
		WriteAsmJumperOnSSRExePlayBGM2();
	}

	if (!isWriteAsmJumperOnSSRExePlayBGM3) {
		isWriteAsmJumperOnSSRExePlayBGM3 = true;
		WriteAsmJumperOnSSRExePlayBGM3();
	}

	if (!isWriteAsmJumperOnSSRExeKahouShowBgn) {
		isWriteAsmJumperOnSSRExeKahouShowBgn = true;
		WriteAsmJumperOnSSRExeKahouShowBgn();
	}

	if (!isWriteAsmJumperOnSSRExeKahouShowPic) {
		isWriteAsmJumperOnSSRExeKahouShowPic = true;
		WriteAsmJumperOnSSRExeKahouShowPic();
	}

	if (!isWriteAsmJumperOnSSRExeKahouShowEnd) {
		isWriteAsmJumperOnSSRExeKahouShowEnd = true;
		WriteAsmJumperOnSSRExeKahouShowEnd();
	}

	if (!isWriteAsmJumperOnSSRExeUnknownDialog1) {
		isWriteAsmJumperOnSSRExeUnknownDialog1 = true;
		WriteAsmJumperOnSSRExeUnknownDialog1();
	}

	if (!isWriteAsmJumperOnSSRExeUnknownDialog2) {
		isWriteAsmJumperOnSSRExeUnknownDialog2 = true;
		WriteAsmJumperOnSSRExeUnknownDialog2();
	}

	if (!isWriteAsmJumperOnSSRExeUnknownDialog3) {
		isWriteAsmJumperOnSSRExeUnknownDialog3 = true;
		WriteAsmJumperOnSSRExeUnknownDialog3();
	}

	if (!isWriteAsmJumperOnSSRExeLoadDataResource) {
		isWriteAsmJumperOnSSRExeLoadDataResource = true;
		WriteAsmJumperOnSSRExeShowDIBitmap();
	}

	if (!isWriteAsmJumperOnSSRExeGetYasenHeisuu1) {
		isWriteAsmJumperOnSSRExeGetYasenHeisuu1 = true;
		WriteAsmJumperOnSSRExeGetYasenHeisuu1();
	}

	if (!isWriteAsmJumperOnSSRExeWriteYear) {
		isWriteAsmJumperOnSSRExeWriteYear = true;
		WriteAsmJumperOnSSRExeWriteYear();
	}

	if (!isWriteAsmJumperOnSSRExeWriteMonth) {
		isWriteAsmJumperOnSSRExeWriteMonth = true;
		WriteAsmJumperOnSSRExeWriteMonth();
	}

	if (!isWriteAsmJumperOnSSRExeWriteSobaKome) {
		isWriteAsmJumperOnSSRExeWriteSobaKome = true;
		WriteAsmJumperOnSSRExeWriteSobaKome();
	}

	if (!isWriteAsmJumperOnSSRExeWriteSobaUma) {
		isWriteAsmJumperOnSSRExeWriteSobaUma = true;
		WriteAsmJumperOnSSRExeWriteSobaUma();
	}

	if (!isWriteAsmJumperOnSSRExeWriteSobaTeppou) {
		isWriteAsmJumperOnSSRExeWriteSobaTeppou = true;
		WriteAsmJumperOnSSRExeWriteSobaTeppou();
	}

	if (!isWriteAsmJumperOnSSRExeUpdateMonth) {
		isWriteAsmJumperOnSSRExeUpdateMonth = true;
		WriteAsmJumperOnSSRExeUpdateMonth();
	}

	if (!isWriteAsmJumperOnSSRExeUpdateSobaKome) {
		isWriteAsmJumperOnSSRExeUpdateSobaKome = true;
		WriteAsmJumperOnSSRExeUpdateSobaKome();
	}

	if (!isWriteAsmJumperOnSSRExeUpdateSobaUma) {
		isWriteAsmJumperOnSSRExeUpdateSobaUma = true;
		WriteAsmJumperOnSSRExeUpdateSobaUma();
	}

	if (!isWriteAsmJumperOnSSRExeUpdateSobaTeppou) {
		isWriteAsmJumperOnSSRExeUpdateSobaTeppou = true;
		WriteAsmJumperOnSSRExeUpdateSobaTeppou();
	}

	if (!isWriteAsmJumperOnSSRExeBushouKoudouzumi) {
		isWriteAsmJumperOnSSRExeBushouKoudouzumi = true;
		WriteAsmJumperOnSSRExeBushouKoudouzumi();
	}

	if (!isWriteAsmJumperOnSSRExeYasenWeatherChange) {
		isWriteAsmJumperOnSSRExeYasenWeatherChange = true;
		WriteAsmJumperOnSSRExeYasenWeatherChange();
	}

	if (!isWriteAsmJumperOnSSRExeYasenWeatherWrite) {
		isWriteAsmJumperOnSSRExeYasenWeatherWrite = true;
		WriteAsmJumperOnSSRExeYasenWeatherWrite();
	}

	if (!isWriteAsmJumperOnSSRExeKahouTitle) {
		isWriteAsmJumperOnSSRExeKahouTitle = true;
		WriteAsmJumperOnSSRExeKahouTitle();
	}

	if (!isWriteAsmJumperOnSSRExeKahouDetail) {
		isWriteAsmJumperOnSSRExeKahouDetail = true;
		WriteAsmJumperOnSSRExeKahouDetail();
	}
}