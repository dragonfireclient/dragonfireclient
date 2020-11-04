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

#include "script/scripting_client.h"
#include "client/client.h"
#include "client/fontengine.h"
#include "cheatMenu.h"
#include <cstddef>

FontMode CheatMenu::fontStringToEnum(std::string str) {
	if (str == "FM_Standard") 
		return FM_Standard;
	else if (str == "FM_Mono")
		return FM_Mono;
	else if (str == "FM_Fallback")
		return FM_Fallback;
	else if (str == "FM_Simple")
		return FM_Simple;
	else if (str == "FM_SimpleMono")
		return FM_SimpleMono;
	else if (str == "FM_MaxMode")
		return FM_MaxMode;
	else if (str == "FM_Unspecified")
		return FM_Unspecified;
	else
		return FM_Standard;
}

CheatMenu::CheatMenu(Client *client) : m_client(client)
{
	FontMode fontMode = fontStringToEnum(g_settings->get("cheat_menu_font"));
	v3f bg_color, active_bg_color, font_color, selected_font_color;

	bg_color = g_settings->getV3F("cheat_menu_bg_color");
	active_bg_color = g_settings->getV3F("cheat_menu_active_bg_color");
	font_color = g_settings->getV3F("cheat_menu_font_color");
	selected_font_color = g_settings->getV3F("cheat_menu_selected_font_color");

	m_bg_color = video::SColor(g_settings->getU32("cheat_menu_bg_color_alpha"), 
							   bg_color.X, bg_color.Y, bg_color.Z);
	
	m_active_bg_color = video::SColor(g_settings->getU32("cheat_menu_active_bg_color_alpha"), 
							          active_bg_color.X, active_bg_color.Y, active_bg_color.Z);

	m_font_color = video::SColor(g_settings->getU32("cheat_menu_font_color_alpha"),
								 font_color.X, font_color.Y, font_color.Z);

	m_selected_font_color = video::SColor(g_settings->getU32("cheat_menu_selected_font_color_alpha"),
										  selected_font_color.X, selected_font_color.Y, selected_font_color.Z);
	
	m_font = g_fontengine->getFont(FONT_SIZE_UNSPECIFIED, fontMode);

	if (!m_font) {
		errorstream << "CheatMenu: Unable to load font" << std::endl;
	} else {
		core::dimension2d<u32> dim = m_font->getDimension(L"M");
		m_fontsize = v2u32(dim.Width, dim.Height);
		m_font->grab();
	}
	m_fontsize.X = MYMAX(m_fontsize.X, 1);
	m_fontsize.Y = MYMAX(m_fontsize.Y, 1);
}

void CheatMenu::drawEntry(video::IVideoDriver *driver, std::string name, int number,
		bool selected, bool active, CheatMenuEntryType entry_type)
{
	int x = m_gap, y = m_gap, width = m_entry_width, height = m_entry_height;
	video::SColor *bgcolor = &m_bg_color, *fontcolor = &m_font_color;
	if (entry_type == CHEAT_MENU_ENTRY_TYPE_HEAD) {
		bgcolor = &m_active_bg_color;
		height = m_head_height;
	} else {
		bool is_category = entry_type == CHEAT_MENU_ENTRY_TYPE_CATEGORY;
		y += m_gap + m_head_height +
		     (number + (is_category ? 0 : m_selected_category)) *
				     (m_entry_height + m_gap);
		x += (is_category ? 0 : m_gap + m_entry_width);
		if (active)
			bgcolor = &m_active_bg_color;
		if (selected)
			fontcolor = &m_selected_font_color;
	}
	driver->draw2DRectangle(*bgcolor, core::rect<s32>(x, y, x + width, y + height));
	if (selected)
		driver->draw2DRectangleOutline(
				core::rect<s32>(x - 1, y - 1, x + width, y + height),
				*fontcolor);
	int fx = x + 5, fy = y + (height - m_fontsize.Y) / 2;
	core::rect<s32> fontbounds(
			fx, fy, fx + m_fontsize.X * name.size(), fy + m_fontsize.Y);
	m_font->draw(name.c_str(), fontbounds, *fontcolor, false, false);
}

void CheatMenu::draw(video::IVideoDriver *driver, bool show_debug)
{
	CHEAT_MENU_GET_SCRIPTPTR

	if (!show_debug)
		drawEntry(driver, "Dragonfireclient", 0, false, false,
				CHEAT_MENU_ENTRY_TYPE_HEAD);
	int category_count = 0;
	for (auto category = script->m_cheat_categories.begin();
			category != script->m_cheat_categories.end(); category++) {
		bool is_selected = category_count == m_selected_category;
		drawEntry(driver, (*category)->m_name, category_count, is_selected, false,
				CHEAT_MENU_ENTRY_TYPE_CATEGORY);
		if (is_selected && m_cheat_layer) {
			int cheat_count = 0;
			for (auto cheat = (*category)->m_cheats.begin();
					cheat != (*category)->m_cheats.end(); cheat++) {
				drawEntry(driver, (*cheat)->m_name, cheat_count,
						cheat_count == m_selected_cheat,
						(*cheat)->is_enabled());
				cheat_count++;
			}
		}
		category_count++;
	}
}

void CheatMenu::drawHUD(video::IVideoDriver *driver, double dtime)
{
	CHEAT_MENU_GET_SCRIPTPTR
	
	m_rainbow_offset += dtime;

	m_rainbow_offset = fmod(m_rainbow_offset, 6.0f);
	
	std::vector<std::string> enabled_cheats;
	
	int cheat_count = 0;
	
	for (auto category = script->m_cheat_categories.begin(); category != script->m_cheat_categories.end(); category++) {
		for (auto cheat = (*category)->m_cheats.begin(); cheat != (*category)->m_cheats.end(); cheat++) {
			if ((*cheat)->is_enabled()) {
				enabled_cheats.push_back((*cheat)->m_name);
				cheat_count++;
			}
		}
	}
	
	if (enabled_cheats.empty())
		return;
	
	std::vector<video::SColor> colors;
	
	for (int i = 0; i < cheat_count; i++) {
		video::SColor color;
		f32 h = (f32)i * 2.0f / (f32)cheat_count - m_rainbow_offset;
		if (h < 0)
			h = 6.0f + h;
		f32 x = (1 - fabs(fmod(h, 2.0f) - 1.0f)) * 255.0f;
		switch((int)h) {
		case 0:
			color = video::SColor(255, 255, x, 0); break;
		case 1:
			color = video::SColor(255, x, 255, 0); break;
		case 2:
			color = video::SColor(255, 0, 255, x); break;
		case 3:
			color = video::SColor(255, 0, x, 255); break;
		case 4:
			color = video::SColor(255, x, 0, 255); break;
		case 5:
			color = video::SColor(255, 255, 0, x); break;
		}
		colors.push_back(color);
	}
	
	core::dimension2d<u32> screensize = driver->getScreenSize();
	
	u32 y = 5;
	
	int i = 0;
	for (std::string cheat : enabled_cheats) {
		core::dimension2d<u32> dim = m_font->getDimension(utf8_to_wide(cheat).c_str());
		u32 x = screensize.Width - 5 - dim.Width;
		
		core::rect<s32> fontbounds(x, y, x + dim.Width, y + dim.Height);
		m_font->draw(cheat.c_str(), fontbounds, colors[i], false, false);
		
		y += dim.Height;
		i++;
	}
}

void CheatMenu::selectUp()
{
	CHEAT_MENU_GET_SCRIPTPTR

	int max = (m_cheat_layer ? script->m_cheat_categories[m_selected_category]
								  ->m_cheats.size()
				 : script->m_cheat_categories.size()) -
		  1;
	int *selected = m_cheat_layer ? &m_selected_cheat : &m_selected_category;
	--*selected;
	if (*selected < 0)
		*selected = max;
}

void CheatMenu::selectDown()
{
	CHEAT_MENU_GET_SCRIPTPTR

	int max = (m_cheat_layer ? script->m_cheat_categories[m_selected_category]
								  ->m_cheats.size()
				 : script->m_cheat_categories.size()) -
		  1;
	int *selected = m_cheat_layer ? &m_selected_cheat : &m_selected_category;
	++*selected;
	if (*selected > max)
		*selected = 0;
}

void CheatMenu::selectRight()
{
	if (m_cheat_layer)
		return;
	m_cheat_layer = true;
	m_selected_cheat = 0;
}

void CheatMenu::selectLeft()
{
	if (!m_cheat_layer)
		return;
	m_cheat_layer = false;
}

void CheatMenu::selectConfirm()
{
	CHEAT_MENU_GET_SCRIPTPTR

	if (m_cheat_layer)
		script->toggle_cheat(script->m_cheat_categories[m_selected_category]
						     ->m_cheats[m_selected_cheat]);
}
