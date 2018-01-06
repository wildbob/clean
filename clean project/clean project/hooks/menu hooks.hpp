#pragma once
#include "..\sdk\sdk.hpp"

namespace sdk
{
	namespace hooks
	{
		extern HRESULT  __stdcall		hk_reset(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters);	
		extern HRESULT __stdcall		hk_present(IDirect3DDevice9* pDevice, const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const RGNDATA* pDirtyRegion);
	}
}