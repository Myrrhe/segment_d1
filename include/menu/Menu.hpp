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

#ifndef MENU_HPP
#define MENU_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Animation.hpp"
#include "MenuLine.hpp"

namespace segment_d1
{
////////////////////////////////////////////////////////////
/// \brief Menu class
///
////////////////////////////////////////////////////////////

using CallbackType = std::function<MenuState(const MenuState&)>;

class Menu final : public sf::Drawable, public Animation
{
public:
    Menu();
    explicit Menu(const uint64_t id, const CallbackType &callback);
    Menu(const Menu &menu) noexcept;
    Menu &operator=(const Menu &menu);
    ~Menu() override;

    MenuState update();

    static void initialize();
private:
    uint64_t m_id;
    uint64_t m_index;
    std::vector<MenuLine> m_menuLines;

    CallbackType m_callback;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    static std::vector<Menu> s_menus;
    static Menu *s_currentMenu;
};

} // namespace segment_d1

#endif // MENU_HPP
