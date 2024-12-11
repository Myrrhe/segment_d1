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

#include "Input.hpp"

namespace segment_d1
{

uint64_t Input::joystickSensitivity;

Input::Input()
    : typeInput(), key(), button(), axis(), buttonJoystick(), idJoystick(),
      signAxis()
{
}

Input::~Input() = default;

Input::Input(const sf::Keyboard::Key &newKey)
    : typeInput(TypeInput::KEYBOARD), key(newKey), button(), axis(),
      buttonJoystick(), idJoystick(), signAxis()
{
}

Input::Input(const sf::Mouse::Button &newButton)
    : typeInput(TypeInput::MOUSE), key(), button(newButton), axis(),
      buttonJoystick(), idJoystick(), signAxis()
{
}

Input::Input(const sf::Joystick::Axis &newAxis, const uint32_t newIdJoystick,
             const bool newSignAxis)
    : typeInput(TypeInput::JOYSTICK_AXIS), key(), button(), axis(newAxis),
      buttonJoystick(), idJoystick(newIdJoystick), signAxis(newSignAxis)
{
}

Input::Input(const uint32_t newButtonJoystick, const uint32_t newIdJoystick)
    : typeInput(TypeInput::JOYSTICK), key(), button(), axis(),
      buttonJoystick(newButtonJoystick), idJoystick(newIdJoystick), signAxis()
{
}

Input::Input(const Input &input) noexcept
    : typeInput(input.typeInput), key(input.key), button(input.button), axis(),
      buttonJoystick(input.buttonJoystick), idJoystick(), signAxis()
{
}

Input::Input(const std::string_view &str)
    : typeInput(), key(), button(), axis(), buttonJoystick(), idJoystick(),
      signAxis()
{
    typeInput = TypeInput::ERROR_TYPE_INPUT;
    if (str == "A")
    {
        key = sf::Keyboard::Key::A;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "B")
    {
        key = sf::Keyboard::Key::B;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "C")
    {
        key = sf::Keyboard::Key::C;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "D")
    {
        key = sf::Keyboard::Key::D;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "E")
    {
        key = sf::Keyboard::Key::E;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "F")
    {
        key = sf::Keyboard::Key::F;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "G")
    {
        key = sf::Keyboard::Key::G;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "H")
    {
        key = sf::Keyboard::Key::H;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "I")
    {
        key = sf::Keyboard::Key::I;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "J")
    {
        key = sf::Keyboard::Key::J;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "K")
    {
        key = sf::Keyboard::Key::K;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "L")
    {
        key = sf::Keyboard::Key::L;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "M")
    {
        key = sf::Keyboard::Key::M;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "N")
    {
        key = sf::Keyboard::Key::N;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "O")
    {
        key = sf::Keyboard::Key::O;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "P")
    {
        key = sf::Keyboard::Key::P;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "Q")
    {
        key = sf::Keyboard::Key::Q;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "R")
    {
        key = sf::Keyboard::Key::R;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "S")
    {
        key = sf::Keyboard::Key::S;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "T")
    {
        key = sf::Keyboard::Key::T;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "U")
    {
        key = sf::Keyboard::Key::U;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "V")
    {
        key = sf::Keyboard::Key::V;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "W")
    {
        key = sf::Keyboard::Key::W;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "X")
    {
        key = sf::Keyboard::Key::X;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "Y")
    {
        key = sf::Keyboard::Key::Y;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "Z")
    {
        key = sf::Keyboard::Key::Z;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "Num0")
    {
        key = sf::Keyboard::Key::Num0;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "Num1")
    {
        key = sf::Keyboard::Key::Num1;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "Num2")
    {
        key = sf::Keyboard::Key::Num2;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "Num3")
    {
        key = sf::Keyboard::Key::Num3;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "Num4")
    {
        key = sf::Keyboard::Key::Num4;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "Num5")
    {
        key = sf::Keyboard::Key::Num5;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "Num6")
    {
        key = sf::Keyboard::Key::Num6;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "Num7")
    {
        key = sf::Keyboard::Key::Num7;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "Num8")
    {
        key = sf::Keyboard::Key::Num8;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "Num9")
    {
        key = sf::Keyboard::Key::Num9;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "Escape")
    {
        key = sf::Keyboard::Key::Escape;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "LControl")
    {
        key = sf::Keyboard::Key::LControl;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "LShift")
    {
        key = sf::Keyboard::Key::LShift;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "LAlt")
    {
        key = sf::Keyboard::Key::LAlt;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "LSystem")
    {
        key = sf::Keyboard::Key::LSystem;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "RControl")
    {
        key = sf::Keyboard::Key::RControl;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "RShift")
    {
        key = sf::Keyboard::Key::RShift;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "RAlt")
    {
        key = sf::Keyboard::Key::RAlt;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "RSystem")
    {
        key = sf::Keyboard::Key::RSystem;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "Menu")
    {
        key = sf::Keyboard::Key::Menu;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "LBracket")
    {
        key = sf::Keyboard::Key::LBracket;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "RBracket")
    {
        key = sf::Keyboard::Key::RBracket;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "SemiColon")
    {
        key = sf::Keyboard::Key::Semicolon;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "Comma")
    {
        key = sf::Keyboard::Key::Comma;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "Period")
    {
        key = sf::Keyboard::Key::Period;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "Quote")
    {
        key = sf::Keyboard::Key::Quote;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "Slash")
    {
        key = sf::Keyboard::Key::Slash;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "BackSlash")
    {
        key = sf::Keyboard::Key::Backslash;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "Tilde")
    {
        key = sf::Keyboard::Key::Equal;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "Hyphen")
    {
        key = sf::Keyboard::Key::Hyphen;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "Space")
    {
        key = sf::Keyboard::Key::Space;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "Enter")
    {
        key = sf::Keyboard::Key::Enter;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "BackSpace")
    {
        key = sf::Keyboard::Key::Backspace;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "Tab")
    {
        key = sf::Keyboard::Key::Tab;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "PageUp")
    {
        key = sf::Keyboard::Key::PageUp;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "PageDown")
    {
        key = sf::Keyboard::Key::PageDown;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "End")
    {
        key = sf::Keyboard::Key::End;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "Home")
    {
        key = sf::Keyboard::Key::Home;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "Insert")
    {
        key = sf::Keyboard::Key::Insert;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "Delete")
    {
        key = sf::Keyboard::Key::Delete;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "Add")
    {
        key = sf::Keyboard::Key::Add;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "Substract")
    {
        key = sf::Keyboard::Key::Subtract;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "Multiply")
    {
        key = sf::Keyboard::Key::Multiply;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "Divide")
    {
        key = sf::Keyboard::Key::Divide;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "Left")
    {
        key = sf::Keyboard::Key::Left;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "Right")
    {
        key = sf::Keyboard::Key::Right;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "Up")
    {
        key = sf::Keyboard::Key::Up;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "Down")
    {
        key = sf::Keyboard::Key::Down;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "Numpad0")
    {
        key = sf::Keyboard::Key::Numpad0;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "Numpad1")
    {
        key = sf::Keyboard::Key::Numpad1;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "Numpad2")
    {
        key = sf::Keyboard::Key::Numpad2;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "Numpad3")
    {
        key = sf::Keyboard::Key::Numpad3;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "Numpad4")
    {
        key = sf::Keyboard::Key::Numpad4;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "Numpad5")
    {
        key = sf::Keyboard::Key::Numpad5;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "Numpad6")
    {
        key = sf::Keyboard::Key::Numpad6;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "Numpad7")
    {
        key = sf::Keyboard::Key::Numpad7;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "Numpad8")
    {
        key = sf::Keyboard::Key::Numpad8;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "Numpad9")
    {
        key = sf::Keyboard::Key::Numpad9;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "F1")
    {
        key = sf::Keyboard::Key::F1;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "F2")
    {
        key = sf::Keyboard::Key::F2;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "F3")
    {
        key = sf::Keyboard::Key::F3;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "F4")
    {
        key = sf::Keyboard::Key::F4;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "F5")
    {
        key = sf::Keyboard::Key::F5;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "F6")
    {
        key = sf::Keyboard::Key::F6;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "F7")
    {
        key = sf::Keyboard::Key::F7;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "F8")
    {
        key = sf::Keyboard::Key::F8;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "F9")
    {
        key = sf::Keyboard::Key::F9;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "F10")
    {
        key = sf::Keyboard::Key::F10;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "F11")
    {
        key = sf::Keyboard::Key::F11;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "F12")
    {
        key = sf::Keyboard::Key::F12;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "F13")
    {
        key = sf::Keyboard::Key::F13;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "F14")
    {
        key = sf::Keyboard::Key::F14;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "F15")
    {
        key = sf::Keyboard::Key::F15;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "Pause")
    {
        key = sf::Keyboard::Key::Pause;
        typeInput = TypeInput::KEYBOARD;
    }
    else if (str == "LeftMouse")
    {
        button = sf::Mouse::Button::Left;
        typeInput = TypeInput::MOUSE;
    }
    else if (str == "RightMouse")
    {
        button = sf::Mouse::Button::Right;
        typeInput = TypeInput::MOUSE;
    }
    else if (str == "MiddleMouse")
    {
        button = sf::Mouse::Button::Middle;
        typeInput = TypeInput::MOUSE;
    }
    else if (str == "XButton1")
    {
        button = sf::Mouse::Button::XButton1;
        typeInput = TypeInput::MOUSE;
    }
    else if (str == "XButton2")
    {
        button = sf::Mouse::Button::XButton2;
        typeInput = TypeInput::MOUSE;
    }
    else if (str == "XAxis-")
    {
        axis = sf::Joystick::Axis::X;
        signAxis = false;
        typeInput = TypeInput::JOYSTICK_AXIS;
    }
    else if (str == "XAxis+")
    {
        axis = sf::Joystick::Axis::X;
        signAxis = true;
        typeInput = TypeInput::JOYSTICK_AXIS;
    }
    else if (str == "YAxis-")
    {
        axis = sf::Joystick::Axis::Y;
        signAxis = false;
        typeInput = TypeInput::JOYSTICK_AXIS;
    }
    else if (str == "YAxis+")
    {
        axis = sf::Joystick::Axis::Y;
        signAxis = true;
        typeInput = TypeInput::JOYSTICK_AXIS;
    }
    else
    {
        for (uint32_t i = 0u; i < sf::Joystick::Count; ++i)
        {
            if (str == ("XAxis-" + std::to_string(i)))
            {
                axis = sf::Joystick::Axis::X;
                signAxis = false;
                idJoystick = i;
                typeInput = TypeInput::JOYSTICK_AXIS;
            }
            else if (str == ("XAxis+" + std::to_string(i)))
            {
                axis = sf::Joystick::Axis::X;
                signAxis = true;
                idJoystick = i;
                typeInput = TypeInput::JOYSTICK_AXIS;
            }
            else if (str == ("YAxis-" + std::to_string(i)))
            {
                axis = sf::Joystick::Axis::Y;
                signAxis = false;
                idJoystick = i;
                typeInput = TypeInput::JOYSTICK_AXIS;
            }
            else if (str == ("YAxis+" + std::to_string(i)))
            {
                axis = sf::Joystick::Axis::Y;
                signAxis = true;
                idJoystick = i;
                typeInput = TypeInput::JOYSTICK_AXIS;
            }
            else if (str == ("ZAxis-" + std::to_string(i)))
            {
                axis = sf::Joystick::Axis::Z;
                signAxis = false;
                idJoystick = i;
                typeInput = TypeInput::JOYSTICK_AXIS;
            }
            else if (str == ("ZAxis+" + std::to_string(i)))
            {
                axis = sf::Joystick::Axis::Z;
                signAxis = true;
                idJoystick = i;
                typeInput = TypeInput::JOYSTICK_AXIS;
            }
            else if (str == ("RAxis-" + std::to_string(i)))
            {
                axis = sf::Joystick::Axis::R;
                signAxis = false;
                idJoystick = i;
                typeInput = TypeInput::JOYSTICK_AXIS;
            }
            else if (str == ("RAxis+" + std::to_string(i)))
            {
                axis = sf::Joystick::Axis::R;
                signAxis = true;
                idJoystick = i;
                typeInput = TypeInput::JOYSTICK_AXIS;
            }
            else if (str == ("UAxis-" + std::to_string(i)))
            {
                axis = sf::Joystick::Axis::U;
                signAxis = false;
                idJoystick = i;
                typeInput = TypeInput::JOYSTICK_AXIS;
            }
            else if (str == ("UAxis+" + std::to_string(i)))
            {
                axis = sf::Joystick::Axis::U;
                signAxis = true;
                idJoystick = i;
                typeInput = TypeInput::JOYSTICK_AXIS;
            }
            else if (str == ("VAxis-" + std::to_string(i)))
            {
                axis = sf::Joystick::Axis::V;
                signAxis = false;
                idJoystick = i;
                typeInput = TypeInput::JOYSTICK_AXIS;
            }
            else if (str == ("VAxis+" + std::to_string(i)))
            {
                axis = sf::Joystick::Axis::V;
                signAxis = true;
                idJoystick = i;
                typeInput = TypeInput::JOYSTICK_AXIS;
            }
            else if (str == ("PovXAxis-" + std::to_string(i)))
            {
                axis = sf::Joystick::Axis::PovX;
                signAxis = false;
                idJoystick = i;
                typeInput = TypeInput::JOYSTICK_AXIS;
            }
            else if (str == ("PovXAxis+" + std::to_string(i)))
            {
                axis = sf::Joystick::Axis::PovX;
                signAxis = true;
                idJoystick = i;
                typeInput = TypeInput::JOYSTICK_AXIS;
            }
            else if (str == ("PovYAxis-" + std::to_string(i)))
            {
                axis = sf::Joystick::Axis::PovY;
                signAxis = false;
                idJoystick = i;
                typeInput = TypeInput::JOYSTICK_AXIS;
            }
            else if (str == ("PovYAxis+" + std::to_string(i)))
            {
                axis = sf::Joystick::Axis::PovY;
                signAxis = true;
                idJoystick = i;
                typeInput = TypeInput::JOYSTICK_AXIS;
            }
            else
            {
                for (uint32_t j = 0u; j < sf::Joystick::ButtonCount; ++j)
                {
                    if (str == ("JoystickButton" + std::to_string(i) + "-" +
                                std::to_string(j)))
                    {
                        buttonJoystick = j;
                        idJoystick = i;
                        typeInput = TypeInput::JOYSTICK;
                    }
                }
            }
        }
    }
}

Input &Input::operator=(const Input &input) = default;

std::string Input::toString() const
{
    std::string res = "error";
    switch (typeInput)
    {
    case TypeInput::KEYBOARD: {
        if (key == sf::Keyboard::Key::A)
        {
            res = "A";
        }
        else if (key == sf::Keyboard::Key::B)
        {
            res = "B";
        }
        else if (key == sf::Keyboard::Key::C)
        {
            res = "C";
        }
        else if (key == sf::Keyboard::Key::D)
        {
            res = "D";
        }
        else if (key == sf::Keyboard::Key::E)
        {
            res = "E";
        }
        else if (key == sf::Keyboard::Key::F)
        {
            res = "F";
        }
        else if (key == sf::Keyboard::Key::G)
        {
            res = "G";
        }
        else if (key == sf::Keyboard::Key::H)
        {
            res = "H";
        }
        else if (key == sf::Keyboard::Key::I)
        {
            res = "I";
        }
        else if (key == sf::Keyboard::Key::J)
        {
            res = "J";
        }
        else if (key == sf::Keyboard::Key::K)
        {
            res = "K";
        }
        else if (key == sf::Keyboard::Key::L)
        {
            res = "L";
        }
        else if (key == sf::Keyboard::Key::M)
        {
            res = "M";
        }
        else if (key == sf::Keyboard::Key::N)
        {
            res = "N";
        }
        else if (key == sf::Keyboard::Key::O)
        {
            res = "O";
        }
        else if (key == sf::Keyboard::Key::P)
        {
            res = "P";
        }
        else if (key == sf::Keyboard::Key::Q)
        {
            res = "Q";
        }
        else if (key == sf::Keyboard::Key::R)
        {
            res = "R";
        }
        else if (key == sf::Keyboard::Key::S)
        {
            res = "S";
        }
        else if (key == sf::Keyboard::Key::T)
        {
            res = "T";
        }
        else if (key == sf::Keyboard::Key::U)
        {
            res = "U";
        }
        else if (key == sf::Keyboard::Key::V)
        {
            res = "V";
        }
        else if (key == sf::Keyboard::Key::W)
        {
            res = "W";
        }
        else if (key == sf::Keyboard::Key::X)
        {
            res = "X";
        }
        else if (key == sf::Keyboard::Key::Y)
        {
            res = "Y";
        }
        else if (key == sf::Keyboard::Key::Z)
        {
            res = "Z";
        }
        else if (key == sf::Keyboard::Key::Num0)
        {
            res = "Num0";
        }
        else if (key == sf::Keyboard::Key::Num1)
        {
            res = "Num1";
        }
        else if (key == sf::Keyboard::Key::Num2)
        {
            res = "Num2";
        }
        else if (key == sf::Keyboard::Key::Num3)
        {
            res = "Num3";
        }
        else if (key == sf::Keyboard::Key::Num4)
        {
            res = "Num4";
        }
        else if (key == sf::Keyboard::Key::Num5)
        {
            res = "Num5";
        }
        else if (key == sf::Keyboard::Key::Num6)
        {
            res = "Num6";
        }
        else if (key == sf::Keyboard::Key::Num7)
        {
            res = "Num7";
        }
        else if (key == sf::Keyboard::Key::Num8)
        {
            res = "Num8";
        }
        else if (key == sf::Keyboard::Key::Num9)
        {
            res = "Num9";
        }
        else if (key == sf::Keyboard::Key::Escape)
        {
            res = "Escape";
        }
        else if (key == sf::Keyboard::Key::LControl)
        {
            res = "LControl";
        }
        else if (key == sf::Keyboard::Key::LShift)
        {
            res = "LShift";
        }
        else if (key == sf::Keyboard::Key::LAlt)
        {
            res = "LAlt";
        }
        else if (key == sf::Keyboard::Key::LSystem)
        {
            res = "LSystem";
        }
        else if (key == sf::Keyboard::Key::RControl)
        {
            res = "RControl";
        }
        else if (key == sf::Keyboard::Key::RShift)
        {
            res = "RShift";
        }
        else if (key == sf::Keyboard::Key::RAlt)
        {
            res = "RAlt";
        }
        else if (key == sf::Keyboard::Key::RSystem)
        {
            res = "RSystem";
        }
        else if (key == sf::Keyboard::Key::Menu)
        {
            res = "Menu";
        }
        else if (key == sf::Keyboard::Key::LBracket)
        {
            res = "LBracket";
        }
        else if (key == sf::Keyboard::Key::RBracket)
        {
            res = "RBracket";
        }
        else if (key == sf::Keyboard::Key::Semicolon)
        {
            res = "SemiColon";
        }
        else if (key == sf::Keyboard::Key::Comma)
        {
            res = "Comma";
        }
        else if (key == sf::Keyboard::Key::Period)
        {
            res = "Period";
        }
        else if (key == sf::Keyboard::Key::Quote)
        {
            res = "Quote";
        }
        else if (key == sf::Keyboard::Key::Slash)
        {
            res = "Slash";
        }
        else if (key == sf::Keyboard::Key::Backslash)
        {
            res = "BackSlash";
        }
        else if (key == sf::Keyboard::Key::Equal)
        {
            res = "Tilde";
        }
        else if (key == sf::Keyboard::Key::Hyphen)
        {
            res = "Hyphen";
        }
        else if (key == sf::Keyboard::Key::Space)
        {
            res = "Space";
        }
        else if (key == sf::Keyboard::Key::Enter)
        {
            res = "Enter";
        }
        else if (key == sf::Keyboard::Key::Backspace)
        {
            res = "BackSpace";
        }
        else if (key == sf::Keyboard::Key::Tab)
        {
            res = "Tab";
        }
        else if (key == sf::Keyboard::Key::PageUp)
        {
            res = "PageUp";
        }
        else if (key == sf::Keyboard::Key::PageDown)
        {
            res = "PageDown";
        }
        else if (key == sf::Keyboard::Key::End)
        {
            res = "End";
        }
        else if (key == sf::Keyboard::Key::Home)
        {
            res = "Home";
        }
        else if (key == sf::Keyboard::Key::Insert)
        {
            res = "Insert";
        }
        else if (key == sf::Keyboard::Key::Delete)
        {
            res = "Delete";
        }
        else if (key == sf::Keyboard::Key::Add)
        {
            res = "Add";
        }
        else if (key == sf::Keyboard::Key::Subtract)
        {
            res = "Substract";
        }
        else if (key == sf::Keyboard::Key::Multiply)
        {
            res = "Multiply";
        }
        else if (key == sf::Keyboard::Key::Divide)
        {
            res = "Divide";
        }
        else if (key == sf::Keyboard::Key::Left)
        {
            res = "Left";
        }
        else if (key == sf::Keyboard::Key::Right)
        {
            res = "Right";
        }
        else if (key == sf::Keyboard::Key::Up)
        {
            res = "Up";
        }
        else if (key == sf::Keyboard::Key::Down)
        {
            res = "Down";
        }
        else if (key == sf::Keyboard::Key::Numpad0)
        {
            res = "Numpad0";
        }
        else if (key == sf::Keyboard::Key::Numpad1)
        {
            res = "Numpad1";
        }
        else if (key == sf::Keyboard::Key::Numpad2)
        {
            res = "Numpad2";
        }
        else if (key == sf::Keyboard::Key::Numpad3)
        {
            res = "Numpad3";
        }
        else if (key == sf::Keyboard::Key::Numpad4)
        {
            res = "Numpad4";
        }
        else if (key == sf::Keyboard::Key::Numpad5)
        {
            res = "Numpad5";
        }
        else if (key == sf::Keyboard::Key::Numpad6)
        {
            res = "Numpad6";
        }
        else if (key == sf::Keyboard::Key::Numpad7)
        {
            res = "Numpad7";
        }
        else if (key == sf::Keyboard::Key::Numpad8)
        {
            res = "Numpad8";
        }
        else if (key == sf::Keyboard::Key::Numpad9)
        {
            res = "Numpad9";
        }
        else if (key == sf::Keyboard::Key::F1)
        {
            res = "F1";
        }
        else if (key == sf::Keyboard::Key::F2)
        {
            res = "F2";
        }
        else if (key == sf::Keyboard::Key::F3)
        {
            res = "F3";
        }
        else if (key == sf::Keyboard::Key::F4)
        {
            res = "F4";
        }
        else if (key == sf::Keyboard::Key::F5)
        {
            res = "F5";
        }
        else if (key == sf::Keyboard::Key::F6)
        {
            res = "F6";
        }
        else if (key == sf::Keyboard::Key::F7)
        {
            res = "F7";
        }
        else if (key == sf::Keyboard::Key::F8)
        {
            res = "F8";
        }
        else if (key == sf::Keyboard::Key::F9)
        {
            res = "F9";
        }
        else if (key == sf::Keyboard::Key::F10)
        {
            res = "F10";
        }
        else if (key == sf::Keyboard::Key::F11)
        {
            res = "F11";
        }
        else if (key == sf::Keyboard::Key::F12)
        {
            res = "F12";
        }
        else if (key == sf::Keyboard::Key::F13)
        {
            res = "F13";
        }
        else if (key == sf::Keyboard::Key::F14)
        {
            res = "F14";
        }
        else if (key == sf::Keyboard::Key::F15)
        {
            res = "F15";
        }
        else
        {
            res = "Pause";
        }
        break;
    }
    case TypeInput::MOUSE: {
        if (button == sf::Mouse::Button::Left)
        {
            res = "LeftMouse";
        }
        else if (button == sf::Mouse::Button::Right)
        {
            res = "RightMouse";
        }
        else if (button == sf::Mouse::Button::Middle)
        {
            res = "MiddleMouse";
        }
        else if (button == sf::Mouse::Button::XButton2)
        {
            res = "XButton1";
        }
        else
        {
            res = "XButton2";
        }
        break;
    }
    case TypeInput::JOYSTICK_AXIS: {
        if (axis == sf::Joystick::Axis::X)
        {
            res = "XAxis";
        }
        else if (axis == sf::Joystick::Axis::Y)
        {
            res = "YAxis";
        }
        else if (axis == sf::Joystick::Axis::Z)
        {
            res = "ZAxis";
        }
        else if (axis == sf::Joystick::Axis::R)
        {
            res = "RAxis";
        }
        else if (axis == sf::Joystick::Axis::U)
        {
            res = "UAxis";
        }
        else if (axis == sf::Joystick::Axis::V)
        {
            res = "VAxis";
        }
        else if (axis == sf::Joystick::Axis::PovX)
        {
            res = "PovXAxis";
        }
        else
        {
            res = "PovYAxis";
        }
        if (signAxis)
        {
            res += "+";
        }
        else
        {
            res += "-";
        }
        res += std::to_string(idJoystick);
        break;
    }
    case TypeInput::JOYSTICK: {
        res = "JoystickButton" + std::to_string(idJoystick) + "-" +
              std::to_string(buttonJoystick);
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
    return res;
}

bool Input::isPressed() const
{
    bool res = false;
    switch (typeInput)
    {
    case TypeInput::KEYBOARD: {
        res = sf::Keyboard::isKeyPressed(key);
        break;
    }
    case TypeInput::MOUSE: {
        res = sf::Mouse::isButtonPressed(button);
        break;
    }
    case TypeInput::JOYSTICK_AXIS: {
        bool above = false;
        if (signAxis)
        {
            above = sf::Joystick::getAxisPosition(idJoystick, axis) >
                    static_cast<float32_t>(joystickSensitivity);
        }
        else
        {
            above = sf::Joystick::getAxisPosition(idJoystick, axis) <
                    -static_cast<float32_t>(joystickSensitivity);
        }
        res = sf::Joystick::isConnected(idJoystick) &&
              sf::Joystick::hasAxis(idJoystick, axis) && above;
        break;
    }
    case TypeInput::JOYSTICK: {
        res = sf::Joystick::isConnected(idJoystick) &&
              sf::Joystick::isButtonPressed(idJoystick, buttonJoystick);
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
    return res;
}

Input::TypeInput Input::getTypeInput() const { return typeInput; }

sf::Keyboard::Key Input::getKey() const { return key; }

sf::Joystick::Axis Input::getAxis() const { return axis; }

bool Input::getSignAxis() const { return signAxis; }

sf::Mouse::Button Input::getButton() const { return button; }

uint32_t Input::getButtonJoyStick() const { return buttonJoystick; }

uint32_t Input::getIdJoystick() const { return idJoystick; }

uint64_t Input::getJoystickSensitivity() { return joystickSensitivity; }

void Input::setJoystickSensitivity(const uint64_t newJoystickSensitivity)
{
    joystickSensitivity = newJoystickSensitivity;
}

void Input::initialize()
{
    // Useful ?
    joystickSensitivity = 50;
}

uint64_t operator|(const Input::InputFl &inputFl1,
                   const Input::InputFl &inputFl2)
{
    return static_cast<uint64_t>(inputFl1) | static_cast<uint64_t>(inputFl2);
}

uint64_t operator|(const uint64_t inputFl1, const Input::InputFl &inputFl2)
{
    return inputFl1 | static_cast<uint64_t>(inputFl2);
}

} // namespace segment_d1
