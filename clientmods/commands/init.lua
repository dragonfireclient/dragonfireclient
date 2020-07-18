minetest.register_chatcommand("say", {
	description = "Send raw text",
	func = function(text)
		minetest.send_chat_message(text)
		return true
	end,
})

minetest.register_chatcommand("teleport", {
	params = "<X>,<Y>,<Z>",
	description = "Teleport to relative coordinates. " .. (core.anticheat_protection and "Only works for short distances." or ""),
	func = function(param)
		local success, pos = minetest.parse_relative_pos(param)
		if success then
			minetest.localplayer:set_pos(pos)
			return true, "Teleporting to " .. minetest.pos_to_string(pos)
		end
		return false, pos
	end,
})

minetest.register_chatcommand("wielded", {
	description = "Print itemstring of wieleded item",
	func = function()
		return true, minetest.get_wielded_item():get_name()
	end
})

minetest.register_chatcommand("disconnect", {
	description = "Exit to main menu",
	func = function(param)
		minetest.disconnect()
	end,
})

minetest.register_chatcommand("players", {
	description = "List online players",
	func = function(param)
		return true, "Online players: " .. table.concat(minetest.get_player_names(), ", ")
	end
})

minetest.register_chatcommand("kill", {
	description = "Kill yourself",
	func = function()
		minetest.send_damage(minetest.localplayer:get_hp())
	end,
})

minetest.register_chatcommand("set", {
	params = "([-n] <name> <value>) | <name>",
	description = "Set or read client configuration setting",
	func = function(param)
		local arg, setname, setvalue = string.match(param, "(-[n]) ([^ ]+) (.+)")
		if arg and arg == "-n" and setname and setvalue then
			minetest.settings:set(setname, setvalue)
			return true, setname .. " = " .. setvalue
		end

		setname, setvalue = string.match(param, "([^ ]+) (.+)")
		if setname and setvalue then
			if not minetest.settings:get(setname) then
				return false, "Failed. Use '.set -n <name> <value>' to create a new setting."
			end
			minetest.settings:set(setname, setvalue)
			return true, setname .. " = " .. setvalue
		end

		setname = string.match(param, "([^ ]+)")
		if setname then
			setvalue = minetest.settings:get(setname)
			if not setvalue then
				setvalue = "<not set>"
			end
			return true, setname .. " = " .. setvalue
		end

		return false, "Invalid parameters (see .help set)."
	end,
})
 
