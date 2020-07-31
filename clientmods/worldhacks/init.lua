minetest.register_globalstep(function()
	if not minetest.localplayer then return end
	if minetest.settings:get_bool("scaffold") then
		minetest.place_node(vector.add(minetest.localplayer:get_pos(), {x = 0, y = -0.6, z = 0}))
	end
	if minetest.settings:get_bool("highway") and minetest.localplayer:get_wielded_item() then
		local z = minetest.localplayer:get_pos().z
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
end) 
