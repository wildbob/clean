#pragma once
#include <memory>
#include <iostream>
#include <unordered_map>
#include "..\sdk\client props.hpp"

namespace sdk
{
	namespace utilities
	{
		class c_netvar
		{
			struct netvar_table
			{
				std::string               name;
				sdk::RecvProp*                 prop;
				uint32_t                  offset;
				std::vector<sdk::RecvProp*>    child_props;
				std::vector<netvar_table> child_tables;
			};
		public:
			void initialize();

			void dump();
			void dump(std::ostream& stream);

			uint32_t      get_offset(const std::string& tableName, const std::string& propName);
			sdk::RecvProp*     get_netvar_prop(const std::string& tableName, const std::string& propName);

		private:
			static netvar_table  load_table(sdk::RecvTable* clientClass);
			static void          dump_table(std::ostream& stream, const netvar_table& table, uint32_t indentation);
			static uint32_t      get_offset(const netvar_table& table, const std::string& propName);
			static sdk::RecvProp*     get_netvar_prop(const netvar_table& table, const std::string& propName);

		private:
			std::vector<netvar_table>  database;
		};
	}
}