#include "visuals.hpp"
#include "..\sdk\entity.hpp"

namespace sdk
{
	namespace features
	{
		c_visuals::box_t c_visuals::get_bounding_box(entity_t* m_entity)
		{
			box_t box{};

			vec3_t flb, brt, blb, frt, frb, brb, blt, flt;

			vec3_t m_min = m_entity->get_collideable()->obb_min();
			vec3_t m_max = m_entity->get_collideable()->obb_max();

			const matrix3x4_t& trans = m_entity->get_coordinate_frame();

			vec3_t points[] = {
				vec3_t(m_min.x, m_min.y, m_min.z),
				vec3_t(m_min.x, m_max.y, m_min.z),
				vec3_t(m_max.x, m_max.y, m_min.z),
				vec3_t(m_max.x, m_min.y, m_min.z),
				vec3_t(m_max.x, m_max.y, m_max.z),
				vec3_t(m_min.x, m_max.y, m_max.z),
				vec3_t(m_min.x, m_min.y, m_max.z),
				vec3_t(m_max.x, m_min.y, m_max.z)
			};

			vec3_t pointsTransformed[8];
			for (int i = 0; i < 8; i++) {
				csgo.m_math()->vector_transform(points[i], trans, pointsTransformed[i]);
			}


			if (!csgo.m_math()->world_to_screen(pointsTransformed[3], flb) || !csgo.m_math()->world_to_screen(pointsTransformed[5], brt)
				|| !csgo.m_math()->world_to_screen(pointsTransformed[0], blb) || !csgo.m_math()->world_to_screen(pointsTransformed[4], frt)
				|| !csgo.m_math()->world_to_screen(pointsTransformed[2], frb) || !csgo.m_math()->world_to_screen(pointsTransformed[1], brb)
				|| !csgo.m_math()->world_to_screen(pointsTransformed[6], blt) || !csgo.m_math()->world_to_screen(pointsTransformed[7], flt))
				return box;

			vec3_t arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };

			// Init this shit
			auto left = flb.x;
			auto top = flb.y;
			auto right = flb.x;
			auto bottom = flb.y;

			// Find the bounding corners for our box
			for (int i = 1; i < 8; i++)
			{
				if (left > arr[i].x)
					left = arr[i].x;
				if (bottom < arr[i].y)
					bottom = arr[i].y;
				if (right < arr[i].x)
					right = arr[i].x;
				if (top > arr[i].y)
					top = arr[i].y;
			}

			box.x = left;
			box.y = top;
			box.w = right - left;
			box.h = bottom - top;

			return box;
		}
	}
}