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

#ifndef TIMETRACKER_HPP
#define TIMETRACKER_HPP
#include "Types.hpp"

namespace segment_d1
{

class TimeTracker
{
public:
    TimeTracker();
    TimeTracker(const TimeTracker &timeTracker);
    virtual ~TimeTracker();
    TimeTracker &operator=(const TimeTracker &right);
protected:
    [[nodiscard]] float64_t getWatch() const;
    void incrementWatch(const float64_t delta);
    void resetWatch();
private:
    float64_t m_watch;
};

} // namespace segment_d1

#endif // TIMETRACKER_HPP
