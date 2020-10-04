autoeat = {}

local last_step_eating = false

minetest.register_on_damage_taken(function()
	if not minetest.settings:get_bool("autoeat") then return end
	local player = minetest.localplayer
	player:set_wield_index(0)
	minetest.place_node(player:get_pos())
	autoeat.eating = true
end)

minetest.register_globalstep(function()
	if last_step_eating then
		autoeat.eating, last_step_eating = false, false
	elseif autoeat.eating then
		last_step_eating = true
	end
end)

minetest.register_cheat("AutoEat", "Player", "autoeat")
