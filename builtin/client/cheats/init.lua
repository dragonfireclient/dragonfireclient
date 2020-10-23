core.cheats = {
	["Combat"] = {
		["Killaura"] = "killaura",
		["AntiKnockback"] = "antiknockback",
		["FastHit"] = "spamclick",
		["AttachmentFloat"] = "float_above_parent",
		["CrystalPvP"] = "crystal_pvp",
		["AutoTotem"] = "autototem",
		["ThroughWalls"] = "dont_point_nodes",
	},
	["Movement"] = {
		["Freecam"] = "freecam",
		["AutoForward"] = "continuous_forward",
		["PitchMove"] = "pitch_move",
		["AutoJump"] = "autojump",
		["Jesus"] = "jesus",
		["NoSlow"] = "no_slow",
		["AutoSneak"] = "autosneak",
	},
	["Render"] = {
		["Xray"] = "xray",
		["Fullbright"] = "fullbright",
		["HUDBypass"] = "hud_flags_bypass",
		["NoHurtCam"] = "no_hurt_cam",
		["BrightNight"] = "no_night",
		["Coords"] = "coords",
		["Tracers"] = "enable_tracers",
		["ESP"] = "enable_esp",
	},
	["World"] = {
		["FastDig"] = "fastdig",
		["FastPlace"] = "fastplace",
		["AutoDig"] = "autodig",
		["AutoPlace"] = "autoplace",
		["InstantBreak"] = "instant_break",
		["Scaffold"] = "scaffold",
		["ScaffoldPlus"] = "scaffold_plus",
		["BlockWater"] = "block_water",
		["PlaceOnTop"] = "autotnt",
		["Replace"] = "replace"
	},
	["Exploit"] = {
		["EntitySpeed"] = "entity_speed",
		["ParticleExploit"] = "log_particles",
	},
	["Player"] = {
		["NoFallDamage"] = "prevent_natural_damage",
		["NoForceRotate"] = "no_force_rotate",
		["IncreasedRange"] = "increase_tool_range",
		["UnlimitedRange"] = "increase_tool_range_plus",
		["PointLiquids"] = "point_liquids",
		["PrivBypass"] = "priv_bypass",
		["AutoRespawn"] = "autorespawn",
		["BlockFormspec"] = "block_formspec"
	},
	["Chat"] = {
		["IgnoreStatus"] = "ignore_status_messages",
		["Deathmessages"] = "mark_deathmessages"
	},
	["Inventory"] = {
		["AutoEject"] = "autoeject",
		["AutoTool"] = "autotool",
		["Enderchest"] = function() core.open_enderchest() end,
		["HandSlot"] = function() core.open_handslot() end,
		["NextItem"] = "next_item",
	}
}

function core.register_cheat(cheatname, category, func)
	core.cheats[category] = core.cheats[category] or {}
	core.cheats[category][cheatname] = func
end

local cheatpath = core.get_builtin_path() .. "client" .. DIR_DELIM .. "cheats" .. DIR_DELIM

dofile(cheatpath .. "chat.lua")
dofile(cheatpath .. "combat.lua")
dofile(cheatpath .. "inventory.lua")
dofile(cheatpath .. "movement.lua")
dofile(cheatpath .. "player.lua")
dofile(cheatpath .. "render.lua")
dofile(cheatpath .. "world.lua")
