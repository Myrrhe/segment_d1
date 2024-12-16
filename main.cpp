#include "Constants.hpp"
#include "Func.hpp"
#include "Global.hpp"
#include "Input.hpp"
#include "Logger.hpp"
#include "MouseWheel.hpp"
#include "OsManager.hpp"
#include "PathManager.hpp"
#include "Quaternion.hpp"
#include "ScreenConnected.hpp"
#include "StaticObject.hpp"
#include "TextureManager.hpp"
#include "Types.hpp"
#include "Windowmanager.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

int main(int /*argc*/, char **argv, char ** /*options*/)
{
    segment_d1::Logger().info(__cplusplus);

    segment_d1::OsManager::setPath(argv[0]);
    segment_d1::WindowManager::getMonitorSize();
    segment_d1::WindowManager::create();
    segment_d1::TextureManager::initializeStateTexture();
    segment_d1::MouseWheel::initialize();
    // segment_d1::TextureManager::manageTexture(
    //     segment_d1::TextureManager::TexFl::LOADING);
    segment_d1::TextureManager::loadUnloadAllTextureFile();
    // segment_d1::Language::setLanguage();
    // segment_d1::Setting::initialize();
    segment_d1::Input::initialize();
    // Language::initialize();
    segment_d1::TextureManager::initialize();
    segment_d1::WindowManager::initialize();
    // segment_d1::WindowManager::setIcon();
    while (segment_d1::TextureManager::loadUnloadOneTextureFile())
    {
        segment_d1::WindowManager::manageEvent();
    }
    segment_d1::OsManager::initialize();

    segment_d1::WindowManager::initialize();
    segment_d1::Logger().info(
        segment_d1::OsManager::getSizePng("assets/p1.png"));
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (segment_d1::WindowManager::isOpen())
    {
        sf::Event event;
        while (segment_d1::WindowManager::pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                segment_d1::WindowManager::close();
            }
        }

        segment_d1::WindowManager::clear();
        segment_d1::WindowManager::draw(shape);
        segment_d1::WindowManager::display();
    }

    return 0;
}
