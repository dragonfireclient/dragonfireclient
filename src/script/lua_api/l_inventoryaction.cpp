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

#include "l_inventoryaction.h"
#include "l_internal.h"
#include "client/client.h"

int LuaInventoryAction::gc_object(lua_State *L)
{
	LuaInventoryAction *o = *(LuaInventoryAction **)(lua_touserdata(L, 1));
	delete o;
	return 0;
}

int LuaInventoryAction::mt_tostring(lua_State *L)
{
	LuaInventoryAction *o = checkobject(L, 1);
	std::ostringstream os(std::ios::binary);
	o->m_action->serialize(os);
	lua_pushfstring(L, "InventoryAction(\"%s\")", os.str().c_str());
	return 1;
}

int LuaInventoryAction::l_apply(lua_State *L)
{
	LuaInventoryAction *o = checkobject(L, 1);

	std::ostringstream os(std::ios::binary);
	o->m_action->serialize(os);
	
	std::istringstream is(os.str(), std::ios_base::binary);
	
	InventoryAction *a = InventoryAction::deSerialize(is);

	getClient(L)->inventoryAction(a);
	return 0;
}

int LuaInventoryAction::l_from(lua_State *L)
{
	GET_MOVE_ACTION
	readFullInventoryLocationInto(L, &act->from_inv, &act->from_list, &act->from_i);
	return 0;
}

int LuaInventoryAction::l_to(lua_State *L)
{
	GET_MOVE_ACTION
	readFullInventoryLocationInto(L, &act->to_inv, &act->to_list, &act->to_i);
	return 0;
}

int LuaInventoryAction::l_craft(lua_State *L)
{
	LuaInventoryAction *o = checkobject(L, 1);
	
	if (o->m_action->getType() != IAction::Craft)
		return 0;
		
	std::string locStr;
	InventoryLocation loc;
	
	locStr = readParam<std::string>(L, 2);
	
	try {
		loc.deSerialize(locStr);
		dynamic_cast<ICraftAction *>(o->m_action)->craft_inv = loc;
	} catch (SerializationError &) {}
	
	return 0;
}

int LuaInventoryAction::l_set_count(lua_State *L)
{
	LuaInventoryAction *o = checkobject(L, 1);
	
	s16 count = luaL_checkinteger(L, 2);
	
	switch (o->m_action->getType()) {
	case IAction::Move:
		((IMoveAction *)o->m_action)->count = count;
		break;
	case IAction::Drop:
		((IDropAction *)o->m_action)->count = count;
		break;
	case IAction::Craft:
		((ICraftAction *)o->m_action)->count = count;
		break;
	}
	
	return 0;
}

LuaInventoryAction::LuaInventoryAction(const IAction &type) : m_action(nullptr)
{
	switch (type) {
	case IAction::Move:
		m_action = new IMoveAction();
		break;
	case IAction::Drop:
		m_action = new IDropAction();
		break;
	case IAction::Craft:
		m_action = new ICraftAction();
		break;
	}
}

LuaInventoryAction::~LuaInventoryAction()
{
	delete m_action;
}

void LuaInventoryAction::readFullInventoryLocationInto(lua_State *L, InventoryLocation *loc, std::string *list, s16 *index)
{
	try {
		loc->deSerialize(readParam<std::string>(L, 2));
		std::string l = readParam<std::string>(L, 3);
		*list = l;
		*index = luaL_checkinteger(L, 4) - 1;
	} catch (SerializationError &) {}
}

int LuaInventoryAction::create_object(lua_State *L)
{
	IAction type;
	std::string typeStr;
	
	typeStr = readParam<std::string>(L, 1);
	
	if (typeStr == "move")
		type = IAction::Move;
	else if (typeStr == "drop")
		type = IAction::Drop;
	else if (typeStr == "craft")
		type = IAction::Craft;
	else
		return 0;

	LuaInventoryAction *o = new LuaInventoryAction(type);
	*(void **)(lua_newuserdata(L, sizeof(void *))) = o;
	luaL_getmetatable(L, className);
	lua_setmetatable(L, -2);
	return 1;
}

int LuaInventoryAction::create(lua_State *L, const IAction &type)
{
	LuaInventoryAction *o = new LuaInventoryAction(type);
	*(void **)(lua_newuserdata(L, sizeof(void *))) = o;
	luaL_getmetatable(L, className);
	lua_setmetatable(L, -2);
	return 1;
}

LuaInventoryAction *LuaInventoryAction::checkobject(lua_State *L, int narg)
{
	return *(LuaInventoryAction **)luaL_checkudata(L, narg, className);
}

void LuaInventoryAction::Register(lua_State *L)
{
	lua_newtable(L);
	int methodtable = lua_gettop(L);
	luaL_newmetatable(L, className);
	int metatable = lua_gettop(L);

	lua_pushliteral(L, "__metatable");
	lua_pushvalue(L, methodtable);
	lua_settable(L, metatable);

	lua_pushliteral(L, "__index");
	lua_pushvalue(L, methodtable);
	lua_settable(L, metatable);

	lua_pushliteral(L, "__gc");
	lua_pushcfunction(L, gc_object);
	lua_settable(L, metatable);

	lua_pushliteral(L, "__tostring");
	lua_pushcfunction(L, mt_tostring);
	lua_settable(L, metatable);

	lua_pop(L, 1);

	luaL_openlib(L, 0, methods, 0);
	lua_pop(L, 1);

	lua_register(L, className, create_object);
}

const char LuaInventoryAction::className[] = "InventoryAction";
const luaL_Reg LuaInventoryAction::methods[] = {
	luamethod(LuaInventoryAction, apply),
	luamethod(LuaInventoryAction, from),
	luamethod(LuaInventoryAction, to),
	luamethod(LuaInventoryAction, craft),
	luamethod(LuaInventoryAction, set_count),
	{0,0}
};
