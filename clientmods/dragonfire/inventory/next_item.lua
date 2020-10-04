local elapsed_time = 0
local tick_time = 0.05

minetest.register_globalstep(function(dtime)
	elapsed_time = elapsed_time + dtime
	if elapsed_time < tick_time then return end
	local player = minetest.localplayer
	if not player then return end
	local item = player:get_wielded_item()
	if item:get_count() == 0 and minetest.settings:get_bool("next_item") then
		local index = player:get_wield_index()
		player:set_wield_index(index + 1)
	end
	elapsed_time = 0
end)

minetest.register_cheat("NextItem", "Player", "next_item")

