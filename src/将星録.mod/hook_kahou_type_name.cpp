/*
00523F44  8D 81 96 D8 00 00 00 00 92 BF 95 69 00 00 00 00  Ø....¿i....
00523F54  8F 5C 8E 9A 89 CB 00 00 8E 5A 94 D5 00 00 00 00  \Ë..ZÕ....
00523F64  93 EC 94 D8 8E 9E 8C 76 00 00 00 00 97 85 90 6A  ìØv....j
00523F74  94 D5 00 00 92 6E 90 7D 00 00 00 00 8A 47 89 E6  Õ..n}....Gæ
00523F84  00 00 00 00 8F A4 8B C6 8F 91 00 00 8C 52 8B 4C  ....¤Æ..RL
00523F94  95 A8 8C EA 00 00 00 00 95 A7 8B B3 8F 91 00 00  ¨ê....§³..
00523FA4  95 B6 8A 77 8F 91 00 00 8F 40 8B B3 8F 91 00 00  ¶w..@³..
00523FB4  97 F0 8E 6A 8F 91 00 00 8C 9A 92 7A 8F 91 00 00  ðj..z..
00523FC4  8D 7A 8F 70 8F 91 00 00 8A 4F 8C F0 8F 91 00 00  zp..Oð..
00523FD4  94 5F 90 AD 8F 91 00 00 92 6D 8E AF 8F 91 00 00  _­..m¯..
00523FE4  94 45 8F 70 8F 91 00 00 88 E3 8F 70 8F 91 00 00  Ep..ãp..
00523FF4  95 BA 96 40 8F 91 00 00 96 43 8F 70 8F 91 00 00  º@..Cp..
00524004  94 6E 8F 70 8F 91 00 00 8C 95 8F 70 8F 91 00 00  np..p..
00524014  92 5A 93 9B 00 00 00 00 96 BC 94 6E 00 00 00 00  Z....¼n....
00524024  95 BA 91 95 95 69 00 00 95 90 8A ED 00 00 00 00  ºi..í....
00524034  92 83 93 B9 93 B9 8B EF                          ¹¹ï....

*/

/*
ãÌ|C^Ìzñ
0053A8B8  34 40 52 00 2C 40 52 00 24 40 52 00 1C 40 52 00  4@R.,@R.$@R.@R.
0053A8C8  14 40 52 00 0C 40 52 00 04 40 52 00 FC 3F 52 00  @R..@R.@R.ER.
0053A8D8  F4 3F 52 00 EC 3F 52 00 E4 3F 52 00 DC 3F 52 00  ER.ER.ER.Ü?R.
0053A8E8  D4 3F 52 00 CC 3F 52 00 C4 3F 52 00 BC 3F 52 00  Ô?R.Ì?R.Ä?R.¼?R.
0053A8F8  B4 3F 52 00 AC 3F 52 00 A4 3F 52 00 9C 3F 52 00  ´?R.¬?R.¤?R.ER.
0053A908  90 3F 52 00 88 3F 52 00 80 3F 52 00 78 3F 52 00  ER.ER.?R.x?R.
0053A918  70 3F 52 00 64 3F 52 00 5C 3F 52 00 54 3F 52 00  p?R.d?R.\?R.T?R.
0053A928  4C 3F 52 00 44 3F 52 00                          L?R.D?R.

*/

/*
0047C9C0  /$ 51             PUSH ECX
0047C9C1  |. 56             PUSH ESI
0047C9C2  |. 8BF1           MOV ESI,ECX
0047C9C4  |. 57             PUSH EDI
0047C9C5  |. 8D4C24 08      LEA ECX,DWORD PTR SS:[ESP+8]

*/

/*
ãÌ|C^ðpµÄ¢éÓÍ1Ó¾¯B±ÌECXÍAYÌÆóîñÖÌÆó|C^ªüÁÄ¢éB
EAXÍà¿ëñÆóíÞÔ
0047CA24  |. 0F8D E3010000          JGE Nobunaga.0047CC0D
0047CA2A  |. 8B3485 B8A85300        MOV ESI,DWORD PTR DS:[EAX*4+53A8B8]                         ;  Nobunaga.00523F4C
0047CA31  |. E9 DD010000            JMP Nobunaga.0047CC13

*/



#include <windows.h>
#include <string>
#include <memory>
#include "data_game_struct.h"
#include "output_debug_stream.h"
#include "data_kahou_struct.h"
#include "game_process.h"
#include "mng_Æóñ.h"
#include "usr_custom_mod.h"

using namespace std;


static int ECXOfKahouTypeName = -1;
static int EAXOfKahouTypeName = -1;
static int ESIOfKahouTypeName = -1;

struct TKahouTypeName {
	char name[9]; // Sp4¶ÜÅ
};

//TKahouTypeName listKahouType[Åå::Æóîñ::zñ] = { 0 };
std::unique_ptr<TKahouTypeName[]> listKahouType(new TKahouTypeName[Åå::Æóîñ::zñ]());

void OverrideKahouTypeName(int iKahouID) {
	// C#ÌdllÅã«
	try {
		System::Collections::Generic::Dictionary<System::String^, System::Object^>^ dic = gcnew System::Collections::Generic::Dictionary<System::String^, System::Object^>(5);
		dic->Add("ÆóÔ", iKahouID);
		System::Collections::Generic::Dictionary<System::String^, System::Object^>^ ret = InvokeUserMethod("onÆóíÞ¼v", dic);

		if (ret != nullptr && ret->ContainsKey("íÞ¼")) {
			System::String^ kahou_type_name = (System::String^)(ret["íÞ¼"]);
			if (System::String::IsNullOrEmpty(kahou_type_name)) {
				;
			}
			else {
				string native_typename = to_native_string(kahou_type_name);
				native_typename[8] = '\0'; // 8¶ÜÅ
				strcpy_s(listKahouType[iKahouID].name, native_typename.c_str());
			}
		}

	}
	catch (System::Exception^ ) {
		OutputDebugStream("onÆóíÞ¼vÅÌG[");
	}

}

void OnSSRExeKahouTypeNameExecute() {

	int iKahouID = getKahouIDFromKahouPtr((int*)ECXOfKahouTypeName);
	if (isValidKahouID(iKahouID)) {

		// ÆóÌftHgÌíÞ¼ð¾é
		int iKahouType = nb7Æóîñ[iKahouID].íÞ;
		int iKahouTypeNameLocation = 4 * iKahouType + 0x53A8B8;
		int pKahouName = *((int*)iKahouTypeNameLocation);
		// OutputDebugStream("íÞ¼Í%s\n", pKahouName);

		// »êð200ÂÌobt@[Éi[µÄ¨­
		strcpy_s(listKahouType[iKahouID].name, (char*)pKahouName);

		// ÆóíÞ¼ðæ¾·é
		// OutputDebugStream("Æó:"s + nb7Æóîñ[iKahouID].Æó¼);
		// OutputDebugStream("êÍ%x¾æ", ESIOfKahouTypeName);
		
		// ±±ÅÎÛÌÆóÌíÞ¼ðÏX·é
		int iKahouImageType = nb7Æóîñ[iKahouID].æ;
		if (iKahouImageType == ñ::Æó::æ::ï«) {
			strcpy_s(listKahouType[iKahouID].name, "ï«");
		}
		else if (iKahouImageType == ñ::Æó::æ::) {
			strcpy_s(listKahouType[iKahouID].name, "");
		}
		else if (iKahouImageType == ñ::Æó::æ::wHD) {
			strcpy_s(listKahouType[iKahouID].name, "wHD");
		}
		else if (iKahouImageType == ñ::Æó::æ::) {
			strcpy_s(listKahouType[iKahouID].name, "");
		}
		else if (iKahouImageType == ñ::Æó::æ::Æ) {
			strcpy_s(listKahouType[iKahouID].name, "Æ");
		}
		else if (iKahouImageType == ñ::Æó::æ::ç¹) {
			strcpy_s(listKahouType[iKahouID].name, "ç¹");
		}
		else if (iKahouImageType == ñ::Æó::æ::Ôü) {
			strcpy_s(listKahouType[iKahouID].name, "Ôü");
		}
		else if (iKahouImageType == ñ::Æó::æ::ü) {
			strcpy_s(listKahouType[iKahouID].name, "ü");
		}
		else if (iKahouImageType == ñ::Æó::æ::â) {
			strcpy_s(listKahouType[iKahouID].name, "â");
		}
		else if (iKahouImageType == ñ::Æó::æ::q) {
			strcpy_s(listKahouType[iKahouID].name, "q");
		}
		else if (iKahouImageType == ñ::Æó::æ::) {
			strcpy_s(listKahouType[iKahouID].name, "");
		}
		else if (iKahouImageType == ñ::Æó::æ::myí) {
			strcpy_s(listKahouType[iKahouID].name, "myí");
		}
		else if (iKahouImageType == ñ::Æó::æ::á¾) {
			strcpy_s(listKahouType[iKahouID].name, "á¾");
		}
		else if (iKahouImageType == ñ::Æó::æ::VYï) {
			strcpy_s(listKahouType[iKahouID].name, "VYï");
		}
		else if (iKahouImageType == ñ::Æó::æ::) {
			strcpy_s(listKahouType[iKahouID].name, "");
		}

		// C#ÌdllÅã«
		OverrideKahouTypeName(iKahouID);

		// ofBbVÈç
		if (nb7Æóîñ[iKahouID].Æó¼ == "o ¡¢£¤"s) {
			strcpy_s(listKahouType[iKahouID].name, "");
		}
		else if (nb7Æóîñ[iKahouID].Æó¼ == "MFGHIv"s) {
			strcpy_s(listKahouType[iKahouID].name, "éó");
		}
		else if (nb7Æóîñ[iKahouID].Æó¼ == "¨¥¦©§ª"s) {
			strcpy_s(listKahouType[iKahouID].name, "ï«");
		}

		// ÎÛÌ¼OÖÌ|C^ðãüµÄ¨­B
		ESIOfKahouTypeName = (int)(listKahouType[iKahouID].name);
	}

}

#pragma unmanaged

/*
ãÌ|C^ðpµÄ¢éÓÍ1Ó¾¯B±ÌECXÍAYÌÆóîñÖÌÆó|C^ªüÁÄ¢éB
EAXÍà¿ëñÆóíÞÔ
0047CA24  |. 0F8D E3010000          JGE Nobunaga.0047CC0D
0047CA2A  |. 8B3485 B8A85300        MOV ESI,DWORD PTR DS:[EAX*4+53A8B8]                         ;  Nobunaga.00523F4C
0047CA31  |. E9 DD010000            JMP Nobunaga.0047CC13

*/

int pSSRExeJumpFromToOnSSRExeKahouTypeName = 0x47CA2A; // ÖÍ±ÌAhX©çAOnSSRExeKahouTypeNameÖÆWvµÄ­éB
int pSSRExeReturnLblFromOnSSRExeKahouTypeName = 0x47CA31; // ÖªÅãÜÅ¢­ÆA±ÌÀsexeàÉ¼ÚWv·é

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeKahouTypeName() {
	// X^bNÉ½ßÄ¨­
	__asm {

		MOV ESI, DWORD PTR DS : [EAX * 4 + 0x53A8B8]

		mov ECXOfKahouTypeName, ecx
		mov EAXOfKahouTypeName, eax
		mov ESIOfKahouTypeName, esi
		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeKahouTypeNameExecute();

	// X^bNÉø«o·
	__asm {
		pop edi
		pop esi
		pop ebp
		pop esp
		pop edx
		pop ecx
		pop ebx
		pop eax

		MOV ESI, ESIOfKahouTypeName

		jmp pSSRExeReturnLblFromOnSSRExeKahouTypeName
	}
}
#pragma warning(default: 4733) // [jOÌ}§ðð·é



char cmdOnSSRExeJumpFromKahouTypeName[8] = "\xE9\x90\x90\x90\x90\x90\x90";
// ³Ì½ßª5oCgAÈãÌÖÅ¶Üêé½ßªvToCgÈÌÅc ÅãPÂgíÈ¢


// j[jbN«·¦p
void WriteAsmJumperOnSSRExeKahouTypeName() {

	// Ü¸AhXðÆµÄµ¤
	int iAddress = (int)OnSSRExeKahouTypeName;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeKahouTypeName + 5);
	// TÆ¢¤ÌÍA0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  Ì½ßÉKvÈoCgBv·éÉToCg«·ÆÌj[jbN½ßQÉÚ®·éÌ¾B»µÄ»±©çÌ·ªªWv·éÛÌÚIiÆµÄp³êéB
	memcpy(cmdOnSSRExeJumpFromKahouTypeName + 1, &SubAddress, 4); // +1 ÍE9Ì©ç4oCgª«·¦é©çB

	// \zµ½j[jbN½ßðÀsexeÌÉ«·¦é
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeKahouTypeName), cmdOnSSRExeJumpFromKahouTypeName, 7, NULL); //7oCgÌÝ«Þ
}

#pragma managed
