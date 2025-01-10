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

#ifndef GRPAHICSTATE_HPP
#define GRPAHICSTATE_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Func.hpp"
#include "Types.hpp"
#include <SFML/Graphics.hpp>

namespace segment_d1
{
////////////////////////////////////////////////////////////
/// \brief GrpahicState class
///
////////////////////////////////////////////////////////////
class GraphicState final
{
public:
    GraphicState();
    GraphicState(const sf::Vector2<float64_t> &position,
                 const sf::Color &innerColor, const sf::Color &outerColor);
    GraphicState(const GraphicState &rhs);
    ~GraphicState();
    GraphicState &operator=(const GraphicState &rhs);

    GraphicState &operator*=(const float64_t right);
    GraphicState &operator+=(const GraphicState &right);

    [[nodiscard]] GraphicState balance(const GraphicState &right,
                                       const float64_t coeff) const;

private:
    sf::Vector2<float64_t> m_position;
    sf::Color m_innerColor;
    sf::Color m_outerColor;

    friend GraphicState operator*(const GraphicState &left,
                                  const float64_t right)
    {
        return GraphicState(left.m_position * right, left.m_innerColor * right,
                            left.m_outerColor * right);
    }

    friend GraphicState operator+(const GraphicState &left,
                                  const GraphicState &right)
    {
        return GraphicState(left.m_position + right.m_position,
                            left.m_innerColor + right.m_innerColor,
                            left.m_outerColor * right.m_outerColor);
    }
};

} // namespace segment_d1

#endif // GRPAHICSTATE_HPP
