#pragma once
#include "..\sdk\sdk.hpp"
#include "..\sdk\enums.hpp"

namespace sdk
{
	namespace hooks
	{
		extern void __stdcall hk_frame_stage_notify(clientframestage_t curStage);
	}
}