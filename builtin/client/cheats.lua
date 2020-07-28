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
	},
	["Render"] = {
		["Xray"] = "xray",
		["Fullbright"] = "fullbright",
		["HUDBypass"] = "hud_flags_bypass",
		["NoHurtCam"] = "no_hurt_cam"
	},
	["World"] = {
		["FastDig"] = "fastdig",
		["AutoDig"] = "autodig",
		["IncreasedRange"] = "increase_tool_range",
		["UnlimitedRange"] = "increase_tool_range_plus",
	},
	["Misc"] = {
		["Enderchest"] = function()
			minetest.open_special_inventory()
		end,
	}
}
