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


}