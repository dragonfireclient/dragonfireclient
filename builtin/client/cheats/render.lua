core.register_list_command("xray", "Configure X-Ray", "xray_nodes") 
core.register_list_command("search", "Configure NodeESP", "node_esp_nodes") 

core.register_on_spawn_particle(function(particle)
	if core.settings:get_bool("noweather") and particle.texture:sub(1, 12) == "weather_pack" then
		return true
	end
end)

core.register_on_play_sound(function(sound)
	if core.settings:get_bool("noweather") and sound.name == "weather_rain" then
		return true
	end
end)
