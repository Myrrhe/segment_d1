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

#include "text/Text.hpp"
#include "Func.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <cmath>


namespace segment_d1
{

// Add an underline or strikethrough line to the vertex array
void addLine(std::vector<sf::Vertex> &vertices, float32_t lineLength,
             float32_t lineTop, const sf::Color &color, float32_t offset,
             float32_t thickness, float32_t outlineThickness)
{
    float32_t top = std::floor(lineTop + offset - (thickness / 2) + 0.5f);
    float32_t bottom = top + std::floor(thickness + 0.5f);

    vertices.emplace_back(
        sf::Vector2<float32_t>(-outlineThickness, top - outlineThickness),
        color, sf::Vector2<float32_t>(1, 1));
    vertices.emplace_back(sf::Vector2<float32_t>(lineLength + outlineThickness,
                                                 top - outlineThickness),
                          color, sf::Vector2<float32_t>(1, 1));
    vertices.emplace_back(
        sf::Vector2<float32_t>(-outlineThickness, bottom + outlineThickness),
        color, sf::Vector2<float32_t>(1, 1));
    vertices.emplace_back(
        sf::Vector2<float32_t>(-outlineThickness, bottom + outlineThickness),
        color, sf::Vector2<float32_t>(1, 1));
    vertices.emplace_back(sf::Vector2<float32_t>(lineLength + outlineThickness,
                                                 top - outlineThickness),
                          color, sf::Vector2<float32_t>(1, 1));
    vertices.emplace_back(sf::Vector2<float32_t>(lineLength + outlineThickness,
                                                 bottom + outlineThickness),
                          color, sf::Vector2<float32_t>(1, 1));
}

// Add a glyph quad to the vertex array
void addGlyphQuad(std::vector<sf::Vertex> &vertices,
                  sf::Vector2<float32_t> position, const sf::Color &color,
                  const sf::Glyph &glyph, float32_t italicShear,
                  float32_t outlineThickness)
{
    float32_t padding = 1.0;

    float32_t left = glyph.bounds.left - padding;
    float32_t top = glyph.bounds.top - padding;
    float32_t right = glyph.bounds.left + glyph.bounds.width + padding;
    float32_t bottom = glyph.bounds.top + glyph.bounds.height + padding;

    float32_t u1 = static_cast<float32_t>(glyph.textureRect.left) - padding;
    float32_t v1 = static_cast<float32_t>(glyph.textureRect.top) - padding;
    float32_t u2 = static_cast<float32_t>(glyph.textureRect.left +
                                          glyph.textureRect.width) +
                   padding;
    float32_t v2 = static_cast<float32_t>(glyph.textureRect.top +
                                          glyph.textureRect.height) +
                   padding;

    vertices.emplace_back(
        sf::Vector2<float32_t>(position.x + left - italicShear * top -
                                   outlineThickness,
                               position.y + top - outlineThickness),
        color, sf::Vector2<float32_t>(u1, v1));
    vertices.emplace_back(
        sf::Vector2<float32_t>(position.x + right - italicShear * top -
                                   outlineThickness,
                               position.y + top - outlineThickness),
        color, sf::Vector2<float32_t>(u2, v1));
    vertices.emplace_back(
        sf::Vector2<float32_t>(position.x + left - italicShear * bottom -
                                   outlineThickness,
                               position.y + bottom - outlineThickness),
        color, sf::Vector2<float32_t>(u1, v2));
    vertices.emplace_back(
        sf::Vector2<float32_t>(position.x + left - italicShear * bottom -
                                   outlineThickness,
                               position.y + bottom - outlineThickness),
        color, sf::Vector2<float32_t>(u1, v2));
    vertices.emplace_back(
        sf::Vector2<float32_t>(position.x + right - italicShear * top -
                                   outlineThickness,
                               position.y + top - outlineThickness),
        color, sf::Vector2<float32_t>(u2, v1));
    vertices.emplace_back(
        sf::Vector2<float32_t>(position.x + right - italicShear * bottom -
                                   outlineThickness,
                               position.y + bottom - outlineThickness),
        color, sf::Vector2<float32_t>(u2, v2));
}

uint32_t operator|(const Text::Style &left, const Text::Style &right)
{
    return static_cast<uint32_t>(left) | static_cast<uint32_t>(right);
}

uint32_t operator|(uint32_t left, const Text::Style &right)
{
    return left | static_cast<uint32_t>(right);
}

uint32_t operator&(const Text::Style &left, const Text::Style &right)
{
    return static_cast<uint32_t>(left) & static_cast<uint32_t>(right);
}

Text::Text()
    : m_string(), m_font(nullptr), m_characterSize(30),
      m_letterSpacingFactor(1.f), m_lineSpacingFactor(1.f),
      m_style(Text::Style::Regular), m_fillColor(255, 255, 255),
      m_outlineColor(0, 0, 0), m_outlineThickness(0), m_vertices(),
      m_outlineVertices(), m_bounds(), m_geometryNeedUpdate(false),
      m_fontTextureId(0)
{
}

Text::~Text() {}

Text::Text(const sf::String &string, const sf::Font &font,
           uint32_t characterSize)
    : m_string(string), m_font(&font), m_characterSize(characterSize),
      m_letterSpacingFactor(1.f), m_lineSpacingFactor(1.f),
      m_style(Text::Style::Regular), m_fillColor(255, 255, 255),
      m_outlineColor(0, 0, 0), m_outlineThickness(0),
      m_vertices(sf::PrimitiveType::Triangles),
      m_outlineVertices(sf::PrimitiveType::Triangles), m_bounds(),
      m_geometryNeedUpdate(true), m_fontTextureId(0)
{
}

Text::Text(const Text &right)
    : sf::Transformable(right), sf::Drawable(right), m_string(right.m_string),
      m_font(right.m_font), m_characterSize(right.m_characterSize),
      m_letterSpacingFactor(right.m_letterSpacingFactor),
      m_lineSpacingFactor(right.m_lineSpacingFactor), m_style(right.m_style),
      m_fillColor(right.m_fillColor), m_outlineColor(right.m_outlineColor),
      m_outlineThickness(right.m_outlineThickness),
      m_vertices(right.m_vertices), m_outlineVertices(right.m_outlineVertices),
      m_bounds(right.m_bounds),
      m_geometryNeedUpdate(right.m_geometryNeedUpdate),
      m_fontTextureId(right.m_fontTextureId)
{
}

Text &Text::operator=(const Text &rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
    sf::Transformable::operator=(rhs);
    sf::Drawable::operator=(rhs);
    m_string = rhs.m_string;
    m_font = rhs.m_font;
    m_characterSize = rhs.m_characterSize;
    m_letterSpacingFactor = rhs.m_letterSpacingFactor;
    m_lineSpacingFactor = rhs.m_lineSpacingFactor;
    m_style = rhs.m_style;
    m_fillColor = rhs.m_fillColor;
    m_outlineColor = rhs.m_outlineColor;
    m_outlineThickness = rhs.m_outlineThickness;
    m_vertices = rhs.m_vertices;
    m_outlineVertices = rhs.m_outlineVertices;
    m_bounds = rhs.m_bounds;
    m_geometryNeedUpdate = rhs.m_geometryNeedUpdate;
    m_fontTextureId = rhs.m_fontTextureId;
    return *this;
}

void Text::setString(const sf::String &string)
{
    if (m_string != string)
    {
        m_string = string;
        m_geometryNeedUpdate = true;
    }
}

void Text::setFont(const sf::Font &font)
{
    if (m_font != &font)
    {
        m_font = &font;
        m_geometryNeedUpdate = true;
    }
}

void Text::setCharacterSize(uint32_t size)
{
    if (m_characterSize != size)
    {
        m_characterSize = size;
        m_geometryNeedUpdate = true;
    }
}

void Text::setLetterSpacing(float32_t spacingFactor)
{
    if (std::abs(m_letterSpacingFactor - spacingFactor) > Func::m_epsilon_f)
    {
        m_letterSpacingFactor = spacingFactor;
        m_geometryNeedUpdate = true;
    }
}

void Text::setLineSpacing(float32_t spacingFactor)
{
    if (std::abs(m_lineSpacingFactor - spacingFactor) > Func::m_epsilon_f)
    {
        m_lineSpacingFactor = spacingFactor;
        m_geometryNeedUpdate = true;
    }
}

void Text::setStyle(Style style)
{
    if (m_style != style)
    {
        m_style = style;
        m_geometryNeedUpdate = true;
    }
}

void Text::setFillColor(const sf::Color &color)
{
    if (color != m_fillColor)
    {
        m_fillColor = color;

        // Change vertex colors directly, no need to update whole geometry
        // (if geometry is updated anyway, we can skip this step)
        if (!m_geometryNeedUpdate)
        {
            for (std::size_t i = 0; i < m_vertices.size(); ++i)
            {
                m_vertices[i].color = m_fillColor;
            }
        }
    }
}

void Text::setOutlineColor(const sf::Color &color)
{
    if (color != m_outlineColor)
    {
        m_outlineColor = color;

        // Change vertex colors directly, no need to update whole geometry
        // (if geometry is updated anyway, we can skip this step)
        if (!m_geometryNeedUpdate)
        {
            for (std::size_t i = 0; i < m_outlineVertices.size(); ++i)
            {
                m_outlineVertices[i].color = m_outlineColor;
            }
        }
    }
}

void Text::setOutlineThickness(float32_t thickness)
{
    if (std::abs(thickness - m_outlineThickness) > Func::m_epsilon_f)
    {
        m_outlineThickness = thickness;
        m_geometryNeedUpdate = true;
    }
}

const sf::String &Text::getString() const { return m_string; }

const sf::Font *Text::getFont() const { return m_font; }

uint32_t Text::getCharacterSize() const { return m_characterSize; }

float32_t Text::getLetterSpacing() const { return m_letterSpacingFactor; }

float32_t Text::getLineSpacing() const { return m_lineSpacingFactor; }

Text::Style Text::getStyle() const { return m_style; }

const sf::Color &Text::getFillColor() const { return m_fillColor; }

const sf::Color &Text::getOutlineColor() const { return m_outlineColor; }

float32_t Text::getOutlineThickness() const { return m_outlineThickness; }

sf::Vector2<float32_t> Text::findCharacterPos(std::size_t index) const
{
    // Make sure that we have a valid font
    if (!m_font)
    {
        return sf::Vector2<float32_t>();
    }

    // Adjust the index if it's out of range
    if (index > m_string.getSize())
    {
        index = m_string.getSize();
    }

    // Precompute the variables needed by the algorithm
    bool isBold = m_style & Style::Bold;
    float32_t whitespaceWidth =
        m_font->getGlyph(L' ', m_characterSize, isBold).advance;
    float32_t letterSpacing =
        (whitespaceWidth / 3.f) * (m_letterSpacingFactor - 1.f);
    whitespaceWidth += letterSpacing;
    float32_t lineSpacing =
        m_font->getLineSpacing(m_characterSize) * m_lineSpacingFactor;

    // Compute the position
    sf::Vector2<float32_t> position;
    uint32_t prevChar = 0;
    for (std::size_t i = 0; i < index; ++i)
    {
        uint32_t curChar = m_string[i];

        // Apply the kerning offset
        position.x += m_font->getKerning(prevChar, curChar, m_characterSize);
        prevChar = curChar;

        // Handle special characters
        switch (curChar)
        {
        case ' ':
            position.x += whitespaceWidth;
            continue;
        case '\t':
            position.x += whitespaceWidth * 4;
            continue;
        case '\n':
            position.y += lineSpacing;
            position.x = 0;
            continue;
        default:
            break;
        }

        // For regular characters, add the advance offset of the glyph
        position.x +=
            m_font->getGlyph(curChar, m_characterSize, isBold).advance +
            letterSpacing;
    }

    // Transform the position to global coordinates
    position = getTransform().transformPoint(position);

    return position;
}

sf::Rect<float32_t> Text::getLocalBounds() const
{
    ensureGeometryUpdate();

    return m_bounds;
}

sf::Rect<float32_t> Text::getGlobalBounds() const
{
    return getTransform().transformRect(getLocalBounds());
}

void Text::setGeomtryNeedUpdate() { m_geometryNeedUpdate = true; }

void Text::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    if (m_font)
    {
        ensureGeometryUpdate();

        states.transform *= getTransform();
        states.texture = &m_font->getTexture(m_characterSize);

        // Only draw the outline if there is something to draw
        if (std::abs(m_outlineThickness) > Func::m_epsilon_f)
        {
            target.draw(m_outlineVertices.data(), m_outlineVertices.size(),
                        sf::PrimitiveType::Triangles, states);
        }

        target.draw(m_vertices.data(), m_vertices.size(),
                    sf::PrimitiveType::Triangles, states);
    }
}

void Text::ensureGeometryUpdate() const
{
    if (!m_font)
    {
        return;
    }

    // Do nothing, if geometry has not changed and the font texture has not
    // changed
    if (!m_geometryNeedUpdate/* && m_font->getTexture(m_characterSize).m_cacheId == m_fontTextureId*/)
    {
        return;
    }

    // Save the current fonts texture id
    // m_fontTextureId = m_font->getTexture(m_characterSize).m_cacheId;

    // Mark geometry as updated
    m_geometryNeedUpdate = false;

    // Clear the previous geometry
    m_vertices.clear();
    m_outlineVertices.clear();
    m_bounds = sf::Rect<float32_t>();

    // No text: nothing to draw
    if (m_string.isEmpty())
    {
        return;
    }

    // Compute values related to the text style
    bool isBold = m_style & Style::Bold;
    bool isUnderlined = m_style & Style::Underlined;
    bool isStrikeThrough = m_style & Style::StrikeThrough;
    float32_t italicShear =
        (m_style & Style::Italic) ? 0.209f : 0.f; // 12 degrees in radians
    float32_t underlineOffset = m_font->getUnderlinePosition(m_characterSize);
    float32_t underlineThickness =
        m_font->getUnderlineThickness(m_characterSize);

    // Compute the location of the strike through dynamically
    // We use the center point of the lowercase 'x' glyph as the reference
    // We reuse the underline thickness as the thickness of the strike through
    // as well
    sf::Rect<float32_t> xBounds =
        m_font->getGlyph(L'x', m_characterSize, isBold).bounds;
    float32_t strikeThroughOffset = xBounds.top + xBounds.height / 2.f;

    // Precompute the variables needed by the algorithm
    float32_t whitespaceWidth =
        m_font->getGlyph(L' ', m_characterSize, isBold).advance;
    float32_t letterSpacing =
        (whitespaceWidth / 3.f) * (m_letterSpacingFactor - 1.f);
    whitespaceWidth += letterSpacing;
    float32_t lineSpacing =
        m_font->getLineSpacing(m_characterSize) * m_lineSpacingFactor;
    float32_t x = 0.f;
    float32_t y = static_cast<float32_t>(m_characterSize);

    // Create one quad for each character
    float32_t minX = static_cast<float32_t>(m_characterSize);
    float32_t minY = static_cast<float32_t>(m_characterSize);
    float32_t maxX = 0.f;
    float32_t maxY = 0.f;
    uint32_t prevChar = 0;
    for (std::size_t i = 0; i < m_string.getSize(); ++i)
    {
        uint32_t curChar = m_string[i];

        // Skip the \r char to avoid weird graphical issues
        if (curChar == '\r')
        {
            continue;
        }

        // Apply the kerning offset
        x += m_font->getKerning(prevChar, curChar, m_characterSize);

        // If we're using the underlined style and there's a new line, draw a
        // line
        if (isUnderlined && (curChar == L'\n' && prevChar != L'\n'))
        {
            addLine(m_vertices, x, y, m_fillColor, underlineOffset,
                    underlineThickness);

            if (std::abs(m_outlineThickness) > Func::m_epsilon_f)
            {
                addLine(m_outlineVertices, x, y, m_outlineColor,
                        underlineOffset, underlineThickness,
                        m_outlineThickness);
            }
        }

        // If we're using the strike through style and there's a new line, draw
        // a line across all characters
        if (isStrikeThrough && (curChar == L'\n' && prevChar != L'\n'))
        {
            addLine(m_vertices, x, y, m_fillColor, strikeThroughOffset,
                    underlineThickness);

            if (std::abs(m_outlineThickness) > Func::m_epsilon_f)
            {
                addLine(m_outlineVertices, x, y, m_outlineColor,
                        strikeThroughOffset, underlineThickness,
                        m_outlineThickness);
            }
        }

        prevChar = curChar;

        // Handle special characters
        if ((curChar == L' ') || (curChar == L'\n') || (curChar == L'\t'))
        {
            // Update the current bounds (min coordinates)
            minX = std::min(minX, x);
            minY = std::min(minY, y);

            switch (curChar)
            {
            case L' ':
                x += whitespaceWidth;
                break;
            case L'\t':
                x += whitespaceWidth * 4;
                break;
            case L'\n':
                y += lineSpacing;
                x = 0;
                break;
            default:
                break;
            }

            // Update the current bounds (max coordinates)
            maxX = std::max(maxX, x);
            maxY = std::max(maxY, y);

            // Next glyph, no need to create a quad for whitespace
            continue;
        }

        // Apply the outline
        if (std::abs(m_outlineThickness) > Func::m_epsilon_f)
        {
            const sf::Glyph &glyph = m_font->getGlyph(
                curChar, m_characterSize, isBold, m_outlineThickness);

            float32_t left = glyph.bounds.left;
            float32_t top = glyph.bounds.top;
            float32_t right = glyph.bounds.left + glyph.bounds.width;
            float32_t bottom = glyph.bounds.top + glyph.bounds.height;

            // Add the outline glyph to the vertices
            addGlyphQuad(m_outlineVertices, sf::Vector2<float32_t>(x, y),
                         m_outlineColor, glyph, italicShear,
                         m_outlineThickness);

            // Update the current bounds with the outlined glyph bounds
            minX = std::min(minX, x + left - italicShear * bottom -
                                      m_outlineThickness);
            maxX = std::max(maxX,
                            x + right - italicShear * top - m_outlineThickness);
            minY = std::min(minY, y + top - m_outlineThickness);
            maxY = std::max(maxY, y + bottom - m_outlineThickness);
        }

        // Extract the current glyph's description
        const sf::Glyph &glyph =
            m_font->getGlyph(curChar, m_characterSize, isBold);

        // Add the glyph to the vertices
        addGlyphQuad(m_vertices, sf::Vector2<float32_t>(x, y), m_fillColor,
                     glyph, italicShear);

        // Update the current bounds with the non outlined glyph bounds
        if (std::abs(m_outlineThickness) <= Func::m_epsilon_f)
        {
            float32_t left = glyph.bounds.left;
            float32_t top = glyph.bounds.top;
            float32_t right = glyph.bounds.left + glyph.bounds.width;
            float32_t bottom = glyph.bounds.top + glyph.bounds.height;

            minX = std::min(minX, x + left - italicShear * bottom);
            maxX = std::max(maxX, x + right - italicShear * top);
            minY = std::min(minY, y + top);
            maxY = std::max(maxY, y + bottom);
        }

        // Advance to the next character
        x += glyph.advance + letterSpacing;
    }

    // If we're using the underlined style, add the last line
    if (isUnderlined && (x > 0))
    {
        addLine(m_vertices, x, y, m_fillColor, underlineOffset,
                underlineThickness);

        if (std::abs(m_outlineThickness) > Func::m_epsilon_f)
        {
            addLine(m_outlineVertices, x, y, m_outlineColor, underlineOffset,
                    underlineThickness, m_outlineThickness);
        }
    }

    // If we're using the strike through style, add the last line across all
    // characters
    if (isStrikeThrough && (x > 0))
    {
        addLine(m_vertices, x, y, m_fillColor, strikeThroughOffset,
                underlineThickness);

        if (std::abs(m_outlineThickness) > Func::m_epsilon_f)
        {
            addLine(m_outlineVertices, x, y, m_outlineColor,
                    strikeThroughOffset, underlineThickness,
                    m_outlineThickness);
        }
    }

    // Update the bounding rectangle
    m_bounds.left = minX;
    m_bounds.top = minY;
    m_bounds.width = maxX - minX;
    m_bounds.height = maxY - minY;
}

} // namespace segment_d1
