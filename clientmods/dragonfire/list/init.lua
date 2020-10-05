list = {}

function list.new(desc, setting)
	local def = {}
	def.description = desc
	def.params = "del <item> | add <item> | list"
	function def.func(param)
		local list = (minetest.settings:get(setting) or ""):split(",")
		if param == "list" then
			return true, table.concat(list, ", ")
		else
			local sparam = param:split(" ")
			local cmd = sparam[1]
			local item = sparam[2]
			if cmd == "del" then
				if not item then
					return false, "Missing item."
				end
				local i = table.indexof(list, item)
				if i == -1 then
					return false, item .. " is not on the list."
				else
					table.remove(list, i)
					minetest.settings:set(setting, table.concat(list, ","))
					return true, "Removed " .. item .. " from the list."
				end
			elseif cmd == "add" then
				if not item then
					return false, "Missing item."
				end
				local i = table.indexof(list, item)
				if i ~= -1 then
					return false, item .. " is already on the list."
				else
					table.insert(list, item)
					minetest.settings:set(setting, table.concat(list, ","))
					return true, "Added " .. item .. " to the list."
				end
			end
		end
		return false, "Invalid usage. (See /help <command>)"
	end
	return def
end

minetest.register_chatcommand("xray", list.new("Configure X-Ray", "xray_nodes"))
--minetest.register_chatcommand("Configure Search Nodes", "search_nodes")
