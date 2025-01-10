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

#ifndef ANIMATION_HPP
#define ANIMATION_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Enums.hpp"
#include "GraphicState.hpp"
#include "TimeTracker.hpp"
#include <SFML/Graphics.hpp>

namespace segment_d1
{
////////////////////////////////////////////////////////////
/// \brief Animation class
///
////////////////////////////////////////////////////////////
class Animation : public TimeTracker
{
public:
    Animation();
    Animation(const Interp intert, const float64_t duration,
              const GraphicState &start, const GraphicState &end);
    Animation(const Animation &animation);
    ~Animation() override;
    Animation &operator=(const Animation &rhs);
    GraphicState getCurrentGraphicState() const;

private:
    Interp m_interp;
    float64_t m_duration;
    GraphicState m_start;
    GraphicState m_end;
};

} // namespace segment_d1

#endif // ANIMATION_HPP
