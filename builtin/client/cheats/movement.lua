local function register_keypress_cheat(cheat, keyname, condition)
	local was_enabled = false
	core.register_globalstep(function()
		local is_active = core.settings:get_bool(cheat)
		local condition_true = (not condition or condition())
		if is_active and condition_true then
			core.set_keypress(keyname, true)
		elseif was_enabled then
			core.set_keypress(keyname, false)
		end
		was_enabled = is_active and condition_true
	end)
end

register_keypress_cheat("autosneak", "sneak", function()
	return core.localplayer:is_touching_ground()
end)
register_keypress_cheat("autosprint", "special1")
