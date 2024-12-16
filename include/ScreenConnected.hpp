/*
 * <one line to give the library's name and an idea of what it does.>
 * Copyright (C) 2017  <copyright holder> <email>
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

#ifndef SCREENCONNECTED_HPP
#define SCREENCONNECTED_HPP
#include "Types.hpp"
#include <SFML/Graphics.hpp>
#include <cstdint>

namespace segment_d1
{

class ScreenConnected final
{
public:
    ScreenConnected();
    ScreenConnected(const std::wstring &newName,
                    const sf::Rect<float32_t> &newBounds,
                    const uint32_t newRefreshRate,
                    const sf::Vector2<uint32_t> &newDpi);
    ScreenConnected(const ScreenConnected &right);
    ~ScreenConnected();
    ScreenConnected &operator=(const ScreenConnected &right);

    static void initialize();
    static void deleteAll();

    std::wstring name;
    // dimension in virtual screen space coordinates
    sf::Rect<float32_t> bounds;
    uint32_t refreshRate;
    sf::Vector2<uint32_t> dpi;
};

} // namespace segment_d1

#endif // SCREENCONNECTED_HPP
