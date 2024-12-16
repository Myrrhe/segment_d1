////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2018 Laurent Gomila (laurent@sfml-dev.org)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the
// use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#ifndef TEXT_HPP
#define TEXT_HPP

#include "Types.hpp"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Export.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/String.hpp>
#include <cstdint>
#include <string>
#include <vector>


namespace segment_d1
{

class Text final : public sf::Transformable, public sf::Drawable
{
public:
    enum class Style : uint32_t
    {
        Regular = 0,           ///< Regular characters, no style
        Bold = 1 << 0,         ///< Bold characters
        Italic = 1 << 1,       ///< Italic characters
        Underlined = 1 << 2,   ///< Underlined characters
        StrikeThrough = 1 << 3 ///< Strike through characters
    };

    Text();

    ~Text();

    Text(const sf::String &string, const sf::Font &font,
         uint32_t characterSize = 30);

    Text(const Text &right);

    Text &operator=(const Text &rhs);

    void setString(const sf::String &string);

    void setFont(const sf::Font &font);

    void setCharacterSize(uint32_t size);

    void setLineSpacing(float32_t spacingFactor);

    void setLetterSpacing(float32_t spacingFactor);

    void setStyle(Style style);

    void setFillColor(const sf::Color &color);

    void setOutlineColor(const sf::Color &color);

    void setOutlineThickness(float32_t thickness);

    const sf::String &getString() const;

    const sf::Font *getFont() const;

    uint32_t getCharacterSize() const;

    float32_t getLetterSpacing() const;

    float32_t getLineSpacing() const;

    Style getStyle() const;

    const sf::Color &getFillColor() const;

    const sf::Color &getOutlineColor() const;

    float32_t getOutlineThickness() const;

    sf::Vector2<float32_t> findCharacterPos(std::size_t index) const;

    sf::Rect<float32_t> getLocalBounds() const;

    sf::Rect<float32_t> getGlobalBounds() const;

    void setGeomtryNeedUpdate();

private:
    virtual void draw(sf::RenderTarget &target,
                      sf::RenderStates states) const override;

    void ensureGeometryUpdate() const;

    sf::String m_string;             ///< String to display
    const sf::Font *m_font;          ///< Font used to display the string
    uint32_t m_characterSize;        ///< Base size of characters, in pixels
    float32_t m_letterSpacingFactor; ///< Spacing factor between letters
    float32_t m_lineSpacingFactor;   ///< Spacing factor between lines
    Style m_style;                   ///< Text style (see Style enum)
    sf::Color m_fillColor;           ///< Text fill color
    sf::Color m_outlineColor;        ///< Text outline color
    float32_t m_outlineThickness;    ///< Thickness of the text's outline
    mutable std::vector<sf::Vertex>
        m_vertices; ///< Vertex array containing the fill geometry
    mutable std::vector<sf::Vertex>
        m_outlineVertices; ///< Vertex array containing the outline geometry
    mutable sf::Rect<float32_t>
        m_bounds; ///< Bounding rectangle of the text (in local coordinates)
    mutable bool
        m_geometryNeedUpdate; ///< Does the geometry need to be recomputed?
    mutable sf::Uint64 m_fontTextureId; ///< The font texture id
};

void addLine(std::vector<sf::Vertex> &vertices, float32_t lineLength,
             float32_t lineTop, const sf::Color &color, float32_t offset,
             float32_t thickness, float32_t outlineThickness = 0);
void addGlyphQuad(std::vector<sf::Vertex> &vertices,
                  sf::Vector2<float32_t> position, const sf::Color &color,
                  const sf::Glyph &glyph, float32_t italicShear,
                  float32_t outlineThickness = 0);

uint32_t operator|(const Text::Style &left, const Text::Style &right);
uint32_t operator|(uint32_t left, const Text::Style &right);

uint32_t operator&(const Text::Style &left, const Text::Style &right);

} // namespace segment_d1

#endif // TEXT_HPP
