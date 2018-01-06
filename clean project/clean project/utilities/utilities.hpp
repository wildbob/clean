#pragma once
#include "..\sdk\sdk.hpp"
#include <Psapi.h>
#include <random>

namespace sdk
{
	namespace utilities
	{
		class c_utils
		{
		public:
			inline HMODULE get_handle_safe(std::string handle)
			{
				while (!GetModuleHandleA(handle.c_str())) Sleep(50);

				return GetModuleHandleA(handle.c_str());
			}

			inline float random_number_range(float min, float max)
			{
				std::random_device device;
				std::mt19937 engine(device());
				std::uniform_real_distribution<> distribution(min, max);
				return static_cast<float>(distribution(engine));
			}

			inline bool compare(const BYTE* Data, const BYTE* Mask, const char* szMask)
			{
				for (; *szMask; ++szMask, ++Mask, ++Data)
				{
					if (*szMask == 'x' && *Mask != *Data)
					{
						return false;
					}
				}
				return (*szMask) == 0;
			}
			inline DWORD wait_on_module_handle(std::string moduleName)
			{
				DWORD ModuleHandle = NULL;
				while (!ModuleHandle)
				{
					ModuleHandle = (DWORD)GetModuleHandle(moduleName.c_str());
					if (!ModuleHandle)
						Sleep(50);
				}
				return ModuleHandle;
			}
			inline uint64_t find_pattern_ida(const char* szModule, const char* szSignature)
			{
				//CREDITS: learn_more
#define INRANGE(x,a,b)  (x >= a && x <= b) 
#define getBits( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define getByte( x )    (getBits(x[0]) << 4 | getBits(x[1]))

				MODULEINFO modInfo;
				GetModuleInformation(GetCurrentProcess(), GetModuleHandleA(szModule), &modInfo, sizeof(MODULEINFO));
				DWORD startAddress = (DWORD)modInfo.lpBaseOfDll;
				DWORD endAddress = startAddress + modInfo.SizeOfImage;
				const char* pat = szSignature;
				DWORD firstMatch = 0;
				for (DWORD pCur = startAddress; pCur < endAddress; pCur++) {
					if (!*pat) return firstMatch;
					if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == getByte(pat)) {
						if (!firstMatch) firstMatch = pCur;
						if (!pat[2]) return firstMatch;
						if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?') pat += 3;
						else pat += 2;    //one ?
					}
					else {
						pat = szSignature;
						firstMatch = 0;
					}
				}
				return NULL;
			}

			inline DWORD find_pattern_code(std::string moduleName, BYTE* Mask, char* szMask)
			{
				DWORD Address = wait_on_module_handle(moduleName.c_str());
				MODULEINFO ModInfo; GetModuleInformation(GetCurrentProcess(), (HMODULE)Address, &ModInfo, sizeof(MODULEINFO));
				DWORD Length = ModInfo.SizeOfImage;
				for (DWORD c = 0; c < Length; c += 1)
				{
					if (compare((BYTE*)(Address + c), Mask, szMask))
					{
						return (DWORD)(Address + c);
					}
				}
				return 0;
			}
		};

	}
}
