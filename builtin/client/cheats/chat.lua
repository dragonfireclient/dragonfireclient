core.register_on_receiving_chat_message(function(message)
	if message:sub(1, 1) == "#" and core.settings:get_bool("ignore_status_messages") ~= false then
		return true
	elseif message:find('\1b@mcl_death_messages\1b') and core.settings:get_bool("mark_deathmessages") ~= false then
		core.display_chat_message(core.colorize("#F25819", "[Deathmessage] ") .. message)
		return true
	end
end)

function core.send_colorized(message)
	local starts_with = message:sub(1, 1)
	
	if starts_with == "/" or starts_with == "." then return end

	local reverse = core.settings:get_bool("chat_reverse")
	
	if reverse then
		local msg = ""
		for i = 1, #message do
			msg = message:sub(i, i) .. msg
		end
		message = msg
	end
	
	local use_chat_color = core.settings:get("use_chat_color")
	local color = core.settings:get("chat_color")

	if color then
		local msg
		if color == "rainbow" then
			msg = core.rainbow(message)
		else
			msg = core.colorize(color, message)
		end
		message = msg
	end
	
	core.send_chat_message(message)
	return true
end

core.register_on_sending_chat_message(core.send_colorized)
 
