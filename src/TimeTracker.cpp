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

#include "TimeTracker.hpp"

namespace segment_d1
{
TimeTracker::TimeTracker() : m_watch(0.0) {}

TimeTracker::TimeTracker(const TimeTracker &timeTracker) = default;

TimeTracker::~TimeTracker() = default;

TimeTracker &TimeTracker::operator=(const TimeTracker &right) = default;

float64_t TimeTracker::getWatch() const
{
    return m_watch;
}

void TimeTracker::incrementWatch(const float64_t delta)
{
    m_watch += delta;
}

void TimeTracker::resetWatch()
{
    m_watch = 0.0;
}

} // namespace segment_d1
