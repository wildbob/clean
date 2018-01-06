#include "render.hpp"



namespace sdk
{
	namespace renderer
	{
		bool c_renderer::render_initalized = false;

		struct Vertex
		{
			float x, y, z, rhw;
			DWORD color;
		};


		c_font* c_renderer::m_fonts()
		{
			if (!fonts)
				fonts = new c_font();

			return fonts;
		}

		c_renderer::c_renderer()
		{
			this->pDevice = nullptr;
			m_fonts()->pFontTahoma10 = nullptr;
			fonts = nullptr;
		}


		void c_renderer::init_device_objects(LPDIRECT3DDEVICE9 pDevice)
		{
			// Save the device internally
			this->pDevice = pDevice;

			// Get viewport for our center coords
			this->pDevice->GetViewport(&pViewPort);

			// Create new fonts
			m_fonts()->pFontTahoma8 = std::make_unique<CD3DFont>("Tahoma", 8, FW_NORMAL);
			m_fonts()->pFontTahoma10 = std::make_unique<CD3DFont>("Tahoma", 10, FW_MEDIUM);

			// Init font device objects
			m_fonts()->init_device_objects(pDevice);
		}


		void c_renderer::invalidate_device_objects()
		{
			// Remove a pointer to game device
			this->pDevice = nullptr;

			m_fonts()->invalidate_device_objects();
		}


		void c_renderer::restore_device_objects(LPDIRECT3DDEVICE9 pDevice)
		{
			this->pDevice = pDevice;
			this->pDevice->GetViewport(&pViewPort);

			m_fonts()->init_device_objects(pDevice);
		}


		void c_renderer::line(vec2_t vecPos1, vec2_t vecPos2, Color color)
		{
			this->line(vecPos1.x, vecPos1.y, vecPos2.x, vecPos2.y, color);
		}


		void c_renderer::line(float posx1, float posy1, float posx2, float posy2, Color color)
		{
			D3DCOLOR dwColor = COL2DWORD(color);
			Vertex vert[2] =
			{
				{ posx1, posy1, 0.0f, 1.0f, dwColor },
				{ posx2, posy2, 0.0f, 1.0f, dwColor }
			};

			this->pDevice->SetTexture(0, nullptr);
			this->pDevice->DrawPrimitiveUP(D3DPT_LINELIST, 1, &vert, sizeof(Vertex));
		}


		void c_renderer::rect(vec2_t vecPos1, vec2_t vecPos2, Color color)
		{
			this->rect(vecPos1.x, vecPos1.y, vecPos1.x + vecPos2.x, vecPos1.y + vecPos2.y, color);
		}


		void c_renderer::rect(float posx1, float posy1, float posx2, float posy2, Color color)
		{
			D3DCOLOR dwColor = COL2DWORD(color);
			Vertex vert[5] =
			{   // Draw lines between declared points, needs primitive count as number of lines (4 here)
				{ posx1, posy1, 0.0f, 1.0f, dwColor },  // Top left corner
				{ posx2, posy1, 0.0f, 1.0f, dwColor },  // Top right corner
				{ posx2, posy2, 0.0f, 1.0f, dwColor },  // Bottom right corner
				{ posx1, posy2, 0.0f, 1.0f, dwColor },  // Bottom left corner
				{ posx1, posy1, 0.0f, 1.0f, dwColor }   // Back to top left to finish drawing
			};

			this->pDevice->SetTexture(0, nullptr);
			this->pDevice->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, FALSE);  /* Disabled, cause corners of the rectangle get antialiased */
			this->pDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, 4, &vert, sizeof(Vertex));
			this->pDevice->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, TRUE);   /* And enable again for the rest of the drawing */
		}

		void c_renderer::rect_filled(vec2_t vecPos1, vec2_t vecPos2, Color color)
		{
			this->rect_filled(vecPos1.x, vecPos1.y, vecPos2.x, vecPos2.y, color);
		}

		void c_renderer::rect_filled(float posx1, float posy1, float posx2, float posy2, Color color)
		{
			D3DCOLOR dwColor = COL2DWORD(color);
			Vertex vert[4] =
			{
				{ posx1, posy1, 0.0f, 1.0f, dwColor },
				{ posx2, posy1, 0.0f, 1.0f, dwColor },
				{ posx1, posy2, 0.0f, 1.0f, dwColor },
				{ posx2, posy2, 0.0f, 1.0f, dwColor }
			};

			this->pDevice->SetTexture(0, nullptr);
			this->pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &vert, sizeof(Vertex));
		}

		void c_renderer::triangle(vec2_t pos1, vec2_t pos2, vec2_t pos3, Color color)
		{
			D3DCOLOR dwColor = COL2DWORD(color);
			Vertex vert[4] =
			{
				{ pos1.x, pos1.y, 0.0f, 1.0f, dwColor },
				{ pos2.x, pos2.y, 0.0f, 1.0f, dwColor },
				{ pos3.x, pos3.y, 0.0f, 1.0f, dwColor },
				{ pos1.x, pos1.y, 0.0f, 1.0f, dwColor }
			};

			this->pDevice->SetTexture(0, nullptr);
			this->pDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, 3, &vert, sizeof(Vertex));
		}


		void c_renderer::triangle_filled(vec2_t pos1, vec2_t pos2, vec2_t pos3, Color color)
		{
			D3DCOLOR dwColor = COL2DWORD(color);
			Vertex vert[3] =
			{
				{ pos1.x, pos1.y, 0.0f, 1.0f, dwColor },
				{ pos2.x, pos2.y, 0.0f, 1.0f, dwColor },
				{ pos3.x, pos3.y, 0.0f, 1.0f, dwColor }
			};

			this->pDevice->SetTexture(0, nullptr);
			this->pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 1, &vert, sizeof(Vertex));
		}


		void c_renderer::rect_filled_gradient(vec2_t vecPos1, vec2_t vecPos2, Color col1, Color col2, GradientType vertical)
		{
			D3DCOLOR dwColor = COL2DWORD(col1);
			D3DCOLOR dwColor2 = COL2DWORD(col2);
			D3DCOLOR dwcol1, dwcol2, dwcol3, dwcol4;

			switch (vertical)
			{
			case GradientType::GRADIENT_VERTICAL:
				dwcol1 = dwColor;
				dwcol2 = dwColor;
				dwcol3 = dwColor2;
				dwcol4 = dwColor2;
				break;
			case GradientType::GRADIENT_HORIZONTAL:
				dwcol1 = dwColor;
				dwcol2 = dwColor2;
				dwcol3 = dwColor;
				dwcol4 = dwColor2;
				break;
			default:
				dwcol1 = D3DCOLOR_RGBA(255, 255, 255, 255);
				dwcol4 = dwcol3 = dwcol2 = dwcol1;
			}

			Vertex vert[4] =
			{
				{ vecPos1.x, vecPos1.y, 0.0f, 1.0f, dwcol1 },
				{ vecPos2.x, vecPos1.y, 0.0f, 1.0f, dwcol2 },
				{ vecPos1.x, vecPos2.y, 0.0f, 1.0f, dwcol3 },
				{ vecPos2.x, vecPos2.y, 0.0f, 1.0f, dwcol4 }
			};

			this->pDevice->SetTexture(0, nullptr);
			this->pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &vert, sizeof(Vertex));
		}


		void c_renderer::string(float posx, float posy, DWORD dwFlags, Color color, CD3DFont* pFont, const char* szText, ...)
		{
			D3DCOLOR dwColor = COL2DWORD(color);
			posx = std::roundf(posx); posy = std::roundf(posy);
			pFont->DrawString(posx, posy, dwColor, szText, dwFlags);    // To make life easier
		}


		/*
		*   SetupRenderStates - Sets RenderStates for our custom StateBlock
		*   It's required to draw everything independent on game settings.
		*/
		void c_renderer::setup_render_states()
		{
			this->pDevice->SetVertexShader(nullptr);
			this->pDevice->SetPixelShader(nullptr);
			this->pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
			this->pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
			this->pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);
			this->pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
			this->pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

			this->pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
			this->pDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, TRUE);
			this->pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
			this->pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);

			this->pDevice->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, TRUE);
			this->pDevice->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, TRUE);

			this->pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
			this->pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
			this->pDevice->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, TRUE);
			this->pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			this->pDevice->SetRenderState(D3DRS_SRCBLENDALPHA, D3DBLEND_INVDESTALPHA);
			this->pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			this->pDevice->SetRenderState(D3DRS_DESTBLENDALPHA, D3DBLEND_ONE);

			this->pDevice->SetRenderState(D3DRS_SRGBWRITEENABLE, FALSE);
			this->pDevice->SetRenderState(D3DRS_COLORWRITEENABLE,
				D3DCOLORWRITEENABLE_RED | D3DCOLORWRITEENABLE_GREEN |
				D3DCOLORWRITEENABLE_BLUE | D3DCOLORWRITEENABLE_ALPHA);
		}


		vec2_t c_renderer::get_screen_center()
		{
			return vec2_t((static_cast<float>(this->pViewPort.Width)*0.5f), (static_cast<float>(this->pViewPort.Height)*0.5f));
		}
	}
}
