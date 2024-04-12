#include <windows.h>
#include <string>
#include "data_game_struct.h"
#include "output_debug_stream.h"
#include "game_process.h"
#include "game_screen.h"
#include "message_albedo.h"
#include "file_attribute.h"
#include "usr_custom_mod.h"

using namespace std;



/*
ƒ€[ƒr[ƒtƒ@ƒCƒ‹–Ό‚Μƒ|ƒCƒ“ƒ^”z—ρ‚πQΖ‚µ‚Δ‚Ά‚ι‚Ζ‚±‚λ
00419AF9   77 07            JA SHORT Nobunaga.00419B02
00419AFB   8B048D 2C855300  MOV EAX,DWORD PTR DS:[ECX*4+53852C]
00419B02   C3               RETN
00419B03   CC               INT3
00419B04   CC               INT3


ƒ€[ƒr[ƒtƒ@ƒCƒ‹Q‚Φ‚Μƒ|ƒCƒ“ƒ^‚Μ”z—ρ
00538520  00 00 00 00 00 00 00 00 00 00 00 00 3C 10 52 00  ............<R.
00538530  28 10 52 00 14 10 52 00 00 10 52 00 EC 0F 52 00  (R.R..R.ER.
00538540  D8 0F 52 00 C4 0F 52 00 B0 0F 52 00 9C 0F 52 00  ΨR.ΔR.°R.ER.
00538550  88 0F 52 00 08 9A 52 00 00 00 00 00              ER.R......?



ƒ€[ƒr[‚Μƒtƒ@ƒCƒ‹Q‚Μ”z—ρ
00520F88  4D 6F 76 69 65 5C 45 6E 64 69 6E 67 2E 61 76 69  Movie\Ending.avi
00520F98  00 00 00 00 4D 6F 76 69 65 5C 4F 70 65 6E 69 6E  ....Movie\Openin
00520FA8  67 2E 61 76 69 00 00 00 4D 6F 76 69 65 5C 54 65  g.avi...Movie\Te
00520FB8  70 70 6F 75 2E 61 76 69 00 00 00 00 4D 6F 76 69  ppou.avi....Movi
00520FC8  65 5C 43 68 72 69 73 74 2E 61 76 69 00 00 00 00  e\Christ.avi....
00520FD8  4D 6F 76 69 65 5C 53 61 6E 73 68 69 2E 61 76 69  Movie\Sanshi.avi
00520FE8  00 00 00 00 4D 6F 76 69 65 5C 4B 61 69 6D 65 69  ....Movie\Kaimei
00520FF8  2E 61 76 69 00 00 00 00 4D 6F 76 69 65 5C 4B 69  .avi....Movie\Ki
00521008  79 6F 73 75 2E 61 76 69 00 00 00 00 4D 6F 76 69  yosu.avi....Movi
00521018  65 5C 48 41 66 74 65 72 32 2E 61 76 69 00 00 00  e\HAfter2.avi...
00521028  4D 6F 76 69 65 5C 48 41 66 74 65 72 31 2E 61 76  Movie\HAfter1.av
00521038  69 00 00 00 4D 6F 76 69 65 5C 48 6F 6E 6E 6F 75  i...Movie\Honnou
00521048  6A 69 2E 61 76 69                                ji.avi
*/


int iMovieFileNameCharPointer = NULL;

char bufOverrideMovieName[512] = "";

std::string getUserCustomMovieFileName(System::String^ movie_filename) {
	bool isUserCustomOverride = false;
	try {
		System::Collections::Generic::Dictionary<System::String^, System::Object^>^ dic = gcnew System::Collections::Generic::Dictionary<System::String^, System::Object^>(5);
		dic->Add("ƒtƒ@ƒCƒ‹–Ό", movie_filename);
		System::Collections::Generic::Dictionary<System::String^, System::Object^>^ ret = InvokeUserMethod("onƒ€[ƒr[—v‹", dic);

		if (ret != nullptr && ret->ContainsKey("ƒtƒ@ƒCƒ‹–Ό")) {
			System::String^ filename = (System::String^)(ret["ƒtƒ@ƒCƒ‹–Ό"]);
			if (System::String::IsNullOrEmpty(filename)) {
				return "";
			}

			return to_native_string(filename);
		}

	}
	catch (System::Exception^ ) {
		OutputDebugStream("onƒ€[ƒr[ƒtƒ@ƒCƒ‹—v‹‚ΕƒGƒ‰[");
	}

	return "";
}

void OnSSRExeMovieFileNameExecute() {
	OutputDebugStream("ƒ€[ƒr[ƒtƒ@ƒCƒ‹–Ό‚Μζ“Ύ:");
	OutputDebugStream("’l %x\n", iMovieFileNameCharPointer);
	OutputDebugStream("’l %s\n", iMovieFileNameCharPointer);

	if (iMovieFileNameCharPointer != NULL) {

		std::string userCustomMovieName = getUserCustomMovieFileName(gcnew System::String((char*)iMovieFileNameCharPointer));
		if (userCustomMovieName != "" && isFileExists(userCustomMovieName)) {
			OutputDebugStream("ƒ†[ƒU[ƒJƒXƒ^ƒ€‚Μƒ€[ƒr[ƒtƒ@ƒCƒ‹–Ό‚ª‘¶έ‚·‚ι‚Μ‚ΕA‚»‚κ‚πg‚¤\n");
			strcpy_s(bufOverrideMovieName, userCustomMovieName.c_str());
			iMovieFileNameCharPointer = (int)bufOverrideMovieName;
			return;
		}

		string overrideMovieName = string("OVERRIDE\\") + string((char*)iMovieFileNameCharPointer);
		if (isFileExists(overrideMovieName)) {
			OutputDebugStream("ƒI[ƒo[ƒ‰ƒCƒhƒtƒ@ƒCƒ‹‚ª‘¶έ‚·‚ι‚Μ‚ΕA‚»‚κ‚πg‚¤\n");
			strcpy_s(bufOverrideMovieName, overrideMovieName.c_str());
			iMovieFileNameCharPointer = (int)bufOverrideMovieName;
			return;
		}
	}
}

#pragma unmanaged


/*
00419AF9   77 07            JA SHORT Nobunaga.00419B02
00419AFB   8B048D 2C855300  MOV EAX,DWORD PTR DS:[ECX*4+53852C]
00419B02   C3               RETN
*/

int pSSRExeJumpFromToOnSSRExeMovieFileName = 0x419AFB; // Φ”‚Ν‚±‚ΜƒAƒhƒƒX‚©‚ηAOnSSRExeMovieFileName‚Φ‚ΖƒWƒƒƒ“ƒv‚µ‚Δ‚­‚ιB
int pSSRExeReturnLblFromOnSSRExeMovieFileName = 0x419B02; // Φ”‚ªΕγ‚ά‚Ε‚Ά‚­‚ΖA‚±‚Μΐsexe“ΰ‚Ι’ΌΪƒWƒƒƒ“ƒv‚·‚ι

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeMovieFileName() {
	// ƒXƒ^ƒbƒN‚Ι‚½‚ί‚Δ‚¨‚­
	__asm {
		MOV EAX, DWORD PTR DS : [ECX*4 + 0x53852C] // ³X‚Μ—‚π‚±‚±‚Ι
		mov iMovieFileNameCharPointer, EAX // ƒtƒ@ƒCƒ‹–Ό‚Φ‚Μƒ|ƒCƒ“ƒ^‚π•Ϋ‘¶‚µ‚Δ‚¨‚­
		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeMovieFileNameExecute();

	// ƒXƒ^ƒbƒN‚Ιψ‚«o‚·
	__asm {
		pop edi
		pop esi
		pop ebp
		pop esp
		pop edx
		pop ecx
		pop ebx
		pop eax

		MOV EAX, iMovieFileNameCharPointer; // ƒtƒ@ƒCƒ‹ƒ|ƒCƒ“ƒ^‚πγ‘‚«‚µ‚Δ‚Ά‚ι‚©‚ΰ‚µ‚κ‚Θ‚Ά‚Μ‚ΕEAX‚Ι“]Κ(γ‘‚«‚µ‚Δ‚Θ‚―‚κ‚Ξ³XEAX‚Ζ“―‚¶’l‚ª“ό‚Α‚Δ‚Ά‚ι)

		jmp pSSRExeReturnLblFromOnSSRExeMovieFileName
	}
}
#pragma warning(default: 4733) // ƒ[ƒjƒ“ƒO‚Μ—}§‚π‰π‚·‚ι



char cmdOnSSRExeJumpFromMovieFileName[8] = "\xE9\x90\x90\x90\x90\x90\x90";
// ³‚Μ–½—ί‚ª5ƒoƒCƒgAΘγ‚ΜΦ”‚Ε¶‚ά‚κ‚ι–½—ί‚ª‡v‚TƒoƒCƒg‚Θ‚Μ‚Εc Εγ‚P‚Βg‚ν‚Θ‚Ά


// ƒj[ƒ‚ƒjƒbƒN‘‚«·‚¦—p
void WriteAsmJumperOnSSRExeMovieFileName() {

	// ‚ά‚ΈƒAƒhƒƒX‚π”‚Ζ‚µ‚Δµ‚¤
	int iAddress = (int)OnSSRExeMovieFileName;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeMovieFileName + 5);
	// ‚T‚Ζ‚Ά‚¤‚Μ‚ΝA0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  ‚Μ–½—ί‚Ι•K—v‚ΘƒoƒCƒg”B—v‚·‚ι‚Ι‚TƒoƒCƒg‘«‚·‚Ζ‚Μƒj[ƒ‚ƒjƒbƒN–½—ίQ‚ΙΪ“®‚·‚ι‚Μ‚ΎB‚»‚µ‚Δ‚»‚±‚©‚η‚Μ·•ª‚ªƒWƒƒƒ“ƒv‚·‚ιΫ‚Μ–Ϊ“Ii‚Ζ‚µ‚Δ——p‚³‚κ‚ιB
	memcpy(cmdOnSSRExeJumpFromMovieFileName + 1, &SubAddress, 4); // +1 ‚ΝE9‚Μ‚©‚η4ƒoƒCƒg•ª‘‚«·‚¦‚ι‚©‚ηB

	// \’z‚µ‚½ƒj[ƒ‚ƒjƒbƒN–½—ί‚πTENSHOU.EXE‚Μƒƒ‚ƒ‚Ι‘‚«·‚¦‚ι
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeMovieFileName), cmdOnSSRExeJumpFromMovieFileName, 7, NULL);
	//7ƒoƒCƒg‚Μ‚έ‘‚«‚ή
	// 00419AFB   8B048D 2C855300  MOV EAX,DWORD PTR DS:[ECX*4+53852C]@‚ª 7ƒoƒCƒg‚ ‚ι‚Μ‚ΕγY—ν‚Ι‘‚«·‚¦‚Δ‚¨‚­
}

#pragma managed
