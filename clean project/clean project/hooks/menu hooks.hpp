#pragma once
#include "..\sdk\sdk.hpp"

namespace sdk
{
	namespace hooks
	{
		HRESULT __stdcall		hk_endscene(IDirect3DDevice9* thisptr);
		HRESULT  __stdcall		hk_reset(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters);	
	}
}