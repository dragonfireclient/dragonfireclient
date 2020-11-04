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

#include "inventorymanager.h"
#include "lua_api/l_base.h"

#define GET_MOVE_ACTION                                                                  \
	LuaInventoryAction *o = checkobject(L, 1);                                       \
	if (o->m_action->getType() == IAction::Craft)                                    \
		return 0;                                                                \
	MoveAction *act = dynamic_cast<MoveAction *>(o->m_action);

class LuaInventoryAction : public ModApiBase
{
private:
	InventoryAction *m_action;

	static void readFullInventoryLocationInto(lua_State *L, InventoryLocation *loc,
			std::string *list, s16 *index);

	static const char className[];
	static const luaL_Reg methods[];

	// Exported functions

	// garbage collector
	static int gc_object(lua_State *L);

	// __tostring metamethod
	static int mt_tostring(lua_State *L);

	// apply(self)
	static int l_apply(lua_State *L);

	// from(self, location, list, index)
	static int l_from(lua_State *L);

	// to(self, location, list, index)
	static int l_to(lua_State *L);

	// craft(self, location)
	static int l_craft(lua_State *L);

	// set_count(self, count)
	static int l_set_count(lua_State *L);

public:
	LuaInventoryAction(const IAction &type);
	~LuaInventoryAction();

	// LuaInventoryAction(inventory action type)
	// Creates an LuaInventoryAction and leaves it on top of stack
	static int create_object(lua_State *L);
	// Not callable from Lua
	static int create(lua_State *L, const IAction &type);
	static LuaInventoryAction *checkobject(lua_State *L, int narg);
	static void Register(lua_State *L);
};
