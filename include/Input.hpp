/*
 * <one line to give the library's name and an idea of what it does.>
 * Copyright (C) 2017  <copyright holder> <email>
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

#ifndef INPUT_HPP
#define INPUT_HPP
#include "Func.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <istream>


namespace segment_d1
{

class Input final
{
public:
    enum class InputFl : uint64_t
    {
        LEFT = 1,
        RIGHT = 1 << 1,
        UP = 1 << 2,
        DOWN = 1 << 3,
        SLOW = 1 << 4,
        SHOT = 1 << 5,
        BOMB = 1 << 6,
        NEXT = 1 << 7,
        PREV = 1 << 8,
        SKIP = 1 << 9
    };

    enum class TypeInput : uint64_t
    {
        KEYBOARD,
        MOUSE,
        JOYSTICK_AXIS,
        JOYSTICK,
        ERROR_TYPE_INPUT
    };

    Input();
    explicit Input(const sf::Keyboard::Key &newKey);
    explicit Input(const sf::Mouse::Button &newButton);
    explicit Input(const sf::Joystick::Axis &newAxis,
                   const uint32_t newIdJoystick, const bool newSignAxis);
    explicit Input(const uint32_t newButtonJoystick,
                   const uint32_t newIdJoystick);
    explicit Input(const std::string_view &str);
    Input(const Input &input) noexcept;
    Input &operator=(const Input &input);
    ~Input();
    std::string toString() const;
    bool isPressed() const;
    [[nodiscard]] TypeInput getTypeInput() const;
    [[nodiscard]] sf::Keyboard::Key getKey() const;
    [[nodiscard]] sf::Mouse::Button getButton() const;
    [[nodiscard]] sf::Joystick::Axis getAxis() const;
    [[nodiscard]] bool getSignAxis() const;
    [[nodiscard]] uint32_t getButtonJoyStick() const;
    [[nodiscard]] uint32_t getIdJoystick() const;

    static void initialize();
    [[nodiscard]] static uint64_t getJoystickSensitivity();
    static void setJoystickSensitivity(const uint64_t newJoystickSensitivity);

private:
    TypeInput typeInput;
    sf::Keyboard::Key key;
    sf::Mouse::Button button;
    sf::Joystick::Axis axis;
    uint32_t buttonJoystick;
    uint32_t idJoystick;
    bool signAxis;

    static uint64_t joystickSensitivity;

    friend bool operator==(const Input &left, const Input &right)
    {
        bool res = false;
        if (left.typeInput != right.typeInput)
        {
            res = false;
        }
        else
        {
            switch (left.typeInput)
            {
            case TypeInput::KEYBOARD: {
                res = left.key == right.key;
                break;
            }
            case TypeInput::MOUSE: {
                res = left.button == right.button;
                break;
            }
            case TypeInput::JOYSTICK_AXIS: {
                res = ((left.axis == right.axis) &&
                       (left.signAxis == right.signAxis) &&
                       (left.idJoystick == right.idJoystick));
                break;
            }
            case TypeInput::JOYSTICK: {
                res = ((left.buttonJoystick == right.buttonJoystick) &&
                       (left.idJoystick == right.idJoystick));
                break;
            }
            case TypeInput::ERROR_TYPE_INPUT: {
                DEBUG_LOG("error type input");
                break;
            }
            default: {
                DEBUG_LOG("default reached");
                break;
            }
            }
        }
        return res;
    }

    friend bool operator!=(const Input &left, const Input &right)
    {
        return !(left == right);
    }
};

uint64_t operator|(const Input::InputFl &inputFl1,
                   const Input::InputFl &inputFl2);
uint64_t operator|(const uint64_t inputFl1, const Input::InputFl &inputFl2);

} // namespace segment_d1

#endif // INPUT_HPP
