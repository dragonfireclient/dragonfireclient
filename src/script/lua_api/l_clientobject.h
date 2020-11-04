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

#include "lua_api/l_base.h"
#include "client/clientobject.h"
#include "client/content_cao.h"

class ClientObjectRef : public ModApiBase
{
public:
	ClientObjectRef(ClientActiveObject *object);

	~ClientObjectRef() = default;

	static void Register(lua_State *L);

	static void create(lua_State *L, ClientActiveObject *object);
	static void create(lua_State *L, s16 id);

	static ClientObjectRef *checkobject(lua_State *L, int narg);

private:
	ClientActiveObject *m_object = nullptr;
	static const char className[];
	static luaL_Reg methods[];

	static ClientActiveObject *get_cao(ClientObjectRef *ref);
	static GenericCAO *get_generic_cao(ClientObjectRef *ref, lua_State *L);

	static int gc_object(lua_State *L);

	// get_pos(self)
	// returns: {x=num, y=num, z=num}
	static int l_get_pos(lua_State *L);

	// get_velocity(self)
	static int l_get_velocity(lua_State *L);

	// get_acceleration(self)
	static int l_get_acceleration(lua_State *L);

	// get_rotation(self)
	static int l_get_rotation(lua_State *L);

	// is_player(self)
	static int l_is_player(lua_State *L);

	// is_local_player(self)
	static int l_is_local_player(lua_State *L);

	// get_name(self)
	static int l_get_name(lua_State *L);

	// get_attach(self)
	static int l_get_attach(lua_State *L);

	// get_nametag(self)
	static int l_get_nametag(lua_State *L);

	// get_textures(self)
	static int l_get_item_textures(lua_State *L);

	// get_hp(self)
	static int l_get_max_hp(lua_State *L);

	// punch(self)
	static int l_punch(lua_State *L);

	// rightclick(self)
	static int l_rightclick(lua_State *L);
};
