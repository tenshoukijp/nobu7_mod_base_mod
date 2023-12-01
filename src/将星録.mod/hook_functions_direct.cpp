extern void WriteAsmJumperOnSSRExeMessageDetail();

bool isWriteAsmJumperOnSSRExeMessageDetail = false;

void hookFunctionsDirect() {

	if (!isWriteAsmJumperOnSSRExeMessageDetail) {
		isWriteAsmJumperOnSSRExeMessageDetail = true;
		WriteAsmJumperOnSSRExeMessageDetail();
	}
}