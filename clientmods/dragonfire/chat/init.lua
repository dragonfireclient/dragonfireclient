chat = {}

local modname = minetest.get_current_modname()
local modpath = minetest.get_modpath(modname)

chat.rainbow = dofile(modpath .. "/rainbow.lua")

dofile(modpath .. "/colors.lua")
dofile(modpath .. "/spam.lua")
dofile(modpath .. "/status.lua")
dofile(modpath .. "/leak.lua")


