core.register_chatcommand("set", {
	params = "([-n] <name> <value>) | <name>",
	description = "Set or read client configuration setting",
	privs = {server=true},
	func = function(param)
		local arg, setname, setvalue = string.match(param, "(-[n]) ([^ ]+) (.+)")
		if arg and arg == "-n" and setname and setvalue then
			core.settings:set(setname, setvalue)
			return true, setname .. " = " .. setvalue
		end

		setname, setvalue = string.match(param, "([^ ]+) (.+)")
		if setname and setvalue then
			if not core.settings:get(setname) then
				return false, "Failed. Use '.set -n <name> <value>' to create a new setting."
			end
			core.settings:set(setname, setvalue)
			return true, setname .. " = " .. setvalue
		end

		setname = string.match(param, "([^ ]+)")
		if setname then
			setvalue = core.settings:get(setname)
			if not setvalue then
				setvalue = "<not set>"
			end
			return true, setname .. " = " .. setvalue
		end

		return false, "Invalid parameters (see .help set)."
	end,
})
 
