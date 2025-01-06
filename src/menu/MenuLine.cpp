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

#include "menu/MenuLine.hpp"

namespace segment_d1
{
MenuLine::MenuLine() : m_chainText(""), m_textComp(), m_callback(nullptr) {};

MenuLine::MenuLine(const std::u32string &str, const sf::Font &font,
                   const uint32_t characterSize, CallbackType callback)
    : m_chainText(str), m_textComp({&m_chainText}, font, characterSize),
      m_callback(callback)
{
}

MenuLine::MenuLine(const MenuLine &menuLine) noexcept = default;

MenuLine &MenuLine::operator=(const MenuLine &menuLine) = default;

MenuLine::~MenuLine() = default;

void MenuLine::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_textComp, states);
}

} // namespace segment_d1
