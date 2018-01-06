#pragma once

#include "..\sdk\vfunc_hook.hpp"


namespace sdk
{
	namespace hooks
	{
		class c_hooks
		{
		private:
		public:

			void setup_hooks();
			c_vfunc_hook d3d_hook;
		};
	}
}