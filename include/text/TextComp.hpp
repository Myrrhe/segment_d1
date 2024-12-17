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

#ifndef TEXTCOMP_HPP
#define TEXTCOMP_HPP

#include "text/ChainText.hpp"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Export.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/String.hpp>
#include <string>
#include <vector>

namespace segment_d1
{

class TextComp final : public sf::Drawable, public sf::Transformable
{
public:
    TextComp();
    TextComp(const std::vector<const ChainText *> &chainText,
             const sf::Font &font, const uint32_t characterSize);
    TextComp(const TextComp &right);
    TextComp &operator=(const TextComp &rhs);
    ~TextComp() override;

    void setFont(const sf::Font &font);

    void setCharacterSize(const uint32_t size);

    void setLineSpacing(float32_t spacingFactor);

    void setLetterSpacing(bool spacingFixed, float32_t spacing);

    void setStyle(const InfoText::Style style);

    void setFillColor(const sf::Color &color);

    void setOutlineColor(const sf::Color &color);

    void setOutlineThickness(const float32_t thickness);

    void setWidthWrap(float32_t widthWrap);

    const std::vector<const ChainText *> &getChainText() const;

    const sf::Font *getFont() const;

    uint64_t getCharacterSize() const;

    const std::tuple<bool, float32_t> &getLetterSpacing() const;

    float32_t getLineSpacing() const;

    InfoText::Style getStyle() const;

    const sf::Color &getFillColor() const;

    const sf::Color &getOutlineColor() const;

    float32_t getOutlineThickness() const;

    float32_t getWidthWrap() const;

    sf::Vector2<float32_t> findCharacterPos(std::size_t index) const;

    sf::Rect<float32_t> getLocalBounds() const;

    sf::Rect<float32_t> getGlobalBounds() const;

    void setGeomtryNeedUpdate();

private:
    /*virtual*/ void draw(sf::RenderTarget &target,
                          sf::RenderStates states) const override;

    void ensureGeometryUpdate() const;

    static void addLine(std::vector<sf::Vertex> &vertices,
                        const float32_t lineLength, const float32_t lineTop,
                        const sf::Color &color, const float32_t offset,
                        const float32_t thickness,
                        const float32_t outlineThickness);
    static void addLinePart(std::vector<sf::Vertex> &vertices,
                            const float32_t xInit, const float32_t xFina,
                            const float32_t lineTop, const sf::Color &color,
                            const float32_t offset, const float32_t thickness,
                            const float32_t outlineThickness);
    static void addGlyphQuad(std::vector<sf::Vertex> &vertices,
                             const sf::Vector2<float32_t> position,
                             const sf::Color &color, const sf::Glyph &glyph,
                             const float32_t italicShear,
                             const float32_t outlineThickness);

    std::vector<const ChainText *> m_chainText;

    // sf::String                      m_string;              ///< String to
    // display
    InfoText m_infoText;
    mutable std::vector<std::tuple<const sf::Font *, uint64_t>> m_fontsSizes;
    float32_t m_widthWrap;
    /*
    const sf::Font*                 m_font;                ///< Font used to
    display the string uint32_t                    m_characterSize; ///<
    Base size of characters, in pixels float32_t m_letterSpacingFactor; ///<
    Spacing factor between letters float32_t m_lineSpacingFactor;
    ///< Spacing factor between lines InfoText::Style                 m_style;
    ///< Text style (see Style enum) sf::Color m_fillColor;           ///< Text
    fill color sf::Color                       m_outlineColor;        ///< Text
    outline color float32_t                           m_outlineThickness; ///<
    Thickness of the text's outline
    */

    mutable std::vector<std::vector<sf::Vertex>>
        m_vertices; ///< Vertex array containing the fill geometry
    mutable std::vector<std::vector<sf::Vertex>>
        m_outlineVertices; ///< Vertex array containing the outline geometry
    mutable sf::Rect<float32_t>
        m_bounds; ///< Bounding rectangle of the text (in local coordinates)
    mutable bool
        m_geometryNeedUpdate; ///< Does the geometry need to be recomputed?
    mutable sf::Uint64 m_fontTextureId; ///< The font texture id
};

} // namespace segment_d1

#endif // TEXTCOMP_HPP
