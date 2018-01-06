#pragma once
#include "..\interface helpers.hpp"
#include "..\client class.hpp"
#include "..\player info.hpp"
#include "..\angles.hpp"
#include "..\net channel.hpp"
#include "..\trace.hpp"

namespace sdk
{
	class c_convar
	{
	public:
		void internal_set_string(const char *str)
		{
			typedef void(__thiscall* SetStringFn)(void*, const char *);
			sdk::helpers::get_virtual_function< SetStringFn >(this, 17)(this, str);
		}
		char* get_name()
		{
			typedef char*(__thiscall* SetStringFn)(void*);
			return sdk::helpers::get_virtual_function< SetStringFn >(this, 5)(this);
		}
		void set_value(const char* value)
		{
			typedef void(__thiscall* SetStringFn)(void*, const char*);
			return sdk::helpers::get_virtual_function<SetStringFn>(this, 14)(this, value);
		}
		void set_value(int value)
		{
			typedef void(__thiscall* SetStringFn)(void*, int);
			return sdk::helpers::get_virtual_function<SetStringFn>(this, 16)(this, value);
		}
		char pad_0x0000[0x4]; //0x0000
		c_convar* pNext; //0x0004 
		__int32 bRegistered; //0x0008 
		char* pszName; //0x000C 
		char* pszHelpString; //0x0010 
		__int32 nFlags; //0x0014 
		char pad_0x0018[0x4]; //0x0018
		c_convar* pParent; //0x001C 
		char* pszDefaultValue; //0x0020 
		char* strString; //0x0024 
		__int32 StringLength; //0x0028 
		float fValue; //0x002C 
		__int32 nValue; //0x0030 
		__int32 bHasMin; //0x0034 
		float fMinVal; //0x0038 
		__int32 bHasMax; //0x003C 
		float fMaxVal; //0x0040 
		void* fnChangeCallback; //0x0044 

	};//Size=0x0048
	namespace interfaces
	{
		typedef void(*FnChangeCallback_t)(c_convar *var, const char *pOldValue, float flOldValue);
		class c_cvar
		{
		public:
			c_convar	*find_convar(const char *var_name)
			{
				typedef c_convar*(__thiscall* FindVarFn)(void*, const char *);
				return sdk::helpers::get_virtual_function<FindVarFn>(this, 15)(this, var_name);
			}
			virtual void			register_command(c_convar *pCommandBase) = 0;
			virtual void			unregister_command(c_convar *pCommandBase) = 0;
			// Value set
			virtual void set_value(const char *pValue) = 0;
			virtual void set_value(float flValue) = 0;
			virtual void set_value(int nValue) = 0;
			// Return name of command
			virtual const char *get_name(void) const = 0;

			// Accessors.. not as efficient as using GetState()/GetInfo()
			// if you call these methods multiple times on the same Icon_var
			virtual bool is_flag_set(int nFlag) const = 0;
		};
	}
}