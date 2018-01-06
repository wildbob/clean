#pragma once
#include "features.hpp"

namespace sdk
{
	namespace features
	{
		c_features::c_features()
		{
			visuals = nullptr;
		}

		c_features::~c_features()
		{
			if (visuals)
				delete[] visuals;
		}

		c_visuals* c_features::m_visuals( )
		{
			if (!visuals)
				visuals = new c_visuals();

			return visuals;
		}
	}
}