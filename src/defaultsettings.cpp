/*
Minetest
Copyright (C) 2013 celeron55, Perttu Ahola <celeron55@gmail.com>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#include <IrrCompileConfig.h>
#include "settings.h"
#include "porting.h"
#include "filesys.h"
#include "config.h"
#include "constants.h"
#include "porting.h"
#include "mapgen/mapgen.h" // Mapgen::setDefaultSettings
#include "util/string.h"

void set_default_settings()
{
	Settings *settings = Settings::createLayer(SL_DEFAULTS);

	// Client and server
	settings->setDefault("language", "");
	settings->setDefault("name", "");
	settings->setDefault("bind_address", "");
	settings->setDefault("serverlist_url", "servers.minetest.net");

	// Client
	settings->setDefault("address", "");
	settings->setDefault("enable_sound", "true");
	settings->setDefault("sound_volume", "0.8");
	settings->setDefault("mute_sound", "false");
	settings->setDefault("enable_mesh_cache", "false");
	settings->setDefault("mesh_generation_interval", "0");
	settings->setDefault("meshgen_block_cache_size", "20");
	settings->setDefault("enable_vbo", "true");
	settings->setDefault("free_move", "false");
	settings->setDefault("pitch_move", "false");
	settings->setDefault("fast_move", "false");
	settings->setDefault("noclip", "false");
	settings->setDefault("screenshot_path", "screenshots");
	settings->setDefault("screenshot_format", "png");
	settings->setDefault("screenshot_quality", "0");
	settings->setDefault("client_unload_unused_data_timeout", "600");
	settings->setDefault("client_mapblock_limit", "7500");
	settings->setDefault("enable_build_where_you_stand", "true");
	settings->setDefault("curl_timeout", "20000");
	settings->setDefault("curl_parallel_limit", "8");
	settings->setDefault("curl_file_download_timeout", "300000");
	settings->setDefault("curl_verify_cert", "true");
	settings->setDefault("enable_remote_media_server", "true");
	settings->setDefault("enable_client_modding", "true");
	settings->setDefault("max_out_chat_queue_size", "20");
	settings->setDefault("pause_on_lost_focus", "false");
	settings->setDefault("enable_split_login_register", "true");
	settings->setDefault("chat_weblink_color", "#8888FF");

	// Cheat Menu
	settings->setDefault("cheat_menu_font", "FM_Standard");
	settings->setDefault("cheat_menu_bg_color", "(45, 45, 68)");
	settings->setDefault("cheat_menu_bg_color_alpha", "173");
	settings->setDefault("cheat_menu_active_bg_color", "(0, 0, 0)");
	settings->setDefault("cheat_menu_active_bg_color_alpha", "210");
	settings->setDefault("cheat_menu_font_color", "(255, 255, 255)");
	settings->setDefault("cheat_menu_font_color_alpha", "195");
	settings->setDefault("cheat_menu_selected_font_color", "(255, 255, 255)");
	settings->setDefault("cheat_menu_selected_font_color_alpha", "235");
	settings->setDefault("cheat_menu_head_height", "50");
	settings->setDefault("cheat_menu_entry_height", "35");
	settings->setDefault("cheat_menu_entry_width", "200");

	// Cheats
	settings->setDefault("xray", "false");
	settings->setDefault("xray_nodes", "default:stone,mcl_core:stone");
	settings->setDefault("fullbright", "false");
	settings->setDefault("priv_bypass", "true");
	settings->setDefault("freecam", "false");
	settings->setDefault("prevent_natural_damage", "true");
	settings->setDefault("freecam", "false");
	settings->setDefault("no_hurt_cam", "false");
	settings->setDefault("reach", "true");
	settings->setDefault("hud_flags_bypass", "true");
	settings->setDefault("antiknockback", "false");
	settings->setDefault("entity_speed", "false");
	settings->setDefault("autodig", "false");
	settings->setDefault("fastdig", "false");
	settings->setDefault("jesus", "false");
	settings->setDefault("fastplace", "false");
	settings->setDefault("autoplace", "false");
	settings->setDefault("instant_break", "false");
	settings->setDefault("no_night", "false");
	settings->setDefault("coords", "false");
	settings->setDefault("point_liquids", "false");
	settings->setDefault("spamclick", "false");
	settings->setDefault("no_force_rotate", "false");
	settings->setDefault("no_slow", "false");
	settings->setDefault("float_above_parent", "false");
	settings->setDefault("dont_point_nodes", "false");
	settings->setDefault("cheat_hud", "true");
	settings->setDefault("node_esp_nodes", "");
	settings->setDefault("jetpack", "false");
	settings->setDefault("autohit", "false");
	settings->setDefault("antislip", "false");
	settings->setDefault("enable_entity_esp", "false");
	settings->setDefault("enable_entity_tracers", "false");
	settings->setDefault("enable_player_esp", "false");
	settings->setDefault("enable_player_tracers", "false");
	settings->setDefault("enable_node_esp", "false");
	settings->setDefault("enable_node_tracers", "false");
	settings->setDefault("entity_esp_color", "(255, 255, 255)");
	settings->setDefault("player_esp_color", "(0, 255, 0)");
	settings->setDefault("tool_range", "2");
	settings->setDefault("scaffold", "false");
	settings->setDefault("killaura", "false");
	settings->setDefault("airjump", "false");
	settings->setDefault("spider", "false");
	settings->setDefault("node_light", "false");
	settings->setDefault("node_light_color", "(255, 0, 0)");

	// Keymap
	settings->setDefault("remote_port", "30000");
	settings->setDefault("keymap_forward", "KEY_KEY_W");
	settings->setDefault("keymap_autoforward", "");
	settings->setDefault("keymap_backward", "KEY_KEY_S");
	settings->setDefault("keymap_left", "KEY_KEY_A");
	settings->setDefault("keymap_right", "KEY_KEY_D");
	settings->setDefault("keymap_jump", "KEY_SPACE");
	settings->setDefault("keymap_sneak", "KEY_LSHIFT");
	settings->setDefault("keymap_dig", "KEY_LBUTTON");
	settings->setDefault("keymap_place", "KEY_RBUTTON");
	settings->setDefault("keymap_drop", "KEY_KEY_Q");
	settings->setDefault("keymap_zoom", "KEY_KEY_Z");
	settings->setDefault("keymap_inventory", "KEY_KEY_I");
	settings->setDefault("keymap_enderchest", "KEY_KEY_O");
	settings->setDefault("keymap_aux1", "KEY_KEY_E");
	settings->setDefault("keymap_chat", "KEY_KEY_T");
	settings->setDefault("keymap_cmd", "/");
	settings->setDefault("keymap_cmd_local", ".");
	settings->setDefault("keymap_minimap", "KEY_KEY_V");
	settings->setDefault("keymap_console", "KEY_F10");
	settings->setDefault("keymap_rangeselect", "KEY_KEY_R");
	settings->setDefault("keymap_freemove", "KEY_KEY_K");
	settings->setDefault("keymap_pitchmove", "KEY_KEY_P");
	settings->setDefault("keymap_fastmove", "KEY_KEY_J");
	settings->setDefault("keymap_noclip", "KEY_KEY_H");
	settings->setDefault("keymap_hotbar_next", "KEY_KEY_N");
	settings->setDefault("keymap_hotbar_previous", "KEY_KEY_B");
	settings->setDefault("keymap_mute", "KEY_KEY_M");
	settings->setDefault("keymap_increase_volume", "");
	settings->setDefault("keymap_decrease_volume", "");
	settings->setDefault("keymap_cinematic", "");
	settings->setDefault("keymap_toggle_block_bounds", "");
	settings->setDefault("keymap_toggle_hud", "KEY_F1");
	settings->setDefault("keymap_toggle_chat", "KEY_F2");
	settings->setDefault("keymap_toggle_fog", "KEY_F3");
	settings->setDefault("keymap_toggle_cheat_menu", "KEY_F8");
#if DEBUG
	settings->setDefault("keymap_toggle_update_camera", "KEY_F4");
#else
	settings->setDefault("keymap_toggle_update_camera", "");
#endif
	settings->setDefault("keymap_toggle_debug", "KEY_F5");
	settings->setDefault("keymap_toggle_profiler", "KEY_F6");
	settings->setDefault("keymap_camera_mode", "KEY_KEY_C");
	settings->setDefault("keymap_screenshot", "KEY_F12");
	settings->setDefault("keymap_increase_viewing_range_min", "+");
	settings->setDefault("keymap_decrease_viewing_range_min", "-");
	settings->setDefault("keymap_toggle_killaura", "KEY_KEY_X");
	settings->setDefault("keymap_toggle_freecam", "KEY_KEY_G");
	settings->setDefault("keymap_toggle_scaffold", "KEY_KEY_Y");
	settings->setDefault("keymap_select_up", "KEY_UP");
	settings->setDefault("keymap_select_down", "KEY_DOWN");
	settings->setDefault("keymap_select_left", "KEY_LEFT");
	settings->setDefault("keymap_select_right", "KEY_RIGHT");
	settings->setDefault("keymap_select_confirm", "KEY_RETURN");
	settings->setDefault("keymap_slot1", "KEY_KEY_1");
	settings->setDefault("keymap_slot2", "KEY_KEY_2");
	settings->setDefault("keymap_slot3", "KEY_KEY_3");
	settings->setDefault("keymap_slot4", "KEY_KEY_4");
	settings->setDefault("keymap_slot5", "KEY_KEY_5");
	settings->setDefault("keymap_slot6", "KEY_KEY_6");
	settings->setDefault("keymap_slot7", "KEY_KEY_7");
	settings->setDefault("keymap_slot8", "KEY_KEY_8");
	settings->setDefault("keymap_slot9", "KEY_KEY_9");
	settings->setDefault("keymap_slot10", "KEY_KEY_0");
	settings->setDefault("keymap_slot11", "");
	settings->setDefault("keymap_slot12", "");
	settings->setDefault("keymap_slot13", "");
	settings->setDefault("keymap_slot14", "");
	settings->setDefault("keymap_slot15", "");
	settings->setDefault("keymap_slot16", "");
	settings->setDefault("keymap_slot17", "");
	settings->setDefault("keymap_slot18", "");
	settings->setDefault("keymap_slot19", "");
	settings->setDefault("keymap_slot20", "");
	settings->setDefault("keymap_slot21", "");
	settings->setDefault("keymap_slot22", "");
	settings->setDefault("keymap_slot23", "");
	settings->setDefault("keymap_slot24", "");
	settings->setDefault("keymap_slot25", "");
	settings->setDefault("keymap_slot26", "");
	settings->setDefault("keymap_slot27", "");
	settings->setDefault("keymap_slot28", "");
	settings->setDefault("keymap_slot29", "");
	settings->setDefault("keymap_slot30", "");
	settings->setDefault("keymap_slot31", "");
	settings->setDefault("keymap_slot32", "");

	// Some (temporary) keys for debugging
	settings->setDefault("keymap_quicktune_prev", "KEY_HOME");
	settings->setDefault("keymap_quicktune_next", "KEY_END");
	settings->setDefault("keymap_quicktune_dec", "KEY_NEXT");
	settings->setDefault("keymap_quicktune_inc", "KEY_PRIOR");

	// Visuals
#ifdef NDEBUG
	settings->setDefault("show_debug", "false");
#else
	settings->setDefault("show_debug", "true");
#endif
	settings->setDefault("fsaa", "0");
	settings->setDefault("undersampling", "0");
	settings->setDefault("world_aligned_mode", "enable");
	settings->setDefault("autoscale_mode", "disable");
	settings->setDefault("enable_fog", "true");
	settings->setDefault("fog_start", "0.4");
	settings->setDefault("3d_mode", "none");
	settings->setDefault("3d_paralax_strength", "0.025");
	settings->setDefault("tooltip_show_delay", "400");
	settings->setDefault("tooltip_append_itemname", "false");
	settings->setDefault("fps_max", "60");
	settings->setDefault("fps_max_unfocused", "20");
	settings->setDefault("viewing_range", "190");
#if ENABLE_GLES
	settings->setDefault("near_plane", "0.1");
#endif
	settings->setDefault("screen_w", "1024");
	settings->setDefault("screen_h", "600");
	settings->setDefault("autosave_screensize", "true");
	settings->setDefault("fullscreen", "false");
	settings->setDefault("vsync", "false");
	settings->setDefault("fov", "72");
	settings->setDefault("leaves_style", "fancy");
	settings->setDefault("connected_glass", "false");
	settings->setDefault("smooth_lighting", "true");
	settings->setDefault("performance_tradeoffs", "false");
	settings->setDefault("lighting_alpha", "0.0");
	settings->setDefault("lighting_beta", "1.5");
	settings->setDefault("display_gamma", "1.0");
	settings->setDefault("lighting_boost", "0.2");
	settings->setDefault("lighting_boost_center", "0.5");
	settings->setDefault("lighting_boost_spread", "0.2");
	settings->setDefault("texture_path", "");
	settings->setDefault("shader_path", "");
#if ENABLE_GLES
#ifdef _IRR_COMPILE_WITH_OGLES1_
	settings->setDefault("video_driver", "ogles1");
#else
	settings->setDefault("video_driver", "ogles2");
#endif
#else
	settings->setDefault("video_driver", "opengl");
#endif
	settings->setDefault("cinematic", "false");
	settings->setDefault("camera_smoothing", "0");
	settings->setDefault("cinematic_camera_smoothing", "0.7");
	settings->setDefault("enable_clouds", "true");
	settings->setDefault("view_bobbing_amount", "1.0");
	settings->setDefault("fall_bobbing_amount", "0.03");
	settings->setDefault("enable_3d_clouds", "true");
	settings->setDefault("cloud_radius", "12");
	settings->setDefault("menu_clouds", "true");
	settings->setDefault("opaque_water", "false");
	settings->setDefault("console_height", "0.6");
	settings->setDefault("console_color", "(0,0,0)");
	settings->setDefault("console_alpha", "150");
	settings->setDefault("formspec_fullscreen_bg_color", "(0,0,0)");
	settings->setDefault("formspec_fullscreen_bg_opacity", "140");
	settings->setDefault("formspec_default_bg_color", "(0,0,0)");
	settings->setDefault("formspec_default_bg_opacity", "140");
	settings->setDefault("selectionbox_color", "(0,0,0)");
	settings->setDefault("selectionbox_width", "2");
	settings->setDefault("node_highlighting", "box");
	settings->setDefault("crosshair_color", "(255,255,255)");
	settings->setDefault("crosshair_alpha", "255");
	settings->setDefault("recent_chat_messages", "6");
	settings->setDefault("hud_scaling", "1.0");
	settings->setDefault("gui_scaling", "1.0");
	settings->setDefault("gui_scaling_filter", "false");
	settings->setDefault("gui_scaling_filter_txr2img", "true");
	settings->setDefault("desynchronize_mapblock_texture_animation", "true");
	settings->setDefault("hud_hotbar_max_width", "1.0");
	settings->setDefault("enable_local_map_saving", "false");
	settings->setDefault("show_entity_selectionbox", "false");
	settings->setDefault("texture_clean_transparent", "false");
	settings->setDefault("texture_min_size", "64");
	settings->setDefault("ambient_occlusion_gamma", "1.8");
#if ENABLE_GLES
	settings->setDefault("enable_shaders", "false");
#else
	settings->setDefault("enable_shaders", "true");
#endif
	settings->setDefault("enable_particles", "true");
	settings->setDefault("arm_inertia", "true");
	settings->setDefault("show_nametag_backgrounds", "true");
	settings->setDefault("transparency_sorting_distance", "16");

	settings->setDefault("enable_minimap", "true");
	settings->setDefault("minimap_shape_round", "false");
	settings->setDefault("minimap_double_scan_height", "true");

	// Effects
	settings->setDefault("directional_colored_fog", "true");
	settings->setDefault("inventory_items_animations", "false");
	settings->setDefault("mip_map", "false");
	settings->setDefault("anisotropic_filter", "false");
	settings->setDefault("bilinear_filter", "false");
	settings->setDefault("trilinear_filter", "false");
	settings->setDefault("tone_mapping", "false");
	settings->setDefault("enable_waving_water", "false");
	settings->setDefault("water_wave_height", "1.0");
	settings->setDefault("water_wave_length", "20.0");
	settings->setDefault("water_wave_speed", "5.0");
	settings->setDefault("enable_waving_leaves", "false");
	settings->setDefault("enable_waving_plants", "false");

	// Effects Shadows
	settings->setDefault("enable_dynamic_shadows", "false");
	settings->setDefault("shadow_strength_gamma", "1.0");
	settings->setDefault("shadow_map_max_distance", "200.0");
	settings->setDefault("shadow_map_texture_size", "2048");
	settings->setDefault("shadow_map_texture_32bit", "true");
	settings->setDefault("shadow_map_color", "false");
	settings->setDefault("shadow_filters", "1");
	settings->setDefault("shadow_poisson_filter", "true");
	settings->setDefault("shadow_update_frames", "8");
	settings->setDefault("shadow_soft_radius", "5.0");
	settings->setDefault("shadow_sky_body_orbit_tilt", "0.0");

	// Input
	settings->setDefault("invert_mouse", "false");
	settings->setDefault("mouse_sensitivity", "0.2");
	settings->setDefault("repeat_place_time", "0.25");
	settings->setDefault("safe_dig_and_place", "false");
	settings->setDefault("random_input", "false");
	settings->setDefault("aux1_descends", "false");
	settings->setDefault("doubletap_jump", "false");
	settings->setDefault("always_fly_fast", "true");
#ifdef HAVE_TOUCHSCREENGUI
	settings->setDefault("autojump", "true");
#else
	settings->setDefault("autojump", "false");
#endif
	settings->setDefault("continuous_forward", "false");
	settings->setDefault("enable_joysticks", "false");
	settings->setDefault("joystick_id", "0");
	settings->setDefault("joystick_type", "");
	settings->setDefault("repeat_joystick_button_time", "0.17");
	settings->setDefault("joystick_frustum_sensitivity", "170");
	settings->setDefault("joystick_deadzone", "2048");

	// Main menu
	settings->setDefault("main_menu_path", "");
	settings->setDefault("serverlist_file", "favoriteservers.json");

	// General font settings
	settings->setDefault("font_path", porting::getDataPath("fonts" DIR_DELIM "Arimo-Regular.ttf"));
	settings->setDefault("font_path_italic", porting::getDataPath("fonts" DIR_DELIM "Arimo-Italic.ttf"));
	settings->setDefault("font_path_bold", porting::getDataPath("fonts" DIR_DELIM "Arimo-Bold.ttf"));
	settings->setDefault("font_path_bold_italic", porting::getDataPath("fonts" DIR_DELIM "Arimo-BoldItalic.ttf"));
	settings->setDefault("font_bold", "false");
	settings->setDefault("font_italic", "false");
	settings->setDefault("font_shadow", "1");
	settings->setDefault("font_shadow_alpha", "127");
	settings->setDefault("font_size_divisible_by", "1");
	settings->setDefault("mono_font_path", porting::getDataPath("fonts" DIR_DELIM "Cousine-Regular.ttf"));
	settings->setDefault("mono_font_path_italic", porting::getDataPath("fonts" DIR_DELIM "Cousine-Italic.ttf"));
	settings->setDefault("mono_font_path_bold", porting::getDataPath("fonts" DIR_DELIM "Cousine-Bold.ttf"));
	settings->setDefault("mono_font_path_bold_italic", porting::getDataPath("fonts" DIR_DELIM "Cousine-BoldItalic.ttf"));
	settings->setDefault("mono_font_size_divisible_by", "1");
	settings->setDefault("fallback_font_path", porting::getDataPath("fonts" DIR_DELIM "DroidSansFallbackFull.ttf"));

	std::string font_size_str = std::to_string(TTF_DEFAULT_FONT_SIZE);
	settings->setDefault("font_size", font_size_str);
	settings->setDefault("mono_font_size", font_size_str);
	settings->setDefault("chat_font_size", "0"); // Default "font_size"

	// ContentDB
	settings->setDefault("contentdb_url", "http://cheatdb.elidragon.com");
	settings->setDefault("contentdb_max_concurrent_downloads", "3");

#ifdef __ANDROID__
	settings->setDefault("contentdb_flag_blacklist", "android_default");
#else
	settings->setDefault("contentdb_flag_blacklist", "desktop_default");
#endif


	// Server
	settings->setDefault("disable_escape_sequences", "false");
	settings->setDefault("strip_color_codes", "false");
#if USE_PROMETHEUS
	settings->setDefault("prometheus_listener_address", "127.0.0.1:30000");
#endif

	// Network
	settings->setDefault("enable_ipv6", "true");
	settings->setDefault("ipv6_server", "false");
	settings->setDefault("max_packets_per_iteration","1024");
	settings->setDefault("port", "30000");
	settings->setDefault("strict_protocol_version_checking", "false");
	settings->setDefault("player_transfer_distance", "0");
	settings->setDefault("max_simultaneous_block_sends_per_client", "40");
	settings->setDefault("time_send_interval", "5");

	settings->setDefault("default_game", "MineClone2");
	settings->setDefault("motd", "");
	settings->setDefault("max_users", "15");
	settings->setDefault("creative_mode", "false");
	settings->setDefault("enable_damage", "true");
	settings->setDefault("default_password", "");
	settings->setDefault("default_privs", "interact, shout");
	settings->setDefault("enable_pvp", "true");
	settings->setDefault("enable_mod_channels", "false");
	settings->setDefault("disallow_empty_password", "false");
	settings->setDefault("disable_anticheat", "false");
	settings->setDefault("enable_rollback_recording", "false");
	settings->setDefault("deprecated_lua_api_handling", "log");

	settings->setDefault("kick_msg_shutdown", "Server shutting down.");
	settings->setDefault("kick_msg_crash", "This server has experienced an internal error. You will now be disconnected.");
	settings->setDefault("ask_reconnect_on_crash", "false");

	settings->setDefault("chat_message_format", "<@name> @message");
	settings->setDefault("profiler_print_interval", "0");
	settings->setDefault("active_object_send_range_blocks", "8");
	settings->setDefault("active_block_range", "4");
	//settings->setDefault("max_simultaneous_block_sends_per_client", "1");
	// This causes frametime jitter on client side, or does it?
	settings->setDefault("max_block_send_distance", "12");
	settings->setDefault("block_send_optimize_distance", "4");
	settings->setDefault("server_side_occlusion_culling", "true");
	settings->setDefault("csm_restriction_flags", "62");
	settings->setDefault("csm_restriction_noderange", "0");
	settings->setDefault("max_clearobjects_extra_loaded_blocks", "4096");
	settings->setDefault("time_speed", "72");
	settings->setDefault("world_start_time", "6125");
	settings->setDefault("server_unload_unused_data_timeout", "29");
	settings->setDefault("max_objects_per_block", "256");
	settings->setDefault("server_map_save_interval", "5.3");
	settings->setDefault("chat_message_max_size", "500");
	settings->setDefault("chat_message_limit_per_10sec", "8.0");
	settings->setDefault("chat_message_limit_trigger_kick", "50");
	settings->setDefault("sqlite_synchronous", "2");
	settings->setDefault("map_compression_level_disk", "-1");
	settings->setDefault("map_compression_level_net", "-1");
	settings->setDefault("full_block_send_enable_min_time_from_building", "2.0");
	settings->setDefault("dedicated_server_step", "0.09");
	settings->setDefault("active_block_mgmt_interval", "2.0");
	settings->setDefault("abm_interval", "1.0");
	settings->setDefault("abm_time_budget", "0.2");
	settings->setDefault("nodetimer_interval", "0.2");
	settings->setDefault("ignore_world_load_errors", "false");
	settings->setDefault("remote_media", "");
	settings->setDefault("debug_log_level", "action");
	settings->setDefault("debug_log_size_max", "50");
	settings->setDefault("chat_log_level", "error");
	settings->setDefault("emergequeue_limit_total", "1024");
	settings->setDefault("emergequeue_limit_diskonly", "128");
	settings->setDefault("emergequeue_limit_generate", "128");
	settings->setDefault("num_emerge_threads", "1");
	settings->setDefault("secure.enable_security", "true");
	settings->setDefault("secure.trusted_mods", "");
	settings->setDefault("secure.http_mods", "");

	// Physics
	settings->setDefault("movement_acceleration_default", "3");
	settings->setDefault("movement_acceleration_air", "2");
	settings->setDefault("movement_acceleration_fast", "10");
	settings->setDefault("movement_speed_walk", "4");
	settings->setDefault("movement_speed_crouch", "1.35");
	settings->setDefault("movement_speed_fast", "20");
	settings->setDefault("movement_speed_climb", "3");
	settings->setDefault("movement_speed_jump", "6.5");
	settings->setDefault("movement_liquid_fluidity", "1");
	settings->setDefault("movement_liquid_fluidity_smooth", "0.5");
	settings->setDefault("movement_liquid_sink", "10");
	settings->setDefault("movement_gravity", "9.81");

	// Liquids
	settings->setDefault("liquid_loop_max", "100000");
	settings->setDefault("liquid_queue_purge_time", "0");
	settings->setDefault("liquid_update", "1.0");

	// Mapgen
	settings->setDefault("mg_name", "v7");
	settings->setDefault("water_level", "1");
	settings->setDefault("mapgen_limit", "31007");
	settings->setDefault("chunksize", "5");
	settings->setDefault("fixed_map_seed", "");
	settings->setDefault("max_block_generate_distance", "10");
	settings->setDefault("enable_mapgen_debug_info", "false");
	Mapgen::setDefaultSettings(settings);

	// Server list announcing
	settings->setDefault("server_announce", "false");
	settings->setDefault("server_url", "");
	settings->setDefault("server_address", "");
	settings->setDefault("server_name", "");
	settings->setDefault("server_description", "");

	settings->setDefault("enable_console", "false");
	settings->setDefault("screen_dpi", "72");
	settings->setDefault("display_density_factor", "1");

	// Altered settings for macOS
#if defined(__MACH__) && defined(__APPLE__)
	settings->setDefault("keymap_sneak", "KEY_SHIFT");
#endif

#ifdef HAVE_TOUCHSCREENGUI
	settings->setDefault("touchtarget", "true");
	settings->setDefault("touchscreen_threshold","20");
	settings->setDefault("fixed_virtual_joystick", "false");
	settings->setDefault("virtual_joystick_triggers_aux1", "false");
	settings->setDefault("clickable_chat_weblinks", "false");
#else
	settings->setDefault("clickable_chat_weblinks", "true");
#endif
	// Altered settings for Android
#ifdef __ANDROID__
	settings->setDefault("screen_w", "0");
	settings->setDefault("screen_h", "0");
	settings->setDefault("fullscreen", "true");
	settings->setDefault("smooth_lighting", "false");
	settings->setDefault("performance_tradeoffs", "true");
	settings->setDefault("max_simultaneous_block_sends_per_client", "10");
	settings->setDefault("emergequeue_limit_diskonly", "16");
	settings->setDefault("emergequeue_limit_generate", "16");
	settings->setDefault("max_block_generate_distance", "5");
	settings->setDefault("enable_3d_clouds", "false");
	settings->setDefault("fps_max", "30");
	settings->setDefault("fps_max_unfocused", "10");
	settings->setDefault("sqlite_synchronous", "1");
	settings->setDefault("map_compression_level_disk", "-1");
	settings->setDefault("map_compression_level_net", "-1");
	settings->setDefault("server_map_save_interval", "15");
	settings->setDefault("client_mapblock_limit", "1000");
	settings->setDefault("active_block_range", "2");
	settings->setDefault("viewing_range", "50");
	settings->setDefault("leaves_style", "simple");
	settings->setDefault("curl_verify_cert","false");

	// Apply settings according to screen size
	float x_inches = (float) porting::getDisplaySize().X /
			(160.f * porting::getDisplayDensity());

	if (x_inches < 3.7f) {
		settings->setDefault("hud_scaling", "0.6");
		settings->setDefault("font_size", "14");
		settings->setDefault("mono_font_size", "14");
	} else if (x_inches < 4.5f) {
		settings->setDefault("hud_scaling", "0.7");
		settings->setDefault("font_size", "14");
		settings->setDefault("mono_font_size", "14");
	} else if (x_inches < 6.0f) {
		settings->setDefault("hud_scaling", "0.85");
		settings->setDefault("font_size", "14");
		settings->setDefault("mono_font_size", "14");
	}
	// Tablets >= 6.0 use non-Android defaults for these settings
#endif
}
