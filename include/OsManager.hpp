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

#ifndef OSMANAGER_HPP
#define OSMANAGER_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "StaticObject.hpp"
#include "Types.hpp"
#include <SFML/Graphics.hpp>
#include <string>

#ifdef __linux__
#define GNU_CONST [[gnu::const]]
#define GNU_PURE [[gnu::pure]]
#elif _WIN32
#define GNU_CONST
#define GNU_PURE
#elif _OSX

#endif // __linux__

namespace segment_d1
{
////////////////////////////////////////////////////////////
/// \brief Static class for the OS
///
////////////////////////////////////////////////////////////
class OsManager final : public StaticObject
{
public:
    static sf::Vector2<uint64_t> getMonitorSize();

    static float64_t getWallTime();
    static float64_t getCpuTime();
    static int32_t createDir(const std::string &str);
    static bool sleep(const float64_t nbUsec);
    static void initiateCoreFile();

    static uint64_t getPhysicalMemoryUsed();
    static uint64_t getPhysicalMemoryUsedProcess();

    static uint64_t getMaxRAM();

    static const char SlashC;
    static const std::string Slash;

    static const std::string StrIcon;

    static const uint32_t WidthIcon;
    static const uint32_t HeightIcon;

private:
    static uint64_t maxRAM;
};

} // namespace segment_d1

#endif // OSMANAGER_HPP
