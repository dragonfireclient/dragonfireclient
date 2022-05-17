/*
Minetest
Copyright (C) 2013 celeron55, Perttu Ahola <celeron55@gmail.com>
Copyright (C) 2017 nerzhul, Loic Blot <loic.blot@unix-experience.fr>

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

#include "nodedef.h"
#include "itemdef.h"
#include "s_client.h"
#include "s_internal.h"
#include "client/client.h"
#include "common/c_converter.h"
#include "common/c_content.h"
#include "lua_api/l_clientobject.h"
#include "s_item.h"

void ScriptApiClient::on_mods_loaded()
{
	SCRIPTAPI_PRECHECKHEADER

	// Get registered shutdown hooks
	lua_getglobal(L, "core");
	lua_getfield(L, -1, "registered_on_mods_loaded");
	// Call callbacks
	try {
		runCallbacks(0, RUN_CALLBACKS_MODE_FIRST);
	} catch (LuaError &e) {
		getClient()->setFatalError(e);
	}
}

void ScriptApiClient::on_shutdown()
{
	SCRIPTAPI_PRECHECKHEADER

	// Get registered shutdown hooks
	lua_getglobal(L, "core");
	lua_getfield(L, -1, "registered_on_shutdown");
	// Call callbacks
	try {
		runCallbacks(0, RUN_CALLBACKS_MODE_FIRST);
	} catch (LuaError &e) {
		getClient()->setFatalError(e);
	}
}

bool ScriptApiClient::on_sending_message(const std::string &message)
{
	SCRIPTAPI_PRECHECKHEADER

	// Get core.registered_on_chat_messages
	lua_getglobal(L, "core");
	lua_getfield(L, -1, "registered_on_sending_chat_message");
	// Call callbacks
	lua_pushstring(L, message.c_str());
	try {
		runCallbacks(1, RUN_CALLBACKS_MODE_OR_SC);
	} catch (LuaError &e) {
		getClient()->setFatalError(e);
		return true;
	}
	return readParam<bool>(L, -1);
}

bool ScriptApiClient::on_receiving_message(const std::string &message)
{
	SCRIPTAPI_PRECHECKHEADER

	// Get core.registered_on_chat_messages
	lua_getglobal(L, "core");
	lua_getfield(L, -1, "registered_on_receiving_chat_message");
	// Call callbacks
	lua_pushstring(L, message.c_str());
	try {
		runCallbacks(1, RUN_CALLBACKS_MODE_OR_SC);
	} catch (LuaError &e) {
		getClient()->setFatalError(e);
		return true;
	}
	return readParam<bool>(L, -1);
}

void ScriptApiClient::on_damage_taken(int32_t damage_amount)
{
	SCRIPTAPI_PRECHECKHEADER

	// Get core.registered_on_chat_messages
	lua_getglobal(L, "core");
	lua_getfield(L, -1, "registered_on_damage_taken");
	// Call callbacks
	lua_pushinteger(L, damage_amount);
	try {
		runCallbacks(1, RUN_CALLBACKS_MODE_OR_SC);
	} catch (LuaError &e) {
		getClient()->setFatalError(e);
	}
}

void ScriptApiClient::on_hp_modification(int32_t newhp)
{
	SCRIPTAPI_PRECHECKHEADER

	// Get core.registered_on_chat_messages
	lua_getglobal(L, "core");
	lua_getfield(L, -1, "registered_on_hp_modification");
	// Call callbacks
	lua_pushinteger(L, newhp);
	try {
		runCallbacks(1, RUN_CALLBACKS_MODE_OR_SC);
	} catch (LuaError &e) {
		getClient()->setFatalError(e);
	}
}

void ScriptApiClient::on_death()
{
	SCRIPTAPI_PRECHECKHEADER

	// Get registered shutdown hooks
	lua_getglobal(L, "core");
	lua_getfield(L, -1, "registered_on_death");
	// Call callbacks
	try {
		runCallbacks(0, RUN_CALLBACKS_MODE_FIRST);
	} catch (LuaError &e) {
		getClient()->setFatalError(e);
	}
}

void ScriptApiClient::environment_step(float dtime)
{
	SCRIPTAPI_PRECHECKHEADER

	// Get core.registered_globalsteps
	lua_getglobal(L, "core");
	lua_getfield(L, -1, "registered_globalsteps");
	// Call callbacks
	lua_pushnumber(L, dtime);
	try {
		runCallbacks(1, RUN_CALLBACKS_MODE_FIRST);
	} catch (LuaError &e) {
		getClient()->setFatalError(e);
	}
}

void ScriptApiClient::on_formspec_input(const std::string &formname,
	const StringMap &fields)
{
	SCRIPTAPI_PRECHECKHEADER

	// Get core.registered_on_chat_messages
	lua_getglobal(L, "core");
	lua_getfield(L, -1, "registered_on_formspec_input");
	// Call callbacks
	// param 1
	lua_pushstring(L, formname.c_str());
	// param 2
	lua_newtable(L);
	StringMap::const_iterator it;
	for (it = fields.begin(); it != fields.end(); ++it) {
		const std::string &name = it->first;
		const std::string &value = it->second;
		lua_pushstring(L, name.c_str());
		lua_pushlstring(L, value.c_str(), value.size());
		lua_settable(L, -3);
	}
	try {
		runCallbacks(2, RUN_CALLBACKS_MODE_OR_SC);
	} catch (LuaError &e) {
		getClient()->setFatalError(e);
	}
}

bool ScriptApiClient::on_dignode(v3s16 p, MapNode node)
{
	SCRIPTAPI_PRECHECKHEADER

	const NodeDefManager *ndef = getClient()->ndef();

	// Get core.registered_on_dignode
	lua_getglobal(L, "core");
	lua_getfield(L, -1, "registered_on_dignode");

	// Push data
	push_v3s16(L, p);
	pushnode(L, node, ndef);

	// Call functions
	try {
		runCallbacks(2, RUN_CALLBACKS_MODE_OR);
	} catch (LuaError &e) {
		getClient()->setFatalError(e);
		return true;
	}
	return lua_toboolean(L, -1);
}

bool ScriptApiClient::on_punchnode(v3s16 p, MapNode node)
{
	SCRIPTAPI_PRECHECKHEADER

	const NodeDefManager *ndef = getClient()->ndef();

	// Get core.registered_on_punchnode
	lua_getglobal(L, "core");
	lua_getfield(L, -1, "registered_on_punchnode");

	// Push data
	push_v3s16(L, p);
	pushnode(L, node, ndef);

	// Call functions
	try {
		runCallbacks(2, RUN_CALLBACKS_MODE_OR);
	} catch (LuaError &e) {
		getClient()->setFatalError(e);
		return true;
	}
	return readParam<bool>(L, -1);
}

bool ScriptApiClient::on_placenode(const PointedThing &pointed, const ItemDefinition &item)
{
	SCRIPTAPI_PRECHECKHEADER

	// Get core.registered_on_placenode
	lua_getglobal(L, "core");
	lua_getfield(L, -1, "registered_on_placenode");

	// Push data
	push_pointed_thing(L, pointed, true);
	push_item_definition(L, item);

	// Call functions
	try {
		runCallbacks(2, RUN_CALLBACKS_MODE_OR);
	} catch (LuaError &e) {
		getClient()->setFatalError(e);
		return true;
	}
	return readParam<bool>(L, -1);
}

bool ScriptApiClient::on_item_use(const ItemStack &item, const PointedThing &pointed)
{
	SCRIPTAPI_PRECHECKHEADER

	// Get core.registered_on_item_use
	lua_getglobal(L, "core");
	lua_getfield(L, -1, "registered_on_item_use");

	// Push data
	LuaItemStack::create(L, item);
	push_pointed_thing(L, pointed, true);

	// Call functions
	try {
		runCallbacks(2, RUN_CALLBACKS_MODE_OR);
	} catch (LuaError &e) {
		getClient()->setFatalError(e);
		return true;
	}
	return readParam<bool>(L, -1);
}

bool ScriptApiClient::on_recieve_physics_override(float speed, float jump, float gravity, bool sneak, bool sneak_glitch, bool new_move)
{
	SCRIPTAPI_PRECHECKHEADER

	// Get core.registered_on_recieve_physics_override
	lua_getglobal(L, "core");
	lua_getfield(L, -1, "registered_on_recieve_physics_override");

	// Push data
	push_physics_override(L, speed, jump, gravity, sneak, sneak_glitch, new_move);

	// Call functions
	runCallbacks(1, RUN_CALLBACKS_MODE_OR);
	return readParam<bool>(L, -1);
}

bool ScriptApiClient::on_play_sound(SimpleSoundSpec spec)
{
	SCRIPTAPI_PRECHECKHEADER

	// Get core.registered_on_play_sound
	lua_getglobal(L, "core");
	lua_getfield(L, -1, "registered_on_play_sound");

	// Push data
	push_soundspec(L, spec);

	// Call functions
	runCallbacks(1, RUN_CALLBACKS_MODE_OR);
	return readParam<bool>(L, -1);
}

bool ScriptApiClient::on_spawn_particle(struct ParticleParameters param)
{
	SCRIPTAPI_PRECHECKHEADER

	// Get core.registered_on_play_sound

	lua_getglobal(L, "core");
	lua_getfield(L, -1, "registered_on_spawn_particle");

	// Push data
	lua_newtable(L);
	push_v3f(L, param.pos);
	lua_setfield(L, -2, "pos");
	push_v3f(L, param.vel);
	lua_setfield(L, -2, "velocity");
	push_v3f(L, param.acc);
	lua_setfield(L, -2, "acceleration");
	setfloatfield(L, -1, "expirationtime", param.expirationtime);
	setboolfield(L, -1, "collisiondetection", param.collisiondetection);
	setboolfield(L, -1, "collision_removal", param.collision_removal);
	setboolfield(L, -1, "object_collision", param.object_collision);
	setboolfield(L, -1, "vertical", param.vertical);
	push_animation_definition(L, param.animation);
	lua_setfield(L, -2, "animation");
	setstringfield(L, -1, "texture", param.texture);
	setintfield(L, -1, "glow", param.glow);
	if (param.node.getContent() != CONTENT_IGNORE) {
		pushnode(L, param.node, getGameDef()->ndef());
		lua_setfield(L, -2, "node");
	}
	setintfield(L, -1, "node_tile", param.node_tile);

	// Call functions
	runCallbacks(1, RUN_CALLBACKS_MODE_OR);
	return readParam<bool>(L, -1);
}

void ScriptApiClient::on_object_properties_change(s16 id)
{
	SCRIPTAPI_PRECHECKHEADER

	// Get core.registered_on_object_properties_change
	lua_getglobal(L, "core");
	lua_getfield(L, -1, "registered_on_object_properties_change");

	// Push data
	push_objectRef(L, id);

	// Call functions
	runCallbacks(1, RUN_CALLBACKS_MODE_FIRST);
}

void ScriptApiClient::on_object_hp_change(s16 id)
{
	SCRIPTAPI_PRECHECKHEADER

	// Get core.registered_on_object_hp_change
	lua_getglobal(L, "core");
	lua_getfield(L, -1, "registered_on_object_hp_change");

	// Push data
	push_objectRef(L, id);

	// Call functions
	runCallbacks(1, RUN_CALLBACKS_MODE_FIRST);
}

bool ScriptApiClient::on_object_add(s16 id)
{
	SCRIPTAPI_PRECHECKHEADER

	// Get core.registered_on_object_add
	lua_getglobal(L, "core");
	lua_getfield(L, -1, "registered_on_object_add");

	// Push data
	push_objectRef(L, id);

	// Call functions
	runCallbacks(1, RUN_CALLBACKS_MODE_OR);
	return readParam<bool>(L, -1);
}

bool ScriptApiClient::on_inventory_open(Inventory *inventory)
{
	SCRIPTAPI_PRECHECKHEADER

	lua_getglobal(L, "core");
	lua_getfield(L, -1, "registered_on_inventory_open");

	push_inventory_lists(L, *inventory);

	try {
		runCallbacks(1, RUN_CALLBACKS_MODE_OR);
	} catch (LuaError &e) {
		getClient()->setFatalError(e);
		return true;
	}
	return readParam<bool>(L, -1);
}

void ScriptApiClient::open_enderchest()
{
	SCRIPTAPI_PRECHECKHEADER

	PUSH_ERROR_HANDLER(L);
	int error_handler = lua_gettop(L) - 1;
	lua_insert(L, error_handler);

	lua_getglobal(L, "core");
	lua_getfield(L, -1, "open_enderchest");
	if (lua_isfunction(L, -1))
		lua_pcall(L, 0, 0, error_handler);
}

v3f ScriptApiClient::get_send_speed(v3f speed)
{
	SCRIPTAPI_PRECHECKHEADER

	PUSH_ERROR_HANDLER(L);
	int error_handler = lua_gettop(L) - 1;
	lua_insert(L, error_handler);

	lua_getglobal(L, "core");
	lua_getfield(L, -1, "get_send_speed");
	if (lua_isfunction(L, -1)) {
		speed /= BS;
		push_v3f(L, speed);
		lua_pcall(L, 1, 1, error_handler);
		speed = read_v3f(L, -1);
		speed *= BS;
	}

	return speed;
}

void ScriptApiClient::set_node_def(const ContentFeatures &f)
{
	SCRIPTAPI_PRECHECKHEADER

	lua_getglobal(L, "core");
	lua_getfield(L, -1, "registered_nodes");

	push_content_features(L, f);
	lua_setfield(L, -2, f.name.c_str());
}

void ScriptApiClient::set_item_def(const ItemDefinition &i)
{
	SCRIPTAPI_PRECHECKHEADER

	lua_getglobal(L, "core");
	lua_getfield(L, -1, "registered_items");

	push_item_definition(L, i);
	lua_setfield(L, -2, i.name.c_str());
}

void ScriptApiClient::setEnv(ClientEnvironment *env)
{
	ScriptApiBase::setEnv(env);
}
