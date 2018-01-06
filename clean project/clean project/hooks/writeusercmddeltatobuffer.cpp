#include "..\core.hpp"
#include "writeusercmddeltatobuffer.hpp"

namespace sdk
{
	namespace hooks
	{
		int tickBaseShift = 0;
		bool inSendMove = false, firstSendMovePack = false;
		bool __fastcall hk_write_user_cmd_delta_to_buffer(sdk::interfaces::c_client* this0,int nSlot, void* buf, int from, int to, bool isNewCmd)
		{
			/*static auto o_func = csgo.m_hooks( )->client_hook.get_original< decltype(&hk_write_user_cmd_delta_to_buffer) >(23);
			static uint64_t sig = csgo.m_utils( )->find_pattern_ida( "client.dll", "55 8B EC 83 E4 F8 51 53 56 8B D9 8B 0D" );

			if (tickBaseShift <= 0 || _ReturnAddress() != &sig) {
				return o_func(this0, nSlot, buf, from, to, isNewCmd);
			}
			if (from != -1) {
				return true; // Skip next calls
			}
		
			PVOID pebp;
			__asm mov pebp, ebp;

			auto msg = reinterpret_cast<sdk::c_msg_move_t*>((uintptr_t)pebp + 0xFCC);
			auto netChan = csgo.m_engine()->get_net_channel_info();

			int newCommands = msg->numNewCommands;

			// Call CL_SendMove multiple times - split fake move commands between packets to bypass 62 limit
			if (!inSendMove) {
				if (newCommands <= 0) {
					return false;
				}

				inSendMove = true;
				firstSendMovePack = true;
				tickBaseShift += newCommands;

				while (tickBaseShift > 0) {
					engine->CL_SendMove();
					netChan->trans(false);
					firstSendMovePack = false;
				}

				inSendMove = false;
				return false; // Stop current CL_SendMove from sending
			}*/
		}
	}
}