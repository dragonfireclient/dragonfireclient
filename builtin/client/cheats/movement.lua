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
 
