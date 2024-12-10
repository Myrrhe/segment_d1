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

#ifndef LOGGER_HPP
#define LOGGER_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <iostream>
#include <mutex>


namespace segment_d1
{
////////////////////////////////////////////////////////////
/// \brief Logger class
///
////////////////////////////////////////////////////////////
class Logger final
{
public:
    Logger();
    ~Logger();

    template<typename T>
    void info(const T &message)
    {
        const std::scoped_lock lock(mtx);
        std::cout << getCurrentTime() << " - " << message << "\n";
    }

private:
    std::mutex mtx;

    std::string getCurrentTime() const;
};

} // namespace segment_d1

#endif // LOGGER_HPP
