#pragma once
#include "..\interface helpers.hpp"
#include "..\client class.hpp"
#include "..\player info.hpp"
#include "..\angles.hpp"
#include "..\net channel.hpp"

typedef unsigned long c_basehandle;

namespace sdk
{
	class entity_t;
	namespace interfaces
	{
		class c_cliententitylist
		{
		public:
			virtual void				Function0();
			virtual void				Function1();
			virtual void				Function2();
			virtual entity_t *			get_entity(int entnum);
			virtual entity_t *			get_entity_handle(c_basehandle hEnt) = 0;
			virtual int					num_of_entites(bool bIncludeNonNetworkable) = 0;
			virtual int					get_hightest_entity_index(void);
			virtual void				set_max_entities(int maxents);
			virtual int					get_max_entities();
		};
	}
}