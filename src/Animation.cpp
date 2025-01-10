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

#include "Animation.hpp"

namespace segment_d1
{
Animation::Animation()
    : TimeTracker(), m_interp(Interp::LIN), m_duration(0.0),
      m_start(GraphicState()), m_end(GraphicState())
{
}

Animation::Animation(const Interp intert, const float64_t duration,
                     const GraphicState &start, const GraphicState &end)
    : TimeTracker(), m_interp(intert), m_duration(duration), m_start(start),
      m_end(end)
{
}

Animation::Animation(const Animation &animation) = default;

Animation::~Animation() = default;

Animation &Animation::operator=(const Animation &rhs) = default;

GraphicState Animation::getCurrentGraphicState() const
{
    return m_start.balance(
        m_end, Func::getCoeff(getWatch(), m_duration, m_interp, true));
}

} // namespace segment_d1
