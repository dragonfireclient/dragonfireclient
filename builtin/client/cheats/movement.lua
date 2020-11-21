-- autosneak

local autosneak_was_enabled = false
local autosneak_conditional_was_enabled = false
local autosprint was enabled

core.register_globalstep(function()
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

    	if minetest.settings:get_bool("autosprint") or (minetest.settings:get_bool("continuous_forward") and minetest.settings:get_bool("autofsprint")) then
        	core.set_keypress("special1", true)
        	sprint_was_enabled = true
	elseif sprint_was_enabled then
        	core.set_keypress("special1", false)
        	sprint_was_enabled = false
    	end

end)
 
