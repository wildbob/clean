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

	c_clientclass* entity_t::get_client_class()
	{
		void *pNetworked = (void*)(this + 0x8);
		typedef c_clientclass*(__thiscall *OrigFn)(void*);
		return sdk::helpers::get_virtual_function<OrigFn>(pNetworked, 2)(pNetworked);
	}

	bool entity_t::is_dormant()
	{
		void *pNetworked = (void*)(this + 0x8);
		typedef bool(__thiscall *OrigFn)(void*);
		return sdk::helpers::get_virtual_function<OrigFn>(pNetworked, 9)(pNetworked);
	}

	int entity_t::get_index()
	{
		void *pNetworked = (void*)(this + 0x8);
		typedef int(__thiscall *OrigFn)(void*);
		return sdk::helpers::get_virtual_function<OrigFn>(pNetworked, 10)(pNetworked);
	}

	i_collideable* entity_t::get_collideable()
	{
		typedef i_collideable*(__thiscall *OrigFn)(void*);
		return sdk::helpers::get_virtual_function<OrigFn>(this, 3)(this);
	}
}