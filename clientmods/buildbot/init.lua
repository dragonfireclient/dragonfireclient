buildbot = {}

local function build_y(callback)
	buildbot.pos.y = buildbot.pos.y - buildbot.step.y
	local function step()
		buildbot.pos.y = buildbot.pos.y + buildbot.step.y
		minetest.after(0.25, (buildbot.pos.y == buildbot.goal.y) and callback or step)
		minetest.place_node(buildbot.pos)
		local player_pos = minetest.find_node_near(buildbot.pos, 2, "air")
		if player_pos then
			minetest.localplayer:set_pos(player_pos)
		end
	end
	minetest.after(0.25, step)
end

local function build_z(callback)
	buildbot.pos.z = buildbot.pos.z - buildbot.step.z
	local function step()
		buildbot.start.y, buildbot.goal.y = buildbot.goal.y, buildbot.start.y
		buildbot.step.y = (buildbot.goal.y > buildbot.pos.y) and 1 or -1
		buildbot.pos.z = buildbot.pos.z + buildbot.step.z
		build_y((buildbot.pos.z == buildbot.goal.z) and callback or step)
	end
	minetest.after(0.25, step)
end

local function build_x(callback)
	buildbot.pos.x = buildbot.pos.x - buildbot.step.x
	local function step()
		buildbot.start.z, buildbot.goal.z = buildbot.goal.z, buildbot.start.z
		buildbot.step.z = (buildbot.goal.z > buildbot.pos.z) and 1 or -1
		buildbot.pos.x = buildbot.pos.x + buildbot.step.x
		build_z((buildbot.pos.x == buildbot.goal.x) and callback or step)
	end
	minetest.after(0.25, step)
end

minetest.register_chatcommand("build", {
	func = function(param)
		local sucess
		buildbot.start = vector.round(minetest.localplayer:get_pos())
		buildbot.pos = vector.new(buildbot.start)
		success, buildbot.goal = minetest.parse_pos(param)
		if success then
			buildbot.step = {}
			buildbot.step.x = (buildbot.goal.x > buildbot.start.x) and 1 or -1
			buildbot.start.z, buildbot.goal.z = buildbot.goal.z, buildbot.start.z
			buildbot.start.y, buildbot.goal.y = buildbot.goal.y, buildbot.start.y
			build_x(function() minetest.display_chat_message("Done.") end)
		end
		return false, buildbot.goal
	end
})

local keep_digging = false

core.register_chatcommand("keepdigging", {
	params = "<X>,<Y>,<Z>",
	description = "Dig node again and again",
	func = function(param)
		local success, pos = core.parse_pos(param)
		if success then
			keep_digging = true
			local function loop()
				core.dig_node(pos)
				if keep_digging then
					core.after(0.1, loop)
				end
			end
			loop()
		end
	end,
})

core.register_chatcommand("stopdigging", {
	description = "Stop diggin",
	func = function()
		keep_digging = false
	end,
})


core.register_chatcommand("digaround", {
	description = "Automatically dig nodes around you",
	param = "<node1> [<node2>] ...",
	func = function(param)
		local nodes = param:split(" ")
		local function loop()
			local fpos = core.find_node_near(core.localplayer:get_pos(), 5, nodes, true)
			if fpos then core.dig_node(fpos) end
			core.after(0, loop)
		end
		loop()
	end,
})
