#pragma once
#include "..\sdk\sdk.hpp"
#include "..\sdk\angles.hpp"
#include "..\sdk\color.hpp"
#include "D3DFont.h"
#include <memory>

#define GET_D3DCOLOR_ALPHA(x) (( x >> 24) & 255)
#define COL2DWORD(x) (D3DCOLOR_ARGB(x.a(), x.r(), x.g(), x.b()))

enum GradientType;

namespace sdk
{
	namespace renderer
	{
		struct c_font
		{
		public:
			void delete_device_objects()
			{

				HRESULT hr;
				hr = pFontTahoma8->DeleteDeviceObjects();
				if (FAILED(hr)) {}
				hr = pFontTahoma10->DeleteDeviceObjects();
				if (FAILED(hr)) {}
			};
			void invalidate_device_objects()
			{
				HRESULT hr;
				hr = pFontTahoma8->InvalidateDeviceObjects();
				if (FAILED(hr)) {}
				hr = pFontTahoma10->InvalidateDeviceObjects();
				if (FAILED(hr)) {}
			};
			void init_device_objects(LPDIRECT3DDEVICE9 pDevice)
			{

				HRESULT hr;
				hr = pFontTahoma8->InitDeviceObjects(pDevice);
				if (FAILED(hr)) {}
				hr = pFontTahoma8->RestoreDeviceObjects();
				if (FAILED(hr)) {}

				hr = pFontTahoma10->InitDeviceObjects(pDevice);
				if (FAILED(hr)) {}
				hr = pFontTahoma10->RestoreDeviceObjects();
				if (FAILED(hr)) {}
			};

			// Fonts
			std::unique_ptr<CD3DFont> pFontTahoma8;
			std::unique_ptr<CD3DFont> pFontTahoma10;
		};

		enum GradientType
		{
			GRADIENT_VERTICAL,
			GRADIENT_HORIZONTAL
		};

		class c_renderer
		{
		public: // Function members
				// Basic non-drawing functions
			static bool render_initalized;

			c_font*	m_fonts();

			c_renderer();

			void init_device_objects(LPDIRECT3DDEVICE9 pDevice);
			void restore_device_objects(LPDIRECT3DDEVICE9 pDevice);
			void invalidate_device_objects();
			void setup_render_states();


			// Drawing functions

			void line(vec2_t vecPos1, vec2_t vecPos2, Color color);
			void line(float posx1, float posy1, float posx2, float posy2, Color color);
			void rect(vec2_t vecPos1, vec2_t vecPos2, Color color);
			void rect(float posx1, float posy1, float posx2, float posy2, Color color);
			void rect_filled(vec2_t vecPos1, vec2_t vecPos2, Color color);
			void rect_filled(float posx1, float posy1, float posx2, float posy2, Color color);
			void triangle(vec2_t pos1, vec2_t pos2, vec2_t pos3, Color color);
			void triangle_filled(vec2_t pos1, vec2_t pos2, vec2_t pos3, Color color);
			void rect_filled_gradient(vec2_t vecPos1, vec2_t vecPos2, Color col1, Color col2, GradientType type);

			void string(float posx, float posy, DWORD dwFlags, Color color, CD3DFont* pFont, const char* szText, ...);


			// Helpers
			vec2_t get_screen_center();

		private: // Variable members
			LPDIRECT3DDEVICE9   pDevice;
			D3DVIEWPORT9        pViewPort;
			c_font*				fonts;
		};
	}
}

