/*
Dragonfire
Copyright (C) 2020 Elias Fleckenstein <eliasfleckenstein@web.de>

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

#pragma once

#include "client/client.h"
#include "irrlichttypes_extrabloated.h"
#include "script/scripting_client.h"
#include <cstddef>
#include <string>

#define CHEAT_MENU_GET_SCRIPTPTR                                                         \
	ClientScripting *script = m_client->getScript();                                 \
	if (!script || !script->m_cheats_loaded)                                         \
		return;

enum CheatMenuEntryType
{
	CHEAT_MENU_ENTRY_TYPE_HEAD,
	CHEAT_MENU_ENTRY_TYPE_CATEGORY,
	CHEAT_MENU_ENTRY_TYPE_ENTRY,
};

class CheatMenu
{
public:
	CheatMenu(Client *client);

	ClientScripting *getScript()
	{
		return m_client->getScript();
	}

	void draw(video::IVideoDriver *driver, bool show_debug);
	
	void drawHUD(video::IVideoDriver *driver, double dtime);

	void drawEntry(video::IVideoDriver *driver, std::string name,
		std::size_t column_align_index, std::size_t cheat_entry_index,
		bool is_selected, bool is_enabled,
		CheatMenuEntryType entry_type = CHEAT_MENU_ENTRY_TYPE_ENTRY);

	void selectUp();
	void selectDown();
	void selectLeft();
	void selectRight();
	void selectConfirm();

private:
	bool m_cheat_layer = false;
	int m_selected_cheat = 0;
	int m_selected_category = 0;

	int m_head_height = 20;
	int m_entry_height = 20;
	int m_entry_width = 150;
	int m_gap = 3;

	video::SColor m_bg_color = video::SColor(173, 45, 45, 68);
	video::SColor m_active_bg_color = video::SColor(210, 0, 0, 0);
	video::SColor m_font_color = video::SColor(195, 255, 255, 255);
	video::SColor m_selected_font_color = video::SColor(235, 255, 255, 255);

	FontMode fontStringToEnum(std::string str);

	Client *m_client;

	gui::IGUIFont *m_font = nullptr;
	v2u32 m_fontsize;
	
	float m_rainbow_offset = 0.0;
};
