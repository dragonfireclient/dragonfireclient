local death_formspec = ""
	.. "size[11,5.5]"
	.. "bgcolor[#320000b4;true]"
	.. "label[4.85,1.35;" .. "You died" .. "]"
	.. "button_exit[2,3;3,0.5;btn_respawn;" .. "Respawn" .. "]"
	.. "button_exit[6,3;3,0.5;btn_ghost_mode;" .. "Ghost Mode" .. "]"
	.. "set_focus[btn_respawn;true]"

core.register_on_death(function()
	core.display_chat_message("You died at " .. core.pos_to_string(vector.round(core.localplayer:get_pos())) .. ".")
	if core.settings:get_bool("autorespawn") then
		core.send_respawn()
	else
		core.show_formspec("__builtin__:death", death_formspec)
	end
end)

core.register_on_formspec_input(function(formname, fields)
	if formname == "__builtin__:death" then
		if fields.btn_ghost_mode then
			core.display_chat_message("You are in ghost mode. Use .respawn to Respawn.")
		else
			core.send_respawn()
		end
	end
end)

core.register_chatcommand("respawn", {
	description = "Respawn when in ghost mode",
	func = function()
		if core.localplayer:get_hp() == 0 then
			core.send_respawn()
			core.display_chat_message("Respawned.")
		else
			core.display_chat_message("You are not in ghost mode.")
		end
	end
})
