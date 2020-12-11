core.cheats = {
	["Combat"] = {
		["Killaura"] = "killaura",
		["Forcefield"] = "forcefield",
		["AntiKnockback"] = "antiknockback",
		["FastHit"] = "spamclick",
		["AttachmentFloat"] = "float_above_parent",
		["CrystalPvP"] = "crystal_pvp",
		["AutoTotem"] = "autototem",
		["ThroughWalls"] = "dont_point_nodes",
		["AutoHit"] = "autohit",
	},
	["Movement"] = {
		["Freecam"] = "freecam",
		["AutoForward"] = "continuous_forward",
		["PitchMove"] = "pitch_move",
		["AutoJump"] = "autojump",
		["Jesus"] = "jesus",
		["NoSlow"] = "no_slow",
		["AutoSneak"] = "autosneak",
		["AutoSprint"] = "autosprint",
		["SpeedOverride"] = "override_speed",
		["JumpOverride"] = "override_jump",
		["GravityOverride"] = "override_gravity",
		["JetPack"] = "jetpack",
		["AntiSlip"] = "antislip",
	},
	["Render"] = {
		["Xray"] = "xray",
		["Fullbright"] = "fullbright",
		["HUDBypass"] = "hud_flags_bypass",
		["NoHurtCam"] = "no_hurt_cam",
		["BrightNight"] = "no_night",
		["Coords"] = "coords",
		["CheatHUD"] = "cheat_hud",
		["EntityESP"] = "enable_entity_esp",
		["EntityTracers"] = "enable_entity_tracers",
		["PlayerESP"] = "enable_player_esp",
		["PlayerTracers"] = "enable_player_tracers",
		["NodeESP"] = "enable_node_esp",
		["NodeTracers"] = "enable_node_tracers",
		["NoWeather"] = "noweather",
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
		["BlockLava"] = "block_lava",
		["PlaceOnTop"] = "autotnt",
		["Replace"] = "replace",
		["Nuke"] = "nuke",
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
	},
	["Chat"] = {
		["IgnoreStatus"] = "ignore_status_messages",
		["Deathmessages"] = "mark_deathmessages",
		["ColoredChat"] = "use_chat_color",
		["ReversedChat"] = "chat_reverse",
	},
	["Inventory"] = {
		["AutoEject"] = "autoeject",
		["AutoTool"] = "autotool",
		["Enderchest"] = function() core.open_enderchest() end,
		["HandSlot"] = function() core.open_handslot() end,
		["Strip"] = "strip",
		["AutoRefill"] = "autorefill",
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
