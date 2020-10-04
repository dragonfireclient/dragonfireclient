minetest.register_on_receiving_chat_message(function(message)
	if message:sub(1, 1) == "#" and minetest.settings:get_bool("ignore_status_messages") ~= false then
		return true
	end
end) 
