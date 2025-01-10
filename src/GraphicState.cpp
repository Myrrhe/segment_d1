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

#include "GraphicState.hpp"

namespace segment_d1
{

GraphicState::GraphicState()
    : m_position(0.0, 0.0), m_innerColor(sf::Color(0, 0, 0, 0)),
      m_outerColor(sf::Color(0, 0, 0, 0))
{
}

GraphicState::GraphicState(const sf::Vector2<float64_t> &position,
                           const sf::Color &innerColor,
                           const sf::Color &outerColor)
    : m_position(position), m_innerColor(innerColor), m_outerColor(outerColor)
{
}

GraphicState::GraphicState(const GraphicState &rhs) = default;

GraphicState::~GraphicState() = default;

GraphicState &GraphicState::operator=(const GraphicState &rhs) = default;

GraphicState &GraphicState::operator*=(const float64_t right)
{
    return *this = *this * right;
}

GraphicState &GraphicState::operator+=(const GraphicState &right)
{
    return *this = *this + right;
}

GraphicState GraphicState::balance(const GraphicState &right,
                                   const float64_t coeff) const
{
    return GraphicState(m_position + (right.m_position - m_position) * coeff,
                        Func::colorBalance(m_innerColor, right.m_innerColor,
                                           coeff, Interp::LIN),
                        Func::colorBalance(m_outerColor, right.m_outerColor,
                                           coeff, Interp::LIN));
}

} // namespace segment_d1
