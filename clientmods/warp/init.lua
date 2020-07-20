warp = {}

local storage = minetest.get_mod_storage()

function warp.set(warp, pos)
	if warp == "" or not pos then return false, "Missing parameter." end
	local posstr = minetest.pos_to_string(pos)
	storage:set_string(warp, posstr)
	return true, "Warp " .. warp .. " set to " .. posstr .. "."
end

function warp.set_here(param)
	local success, message = warp.set(param, vector.round(minetest.localplayer:get_pos()))
	return success, message
end

function warp.get(param)
	if param == "" then return false, "Missing parameter." end
	local pos = storage:get_string(param)
	if pos == "" then return false, "Warp " .. param .. " not set." end
	return true, "Warp " .. param .. " is set to " .. pos .. ".", minetest.string_to_pos(pos)
end

function warp.delete(param)
	if param == "" then return false, "Missing parameter." end
	storage:set_string(param, "")
	return true, "Deleted warp " .. param .. "."
end

minetest.register_chatcommand("setwarp", {
	params = "<warp>",
	description = "Set a warp to your current position.",
	func = warp.set_here,
})

minetest.register_chatcommand("readwarp", {
	params = "<warp>",
	description = "Print the coordinates of a warp.",
	func = warp.get,
})

minetest.register_chatcommand("deletewarp", {
	params = "<warp>",
	description = "Delete a warp.",
	func = warp.delete,
})

local function do_warp(param)
	if param == "" then return false, "Missing parameter." end
	local success, pos = minetest.parse_pos(param)
	if not success then
		local msg
		success, msg, pos = warp.get(param)
		if not success then
			return false, msg
		end
	end
	minetest.localplayer:set_pos(pos)
	return true, "Warped to " .. minetest.pos_to_string(pos)
end

minetest.register_chatcommand("warp", {
	params = "<pos>|<warp>",
	description = "Warp to a set warp or a position.",
	func = do_warp
})

minetest.register_chatcommand("warpandexit", {
	params = "<pos>|<warp>",
	description = "Warp to a set warp or a position and exit.",
	func = function(param)
		local s, m = do_warp(param)
		if s then
			minetest.disconnect()
		end
		return s,m 
	end
})
