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
#include "NewMenu.h"
#include <iostream>


NewMenu::NewMenu(gui::IGUIEnvironment* env, 
    gui::IGUIElement* parent, 
    s32 id, IMenuManager* menumgr, 
    Client* client)
    : IGUIElement(gui::EGUIET_ELEMENT, env, parent, id, 
    core::rect<s32>(0, 0, 10, 10)), 
    m_menumgr(menumgr), isDragging(false), draggedRectIndex(-1),
    m_client(client), m_rectsCreated(false) 
{    

    infostream << "[NEWMENU] Successfully created" << std::endl;
}

NewMenu::~NewMenu()
{
}

void NewMenu::create()
{
    GET_SCRIPT_POINTER

    if (script->m_cheat_categories.empty()) {
        std::cout << "No categories available." << std::endl;
        return;
    }
    
    if (!m_rectsCreated) {
        for (size_t i = 0; i < script->m_cheat_categories.size(); i++) {
            categoryRects.push_back(createRect(20, 20 + i * (rectHeight + 10))); 
            selectedCategory.push_back(false); 
            subCategoryRects.push_back(std::vector<core::rect<s32>>());
        }
        m_rectsCreated = true; 
    }

    subCategoryColors.resize(script->m_cheat_categories.size());

    for (size_t i = 0; i < script->m_cheat_categories.size(); ++i) {
        subCategoryColors[i].resize(script->m_cheat_categories[i]->m_cheats.size(), video::SColor(150, 100, 100, 100)); 
    }

    core::rect<s32> screenRect(0, 0, 
        Environment->getVideoDriver()->getScreenSize().Width, 
        Environment->getVideoDriver()->getScreenSize().Height);
    setRelativePosition(screenRect);

    IGUIElement::setVisible(true);
    Environment->setFocus(this);
    m_menumgr->createdMenu(this);
    m_is_open = true;
}

void NewMenu::close()
{
    Environment->removeFocus(this);
    m_menumgr->deletingMenu(this);
    IGUIElement::setVisible(false);
    m_is_open = false;
}

core::rect<s32> NewMenu::createRect(s32 x, s32 y) {
    return core::rect<s32>(x, y, x + rectWidth, y + rectHeight);
}

bool NewMenu::OnEvent(const irr::SEvent& event) 
{
    if (!m_is_open) {
        return false;
    }

    GET_SCRIPT_POINTER_BOOL  
    if (event.EventType == irr::EET_KEY_INPUT_EVENT)
    {
        if (event.KeyInput.Key == KEY_ESCAPE)
        {
            close();
            return true; 
        }
    } 
    if (event.EventType == irr::EET_MOUSE_INPUT_EVENT) {
        if (event.MouseInput.Event == irr::EMIE_LMOUSE_PRESSED_DOWN) {
            for (size_t i = 0; i < categoryRects.size(); ++i) {
                if (categoryRects[i].isPointInside(core::vector2d<s32>(event.MouseInput.X, event.MouseInput.Y))) {
                    isDragging = true;
                    draggedRectIndex = i;
                    offset = core::vector2d<s32>(event.MouseInput.X - categoryRects[i].UpperLeftCorner.X, event.MouseInput.Y - categoryRects[i].UpperLeftCorner.Y);
                    selectedCategory[i] = !selectedCategory[i]; 

                    if (selectedCategory[i]) {
                        subCategoryRects[i].clear();
                        int subCategoryCount = script->m_cheat_categories[i]->m_cheats.size();
                        for (int j = 0; j < subCategoryCount; ++j) { 
                            subCategoryRects[i].push_back(createRect(categoryRects[i].UpperLeftCorner.X, categoryRects[i].LowerRightCorner.Y + j * (rectHeight)));
                        }
                    } else {
                        subCategoryRects[i].clear(); 
                    }
                    return true; 
                }
            }

            for (size_t i = 0; i < subCategoryRects.size(); ++i) {
                if (selectedCategory[i]) {
                    for (size_t j = 0; j < subCategoryRects[i].size(); ++j) {
                        if (subCategoryRects[i][j].isPointInside(core::vector2d<s32>(event.MouseInput.X, event.MouseInput.Y))) {
                            script->toggle_cheat(script->m_cheat_categories[i]->m_cheats[j]);
                            return true; 
                        }
                    }
                }
            }
            return false; 
        }
        else if (event.MouseInput.Event == irr::EMIE_LMOUSE_LEFT_UP) {
            isDragging = false;
            draggedRectIndex = -1;
            return true;
        }
        else if (event.MouseInput.Event == irr::EMIE_MOUSE_MOVED && isDragging && draggedRectIndex != -1) {
            s32 screenWidth = Environment->getVideoDriver()->getScreenSize().Width;
            s32 screenHeight = Environment->getVideoDriver()->getScreenSize().Height;

            s32 newX = event.MouseInput.X - offset.X;
            s32 newY = event.MouseInput.Y - offset.Y;

            if (newX < 0) {
                newX = 0;
            } else if (newX + rectWidth > screenWidth) {
                newX = screenWidth - rectWidth;
            }

            if (newY < 0) {
                newY = 0;
            } else if (newY + rectHeight > screenHeight) {
                newY = screenHeight - rectHeight;
            }

            categoryRects[draggedRectIndex].UpperLeftCorner.X = newX;
            categoryRects[draggedRectIndex].UpperLeftCorner.Y = newY;
            categoryRects[draggedRectIndex].LowerRightCorner.X = categoryRects[draggedRectIndex].UpperLeftCorner.X + rectWidth;
            categoryRects[draggedRectIndex].LowerRightCorner.Y = categoryRects[draggedRectIndex].UpperLeftCorner.Y + rectHeight;

            for (size_t j = 0; j < subCategoryRects[draggedRectIndex].size(); ++j) {
                subCategoryRects[draggedRectIndex][j].UpperLeftCorner.X = categoryRects[draggedRectIndex].UpperLeftCorner.X;
                subCategoryRects[draggedRectIndex][j].UpperLeftCorner.Y = categoryRects[draggedRectIndex].LowerRightCorner.Y + j * (rectHeight);
                subCategoryRects[ draggedRectIndex][j].LowerRightCorner.X = subCategoryRects[draggedRectIndex][j].UpperLeftCorner.X + rectWidth;
                subCategoryRects[draggedRectIndex][j].LowerRightCorner.Y = subCategoryRects[draggedRectIndex][j].UpperLeftCorner.Y + rectHeight;
            }
            return true;
        }
    }

    return Parent ? Parent->OnEvent(event) : false; 
}

void NewMenu::draw() 
{
    GET_SCRIPT_POINTER

    video::IVideoDriver* driver = Environment->getVideoDriver();
    gui::IGUIFont* font = g_fontengine->getFont(FONT_SIZE_UNSPECIFIED, FM_Standard);
    
    if (m_is_open) {
        for (size_t i = 0; i < categoryRects.size(); ++i) {
            const auto& rect = categoryRects[i];
            video::SColor color = selectedCategory[i] ? video::SColor(210, 0, 0, 0) : video::SColor(173, 45, 45, 68);
            driver->draw2DRectangle(color, rect);

            video::SColor outlineColor(255, 255, 255, 255); 
            driver->draw2DRectangleOutline(core::rect<s32>(rect.UpperLeftCorner.X - 1, rect.UpperLeftCorner.Y - 1, rect.LowerRightCorner.X + 1, rect.LowerRightCorner.Y + 1), outlineColor);

            const std::string& categoryName = script->m_cheat_categories[i]->m_name;
            std::wstring wCategoryName = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(categoryName);

            core::dimension2d<u32> textSizeU32 = font->getDimension(wCategoryName.c_str());
            core::dimension2d<s32> textSize(textSizeU32.Width, textSizeU32.Height);

            s32 textX = rect.UpperLeftCorner.X + (rect.getWidth() - textSize.Width) / 2;
            s32 textY = rect.UpperLeftCorner.Y + (rect.getHeight() - textSize.Height) / 2;

            font->draw(wCategoryName.c_str(), core::rect<s32>(textX, textY, textX + textSize.Width, textY + textSize.Height), video::SColor(255, 255, 255, 255));
        }

        for (size_t i = 0; i < subCategoryRects.size(); ++i) {
            if (selectedCategory[i]) {
                for (size_t j = 0; j < subCategoryRects[i].size(); ++j) {
                    const auto& subRect = subCategoryRects[i][j];
                    driver->draw2DRectangle(subCategoryColors[i][j], subRect);
                    driver->draw2DRectangleOutline(core::rect<s32>(subRect.UpperLeftCorner.X - 1, subRect.UpperLeftCorner.Y - 1, subRect.LowerRightCorner.X + 1, subRect.LowerRightCorner.Y + 1), outlineColor);

                    const auto& functionName = script->m_cheat_categories[i]->m_cheats[j]->m_name;
                    std::wstring wFunctionName = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(functionName);
                    if (script->m_cheat_categories[i]->m_cheats[j]->is_enabled()) {
                        subCategoryColors[i][j] = video::SColor(210, 0, 0, 0);
                    } else {
                        subCategoryColors[i][j] = video::SColor(150, 100, 100, 100);
                    }
                    core::dimension2d<u32> functionTextSizeU32 = font->getDimension(wFunctionName.c_str());
                    core::dimension2d<s32> functionTextSize(functionTextSizeU32.Width, functionTextSizeU32.Height);

                    s32 functionTextX = subRect.UpperLeftCorner.X + (subRect.getWidth() - functionTextSize.Width) / 2;
                    s32 functionTextY = subRect.UpperLeftCorner.Y + (subRect.getHeight() - functionTextSize.Height) / 2;

                    font->draw(wFunctionName.c_str(), core::rect<s32>(functionTextX, functionTextY, functionTextX + functionTextSize.Width, functionTextY + functionTextSize.Height), video::SColor(255, 255, 255, 255));
                }
            }
        }
    }
}