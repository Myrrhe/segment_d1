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

#include "Engine.hpp"
#include "Func.hpp"
#include "GraphicState.hpp"
#include "Logger.hpp"
#include "OsManager.hpp"
#include "PathManager.hpp"
#include "ShaderManager.hpp"
#include "WindowManager.hpp"
#include "menu/MenuManager.hpp"
#include "text/ChainText.hpp"
#include <cmath>
#include <iostream>
#include <istream>


namespace segment_d1
{

bool Engine::qEntered;
TextComp Engine::textTest;
sf::Clock Engine::s_clock;

void Engine::initialize() { qEntered = false; }

void Engine::terminate()
{
    // Nothing to do
}

void Engine::launch()
{
    initialize();

    const GraphicState graphicState = GraphicState() * 0.5;

    sf::Font font;
    std::vector<std::string> allFont =
        Func::getDir(PathManager::getPath(PathManager::Dir::FONT));
    const std::size_t nbFile = allFont.size();
    for (std::size_t i = 0; i < nbFile; ++i)
    {
        if (allFont[i].size() < 4)
        {
            continue;
        }
        if ((allFont[i].substr(allFont[i].size() - 4, std::string::npos) !=
             ".ttf") &&
            (allFont[i].substr(allFont[i].size() - 4, std::string::npos) !=
             ".otf"))
        {
            continue;
        }
        if (!font.openFromFile(PathManager::getPath(PathManager::Dir::FONT) +
                               OsManager::Slash + allFont[i]))
        {
            Logger().info("Error loading font: " + allFont[i]);
        }
        break;
    }
    // std::cout << std::stoul("ff0000ff", nullptr, 16) << std::endl;
    const auto cha = ChainText(std::u32string(
        U"aa<fColor=ff0000ff,cSize=30>bb</>aaa<style=4>aaa<fColor=ff00ffff>bb</"
        U"></>aaaŽivaaaa<style=4>vvv\nccc</>"));

    std::cout << "std::string(\"Živa\").size() = " << std::string("Živa").size()
              << "\n";

    std::string n1 = "Machin";
    std::u32string n2 = U"";
    Func::utf8ToUtf32(n1.begin(), n1.end(), std::back_inserter(n2));
    std::string n3 = "";
    Func::utf32ToUtf8(n2.begin(), n2.end(), std::back_inserter(n3));
    std::u32string n4;

    std::u32string alpha = U"ŽivaŽivaŽivaŽivaŽivaŽivaŽivaŽivaŽiva";
    std::string beta = "";
    std::u32string gamma = U"";
    std::string zeta = "";
    Func::utf32ToUtf8(alpha.begin(), alpha.end(), std::back_inserter(beta));
    Func::utf8ToUtf32(beta.begin(), beta.end(), std::back_inserter(gamma));
    Func::utf32ToUtf8(gamma.begin(), gamma.end(), std::back_inserter(zeta));

    Func::utf8ToUtf32(n1.begin(), n1.end(), std::back_inserter(n2));

    auto n5 = sf::String(n4);
    // ChainText cha1 = *LangManager::getText("name1");
    ChainText cha2(U"Živa");

    std::cout << "n1 = " << n1 << "\n";
    // std::wcout << U"n2 = " << n2 << U"\n";
    std::cout << "n3 = " << n3 << "\n";
    std::cout << "beta = " << beta << "\n";
    std::cout << "zeta = " << zeta << "\n";
    // std::wcout << "n4 = " << n4 << "\n";
    // std::wcout << "n5 = " << n5 << "\n";
    // ChainText cha = std::u32string(U"Živa");
    // std::cout << "cha.getStr() = " << cha.getStr() << "\n";
    // std::cout << "cha.toStr() = " << cha.toStr() << "\n";
    textTest = TextComp({&cha, &cha2}, font, 60);
    // textTest.setStyle(InfoText::Style::Underlined);
    textTest.setOutlineThickness(2.0f);
    textTest.setStyle(InfoText::Style::UNDERLINED);
    textTest.setFillColor(sf::Color(255, 0, 0, 127));
    textTest.setOutlineColor(sf::Color(0, 255, 0, 127));
    textTest.setPosition(sf::Vector2<float32_t>(100.0f, 100.0f));

    ShaderManager::getShader("wave").setUniform("resolution",
                                                sf::Vector2f(1920, 1080));

    ShaderManager::getShader("wave").setUniform("wave_amplitude", 0.02f);

    while (WindowManager::isOpen())
    {
        getInput();
        update();
        draw(*WindowManager::getRenderWindow());
        WindowManager::display();
    }
    terminate();
}

void Engine::getInput()
{
    if (WindowManager::hasFocus())
    {
        qEntered = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q);
    }
}

void Engine::update()
{
    WindowManager::manageEvent();
    MenuManager::getInstance().update();
    if (qEntered)
    {
        WindowManager::close();
    }
}

void Engine::draw(sf::RenderTarget &renderTarget)
{
    renderTarget.clear(sf::Color(0, 0, 0, 255));
    // renderTarget.draw(textTest, sf::RenderStates::Default);

    ShaderManager::getShader("wave").setUniform(
        "time", s_clock.getElapsedTime().asSeconds());

    ShaderManager::getShader("wave").setUniform(
        "wave_phase", s_clock.getElapsedTime().asSeconds() * 0.1f);

    renderTarget.draw(textTest, &ShaderManager::getShader("wave"));

    MenuManager::getInstance().draw(renderTarget, sf::RenderStates::Default);
}

} // namespace segment_d1
