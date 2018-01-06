#include "..\sdk\sdk.hpp"

namespace sdk
{
	struct entity_t;
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
		public:
			box_t get_bounding_box(entity_t* m_entity);
		};
	}
}