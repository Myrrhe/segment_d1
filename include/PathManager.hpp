/*
 * This file manager the path needed to find the assets of the application.
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

#ifndef PATHMANAGER_HPP
#define PATHMANAGER_HPP
#include "StaticObject.hpp"
#include <cstdint>
#include <string>

namespace segment_d1
{

class PathManager final : public StaticObject
{
public:
    enum class Dir : uint64_t
    {
        ROOT,
        DAT,
        IMG,
        SOUND,
        FONT,
        SCREENSHOT,
    };

    static std::string getPath(const Dir dir);
    static void setPath(const std::string_view &argv0);
    static void rewrite();
    static void read();
    static void initialize();

    static const std::string PathName;
    static const std::string PathExtension;

    static const std::string FolderDat;
    static const std::string FolderImg;
    static const std::string FolderSound;
    static const std::string FolderFont;
    static const std::string FolderScreenshot;

    static const std::string KeyPath;

private:
    static std::string path;
    static std::string pathVar;
    static std::string exeName;
};

} // namespace segment_d1

#endif // PATHMANAGER_HPP
