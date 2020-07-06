function core.parse_pos(param)
	local p = {}
	p.x, p.y, p.z = string.match(param, "^([~|%d.-]+)[, ] *([~|%d.-]+)[, ] *([~|%d.-]+)$")
	for k, v in pairs(p) do
		if p[k] == "~" then
			p[k] = core.localplayer:get_pos()[k]
		else
			p[k] = tonumber(v)
		end
	end
	if p.x and p.y and p.z then
		local lm = 31000
		if p.x < -lm or p.x > lm or p.y < -lm or p.y > lm or p.z < -lm or p.z > lm then
			return false, "Position out of Map bounds."
		end
		return true, p
	end
	return false, "Invalid position (" .. param .. ")"
end 
