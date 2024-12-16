#ifndef INFOTEXT_HPP
#define INFOTEXT_HPP
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
        Regular = 0,           ///< Regular characters, no style
        Bold = 1 << 0,         ///< Bold characters
        Italic = 1 << 1,       ///< Italic characters
        Underlined = 1 << 2,   ///< Underlined characters
        StrikeThrough = 1 << 3 ///< Strike through characters
    };

    /** Default constructor */
    InfoText();
    /** Default destructor */
    ~InfoText();
    /** Copy constructor
     *  \param other Object to copy from
     */
    InfoText(const InfoText &other);
    InfoText(const sf::Font *newFont, uint64_t newCharSize);
    explicit InfoText(const std::u32string &str);
    /** Assignment operator
     *  \param rhs Object to assign from
     *  \return A reference to this
     */
    InfoText &operator=(const InfoText &rhs);

    void setFont(const sf::Font *newFont);
    void setCharSize(uint64_t newCharSize);
    void setLetterSpacing(const std::tuple<bool, float32_t> &newLetterSpacing);
    void setLineSpacingFactor(float32_t newLineSpacingFactor);
    void setStyle(Style newStyle);
    void setFillColor(sf::Color newFillColor);
    void setOutlineColor(sf::Color newOutlineColor);
    void setThickness(float32_t newThickness);

    const sf::Font *getFont() const;
    uint64_t getCharSize() const;
    const std::tuple<bool, float32_t> &getLetterSpacing() const;
    float32_t getLineSpacingFactor() const;
    Style getStyle() const;
    sf::Color getFillColor() const;
    sf::Color getOutlineColor() const;
    float32_t getThickness() const;

    /*
            template <typename T, Info I>
            struct type{};

            template <typename T, Info I>
            T create(type<T, I>)
            {
                return T();
            }

            template <>
            uint64_t create(type<uint64_t, Info::CHAR_SIZE>)
            {
                return charSize;
            }

            template <typename T, Info I>
            T create(I)
            {
                return create(type<T, I>{});
            }
    */
    // template<class I, Info T> const I& getInfo() const;
    // template<> const sf::Font*& getInfo<const sf::Font*, Info::FONT>() const;

    template <Info typeCode> struct Typer;

    template <Info typeCode> typename Typer<typeCode>::Type getInfo() const;

    template <Info typeCode> void setInfo(typename Typer<typeCode>::Type t);

    bool operator==(const InfoText &right) const;
    bool operator!=(const InfoText &right) const;

    std::u32string getValStr(Info i) const;

    static const std::u32string &getKeyStr32(Info i);

    static const std::array<std::u32string, 8> Keys32;

    static const char32_t Separator;
    static const InfoText Default;

protected:
private:
    const sf::Font *font;
    uint64_t charSize;
    std::tuple<bool, float32_t> letterSpacing;
    float32_t lineSpacingFactor;
    Style style;
    sf::Color fillColor;
    sf::Color outlineColor;
    float32_t thickness;
};

template <InfoText::Info n> struct InfoText::Typer
{
};

template <> struct InfoText::Typer<InfoText::Info::FONT>
{
    typedef const sf::Font *Type;
};
template <> struct InfoText::Typer<InfoText::Info::CHAR_SIZE>
{
    typedef uint64_t Type;
};
template <> struct InfoText::Typer<InfoText::Info::LETTER_SPACING>
{
    typedef const std::tuple<bool, float32_t> &Type;
};
template <> struct InfoText::Typer<InfoText::Info::LINE_SPACING_FACTOR>
{
    typedef float32_t Type;
};
template <> struct InfoText::Typer<InfoText::Info::STYLE>
{
    typedef InfoText::Style Type;
};
template <> struct InfoText::Typer<InfoText::Info::FILL_COLOR>
{
    typedef const sf::Color &Type;
};
template <> struct InfoText::Typer<InfoText::Info::OUTLINE_COLOR>
{
    typedef const sf::Color &Type;
};
template <> struct InfoText::Typer<InfoText::Info::THICKNESS>
{
    typedef float32_t Type;
};

InfoText::Info operator++(InfoText::Info &i, int);

uint64_t operator|(const InfoText::Style &left, const InfoText::Style &right);
uint64_t operator|(uint64_t left, const InfoText::Style &right);
uint64_t operator&(const InfoText::Style &left, const InfoText::Style &right);

std::ostream &operator<<(std::ostream &os, InfoText::Style right);

} // namespace segment_d1

#endif // INFOTEXT_HPP
