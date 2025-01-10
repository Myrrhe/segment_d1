/*
 * The engine of the watch.
 * Copyright (C) 2020  Myrrhe <email>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "menu/MenuManager.hpp"

namespace segment_d1
{

MenuManager::MenuManager()
    : m_menus({}), m_currentMenu(nullptr), m_previousMenu(nullptr)

{
    m_menus = {Menu(0, [](const MenuState &m) noexcept { return m; })};
    m_currentMenu = &(m_menus[0]);
    m_previousMenu = nullptr;
}

void MenuManager::update()
{
    if (nullptr != m_currentMenu)
    {
        const MenuState res = m_currentMenu->update();
        if (res.isNavigation())
        {
            m_previousMenu = m_currentMenu;
            m_currentMenu = &(m_menus[res.getId()]);
        }
    }
}

void MenuManager::draw(sf::RenderTarget &renderTarget,
                       const sf::RenderStates &renderStates) const
{
    if (nullptr != m_currentMenu)
    {
        renderTarget.draw(*m_currentMenu, renderStates);
    }
}

} // namespace segment_d1
