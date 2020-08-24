local storage = minetest.get_mod_storage()
local pos1, pos2
local min, max = math.min, math.max
local building, build_index, build_data, build_pos, just_placed_node, failed_count, out_of_blocks

minetest.register_chatcommand("pos1", {
	description = "Set schematicas position 1 at your current location",
	func = function()
		pos1 = vector.round(minetest.localplayer:get_pos())
		return true, "Position 1 set to " .. minetest.pos_to_string(pos1)
	end
})

minetest.register_chatcommand("pos2", {
	description = "Set schematicas position 2 at your current location",
	func = function()
		pos2 = vector.round(minetest.localplayer:get_pos())
		return true, "Position 2 set to " .. minetest.pos_to_string(pos2)
	end
})


minetest.register_chatcommand("schemesave", {
	description = "Save a schematica",
	param = "<name>",
	func = function(name)
		if not pos1 or not pos2 then
			return false, "Position 1 or 2 not set."
		end
		
		local data = {}
		
		local lx, ly, lz, hx, hy, hz = min(pos1.x, pos2.x), min(pos1.y, pos2.y), min(pos1.z, pos2.z), max(pos1.x, pos2.x), max(pos1.y, pos2.y), max(pos1.z, pos2.z)

		for x = lx, hx do
			local rx = x - lx
			for y = ly, hy do
				local ry = y - ly
				for z = lz, hz do
					local rz = z - lz
					local node = minetest.get_node_or_nil({x = x, y = y, z = z})
					if node and node.name ~= "air" then
						table.insert(data, {pos = {x = rx, y = ry, z = rz}, node = node.name})
					end
				end
			end
		end
		
		storage:set_string(name, minetest.serialize(data))
		return true, "Scheme saved successfully as '" .. name .. "'."
	end
})

minetest.register_chatcommand("schemebuild", {
	description = "Build a schematica",
	param = "<name>",
	func = function(name)
		if not pos1 then
			return false, "Position 1 not set."
		end
		if building then
			return false, "Still building a scheme. Use .schemeabort to stop it."
		end
		local rawdata = storage:get(name)
		if not rawdata then
			return false, "Schematica '" .. name .. "' not found."
		end
		building, build_index, build_data, build_pos, just_placed_node, failed_count, out_of_blocks  = true, 1, minetest.deserialize(rawdata), vector.new(pos1), false, 0, false
	end
})

minetest.register_chatcommand("schemerecipe", {
	description = "Print the recipe for a schematica",
	param = "<name>",
	func = function(name)
		local rawdata = storage:get(name)
		if not rawdata then
			return false, "Schematica '" .. name .. "' not found."
		end
		local data = minetest.deserialize(rawdata)
		local sorted = {}
		for _, d in ipairs(data) do
			
		end
	end
})

minetest.register_chatcommand("schemeresume", {
	description = "Resume constructing a schematica",
	func = function()
		if not build_data then
			return false, "Currently not building a scheme."
		end
		building, out_of_blocks = true, false
		return true, "Resumed."
	end
})

minetest.register_chatcommand("schemepause", {
	description = "Pause constructing a schematica",
	func = function()
		if not build_data then
			return false, "Currently not building a scheme."
		end
		building = false
		return true, "Paused."
	end
})

minetest.register_chatcommand("schemeabort", {
	description = "Abort constructing a schematica",
	param = "<name>",
	func = function()
		if not build_data then
			return false, "Currently not building a scheme."
		end
		building, build_index, build_data, build_pos, just_placed_node = nil
		return true, "Aborted."
	end
})

minetest.register_chatcommand("schemeskip", {
	description = "Skip a step in constructing a schematica",
	param = "<name>",
	func = function()
		if not build_data then
			return false, "Currently not building a scheme."
		end
		building, build_index = true, build_index + 1
		return true, "Skipped."
	end
})

minetest.register_chatcommand("schemegetindex", {
	description = "Output the build index of the schematica",
	func = function()
		return build_index and true or false, build_index
	end
})

minetest.register_chatcommand("schemesetindex", {
	description = "Set the build index of the schematica",
	param = "<index>",
	func = function(param)
		local index = tonumber(param)
		if not index then return false, "Invalid usage." end
		build_index = index
		return true, "Index Changed"
	end
})

minetest.register_globalstep(function()
	if building then
		local data = build_data[build_index]
		if not data then
			building, build_index, build_data, build_pos, just_placed_node, failed_count, out_of_blocks  = true, 1, minetest.deserialize(rawdata), vector.new(pos1), false, 0, false
			minetest.display_chat_message("Completed Schematica.")
			return
		end
		local pos, node = vector.add(build_pos, data.pos), data.node
		if just_placed_node then
			local map_node = minetest.get_node_or_nil(pos)
			if map_node and map_node.name == node then
				build_index = build_index + 1
				just_placed_node = false
			else
				failed_count = failed_count + 1
			end
			if failed_count < 10 then
				return
			end
		end
		failed_count = 0
		local new_index
		local inventory = minetest.get_inventory("current_player").main
		for index, stack in ipairs(inventory) do
			if minetest.get_item_def(stack:get_name()).node_placement_prediction == node then
				new_index = index - 1
				break
			end
		end
		if not new_index then
			if not out_of_blocks then
				minetest.display_chat_message("Out of blocks for schematica. Missing ressource: '" .. node .. "'. It will resume as soon as you got it or use .schemeskip to skip it.")
				minetest.send_chat_message(node)
			end
			out_of_blocks = true
			return
		end
		out_of_blocks = false
		minetest.localplayer:set_wield_index(new_index)
		minetest.localplayer:set_pos(minetest.find_node_near(pos, 5, {"air", "ignore", "mcl_core:water_source", "mcl_core:water_flowing"}, false) or pos)
		minetest.place_node(pos)
		just_placed_node = true
	end
end)

