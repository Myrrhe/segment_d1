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

#ifndef FUNC_HPP
#define FUNC_HPP
#include "Global.hpp"
#include "Quaternion.hpp"
#include "StaticObject.hpp"
#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>
#include <istream>
#include <iterator>
#include <ostream>

namespace segment_d1
{

std::ostream &operator<<(std::ostream &os, const sf::Color &right);

std::ostream &operator<<(std::ostream &os, const sf::Vector2<int32_t> &right);
std::ostream &operator<<(std::ostream &os, const sf::Vector2<uint32_t> &right);
std::ostream &operator<<(std::ostream &os, const sf::Vector2<float32_t> &right);
std::ostream &operator<<(std::ostream &os, const sf::Vector2<float64_t> &right);

std::ostream &operator<<(std::ostream &os, const sf::Rect<int32_t> &right);
std::ostream &operator<<(std::ostream &os, const sf::Rect<float32_t> &right);
std::ostream &operator<<(std::ostream &os, const sf::Rect<float64_t> &right);

std::ostream &operator<<(std::ostream &os, const sf::Transform &right);

std::ostream &operator<<(std::ostream &os, const sf::Time &right);

std::ostream &operator<<(std::ostream &os,
                         const std::vector<std::string> &right);
std::ostream &operator<<(std::ostream &os, const std::vector<uint64_t> &right);
std::ostream &operator<<(std::ostream &os, const std::vector<float64_t> &right);

sf::Rect<int32_t> operator|(const sf::Rect<int32_t> &left,
                            const sf::Rect<int32_t> &right);
sf::Rect<float32_t> operator|(const sf::Rect<float32_t> &left,
                              const sf::Rect<float32_t> &right);
sf::Rect<float64_t> operator|(const sf::Rect<float64_t> &left,
                              const sf::Rect<float64_t> &right);

sf::Rect<int32_t> operator+(const sf::Rect<int32_t> &left,
                            const sf::Vector2<int32_t> &right);
sf::Rect<float32_t> operator+(const sf::Rect<float32_t> &left,
                              const sf::Vector2<float32_t> &right);
sf::Rect<float64_t> operator+(const sf::Rect<float64_t> &left,
                              const sf::Vector2<float64_t> &right);

sf::Rect<int32_t> &operator+=(sf::Rect<int32_t> &left,
                              const sf::Vector2<int32_t> &right);
sf::Rect<float32_t> &operator+=(sf::Rect<float32_t> &left,
                                const sf::Vector2<float32_t> &right);
sf::Rect<float64_t> &operator+=(sf::Rect<float64_t> &left,
                                const sf::Vector2<float64_t> &right);

sf::Rect<int32_t> operator-(const sf::Rect<int32_t> &left,
                            const sf::Vector2<int32_t> &right);
sf::Rect<float32_t> operator-(const sf::Rect<float32_t> &left,
                              const sf::Vector2<float32_t> &right);
sf::Rect<float64_t> operator-(const sf::Rect<float64_t> &left,
                              const sf::Vector2<float64_t> &right);

sf::Rect<int32_t> &operator-=(sf::Rect<int32_t> &left,
                              const sf::Vector2<int32_t> &right);
sf::Rect<float32_t> &operator-=(sf::Rect<float32_t> &left,
                                const sf::Vector2<float32_t> &right);
sf::Rect<float64_t> &operator-=(sf::Rect<float64_t> &left,
                                const sf::Vector2<float64_t> &right);

sf::Rect<int32_t> operator*(const sf::Rect<int32_t> &left, int32_t right);
sf::Rect<float32_t> operator*(const sf::Rect<float32_t> &left, float32_t right);
sf::Rect<float64_t> operator*(const sf::Rect<float64_t> &left, float64_t right);

sf::Rect<int32_t> &operator*=(sf::Rect<int32_t> &left, int32_t right);
sf::Rect<float32_t> &operator*=(sf::Rect<float32_t> &left, float32_t right);
sf::Rect<float64_t> &operator*=(sf::Rect<float64_t> &left, float64_t right);

sf::Rect<int32_t> operator/(const sf::Rect<int32_t> &left, int32_t right);
sf::Rect<float32_t> operator/(const sf::Rect<float32_t> &left, float32_t right);
sf::Rect<float64_t> operator/(const sf::Rect<float64_t> &left, float64_t right);

sf::Rect<int32_t> &operator/=(sf::Rect<int32_t> &left, int32_t right);
sf::Rect<float32_t> &operator/=(sf::Rect<float32_t> &left, float32_t right);
sf::Rect<float64_t> &operator/=(sf::Rect<float64_t> &left, float64_t right);

sf::Rect<int32_t> operator*(const sf::Rect<int32_t> &left,
                            const sf::Vector2<int32_t> &right);
sf::Rect<float32_t> operator*(const sf::Rect<float32_t> &left,
                              const sf::Vector2<float32_t> &right);
sf::Rect<float64_t> operator*(const sf::Rect<float64_t> &left,
                              const sf::Vector2<float64_t> &right);

sf::Rect<int32_t> &operator*=(sf::Rect<int32_t> &left,
                              const sf::Vector2<int32_t> &right);
sf::Rect<float32_t> &operator*=(sf::Rect<float32_t> &left,
                                const sf::Vector2<float32_t> &right);
sf::Rect<float64_t> &operator*=(sf::Rect<float64_t> &left,
                                const sf::Vector2<float64_t> &right);

sf::Rect<int32_t> operator/(const sf::Rect<int32_t> &left,
                            const sf::Vector2<int32_t> &right);
sf::Rect<float32_t> operator/(const sf::Rect<float32_t> &left,
                              const sf::Vector2<float32_t> &right);
sf::Rect<float64_t> operator/(const sf::Rect<float64_t> &left,
                              const sf::Vector2<float64_t> &right);

sf::Rect<int32_t> &operator/=(sf::Rect<int32_t> &left,
                              const sf::Vector2<int32_t> &right);
sf::Rect<float32_t> &operator/=(sf::Rect<float32_t> &left,
                                const sf::Vector2<float32_t> &right);
sf::Rect<float64_t> &operator/=(sf::Rect<float64_t> &left,
                                const sf::Vector2<float64_t> &right);

int32_t operator*(const sf::Vector2<int32_t> &left,
                  const sf::Vector2<int32_t> &right);
uint32_t operator*(const sf::Vector2<uint32_t> &left,
                   const sf::Vector2<uint32_t> &right);
float32_t operator*(const sf::Vector2<float32_t> &left,
                    const sf::Vector2<float32_t> &right);
float64_t operator*(const sf::Vector2<float64_t> &left,
                    const sf::Vector2<float64_t> &right);

int32_t operator^(const sf::Vector2<int32_t> &left,
                  const sf::Vector2<int32_t> &right);
float32_t operator^(const sf::Vector2<float32_t> &left,
                    const sf::Vector2<float32_t> &right);
float64_t operator^(const sf::Vector2<float64_t> &left,
                    const sf::Vector2<float64_t> &right);

class Func final : public StaticObject
{
public:
#if DEBUG
#define DEBUG_LOG(...)                                                         \
    {                                                                          \
        char debugLogStr[100];                                                 \
        sprintf(debugLogStr, __VA_ARGS__);                                     \
        std::cout << "[" << __FILE__ << "][" << __FUNCTION__ << "][Line "      \
                  << __LINE__ << "] " << debugLogStr << std::endl;             \
    }
#else
#define DEBUG_LOG(...)
#endif // DEBUG

    static constexpr float64_t m_e = 2.71828182845904523536;
    static constexpr float64_t m_log2e = 1.44269504088896340736;
    static constexpr float64_t m_log10e = 0.434294481903251827651;
    static constexpr float64_t m_ln2 = 0.693147180559945309417;
    static constexpr float64_t m_ln10 = 2.30258509299404568402;
    static constexpr float64_t m_pi = 3.14159265358979323846;
    static constexpr float64_t m_2pi = 6.28318530717958647692;
    static constexpr float64_t m_pi_2 = 1.57079632679489661923;
    static constexpr float64_t m_pi_4 = 0.785398163397448309616;
    static constexpr float64_t m_1_pi = 0.318309886183790671538;
    static constexpr float64_t m_2_pi = 0.636619772367581343076;
    static constexpr float64_t m_2_sqrtpi = 1.12837916709551257390;
    static constexpr float64_t m_sqrt2 = 1.41421356237309504880;
    static constexpr float64_t m_1_sqrt2 = 0.707106781186547524401;
    static constexpr float64_t m_epsilon = 0.00000000000000000001;

    static constexpr float64_t m_1_60s = 1.0 / 60.0;

    static constexpr float32_t m_e_f = 2.71828182845904523536f;
    static constexpr float32_t m_log2e_f = 1.44269504088896340736f;
    static constexpr float32_t m_log10e_f = 0.434294481903251827651f;
    static constexpr float32_t m_ln2_f = 0.693147180559945309417f;
    static constexpr float32_t m_ln10_f = 2.30258509299404568402f;
    static constexpr float32_t m_pi_f = 3.14159265358979323846f;
    static constexpr float32_t m_2pi_f = 6.28318530717958647692f;
    static constexpr float32_t m_pi_2_f = 1.57079632679489661923f;
    static constexpr float32_t m_pi_4_f = 0.785398163397448309616f;
    static constexpr float32_t m_1_pi_f = 0.318309886183790671538f;
    static constexpr float32_t m_2_pi_f = 0.636619772367581343076f;
    static constexpr float32_t m_2_sqrtpi_f = 1.12837916709551257390f;
    static constexpr float32_t m_sqrt2_f = 1.41421356237309504880f;
    static constexpr float32_t m_1_sqrt2_f = 0.707106781186547524401f;
    static constexpr float32_t m_epsilon_f = 0.00000000000000000001f;

    static constexpr float32_t m_1_60sf = 1.0f / 60.0f;

    enum class Interp : uint64_t
    {
        LIN,
        ACC,
        BRA,
        SIN,
        SFO,
        SIN0
    };

    static sf::Vector2<float32_t> flooring(const sf::Vector2<float32_t> &v);

    static float32_t getNorm(const sf::Vector2<float32_t> &v);
    static float64_t getNorm(const sf::Vector2<float64_t> &v);

    [[nodiscard]] static float32_t
    getNormSquared(const sf::Vector2<float32_t> &v);
    [[nodiscard]] static float64_t
    getNormSquared(const sf::Vector2<float64_t> &v);

    [[nodiscard]] static sf::Vector2<int32_t>
    getInverted(const sf::Vector2<int32_t> &v);
    [[nodiscard]] static sf::Vector2<float32_t>
    getInverted(const sf::Vector2<float32_t> &v);
    [[nodiscard]] static sf::Vector2<float64_t>
    getInverted(const sf::Vector2<float64_t> &v);

    static sf::Vector2<float32_t>
    getNormalized(const sf::Vector2<float32_t> &v);
    static sf::Vector2<float64_t>
    getNormalized(const sf::Vector2<float64_t> &v);

    [[nodiscard]] static float32_t radToDeg(const float32_t radians);
    [[nodiscard]] static float64_t radToDeg(const float64_t radians);

    [[nodiscard]] static float32_t degToRad(const float32_t degree);
    [[nodiscard]] static float64_t degToRad(const float64_t degree);

    // Angle in radians
    static float32_t getRotationAngle(const sf::Vector2<float32_t> &v);
    // Angle in radians
    static float64_t getRotationAngle(const sf::Vector2<float64_t> &v);

    // Angle in radians
    static float32_t getAngleBetween(const sf::Vector2<float32_t> &v1,
                                     const sf::Vector2<float32_t> &v2);
    // Angle in radians
    static float64_t getAngleBetween(const sf::Vector2<float64_t> &v1,
                                     const sf::Vector2<float64_t> &v2);

    static sf::Vector2<float32_t> getRotated(const sf::Vector2<float32_t> &vec,
                                             const float32_t angle);
    static sf::Vector2<float64_t> getRotated(const sf::Vector2<float64_t> &vec,
                                             const float64_t angle);

    static float64_t getCoeff(const float64_t coeff, const Interp interp,
                              const bool limiter);
    static float64_t getCoeff(const float64_t x, const float64_t bigX,
                              const Interp interp, const bool limiter);

    static sf::Color colorBalance(const sf::Color &color1,
                                  const sf::Color &color2, float64_t coeff,
                                  Interp interp);

    static std::string getStringHourPrecise();
    static std::string getStringHourVeryPrecise();
    static std::array<uint64_t, 4> getHourVeryPrecise();

    static std::vector<std::string> split(const std::string &s,
                                          const char delim);

    static std::vector<std::string> split(const std::string_view &s,
                                          const std::string_view &delim);

    static std::vector<std::u32string> split(const std::u32string &s,
                                             const char32_t delim);

    static std::vector<std::u32string> split(const std::u32string_view &s,
                                             const std::u32string_view &delim);

    [[nodiscard]] static uint64_t imod(int64_t i1, const int64_t i2);

    [[nodiscard]] static float64_t dmod(float64_t numer, const float64_t denom);

    [[nodiscard]] static float32_t fMod(float32_t numer, const float32_t denom);

    [[nodiscard]] static uint64_t power(const uint64_t base,
                                        const uint64_t exponent);

    static sf::String stringTosfString(const std::string_view &str);

    static sf::String evaluateSpecialChars(const sf::String &str);

    static std::vector<std::string> getDir(const std::string &dir);

    static bool fileExist(const std::string &path);

    static std::string getKeyWordLine(const std::string_view &line);
    static std::u32string getKeyWordLine(const std::u32string_view &line);

    static std::string getValueLine(const std::string_view &line);
    static std::u32string getValueLine(const std::u32string_view &line);

    static std::pair<std::string, std::string>
    getKeyValueLine(const std::string_view &line);
    static std::pair<std::u32string, std::u32string>
    getKeyValueLine(const std::u32string_view &line);

    static bool isFloat(const std::string &s);

    static bool isFloat(const std::u32string &s);

    static bool isPosInt(const std::string_view &s);

    static bool isPosInt(const std::u32string_view &s);

    static float32_t str32ToF(const std::u32string &s);

    static uint64_t str32ToLui(const std::u32string &s);

    static uint64_t str32HexToLui(const std::u32string &s);

    static std::u32string luiTo32Str(uint64_t n);

    static std::u32string luiTo32StrHex(uint64_t n);

    static std::u32string fTo32Str(float32_t n);

    static sf::Rect<int32_t> getTextureRect(const sf::Texture *const texture);

    enum class RotSeq : uint64_t
    {
        ZYX,
        ZYZ,
        ZXY,
        ZXZ,
        YXZ,
        YXY,
        YZX,
        YZY,
        XYZ,
        XYX,
        XZY,
        XZX
    };

    static Quaternion getQuatRot(const float64_t angle,
                                 const sf::Vector3<float64_t> &axe);

    static Quaternion euler2Quaternion(const sf::Vector3<float64_t> &angle,
                                       const RotSeq rotSeq);

    static sf::Vector3<float64_t>
    twoaxisrot(const float64_t r11, const float64_t r12, const float64_t r21,
               const float64_t r31, const float64_t r32);

    static sf::Vector3<float64_t>
    threeaxisrot(const float64_t r11, const float64_t r12, const float64_t r21,
                 const float64_t r31, const float64_t r32);

    static sf::Vector3<float64_t> quaternion2Euler(const Quaternion &q,
                                                   const RotSeq rotSeq);

    static std::back_insert_iterator<std::u32string>
    utf8ToUtf32(std::string::const_iterator be,
                const std::string::const_iterator en,
                std::back_insert_iterator<std::u32string> output);

    static std::back_insert_iterator<std::string>
    utf32ToUtf8(std::u32string::const_iterator be,
                const std::u32string::const_iterator en,
                std::back_insert_iterator<std::string> output);

    static std::u32string str8Tostr32(const std::string_view &s);

    static std::string str32Tostr8(const std::u32string_view &s);

    static sf::Texture loadTexture(const std::string &path,
                                   const sf::Rect<int32_t> &area);
    static sf::Texture loadTexture(const std::string &path);
};

} // namespace segment_d1

#endif // FUNC_HPP
