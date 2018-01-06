#pragma once
#include "..\sdk\sdk.hpp"
#include "visuals.hpp"

namespace sdk
{
	namespace features
	{
		class c_features
		{
		private:
			c_visuals*		visuals;
		public:
			c_features();
			~c_features();
			c_visuals*		m_visuals( );
		};
	}
}