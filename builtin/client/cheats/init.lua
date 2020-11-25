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
		["NoSlip"] = "noslip",
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
		["NodeTracers"] = "enable_node_tracers",
		["NodeESP"] = "enable_node_esp",
		["EntityESP"] = "enable_entity_esp",
		["EntityTracers"] = "enable_entity_tracers",
		["CheatHUD"] = "cheat_hud",
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
		["NextItem"] = "next_item",
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
