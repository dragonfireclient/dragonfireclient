local function loop()
	local item = minetest.get_wielded_item():get_name()
	local pos = minetest.find_node_near(minetest.localplayer:get_pos(), 5, "mcl_farming:wheat", true)
	if item == "mcl_farming:wheat_seeds" and pos then
		minetest.dig_node(pos)
		minetest.place_node(pos)
	end
	minetest.after(0.1, loop)
end

minetest.after(0.1, loop)
