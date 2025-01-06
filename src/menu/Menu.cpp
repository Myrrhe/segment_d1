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

#include "menu/Menu.hpp"

namespace segment_d1
{
std::vector<Menu> Menu::s_menus;
Menu *Menu::s_currentMenu;

Menu::Menu() : m_id(0), m_menuLines({}) {}

Menu::Menu(const uint64_t id) : m_id(id), m_menuLines({}) {}

Menu::Menu(const Menu &menu) noexcept = default;

Menu &Menu::operator=(const Menu &menu) = default;

Menu::~Menu() = default;

void Menu::update()
{

}

void Menu::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (const auto &menuLine : m_menuLines)
    {
        target.draw(menuLine, states);
    }
}

void Menu::initialize()
{
    s_menus = {Menu(0)};
    s_currentMenu = &(s_menus[0]);
}
} // namespace segment_d1
