inventory_mod = {}

local modname = minetest.get_current_modname()
local modpath = minetest.get_modpath(modname)

dofile(modpath .. "/invhack.lua") 
dofile(modpath .. "/enderchest.lua")
dofile(modpath .. "/hand.lua")
dofile(modpath .. "/next_item.lua")
dofile(modpath .. "/autotool.lua") 
dofile(modpath .. "/autoeject.lua")
