local autosneak_was_enabled = false
local autosneak_ground_was_enabled = false
local autosprint_was_enabled = false

core.register_globalstep(function()
-- autosneak
	if core.settings:get_bool("autosneak") then
		core.set_keypress("sneak", true)
		autosneak_was_enabled = true
	elseif autosneak_was_enabled then
		autosneak_was_enabled = false
		core.set_keypress("sneak", false)
	end
-- autosneak_ground
	if core.settings:get_bool("autosneak_ground") and core.localplayer:is_touching_ground() then
			core.set_keypress("sneak", true)
			autosneak_ground_was_enabled = true
	elseif autosneak_ground_was_enabled then
		autosneak_ground_was_enabled = false
		core.set_keypress("sneak", false)
	end
-- autosprint
    if core.settings:get_bool("autosprint") then
        core.set_keypress("special1", true)
        autosprint_was_enabled = true
    elseif autosprint_was_enabled then
        core.set_keypress("special1", false)
        autosprint_was_enabled = false
    end
end)
