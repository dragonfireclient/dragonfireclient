/*
Dragonfire
Copyright (C) 2020 system32

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

#include "lua_api/l_clientobject.h"
#include "l_internal.h"
#include "common/c_converter.h"
#include "common/c_content.h"
#include "client/client.h"
#include "object_properties.h"
#include "util/pointedthing.h"

ClientActiveObject *ClientObjectRef::getClientActiveObject()
{
	return m_object;
}

ClientObjectRef *ClientObjectRef::checkobject(lua_State *L, int narg)
{
	luaL_checktype(L, narg, LUA_TUSERDATA);
	void *userdata = luaL_checkudata(L, narg, className);
	if (!userdata)
		luaL_typerror(L, narg, className);
	return *(ClientObjectRef **)userdata;
}

ClientActiveObject *ClientObjectRef::get_cao(ClientObjectRef *ref)
{
	ClientActiveObject *obj = ref->m_object;
	return obj;
}

GenericCAO *ClientObjectRef::get_generic_cao(ClientObjectRef *ref, lua_State *L)
{
	ClientActiveObject *obj = get_cao(ref);
	if (!obj)
		return nullptr;
	ClientEnvironment &env = getClient(L)->getEnv();
	GenericCAO *gcao = env.getGenericCAO(obj->getId());
	return gcao;
}

int ClientObjectRef::l_get_pos(lua_State *L)
{
	ClientObjectRef *ref = checkobject(L, 1);
	ClientActiveObject *cao = get_cao(ref);
	if (!cao)
		return 0;
	push_v3f(L, cao->getPosition() / BS);
	return 1;
}

int ClientObjectRef::l_get_velocity(lua_State *L)
{
	ClientObjectRef *ref = checkobject(L, 1);
	GenericCAO *gcao = get_generic_cao(ref, L);
	if (!gcao)
		return 0;
	push_v3f(L, gcao->getVelocity() / BS);
	return 1;
}

int ClientObjectRef::l_get_acceleration(lua_State *L)
{
	ClientObjectRef *ref = checkobject(L, 1);
	GenericCAO *gcao = get_generic_cao(ref, L);
	if (!gcao)
		return 0;
	push_v3f(L, gcao->getAcceleration() / BS);
	return 1;
}

int ClientObjectRef::l_get_rotation(lua_State *L)
{
	ClientObjectRef *ref = checkobject(L, 1);
	GenericCAO *gcao = get_generic_cao(ref, L);
	if (!gcao)
		return 0;
	push_v3f(L, gcao->getRotation());
	return 1;
}

int ClientObjectRef::l_is_player(lua_State *L)
{
	ClientObjectRef *ref = checkobject(L, 1);
	GenericCAO *gcao = get_generic_cao(ref, L);
	if (!gcao)
		return 0;
	lua_pushboolean(L, gcao->isPlayer());
	return 1;
}

int ClientObjectRef::l_is_local_player(lua_State *L)
{
	ClientObjectRef *ref = checkobject(L, 1);
	GenericCAO *gcao = get_generic_cao(ref, L);
	if (!gcao)
		return 0;
	lua_pushboolean(L, gcao->isLocalPlayer());
	return 1;
}

int ClientObjectRef::l_get_name(lua_State *L)
{
	ClientObjectRef *ref = checkobject(L, 1);
	GenericCAO *gcao = get_generic_cao(ref, L);
	if (!gcao)
		return 0;
	lua_pushstring(L, gcao->getName().c_str());
	return 1;
}

int ClientObjectRef::l_get_attach(lua_State *L)
{
	ClientObjectRef *ref = checkobject(L, 1);
	GenericCAO *gcao = get_generic_cao(ref, L);
	if (!gcao)
		return 0;
	ClientActiveObject *parent = gcao->getParent();
	if (!parent)
		return 0;
	push_objectRef(L, parent->getId());
	return 1;
}

int ClientObjectRef::l_get_nametag(lua_State *L)
{
	log_deprecated(L, "Deprecated call to get_nametag, use get_properties().nametag "
			  "instead");
	ClientObjectRef *ref = checkobject(L, 1);
	GenericCAO *gcao = get_generic_cao(ref, L);
	if (!gcao)
		return 0;
	ObjectProperties *props = gcao->getProperties();
	lua_pushstring(L, props->nametag.c_str());
	return 1;
}

int ClientObjectRef::l_get_item_textures(lua_State *L)
{
	log_deprecated(L, "Deprecated call to get_item_textures, use "
			  "get_properties().textures instead");
	ClientObjectRef *ref = checkobject(L, 1);
	GenericCAO *gcao = get_generic_cao(ref, L);
	if (!gcao)
		return 0;
	ObjectProperties *props = gcao->getProperties();
	lua_newtable(L);

	for (std::string &texture : props->textures) {
		lua_pushstring(L, texture.c_str());
	}
	return 1;
}

int ClientObjectRef::l_get_max_hp(lua_State *L)
{
	log_deprecated(L, "Deprecated call to get_max_hp, use get_properties().hp_max "
			  "instead");
	ClientObjectRef *ref = checkobject(L, 1);
	GenericCAO *gcao = get_generic_cao(ref, L);
	if (!gcao)
		return 0;
	ObjectProperties *props = gcao->getProperties();
	lua_pushnumber(L, props->hp_max);
	return 1;
}

int ClientObjectRef::l_get_properties(lua_State *L)
{
	ClientObjectRef *ref = checkobject(L, 1);
	GenericCAO *gcao = get_generic_cao(ref, L);
	if (!gcao)
		return 0;
	ObjectProperties *prop = gcao->getProperties();
	push_object_properties(L, prop);
	return 1;
}

int ClientObjectRef::l_set_properties(lua_State *L)
{
	ClientObjectRef *ref = checkobject(L, 1);
	GenericCAO *gcao = get_generic_cao(ref, L);
	if (!gcao)
		return 0;
	ObjectProperties prop = *gcao->getProperties();
	read_object_properties(L, 2, nullptr, &prop, getClient(L)->idef());
	gcao->setProperties(prop);
	return 1;
}

int ClientObjectRef::l_get_hp(lua_State *L)
{
	ClientObjectRef *ref = checkobject(L, 1);
	GenericCAO *gcao = get_generic_cao(ref, L);
	if (!gcao)
		return 0;
	lua_pushnumber(L, gcao->getHp());
	return 1;
}

int ClientObjectRef::l_punch(lua_State *L)
{
	ClientObjectRef *ref = checkobject(L, 1);
	GenericCAO *gcao = get_generic_cao(ref, L);
	if (!gcao)
		return 0;
	PointedThing pointed(gcao->getId(), v3f(0, 0, 0), v3s16(0, 0, 0), 0);
	getClient(L)->interact(INTERACT_START_DIGGING, pointed);
	return 0;
}

int ClientObjectRef::l_rightclick(lua_State *L)
{
	ClientObjectRef *ref = checkobject(L, 1);
	GenericCAO *gcao = get_generic_cao(ref, L);
	if (!gcao)
		return 0;
	PointedThing pointed(gcao->getId(), v3f(0, 0, 0), v3s16(0, 0, 0), 0);
	getClient(L)->interact(INTERACT_PLACE, pointed);
	return 0;
}

int ClientObjectRef::l_remove(lua_State *L)
{
	ClientObjectRef *ref = checkobject(L, 1);
	ClientActiveObject *cao = get_cao(ref);
	if (!cao)
		return 0;
	getClient(L)->getEnv().removeActiveObject(cao->getId());

	return 0;
}

int ClientObjectRef::l_set_nametag_images(lua_State *L)
{
	ClientObjectRef *ref = checkobject(L, 1);
	GenericCAO *gcao = get_generic_cao(ref, L);
	if (!gcao)
		return 0;
	gcao->nametag_images.clear();
	if (lua_istable(L, 2)) {
		lua_pushnil(L);
		while (lua_next(L, 2) != 0) {
			gcao->nametag_images.push_back(lua_tostring(L, -1));
			lua_pop(L, 1);
		}
	}
	gcao->updateNametag();

	return 0;
}

ClientObjectRef::ClientObjectRef(ClientActiveObject *object) : m_object(object)
{
}

void ClientObjectRef::create(lua_State *L, ClientActiveObject *object)
{
	ClientObjectRef *o = new ClientObjectRef(object);
	*(void **)(lua_newuserdata(L, sizeof(void *))) = o;
	luaL_getmetatable(L, className);
	lua_setmetatable(L, -2);
}

void ClientObjectRef::create(lua_State *L, s16 id)
{
	create(L, ((ClientEnvironment *)getEnv(L))->getActiveObject(id));
}

void ClientObjectRef::set_null(lua_State *L)
{
	ClientObjectRef *obj = checkobject(L, -1);
	obj->m_object = nullptr;
}

int ClientObjectRef::gc_object(lua_State *L)
{
	ClientObjectRef *obj = *(ClientObjectRef **)(lua_touserdata(L, 1));
	delete obj;
	return 0;
}

// taken from LuaLocalPlayer
void ClientObjectRef::Register(lua_State *L)
{
	lua_newtable(L);
	int methodtable = lua_gettop(L);
	luaL_newmetatable(L, className);
	int metatable = lua_gettop(L);

	lua_pushliteral(L, "__metatable");
	lua_pushvalue(L, methodtable);
	lua_settable(L, metatable); // hide metatable from lua getmetatable()

	lua_pushliteral(L, "__index");
	lua_pushvalue(L, methodtable);
	lua_settable(L, metatable);

	lua_pushliteral(L, "__gc");
	lua_pushcfunction(L, gc_object);
	lua_settable(L, metatable);

	lua_pop(L, 1); // Drop metatable

	luaL_openlib(L, 0, methods, 0); // fill methodtable
	lua_pop(L, 1);			// Drop methodtable
}

const char ClientObjectRef::className[] = "ClientObjectRef";
luaL_Reg ClientObjectRef::methods[] = {luamethod(ClientObjectRef, get_pos),
		luamethod(ClientObjectRef, get_velocity),
		luamethod(ClientObjectRef, get_acceleration),
		luamethod(ClientObjectRef, get_rotation),
		luamethod(ClientObjectRef, is_player),
		luamethod(ClientObjectRef, is_local_player),
		luamethod(ClientObjectRef, get_name),
		luamethod(ClientObjectRef, get_attach),
		luamethod(ClientObjectRef, get_nametag),
		luamethod(ClientObjectRef, get_item_textures),
		luamethod(ClientObjectRef, get_properties),
		luamethod(ClientObjectRef, set_properties),
		luamethod(ClientObjectRef, get_hp),
		luamethod(ClientObjectRef, get_max_hp), luamethod(ClientObjectRef, punch),
		luamethod(ClientObjectRef, rightclick),
		luamethod(ClientObjectRef, remove),
		luamethod(ClientObjectRef, set_nametag_images), {0, 0}};
