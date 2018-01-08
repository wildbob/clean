#pragma once
#include "..\sdk\sdk.hpp"

namespace sdk
{
	namespace hooks
	{
		extern HRESULT  __stdcall		hk_reset(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters);	
		extern HRESULT __stdcall		hk_present(IDirect3DDevice9* pDevice, const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const RGNDATA* pDirtyRegion);
		extern LRESULT __stdcall		hk_wndproc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		extern WNDPROC wndproc_o;
		extern HWND m_window;
		extern HRESULT WINAPI			hk_draw(LPDIRECT3DDEVICE9 pDev,
			D3DPRIMITIVETYPE PrimType, INT BaseVertexIndex, UINT MinVertexIndex,
			UINT NumVertices, UINT startIndex, UINT PrimitiveCount);

		extern void* draw_points_ret_addr;

		struct CUSTOMVERTEX {
			FLOAT x, y, z, r, h, w;
		};
	}
}