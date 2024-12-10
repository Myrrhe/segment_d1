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

#ifndef QUATERNION_HPP
#define QUATERNION_HPP
#include "Types.hpp"
#include <complex>
#include <cstdint>
#include <iostream>
#include <istream>

namespace segment_d1
{

class Quaternion final
{
public:
    Quaternion(const float64_t newX, const float64_t newY, const float64_t newZ,
               const float64_t newT);
    Quaternion(const std::complex<float64_t> newXY,
               const std::complex<float64_t> newZT);
    Quaternion(const Quaternion &newXYZT);
    ~Quaternion();
    Quaternion &operator=(const Quaternion &right);
    // std::partial_ordering operator<=>(const Quaternion& right) const;
    const float64_t &operator[](const std::size_t i) const;
    float64_t &operator[](const std::size_t i);
    Quaternion &operator++();
    Quaternion operator++(const int32_t);
    Quaternion &operator--();
    Quaternion operator--(const int32_t);
    Quaternion &operator+=(const Quaternion &right);
    Quaternion &operator-=(const Quaternion &right);
    Quaternion &operator*=(const Quaternion &right);
    Quaternion &operator/=(const Quaternion &right);
    Quaternion operator+() const;
    Quaternion operator-() const;
    [[nodiscard]] float64_t getNormSquare() const;
    [[nodiscard]] float64_t getNorm() const;
    [[nodiscard]] Quaternion getConjugation() const;
    [[nodiscard]] Quaternion getReciprocal() const;
    Quaternion &setNorm(const float64_t newNorm);
    Quaternion &conjugate();
    Quaternion &reciproc();
    [[nodiscard]] float64_t getX() const;
    [[nodiscard]] float64_t getY() const;
    [[nodiscard]] float64_t getZ() const;
    [[nodiscard]] float64_t getT() const;
    [[nodiscard]] std::complex<float64_t> getXY() const;
    [[nodiscard]] std::complex<float64_t> getZT() const;
    void setX(const float64_t newX);
    void setY(const float64_t newY);
    void setZ(const float64_t newZ);
    void setT(const float64_t newT);
    void setXY(const float64_t newX, const float64_t newY);
    void setXY(const std::complex<float64_t> newXY);
    void setXYZT(const float64_t newX, const float64_t newY,
                 const float64_t newZ, const float64_t newT);
    void setXYZT(const std::complex<float64_t> newXY,
                 const std::complex<float64_t> newZT);
    void setXYZT(const Quaternion &newXYZT);

    static const float64_t epsilon;

    float64_t x;
    float64_t y;
    float64_t z;
    float64_t t;

private:
    friend bool operator==(const Quaternion &left, const Quaternion &right)
    {
        return ((std::abs(left.x - right.x) <= epsilon) &&
                (std::abs(left.y - right.y) <= epsilon) &&
                (std::abs(left.z - right.z) <= epsilon) &&
                (std::abs(left.t - right.t) <= epsilon));
    }

    friend bool operator!=(const Quaternion &left, const Quaternion &right)
    {
        return ((std::abs(left.x - right.x) > epsilon) ||
                (std::abs(left.y - right.y) > epsilon) ||
                (std::abs(left.z - right.z) > epsilon) ||
                (std::abs(left.t - right.t) > epsilon));
    }

    friend bool operator>(const Quaternion &left, const Quaternion &right)
    {
        return ((left.x > right.x) && (left.y > right.y) &&
                (left.z > right.z) && (left.t > right.t));
    }

    friend bool operator<(const Quaternion &left, const Quaternion &right)
    {
        return ((left.x < right.x) && (left.y < right.y) &&
                (left.z < right.z) && (left.t < right.t));
    }

    friend bool operator>=(const Quaternion &left, const Quaternion &right)
    {
        return ((left.x >= right.x) && (left.y >= right.y) &&
                (left.z >= right.z) && (left.t >= right.t));
    }

    friend bool operator<=(const Quaternion &left, const Quaternion &right)
    {
        return ((left.x <= right.x) && (left.y <= right.y) &&
                (left.z <= right.z) && (left.t <= right.t));
    }

    friend Quaternion operator+(const Quaternion &left, const Quaternion &right)
    {
        return Quaternion(left.x + right.x, left.y + right.y, left.z + right.z,
                          left.t + right.t);
    }

    friend Quaternion operator-(const Quaternion &left, const Quaternion &right)
    {
        return Quaternion(left.x - right.x, left.y - right.y, left.z - right.z,
                          left.t - right.t);
    }

    friend Quaternion operator*(const Quaternion &left, const Quaternion &right)
    {
        return Quaternion(
            (left.x * right.x) - (left.y * right.y) - (left.z * right.z) -
                (left.t * right.t),
            ((left.x * right.y) + (left.y * right.x) + (left.z * right.t)) -
                (left.t * right.z),
            ((left.x * right.z) + (left.z * right.x) + (left.t * right.y)) -
                (left.y * right.t),
            ((left.x * right.t) + (left.y * right.z) + (left.t * right.x)) -
                (left.z * right.y));
    }

    friend Quaternion operator/(const Quaternion &left, const Quaternion &right)
    {
        return Quaternion(left.x, left.y, left.z, left.t) *
               (right.getReciprocal());
    }

    friend std::ostream &operator<<(std::ostream &os, const Quaternion &q)
    {
        os << '(' << q.x << ", " << q.y << ", " << q.z << ", " << q.t << ')';
        return os;
    }
};

} // namespace segment_d1

#endif // QUATERNION_HPP
