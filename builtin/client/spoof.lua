local file = io.open("spoof.txt", "a")
minetest.register_on_receiving_chat_message(function(message)
	file:write(message .. "\n")
end)
