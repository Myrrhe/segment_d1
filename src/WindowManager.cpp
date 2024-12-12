/*
 * The file that manage the main window.
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

#include "WindowManager.hpp"
#include "Constants.hpp"
#include "MouseWheel.hpp"
#include "OsManager.hpp"
#include "PathManager.hpp"
#include <iostream>
#include <istream>

namespace segment_d1
{

std::unique_ptr<sf::RenderWindow> WindowManager::renderWindow;
std::unique_ptr<sf::Texture> WindowManager::textureIcon;

std::array<sf::View, 4> WindowManager::views;
std::stack<WindowManager::IdView> WindowManager::stateView;

float32_t WindowManager::mainScale;

float32_t WindowManager::uiX;
float32_t WindowManager::uiY;
float32_t WindowManager::uiWidth;
float32_t WindowManager::uiHeight;

float32_t WindowManager::offsetX;
float32_t WindowManager::offsetY;

sf::Vector2<uint64_t> WindowManager::monitorSize;

bool WindowManager::textEntered;
char32_t WindowManager::charEntered;

bool WindowManager::keyPressed;
sf::Keyboard::Key WindowManager::codeKeyPressed;

bool WindowManager::altEntered;
bool WindowManager::controlEntered;
bool WindowManager::shiftEntered;
bool WindowManager::systemEntered;

void WindowManager::getMonitorSize()
{
    monitorSize = OsManager::getMonitorSize();
}

void WindowManager::create()
{
    renderWindow = std::make_unique<sf::RenderWindow>();
    renderWindow->create(
        sf::VideoMode(Width, Height, ModeBitsPerPixel), "",
        sf::Style::Titlebar | sf::Style::Close,
        sf::ContextSettings(0, 0, 0, 1u, 1u,
                            sf::ContextSettings::Attribute::Default, false));

    stateView.push(IdView::MAIN);
    setViewTarget(*renderWindow);
}

void WindowManager::initialize()
{
    // textureIcon = new sf::Texture;
    // textureIcon->loadFromFile(PathManager::getPath(PathManager::Dir::IMG) +
    // OsManager::Slash + OsManager::StrIcon); textureIcon->setSmooth(false);
    // textureIcon->setRepeated(false);
    // if (textureIcon->getSize().x > 0 && textureIcon->getSize().y > 0)
    // {
    //     renderWindow->setIcon(OsManager::WidthIcon, OsManager::HeightIcon,
    //     textureIcon->copyToImage().getPixelsPtr());
    // }
    renderWindow->setTitle("Watch");
    renderWindow->setVerticalSyncEnabled(false);
    renderWindow->setMouseCursorVisible(true);
    renderWindow->setMouseCursorGrabbed(false);
    renderWindow->setFramerateLimit(Fps);

    textEntered = false;
    charEntered = 0;

    keyPressed = false;
    codeKeyPressed = sf::Keyboard::Key::A;

    altEntered = false;
    controlEntered = false;
    shiftEntered = false;
    systemEntered = false;
}

void WindowManager::terminate()
{
    // Nothing to do
}

void WindowManager::pushStateView(const IdView idView)
{
    stateView.push(idView);
}

void WindowManager::popStateView() { stateView.pop(); }

void WindowManager::setViewTarget(sf::RenderTarget &renderTarget)
{
    const sf::Vector2<uint32_t> sizeTarget = renderTarget.getSize();
    switch (stateView.top())
    {
    case IdView::MAIN: {
        mainScale = std::min(static_cast<float32_t>(sizeTarget.x) /
                                 static_cast<float32_t>(Width),
                             static_cast<float32_t>(sizeTarget.y) /
                                 static_cast<float32_t>(Height));
        auto rendingSize = sf::Vector2<float32_t>(0, 0);
        if (Fullscreen)
        {
            rendingSize =
                sf::Vector2<float32_t>(static_cast<float32_t>(monitorSize.x),
                                       static_cast<float32_t>(monitorSize.y));
        }
        else
        {
            rendingSize =
                sf::Vector2<float32_t>(static_cast<float32_t>(sizeTarget.x),
                                       static_cast<float32_t>(sizeTarget.y));
        }
        views[0].reset(sf::Rect<float32_t>(0.0f, 0.0f, Width, Height));
        views[0].setViewport(sf::Rect<float32_t>(
            ((rendingSize.x - (Width * mainScale)) * 0.5f) / rendingSize.x,
            ((rendingSize.y - (Height * mainScale)) * 0.5f) / rendingSize.y,
            1.0f - ((rendingSize.x - (Width * mainScale)) / rendingSize.x),
            1.0f - ((rendingSize.y - (Height * mainScale)) / rendingSize.y)));
        renderTarget.setView(views[0]);
        break;
    }
    case IdView::UI: {
        auto rendingSize = sf::Vector2<float32_t>(0, 0);
        if (Fullscreen)
        {
            rendingSize =
                sf::Vector2<float32_t>(static_cast<float32_t>(monitorSize.x),
                                       static_cast<float32_t>(monitorSize.y));
        }
        else
        {
            rendingSize =
                sf::Vector2<float32_t>(static_cast<float32_t>(sizeTarget.x),
                                       static_cast<float32_t>(sizeTarget.y));
        }
        views[1].reset(sf::Rect<float32_t>(uiX, uiY, uiWidth, uiHeight));
        views[1].setViewport(sf::Rect<float32_t>(
            (((rendingSize.x - (Width * mainScale)) * 0.5f) +
             (uiX * mainScale)) /
                rendingSize.x,
            (((rendingSize.y - (Height * mainScale)) * 0.5f) +
             (uiY * mainScale)) /
                rendingSize.y,
            (uiWidth * mainScale) / rendingSize.x,
            (uiHeight * mainScale) / rendingSize.y));
        renderTarget.setView(views[1]);
        break;
    }
    case IdView::SHAKE: {
        mainScale = std::min(static_cast<float32_t>(sizeTarget.x) /
                                 static_cast<float32_t>(Width),
                             static_cast<float32_t>(sizeTarget.y) /
                                 static_cast<float32_t>(Height));
        auto rendingSize = sf::Vector2<float32_t>(0, 0);
        if (Fullscreen)
        {
            rendingSize =
                sf::Vector2<float32_t>(static_cast<float32_t>(monitorSize.x),
                                       static_cast<float32_t>(monitorSize.y));
        }
        else
        {
            rendingSize =
                sf::Vector2<float32_t>(static_cast<float32_t>(sizeTarget.x),
                                       static_cast<float32_t>(sizeTarget.y));
        }
        views[2].reset(sf::Rect<float32_t>(0.0f, 0.0f, Width, Height));
        views[2].setViewport(sf::Rect<float32_t>(
            ((rendingSize.x - ((Width + (2.0f * offsetX)) * mainScale)) *
             0.5f) /
                rendingSize.x,
            ((rendingSize.y - ((Height + (2.0f * offsetY)) * mainScale)) *
             0.5f) /
                rendingSize.y,
            1.0f - ((rendingSize.x - (Width * mainScale)) / rendingSize.x),
            1.0f - ((rendingSize.y - (Height * mainScale)) / rendingSize.y)));
        renderTarget.setView(views[2]);
        break;
    }
    case IdView::WHOLE: {
        views[3].reset(sf::Rect<float32_t>(0.0f, 0.0f, Width, Height));
        views[3].setViewport(sf::Rect<float32_t>(0.0f, 0.0f, 1.0f, 1.0f));
        renderTarget.setView(views[3]);
        break;
    }
    default: {
        break;
    }
    }
}

void WindowManager::setUiView(const float32_t x, const float32_t y,
                              const float32_t widthUi, const float32_t heightUi)
{
    uiX = x;
    uiY = y;
    uiWidth = widthUi;
    uiHeight = heightUi;
}

void WindowManager::setOffsetX(const float32_t newOffsetX)
{
    offsetX = newOffsetX;
}

void WindowManager::setOffsetY(const float32_t newOffsetY)
{
    offsetY = newOffsetY;
}

void WindowManager::manageEvent()
{
    MouseWheel::setDeltaWheel(0);
    sf::Event event;
    textEntered = false;
    keyPressed = false;
    while (renderWindow->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            renderWindow->close();
        }
        else if (event.type == sf::Event::MouseWheelMoved)
        {
            MouseWheel::setDeltaWheel(event.mouseWheel.delta);
        }
        else if (event.type == sf::Event::TextEntered)
        {
            textEntered = true;
            charEntered = event.text.unicode;
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            keyPressed = true;
            codeKeyPressed = event.key.code;
            altEntered = event.key.alt;
            controlEntered = event.key.control;
            shiftEntered = event.key.shift;
            systemEntered = event.key.system;
        }
        else
        {
            // Nothing to do
        }
    }
}

bool WindowManager::isOpen() { return renderWindow->isOpen(); }

bool WindowManager::pollEvent(sf::Event &event)
{
    return renderWindow->pollEvent(event);
}

bool WindowManager::hasFocus() { return renderWindow->hasFocus(); }

void WindowManager::close() { renderWindow->close(); }

void WindowManager::clear(const sf::Color &color)
{
    renderWindow->clear(color);
}

void WindowManager::clear()
{
    renderWindow->clear(sf::Color(0, 0, 0, MaxColor));
}

void WindowManager::draw(const sf::Vertex *const vertices,
                         const std::size_t vertexCount,
                         const sf::PrimitiveType type,
                         const sf::RenderStates &states)
{
    renderWindow->draw(vertices, vertexCount, type, states);
}

void WindowManager::draw(const sf::Drawable &drawable,
                         const sf::RenderStates &states)
{
    renderWindow->draw(drawable, states);
}

void WindowManager::display() { renderWindow->display(); }

sf::Vector2<int32_t> WindowManager::getMousePosition()
{
    return sf::Mouse::getPosition(*renderWindow);
}

sf::Vector2<float32_t>
WindowManager::mapPixelToCoords(const sf::Vector2<int32_t> &point)
{
    return renderWindow->mapPixelToCoords(point);
}

sf::RenderWindow *WindowManager::getRenderWindow()
{
    return renderWindow.get();
}

bool WindowManager::isTextEntered() { return textEntered; }

char32_t WindowManager::getCharEntered() { return charEntered; }

bool WindowManager::isKeyPressed() { return keyPressed; }

sf::Keyboard::Key WindowManager::getKeyPressed() { return codeKeyPressed; }

bool WindowManager::isAltEntered() { return altEntered; }

bool WindowManager::isControlEntered() { return controlEntered; }

bool WindowManager::isShiftEntered() { return shiftEntered; }

bool WindowManager::isSystemEntered() { return systemEntered; }

} // namespace segment_d1
