local function register_keypress_cheat(cheat, keyname)
	local was_enabled = false
	core.register_globalstep(function()
		if core.settings:get_bool(cheat) then
			was_enabled = true
			core.set_keypress(keyname, true)
		elseif was_enabled then
			was_enabled = false
			core.set_keypress(keyname, false)
		end
	end)
end

register_keypress_cheat("autosneak", "sneak")
register_keypress_cheat("autosprint", "special1")
