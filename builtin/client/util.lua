function core.parse_pos(param)
	local p = {}
	local playerpos = core.localplayer:get_pos()
	p.x, p.y, p.z = string.match(param, "^([~|%d.-]+)[, ] *([~|%d.-]+)[, ] *([~|%d.-]+)$")
	for k, v in pairs(p) do
		if p[k] == "~" then
			p[k] = playerpos[k]
		else
			p[k] = tonumber(v)
		end
	end
	if p.x and p.y and p.z then
		return true, vector.round(p)
	end
	return false, "Invalid position (" .. param .. ")"
end

function core.parse_relative_pos(param)
	local success, pos = core.parse_pos(param:gsub("~", "0"))
	if success then pos = vector.round(vector.add(core.localplayer:get_pos(), pos)) end
	return success, pos
end

function core.find_item(item, mini, maxi)
	for index, stack in ipairs(core.get_inventory("current_player").main) do
		if (not mini or index >= mini) and (not maxi or index <= maxi) and stack:get_name() == item then
			return index
		end
	end
end


local function to_hotbar(it)
    local tpos=nil
    local hotbar_slot = 8
    local plinv = minetest.get_inventory("current_player")
    for i, v in ipairs(plinv.main) do
        if i<10 and v:is_empty() then
            tpos = i
            break
        end
    end
    if tpos == nil then tpos=hotbar_slot end
	local mv = InventoryAction("move")
	mv:from("current_player", "main", it)
	mv:to("current_player", "main", tpos)
	mv:apply()
    return tpos
end

function core.switch_to_item(itname)
    if not minetest.localplayer then return false end
    local plinv = minetest.get_inventory("current_player")
    for i, v in ipairs(plinv.main) do -- check if already in hotbar
        if i<10 and v:get_name() == itname then
            minetest.localplayer:set_wield_index(i)
            return true
        end
    end
    local pos = minetest.find_item(itname) -- otherwise find in inv
    if pos then
        minetest.localplayer:set_wield_index(to_hotbar(pos))
        return true
    end
    return false
end

function core.get_pointed_thing()
	local pos = core.camera:get_pos()
	local pos2 = vector.add(pos, vector.multiply(core.camera:get_look_dir(), 7))
	local player = core.localplayer
	if not player then return end
	local item = player:get_wielded_item()
	if not item then return end
	local def = core.get_item_def(item:get_name())
	local ray = core.raycast(pos, pos2, true, core.settings:get_bool("point_liquids") or def and def.liquids_pointable)
	return ray and ray:next()
end

function core.close_formspec(formname)
	return core.show_formspec(formname, "")
end

function core.get_nearby_objects(radius)
	return core.get_objects_inside_radius(core.localplayer:get_pos(), radius)
end

-- HTTP callback interface

function core.http_add_fetch(httpenv)
	httpenv.fetch = function(req, callback)
		local handle = httpenv.fetch_async(req)

		local function update_http_status()
			local res = httpenv.fetch_async_get(handle)
			if res.completed then
				callback(res)
			else
				core.after(0, update_http_status)
			end
		end
		core.after(0, update_http_status)
	end

	return httpenv
end
