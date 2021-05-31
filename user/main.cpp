// Generated C++ file by Il2CppInspector - http://www.djkaty.com - https://github.com/djkaty
// Custom injected code entry point

#include "pch-il2cpp.h"

#define WIN32_LEAN_AND_MEAN
#include <codecvt>
#include <Windows.h>
#include <iostream>
#include <detours.h>
#include <locale>

#include "il2cpp-appdata.h"
#include "helpers.h"

using namespace app;

extern const LPCWSTR LOG_FILE = L"il2cpp-log.txt";

const std::string NotMelonLoader = "totally_not_melon_loader";
String* not_melon_loader;

void DoNothingMethod(MethodInfo* method)
{
	il2cppi_log_write("CALL: DoNothingMethod\n");
}

bool File_Exists_Hook(String* str, MethodInfo* method)
{
	il2cppi_log_write("CALL: File_Exists_Hook\n");
	std::wstring_convert<std::codecvt_utf8<wchar_t>> wideToNarrow;
	std::string skey = wideToNarrow.to_bytes(std::wstring((const wchar_t*)
		(&((Il2CppString*)str)->chars), ((Il2CppString*)str)->length));

	if(skey.find("dll") != std::string::npos || skey.find(NotMelonLoader) != std::string::npos)
	{
		return false;
	}

	il2cppi_log_write("FileHooked\n");

	return File_Exists(str, method);
}

bool Directory_Exists_Hook(String* str, MethodInfo* method)
{
	il2cppi_log_write("CALL: Directory_Exists_Hook");
	il2cppi_log_write("\t\tstr:" + il2cppi_to_string(str));

	std::wstring_convert<std::codecvt_utf8<wchar_t>> wideToNarrow;
	std::string skey = wideToNarrow.to_bytes(std::wstring((const wchar_t*)
		(&((Il2CppString*)str)->chars), ((Il2CppString*)str)->length));

	if(skey.find("MelonLoader") != std::string::npos || skey.find(NotMelonLoader) != std::string::npos)
	{
		il2cppi_log_write("\t\tRETURN: (fixed) false\n");
		return false;
	}

	bool b =  Directory_Exists(str, method);
	il2cppi_log_write(b ? "\t\tRETURN: true\n" : "\t\tRETURN: false\n");
	return b;
}

bool String_Contains_Hook(String* str, String* str2, MethodInfo* method)
{
	il2cppi_log_write("CALL: String_Contains_Hook");
	il2cppi_log_write("\t\tstr:" + il2cppi_to_string(str));
	il2cppi_log_write("\t\tstr2:" + il2cppi_to_string(str2));

	std::wstring_convert<std::codecvt_utf8<wchar_t>> wideToNarrow;
	std::string skey = wideToNarrow.to_bytes(std::wstring((const wchar_t*)
		(&((Il2CppString*)str)->chars), ((Il2CppString*)str)->length));

	// List of strings the game seems to search for:
	// ============================================
	// OnlineFix
	// PhotonBridge
	// Cheat
	// Unknown
	// Melon
	// version
	// winhttp
	// winmm
	// PhasByPass
	// ByPass

	if(
		skey.find("MelonLoader") != std::string::npos
		|| skey.find(NotMelonLoader) != std::string::npos
		|| skey.find("PhasBypass") != std::string::npos
		|| skey.find("version") != std::string::npos
	) {
		il2cppi_log_write("\t\tRETURN: (fixed) false\n");
		return false;
	}

	bool b = String_Contains(str, str2, method);
	il2cppi_log_write(b ? "\t\tRETURN: true\n" : "\t\tRETURN: false\n");
	return b;
}

void* TryGetModuleHandleHook(String* str, MethodInfo* method)
{
	il2cppi_log_write("CALL: TryGetModuleHandleHook\n");
	il2cppi_log_write("\t\tstr:" + il2cppi_to_string(str));

	std::wstring_convert<std::codecvt_utf8<wchar_t>> wideToNarrow;
	std::string skey = wideToNarrow.to_bytes(std::wstring((const wchar_t*)
		(&((Il2CppString*)str)->chars), ((Il2CppString*)str)->length));

	il2cppi_log_write(skey);

	return nullptr;
}

String* GetMelonLoaderSearchStrings(Byte__Array* theArray, bool b, MethodInfo* method)
{
	il2cppi_log_write("CALL: GetMelonLoaderSearchStrings\n");
	return not_melon_loader;
}

void CheckProcessesForModsFunc(MethodInfo* method)
{
	il2cppi_log_write("CALL: CheckProcessesForModsFunc\n");
}

void CheckForModsFunc(MethodInfo* method)
{
	il2cppi_log_write("CALL: CheckForModsFunc\n");
}



void Run()
{
	NewConsole();

	il2cppi_log_write("Starting Hooks\n");
	not_melon_loader = (String*)il2cpp_string_new(NotMelonLoader.c_str());
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());


	DetourAttach(&(PVOID&)__104____________, DoNothingMethod);
	DetourAttach(&(PVOID&)__104_____________1, DoNothingMethod);
	DetourAttach(&(PVOID&)__104_____________2, DoNothingMethod);
	DetourAttach(&(PVOID&)__104_____________4, DoNothingMethod);
	DetourAttach(&(PVOID&)__104_____________6, DoNothingMethod);
	DetourAttach(&(PVOID&)__104_____________7, DoNothingMethod);
	DetourAttach(&(PVOID&)__104_____________8, DoNothingMethod);
	DetourAttach(&(PVOID&)__104_____________9, DoNothingMethod);


	DetourAttach(&(PVOID&)__104_____________10, TryGetModuleHandleHook);
	DetourAttach(&(PVOID&)__105____________, CheckProcessesForModsFunc);
	DetourAttach(&(PVOID&)__105_____________1, CheckForModsFunc);

	// override mod checking function
	//DetourAttach(&(PVOID&)CheckForGetModuleHandle, TryGetModuleHandleHook);
	//DetourAttach(&(PVOID&)CheckProcessesForMods, CheckProcessesForModsFunc);
	//DetourAttach(&(PVOID&)CheckForMods, CheckForModsFunc);

	// override file/directory/string checking
	DetourAttach(&(PVOID&)File_Exists, File_Exists_Hook);
	DetourAttach(&(PVOID&)Directory_Exists, Directory_Exists_Hook);
	DetourAttach(&(PVOID&)String_Contains, String_Contains_Hook);
	LONG lError = DetourTransactionCommit();
	if(lError != NO_ERROR)
	{
		il2cppi_log_write("Hook Failed");
	}

	il2cppi_log_write("Bypass hooked\n");
}
