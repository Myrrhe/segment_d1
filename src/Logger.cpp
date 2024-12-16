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

#include "Logger.hpp"

namespace segment_d1
{
Logger::Logger() : mtx(std::mutex()) {}

std::string Logger::getCurrentTime() const
{
    const auto now = std::chrono::system_clock::now();
    const std::time_t timeTNow = std::chrono::system_clock::to_time_t(now);
    std::tm localTime;
    const errno_t err = ::localtime_s(&localTime, &timeTNow);
    std::string res = "error_time";
    if (0 == err)
    {
        const std::size_t bufferSize = 100;
        res = std::string(bufferSize, '\0');
        const std::size_t written = std::strftime(
            res.data(), bufferSize, "%Y-%m-%d %H:%M:%S", &localTime);
        if (written > 0)
        {
            res.resize(written);
        }
        else
        {
            res.clear();
        }
    }
    return res;
}

Logger::~Logger() = default;

} // namespace segment_d1
