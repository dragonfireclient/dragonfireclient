minetest.register_chatcommand("findnodes", {
	description = "Scan for one or multible nodes in a radius around you",
	param = "<radius> <node1>[,<node2>...]",
	func = function(param)
		local radius = tonumber(param:split(" ")[1])
		local nodes = param:split(" ")[2]:split(",")
		local pos = core.localplayer:get_pos()
		local fpos = core.find_node_near(pos, radius, nodes, true)
		if fpos then
			return true, "Found " .. table.concat(nodes, " or ") .. " at " .. core.pos_to_string(fpos)
		end
		return false, "None of " .. table.concat(nodes, " or ") .. " found in a radius of " .. tostring(radius)
	end,
}) 

minetest.register_chatcommand("place", {
	params = "<X>,<Y>,<Z>",
	description = "Place wielded item",
	func = function(param)
		local success, pos = minetest.parse_relative_pos(param)
		if success then
			minetest.place_node(pos)
			return true, "Node placed at " .. minetest.pos_to_string(pos)
		end
		return false, pos
	end,
})

minetest.register_chatcommand("dig", {
	params = "<X>,<Y>,<Z>",
	description = "Dig node",
	func = function(param)
		local success, pos = minetest.parse_relative_pos(param)
		if success then
			minetest.dig_node(pos)
			return true, "Node at " .. minetest.pos_to_string(pos) .. " dug"
		end
		return false, pos
	end,
})
 
 
