core.register_chatcommand("place", {
	params = "<X>,<Y>,<Z>",
	description = "Place wielded item",
	func = function(param)
		local success, pos = core.parse_pos(param)
		if success then
			core.place_node(pos)
			return true, "Node placed at " .. core.pos_to_string(pos)
		end
		return false, pos
	end,
})

core.register_chatcommand("dig", {
	params = "<X>,<Y>,<Z>",
	description = "Dig node",
	func = function(param)
		local success, pos = core.parse_pos(param)
		if success then
			core.dig_node(pos)
			return true, "Node at " .. core.pos_to_string(pos) .. " dug"
		end
		return false, pos
	end,
})

core.register_chatcommand("kill", {
	description = "Kill yourself",
	func = function(param)
		core.send_damage(core.localplayer:get_hp())
	end,
})

core.register_chatcommand("scan", {
	description = "Scan for one or multible nodes in a radius around you",
	param = "<radius> node1[,node2...]",
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

local function teleport(param)
	local success, pos = core.parse_pos(param)
	if success then
		core.localplayer:set_pos(pos)
		return true, "Teleporting to " .. core.pos_to_string(pos)
	end
	return false, pos
end

core.register_chatcommand("teleport", {
	params = "<X>,<Y>,<Z>",
	description = "Teleport to position",
	func = function(param)
		return teleport(param)
	end,
})

core.register_chatcommand("tpoff", {
	params = "<X>,<Y>,<Z>",
	description = "Teleport to position and log out immediately",
	func = function(param)
		teleport(param)
		minetest.disconnect()
	end,
})

minetest.register_chatcommand("wielded", {
	description = "Print itemstring of wieleded item",
	func = function()
		return true, minetest.get_wielded_item():get_name()
	end
})
