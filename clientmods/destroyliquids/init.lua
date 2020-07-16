minetest.override_item("air", {liquids_pointable = true}) 
local destroy_water = false

local function loop()
	if destroy_water then
		local pos = minetest.find_node_near(minetest.localplayer:get_pos(), 5, "mcl_core:water_source", true)
		if pos then
			minetest.place_node(pos)
		end
	end
	minetest.after(0, loop)
end

minetest.after(1, loop)

minetest.register_chatcommand("destroywater", {
	param = "true|false",
	description = "Turn destroy water on/off",
	func = function(param)
		destroy_water = minetest.is_yes(param)
	end
})
