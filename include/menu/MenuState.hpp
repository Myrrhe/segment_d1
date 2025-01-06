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

#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <cstdint>

namespace segment_d1
{
////////////////////////////////////////////////////////////
/// \brief MenuState class
///
////////////////////////////////////////////////////////////
class MenuState final
{
public:
    MenuState();
    explicit MenuState(const uint64_t id);
    MenuState(const MenuState &menuState) noexcept;
    MenuState &operator=(const MenuState &menuState);
    ~MenuState();
private:
    uint64_t m_id;
};

} // namespace segment_d1

#endif // MENUSTATE_HPP
