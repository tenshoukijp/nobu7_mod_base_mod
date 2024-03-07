#include "hook_setfilepointer_custom_winframe.h"

#include "output_debug_stream.h"

using namespace std;

/*
unique_ptr<WINFRAME_NB7_HEADER> winframe_nb7_header = make_unique<WINFRAME_NB7_HEADER>();
BOOL WinFrameHeaderCopied = FALSE;
void hook_setfilepointer_custom_winframe(LPVOID lpBuffer, DWORD nNumberOfBytesToRead) {
	if (nNumberOfBytesToRead == sizeof(WINFRAME_NB7_HEADER)) {
		OutputDebugStream("WINFRAME.NB7のヘッダーをコピー!\n");
		memcpy(winframe_nb7_header.get(), lpBuffer, sizeof(WINFRAME_NB7_HEADER));
		WinFrameHeaderCopied = TRUE;
	}
}
*/