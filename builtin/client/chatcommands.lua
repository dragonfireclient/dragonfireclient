-- Minetest: builtin/client/chatcommands.lua

core.register_on_sending_chat_message(function(message)
	if message:sub(1,2) == ".." then
		return false
	end

	local first_char = message:sub(1,1)
	if first_char == "/" or first_char == "." then
		core.display_chat_message(core.gettext("issued command: ") .. message)
	end

	if first_char ~= "." then
		return false
	end

	local cmd, param = string.match(message, "^%.([^ ]+) *(.*)")
	param = param or ""

	if not cmd then
		core.display_chat_message(core.gettext("-!- Empty command"))
		return true
	end

	-- Run core.registered_on_chatcommand callbacks.
	if core.run_callbacks(core.registered_on_chatcommand, 5, cmd, param) then
		return true
	end

	local cmd_def = core.registered_chatcommands[cmd]
	if cmd_def then
		core.set_last_run_mod(cmd_def.mod_origin)
		local _, result = cmd_def.func(param)
		if result then
			core.display_chat_message(result)
		end
	else
		core.display_chat_message(core.gettext("-!- Invalid command: ") .. cmd)
	end

	return true
end)

function core.run_server_chatcommand(cmd, param)
	core.send_chat_message("/" .. cmd .. " " .. param)
end

core.register_chatcommand("say", {
	description = "Send raw text",
	func = function(text)
		core.send_chat_message(text)
		return true
	end,
})

core.register_chatcommand("teleport", {
	params = "<X>,<Y>,<Z>",
	description = "Teleport to coordinates.",
	func = function(param)
		local success, pos = core.parse_pos(param)
		if success then
			core.localplayer:set_pos(pos)
			return true, "Teleporting to " .. core.pos_to_string(pos)
		end
		return false, pos
	end,
})

core.register_chatcommand("wielded", {
	description = "Print itemstring of wieleded item",
	func = function()
		return true, core.localplayer:get_wielded_item():to_string()
	end
})

core.register_chatcommand("disconnect", {
	description = "Exit to main menu",
	func = function(param)
		core.disconnect()
	end,
})

core.register_chatcommand("players", {
	description = "List online players",
	func = function(param)
		return true, "Online players: " .. table.concat(core.get_player_names(), ", ")
	end
})

core.register_chatcommand("kill", {
	description = "Kill yourself",
	func = function()
		core.send_damage(10000)
	end,
})

core.register_chatcommand("set", {
	params = "([-n] <name> <value>) | <name>",
	description = "Set or read client configuration setting",
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

core.register_chatcommand("place", {
	params = "<X>,<Y>,<Z>",
	description = "Place wielded item",
	func = function(param)
		local success, pos = core.parse_relative_pos(param)
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
		local success, pos = core.parse_relative_pos(param)
		if success then
			core.dig_node(pos)
			return true, "Node at " .. core.pos_to_string(pos) .. " dug"
		end
		return false, pos
	end,
})

core.register_chatcommand("setyaw", {
	params = "<yaw>",
	description = "Set your yaw",
	func = function(param)
		local yaw = tonumber(param)
		if yaw then
			core.localplayer:set_yaw(yaw)
			return true
		else
			return false, "Invalid usage (See .help setyaw)"
		end
	end
})

core.register_chatcommand("setpitch", {
	params = "<pitch>",
	description = "Set your pitch",
	func = function(param)
		local pitch = tonumber(param)
		if pitch then
			core.localplayer:set_pitch(pitch)
			return true
		else
			return false, "Invalid usage (See .help setpitch)"
		end
	end
})

core.register_list_command("xray", "Configure X-Ray", "xray_nodes")
core.register_list_command("search", "Configure NodeESP", "node_esp_nodes")
