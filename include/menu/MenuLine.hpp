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

#ifndef MENULINE_HPP
#define MENULINE_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "menu/MenuState.hpp"
#include "text/TextComp.hpp"
#include <functional>

namespace segment_d1
{
////////////////////////////////////////////////////////////
/// \brief MenuLine class
///
////////////////////////////////////////////////////////////

using CallbackType = std::function<MenuState(MenuState)>;

class MenuLine final : public sf::Drawable
{
public:
    MenuLine();
    explicit MenuLine(const std::u32string &str, const sf::Font &font,
                      const uint32_t characterSize, CallbackType callback);
    MenuLine(const MenuLine &menuLine) noexcept;
    MenuLine &operator=(const MenuLine &menuLine);
    ~MenuLine() override;

private:
    ChainText m_chainText;
    TextComp m_textComp;
    CallbackType m_callback;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

} // namespace segment_d1

#endif // MENULINE_HPP
