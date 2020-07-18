local build = {}

local function build_y(callback)
	build.pos.y = build.pos.y - build.step.y
	local function step()
		build.pos.y = build.pos.y + build.step.y
		minetest.after(0.25, (build.pos.y == build.goal.y) and callback or step)
		minetest.place_node(build.pos)
		local player_pos = minetest.find_node_near(build.pos, 2, "air")
		if player_pos then
			minetest.localplayer:set_pos(player_pos)
		end
	end
	minetest.after(0.25, step)
end

local function build_z(callback)
	build.pos.z = build.pos.z - build.step.z
	local function step()
		build.start.y, build.goal.y = build.goal.y, build.start.y
		build.step.y = (build.goal.y > build.pos.y) and 1 or -1
		build.pos.z = build.pos.z + build.step.z
		build_y((build.pos.z == build.goal.z) and callback or step)
	end
	minetest.after(0.25, step)
end

local function build_x(callback)
	build.pos.x = build.pos.x - build.step.x
	local function step()
		build.start.z, build.goal.z = build.goal.z, build.start.z
		build.step.z = (build.goal.z > build.pos.z) and 1 or -1
		build.pos.x = build.pos.x + build.step.x
		build_z((build.pos.x == build.goal.x) and callback or step)
	end
	minetest.after(0.25, step)
end

minetest.register_chatcommand("build", {
	func = function(param)
		local sucess
		build.start = vector.round(minetest.localplayer:get_pos())
		build.pos = vector.new(build.start)
		success, build.goal = minetest.parse_relative_pos(param)
		if success then
			build.step = {}
			build.step.x = (build.goal.x > build.start.x) and 1 or -1
			build.start.z, build.goal.z = build.goal.z, build.start.z
			build.start.y, build.goal.y = build.goal.y, build.start.y
			build_x(function() minetest.display_chat_message("Done.") end)
		end
		return false, build.goal
	end
})


 
