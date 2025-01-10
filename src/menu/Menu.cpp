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
#include "WindowManager.hpp"

namespace segment_d1
{
std::vector<Menu> Menu::s_menus;
Menu *Menu::s_currentMenu;

Menu::Menu() : m_id(0), m_index(0), m_menuLines({}), m_callback(nullptr) {}

Menu::Menu(const uint64_t id, const CallbackType &callback)
    : m_id(id), m_index(0), m_menuLines({}), m_callback(callback)
{
}

Menu::Menu(const Menu &menu) noexcept = default;

Menu &Menu::operator=(const Menu &menu) = default;

Menu::~Menu() = default;

MenuState Menu::update()
{
    auto res = MenuState(false, m_index);
    if (WindowManager::isKeyPressed())
    {
        if (sf::Keyboard::Key::Up == WindowManager::getKeyPressed())
        {
            m_index = (m_index + 1) % m_menuLines.size();
        }
        else if (sf::Keyboard::Key::Down == WindowManager::getKeyPressed())
        {
            m_index = ((m_index + m_menuLines.size()) - 1) % m_menuLines.size();
        }
        else if (sf::Keyboard::Key::Enter == WindowManager::getKeyPressed())
        {
            res = m_menuLines[m_index](res);
        }
        else if (sf::Keyboard::Key::Escape == WindowManager::getKeyPressed())
        {
            // TODO
        }
        else
        {
            // Nothing to do
        }
    }
    return res;
}

void Menu::draw(sf::RenderTarget &target,
                sf::RenderStates states) const // NOSONAR
{
    for (const auto &menuLine : m_menuLines)
    {
        target.draw(menuLine, states);
    }
}

void Menu::initialize()
{
    s_menus = {Menu(0, [](const MenuState &m) noexcept { return m; })};
    s_currentMenu = &(s_menus[0]);
}
} // namespace segment_d1
