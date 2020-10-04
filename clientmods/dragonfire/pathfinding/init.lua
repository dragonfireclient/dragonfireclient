local positions, index, global_goal

local function roundvec(v, d)
	return vector.divide(vector.round(vector.multiply(v, d)), d)
end

local function findpath(pos)
	global_goal = pos
	index = 2
	positions = minetest.find_path(
		minetest.localplayer:get_pos(),
		pos,
		tonumber(minetest.settings:get("goto_max_distance") or 25),
		tonumber(minetest.settings:get("goto_max_jump") or 1),
		tonumber(minetest.settings:get("goto_max_drop") or minetest.settings:get_bool("prevent_natural_damage") and 1000 or 5)
	)
end

minetest.register_chatcommand("goto", {
	description = "Go to a position (use pathfinding).",
	param = "<pos>",
	func = function(param)
		if positions then
			return false, "Goto is still active. Use .gotoabort to abort it."
		end
		local success, pos = minetest.parse_pos(param)
		if not success then
			return false, pos
		end
		findpath(pos)
	end,
})

minetest.register_chatcommand("gotoabort", {
	description = "Abort goto.",
	param = "<pos>",
	func = function(param)
		if not positions then
			return false, "Goto is currently not running (and also not walking haha)"
		end
		minetest.set_keypress("forward", false)
		minetest.set_keypress("sneak", false)
		positions, index, global_goal = nil
		return true, "Aborted."
	end,
})

minetest.register_globalstep(function(dtime)
	if positions then
		minetest.set_keypress("forward", true)
		minetest.set_keypress("sneak", false)
		local player = minetest.localplayer
		local pos = player:get_pos()
		local goal, next_goal = positions[index], positions[index+1]
		if not goal then
			positions, index, global_goal = nil
			minetest.set_keypress("forward", false)
			minetest.display_chat_message("Reached goal.")
			return
		end
		if next_goal then
			local d, dn = vector.subtract(pos, goal), vector.subtract(next_goal, goal)
			for k, v in pairs(dn) do
				if v ~= 0 and k ~= "y" then
					local cv = d[k]
					if v > 0 and cv > 0 or v < 0 and cv < 0 then
						index = index + 1
						goal = next_goal
					end
					break
				end	
			end
		end
		local npos = vector.add(goal, {x = 0, y = 1, z = 0})
		local node =  minetest.get_node_or_nil(npos)
		if node and node.name ~= air then
			minetest.dig_node(npos)
		end
		local velocity = player:get_velocity()
		velocity.y = 0
		if vector.length(velocity) < 0.1 then
			findpath(global_goal)
			return
		end
		local distance = vector.distance(pos, goal)
		if not next_goal and distance < 1 then
			index = index + 1
		end
		local direction = vector.direction(pos, vector.new(goal.x, 0, goal.z))
		local yaw = player:get_yaw() % 360
		local goal_yaw = math.deg(math.atan2(-direction.x, direction.z)) % 360
		local diff = math.abs(goal_yaw - yaw)
		if diff > 175 and diff < 185 and distance < 1 then
			index = index + 1
		elseif diff > 10 and diff < 350 then
			if yaw < goal_yaw and diff < 180 or yaw > goal_yaw and diff > 180 then
				yaw = yaw + 10
			elseif yaw < goal_yaw and diff > 180 or yaw > goal_yaw and diff < 180 then
				yaw = yaw - 10
			end
			if diff >= 90 and diff <= 270 then
				minetest.set_keypress("sneak", true)
			end
			player:set_yaw(yaw)
		else
			player:set_yaw(goal_yaw)
		end
	end
end)
