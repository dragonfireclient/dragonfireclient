core.cheats = {
	["Combat"] = {
		["AntiKnockback"] = "antiknockback",
		["AttachmentFloat"] = "float_above_parent",
	},
	["Movement"] = {
		["Freecam"] = "freecam",
		["AutoForward"] = "continuous_forward",
		["PitchMove"] = "pitch_move",
		["AutoJump"] = "autojump",
		["Jesus"] = "jesus",
		["NoSlow"] = "no_slow",
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
	},
	["Interact"] = {
		["FastDig"] = "fastdig",
		["FastPlace"] = "fastplace",
		["AutoDig"] = "autodig",
		["AutoPlace"] = "autoplace",
		["InstantBreak"] = "instant_break",
		["FastHit"] = "spamclick",
		["AutoHit"] = "autohit",
	},
	["Exploit"] = {
		["EntitySpeed"] = "entity_speed",
	},
	["Player"] = {
		["NoFallDamage"] = "prevent_natural_damage",
		["NoForceRotate"] = "no_force_rotate",
		["Reach"] = "reach",
		["PointLiquids"] = "point_liquids",
		["PrivBypass"] = "priv_bypass",
		["AutoRespawn"] = "autorespawn",
		["ThroughWalls"] = "dont_point_nodes",
	},
}

function core.register_cheat(cheatname, category, func)
	core.cheats[category] = core.cheats[category] or {}
	core.cheats[category][cheatname] = func
end
