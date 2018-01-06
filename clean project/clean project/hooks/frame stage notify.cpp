#pragma once
#include "..\core.hpp"
#include "frame stage notify.hpp"
#include "..\sdk\angles.hpp"

namespace sdk
{
	namespace hooks
	{
		void __stdcall hk_frame_stage_notify(sdk::clientframestage_t cur_stage)
		{
			static auto frame_stage_o = csgo.m_hooks()->client_hook.get_original< decltype(&hk_frame_stage_notify) >(36);

			csgo.world_to_screen_matrix = csgo.m_engine()->world_to_screen_matrix();

			frame_stage_o(cur_stage);
		}
	}
}