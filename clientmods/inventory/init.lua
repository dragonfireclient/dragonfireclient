local modname = minetest.get_current_modname()
local modpath = minetest.get_modpath(modname)

dofile(modpath .. "/invhack.lua") 
dofile(modpath .. "/enderchest.lua") 

local elapsed_time = 0
local tick_time = 0.05

minetest.register_globalstep(function(dtime)
	elapsed_time = elapsed_time + dtime
	if elapsed_time < tick_time then return end
	local player = minetest.localplayer
	if not player then return end
	local item = player:get_wielded_item()
	if item:get_count() == 0 and minetest.settings:get_bool("next_item") then
		local index = player:get_wield_index()
		player:set_wield_index(index + 1)
	end
	elapsed_time = 0
end)

local function check_tool(groups, old_best_time)
	local toolcaps = minetest.localplayer:get_wielded_item():get_tool_capabilities()
	if not toolcaps then return end
	local best_time = old_best_time
	for group, groupdef in pairs(toolcaps.groupcaps) do
		local level = groups[group]
		if level then
			local this_time = groupdef.times[level]
			if this_time < best_time then
				best_time = this_time
			end
		end
	end
	return best_time < old_best_time, best_time
end

minetest.register_on_punchnode(function(pos, node)
	if not minetest.settings:get_bool("autotool") then return end
	local player = minetest.localplayer
	local groups = minetest.get_node_def(node.name).groups
	local new_index = player:get_wield_index()
	local better, best = check_tool(groups, math.huge)
	for i = 0, 35 do
		player:set_wield_index(i)
		better, best = check_tool(groups, best)
		if better then
			new_index = i
		end
	end
	player:set_wield_index(new_index)
end)

minetest.register_cheat("NextItem", "Inventory", "next_item")
minetest.register_cheat("AutoTool", "Inventory", "autotool")
