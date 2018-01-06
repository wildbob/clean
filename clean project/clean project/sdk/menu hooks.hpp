#pragma once
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

namespace sdk
{
	namespace hooks
	{
		HRESULT __stdcall hk_endscene(IDirect3DDevice9* thisptr);

		class c_hooks
		{
		private:

		public:
			void intialize();
		};
	}
}