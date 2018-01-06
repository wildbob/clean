#pragma once
#include "..\interface helpers.hpp"
#include "..\client class.hpp"
#include "..\player info.hpp"
#include "..\angles.hpp"
#include "..\net channel.hpp"
#include "..\trace.hpp"

namespace sdk
{
	namespace interfaces
	{
		class c_enginetrace
		{
		public:
			int get_point_contents(const vec3_t &vecAbsPosition, int contentsMask = MASK_ALL, sdk::IHandleEntity** ppEntity = NULL) {
				typedef int(__thiscall *OrigFn)(void*, const vec3_t &, int, IHandleEntity**);
				return sdk::helpers::get_virtual_function<OrigFn>(this, 0)(this, vecAbsPosition, contentsMask, ppEntity);
			}

			void clip_ray_to_entity(const ray_t &ray, unsigned int fMask, IHandleEntity *pEnt, c_gametrace *pTrace) {
				typedef void(__thiscall *OrigFn)(void*, const ray_t&, unsigned int, IHandleEntity*, c_gametrace*);
				sdk::helpers::get_virtual_function<OrigFn>(this, 3)(this, ray, fMask, pEnt, pTrace);
			}

			void trace_ray(const ray_t &ray, unsigned int fMask, i_tracefilter *pTraceFilter, c_gametrace *pTrace) {
				typedef void(__thiscall *OrigFn)(void*, const ray_t&, unsigned int, i_tracefilter*, c_gametrace*);
				sdk::helpers::get_virtual_function<OrigFn>(this, 5)(this, ray, fMask, pTraceFilter, pTrace);
			}
		};
	}
}