/*
 * The engine of the watch.
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

#include "menu/MenuState.hpp"

namespace segment_d1
{

MenuState::MenuState() : m_navigation(false), m_id(0) {}

MenuState::MenuState(const bool navigation, const uint64_t id)
    : m_navigation(navigation), m_id(id)
{
}

MenuState::MenuState(const MenuState &menuState) noexcept = default;

MenuState &MenuState::operator=(const MenuState &menuState) = default;

MenuState::~MenuState() = default;

bool MenuState::isNavigation() const { return m_navigation; }

uint64_t MenuState::getId() const { return m_id; }

} // namespace segment_d1
