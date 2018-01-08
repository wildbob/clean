#pragma once
#include "..\sdk\sdk.hpp"
#include <cstdint>


namespace sdk
{
	class entity_t;
	class Color;
	namespace features
	{
		class c_visuals
		{
		private:
			struct box_t
			{
				box_t()
				{
					x = 0.f;
					y = 0.f;
					w = 0.f;
					h = 0.f;
				}

				box_t(float X, float Y, float W, float H)
				{
					x = X;
					y = Y;
					w = W;
					h = H;
				}

				float x, y, w, h;
			};
			void draw_box(float x, float y, float w, float h, Color color, Color outline, float width, float height);
		public:
			box_t		get_bounding_box(entity_t* m_entity);
			void		initialize();
		};
	}
}