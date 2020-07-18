mapbot.bots = {}

mapbot.paramtypes = {
	["pos"] = {
		"<X>,<Y>,<Z>",
		function (param)
			local _, pos = minetest.parse_relative_pos(param)
			return pos
		end
	},
	["nodes"] = {
		"<node1> [<node2>] ...",
		function (param)
			return param:split(" ")
		end
	},
}

function mapbot.register_bot(name, description, paramtype, func)
	local pt = mapbot.paramtypes[paramtype]
	if not pt then return end
	minetest.register_chatcommand(name, {
		param = pt[1],
		description = description .. " Empty parameter to stop.",
		func = function(param)
			mapbot.storage:set_string(name, param)
			return true, "Changed " .. name .. " config."
		end
	})
	table.insert(mapbot.bots, {name, pt, func})
end
 
function mapbot.loop()
	for _, bot in pairs(mapbot.bots) do
		local param = mapbot.storage:get_string(bot[1])
		param = (param == "") and nil or bot[2][2](param)
		if param and bot[3](param) end
	end
end

minetest.register_on_connect(mapbot.loop)
