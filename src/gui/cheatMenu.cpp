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

#include "cheatMenu.h"
#include "script/scripting_client.h"
#include "client/client.h"
#include "client/fontengine.h"
#include <cstddef>

CheatMenu::CheatMenu(Client *client) : m_client(client)
{
	m_font = g_fontengine->getFont(FONT_SIZE_UNSPECIFIED, FM_Mono);

	if (!m_font) {
		errorstream << "CheatMenu: Unable to load fallback font" << std::endl;
	} else {
		core::dimension2d<u32> dim = m_font->getDimension(L"M");
		m_fontsize = v2u32(dim.Width, dim.Height);
		m_font->grab();
	}
	m_fontsize.X = MYMAX(m_fontsize.X, 1);
	m_fontsize.Y = MYMAX(m_fontsize.Y, 1);
}

void CheatMenu::drawEntry(video::IVideoDriver *driver, std::string name,
		std::size_t column_align_index, std::size_t cheat_entry_index,
		bool is_selected, bool is_enabled, CheatMenuEntryType entry_type)
{
	int x = m_gap, y = m_gap, width = m_entry_width, height = m_entry_height;
	video::SColor *bgcolor = &m_bg_color, *fontcolor = &m_font_color;

	// Align with correct column.
	x += m_gap + column_align_index * (m_entry_width + m_gap);

	if (is_selected)
		fontcolor = &m_selected_font_color;
	if (is_enabled)
		bgcolor = &m_active_bg_color;

	switch (entry_type)
	{
	case CHEAT_MENU_ENTRY_TYPE_HEAD:
		height = m_head_height;
		break;
	case CHEAT_MENU_ENTRY_TYPE_CATEGORY:
		y += m_head_height + m_gap;
		break;
	case CHEAT_MENU_ENTRY_TYPE_ENTRY:
		y += m_head_height + (cheat_entry_index + 1) * (m_entry_height + m_gap);
		break;
	default:
		// TODO log an error or something.
		break;
	}

	driver->draw2DRectangle(*bgcolor, core::rect<s32>(x, y, x + width, y + height));
	if (is_selected)
		driver->draw2DRectangleOutline(
				core::rect<s32>(x - 1, y - 1, x + width, y + height),
				*fontcolor);
	int fx = x + 5, fy = y + (height - m_fontsize.Y) / 2;
	core::rect<s32> fontbounds(
			fx, fy, fx + m_fontsize.X * name.size(), fy + m_fontsize.Y);
	m_font->draw(name.c_str(), fontbounds, *fontcolor, false, false);
}

void CheatMenu::draw(video::IVideoDriver *driver, bool show_debug)

	ClientScripting *script{ getScript() };
	if (!script || !script->m_cheats_loaded)

	if (!show_debug)
		drawEntry(driver, "Dragonfireclient", 0, 0, false, false,
				CHEAT_MENU_ENTRY_TYPE_HEAD);
	int category_count = 0;
	for (const auto &menu_item : m_cheat_categories) {
		bool is_selected = category_count == m_selected_category;
		drawEntry(driver, menu_item.m_name, category_count, 0, is_selected,
				false, CHEAT_MENU_ENTRY_TYPE_CATEGORY);
		if (is_selected && m_cheat_layer) {
			int cheat_count = 0;
			for (const auto &sub_menu_item : menu_item.m_cheats) {
				drawEntry(driver, sub_menu_item.m_name, category_count, cheat_count,
						cheat_count == m_selected_cheat,
						sub_menu_item.is_enabled());
				cheat_count++;
			}
		}
		category_count++;
	}
}

void CheatMenu::selectLeft()
{
	CHEAT_MENU_GET_SCRIPTPTR

	int max = script->m_cheat_categories.size() - 1;
	int *selected = &m_selected_category;
	--*selected;
	if (*selected < 0)
		*selected = max;
}

void CheatMenu::selectRight()
{
	CHEAT_MENU_GET_SCRIPTPTR

	int max = script->m_cheat_categories.size() - 1;
	int *selected = &m_selected_category;
	++*selected;
	if (*selected > max)
		*selected = 0;
}

void CheatMenu::selectDown()
{
	CHEAT_MENU_GET_SCRIPTPTR

	m_cheat_layer = true;

	int max = script->m_cheat_categories[m_selected_category]->m_cheats.size();
	int *selected = &m_selected_cheat;
	++*selected;
	if (*selected > max) {
		*selected = 1;
	}
}

void CheatMenu::selectUp()
{
	if (!m_cheat_layer) {
		return;
	}

	CHEAT_MENU_GET_SCRIPTPTR

	int *selected = &m_selected_cheat;
	--*selected;

	if (*selected < 0) {
		m_cheat_layer = false;
		*selected = 1;
	}
}

void CheatMenu::selectConfirm()
{
	CHEAT_MENU_GET_SCRIPTPTR

	if (m_cheat_layer)
		script->toggle_cheat(script->m_cheat_categories[m_selected_category]
						     ->m_cheats[m_selected_cheat]);
}
