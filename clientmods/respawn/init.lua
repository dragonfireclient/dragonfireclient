local warp = warp or {set_here = function() return false end}

local formspec = ""
	.. "size[11,5.5]"
	.. "bgcolor[#320000b4;true]"
	.. "label[4.85,1.35;" .. "You died" .. "]"
	.. "button_exit[2,3;3,0.5;btn_respawn;" .. "Respawn" .. "]"
	.. "button_exit[6,3;3,0.5;btn_ghost_mode;" .. "Ghost Mode" .. "]"
	.. "set_focus[btn_respawn;true]"

minetest.register_on_death(function()
	local warp_success, warp_msg = warp.set_here("death")
	if warp_success then
		minetest.display_chat_message(warp_msg)
	else
		minetest.display_chat_message("You died at " .. minetest.pos_to_string(minetest.localplayer:get_pos()) .. ".")
	end
	if minetest.settings:get_bool("autorespawn") then
		minetest.send_respawn()
	else
		minetest.show_formspec("respawn:death", formspec)
	end
end)

minetest.register_on_formspec_input(function(formname, fields)
	if formname == "respawn:death" then
		if fields.btn_ghost_mode then
			minetest.display_chat_message("You are in ghost mode. Use .respawn to Respawn.")
		else
			minetest.send_respawn()
		end
	end
end)

minetest.register_chatcommand("respawn", {
	description = "Respawn when in ghost mode",
	func = function()
		if minetest.localplayer:get_hp() == 0 then
			minetest.send_respawn()
			minetest.display_chat_message("Respawned.")
		else
			minetest.display_chat_message("You are not in ghost mode.")
		end
	end
})
