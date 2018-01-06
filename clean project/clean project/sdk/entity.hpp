#include <Windows.h>
#include "..\utilities\netvar_manager.hpp"
#include "enums.hpp"

namespace sdk
{
	struct entity_t
	{
		netvar(int, get_team, "DT_BaseEntity", "m_iTeamNum")
		netvar(vec3_t, get_origin, "DT_BaseEntity", "m_vecOrigin")
		netvar(float, get_simulation_time, "DT_BaseEntity", "m_flSimulationTime")
		netvar(bool, has_defuser, "DT_CSPlayer", "m_bHasDefuser");
		netvar(bool, is_immune, "DT_CSPlayer", "m_bGunGameImmunity");
		netvar(int32_t, get_shots_fired, "DT_CSPlayer", "m_iShotsFired");
		netvar(angle_t, get_eye_angles, "DT_CSPlayer", "m_angEyeAngles[0]");
		netvar(int, get_armor_value, "DT_CSPlayer", "m_ArmorValue");
		netvar(bool, has_helmet, "DT_CSPlayer", "m_bHasHelmet");
		netvar(bool, is_scoped, "DT_CSPlayer", "m_bIsScoped");;
		netvar(float, get_lowerbody_yaw, "DT_CSPlayer", "m_flLowerBodyYawTarget");
		netvar(float, get_flash_duration, "DT_CSPlayer", "m_flFlashDuration");
		netvar(int32_t, get_health, "DT_BasePlayer", "m_iHealth");
		netvar(int32_t, get_life_state, "DT_BasePlayer", "m_lifeState");
		netvar(int32_t, get_flags, "DT_BasePlayer", "m_fFlags");
		netvar(int32_t, get_tick_base, "DT_BasePlayer", "m_nTickBase");
		netvar(vec3_t, get_view_offset, "DT_BasePlayer", "m_vecViewOffset[0]");
		netvar(angle_t, get_view_punch_angle, "DT_BasePlayer", "m_viewPunchAngle");
		netvar(angle_t, get_aim_punch_angle, "DT_BasePlayer", "m_aimPunchAngle");
		netvar(vec3_t, get_velocity, "DT_BasePlayer", "m_vecVelocity[0]");
		netvar(float, get_max_speed, "DT_BasePlayer", "m_flMaxspeed");

		vec3_t	get_eye_position();
		bool	is_alive();
	};
}