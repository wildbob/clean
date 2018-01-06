#pragma once
#include "angles.hpp"

namespace sdk
{
	class i_collideable
	{
	public:
		virtual void pad0();
		virtual const vec3_t& obb_min() const;
		virtual const vec3_t& obb_max() const;
	};
}