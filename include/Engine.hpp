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

#ifndef ENGINE_HPP
#define ENGINE_HPP
#include "StaticObject.hpp"
#include "text/TextComp.hpp"
#include <SFML/Graphics.hpp>

namespace segment_d1
{

/** \class Engine
    \brief The engine of the software.
*/
class Engine final : public StaticObject
{
public:
    static void launch();

private:
    static void initialize();
    static void terminate();

    static void getInput();
    static void update();
    static void draw(sf::RenderTarget &renderTarget);

    static bool qEntered;
    static TextComp textTest;

    static sf::Clock s_clock;
};

} // namespace segment_d1

#endif // ENGINE_HPP
