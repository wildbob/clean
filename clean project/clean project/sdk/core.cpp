#include <Windows.h>
#include "..\core.hpp"

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:

	//	_beginthread(cheat_init, 0, NULL);

		break;

	case DLL_PROCESS_DETACH:

		break;
	}

	return TRUE;
}