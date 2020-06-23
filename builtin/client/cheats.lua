core.register_chatcommand("set", {
	params = "([-n] <name> <value>) | <name>",
	description = "Set or read client configuration setting",
	privs = {server=true},
	func = function(param)
		local arg, setname, setvalue = string.match(param, "(-[n]) ([^ ]+) (.+)")
		if arg and arg == "-n" and setname and setvalue then
			core.settings:set(setname, setvalue)
			return true, setname .. " = " .. setvalue
		end

		setname, setvalue = string.match(param, "([^ ]+) (.+)")
		if setname and setvalue then
			if not core.settings:get(setname) then
				return false, "Failed. Use '.set -n <name> <value>' to create a new setting."
			end
			core.settings:set(setname, setvalue)
			return true, setname .. " = " .. setvalue
		end

		setname = string.match(param, "([^ ]+)")
		if setname then
			setvalue = core.settings:get(setname)
			if not setvalue then
				setvalue = "<not set>"
			end
			return true, setname .. " = " .. setvalue
		end

		return false, "Invalid parameters (see .help set)."
	end,
})

function core.parse_pos(param)
	local p = {}
	p.x, p.y, p.z = string.match(param, "^([~|%d.-]+)[, ] *([~|%d.-]+)[, ] *([~|%d.-]+)$")
	for k, v in pairs(p) do
		if p[k] == "~" then
			p[k] = core.localplayer:get_pos()[k]
		else
			p[k] = tonumber(v)
		end
	end
	if p.x and p.y and p.z then
		local lm = 31000
		if p.x < -lm or p.x > lm or p.y < -lm or p.y > lm or p.z < -lm or p.z > lm then
			return false, "Position out of Map bounds."
		end
		return true, p
	end
	return false, "Invalid position (" .. param .. ")"
end

core.register_chatcommand("teleport", {
	params = "<X>,<Y>,<Z>",
	description = "Teleport to position",
	func = function(param)
		local success, pos = core.parse_pos(param)
		if success then
			core.localplayer:set_pos(pos)
			return true, "Teleporting to " .. core.pos_to_string(pos)
		end
		return false, pos
	end,
})

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

core.register_chatcommand("digaround", {
	description = "Scan for one or multible nodes in a radius around you",
	param = "<radius> node1[,node2...]",
	func = function(param)
		local radius = tonumber(param:split(" ")[1])
		local nodes = param:split(" ")[2]:split(",")
		local function loop()
			local fpos = core.find_node_near(core.localplayer:get_pos(), radius, nodes, true)
			if fpos then core.dig_node(fpos) end
			core.after(0, loop)
		end
		loop()
	end,
})

local keep_digging = false

core.register_chatcommand("keepdigging", {
	params = "<X>,<Y>,<Z>",
	description = "Dig node again and again",
	func = function(param)
		local success, pos = core.parse_pos(param)
		if success then
			keep_digging = true
			local function loop()
				core.dig_node(pos)
				if keep_digging then
					core.after(0.1, loop)
				end
			end
			loop()
		end
	end,
})

core.register_chatcommand("stopdigging", {
	description = "Stop diggin",
	func = function()
		keep_digging = false
	end,
})

core.register_on_punchnode(function(pos)
	--core.dig_node(pos)
end)

