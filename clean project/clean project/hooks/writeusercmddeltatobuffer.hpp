#include "..\sdk\sdk.hpp"
#include "..\sdk\interfaces\client.hpp"

namespace sdk
{
	namespace hooks
	{
		extern bool __fastcall hk_write_user_cmd_delta_to_buffer(sdk::interfaces::c_client* this0, int nSlot, void* buf, int from, int to, bool isNewCmd);
	}
}