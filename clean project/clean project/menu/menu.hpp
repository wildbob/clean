#pragma once
#include "..\sdk\sdk.hpp"
#include "..\imgui\imgui.h"

namespace sdk
{
	namespace menu
	{
		class c_menu
		{
		private:
		public:
			void initialize_gui(IDirect3DDevice9* pDevice);
			void draw();
			static bool initialized;
			static bool m_pressedkeys[256];
		};

		class c_settings
		{
		public:
			bool m_menuopen = false;
		};
	}
}
