chat = {}

chat.rainbow = dofile(minetest.get_modpath("chat") .. "/rainbow.lua")

function chat.send(message)
	local starts_with = message:sub(1, 1)
	
	if starts_with == "/" or starts_with == "." then return end

	local reverse = minetest.settings:get_bool("chat_reverse")
	
	if reverse then
		local msg = ""
		for i = 1, #message do
			msg = message:sub(i, i) .. msg
		end
		message = msg
	end
	
	local color = minetest.settings:get("chat_color")

	if color then
		local msg
		if color == "rainbow" then
			msg = chat.rainbow(message)
		else
			msg = minetest.colorize(color, message)
		end
		message = msg
	end
	
	minetest.send_chat_message(message)
	return true
end

minetest.register_on_sending_chat_message(chat.send)

local etime = 0

minetest.register_globalstep(function(dtime)
	etime = etime + dtime
	if etime < 10/8 then return end
	etime = 0
	local spam = minetest.settings:get("chat_spam")
	local enable_spam = minetest.settings:get("chat_enable_spam")
	if enable_spam and spam then
		local _ = chat.send(spam) or minetest.send_chat_message(spam)
	end
end)
