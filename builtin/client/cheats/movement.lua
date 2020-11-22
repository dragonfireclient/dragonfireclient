-- autosneak

local autosneak_was_enabled = false

core.register_globalstep(function()
	if core.settings:get_bool("autosneak") then
		core.set_keypress("sneak", true)
		autosneak_was_enabled = true
	elseif autosneak_was_enabled then
		autosneak_was_enabled = false
		core.set_keypress("sneak", false)
	end
end)
 
-- autosprint

local autosprint_was_enabled = false

core.register_globalstep(function()
	if core.settings:get_bool("autosprint") then
		core.set_keypress("special1", true)
		autosprint_was_enabled = true
	elseif autosprint_was_enabled then
		autosprint_was_enabled = false
		core.set_keypress("special1", false)
	end
end)
