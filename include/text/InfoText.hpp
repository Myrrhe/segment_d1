#ifndef INFOTEXT_HPP
#define INFOTEXT_HPP
#include "Func.hpp"
#include "Types.hpp"
#include <SFML/Graphics.hpp>

namespace segment_d1
{

class InfoText final
{
public:
    enum class Info : uint64_t
    {
        INFO_BEGIN = 0,
        FONT = INFO_BEGIN,
        CHAR_SIZE,
        LETTER_SPACING,
        LINE_SPACING_FACTOR,
        STYLE,
        FILL_COLOR,
        OUTLINE_COLOR,
        THICKNESS,
        NB_INFO = THICKNESS
    };

    enum class Style : uint64_t
    {
    REGULAR = 0,           ///< Regular characters, no style
    BOLD = 1 << 0,         ///< Bold characters
    ITALIC = 1 << 1,       ///< Italic characters
    UNDERLINED = 1 << 2,   ///< Underlined characters
    STRIKETHROUGH = 1 << 3 ///< Strike through characters
    };

    /** Default constructor */
    InfoText();
    /** Copy constructor
     *  \param other Object to copy from
     */
    InfoText(const InfoText &other);
    InfoText(const sf::Font *const newFont, const uint64_t newCharSize);
    explicit InfoText(const std::u32string &str);
    /** Assignment operator
     *  \param rhs Object to assign from
     *  \return A reference to this
     */
    InfoText &operator=(const InfoText &rhs);
    /** Default destructor */
    ~InfoText();

    void setFont(const sf::Font * const newFont);
    void setCharSize(const uint64_t newCharSize);
    void setLetterSpacing(const std::tuple<bool, float32_t> &newLetterSpacing);
    void setLineSpacingFactor(const float32_t newLineSpacingFactor);
    void setStyle(const Style newStyle);
    void setFillColor(const sf::Color newFillColor);
    void setOutlineColor(const sf::Color newOutlineColor);
    void setThickness(const float32_t newThickness);

    [[nodiscard]] const sf::Font *getFont() const;
    [[nodiscard]] uint64_t getCharSize() const;
    [[nodiscard]] const std::tuple<bool, float32_t> &getLetterSpacing() const;
    [[nodiscard]] float32_t getLineSpacingFactor() const;
    [[nodiscard]] Style getStyle() const;
    [[nodiscard]] sf::Color getFillColor() const;
    [[nodiscard]] sf::Color getOutlineColor() const;
    [[nodiscard]] float32_t getThickness() const;

    template <Info typeCode> struct Typer;

    template <Info typeCode> typename Typer<typeCode>::Type getInfo() const;

    template <Info typeCode> void setInfo(typename Typer<typeCode>::Type const t);

    std::u32string getValStr(const Info i) const;

    [[nodiscard]] static const std::u32string &getKeyStr32(const Info i);

    static const std::array<std::u32string, 8> Keys32;

    static const char32_t Separator;
    static const InfoText Default;

private:
    const sf::Font *font;
    uint64_t charSize;
    std::tuple<bool, float32_t> letterSpacing;
    float32_t lineSpacingFactor;
    Style style;
    sf::Color fillColor;
    sf::Color outlineColor;
    float32_t thickness;

    friend bool operator==(const InfoText &left, const InfoText &right)
    {
        bool res = true;
        res = res && (left.font == right.font);
        res = res && (left.charSize == right.charSize);
        res = res && (std::get<0>(left.letterSpacing) ==
                      std::get<0>(right.letterSpacing));
        res = res &&
              (std::abs(std::get<1>(left.letterSpacing) -
                        std::get<1>(right.letterSpacing)) < Func::m_epsilon_f);
        res = res && (std::abs(left.lineSpacingFactor -
                               right.lineSpacingFactor) < Func::m_epsilon_f);
        res = res && (left.style == right.style);
        res = res && (left.fillColor == right.fillColor);
        res = res && (left.outlineColor == right.outlineColor);
        res = res &&
              (std::abs(left.thickness - right.thickness) < Func::m_epsilon_f);
        return res;
    }
    friend bool operator!=(const InfoText &left, const InfoText &right)
    {
        return !(left == right);
    }
};

template <InfoText::Info n> struct InfoText::Typer
{
};

template <> struct InfoText::Typer<InfoText::Info::FONT>
{
    using Type = const sf::Font *;
};
template <> struct InfoText::Typer<InfoText::Info::CHAR_SIZE>
{
    using Type = uint64_t;
};
template <> struct InfoText::Typer<InfoText::Info::LETTER_SPACING>
{
    using Type = const std::tuple<bool, float32_t> &;
};
template <> struct InfoText::Typer<InfoText::Info::LINE_SPACING_FACTOR>
{
    using Type = float32_t;
};
template <> struct InfoText::Typer<InfoText::Info::STYLE>
{
    using Type = InfoText::Style;
};
template <> struct InfoText::Typer<InfoText::Info::FILL_COLOR>
{
    using Type = const sf::Color &;
};
template <> struct InfoText::Typer<InfoText::Info::OUTLINE_COLOR>
{
    using Type = const sf::Color &;
};
template <> struct InfoText::Typer<InfoText::Info::THICKNESS>
{
    using Type = float32_t;
};

InfoText::Info operator++(InfoText::Info &i, const int32_t);

InfoText::Info &operator++(InfoText::Info &i);

uint64_t operator|(const InfoText::Style &left, const InfoText::Style &right);
uint64_t operator|(const uint64_t left, const InfoText::Style &right);
uint64_t operator&(const InfoText::Style &left, const InfoText::Style &right);

std::ostream &operator<<(std::ostream &os, const InfoText::Style right);

} // namespace segment_d1

#endif // INFOTEXT_HPP
