core.register_on_receiving_chat_message(function(message)
	if message:sub(1, 1) == "#" and core.settings:get_bool("ignore_status_messages") ~= false then
		return true
	elseif message:find('\1b@mcl_death_messages\1b') and core.settings:get_bool("mark_deathmessages") ~= false then
		core.display_chat_message(core.colorize("#F25819", "[Deathmessage] ") .. message)
		return true
	end
end)
