#include "hooks.hpp"
#include "menu hooks.hpp"
#include "..\core.hpp"

namespace sdk
{
	namespace hooks
	{
		void c_hooks::setup_hooks()
		{
			d3d_hook.setup(csgo.m_d3d_device());
			d3d_hook.hook_index(42, hk_endscene);
			d3d_hook.hook_index(16, hk_reset);
		}
	}
}