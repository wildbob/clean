#pragma once
#include "..\interface helpers.hpp"
#include "..\client class.hpp"

namespace sdk
{
	namespace interfaces
	{
		class c_client
		{
		public:
			c_clientclass* get_class(void)
			{
				typedef c_clientclass*(__thiscall* func)(void*);
				return sdk::helpers::get_virtual_function< func >(this, 8)(this);
			}
		};
	}
}