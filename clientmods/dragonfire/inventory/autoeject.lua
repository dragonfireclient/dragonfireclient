local old_index

minetest.register_globalstep(function()
	if inventory_mod.nodrop then
		inventory_mod.nodrop = false
		return
	end
	local player = minetest.localplayer
	if old_index then
		player:set_wield_index(old_index)
		minetest.set_keypress("drop", false)
		old_index = nil
	elseif minetest.settings:get_bool("autoeject") then
		local list = (minetest.settings:get("eject_items") or ""):split(",")
		local inventory = minetest.get_inventory("current_player")
		for index, stack in pairs(inventory.main) do
			if table.indexof(list, stack:get_name()) ~= -1 then
				old_index = player:get_wield_index()
				player:set_wield_index(index - 1)
				minetest.set_keypress("drop", true) -- causes to drop tools selected using autotool sometimes, just 
				return
			end
		end
	end
end)

minetest.register_chatcommand("eject", list.new("Configure AutoEject", "eject_items"))
minetest.register_cheat("AutoEject", "Player", "autoeject")
