#include "entity.hpp"

namespace sdk
{
	
	vec3_t entity_t::get_eye_position()
	{
		return get_origin() + get_view_offset();
	}

	bool entity_t::is_alive()
	{
		return get_life_state() == life_alive;
	}

	const matrix3x4_t& entity_t::get_coordinate_frame()
	{
		static auto _m_rgflCoordinateFrame = csgo.m_netvar( )->get_offset("DT_BaseEntity", "m_CollisionGroup") - 0x30;
		return *(matrix3x4_t*)((uintptr_t)this + _m_rgflCoordinateFrame);
	}
}