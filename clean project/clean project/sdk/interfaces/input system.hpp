#pragma once
#include "..\interface helpers.hpp"
#include "..\client class.hpp"
#include "..\enums.hpp"

namespace sdk
{

	namespace interfaces
	{
		class c_inputsystem
		{
		public:
			void enable_input(bool bEnable)
			{
				typedef void(__thiscall* OriginalFn)(void*, bool);
				return sdk::helpers::get_virtual_function<OriginalFn>(this, 11)(this, bEnable);
			}

			void reset_input_state()
			{
				typedef void(__thiscall* OriginalFn)(void*);
				return sdk::helpers::get_virtual_function<OriginalFn>(this, 39)(this);
			}

			bool is_button_down(ButtonCode_t code)
			{
				typedef bool(__thiscall* OriginalFn)(void*, ButtonCode_t);
				return sdk::helpers::get_virtual_function<OriginalFn>(this, 15)(this, code);
			}

			void get_cursor_position(int* m_pX, int* m_pY)
			{
				typedef void(__thiscall* OriginalFn)(void*, int*, int*);
				return sdk::helpers::get_virtual_function<OriginalFn>(this, 56)(this, m_pX, m_pY);
			}

			ButtonCode_t virtual_key_to_button_code(int nVirtualKey)
			{
				typedef ButtonCode_t(__thiscall* OriginalFn)(void*, int);
				return sdk::helpers::get_virtual_function<OriginalFn>(this, 44)(this, nVirtualKey);
			}
			int button_code_to_virtual_key(ButtonCode_t code)
			{
				typedef int(__thiscall* OriginalFn)(void*, ButtonCode_t);
				return sdk::helpers::get_virtual_function<OriginalFn>(this, 45)(this, code);
			}
		};
	}
}