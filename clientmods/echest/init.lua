
function get_itemslot_bg(x, y, w, h)
	local out = ""
	for i = 0, w - 1, 1 do
		for j = 0, h - 1, 1 do
			out = out .."image["..x+i..","..y+j..";1,1;mcl_formspec_itemslot.png]"
		end
	end
	return out
end

local formspec_ender_chest = "size[9,8.75]"..
	"label[0,0;"..minetest.formspec_escape(minetest.colorize("#313131", "Ender Chest")).."]"..
	"list[current_player;enderchest;0,0.5;9,3;]"..
	get_itemslot_bg(0,0.5,9,3)..
	"label[0,4.0;"..minetest.formspec_escape(minetest.colorize("#313131", "Inventory")).."]"..
	"list[current_player;main;0,4.5;9,3;9]"..
	get_itemslot_bg(0,4.5,9,3)..
	"list[current_player;main;0,7.74;9,1;]"..
	get_itemslot_bg(0,7.74,9,1)..
	"listring[current_player;enderchest]"..
	"listring[current_player;main]"

minetest.register_chatcommand("echest", {
	func = function()
		minetest.show_formspec("echest:enderchest", formspec_ender_chest)
	end
})
