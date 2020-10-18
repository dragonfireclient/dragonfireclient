/*
Dragonfire
Copyright (C) 2020 Elias Fleckenstein <eliasfleckenstein@web.de>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/ 

#pragma once

#include "cpp_api/s_base.h"
#include <vector>
#include <string>

class ScriptApiCheatsCheat
{
public:
	ScriptApiCheatsCheat(const std::string &name, const std::string &setting);
	ScriptApiCheatsCheat(const std::string &name, const int &function);
	std::string m_name;
	bool is_enabled();
	void toggle(lua_State *L, int error_handler);

private:
	std::string m_setting;
	int m_function_ref;
};

class ScriptApiCheatsCategory
{
public:
	ScriptApiCheatsCategory(const std::string &name);
	~ScriptApiCheatsCategory();
	std::string m_name;
	void read_cheats(lua_State *L);
	std::vector<ScriptApiCheatsCheat *> m_cheats;	
};

class ScriptApiCheats : virtual public ScriptApiBase
{
public:
	virtual ~ScriptApiCheats();
	void init_cheats();
	void toggle_cheat(ScriptApiCheatsCheat *cheat);
	bool m_cheats_loaded = false;
	std::vector<ScriptApiCheatsCategory *> m_cheat_categories;
};
