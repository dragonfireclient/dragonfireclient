minetest.register_globalstep(function()
	local player = minetest.localplayer 
	if not player then return end
	local pos = minetest.localplayer:get_pos()
	local wielditem = minetest.localplayer:get_wielded_item()
	if minetest.settings:get_bool("scaffold") then
		minetest.place_node(vector.add(pos, {x = 0, y = -0.6, z = 0}))
	end
	if minetest.settings:get_bool("highway_z") and wielditem then
		local z = pos.z
		local positions = {
			{x = 0, y = 0, z = z},
			{x = 1, y = 0, z = z},
			{x = 2, y = 1, z = z},
			{x = -2, y = 1, z = z},
			{x = -2, y = 0, z = z},
			{x = -1, y = 0, z = z},
			{x = 2, y = 0, z = z}
		}
		for _, p in pairs(positions) do
			local node = minetest.get_node_or_nil(p)
			if node and not minetest.get_node_def(node.name).walkable then
				minetest.place_node(p)
			end
		end
	end
	if minetest.settings:get_bool("fucker") then
		local p = minetest.find_node_near(pos, 5, "group:bed", true)
		if p then
			minetest.dig_node(p)
		end
	end
end) 

minetest.register_cheat("Scaffold", "World", "scaffold")
minetest.register_cheat("HighwayZ", "World", "highway_z")
minetest.register_cheat("Fucker", "World", "fucker")
