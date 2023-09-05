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

#pragma once

#include "util/pointedthing.h"
#include "cpp_api/s_base.h"
#include "mapnode.h"
#include "itemdef.h"
#include "util/string.h"
#include "util/pointedthing.h"
#include "lua_api/l_item.h"
#include "particles.h"

#ifdef _CRT_MSVCP_CURRENT
#include <cstdint>
#endif

class ClientEnvironment;

class ScriptApiClient : virtual public ScriptApiBase
{
public:
	// Calls when mods are loaded
	void on_mods_loaded();

	// Calls on_shutdown handlers
	void on_shutdown();

	// Chat message handlers
	bool on_sending_message(const std::string &message);
	bool on_receiving_message(const std::string &message);

	void on_damage_taken(int32_t damage_amount);
	void on_hp_modification(int32_t newhp);
	void on_death();
	void environment_step(float dtime);
	void on_formspec_input(const std::string &formname, const StringMap &fields);

	bool on_dignode(v3s16 p, MapNode node);
	bool on_punchnode(v3s16 p, MapNode node);
	bool on_placenode(const PointedThing &pointed, const ItemDefinition &item);
	bool on_item_use(const ItemStack &item, const PointedThing &pointed);
	bool on_recieve_physics_override(float override_speed, float override_jump,
			float override_gravity, bool sneak, bool sneak_glitch,
			bool new_move);
	bool on_play_sound(SimpleSoundSpec spec);
	bool on_spawn_particle(struct ParticleParameters param);
	bool on_receive_particlespawner(struct ParticleSpawnerParameters param);
	void on_object_properties_change(s16 id);
	void on_object_hp_change(s16 id);
	bool on_object_add(s16 id);

	bool on_inventory_open(Inventory *inventory);
	void open_enderchest();

	v3f get_send_speed(v3f speed);

	void set_node_def(const ContentFeatures &f);
	void set_item_def(const ItemDefinition &i);

	void setEnv(ClientEnvironment *env);
};
