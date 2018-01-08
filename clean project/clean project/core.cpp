#include "core.hpp"
#include "hooks\hooks.hpp"
#include <Windows.h>
#include <process.h>
#include "hooks\menu hooks.hpp"

c_csgo csgo;

c_csgo::c_csgo()
{
	client = nullptr;
	engine = nullptr;
	enginetrace = nullptr;
	convar = nullptr;
	entitylist = nullptr;
	utils = nullptr;
	d3d_device = nullptr;
	hooks = nullptr;
	render = nullptr;
	clientstate = nullptr;
	features = nullptr;
	netvar = nullptr;
	math = nullptr;
	localplayer = nullptr;
	menu = nullptr;
	settings = nullptr;
	input_system = nullptr;
}

c_csgo::~c_csgo()
{
	if (engine)
		delete[] engine;

	if (client)
		delete[] client;

	if (enginetrace)
		delete[] enginetrace;

	if (convar)
		delete[] convar;

	if (entitylist)
		delete[] entitylist;

	if (d3d_device)
		delete[] d3d_device;

	if (clientstate)
		delete[] clientstate;

	if (input_system)
		delete[] input_system;
}


sdk::interfaces::c_engine* c_csgo::m_engine( )
{
	if (!engine)
		engine = get_interface< sdk::interfaces::c_engine >( "engine.dll", "VEngineClient" );

	return engine;
}

sdk::interfaces::c_client* c_csgo::m_client()
{
	if (!client)
		client = get_interface< sdk::interfaces::c_client >( "client.dll", "VClient" );

	return client;
}

sdk::interfaces::c_enginetrace* c_csgo::m_enginetrace()
{
	if (!enginetrace)
		enginetrace = get_interface< sdk::interfaces::c_enginetrace >( "engine.dll", "EngineTraceClient" );

	return enginetrace;
}

sdk::interfaces::c_cvar* c_csgo::m_convar()
{
	if (!convar)
		convar = get_interface< sdk::interfaces::c_cvar >( "vstdlib.dll", "VEngineCvar" );

	return convar;
}

sdk::interfaces::c_cliententitylist* c_csgo::m_entitylist()
{
	if (!entitylist)
		entitylist = get_interface< sdk::interfaces::c_cliententitylist >( "client.dll", "VClientEntityList" );

	return entitylist;
}

sdk::interfaces::c_clientstate* c_csgo::m_clientstate()
{
	if (!clientstate && engine)
		clientstate = **reinterpret_cast< sdk::interfaces::c_clientstate*** > ((*reinterpret_cast< uintptr_t** > (engine))[12] + 0x10);

	return clientstate;
}

sdk::utilities::c_utils* c_csgo::m_utils()
{
	if (!utils)
		utils = std::make_unique<sdk::utilities::c_utils>();

	return utils.get();
}

sdk::hooks::c_hooks* c_csgo::m_hooks()
{
	if (!hooks)
		hooks = std::make_unique<sdk::hooks::c_hooks>();

	return hooks.get();
}

sdk::renderer::c_renderer* c_csgo::m_render()
{
	if (!render)
		render = std::make_unique<sdk::renderer::c_renderer>();

	return render.get();
}

IDirect3DDevice9* c_csgo::m_d3d_device()
{
	if (!d3d_device)
		d3d_device = **(IDirect3DDevice9***)(m_utils()->find_pattern_ida( "shaderapidx9.dll", "A1 ? ? ? ? 50 8B 08 FF 51 0C" ) + 1);

	return d3d_device;
}

sdk::features::c_features* c_csgo::m_features()
{
	if (!features)
		features = std::make_unique<sdk::features::c_features>();

	return features.get();
}

sdk::utilities::c_netvar* c_csgo::m_netvar()
{
	if (!netvar)
		netvar = std::make_unique<sdk::utilities::c_netvar>();

	return netvar.get();
}

sdk::utilities::c_math* c_csgo::m_math()
{
	if (!math)
		math = std::make_unique<sdk::utilities::c_math>();

	return math.get();
}

sdk::entity_t* c_csgo::m_localplayer()
{
	if (!localplayer)
		localplayer = m_entitylist()->get_entity(m_engine()->get_local_player());

	return localplayer;
}

sdk::menu::c_menu* c_csgo::m_menu()
{
	if (!menu)
		menu = std::make_unique<sdk::menu::c_menu>();

	return menu.get();
}

sdk::menu::c_settings* c_csgo::m_settings()
{
	if (!settings)
		settings = std::make_unique<sdk::menu::c_settings>();

	return settings.get();
}

sdk::interfaces::c_inputsystem* c_csgo::m_input_system()
{
	if (!input_system)
		input_system = get_interface< sdk::interfaces::c_inputsystem > ( "inputsystem.dll", "InputSystemVersion" );

	return input_system;
}

void cheat_init(PVOID pParam)
{
	csgo.m_netvar( )->initialize();

	csgo.m_netvar( )->dump();

	while (!(sdk::hooks::m_window = FindWindowA("Valve001", NULL)))
		Sleep(200);

	if (sdk::hooks::m_window)
		sdk::hooks::wndproc_o = (WNDPROC)SetWindowLongPtr(sdk::hooks::m_window, GWL_WNDPROC, (LONG_PTR)sdk::hooks::hk_wndproc);

	csgo.m_hooks( )->setup_hooks();
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:

		_beginthread(cheat_init, 0, NULL);

		break;

	case DLL_PROCESS_DETACH:

		break;
	}

	return TRUE;
}