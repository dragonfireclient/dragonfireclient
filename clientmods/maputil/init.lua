local modname = minetest.get_current_modname()
local modpath = minetest.get_modpath(modname)

dofile(modpath .. "/commands.lua")
dofile(modpath .. "/buildbot.lua")
