perlin = dofile(minetest.get_modpath("perlin") .. "/perlin.lua")

local start, height, stretch

minetest.register_chatcommand("perlin", {
	description = "Start perlin terraforming",
	param = "<height> <stretch>",
	func = function(param)
		local sparam = param:split(" ")
		start, height, stretch = math.floor(minetest.localplayer:get_pos().y), sparam[1], sparam[2]
	end	
})

minetest.register_chatcommand("perlinstop", {
	description = "Abort perlin terraforming",
	func = function(param)
		start, height, stretch = nil
	end	
})

minetest.register_globalstep(function()
	if start then
		local player = minetest.localplayer
		local pos = vector.floor(player:get_pos())
		for x = pos.x - 1, pos.x + 1 do
			for z = pos.z - 1, pos.z + 1 do
				local y = math.floor(start + height * perlin:noise(x / stretch, z / stretch))
				local p = vector.new(x, y, z)
				minetest.place_node(p)
			end
		end
	end 
end)
