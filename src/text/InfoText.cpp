#include "text/InfoText.hpp"
#include "Constants.hpp"
#include <cassert>

namespace segment_d1
{

const std::array<std::u32string, 8> InfoText::Keys32 = {
    {U"font", U"cSize", U"leSpace", U"liSpace", U"style", U"fColor", U"oColor",
     U"thick"}};

const char32_t InfoText::Separator = U',';

const InfoText InfoText::Default = InfoText();

InfoText::InfoText()
    : font(nullptr), charSize(30), letterSpacing({true, 1.0f}),
      lineSpacingFactor(1.0f), style(Style::REGULAR),
      fillColor(sf::Color(MaxColor, MaxColor, MaxColor, MaxColor)),
      outlineColor(sf::Color(0, 0, 0, MaxColor)), thickness(0)
{
    // ctor
}

InfoText::~InfoText() = default;

InfoText::InfoText(const InfoText &other) = default;

InfoText::InfoText(const sf::Font *const newFont, const uint64_t newCharSize)
    : font(newFont), charSize(newCharSize), letterSpacing({true, 1.0f}),
      lineSpacingFactor(1.0f), style(Style::REGULAR),
      fillColor(sf::Color(MaxColor, MaxColor, MaxColor, MaxColor)),
      outlineColor(sf::Color(0, 0, 0, MaxColor)), thickness(0)
{
}

InfoText::InfoText(const std::u32string &str)
    : font(nullptr), charSize(30), letterSpacing({true, 1.0f}),
      lineSpacingFactor(1.0f), style(Style::REGULAR),
      fillColor(sf::Color(MaxColor, MaxColor, MaxColor, MaxColor)),
      outlineColor(sf::Color(MaxColor, MaxColor, MaxColor, MaxColor)),
      thickness(0)
{
    std::vector<std::u32string> vecStr = Func::split(str, Separator);
    const std::size_t vecStrSize = vecStr.size();
    for (std::size_t i = 0; i < vecStrSize; ++i)
    {
        const auto [key, val] = Func::getKeyValueLine(vecStr[i]);
        // std::cout << "keyVal = " << keyVal.first << ", " << keyVal.second <<
        // std::endl;
        if (key == U"cSize")
        {
            charSize = Func::str32ToLui(val);
        }
        else if (key == U"leSpace")
        {
            std::get<0>(letterSpacing) = val[0] - U'0';
            std::get<1>(letterSpacing) =
                Func::str32ToF(val.substr(2, std::string::npos));
        }
        else if (key == U"leSpaceFix")
        {
            std::get<0>(letterSpacing) = false;
            std::get<1>(letterSpacing) = Func::str32ToF(val);
        }
        else if (key == U"liSpace")
        {
            lineSpacingFactor = Func::str32ToF(val);
        }
        else if (key == U"style")
        {
            style = static_cast<Style>(Func::str32ToLui(val));
        }
        else if (key == U"fColor")
        {
            fillColor = sf::Color(
                static_cast<uint32_t>(Func::str32HexToLui(val)));
        }
        else if (key == U"oColor")
        {
            outlineColor = sf::Color(
                static_cast<uint32_t>(Func::str32HexToLui(val)));
        }
        else if (key == U"thick")
        {
            thickness = Func::str32ToF(val);
        }
        else
        {
            // Nothing to do
        }
    }
}

InfoText &InfoText::operator=(const InfoText &rhs) = default;

void InfoText::setFont(const sf::Font *const newFont) { font = newFont; }

void InfoText::setCharSize(const uint64_t newCharSize)
{
    charSize = newCharSize;
}

void InfoText::setLetterSpacing(
    const std::tuple<bool, float32_t> &newLetterSpacing)
{
    letterSpacing = newLetterSpacing;
}

void InfoText::setLineSpacingFactor(const float32_t newLineSpacingFactor)
{
    lineSpacingFactor = newLineSpacingFactor;
}

void InfoText::setStyle(const Style newStyle) { style = newStyle; }

void InfoText::setFillColor(const sf::Color newFillColor)
{
    fillColor = newFillColor;
}

void InfoText::setOutlineColor(const sf::Color newOutlineColor)
{
    outlineColor = newOutlineColor;
}

void InfoText::setThickness(const float32_t newThickness)
{
    thickness = newThickness;
}

const sf::Font *InfoText::getFont() const { return font; }

uint64_t InfoText::getCharSize() const { return charSize; }

const std::tuple<bool, float32_t> &InfoText::getLetterSpacing() const
{
    return letterSpacing;
}

float32_t InfoText::getLineSpacingFactor() const { return lineSpacingFactor; }

InfoText::Style InfoText::getStyle() const { return style; }

sf::Color InfoText::getFillColor() const { return fillColor; }

sf::Color InfoText::getOutlineColor() const { return outlineColor; }

float32_t InfoText::getThickness() const { return thickness; }
/*
template<class I, InfoText::Info T> const I& InfoText::getInfo() const
{
    return reinterpret_cast<const I&>(0);
}

template<>
const sf::Font*& InfoText::getInfo<const sf::Font*, InfoText::Info::FONT>()
const
{
    return font;
}
*/

template <>
InfoText::Typer<InfoText::Info::FONT>::Type
InfoText::getInfo<InfoText::Info::FONT>() const
{
    return font;
}
template <>
InfoText::Typer<InfoText::Info::CHAR_SIZE>::Type
InfoText::getInfo<InfoText::Info::CHAR_SIZE>() const
{
    return charSize;
}
template <>
InfoText::Typer<InfoText::Info::LETTER_SPACING>::Type
InfoText::getInfo<InfoText::Info::LETTER_SPACING>() const
{
    return letterSpacing;
}
template <>
InfoText::Typer<InfoText::Info::LINE_SPACING_FACTOR>::Type
InfoText::getInfo<InfoText::Info::LINE_SPACING_FACTOR>() const
{
    return lineSpacingFactor;
}
template <>
InfoText::Typer<InfoText::Info::STYLE>::Type
InfoText::getInfo<InfoText::Info::STYLE>() const
{
    return style;
}
template <>
InfoText::Typer<InfoText::Info::FILL_COLOR>::Type
InfoText::getInfo<InfoText::Info::FILL_COLOR>() const
{
    return fillColor;
}
template <>
InfoText::Typer<InfoText::Info::OUTLINE_COLOR>::Type
InfoText::getInfo<InfoText::Info::OUTLINE_COLOR>() const
{
    return outlineColor;
}
template <>
InfoText::Typer<InfoText::Info::THICKNESS>::Type
InfoText::getInfo<InfoText::Info::THICKNESS>() const
{
    return thickness;
}

template <>
void InfoText::setInfo<InfoText::Info::FONT>(
    InfoText::Typer<InfoText::Info::FONT>::Type const t)
{
    font = t;
}
template <>
void InfoText::setInfo<InfoText::Info::CHAR_SIZE>(
    InfoText::Typer<InfoText::Info::CHAR_SIZE>::Type const t)
{
    charSize = t;
}
template <>
void InfoText::setInfo<InfoText::Info::LETTER_SPACING>(
    InfoText::Typer<InfoText::Info::LETTER_SPACING>::Type t)
{
    letterSpacing = t;
}
template <>
void InfoText::setInfo<InfoText::Info::LINE_SPACING_FACTOR>(
    InfoText::Typer<InfoText::Info::LINE_SPACING_FACTOR>::Type const t)
{
    lineSpacingFactor = t;
}
template <>
void InfoText::setInfo<InfoText::Info::STYLE>(
    InfoText::Typer<InfoText::Info::STYLE>::Type const t)
{
    style = t;
}
template <>
void InfoText::setInfo<InfoText::Info::FILL_COLOR>(
    InfoText::Typer<InfoText::Info::FILL_COLOR>::Type t)
{
    fillColor = t;
}
template <>
void InfoText::setInfo<InfoText::Info::OUTLINE_COLOR>(
    InfoText::Typer<InfoText::Info::OUTLINE_COLOR>::Type t)
{
    outlineColor = t;
}
template <>
void InfoText::setInfo<InfoText::Info::THICKNESS>(
    InfoText::Typer<InfoText::Info::THICKNESS>::Type const t)
{
    thickness = t;
}

std::u32string InfoText::getValStr(const Info i) const
{
    std::u32string res = U"";
    switch (i)
    {
    case Info::FONT: {
        std::basic_stringstream<char32_t, std::char_traits<char32_t>> ss;
        ss << font;
        res = ss.str();
        break;
    }
    case Info::CHAR_SIZE: {
        res = Func::luiTo32Str(charSize);
        break;
    }
    case Info::LETTER_SPACING: {
        res = Func::luiTo32Str(
                  static_cast<uint64_t>(std::get<0>(letterSpacing))) +
              U";" + Func::fTo32Str(std::get<1>(letterSpacing));
        break;
    }
    case Info::LINE_SPACING_FACTOR: {
        res = Func::fTo32Str(lineSpacingFactor);
        break;
    }
    case Info::STYLE: {
        res = Func::luiTo32Str(static_cast<uint64_t>(style));
        break;
    }
    case Info::FILL_COLOR: {
        res = Func::luiTo32StrHex(fillColor.toInteger());
        break;
    }
    case Info::OUTLINE_COLOR: {
        res = Func::luiTo32StrHex(outlineColor.toInteger());
        break;
    }
    case Info::THICKNESS: {
        res = Func::fTo32Str(thickness);
        break;
    }
    default: {
        break;
    }
    }
    return res;
}

const std::u32string &InfoText::getKeyStr32(const Info i)
{
    const std::u32string* res = &EmptyStr32;
    switch (i)
    {
    case Info::FONT: {
        res = &Keys32[0];
        break;
    }
    case Info::CHAR_SIZE: {
        res = &Keys32[1];
        break;
    }
    case Info::LETTER_SPACING: {
        res = &Keys32[2];
        break;
    }
    case Info::LINE_SPACING_FACTOR: {
        res = &Keys32[3];
        break;
    }
    case Info::STYLE: {
        res = &Keys32[4];
        break;
    }
    case Info::FILL_COLOR: {
        res = &Keys32[5];
        break;
    }
    case Info::OUTLINE_COLOR: {
        res = &Keys32[6];
        break;
    }
    case Info::THICKNESS: {
        res = &Keys32[7];
        break;
    }
    default: {
        res = &EmptyStr32;
        break;
    }
    }
    return *res;
}

InfoText::Info operator++(InfoText::Info &i, const int32_t)
{
    assert(i != InfoText::Info::NB_INFO);
    i = static_cast<InfoText::Info>(static_cast<uint64_t>(i) + 1);
    return static_cast<InfoText::Info>(static_cast<uint64_t>(i) - 1);
}

InfoText::Info &operator++(InfoText::Info &i)
{
    assert(i != InfoText::Info::NB_INFO);
    return i = static_cast<InfoText::Info>(static_cast<uint64_t>(i) + 1);
}

uint64_t operator|(const InfoText::Style &left, const InfoText::Style &right)
{
    return static_cast<uint32_t>(left) | static_cast<uint32_t>(right);
}

uint64_t operator|(const uint64_t left, const InfoText::Style &right)
{
    return left | static_cast<uint32_t>(right);
}

uint64_t operator&(const InfoText::Style &left, const InfoText::Style &right)
{
    return static_cast<uint32_t>(left) & static_cast<uint32_t>(right);
}

std::ostream &operator<<(std::ostream &os, const InfoText::Style right)
{
    return os << static_cast<uint64_t>(right);
}

} // namespace segment_d1
