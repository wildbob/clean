#pragma once
#include "client props.hpp"
namespace sdk
{
	class i_clientnetworkable;

	typedef i_clientnetworkable*   (*CreateClientClassFn)(int entnum, int serialNum);
	typedef i_clientnetworkable*   (*CreateEventFn)();
	class c_clientclass
	{
	public:
		CreateClientClassFn m_pCreateFn;
		CreateEventFn* m_pCreateEventFn;
		char			*m_pNetworkName;
		RecvTable		*m_pRecvTable;
		c_clientclass		*m_pNext;
		int				m_ClassID;
	};
}