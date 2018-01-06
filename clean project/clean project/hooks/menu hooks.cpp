#include "..\core.hpp"
#include "menu hooks.hpp"

namespace sdk
{
	namespace hooks
	{
		/*HRESULT __stdcall hk_endscene(IDirect3DDevice9* thisptr)
		{
			static auto end_scene_o = csgo.m_hooks( )->d3d_hook.get_original< decltype(&hk_endscene) >( 42 );
			//so we dont have to do that net graph shit
			thisptr->SetRenderState(D3DRS_COLORWRITEENABLE, 0xFFFFFFFF);

			if (!sdk::renderer::c_renderer::render_initalized)
			{
				csgo.m_render( )->init_device_objects( thisptr );
				sdk::renderer::c_renderer::render_initalized = true;
			}
			else
			{
				csgo.m_render( )->setup_render_states( );

				csgo.m_render( )->string(100.f, 20.f, CD3DFONT_CENTERED_X, Color(255, 255, 255), csgo.m_render()->m_fonts()->pFontTahoma10.get(), "yea your mad");
			}

			return end_scene_o(thisptr);
		}*/

		HRESULT __stdcall hk_present(IDirect3DDevice9* pDevice, const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const RGNDATA* pDirtyRegion)
		{
			IDirect3DStateBlock9* state_block = nullptr;
			pDevice->CreateStateBlock(D3DSBT_ALL, &state_block);

			[pDevice]()
			{
				if (!sdk::renderer::c_renderer::render_initalized)
				{
					csgo.m_render()->init_device_objects(pDevice);
					sdk::renderer::c_renderer::render_initalized = true;
				}
				else
				{
					csgo.m_render()->setup_render_states();

					csgo.m_render()->string(100.f, 20.f, CD3DFONT_CENTERED_X, Color(255, 255, 255), csgo.m_render()->m_fonts()->pFontTahoma10.get(), "yea your mad");				

					csgo.m_features()->m_visuals()->initialize();
				}
			}();

			state_block->Apply();
			state_block->Release();

			static auto present_o = csgo.m_hooks()->d3d_hook.get_original< decltype(&hk_present) >(17);
			return present_o(pDevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
		}

		HRESULT __stdcall hk_reset(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters)
		{
			static auto reset_o = csgo.m_hooks( )->d3d_hook.get_original< decltype(&hk_reset) >( 16 );

			if (sdk::renderer::c_renderer::render_initalized)
			{
				csgo.m_render( )->invalidate_device_objects();
				HRESULT hr = reset_o(pDevice, pPresentationParameters);
				csgo.m_render( )->restore_device_objects(pDevice);
				return hr;
			}

			return reset_o(pDevice, pPresentationParameters);

		}
	}
}