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

#include "Func.hpp"
#include <chrono>
#include <cmath>
#include <dirent.h>
#include <fstream>
#include <locale>
#include <sstream>

namespace segment_d1
{

std::ostream &operator<<(std::ostream &os, const sf::Color &right)
{
    return os << "(" << static_cast<int8_t>(right.r) << ", "
              << static_cast<int8_t>(right.g) << ", "
              << static_cast<int8_t>(right.b) << ", "
              << static_cast<int8_t>(right.a) << ")";
}

std::ostream &operator<<(std::ostream &os, const sf::Vector2<int32_t> &right)
{
    return os << '(' << right.x << ", " << right.y << ')';
}

std::ostream &operator<<(std::ostream &os, const sf::Vector2<uint32_t> &right)
{
    return os << '(' << right.x << ", " << right.y << ')';
}

std::ostream &operator<<(std::ostream &os, const sf::Vector2<float32_t> &right)
{
    return os << '(' << right.x << ", " << right.y << ')';
}

std::ostream &operator<<(std::ostream &os, const sf::Vector2<float64_t> &right)
{
    return os << '(' << right.x << ", " << right.y << ')';
}

std::ostream &operator<<(std::ostream &os, const sf::Rect<int32_t> &right)
{
    return os << '(' << right.left << ", " << right.top << ", " << right.width
              << ", " << right.height << ')';
}

std::ostream &operator<<(std::ostream &os, const sf::Rect<float32_t> &right)
{
    return os << '(' << right.left << ", " << right.top << ", " << right.width
              << ", " << right.height << ')';
}

std::ostream &operator<<(std::ostream &os, const sf::Rect<float64_t> &right)
{
    return os << '(' << right.left << ", " << right.top << ", " << right.width
              << ", " << right.height << ')';
}

std::ostream &operator<<(std::ostream &os, const sf::Transform &right)
{
    const float32_t *const matrix = right.getMatrix();
    return os << "(" << matrix[0] << " " << matrix[4] << " " << matrix[8] << " "
              << matrix[12] << ")" << '\n'
              << "(" << matrix[1] << " " << matrix[5] << " " << matrix[9] << " "
              << matrix[13] << ")" << '\n'
              << "(" << matrix[2] << " " << matrix[6] << " " << matrix[10]
              << " " << matrix[14] << ")" << '\n'
              << "(" << matrix[3] << " " << matrix[7] << " " << matrix[11]
              << " " << matrix[15] << ")";
}

std::ostream &operator<<(std::ostream &os, const sf::Time &right)
{
    return os << right.asSeconds();
}

std::ostream &operator<<(std::ostream &os,
                         const std::vector<std::string> &right)
{
    const std::size_t sizeV = right.size();
    os << '(';
    for (std::size_t i = 0; i < sizeV; ++i)
    {
        os << '\"' << right[i] << '\"';
        if (i != (sizeV - 1))
        {
            os << ", ";
        }
    }
    os << ')';
    return os;
}

std::ostream &operator<<(std::ostream &os, const std::vector<uint64_t> &right)
{
    const std::size_t sizeV = right.size();
    os << '(';
    for (std::size_t i = 0; i < sizeV; ++i)
    {
        os << right[i];
        if (i != (sizeV - 1))
        {
            os << ", ";
        }
    }
    os << ')';
    return os;
}

std::ostream &operator<<(std::ostream &os, const std::vector<float64_t> &right)
{
    const std::size_t sizeV = right.size();
    os << '(';
    for (std::size_t i = 0; i < sizeV; ++i)
    {
        os << right[i];
        if (i != (sizeV - 1))
        {
            os << ", ";
        }
    }
    os << ')';
    return os;
}

sf::Rect<int32_t> operator|(const sf::Rect<int32_t> &left,
                            const sf::Rect<int32_t> &right)
{
    const auto leftTopCorner = sf::Vector2<int32_t>(
        std::min(left.left, right.left), std::min(left.top, right.top));
    return sf::Rect<int32_t>(
        leftTopCorner.x, leftTopCorner.y,
        std::max(left.left + left.width, right.left + right.width) -
            leftTopCorner.x,
        std::max(left.top + left.height, right.top + right.height) -
            leftTopCorner.y);
}

sf::Rect<float32_t> operator|(const sf::Rect<float32_t> &left,
                              const sf::Rect<float32_t> &right)
{
    const auto leftTopCorner = sf::Vector2<float32_t>(
        std::min(left.left, right.left), std::min(left.top, right.top));
    return sf::Rect<float32_t>(
        leftTopCorner.x, leftTopCorner.y,
        std::max(left.left + left.width, right.left + right.width) -
            leftTopCorner.x,
        std::max(left.top + left.height, right.top + right.height) -
            leftTopCorner.y);
}

sf::Rect<float64_t> operator|(const sf::Rect<float64_t> &left,
                              const sf::Rect<float64_t> &right)
{
    const auto leftTopCorner = sf::Vector2<float64_t>(
        std::min(left.left, right.left), std::min(left.top, right.top));
    return sf::Rect<float64_t>(
        leftTopCorner.x, leftTopCorner.y,
        std::max(left.left + left.width, right.left + right.width) -
            leftTopCorner.x,
        std::max(left.top + left.height, right.top + right.height) -
            leftTopCorner.y);
}

sf::Rect<int32_t> operator+(const sf::Rect<int32_t> &left,
                            const sf::Vector2<int32_t> &right)
{
    return sf::Rect<int32_t>(left.left + right.x, left.top + right.y,
                             left.width, left.height);
}

sf::Rect<float32_t> operator+(const sf::Rect<float32_t> &left,
                              const sf::Vector2<float32_t> &right)
{
    return sf::Rect<float32_t>(left.left + right.x, left.top + right.y,
                               left.width, left.height);
}

sf::Rect<float64_t> operator+(const sf::Rect<float64_t> &left,
                              const sf::Vector2<float64_t> &right)
{
    return sf::Rect<float64_t>(left.left + right.x, left.top + right.y,
                               left.width, left.height);
}

sf::Rect<int32_t> &operator+=(sf::Rect<int32_t> &left,
                              const sf::Vector2<int32_t> &right)
{
    return left = sf::Rect<int32_t>(left.left + right.x, left.top + right.y,
                                    left.width, left.height);
}

sf::Rect<float32_t> &operator+=(sf::Rect<float32_t> &left,
                                const sf::Vector2<float32_t> &right)
{
    return left = sf::Rect<float32_t>(left.left + right.x, left.top + right.y,
                                      left.width, left.height);
}

sf::Rect<float64_t> &operator+=(sf::Rect<float64_t> &left,
                                const sf::Vector2<float64_t> &right)
{
    return left = sf::Rect<float64_t>(left.left + right.x, left.top + right.y,
                                      left.width, left.height);
}

sf::Rect<int32_t> operator-(const sf::Rect<int32_t> &left,
                            const sf::Vector2<int32_t> &right)
{
    return sf::Rect<int32_t>(left.left - right.x, left.top - right.y,
                             left.width, left.height);
}

sf::Rect<float32_t> operator-(const sf::Rect<float32_t> &left,
                              const sf::Vector2<float32_t> &right)
{
    return sf::Rect<float32_t>(left.left - right.x, left.top - right.y,
                               left.width, left.height);
}

sf::Rect<float64_t> operator-(const sf::Rect<float64_t> &left,
                              const sf::Vector2<float64_t> &right)
{
    return sf::Rect<float64_t>(left.left - right.x, left.top - right.y,
                               left.width, left.height);
}

sf::Rect<int32_t> &operator-=(sf::Rect<int32_t> &left,
                              const sf::Vector2<int32_t> &right)
{
    return left = sf::Rect<int32_t>(left.left - right.x, left.top - right.y,
                                    left.width, left.height);
}

sf::Rect<float32_t> &operator-=(sf::Rect<float32_t> &left,
                                const sf::Vector2<float32_t> &right)
{
    return left = sf::Rect<float32_t>(left.left - right.x, left.top - right.y,
                                      left.width, left.height);
}

sf::Rect<float64_t> &operator-=(sf::Rect<float64_t> &left,
                                const sf::Vector2<float64_t> &right)
{
    return left = sf::Rect<float64_t>(left.left - right.x, left.top - right.y,
                                      left.width, left.height);
}

sf::Rect<int32_t> operator*(const sf::Rect<int32_t> &left, const int32_t right)
{
    return sf::Rect<int32_t>(left.left, left.top, left.width * right,
                             left.height * right);
}

sf::Rect<float32_t> operator*(const sf::Rect<float32_t> &left,
                              const float32_t right)
{
    return sf::Rect<float32_t>(left.left, left.top, left.width * right,
                               left.height * right);
}

sf::Rect<float64_t> operator*(const sf::Rect<float64_t> &left,
                              const float64_t right)
{
    return sf::Rect<float64_t>(left.left, left.top, left.width * right,
                               left.height * right);
}

sf::Rect<int32_t> &operator*=(sf::Rect<int32_t> &left, const int32_t right)
{
    return left = sf::Rect<int32_t>(left.left, left.top, left.width * right,
                                    left.height * right);
}

sf::Rect<float32_t> &operator*=(sf::Rect<float32_t> &left,
                                const float32_t right)
{
    return left = sf::Rect<float32_t>(left.left, left.top, left.width * right,
                                      left.height * right);
}

sf::Rect<float64_t> &operator*=(sf::Rect<float64_t> &left,
                                const float64_t right)
{
    return left = sf::Rect<float64_t>(left.left, left.top, left.width * right,
                                      left.height * right);
}

sf::Rect<int32_t> operator/(const sf::Rect<int32_t> &left, const int32_t right)
{
    return sf::Rect<int32_t>(left.left, left.top, left.width / right,
                             left.height / right);
}

sf::Rect<float32_t> operator/(const sf::Rect<float32_t> &left,
                              const float32_t right)
{
    return sf::Rect<float32_t>(left.left, left.top, left.width / right,
                               left.height / right);
}

sf::Rect<float64_t> operator/(const sf::Rect<float64_t> &left,
                              const float64_t right)
{
    return sf::Rect<float64_t>(left.left, left.top, left.width / right,
                               left.height / right);
}

sf::Rect<int32_t> &operator/=(sf::Rect<int32_t> &left, const int32_t right)
{
    return left = sf::Rect<int32_t>(left.left, left.top, left.width / right,
                                    left.height / right);
}

sf::Rect<float32_t> &operator/=(sf::Rect<float32_t> &left,
                                const float32_t right)
{
    return left = sf::Rect<float32_t>(left.left, left.top, left.width / right,
                                      left.height / right);
}

sf::Rect<float64_t> &operator/=(sf::Rect<float64_t> &left,
                                const float64_t right)
{
    return left = sf::Rect<float64_t>(left.left, left.top, left.width / right,
                                      left.height / right);
}

sf::Rect<int32_t> operator*(const sf::Rect<int32_t> &left,
                            const sf::Vector2<int32_t> &right)
{
    return sf::Rect<int32_t>(left.left, left.top, left.width * right.x,
                             left.height * right.y);
}

sf::Rect<float32_t> operator*(const sf::Rect<float32_t> &left,
                              const sf::Vector2<float32_t> &right)
{
    return sf::Rect<float32_t>(left.left, left.top, left.width * right.x,
                               left.height * right.y);
}

sf::Rect<float64_t> operator*(const sf::Rect<float64_t> &left,
                              const sf::Vector2<float64_t> &right)
{
    return sf::Rect<float64_t>(left.left, left.top, left.width * right.x,
                               left.height * right.y);
}

sf::Rect<int32_t> &operator*=(sf::Rect<int32_t> &left,
                              const sf::Vector2<int32_t> &right)
{
    return left = sf::Rect<int32_t>(left.left, left.top, left.width * right.x,
                                    left.height * right.y);
}

sf::Rect<float32_t> &operator*=(sf::Rect<float32_t> &left,
                                const sf::Vector2<float32_t> &right)
{
    return left = sf::Rect<float32_t>(left.left, left.top, left.width * right.x,
                                      left.height * right.y);
}

sf::Rect<float64_t> &operator*=(sf::Rect<float64_t> &left,
                                const sf::Vector2<float64_t> &right)
{
    return left = sf::Rect<float64_t>(left.left, left.top, left.width * right.x,
                                      left.height * right.y);
}

sf::Rect<int32_t> operator/(const sf::Rect<int32_t> &left,
                            const sf::Vector2<int32_t> &right)
{
    return sf::Rect<int32_t>(left.left, left.top, left.width / right.x,
                             left.height / right.y);
}

sf::Rect<float32_t> operator/(const sf::Rect<float32_t> &left,
                              const sf::Vector2<float32_t> &right)
{
    return sf::Rect<float32_t>(left.left, left.top, left.width / right.x,
                               left.height / right.y);
}

sf::Rect<float64_t> operator/(const sf::Rect<float64_t> &left,
                              const sf::Vector2<float64_t> &right)
{
    return sf::Rect<float64_t>(left.left, left.top, left.width / right.x,
                               left.height / right.y);
}

sf::Rect<int32_t> &operator/=(sf::Rect<int32_t> &left,
                              const sf::Vector2<int32_t> &right)
{
    return left = sf::Rect<int32_t>(left.left, left.top, left.width / right.x,
                                    left.height / right.y);
}

sf::Rect<float32_t> &operator/=(sf::Rect<float32_t> &left,
                                const sf::Vector2<float32_t> &right)
{
    return left = sf::Rect<float32_t>(left.left, left.top, left.width / right.x,
                                      left.height / right.y);
}

sf::Rect<float64_t> &operator/=(sf::Rect<float64_t> &left,
                                const sf::Vector2<float64_t> &right)
{
    return left = sf::Rect<float64_t>(left.left, left.top, left.width / right.x,
                                      left.height / right.y);
}

int32_t operator*(const sf::Vector2<int32_t> &left,
                  const sf::Vector2<int32_t> &right)
{
    return (left.x * right.x) + (left.y * right.y);
}

uint32_t operator*(const sf::Vector2<uint32_t> &left,
                   const sf::Vector2<uint32_t> &right)
{
    return (left.x * right.x) + (left.y * right.y);
}

float32_t operator*(const sf::Vector2<float32_t> &left,
                    const sf::Vector2<float32_t> &right)
{
    return (left.x * right.x) + (left.y * right.y);
}

float64_t operator*(const sf::Vector2<float64_t> &left,
                    const sf::Vector2<float64_t> &right)
{
    return (left.x * right.x) + (left.y * right.y);
}

int32_t operator^(const sf::Vector2<int32_t> &left,
                  const sf::Vector2<int32_t> &right)
{
    return (left.x * right.y) - (left.y * right.x);
}

float32_t operator^(const sf::Vector2<float32_t> &left,
                    const sf::Vector2<float32_t> &right)
{
    return (left.x * right.y) - (left.y * right.x);
}

float64_t operator^(const sf::Vector2<float64_t> &left,
                    const sf::Vector2<float64_t> &right)
{
    return (left.x * right.y) - (left.y * right.x);
}

sf::Vector2<float32_t> Func::flooring(const sf::Vector2<float32_t> &v)
{
    return sf::Vector2<float32_t>(std::floor(v.x), std::floor(v.y));
}

float32_t Func::getNorm(const sf::Vector2<float32_t> &v)
{
    return std::sqrt((v.x * v.x) + (v.y * v.y));
}

float64_t Func::getNorm(const sf::Vector2<float64_t> &v)
{
    return std::sqrt((v.x * v.x) + (v.y * v.y));
}

float32_t Func::getNormSquared(const sf::Vector2<float32_t> &v)
{
    return (v.x * v.x) + (v.y * v.y);
}

float64_t Func::getNormSquared(const sf::Vector2<float64_t> &v)
{
    return (v.x * v.x) + (v.y * v.y);
}

sf::Vector2<int32_t> Func::getInverted(const sf::Vector2<int32_t> &v)
{
    return sf::Vector2<int32_t>(-v.x, -v.y);
}

sf::Vector2<float32_t> Func::getInverted(const sf::Vector2<float32_t> &v)
{
    return sf::Vector2<float32_t>(-v.x, -v.y);
}

sf::Vector2<float64_t> Func::getInverted(const sf::Vector2<float64_t> &v)
{
    return sf::Vector2<float64_t>(-v.x, -v.y);
}

sf::Vector2<float32_t> Func::getNormalized(const sf::Vector2<float32_t> &v)
{
    const float32_t norm = getNorm(v);
    return sf::Vector2<float32_t>(v.x / norm, v.y / norm);
}

sf::Vector2<float64_t> Func::getNormalized(const sf::Vector2<float64_t> &v)
{
    const float64_t norm = getNorm(v);
    return sf::Vector2<float64_t>(v.x / norm, v.y / norm);
}

float32_t Func::radToDeg(const float32_t radians)
{
    return radians * (180.0f / m_pi_f);
}

float64_t Func::radToDeg(const float64_t radians)
{
    return radians * (180.0 / m_pi);
}

float32_t Func::degToRad(const float32_t degree)
{
    return degree * (m_pi_f / 180.0f);
}

float64_t Func::degToRad(const float64_t degree)
{
    return degree * (m_pi / 180.0);
}

float32_t Func::getRotationAngle(const sf::Vector2<float32_t> &v)
{
    const sf::Vector2<float32_t> normalizedVec = getNormalized(v);
    const float32_t angleXRad = std::acos(normalizedVec.x);
    const float32_t angleYRad = std::asin(normalizedVec.y);
    float32_t angleRad = 0;
    if (angleYRad < 0)
    {
        angleRad = m_2pi_f - angleXRad;
    }
    else
    {
        angleRad = angleXRad;
    }
    // Angle in radians
    return angleRad;
}

float64_t Func::getRotationAngle(const sf::Vector2<float64_t> &v)
{
    const sf::Vector2<float64_t> normalizedVec = getNormalized(v);
    const float64_t angleXRad = std::acos(normalizedVec.x);
    const float64_t angleYRad = std::asin(normalizedVec.y);
    float64_t angleRad = 0;
    if (angleYRad < 0)
    {
        angleRad = m_2pi - angleXRad;
    }
    else
    {
        angleRad = angleXRad;
    }
    // Angle in radians
    return angleRad;
}

float32_t Func::getAngleBetween(const sf::Vector2<float32_t> &v1,
                                const sf::Vector2<float32_t> &v2)
{
    // Angle in radians
    return std::acos((v1 * v2) / (getNorm(v1) * getNorm(v2)));
}

float64_t Func::getAngleBetween(const sf::Vector2<float64_t> &v1,
                                const sf::Vector2<float64_t> &v2)
{
    // Angle in radians
    return std::acos((v1 * v2) / (getNorm(v1) * getNorm(v2)));
}

sf::Vector2<float32_t> Func::getRotated(const sf::Vector2<float32_t> &vec,
                                        const float32_t angle)
{
    return sf::Vector2<float32_t>(
        (vec.x * std::cos(angle)) + (vec.y * std::sin(angle)),
        -(vec.x * std::sin(angle)) + (vec.y * std::cos(angle)));
}

sf::Vector2<float64_t> Func::getRotated(const sf::Vector2<float64_t> &vec,
                                        const float64_t angle)
{
    return sf::Vector2<float64_t>(
        (vec.x * std::cos(angle)) + (vec.y * std::sin(angle)),
        -(vec.x * std::sin(angle)) + (vec.y * std::cos(angle)));
}

float64_t Func::getCoeff(const float64_t coeff, const Interp interp,
                         const bool limiter)
{
    float64_t res = 0.0;
    if (limiter && (coeff >= 1.0))
    {
        res = 1.0;
    }
    else if (limiter && (coeff <= 0.0))
    {
        res = 0.0;
    }
    else
    {
        switch (interp)
        {
        case Interp::LIN: {
            res = coeff;
            break;
        }
        case Interp::ACC: {
            res = coeff * coeff;
            break;
        }
        case Interp::BRA: {
            res = (2.0 - coeff) * coeff;
            break;
        }
        case Interp::SIN: {
            res = (std::sin((coeff - 0.5) * m_pi) + 1.0) * 0.5;
            break;
        }
        case Interp::SFO: {
            res = 1.0 / (1.0 + std::exp(-((2.0 * coeff) - 1.0) /
                                        (coeff * (1.0 - coeff))));
            break;
        }
        case Interp::SIN0: {
            res = (std::sin((coeff - 0.25) * m_2pi) + 1.0) * 0.5;
            break;
        }
        default: {
            res = 0.0;
            break;
        }
        }
    }
    return res;
}

float64_t Func::getCoeff(const float64_t x, const float64_t bigX,
                         const Interp interp, const bool limiter)
{
    return getCoeff(x / bigX, interp, limiter);
}

sf::Color Func::colorBalance(const sf::Color &color1, const sf::Color &color2,
                             const float64_t coeff, const Interp interp)
{
    const float64_t interpCoeff = getCoeff(coeff, interp, true);
    const float64_t oneMinusCoeff = 1.0 - interpCoeff;
    return sf::Color(static_cast<sf::Uint8>((color1.r * interpCoeff) +
                                            (color2.r * oneMinusCoeff)),
                     static_cast<sf::Uint8>((color1.g * interpCoeff) +
                                            (color2.g * oneMinusCoeff)),
                     static_cast<sf::Uint8>((color1.b * interpCoeff) +
                                            (color2.b * oneMinusCoeff)),
                     static_cast<sf::Uint8>((color1.a * interpCoeff) +
                                            (color2.a * oneMinusCoeff)));
}

std::string Func::getStringHourPrecise()
{
    const auto now = std::chrono::system_clock::now();
    std::tm localTime;
    const std::time_t timeTNow = std::chrono::system_clock::to_time_t(now);
    const errno_t err = ::localtime_s(&localTime, &timeTNow);
    std::string res = "error_time";
    if (0 == err)
    {
        const std::size_t bufferSize = 100;
        res = std::string(bufferSize, '\0');
        const std::size_t written =
            std::strftime(res.data(), bufferSize, "%H:%M:%S", &localTime);
        if (written > 0)
        {
            res.resize(written);
        }
        else
        {
            res.clear();
        }
    }
    return res;
}

std::string Func::getStringHourVeryPrecise()
{
    const std::chrono::time_point<std::chrono::system_clock> currentTime =
        std::chrono::system_clock::now();
    std::string format(12, 0);
    const std::chrono::duration<int64_t, std::ratio<1, 1'000'000'000>>::rep
        millis = (currentTime.time_since_epoch().count() / 1'000'000) % 1000;
    std::tm localTime;
    const std::time_t tt = std::chrono::system_clock::to_time_t(currentTime);
    const errno_t err = ::localtime_s(&localTime, &tt);
    const std::size_t written =
        ::strftime(&format[0], 12, "%H:%M:%S", &localTime);
    if (const int32_t writtenMilli = ::sprintf(
            &format[0], "%s:%03d", &format[0], static_cast<int32_t>(millis));
        (0 != err) || (0 == written) || (0 == writtenMilli))
    {
        format = "[error_time]";
    }
    return format;
}

std::array<uint64_t, 4> Func::getHourVeryPrecise()
{
    std::array<uint64_t, 4> res = {{0, 0, 0, 0}};
    const std::chrono::time_point<std::chrono::system_clock> currentTime =
        std::chrono::system_clock::now();
    const std::chrono::duration<int64_t, std::ratio<1, 1'000'000'000>>::rep
        millis = (currentTime.time_since_epoch().count() / 1'000'000) % 1000;
    std::tm localTime;
    const std::time_t tt = std::chrono::system_clock::to_time_t(currentTime);
    if (const errno_t err = ::localtime_s(&localTime, &tt); 0 == err)
    {
        res = {{static_cast<uint64_t>(localTime.tm_hour),
                static_cast<uint64_t>(localTime.tm_min),
                static_cast<uint64_t>(localTime.tm_sec),
                static_cast<uint64_t>(millis)}};
    }
    return res;
}

std::vector<std::string> Func::split(const std::string &s, const char delim)
{
    std::vector<std::string> res;
    std::back_insert_iterator<std::vector<std::string>> result =
        std::back_inserter(res);
    std::stringstream ss(s, std::ios_base::in | std::ios_base::out);
    std::string item;
    while (std::getline(ss, item, delim))
    {
        *(result++) = item;
    }
    return res;
}

std::vector<std::string> Func::split(const std::string_view &s,
                                     const std::string_view &delim)
{
    std::vector<std::string> res = {};
    std::size_t posStart = 0;
    std::size_t posEnd = 0;
    const std::size_t delimLen = delim.length();
    while ((posEnd = s.find(delim, posStart)) != std::string::npos)
    {
        res.emplace_back(s.substr(posStart, posEnd - posStart));
        posStart = posEnd + delimLen;
    }
    res.emplace_back(s.substr(posStart, std::string::npos));
    return res;
}

std::vector<std::u32string> Func::split(const std::u32string &s,
                                        const char32_t delim)
{
    std::vector<std::u32string> res;
    std::back_insert_iterator<std::vector<std::u32string>> result =
        std::back_inserter(res);
    std::basic_stringstream<char32_t, std::char_traits<char32_t>> ss(
        s, std::ios_base::in | std::ios_base::out);
    std::u32string item;
    while (std::getline(ss, item, delim))
    {
        *(result++) = item;
    }
    return res;
}

std::vector<std::u32string> Func::split(const std::u32string_view &s,
                                        const std::u32string_view &delim)
{
    std::vector<std::u32string> res = {};
    std::size_t posStart = 0;
    std::size_t posEnd = 0;
    const std::size_t delimLen = delim.length();
    while ((posEnd = s.find(delim, posStart)) != std::u32string::npos)
    {
        res.emplace_back(s.substr(posStart, posEnd - posStart));
        posStart = posEnd + delimLen;
    }
    res.emplace_back(s.substr(posStart, std::u32string::npos));
    return res;
}

uint64_t Func::imod(int64_t i1, const int64_t i2)
{
    while (i1 < 0)
    {
        i1 += i2;
    }
    while (i1 >= i2)
    {
        i1 -= i2;
    }
    return static_cast<uint64_t>(i1);
}

float64_t Func::dmod(float64_t numer, const float64_t denom)
{
    while (numer >= denom)
    {
        numer -= denom;
    }
    while (numer < 0.0)
    {
        numer += denom;
    }
    return numer;
}

float32_t Func::fMod(float32_t numer, const float32_t denom)
{
    while (numer >= denom)
    {
        numer -= denom;
    }
    while (numer < 0.0f)
    {
        numer += denom;
    }
    return numer;
}

uint64_t Func::power(const uint64_t base, const uint64_t exponent)
{
    uint64_t res = 1;
    if (0 != exponent)
    {
        res = base;
        for (uint64_t i = 1; i < exponent; ++i)
        {
            res *= base;
        }
    }
    return res;
}

sf::String Func::stringTosfString(const std::string_view &str)
{ // Can be useful to display accents properly
    std::basic_string<sf::Uint32> utf32str = {};
    sf::Utf8::toUtf32(str.begin(), str.end(), std::back_inserter(utf32str));
    return sf::String(utf32str);
}

sf::String Func::evaluateSpecialChars(const sf::String &str)
{
    sf::String res = "";
    std::size_t i = 0;
    const std::size_t sizeStr = str.getSize();
    while (i < sizeStr)
    {
        if (const sf::Uint32 c = str[i]; '\\' == c)
        {
            ++i;
            const sf::Uint32 n = str[i];
            switch (n)
            {
            case '\\': {
                res += n;
                break;
            }
            case 'n': {
                res += '\n';
                break;
            }
            case 't': {
                res += '\t';
                break;
            }
            case '<': {
                res += "\\<";
                break;
            }
            case '>': {
                res += "\\>";
                break;
            }
            default: {
                DEBUG_LOG("default reached");
                std::cerr << "Error: invalid special char found : " << c << n
                          << "\n";
                break;
            }
            }
        }
        else
        {
            res += c;
        }
        ++i;
    }
    return res;
}

std::vector<std::string> Func::getDir(const std::string &dir)
{
    std::vector<std::string> res = {};
    DIR *dp = nullptr;
    dirent *dirp = nullptr;
    if (nullptr == (dp = ::opendir(dir.c_str())))
    {
        std::cout << "Error opening " << dir << "\n";
    }
    else
    {
        while ((dirp = ::readdir(dp)) != nullptr)
        {
            res.emplace_back(static_cast<std::string>(dirp->d_name));
        }
        const int32_t err = ::closedir(dp);
        if (-1 == err)
        {
            std::cout << "Error closing " << dir << "\n";
        }
    }
    return res;
}

bool Func::fileExist(const std::string &path)
{
    const std::ifstream infile(path);
    return infile.good();
}

std::string Func::getKeyWordLine(const std::string_view &line)
{
    const std::size_t posEq = line.find("=", 0);
    std::string res = "";
    if (std::string::npos != posEq)
    {
        res = line.substr(0, posEq);
    }
    return res;
}

std::u32string Func::getKeyWordLine(const std::u32string_view &line)
{
    const std::size_t posEq = line.find(U"=", 0);
    std::u32string res = U"";
    if (std::u32string::npos != posEq)
    {
        res = line.substr(0, posEq);
    }
    return res;
}

std::string Func::getValueLine(const std::string_view &line)
{
    const std::size_t posEq = line.find("=", 0);
    std::string res = "";
    if (std::string::npos != posEq)
    {
        res = line.substr(posEq + 1, std::string::npos);
    }
    return res;
}

std::u32string Func::getValueLine(const std::u32string_view &line)
{
    const std::size_t posEq = line.find(U"=", 0);
    std::u32string res = U"";
    if (std::u32string::npos != posEq)
    {
        res = line.substr(posEq + 1, std::u32string::npos);
    }
    return res;
}

std::pair<std::string, std::string>
Func::getKeyValueLine(const std::string_view &line)
{
    const std::size_t posEq = line.find("=", 0);
    std::pair<std::string, std::string> res = {"", ""};
    if (std::string::npos != posEq)
    {
        res.first = line.substr(0, posEq);
        res.second = line.substr(posEq + 1, std::string::npos);
    }
    return res;
}

std::pair<std::u32string, std::u32string>
Func::getKeyValueLine(const std::u32string_view &line)
{
    const std::size_t posEq = line.find(U"=", 0);
    std::pair<std::u32string, std::u32string> res = {U"", U""};
    if (std::u32string::npos != posEq)
    {
        res.first = line.substr(0, posEq);
        res.second = line.substr(posEq + 1, std::u32string::npos);
    }
    return res;
}

bool Func::isFloat(const std::string &s)
{
    std::basic_istringstream<char, std::char_traits<char>, std::allocator<char>>
        iss(s);
    float32_t f = 0;
    iss >> std::noskipws >> f;
    // noskipws considers leading whitespace invalid
    // Check the entire string was consumed and if either failbit or badbit is
    // set
    return iss.eof() && (!iss.fail());
}

bool Func::isFloat(const std::u32string &s)
{
    std::basic_istringstream<char32_t, std::char_traits<char32_t>,
                             std::allocator<char32_t>>
        iss(s);
    float32_t f = 0;
    iss >> std::noskipws >> f;
    // noskipws considers leading whitespace invalid
    // Check the entire string was consumed and if either failbit or badbit is
    // set
    return iss.eof() && (!iss.fail());
}

bool Func::isPosInt(const std::string_view &s)
{
    const std::locale loc;
    return (!s.empty()) &&
           (std::find_if(s.begin(), s.end(), [&loc](const char c) {
                return 0 == std::isdigit(c, loc);
            }) == s.end());
}

bool Func::isPosInt(const std::u32string_view &s)
{
    const std::locale loc;
    return (!s.empty()) &&
           (std::find_if(s.begin(), s.end(), [&loc](const char c) {
                return 0 == std::isdigit(c, loc);
            }) == s.end());
}

uint64_t Func::str32ToLui(const std::u32string &s)
{
    uint64_t res = 0;
    if (isPosInt(s))
    {
        const std::size_t sizeS = s.size();
        for (std::size_t i = 0; i < sizeS; ++i)
        {
            res += (s[i] - U'0') * power(10, s.size() - 1 - i);
        }
    }
    return res;
}

uint64_t Func::str32HexToLui(const std::u32string &s)
{
    uint64_t res = 0;
    const std::size_t sizeS = s.size();
    for (std::size_t i = 0; i < sizeS; ++i)
    {
        uint64_t val = 0;
        if ((s[i] >= U'0') && (s[i] <= U'9'))
        {
            val = s[i] - U'0';
        }
        else if ((s[i] >= U'a') && (s[i] <= U'f'))
        {
            val = (10 + s[i]) - U'a';
        }
        else if ((s[i] >= U'A') && (s[i] <= U'F'))
        {
            val = (10 + s[i]) - U'A';
        }
        else
        {
            // Error, do nothing
        }
        res += val * power(16, s.size() - 1 - i);
    }
    return res;
}

float32_t Func::str32ToF(const std::u32string &s)
{
    float32_t res = 0.0f;
    if (isFloat(s))
    {
        const std::size_t posInit = U'-' == s[0];
        const std::size_t posPoint = s.find(U'.', 0);
        const std::size_t sizeS = s.size();
        for (std::size_t i = posInit; i < sizeS; ++i)
        {
            if (i != posPoint)
            {
                const std::size_t addOne = i > posPoint;
                res += static_cast<float32_t>(s[i] - U'0') *
                       std::pow(10.0f, static_cast<float32_t>(
                                           (posPoint - 1 - i) + addOne));
            }
        }
        if (0 != posInit)
        {
            res *= -1.0f;
        }
    }
    return res;
}

std::u32string Func::luiTo32Str(uint64_t n)
{
    std::u32string res = U"";
    do
    {
        res = std::u32string(1, (static_cast<char32_t>(n % 10) + U'0')) + res;
    } while ((n /= 10) > 0);
    return res;
}

std::u32string Func::luiTo32StrHex(uint64_t n)
{
    std::u32string res = U"";
    do
    {
        if ((n % 16) <= 9)
        {
            res =
                std::u32string(1, (static_cast<char32_t>(n % 16) + U'0')) + res;
        }
        else
        {
            res =
                std::u32string(1, (static_cast<char32_t>(n % 16) + U'a')) + res;
        }
    } while ((n /= 16) > 0);
    return res;
}

std::u32string Func::fTo32Str(float32_t n)
{
    std::u32string res = U"";
    do
    {
        res = std::u32string(
                  1, (static_cast<char32_t>(std::fmod(n, 10.0f)) + U'0')) +
              res;
    } while ((n /= 10.0f) > 1.0f);
    return res;
}

sf::Rect<int32_t> Func::getTextureRect(const sf::Texture *const texture)
{
    auto res = sf::Rect<int32_t>(0, 0, 0, 0);
    if (nullptr != texture)
    {
        res =
            sf::Rect<int32_t>(0, 0, static_cast<int32_t>(texture->getSize().x),
                              static_cast<int32_t>(texture->getSize().y));
    }
    return res;
}

Quaternion Func::getQuatRot(const float64_t angle,
                            const sf::Vector3<float64_t> &axe)
{
    const float64_t norm =
        std::sin(angle * 0.5) /
        std::sqrt((axe.x * axe.x) + (axe.y * axe.y) + (axe.z * axe.z));
    return Quaternion(std::cos(angle * 0.5), axe.x * norm, axe.y * norm,
                      axe.z * norm);
}

Quaternion Func::euler2Quaternion(const sf::Vector3<float64_t> &angle,
                                  const RotSeq rotSeq)
{
    auto res = Quaternion(0, 0, 0, 0);
    const float64_t c1 = std::cos(angle.x * 0.5);
    const float64_t c2 = std::cos(angle.y * 0.5);
    const float64_t c3 = std::cos(angle.z * 0.5);
    const float64_t s1 = std::sin(angle.x * 0.5);
    const float64_t s2 = std::sin(angle.y * 0.5);
    const float64_t s3 = std::sin(angle.z * 0.5);
    switch (rotSeq)
    {
    case RotSeq::ZYX: {
        res = Quaternion(
            (c1 * c2 * c3) + (s1 * s2 * s3), (s1 * c2 * c3) - (c1 * s2 * s3),
            (c1 * s2 * c3) + (s1 * c2 * s3), (c1 * c2 * s3) - (s1 * s2 * c3));
        break;
    }
    case RotSeq::ZYZ: {
        res = Quaternion(
            (c1 * c2 * c3) - (s1 * c2 * s3), (s1 * s2 * c3) - (c1 * s2 * s3),
            (c1 * s2 * c3) + (s1 * s2 * s3), (c1 * c2 * s3) + (s1 * c2 * c3));
        break;
    }
    case RotSeq::ZXY: {
        res = Quaternion(
            (c1 * c2 * c3) - (s1 * s2 * s3), (c1 * s2 * c3) - (s1 * c2 * s3),
            (c1 * s2 * s3) + (s1 * c2 * c3), (c1 * c2 * s3) + (s1 * s2 * c3));
        break;
    }
    case RotSeq::ZXZ: {
        res = Quaternion(
            (c1 * c2 * c3) - (s1 * c2 * s3), (c1 * s2 * c3) + (s1 * s2 * s3),
            (c1 * s2 * s3) - (s1 * s2 * c3), (c1 * c2 * s3) + (s1 * c2 * c3));
        break;
    }
    case RotSeq::YXZ: {
        res = Quaternion(
            (c1 * c2 * c3) + (s1 * s2 * s3), (c1 * s2 * c3) + (s1 * c2 * s3),
            (c1 * c2 * s3) - (s1 * s2 * c3), (s1 * c2 * c3) - (c1 * s2 * s3));
        break;
    }
    case RotSeq::YXY: {
        res = Quaternion(
            (c1 * c2 * c3) - (s1 * c2 * s3), (c1 * s2 * c3) + (s1 * s2 * s3),
            (c1 * c2 * s3) + (s1 * c2 * c3), (s1 * s2 * c3) - (c1 * s2 * s3));
        break;
    }
    case RotSeq::YZX: {
        res = Quaternion(
            (c1 * c2 * c3) - (s1 * s2 * s3), (c1 * s2 * s3) + (s1 * c2 * c3),
            (c1 * c2 * s3) + (s1 * s2 * c3), (c1 * s2 * c3) - (s1 * c2 * s3));
        break;
    }
    case RotSeq::YZY: {
        res = Quaternion(
            (c1 * c2 * c3) - (s1 * c2 * s3), (c1 * s2 * s3) - (s1 * s2 * c3),
            (c1 * c2 * s3) + (s1 * c2 * c3), (c1 * s2 * c3) + (s1 * s2 * s3));
        break;
    }
    case RotSeq::XYZ: {
        res = Quaternion(
            (c1 * c2 * c3) - (s1 * s2 * s3), (c1 * c2 * s3) + (s1 * s2 * c3),
            (c1 * s2 * c3) - (s1 * c2 * s3), (c1 * s2 * s3) + (s1 * c2 * c3));
        break;
    }
    case RotSeq::XYX: {
        res = Quaternion(
            (c1 * c2 * c3) - (s1 * c2 * s3), (c1 * c2 * s3) + (s1 * c2 * c3),
            (c1 * s2 * c3) + (s1 * s2 * s3), (c1 * s2 * s3) - (s1 * s2 * c3));
        break;
    }
    case RotSeq::XZY: {
        res = Quaternion(
            (c1 * c2 * c3) + (s1 * s2 * s3), (c1 * c2 * s3) - (s1 * s2 * c3),
            (s1 * c2 * c3) - (c1 * s2 * s3), (c1 * s2 * c3) + (s1 * c2 * s3));
        break;
    }
    case RotSeq::XZX: {
        res = Quaternion(
            (c1 * c2 * c3) - (s1 * c2 * s3), (c1 * c2 * s3) + (s1 * c2 * c3),
            (s1 * s2 * c3) - (c1 * s2 * s3), (c1 * s2 * c3) + (s1 * s2 * s3));
        break;
    }
    default: {
        DEBUG_LOG("default reached");
        break;
    }
    }
    return res;
}

sf::Vector3<float64_t>
Func::twoaxisrot(const float64_t r11, const float64_t r12, const float64_t r21,
                 const float64_t r31, const float64_t r32)
{
    return sf::Vector3<float64_t>(std::atan2(r11, r12), std::acos(r21),
                                  std::atan2(r31, r32));
}

sf::Vector3<float64_t> Func::threeaxisrot(const float64_t r11,
                                          const float64_t r12,
                                          const float64_t r21,
                                          const float64_t r31,
                                          const float64_t r32)
{
    return sf::Vector3<float64_t>(std::atan2(r31, r32), std::asin(r21),
                                  std::atan2(r11, r12));
}

sf::Vector3<float64_t> Func::quaternion2Euler(const Quaternion &q,
                                              const RotSeq rotSeq)
{
    auto res = sf::Vector3<float64_t>(0.0, 0.0, 0.0);
    switch (rotSeq)
    {
    case RotSeq::ZYX: {
        res = sf::Vector3<double>(
            std::atan2(2.0 * (q.z * q.t + q.x * q.y),
                       q.x * q.x - q.y * q.y - q.z * q.z + q.t * q.t),
            -std::asin(2.0 * (q.y * q.t - q.x * q.z)),
            std::atan2(2.0 * (q.y * q.z + q.x * q.t),
                       q.x * q.x + q.y * q.y - q.z * q.z - q.t * q.t));
        break;
    }
    case RotSeq::ZYZ: {
        res = sf::Vector3<double>(
            std::atan2(2.0 * (q.z * q.t - q.x * q.y),
                       2.0 * (q.y * q.t + q.x * q.z)),
            std::acos(q.x * q.x - q.y * q.y - q.z * q.z + q.t * q.t),
            std::atan2(2.0 * (q.z * q.t + q.x * q.y),
                       -2.0 * (q.y * q.t - q.x * q.z)));
        break;
    }
    case RotSeq::ZXY: {
        res = sf::Vector3<double>(
            std::atan2(-2.0 * (q.y * q.t - q.x * q.z),
                       q.x * q.x - q.y * q.y - q.z * q.z + q.t * q.t),
            std::asin(2.0 * (q.z * q.t + q.x * q.y)),
            std::atan2(-2.0 * (q.y * q.z - q.x * q.t),
                       q.x * q.x - q.y * q.y + q.z * q.z - q.t * q.t));
        break;
    }
    case RotSeq::ZXZ: {
        res = sf::Vector3<double>(
            std::atan2(2.0 * (q.y * q.t + q.x * q.z),
                       -2.0 * (q.z * q.t - q.x * q.y)),
            std::acos(q.x * q.x - q.y * q.y - q.z * q.z + q.t * q.t),
            std::atan2(2.0 * (q.y * q.t - q.x * q.z),
                       2.0 * (q.z * q.t + q.x * q.y)));
        break;
    }
    case RotSeq::YXZ: {
        res = sf::Vector3<double>(
            std::atan2(2.0 * (q.y * q.z + q.x * q.t),
                       q.x * q.x - q.y * q.y + q.z * q.z - q.t * q.t),
            std::asin(-2.0 * (q.z * q.t - q.x * q.y)),
            std::atan2(2.0 * (q.y * q.t + q.x * q.z),
                       q.x * q.x - q.y * q.y - q.z * q.z + q.t * q.t));
        break;
    }
    case RotSeq::YXY: {
        res = sf::Vector3<double>(
            std::atan2(2.0 * (q.y * q.z - q.x * q.t),
                       2.0 * (q.z * q.t + q.x * q.y)),
            std::acos(q.x * q.x - q.y * q.y + q.z * q.z - q.t * q.t),
            std::atan2(2.0 * (q.y * q.z + q.x * q.t),
                       -2.0 * (q.z * q.t - q.x * q.y)));
        break;
    }
    case RotSeq::YZX: {
        res = sf::Vector3<double>(
            std::atan2(-2.0 * (q.z * q.t - q.x * q.y),
                       q.x * q.x - q.y * q.y + q.z * q.z - q.t * q.t),
            std::asin(2.0 * (q.y * q.z + q.x * q.t)),
            std::atan2(-2.0 * (q.y * q.t - q.x * q.z),
                       q.x * q.x + q.y * q.y - q.z * q.z - q.t * q.t));
        break;
    }
    case RotSeq::YZY: {
        res = sf::Vector3<double>(
            std::atan2(2.0 * (q.z * q.t + q.x * q.y),
                       -2.0 * (q.y * q.z - q.x * q.t)),
            std::acos(q.x * q.x - q.y * q.y + q.z * q.z - q.t * q.t),
            std::atan2(2.0 * (q.z * q.t - q.x * q.y),
                       2.0 * (q.y * q.z + q.x * q.t)));
        break;
    }
    case RotSeq::XYZ: {
        res = sf::Vector3<double>(
            std::atan2(-2.0 * (q.y * q.z - q.x * q.t),
                       q.x * q.x + q.y * q.y - q.z * q.z - q.t * q.t),
            std::asin(-2.0 * (q.y * q.t + q.x * q.z)),
            std::atan2(-2.0 * (q.z * q.t - q.x * q.y),
                       q.x * q.x - q.y * q.y - q.z * q.z + q.t * q.t));
        break;
    }
    case RotSeq::XYX: {
        res = sf::Vector3<double>(
            std::atan2(2.0 * (q.y * q.z + q.x * q.t),
                       -2.0 * (q.y * q.t - q.x * q.z)),
            std::acos(q.x * q.x + q.y * q.y - q.z * q.z - q.t * q.t),
            std::atan2(2.0 * (q.y * q.z - q.x * q.t),
                       2.0 * (q.y * q.t + q.x * q.z)));
        break;
    }
    case RotSeq::XZY: {
        res = sf::Vector3<double>(
            std::atan2(2.0 * (q.y * q.t + q.x * q.z),
                       q.x * q.x + q.y * q.y - q.z * q.z - q.t * q.t),
            std::asin(-2.0 * (q.y * q.z - q.x * q.t)),
            std::atan2(2.0 * (q.z * q.t + q.x * q.y),
                       q.x * q.x - q.y * q.y + q.z * q.z - q.t * q.t));
        break;
    }
    case RotSeq::XZX: {
        res = sf::Vector3<double>(
            std::atan2(2.0 * (q.y * q.t - q.x * q.z),
                       2.0 * (q.y * q.z + q.x * q.t)),
            std::acos(q.x * q.x + q.y * q.y - q.z * q.z - q.t * q.t),
            std::atan2(2.0 * (q.y * q.t + q.x * q.z),
                       -2.0 * (q.y * q.z - q.x * q.t)));
        break;
    }
    default: {
        DEBUG_LOG("default reached");
        break;
    }
    }
    return res;
}

std::back_insert_iterator<std::u32string>
Func::utf8ToUtf32(std::string::const_iterator be,
                  const std::string::const_iterator en,
                  std::back_insert_iterator<std::u32string> output)
{
    // Some useful precomputed data
    static const std::array<uint8_t, 256> trailing = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
         1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
         3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5}};
    static const std::array<char32_t, 6> offsets = {
        {0x00'00'00'00, 0x00'00'30'80, 0x00'0E'20'80, 0x03'C8'20'80,
         0xFA'08'20'80U, 0x82'08'20'80U}};
    while (be < en)
    {
        char32_t codepoint = 0;
        // decode the character
        if (const uint8_t trailingBytes =
                trailing[static_cast<uint64_t>(static_cast<uint8_t>(*be))];
            (be + trailingBytes) < en)
        {
            if (trailingBytes <= 5)
            {
                for (uint8_t i = 0; i <= trailingBytes; ++i)
                {
                    if (i == trailingBytes)
                    {
                        codepoint += static_cast<uint8_t>(*be++);
                    }
                    else
                    {
                        (codepoint += static_cast<uint8_t>(*be++)) <<= 6;
                    }
                }
            }
            codepoint -= offsets[trailingBytes];
        }
        else
        {
            // Incomplete character
            be = en;
        }
        *output++ = codepoint;
    }
    return output;
}

std::back_insert_iterator<std::string>
Func::utf32ToUtf8(std::u32string::const_iterator be,
                  const std::u32string::const_iterator en,
                  std::back_insert_iterator<std::string> output)
{
    // Some useful precomputed data
    static const std::array<uint8_t, 7> firstBytes = {
        {0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC}};
    while (be < en)
    {
        // Valid character
        // Get the number of bytes to write
        char32_t input = *be++;
        std::size_t bytestoWrite = 1;
        if (input < 0x80)
        {
            bytestoWrite = 1;
        }
        else if (input < 0x800)
        {
            bytestoWrite = 2;
        }
        else if (input < 0x1'00'00)
        {
            bytestoWrite = 3;
        }
        else if (input <= 0x00'10'FF'FF)
        {
            bytestoWrite = 4;
        }
        else
        {
            // Nothing to do
        }

        // Extract the bytes to write
        std::array<uint8_t, 4> bytes;
        if (bytestoWrite <= 4)
        {
            for (std::size_t i = 1; i <= bytestoWrite; ++i)
            {
                if (i == bytestoWrite)
                {
                    bytes[bytestoWrite - i] =
                        static_cast<uint8_t>(input | firstBytes[bytestoWrite]);
                }
                else
                {
                    bytes[bytestoWrite - i] =
                        static_cast<uint8_t>((input | 0x80) & 0xBF);
                    input >>= 6;
                }
            }
        }
        // Add them to the output
        output = std::copy(bytes.data(), bytes.data() + bytestoWrite, output);
    }
    return output;
}

std::u32string Func::str8Tostr32(const std::string_view &s)
{
    std::u32string res = U"";
    std::string str = {s.begin(), s.end()};
    utf8ToUtf32(str.begin(), str.end(), std::back_inserter(res));
    return res;
}

std::string Func::str32Tostr8(const std::u32string_view &s)
{
    std::string res = "";
    std::u32string str = {s.begin(), s.end()};
    utf32ToUtf8(str.begin(), str.end(), std::back_inserter(res));
    return res;
}

sf::Texture Func::loadTexture(const std::string &path,
                              const sf::Rect<int32_t> &area)
{
    sf::Image image;
    sf::Texture texture;
    image.loadFromFile(path);
    texture.loadFromImage(image, area);
    return texture;
}

sf::Texture Func::loadTexture(const std::string &path)
{
    return loadTexture(path, sf::Rect<int32_t>(0, 0, 0, 0));
}

} // namespace segment_d1
