local placed_crystal
local switched_to_totem = 0
local used_sneak = true

core.register_globalstep(function(dtime)
	if not minetest.settings:get_bool("crystal_pvp") then return end
	local player = core.localplayer
	if not player then return end
	local control = player:get_control()
	local pointed = core.get_pointed_thing()
	local item = player:get_wielded_item():get_name()
	if placed_crystal then
		if core.switch_to_item("mobs_mc:totem") then
			switched_to_totem = 5
		end
		placed_crystal = false
	elseif switched_to_totem > 0 then
		if item ~= "mobs_mc:totem"  then
			switched_to_totem = 0
		elseif pointed and pointed.type == "object" then
			pointed.ref:punch()
			switched_to_totem = 0
		else
			switched_to_totem = switched_to_totem
		end
	elseif control.RMB and item == "mcl_end:crystal" then
		placed_crystal = true
	elseif control.sneak then
		if used_sneak then
			core.switch_to_item("mobs_mc:totem")
			return
		end
		core.switch_to_item("mcl_end:crystal")
		if pointed and pointed.type == "node" then
			local pos = core.get_pointed_thing_position(pointed)
			local node = core.get_node_or_nil(pos)
			if node and (node.name == "mcl_core:obsidian" or node.name == "mcl_core:bedrock") then
				core.place_node(pos)
				placed_crystal = true
			end
		end
		used_sneak = true
	else
		used_sneak = false
	end
end)
