
local autosneak_was_enabled = false
local autosneak_conditional_was_enabled = false
local autosprint was enabled = false
local ign_srv_spd_was_enabled = false
core.register_globalstep(function()
-- autosneak
	if core.settings:get_bool("autosneak") then
		core.set_keypress("sneak", true)
		autosneak_was_enabled = true
	elseif autosneak_was_enabled then
		autosneak_was_enabled = false
		core.set_keypress("sneak", false)
	end

        if minetest.settings:get_bool("autosneak_conditional") then
		if minetest.localplayer:is_touching_ground() then
			minetest.set_keypress("sneak", true)
			autosprint_conditional_was_enabled = true
		end
	elseif autosprint_conditional_was_enabled then
		autosprint_conditional_was_enabled = false
		minetest.set_keypress("sneak", false)
	end
--autosprint
    	if minetest.settings:get_bool("autosprint") or (minetest.settings:get_bool("continuous_forward") and minetest.settings:get_bool("autofsprint")) then
        	core.set_keypress("special1", true)
        	sprint_was_enabled = true
	elseif sprint_was_enabled then
        	core.set_keypress("special1", false)
        	sprint_was_enabled = false
    	end
--ignore server sent speed
	if minetest.localplayer and minetest.settings:get_bool("movement_ignore_server_speed") then
        	minetest.localplayer:set_speeds_from_local_settings()
	        ign_srv_spd_was_enabled=true
	elseif ign_srv_spd_was_enabled then
        	ign_srv_spd_was_enabled=false
        	minetest.localplayer:set_speeds_from_server_settings()
	end
end)
 
