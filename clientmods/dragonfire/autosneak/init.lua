local was_enabled = false

minetest.register_globalstep(function()
	if minetest.settings:get_bool("autosneak") then
		minetest.set_keypress("sneak", true)
		was_enabled = true
	elseif was_enabled then
		was_enabled = false
		minetest.set_keypress("sneak", false)
	end
end)

minetest.register_cheat("AutoSneak", "Movement", "autosneak")
