#pragma once
#include <Windows.h>
#include <cstdio>
#include "sdk\interfaces\client.hpp"
#include "sdk\interfaces\engine.hpp"
#include "sdk\interfaces\engine trace.hpp"
#include "sdk\interfaces\convar.hpp"
#include "sdk\interfaces\entity list.hpp"
#include "utilities\utilities.hpp"
#include "sdk\sdk.hpp"
#include "hooks\hooks.hpp"
#include "renderer\render.hpp"

class c_csgo
{
private:
	template< class T > T* c_csgo::get_interface(std::string szModuleName, std::string szInterfaceName, bool bSkip = false)
	{
		if (szModuleName.empty() || szInterfaceName.empty())
			return nullptr;
		typedef PVOID(*CreateInterfaceFn)(const char* pszName, int* piReturnCode);
		CreateInterfaceFn hInterface = nullptr;
		while (!hInterface)
		{
			hInterface = (CreateInterfaceFn)GetProcAddress(GetModuleHandleA(szModuleName.c_str()), "CreateInterface");
			Sleep(5);
		}

		char pszBuffer[256];
		for (int i = 0; i < 100; i++)
		{
			sprintf_s(pszBuffer, "%s%0.3d", szInterfaceName.c_str(), i);
			PVOID pInterface = hInterface(pszBuffer, nullptr);

			if (pInterface && pInterface != NULL)
			{
				if (bSkip)
					sprintf_s(pszBuffer, "%s%0.3d", szInterfaceName.c_str(), i + 1);

				Sleep(5);
				break;
			}
		}
		printf(pszBuffer);
		printf("\n");

		return (T*)hInterface(pszBuffer, nullptr);
	}
protected:
	//interfaces
	sdk::interfaces::c_engine*				engine;
	sdk::interfaces::c_client*				client;
	sdk::interfaces::c_enginetrace*			enginetrace;
	sdk::interfaces::c_cvar*				convar;
	sdk::interfaces::c_cliententitylist*	entitylist;

	//utilities
	sdk::utilities::c_utils*				utils;
	IDirect3DDevice9*						d3d_device;

	//hooks
	sdk::hooks::c_hooks*					hooks;

	//renderer
	sdk::renderer::c_renderer*				render;
public:
	c_csgo();
	~c_csgo();
	//interfaces
	sdk::interfaces::c_engine*				m_engine( );
	sdk::interfaces::c_client*				m_client( );
	sdk::interfaces::c_enginetrace*			m_enginetrace( );
	sdk::interfaces::c_cvar*				m_convar( );
	sdk::interfaces::c_cliententitylist*	m_entitylist( );

	//utilities
	sdk::utilities::c_utils*				m_utils( );
	IDirect3DDevice9*						m_d3d_device( );
	sdk::hooks::c_hooks*					m_hooks( );
	sdk::renderer::c_renderer*				m_render( );
};

extern c_csgo csgo;