#include "utilities\netvar_manager.hpp"
#include "hooks\hooks.hpp"
#include <Windows.h>
#include <process.h>

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

	if (utils)
		delete[] utils;

	if (d3d_device)
		delete[] d3d_device;

	if (hooks)
		delete[] hooks;

	if (render)
		delete[] render;
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

sdk::utilities::c_utils* c_csgo::m_utils()
{
	if (!utils)
		utils = new sdk::utilities::c_utils();

	return utils;
}

sdk::hooks::c_hooks* c_csgo::m_hooks()
{
	if (!hooks)
		hooks = new sdk::hooks::c_hooks();

	return hooks;
}

sdk::renderer::c_renderer* c_csgo::m_render()
{
	if (!render)
		render = new sdk::renderer::c_renderer();

	return render;
}

IDirect3DDevice9* c_csgo::m_d3d_device()
{
	if (!d3d_device)
		d3d_device = **(IDirect3DDevice9***)(m_utils()->find_pattern_ida( "shaderapidx9.dll", "A1 ? ? ? ? 50 8B 08 FF 51 0C" ) + 1);

	return d3d_device;
}




void cheat_init(PVOID pParam)
{
	g_netvar = std::make_unique<c_netvar>();

	g_netvar->initialize();

	g_netvar->dump();

	csgo.m_hooks()->setup_hooks();
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