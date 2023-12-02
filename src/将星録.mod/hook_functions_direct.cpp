extern void WriteAsmJumperOnSSRExeMessageDetail();
extern void WriteAsmJumperOnSSRExeUnknownDialog1();
extern void WriteAsmJumperOnSSRExeUnknownDialog2();
extern void WriteAsmJumperOnSSRExeUnknownDialog3();


bool isWriteAsmJumperOnSSRExeMessageDetail = false;
bool isWriteAsmJumperOnSSRExeUnknownDialog1 = false;
bool isWriteAsmJumperOnSSRExeUnknownDialog2 = false;
bool isWriteAsmJumperOnSSRExeUnknownDialog3 = false;

void hookFunctionsDirect() {

	if (!isWriteAsmJumperOnSSRExeMessageDetail) {
		isWriteAsmJumperOnSSRExeMessageDetail = true;
		WriteAsmJumperOnSSRExeMessageDetail();
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