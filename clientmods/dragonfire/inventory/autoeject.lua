minetest.register_globalstep(function()
	if minetest.settings:get_bool("autoeject") then
		local player = minetest.localplayer
		local list = (minetest.settings:get("eject_items") or ""):split(",")
		local inventory = minetest.get_inventory("current_player")
		for index, stack in pairs(inventory.main) do
			if table.indexof(list, stack:get_name()) ~= -1 then
				local old_index = player:get_wield_index()
				player:set_wield_index(index - 1)
				minetest.drop_selected_item()
				player:set_wield_index(old_index)
				return
			end
		end
	end
end)

minetest.register_chatcommand("eject", list.new("Configure AutoEject", "eject_items"))
minetest.register_cheat("AutoEject", "Player", "autoeject")
