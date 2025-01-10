/*
 * A basic function library.
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

#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <cstdint>
#include <string>

namespace segment_d1
{

constexpr uint32_t MaxColor = 255;
static constexpr std::string_view ImgExtension = ".png";
static const std::string EmptyStr;
static const std::u32string EmptyStr32;

} // namespace segment_d1

#endif // CONSTANTS_HPP
