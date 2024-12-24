/*
Dragonfire
Copyright (C) 2020 Maintainer_(Ivan Shkatov) <ivanskatov672@gmail.com>

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
#ifndef NEWMENU_H
#define NEWMENU_H

#include <irrlicht.h>
#include "gui/modalMenu.h"
#include <vector>
#include "script/scripting_client.h"
#include "client/client.h"
#include "client/fontengine.h"
#include <codecvt> 
#include <locale> 
#include "log.h"


using namespace irr;
using namespace gui;

#define GET_SCRIPT_POINTER                                                     \
    ClientScripting *script = m_client->getScript();                         \
    if (!script || !script->m_cheats_loaded)                                 \
        return;

#define GET_SCRIPT_POINTER_BOOL                                                     \
    ClientScripting *script = m_client->getScript();                         \
    if (!script || !script->m_cheats_loaded)                                 \
        return true;     

class NewMenu: public IGUIElement
{
public:
    NewMenu(gui::IGUIEnvironment* env, gui::IGUIElement* parent, s32 id, IMenuManager* menumgr, Client *client);

    void create();
    void close();

    virtual bool OnEvent(const irr::SEvent& event);
    virtual void draw() override;

    bool isOpen() { return m_is_open; }

    ~NewMenu();

private:
    core::rect<s32> createRect(s32 x, s32 y);
    std::vector<core::rect<s32>> categoryRects;
    core::vector2d<s32> offset; 
    IMenuManager* m_menumgr; 
    bool isDragging;
    core::vector2d<s32> rectPosition; 
    const int rectWidth = 200; 
    const int rectHeight = 40;
    bool m_is_open = false; 
    int draggedRectIndex;
    std::vector<bool> selectedCategory;
    std::vector<std::vector<core::rect<s32>>> subCategoryRects;
    std::vector<std::vector<video::SColor>> subCategoryColors;
    Client* m_client;
    bool m_rectsCreated = false;
    

    video::SColor outlineColor = video::SColor(255, 255, 255, 255);
};

#endif