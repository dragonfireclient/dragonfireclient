core.register_on_dignode(function(pos)
	if core.settings:get_bool("replace") then
		core.after(0, minetest.place_node, pos)
	end
end)

local etime = 0

core.register_globalstep(function(dtime)
	etime = etime + dtime
	if etime < 1 then return end
	local player = core.localplayer
	if not player then return end
	local pos = player:get_pos()
	local item = player:get_wielded_item()
	local def = core.get_item_def(item:get_name())
	local nodes_per_tick = tonumber(minetest.settings:get("nodes_per_tick")) or 8
	if item and item:get_count() > 0 and def and def.node_placement_prediction ~= "" then
		if core.settings:get_bool("scaffold") then
			local p = vector.round(vector.add(pos, {x = 0, y = -0.6, z = 0}))
			local node = minetest.get_node_or_nil(p)
			if not node or minetest.get_node_def(node.name).buildable_to then
				core.place_node(p)
			end
		elseif core.settings:get_bool("scaffold_plus") then
			local z = pos.z
			local positions = {
				{x = 0, y = -0.6, z = 0},
                {x = 1, y = -0.6, z = 0},
                {x = -1, y = -0.6, z = 0},
                {x = -1, y = -0.6, z = -1},
                {x = 0, y = -0.6, z = -1},
                {x = 1, y = -0.6, z = -1},
                {x = -1, y = -0.6, z = 1},
                {x = 0, y = -0.6, z = 1},
                {x = 1, y = -0.6, z = 1}
			}
			for i, p in pairs(positions) do
				core.place_node(vector.add(pos, p))
			end
		elseif core.settings:get_bool("block_water") then
			local positions = core.find_nodes_near(pos, 5, {"mcl_core:water_source", "mcl_core:water_floating"}, true)
			for i, p in pairs(positions) do
				if i > nodes_per_tick then return end
				core.place_node(p)
			end
		elseif core.settings:get_bool("autotnt") then
			local positions = core.find_nodes_near_under_air_except(pos, 5, item:get_name(), true)
			for i, p in pairs(positions) do
				if i > nodes_per_tick then return end
				core.place_node(vector.add(p, {x = 0, y = 1, z = 0}))
			end
		end
	end
	if core.settings:get_bool("nuke") then
		local i = 0
		for x = pos.x - 5, pos.x + 5 do
			for y = pos.y - 5, pos.y + 5 do
				for z = pos.z - 5, pos.z + 5 do
					local p = vector.new(x, y, z)
					local node = core.get_node_or_nil(p)
					local def = node and core.get_node_def(node.name)
					if def and def.diggable then
						if i > nodes_per_tick then return end
						core.dig_node(p)
						i = i + 1
					end
				end
			end
		end
	end
end) 

 
