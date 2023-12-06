extern void WriteAsmJumperOnSSRExeMessageDetail();
extern void WriteAsmJumperOnSSRExeYasenTurnChange();
extern void WriteAsmJumperOnSSRExeYasenTurnBothBushou();
extern void WriteAsmJumperOnSSRExeYasenTurnButaiOf1to5();
extern void WriteAsmJumperOnSSRExeMovieFileName();
extern void WriteAsmJumperOnSSRExeUnknownDialog1();
extern void WriteAsmJumperOnSSRExeUnknownDialog2();
extern void WriteAsmJumperOnSSRExeUnknownDialog3();


bool isWriteAsmJumperOnSSRExeMessageDetail = false;
bool isWriteAsmJumperOnSSRExeYasenTurnChange = false;
bool isWriteAsmJumperOnSSRExeYasenTurnBothBushou = false;
bool isWriteAsmJumperOnSSRExeYasenTurnButaiOf1to5 = false;
bool isWriteAsmJumperOnSSRExeMovieFileName = false;
bool isWriteAsmJumperOnSSRExeUnknownDialog1 = false;
bool isWriteAsmJumperOnSSRExeUnknownDialog2 = false;
bool isWriteAsmJumperOnSSRExeUnknownDialog3 = false;

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

	if (!isWriteAsmJumperOnSSRExeMovieFileName) {
		isWriteAsmJumperOnSSRExeMovieFileName = true;
		WriteAsmJumperOnSSRExeMovieFileName();
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
}