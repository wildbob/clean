#include "..\core.hpp"
#include "menu hooks.hpp"
#include "..\imgui/imgui_internal.h"
#include "..\imgui\dx9\imgui_dx9.h"
#include "..\sdk\entity.hpp"

#define CUSTOMFVF (D3DFVF_XYZRHW | D3DFVF_TEX1)
extern LRESULT ImGui_ImplDX9_WndProcHandler(HWND, UINT, WPARAM, LPARAM);

namespace sdk
{
	namespace hooks
	{
		WNDPROC wndproc_o;
		HWND m_window;

		void open_menu()
		{

			static bool is_down = false;
			static bool is_clicked = false;

			if (csgo.m_menu()->m_pressedkeys[VK_INSERT])
			{
				is_clicked = false;
				is_down = true;
			}
			else if (!csgo.m_menu()->m_pressedkeys[VK_INSERT] && is_down)
			{
				is_clicked = true;
				is_down = false;
			}
			else
			{
				is_clicked = false;
				is_down = false;
			}

			if (is_clicked)
			{
				csgo.m_settings()->m_menuopen = !csgo.m_settings()->m_menuopen;
				std::string msg = "cl_mouseenable " + std::to_string(!csgo.m_settings()->m_menuopen);
				csgo.m_engine()->client_cmd_unrestricted(msg.c_str());
			}
		}

		LRESULT __stdcall hk_wndproc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

			switch (uMsg) {
			case WM_LBUTTONDOWN:
				csgo.m_menu()->m_pressedkeys[VK_LBUTTON] = true;
				break;
			case WM_LBUTTONUP:
				csgo.m_menu()->m_pressedkeys[VK_LBUTTON] = false;
				break;
			case WM_RBUTTONDOWN:
				csgo.m_menu()->m_pressedkeys[VK_RBUTTON] = true;
				break;
			case WM_RBUTTONUP:
				csgo.m_menu()->m_pressedkeys[VK_RBUTTON] = false;
				break;
			case WM_MBUTTONDOWN:
				csgo.m_menu()->m_pressedkeys[VK_MBUTTON] = true;
				break;
			case WM_MBUTTONUP:
				csgo.m_menu()->m_pressedkeys[VK_MBUTTON] = false;
				break;
			case WM_XBUTTONDOWN:
			{
				UINT button = GET_XBUTTON_WPARAM(wParam);
				if (button == XBUTTON1)
				{
					csgo.m_menu()->m_pressedkeys[VK_XBUTTON1] = true;
				}
				else if (button == XBUTTON2)
				{
					csgo.m_menu()->m_pressedkeys[VK_XBUTTON2] = true;
				}
				break;
			}
			case WM_XBUTTONUP:
			{
				UINT button = GET_XBUTTON_WPARAM(wParam);
				if (button == XBUTTON1)
				{
					csgo.m_menu()->m_pressedkeys[VK_XBUTTON1] = false;
				}
				else if (button == XBUTTON2)
				{
					csgo.m_menu()->m_pressedkeys[VK_XBUTTON2] = false;
				}
				break;
			}
			case WM_KEYDOWN:
				csgo.m_menu()->m_pressedkeys[wParam] = true;
				break;
			case WM_KEYUP:
				csgo.m_menu()->m_pressedkeys[wParam] = false;
				break;
			default: break;
			}

			open_menu();

			if ( csgo.m_menu()->initialized && csgo.m_settings()->m_menuopen && ImGui_ImplDX9_WndProcHandler( hWnd, uMsg, wParam, lParam ) )
				return true;

			return CallWindowProc(wndproc_o, hWnd, uMsg, wParam, lParam);
		}

	

	


		LPDIRECT3DTEXTURE9 pTexturer;
		LPDIRECT3DTEXTURE9 pTexturey;
		IDirect3DBaseTexture9* deftexture;
		IDirect3DBaseTexture9* deftexture2;

		const BYTE bRed[60] = { 0x42, 0x4D, 0x3C, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00,
			0x00, 0x28, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
			0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x20, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x0B,
			0x00, 0x00, 0x12, 0x0B, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00,
			0x00, 0x01 };
		const BYTE bYellow[60] = { 0x42, 0x4D, 0x3C, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00,
			0x00, 0x28, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
			0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x20, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x0B,
			0x00, 0x00, 0x12, 0x0B, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00,
			0x00, 0x01 };

		IDirect3DStateBlock9* ppSB = nullptr;
		DWORD oldz;

		IDirect3DPixelShader9* pixelshader = NULL;
		LPDIRECT3DTEXTURE9 sil_texture = NULL;
		IDirect3DSurface9* ppSurfaceLevel = NULL;
		IDirect3DPixelShader9* sil_ps = nullptr;

		IDirect3DPixelShader9* oldpixelshader;
		IDirect3DSurface9* oldrendersurface;
		IDirect3DSurface9* oldrendersurface2;

		IDirect3DSurface9* backbuffer = NULL;
		D3DSURFACE_DESC desc;

		IDirect3DVertexBuffer9* v_buffer = NULL; // the pointer to the vertex buffer

		void draw_texture(LPDIRECT3DDEVICE9 pDevice)
		{

			pDevice->GetRenderTarget(0, &backbuffer);
			backbuffer->GetDesc(&desc);
			backbuffer->Release();

			pDevice->CreateStateBlock(D3DSBT_ALL, &ppSB);

			CUSTOMVERTEX vertices[] = {
				{
					0, 0.0, 0, 1.0, 0.0, 0.0,
				},
				{
					desc.Width, 0, 0.0, 1.0, 1.0, 0.0,
				},
				{
					0, desc.Height, 0, 1.0, 0.0, 1.0,
				},
				{
					desc.Width, desc.Height, 0, 1.0, 1.0, 1.0,
				},

			};

			VOID* pVoid; // a void pointer

			v_buffer->Lock(0, 0, (void**)&pVoid, 0);
			memcpy(pVoid, vertices, sizeof(vertices));
			v_buffer->Unlock();

			pDevice->SetPixelShader(NULL);
			pDevice->SetTexture(0, sil_texture);

			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

			pDevice->SetStreamSource(0, v_buffer, 0, sizeof(CUSTOMVERTEX));
			pDevice->SetFVF(CUSTOMFVF);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

			ppSB->Apply();
			ppSB->Release();
		}

		HRESULT generate(LPDIRECT3DDEVICE9 pDevice)
		{

			D3DCAPS9 caps;

			int major_vs, minor_vs;
			int major_ps, minor_ps;
			pDevice->GetDeviceCaps(&caps);

			DWORD VERSPX1 = D3DSHADER_VERSION_MAJOR(caps.PixelShaderVersion);
			DWORD VERSPX2 = D3DSHADER_VERSION_MINOR(caps.PixelShaderVersion);

			char szVersion[32];
			sprintf(szVersion, "ps_%d_%d", VERSPX1, VERSPX2);

			char szShader[256];
			sprintf(szShader, "%s \n mov oC0, c0", szVersion);

			ID3DXBuffer* pShaderBuf = NULL;

			D3DXAssembleShader(szShader, sizeof(szShader), NULL, NULL, 0, &pShaderBuf, NULL);
			if (pShaderBuf)
				pDevice->CreatePixelShader((const DWORD*)pShaderBuf->GetBufferPointer(), &pixelshader);

			pDevice->GetRenderTarget(0, &backbuffer);
			backbuffer->GetDesc(&desc);
			backbuffer->Release();

			pDevice->CreateTexture(desc.Width, desc.Height, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &sil_texture, NULL);
			sil_texture->GetSurfaceLevel(0, &ppSurfaceLevel);

			pDevice->CreateVertexBuffer(4 * sizeof(CUSTOMVERTEX),
				0,
				CUSTOMFVF,
				D3DPOOL_MANAGED,
				&v_buffer,
				NULL);

			return S_OK;
		}

		void draw_rect(LPDIRECT3DDEVICE9 pDevice, int x1, int y1, int x2, int y2, BYTE r, BYTE g, BYTE b)
		{

			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

			D3DRECT BarRect;
			D3DCOLOR Cor;

			BarRect.x1 = x1;
			BarRect.x2 = x2;
			BarRect.y1 = y1;
			BarRect.y2 = y2;

			Cor = 0x00000000;

			pDevice->Clear(1, &BarRect, D3DCLEAR_TARGET || D3DCLEAR_ZBUFFER, Cor, 0, 0);
		}

		void* draw_points_ret_addr;
		DWORD old_zenable;
		void* traverse_stack(void** ebp)
		{
			if (ebp == nullptr)
				return nullptr;

				auto** next = *(void***)(ebp);
				if (ebp[1] == draw_points_ret_addr && next)
					return next[4];


				return traverse_stack(next);
			
		}

		void* get_ent()
		{
			auto data = 0;
			__asm {
				mov data, ebp
			}
			return traverse_stack((void**)(data));
		}
		IDirect3DStateBlock9* pStateBlock = NULL;

		HRESULT WINAPI			hk_draw(LPDIRECT3DDEVICE9 pDev,
			D3DPRIMITIVETYPE PrimType, INT BaseVertexIndex, UINT MinVertexIndex,
			UINT NumVertices, UINT startIndex, UINT PrimitiveCount)
		{
			static auto draw_o = csgo.m_hooks()->d3d_hook.get_original< decltype(&hk_draw) >( 82 );
			draw_o(pDev, PrimType, BaseVertexIndex,
				MinVertexIndex, NumVertices, startIndex,
				PrimitiveCount);

			if (csgo.m_engine()->is_in_game())
			{
				const auto* ent = get_ent();
				if (ent != nullptr && csgo.m_localplayer() && *(int*)((uintptr_t)(ent))) {
					int team = *(int*)((uintptr_t)(ent)+0xF0);
					int hpp = *(int*)((uintptr_t)(ent)+0xFC);

					if (csgo.m_localplayer()->get_team() != team && team && (team == 3 || team == 2) && hpp) {


						//textured
						float def[4] = { 1.f,1.f,1.f,1.f };
						float value3[4] = { 1.f, 0.f, 0.f, 1.f };
						float value4[4] = { 0.f, 1.f, 0.f, 1.f };

						pDev->GetRenderTarget(0, &oldrendersurface);
						pDev->GetPixelShader(&oldpixelshader);
						pDev->GetRenderState(D3DRS_ZENABLE, &old_zenable);
						/*************************************************************/
						pDev->SetRenderTarget(0, ppSurfaceLevel);
						pDev->GetTexture(0, &deftexture);

						/*******************************************************/

						pDev->SetRenderState(D3DRS_ZENABLE, false);

			//			pDev->SetTexture(0, pTexturey);
						pDev->SetPixelShaderConstantF(1, value3, 1);

						draw_o(pDev, PrimType, BaseVertexIndex,
							MinVertexIndex, NumVertices, startIndex,
							PrimitiveCount);


						pDev->SetRenderState(D3DRS_ZENABLE, old_zenable);

						pDev->SetPixelShaderConstantF(1, value4, 1);

						draw_o(pDev, PrimType, BaseVertexIndex,
							MinVertexIndex, NumVertices, startIndex,
							PrimitiveCount);

						/****************************************/
						pDev->SetPixelShaderConstantF(0, def, 1);
						pDev->SetPixelShaderConstantF(1, def, 1);
						pDev->SetRenderTarget(0, oldrendersurface);
						pDev->SetRenderState(D3DRS_ZENABLE, old_zenable);
						pDev->SetPixelShader(oldpixelshader);

						pDev->SetTexture(0, deftexture);
						if (deftexture)
							deftexture->Release();
						oldrendersurface->Release();
						if (oldpixelshader)
							oldpixelshader->Release();
					}
				}
			}
			
			return true;
		}
		HRESULT __stdcall hk_present(IDirect3DDevice9* pDevice, const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const RGNDATA* pDirtyRegion)
		{
			IDirect3DStateBlock9* state_block = nullptr;
			pDevice->CreateStateBlock(D3DSBT_ALL, &state_block);

			[pDevice]()
			{			
				if (!sdk::renderer::c_renderer::render_initalized)
				{
					csgo.m_menu()->initialize_gui(pDevice);
					generate(pDevice);
					D3DXCreateTextureFromFileInMemory(pDevice, (LPCVOID)&bRed, sizeof(bRed), &pTexturer);
					csgo.m_render()->init_device_objects(pDevice);
					sdk::renderer::c_renderer::render_initalized = true;
				}
				else
				{
					csgo.m_render()->setup_render_states();

					csgo.m_render()->string(100.f, 20.f, CD3DFONT_CENTERED_X, Color(255, 255, 255), csgo.m_render()->m_fonts()->pFontTahoma10.get(), "yea your mad");

					csgo.m_features()->m_visuals()->initialize();

					csgo.m_menu()->draw();

					if (sil_texture && ppSurfaceLevel)
						draw_texture(pDevice);

					if (pDevice != NULL) {
						pDevice->GetRenderTarget(0, &oldrendersurface);
						pDevice->SetRenderTarget(0, ppSurfaceLevel);
						draw_rect(pDevice, 0, 0, desc.Width, desc.Height, 0, 0, 0);
						pDevice->SetRenderTarget(0, oldrendersurface);
						oldrendersurface->Release();
					}

				}
			}();

			state_block->Apply();
			state_block->Release();

			static auto present_o = csgo.m_hooks()->d3d_hook.get_original< decltype(&hk_present) >(17);
			return present_o(pDevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
		}

		HRESULT __stdcall hk_reset(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters)
		{
			static auto reset_o = csgo.m_hooks()->d3d_hook.get_original< decltype(&hk_reset) >(16);

			if (!sdk::menu::c_menu::initialized)
				return reset_o(pDevice, pPresentationParameters);

			if (sdk::renderer::c_renderer::render_initalized)
			{
				v_buffer->Release();
				sil_texture->Release();
				ppSurfaceLevel->Release();
				csgo.m_render()->invalidate_device_objects();
				ImGui_ImplDX9_InvalidateDeviceObjects();
				HRESULT hr = reset_o(pDevice, pPresentationParameters);
				if (SUCCEEDED(hr))
				{
					generate(pDevice);
					ImGui_ImplDX9_CreateDeviceObjects();
				}
				return hr;
			}

			return reset_o(pDevice, pPresentationParameters);

		}
	}
}