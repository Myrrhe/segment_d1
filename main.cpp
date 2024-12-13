#include "Func.hpp"
#include "Logger.hpp"
#include "OsManager.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>


int main()
{
    segment_d1::Logger().info(__cplusplus);
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    segment_d1::Logger().info(
        segment_d1::OsManager::getSizePng("assets/p1.png"));
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
