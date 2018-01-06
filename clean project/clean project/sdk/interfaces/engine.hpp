#pragma once
#include "..\interface helpers.hpp"
#include "..\client class.hpp"
#include "..\player info.hpp"
#include "..\angles.hpp"
#include "..\net channel.hpp"

namespace sdk
{
	namespace interfaces
	{
		class c_engine
		{
		public:
			int get_local_player()
			{
				typedef int(__thiscall *get_local_playerfn)(void*);
				return sdk::helpers::get_virtual_function<get_local_playerfn>(this, 12)(this);
			}
			void get_screen_size(int& width, int& height)
			{
				typedef int(__thiscall *OrigFn)(void*, int&, int&);
				sdk::helpers::get_virtual_function<OrigFn>(this, 5)(this, width, height);
			}

			bool get_player_info(int ent_num, player_info_t *pinfo)
			{
				typedef bool(__thiscall *OrigFn)(void*, int, player_info_t*);
				return sdk::helpers::get_virtual_function<OrigFn>(this, 8)(this, ent_num, pinfo);
			}
			int get_player_user_id(int UserID)
			{
				using Original = int(__thiscall*)(void*, int);
				return sdk::helpers::get_virtual_function<Original>(this, 9)(this, UserID);
			}
			float get_last_time_stamp() {
				typedef float(__thiscall *OrigFn)(void*);
				return sdk::helpers::get_virtual_function<OrigFn>(this, 14)(this);
			}

			void get_view_angles(angle_t& va)
			{
				typedef void(__thiscall *OrigFn)(void*, angle_t&);
				sdk::helpers::get_virtual_function<OrigFn>(this, 18)(this, va);
			}

			void set_view_angles(angle_t& va)
			{
				typedef void(__thiscall *OrigFn)(void*, angle_t&);
				sdk::helpers::get_virtual_function<OrigFn>(this, 19)(this, va);
			}

			int get_max_clients() {
				typedef int(__thiscall *OrigFn)(void*);
				return sdk::helpers::get_virtual_function<OrigFn>(this, 20)(this);
			}

			bool is_in_game() {
				typedef bool(__thiscall *OrigFn)(void*);
				return sdk::helpers::get_virtual_function<OrigFn>(this, 26)(this);
			}

			bool is_connected() {
				typedef bool(__thiscall *OrigFn)(void*);
				return sdk::helpers::get_virtual_function<OrigFn>(this, 27)(this);
			}

			const VMatrix& world_to_screen_matrix()
			{
				typedef const VMatrix&(__thiscall *OrigFn)(void*);
				return sdk::helpers::get_virtual_function<OrigFn>(this, 37)(this);
			}

			i_net_channel*get_net_channel_info()
			{
				typedef i_net_channel*(__thiscall *OrigFn)(void*);
				return sdk::helpers::get_virtual_function<OrigFn>(this, 78)(this);
			}

			void execute_client_cmd(const char* szCmdString) {
				typedef void(__thiscall *OrigFn)(void*, const char *);
				sdk::helpers::get_virtual_function<OrigFn>(this, 108)(this, szCmdString);
			}

			void client_cmd_unrestricted(const char* szCmdString)
			{
				typedef void(__thiscall* OrigFn)(void*, const char*, char);
				sdk::helpers::get_virtual_function<OrigFn>(this, 114)(this, szCmdString, 1);
			}
		};
	}
}