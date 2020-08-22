local modname = minetest.get_current_modname()
local modpath = minetest.get_modpath(modname)

dofile(modpath .. "/invhack.lua") 
dofile(modpath .. "/enderchest.lua") 
dofile(modpath .. "/next_item.lua") 
dofile(modpath .. "/autotool.lua") 

minetest.register_on_open_inventory(function(inv)
	print(inv)
end)
