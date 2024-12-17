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

#include "Quaternion.hpp"
#include <cmath>

namespace segment_d1
{

const float64_t Quaternion::epsilon = 0.000000000001;

Quaternion::Quaternion(const float64_t newX, const float64_t newY,
                       const float64_t newZ, const float64_t newT)
    : x(newX), y(newY), z(newZ), t(newT)
{
}

Quaternion::Quaternion(const std::complex<float64_t> newXY,
                       const std::complex<float64_t> newZT)
    : x(newXY.real()), y(newXY.real()), z(newZT.imag()), t(newZT.imag())
{
}

Quaternion::Quaternion(const Quaternion &newXYZT) = default;

Quaternion::~Quaternion() = default;

Quaternion &Quaternion::operator=(const Quaternion &right) = default;

/*
std::partial_ordering Quaternion::operator<=>(const Quaternion& right) const
{
    if (x < right.x && y < right.y && z < right.z && t < right.t)
    {
        return std::partial_ordering::less;
    }
    else if (x > right.x && y > right.y && z > right.z && t > right.t)
    {
        return std::partial_ordering::greater;
    }
    else if (std::abs(x - right.x) <= epsilon
          && std::abs(y - right.y) <= epsilon
          && std::abs(z - right.z) <= epsilon
          && std::abs(t - right.t) <= epsilon)
    {
        return std::partial_ordering::equivalent;
    }
    else
    {
        return std::partial_ordering::unordered;
    }
}
*/

const float64_t &Quaternion::operator[](const std::size_t i) const
{
    const std::size_t index = i % 4UL;
    const float64_t *res = &t;
    if (0UL == index)
    {
        res = &x;
    }
    else if (1UL == index)
    {
        res = &y;
    }
    else if (2UL == index)
    {
        res = &z;
    }
    else
    {
        // Nothing to do
    }
    return *res;
}

float64_t &Quaternion::operator[](const std::size_t i)
{
    const std::size_t index = i % 4UL;
    float64_t &res = x;
    if (0UL == index)
    {
        res = x;
    }
    else if (1UL == index)
    {
        res = y;
    }
    else if (2UL == index)
    {
        res = z;
    }
    else
    {
        res = t;
    }
    return res;
}

Quaternion Quaternion::operator+() const { return Quaternion(x, y, z, t); }

Quaternion Quaternion::operator-() const { return Quaternion(-x, -y, -z, -t); }

Quaternion &Quaternion::operator++()
{
    x += 1.0;
    return *this;
}

Quaternion Quaternion::operator++(const int32_t)
{
    const Quaternion res(*this);
    ++(*this);
    return res;
}

Quaternion &Quaternion::operator--()
{
    x -= 1.0;
    return *this;
}

Quaternion Quaternion::operator--(const int32_t)
{
    const Quaternion res(*this);
    --(*this);
    return res;
}

Quaternion &Quaternion::operator+=(const Quaternion &right)
{
    x += right.x;
    y += right.y;
    z += right.z;
    t += right.t;
    return *this;
}

Quaternion &Quaternion::operator-=(const Quaternion &right)
{
    x -= right.x;
    y -= right.y;
    z -= right.z;
    t -= right.t;
    return *this;
}

Quaternion &Quaternion::operator*=(const Quaternion &right)
{
    const float64_t newX =
        (x * right.x) - (y * right.y) - (z * right.z) - (t * right.t);
    const float64_t newY =
        ((x * right.y) + (y * right.x) + (z * right.t)) - (t * right.z);
    const float64_t newZ =
        ((x * right.z) + (z * right.x) + (t * right.y)) - (y * right.t);
    const float64_t newT =
        ((x * right.t) + (y * right.z) + (t * right.x)) - (z * right.y);
    x = newX;
    y = newY;
    z = newZ;
    t = newT;
    return *this;
}

Quaternion &Quaternion::operator/=(const Quaternion &right)
{
    *this = *this / right;
    return *this;
}

float64_t Quaternion::getNormSquare() const
{
    return (x * x) + (y * y) + (z * z) + (t * t);
}

float64_t Quaternion::getNorm() const
{
    return std::sqrt((x * x) + (y * y) + (z * z) + (t * t));
}

Quaternion Quaternion::getConjugation() const
{
    return Quaternion(x, -y, -z, -t);
}

Quaternion Quaternion::getReciprocal() const
{
    const float64_t divisor = (x * x) + (y * y) + (z * z) + (t * t);
    return Quaternion(x / divisor, y / divisor, z / divisor, t / divisor);
}

Quaternion &Quaternion::setNorm(const float64_t newNorm)
{
    const float64_t mul =
        newNorm / std::sqrt((x * x) + (y * y) + (z * z) + (t * t));
    x *= mul;
    y *= mul;
    z *= mul;
    t *= mul;
    return *this;
}

Quaternion &Quaternion::conjugate()
{
    y *= -1.0;
    z *= -1.0;
    z *= -1.0;
    return *this;
}

Quaternion &Quaternion::reciproc()
{
    const float64_t divisor = (x * x) + (y * y) + (z * z) + (t * t);
    x /= divisor;
    y /= -divisor;
    z /= -divisor;
    t /= -divisor;
    return *this;
}

float64_t Quaternion::getX() const { return x; }

float64_t Quaternion::getY() const { return y; }

float64_t Quaternion::getZ() const { return z; }

float64_t Quaternion::getT() const { return t; }

std::complex<float64_t> Quaternion::getXY() const
{
    return std::complex<double>(x, y);
}

std::complex<float64_t> Quaternion::getZT() const
{
    return std::complex<float64_t>(z, t);
}

void Quaternion::setX(const float64_t newX) { x = newX; }

void Quaternion::setY(const float64_t newY) { y = newY; }

void Quaternion::setZ(const float64_t newZ) { z = newZ; }

void Quaternion::setT(const float64_t newT) { t = newT; }

void Quaternion::setXY(const float64_t newX, const float64_t newY)
{
    x = newX;
    y = newY;
}

void Quaternion::setXY(const std::complex<float64_t> newXY)
{
    x = newXY.real();
    y = newXY.imag();
}

void Quaternion::setXYZT(const float64_t newX, const float64_t newY,
                         const float64_t newZ, const float64_t newT)
{
    x = newX;
    y = newY;
    z = newZ;
    t = newT;
}

void Quaternion::setXYZT(const std::complex<float64_t> newXY,
                         const std::complex<float64_t> newZT)
{
    x = newXY.real();
    y = newXY.imag();
    z = newZT.real();
    t = newZT.imag();
}

void Quaternion::setXYZT(const Quaternion &newXYZT)
{
    x = newXYZT.x;
    y = newXYZT.y;
    z = newXYZT.z;
    t = newXYZT.t;
}

} // namespace segment_d1
