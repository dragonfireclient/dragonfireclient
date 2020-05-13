-- CSM death formspec. Only used when clientside modding is enabled, otherwise
-- handled by the engine.

local dead = false

core.register_on_death(function()
	if not dead then
		core.display_chat_message("You died.")
		local formspec = "size[11,5.5]bgcolor[#320000b4;true]" ..
			"label[4.85,1.35;" .. fgettext("You died") ..
			"]button_exit[4,3;3,0.5;btn_respawn;".. fgettext("Respawn") .."]"
		core.show_formspec("bultin:death", formspec)
		dead = true
	end
end)

core.register_on_formspec_input(function(formname, fields)
	if formname == "bultin:death" and fields.btn_respawn then
		core.send_respawn()
		dead = false
	end
end)

core.register_chatcommand("respawn", {
	func = function()
		core.send_respawn()
		dead = false
	end
})
