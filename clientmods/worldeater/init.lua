local x, y, z = 0, 0, 0

function loop()
	local nx, ny, nz = x + 100, y + 100, z + 100
end

minetest.register_on_connect(loop)
