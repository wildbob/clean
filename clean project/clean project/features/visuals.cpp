#include "visuals.hpp"
#include "..\sdk\entity.hpp"

namespace sdk
{
	namespace features
	{
		void c_visuals::draw_box(float x, float y, float w, float h, sdk::Color color, Color outline, float width, float height)
		{
			//top left
			csgo.m_render( )->line(x, y, x + width, y, color);
			csgo.m_render( )->line(x, y, x, y + height, color);

			csgo.m_render( )->line(x, y - 1, x + width, y - 1, outline);
			csgo.m_render( )->line(x - 1, y, x - 1, y + height, outline);

			//top right
			csgo.m_render( )->line(x + w, y, x + w - width, y, color);
			csgo.m_render( )->line(x + w, y, x + w, y + height, color);

			csgo.m_render( )->line(x + w + 1, y - 1, x + w - width, y - 1, outline);
			csgo.m_render( )->line(x + w + 1, y, x + w + 1, y + height, outline);

			//bottom left
			csgo.m_render( )->line(x, y + h, x, y + h - height, color);
			csgo.m_render( )->line(x, y + h, x + width, y + h, color);

			csgo.m_render( )->line(x - 1, y + h, x - 1, y + h - height, outline);
			csgo.m_render( )->line(x - 1, y + h + 1, x + width, y + h + 1, outline);

			//bottom right
			csgo.m_render( )->line(x + w, y + h, x + w - width, y + h, color);
			csgo.m_render( )->line(x + w, y + h, x + w, y + h - height, color);

			csgo.m_render( )->line(x + w, y + h + 1, x + w - width, y + h + 1, outline);
			csgo.m_render( )->line(x + w + 1, y + h, x + w + 1, y + h - height, outline);
		}


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

			vec3_t screen_points[8] = {};

			for (int i = 0; i < 8; i++) {
				if (!csgo.m_math()->world_to_screen(pointsTransformed[i], screen_points[i]))
					return box;
			}

			auto left = screen_points[0].x;
			auto top = screen_points[0].y;
			auto right = screen_points[0].x;
			auto bottom = screen_points[0].y;

			for (int i = 1; i < 8; i++) {
				if (left > screen_points[i].x)
					left = screen_points[i].x;
				if (top < screen_points[i].y)
					top = screen_points[i].y;
				if (right < screen_points[i].x)
					right = screen_points[i].x;
				if (bottom > screen_points[i].y)
					bottom = screen_points[i].y;
			}

			box.x = left;
			box.y = top;
			box.w = right - left;
			box.h = bottom - top;

			return box;
		}

		void c_visuals::initialize()
		{
			for (int i = 0; i < csgo.m_engine( )->get_max_clients( ); i++)
			{
				entity_t* m_entity = static_cast< entity_t* >(csgo.m_entitylist( )->get_entity( i ) );

				if (!m_entity)
					continue;

				if (!m_entity->is_alive())
					continue;

				if (m_entity->is_dormant())
					continue;

				if (m_entity->get_client_class()->m_ClassID != 35)
					continue;

				auto box = this->get_bounding_box(m_entity);

				this->draw_box(box.x, box.y, box.w, box.h, Color(150, 0, 0), Color(10, 10, 10), box.w, box.h);
			}
		}
	}
}