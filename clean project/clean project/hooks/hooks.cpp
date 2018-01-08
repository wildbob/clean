#include "hooks.hpp"
#include "menu hooks.hpp"
#include "frame stage notify.hpp"
#include "..\core.hpp"

namespace sdk
{
	namespace hooks
	{
		void c_hooks::setup_hooks()
		{
			sdk::hooks::draw_points_ret_addr = (void*)(csgo.m_utils()->find_pattern_ida("studiorender.dll", "8B 7D FC 03 F8"));

			d3d_hook.setup(csgo.m_d3d_device());
			d3d_hook.hook_index(16, hk_reset);
			d3d_hook.hook_index(17, hk_present);
			d3d_hook.hook_index(82, hk_draw);

			client_hook.setup(csgo.m_client());
			client_hook.hook_index(36, hk_frame_stage_notify);
		}
	}
}