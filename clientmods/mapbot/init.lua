mapbot = {}

local modname = minetest.get_modname()
local modpath = minetest.get_modpath(modname)
mapbot.storage = minetest.get_mod_storage()

dofile(modpath .. "/api.lua")
dofile(modpath .. "/simple_bots.lua")


