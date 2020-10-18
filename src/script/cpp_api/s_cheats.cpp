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

#include "cpp_api/s_cheats.h"
#include "cpp_api/s_base.h"
#include "cpp_api/s_internal.h"
#include "settings.h"

ScriptApiCheatsCheat::ScriptApiCheatsCheat(
		const std::string &name, const std::string &setting) :
		m_name(name),
		m_setting(setting), m_function_ref(0)
{
}

ScriptApiCheatsCheat::ScriptApiCheatsCheat(const std::string &name, const int &function) :
		m_name(name), m_setting(""), m_function_ref(function)
{
}

bool ScriptApiCheatsCheat::is_enabled()
{
	try {
		return !m_function_ref && g_settings->getBool(m_setting);
	} catch (SettingNotFoundException &) {
		return false;
	}
}

void ScriptApiCheatsCheat::toggle(lua_State *L, int error_handler)
{
	if (m_function_ref) {
		lua_rawgeti(L, LUA_REGISTRYINDEX, m_function_ref);
		lua_pcall(L, 0, 0, error_handler);
	} else
		g_settings->setBool(m_setting, !is_enabled());
}

ScriptApiCheatsCategory::ScriptApiCheatsCategory(const std::string &name) : m_name(name)
{
}

ScriptApiCheatsCategory::~ScriptApiCheatsCategory()
{
	for (auto i = m_cheats.begin(); i != m_cheats.end(); i++)
		delete *i;
}

void ScriptApiCheatsCategory::read_cheats(lua_State *L)
{
	lua_pushnil(L);
	while (lua_next(L, -2)) {
		ScriptApiCheatsCheat *cheat = nullptr;
		std::string name = lua_tostring(L, -2);
		if (lua_isstring(L, -1))
			cheat = new ScriptApiCheatsCheat(name, lua_tostring(L, -1));
		else if (lua_isfunction(L, -1)) {
			cheat = new ScriptApiCheatsCheat(
					name, luaL_ref(L, LUA_REGISTRYINDEX));
			lua_pushnil(L);
		}
		if (cheat)
			m_cheats.push_back(cheat);
		lua_pop(L, 1);
	}
}

ScriptApiCheats::~ScriptApiCheats()
{
	for (auto i = m_cheat_categories.begin(); i != m_cheat_categories.end(); i++)
		delete *i;
}

void ScriptApiCheats::init_cheats()
{
	SCRIPTAPI_PRECHECKHEADER

	lua_getglobal(L, "core");
	lua_getfield(L, -1, "cheats");
	if (!lua_istable(L, -1)) {
		lua_pop(L, 2);
		return;
	}
	lua_pushnil(L);
	while (lua_next(L, -2)) {
		if (lua_istable(L, -1)) {
			ScriptApiCheatsCategory *category =
					new ScriptApiCheatsCategory(lua_tostring(L, -2));
			category->read_cheats(L);
			m_cheat_categories.push_back(category);
		}
		lua_pop(L, 1);
	}
	lua_pop(L, 2);
	m_cheats_loaded = true;
}

void ScriptApiCheats::toggle_cheat(ScriptApiCheatsCheat *cheat)
{
	SCRIPTAPI_PRECHECKHEADER

	PUSH_ERROR_HANDLER(L);
	int error_handler = lua_gettop(L) - 1;
	lua_insert(L, error_handler);

	cheat->toggle(L, error_handler);
}
