core.cheats = {
	["Combat"] = {
		["Killaura"] = "killaura",
		["AntiKnockback"] = "antiknockback",
		["NoFallDamage"] = "prevent_natural_damage",
	},
	["Movement"] = {
		["GodMode"] = "entity_speed",
		["Freecam"] = "freecam",
		["PrivBypass"] = "priv_bypass",
		["AutoForward"] = "continuous_forward",
		["PitchMove"] = "pitch_move",
		["AutoJump"] = "autojump",
		["Jesus"] = "jesus",
	},
	["Render"] = {
		["Xray"] = "xray",
		["Fullbright"] = "fullbright",
		["HUDBypass"] = "hud_flags_bypass",
		["NoHurtCam"] = "no_hurt_cam",
		["BrightNight"] = "no_night",
		["Coords"] = "coords",
	},
	["World"] = {
		["FastDig"] = "fastdig",
		["FastPlace"] = "fastplace",
		["AutoDig"] = "autodig",
		["AutoPlace"] = "autoplace",
		["InstantBreak"] = "instant_break",
		["IncreasedRange"] = "increase_tool_range",
		["UnlimitedRange"] = "increase_tool_range_plus",
		["PointLiquids"] = "point_liquids",
	},
	["Misc"] = {
		["Enderchest"] = function()
			minetest.open_special_inventory()
		end,
	}
}

function core.register_cheat(cheatname, category, func)
	core.cheats[category] = core.cheats[category] or {}
	core.cheats[category][cheatname] = func
end
