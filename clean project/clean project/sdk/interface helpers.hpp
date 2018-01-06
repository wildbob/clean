#pragma once
#include <Windows.h>

namespace sdk
{
	namespace helpers
	{
		template< typename func > func get_virtual_function(PVOID Base, DWORD Index)
		{
			PDWORD* VTablePointer = (PDWORD*)Base;
			PDWORD VTableFunctionBase = *VTablePointer;
			DWORD dwAddress = VTableFunctionBase[Index];
			return (func)(dwAddress);
		}
	}
}