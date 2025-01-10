/*
 * This file manage the differences between several OS.
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

#ifndef MENUMANAGER_HPP
#define MENUMANAGER_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Singleton.hpp"
#include "menu/Menu.hpp"
#include "menu/MenuState.hpp"

namespace segment_d1
{
////////////////////////////////////////////////////////////
/// \brief MenuManager class
///
////////////////////////////////////////////////////////////

class MenuManager final : public Singleton<MenuManager>
{
    friend class Singleton<MenuManager>;

public:
    void update();
    void draw(sf::RenderTarget &renderTarget,
              const sf::RenderStates &renderStates) const;

private:
    MenuManager();

    std::vector<Menu> m_menus;
    Menu *m_currentMenu;
    Menu *m_previousMenu;
};

} // namespace segment_d1

#endif // MENUMANAGER_HPP
