mapbot.register_bot("place_into", "Automatically place wielditem into specified nodes.", "nodes", function(nodes) 
	local pos = minetest.find_node_near(minetest.localplayer:get_pos(), 5, nodes, true)
	if pos then
		minetest.place_node(pos)
	end
end)

mapbot.register_bot("dig_nodes", "Automatically dig specified nodes.", "nodes", function(nodes) 
	local pos = minetest.find_node_near(minetest.localplayer:get_pos(), 5, nodes, true)
	if pos then 
		minetest.dig_node(pos)
	end
end)

mapbot.register_bot("place_into_pos", "Automatically place wielditem at specified pos.", "pos", minetest.place_node)

mapbot.register_bot("dig_pos", "Automatically dig node at specified pos.", "pos", minetest.dig_node)

mapbot.register_bot("dig_place_nodes", "Automatically dig specified nodes and immediately place wielditem there.", "nodes", function (nodes)
	local pos = minetest.find_node_near(minetest.localplayer:get_pos(), 5, nodes, true)
	if pos then 
		minetest.dig_node(pos)
		minetest.place_node(pos)
	end
end)

mapbot.register_bot("dig_place_pos", "Automatically dig node at specified pos and immediately place wielditem there.", "pos", function (pos)
	minetest.dig_node(pos)
	minetest.place_node(pos)
end)
