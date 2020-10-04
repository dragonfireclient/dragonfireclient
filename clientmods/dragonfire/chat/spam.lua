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
