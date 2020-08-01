core.cheats = {
	["Combat"] = {
		["Killaura"] = "killaura",
		["AntiKnockback"] = "antiknockback",
		["NoFallDamage"] = "prevent_natural_damage",
		["AutoRespawn"] = "autorespawn",
	},
	["Movement"] = {
		["DragonRider"] = "entity_speed",
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
		["Scaffold"] = "scaffold",
		["Highway"] = "highway",
	},
	["Misc"] = {
		["Enderchest"] = function()
			minetest.open_special_inventory()
		end,
	}
}
