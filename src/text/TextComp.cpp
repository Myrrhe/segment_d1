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

#include "text/TextComp.hpp"
#include "Func.hpp"
#include "Logger.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <cmath>
#include <stack>

namespace segment_d1
{

// Add an underline or strikethrough line to the vertex array
void TextComp::addLine(std::vector<sf::Vertex> &vertices,
                       const float32_t lineLength, const float32_t lineTop,
                       const sf::Color &color, const float32_t offset,
                       const float32_t thickness,
                       const float32_t outlineThickness)
{
    const float32_t top =
        std::floor(((lineTop + offset) - (thickness / 2)) + 0.5f);
    const float32_t bottom = top + std::floor(thickness + 0.5f);

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

void TextComp::addLinePart(std::vector<sf::Vertex> &vertices,
                           const float32_t xInit, const float32_t xFina,
                           const float32_t lineTop, const sf::Color &color,
                           const float32_t offset, const float32_t thickness,
                           const float32_t outlineThickness)
{
    const float32_t top =
        std::floor(((lineTop + offset) - (thickness / 2)) + 0.5f);
    const float32_t bottom = top + std::floor(thickness + 0.5f);

    vertices.emplace_back(sf::Vector2<float32_t>(xInit - outlineThickness,
                                                 top - outlineThickness),
                          color, sf::Vector2<float32_t>(1, 1));
    vertices.emplace_back(sf::Vector2<float32_t>(xFina + outlineThickness,
                                                 top - outlineThickness),
                          color, sf::Vector2<float32_t>(1, 1));
    vertices.emplace_back(sf::Vector2<float32_t>(xInit - outlineThickness,
                                                 bottom + outlineThickness),
                          color, sf::Vector2<float32_t>(1, 1));
    vertices.emplace_back(sf::Vector2<float32_t>(xInit - outlineThickness,
                                                 bottom + outlineThickness),
                          color, sf::Vector2<float32_t>(1, 1));
    vertices.emplace_back(sf::Vector2<float32_t>(xFina + outlineThickness,
                                                 top - outlineThickness),
                          color, sf::Vector2<float32_t>(1, 1));
    vertices.emplace_back(sf::Vector2<float32_t>(xFina + outlineThickness,
                                                 bottom + outlineThickness),
                          color, sf::Vector2<float32_t>(1, 1));
}

// Add a glyph quad to the vertex array
void TextComp::addGlyphQuad(std::vector<sf::Vertex> &vertices,
                            const sf::Vector2<float32_t> position,
                            const sf::Color &color, const sf::Glyph &glyph,
                            const float32_t italicShear,
                            const float32_t outlineThickness)
{
    const float32_t padding = 1.0;

    const float32_t left = glyph.bounds.left - padding;
    const float32_t top = glyph.bounds.top - padding;
    const float32_t right = glyph.bounds.left + glyph.bounds.width + padding;
    const float32_t bottom = glyph.bounds.top + glyph.bounds.height + padding;

    const float32_t u1 =
        static_cast<float32_t>(glyph.textureRect.left) - padding;
    const float32_t v1 =
        static_cast<float32_t>(glyph.textureRect.top) - padding;
    const float32_t u2 = static_cast<float32_t>(glyph.textureRect.left +
                                                glyph.textureRect.width) +
                         padding;
    const float32_t v2 = static_cast<float32_t>(glyph.textureRect.top +
                                                glyph.textureRect.height) +
                         padding;

    vertices.emplace_back(
        sf::Vector2<float32_t>(((position.x + left) - (italicShear * top)) -
                                   outlineThickness,
                               (position.y + top) - outlineThickness),
        color, sf::Vector2<float32_t>(u1, v1));
    vertices.emplace_back(
        sf::Vector2<float32_t>(((position.x + right) - (italicShear * top)) -
                                   outlineThickness,
                               (position.y + top) - outlineThickness),
        color, sf::Vector2<float32_t>(u2, v1));
    vertices.emplace_back(
        sf::Vector2<float32_t>(((position.x + left) - (italicShear * bottom)) -
                                   outlineThickness,
                               (position.y + bottom) - outlineThickness),
        color, sf::Vector2<float32_t>(u1, v2));
    vertices.emplace_back(
        sf::Vector2<float32_t>(((position.x + left) - (italicShear * bottom)) -
                                   outlineThickness,
                               (position.y + bottom) - outlineThickness),
        color, sf::Vector2<float32_t>(u1, v2));
    vertices.emplace_back(
        sf::Vector2<float32_t>(((position.x + right) - (italicShear * top)) -
                                   outlineThickness,
                               (position.y + top) - outlineThickness),
        color, sf::Vector2<float32_t>(u2, v1));
    vertices.emplace_back(
        sf::Vector2<float32_t>(((position.x + right) - (italicShear * bottom)) -
                                   outlineThickness,
                               (position.y + bottom) - outlineThickness),
        color, sf::Vector2<float32_t>(u2, v2));
}

TextComp::TextComp()
    : sf::Drawable(), sf::Transformable(), m_chainText(),
      // m_string             (),
      m_infoText(), m_fontsSizes({}), m_widthWrap(-1.0f),
      /*
      m_font               (nullptr),
      m_characterSize      (30),
      m_letterSpacingFactor(1.f),
      m_lineSpacingFactor  (1.f),
      m_style              (InfoText::Style::Regular),
      m_fillColor          (255, 255, 255),
      m_outlineColor       (0, 0, 0),
      m_outlineThickness   (0),
      */
      m_vertices(), m_outlineVertices(), m_bounds(),
      m_geometryNeedUpdate(false), m_fontTextureId(0)
{
}

TextComp::~TextComp() = default;
/*
TextComp::TextComp(const std::u32string& string, const sf::Font& font, uint32_t
characterSize) : sf::Drawable(), sf::Transformable(), m_chainText({string}),
//m_string             (string),
m_infoText(&font, characterSize),
m_fontsSizes({}),
m_widthWrap(-1.0f),
//m_font               (&font),
//m_characterSize      (characterSize),
//m_letterSpacingFactor(1.f),
//m_lineSpacingFactor  (1.f),
//m_style              (InfoText::Style::Regular),
//m_fillColor          (255, 255, 255),
//m_outlineColor       (0, 0, 0),
//m_outlineThickness   (0),
m_vertices           (sf::PrimitiveType::Triangles),
m_outlineVertices    (sf::PrimitiveType::Triangles),
m_bounds             (),
m_geometryNeedUpdate (true),
m_fontTextureId      (0)
{

}
*/
TextComp::TextComp(const std::vector<const ChainText *> &chainText,
                   const sf::Font &font, const uint32_t characterSize)
    : sf::Drawable(), sf::Transformable(), m_chainText(chainText),
      // m_string             (string),
      m_infoText(&font, characterSize), m_fontsSizes({}), m_widthWrap(-1.0f),
      /*
      m_font               (&font),
      m_characterSize      (characterSize),
      m_letterSpacingFactor(1.f),
      m_lineSpacingFactor  (1.f),
      m_style              (InfoText::Style::Regular),
      m_fillColor          (255, 255, 255),
      m_outlineColor       (0, 0, 0),
      m_outlineThickness   (0),
      */
      m_vertices(sf::PrimitiveType::Triangles),
      m_outlineVertices(sf::PrimitiveType::Triangles), m_bounds(),
      m_geometryNeedUpdate(true), m_fontTextureId(0)
{
}

TextComp::TextComp(const TextComp &right) = default;

TextComp &TextComp::operator=(const TextComp &rhs) = default;
/*
void TextComp::setString(const std::u32string& string)
{
    ChainText newChain = string;
    if (newChain != m_chainText)
    {
        m_chainText = newChain;
        m_geometryNeedUpdate = true;
    }
}
*/
void TextComp::setFont(const sf::Font &font)
{
    if (m_infoText.getInfo<InfoText::Info::FONT>() != &font)
    {
        m_infoText.setInfo<InfoText::Info::FONT>(&font);
        m_geometryNeedUpdate = true;
    }
}

void TextComp::setCharacterSize(const uint32_t size)
{
    if (m_infoText.getInfo<InfoText::Info::CHAR_SIZE>() != size)
    {
        m_infoText.setInfo<InfoText::Info::CHAR_SIZE>(size);
        m_geometryNeedUpdate = true;
    }
}

void TextComp::setLetterSpacing(bool spacingFixed, float32_t spacing)
{
    if (spacingFixed !=
            std::get<0>(m_infoText.getInfo<InfoText::Info::LETTER_SPACING>()) ||
        std::abs(
            std::get<1>(m_infoText.getInfo<InfoText::Info::LETTER_SPACING>()) -
            spacing) > Func::m_epsilon_f)
    {
        m_infoText.setInfo<InfoText::Info::LETTER_SPACING>(
            {spacingFixed, spacing});
    }
}

void TextComp::setLineSpacing(float32_t spacingFactor)
{
    if (std::abs(m_infoText.getInfo<InfoText::Info::LINE_SPACING_FACTOR>() -
                 spacingFactor) > Func::m_epsilon_f)
    {
        m_infoText.setInfo<InfoText::Info::LINE_SPACING_FACTOR>(spacingFactor);
        m_geometryNeedUpdate = true;
    }
}

void TextComp::setStyle(const InfoText::Style style)
{
    if (m_infoText.getInfo<InfoText::Info::STYLE>() != style)
    {
        m_infoText.setInfo<InfoText::Info::STYLE>(style);
        m_geometryNeedUpdate = true;
    }
}

void TextComp::setFillColor(const sf::Color &color)
{
    if (m_infoText.getInfo<InfoText::Info::FILL_COLOR>() != color)
    {
        m_infoText.setInfo<InfoText::Info::FILL_COLOR>(color);

        // Change vertex colors directly, no need to update whole geometry
        // (if geometry is updated anyway, we can skip this step)
        if (!m_geometryNeedUpdate)
        {
            const std::size_t verticesSize = m_vertices.size();
            for (std::size_t i = 0; i < verticesSize; ++i)
            {
                const std::size_t verticesiSize = m_vertices.size();
                for (std::size_t j = 0; j < verticesiSize; ++j)
                {
                    m_vertices[i][j].color =
                        m_infoText.getInfo<InfoText::Info::FILL_COLOR>();
                }
            }
        }
    }
}

void TextComp::setOutlineColor(const sf::Color &color)
{
    if (m_infoText.getInfo<InfoText::Info::OUTLINE_COLOR>() != color)
    {
        m_infoText.setInfo<InfoText::Info::OUTLINE_COLOR>(color);

        // Change vertex colors directly, no need to update whole geometry
        // (if geometry is updated anyway, we can skip this step)
        if (!m_geometryNeedUpdate)
        {
            const std::size_t outlineVerticesSize = m_outlineVertices.size();
            for (std::size_t i = 0; i < outlineVerticesSize; ++i)
            {
                const std::size_t outlineVerticesiSize =
                    m_outlineVertices.size();
                for (std::size_t j = 0; j < outlineVerticesiSize; ++j)
                {
                    m_outlineVertices[i][j].color =
                        m_infoText.getInfo<InfoText::Info::OUTLINE_COLOR>();
                }
            }
        }
    }
}

void TextComp::setOutlineThickness(const float32_t thickness)
{
    if (std::abs(m_infoText.getInfo<InfoText::Info::THICKNESS>() - thickness) >
        Func::m_epsilon_f)
    {
        m_infoText.setInfo<InfoText::Info::THICKNESS>(thickness);
        m_geometryNeedUpdate = true;
    }
}

void TextComp::setWidthWrap(float32_t widthWrap)
{
    if (std::abs(m_widthWrap - widthWrap) > Func::m_epsilon_f)
    {
        m_widthWrap = widthWrap;
        m_geometryNeedUpdate = true;
    }
}

const std::vector<const ChainText *> &TextComp::getChainText() const
{
    return m_chainText;
}

const sf::Font *TextComp::getFont() const
{
    return m_infoText.getInfo<InfoText::Info::FONT>();
}

uint64_t TextComp::getCharacterSize() const
{
    return m_infoText.getInfo<InfoText::Info::CHAR_SIZE>();
}

const std::tuple<bool, float32_t> &TextComp::getLetterSpacing() const
{
    return m_infoText.getInfo<InfoText::Info::LETTER_SPACING>();
}

float32_t TextComp::getLineSpacing() const
{
    return m_infoText.getInfo<InfoText::Info::LINE_SPACING_FACTOR>();
}

InfoText::Style TextComp::getStyle() const
{
    return m_infoText.getInfo<InfoText::Info::STYLE>();
}

const sf::Color &TextComp::getFillColor() const
{
    return m_infoText.getInfo<InfoText::Info::FILL_COLOR>();
}

const sf::Color &TextComp::getOutlineColor() const
{
    return m_infoText.getInfo<InfoText::Info::OUTLINE_COLOR>();
}

float32_t TextComp::getOutlineThickness() const
{
    return m_infoText.getInfo<InfoText::Info::THICKNESS>();
}

float32_t TextComp::getWidthWrap() const { return m_widthWrap; }

sf::Vector2<float32_t> TextComp::findCharacterPos(std::size_t index) const
{
    // Make sure that we have a valid font
    if (!m_infoText.getInfo<InfoText::Info::FONT>())
    {
        return sf::Vector2<float32_t>();
    }

    std::size_t nbCharTotal = 0;
    const std::size_t chainTextSize = m_chainText.size();
    for (std::size_t i = 0; i < chainTextSize; ++i)
    {
        nbCharTotal += m_chainText[i]->getNbChar();
    }

    // Adjust the index if it's out of range
    if (index > nbCharTotal)
    {
        index = nbCharTotal;
    }

    // Precompute the variables needed by the algorithm
    /*
    bool  isBold          = m_infoText.getInfo<InfoText::Info::STYLE>() &
    InfoText::Style::Bold; float32_t whitespaceWidth =
    m_infoText.getInfo<InfoText::Info::FONT>()->getGlyph(' ',
    m_infoText.getInfo<InfoText::Info::CHAR_SIZE>(), isBold).advance; float32_t
    letterSpacing   = ( whitespaceWidth / 3.f ) * (
    m_infoText.getInfo<InfoText::Info::LETTER_SPACING>() - 1.f );
    whitespaceWidth      += letterSpacing;
    float32_t lineSpacing     =
    m_infoText.getInfo<InfoText::Info::FONT>()->getLineSpacing(m_infoText.getInfo<InfoText::Info::CHAR_SIZE>())
    * m_infoText.getInfo<InfoText::Info::LINE_SPACING>();
    */
    // Compute the position
    sf::Vector2<float32_t> position;
    char32_t prevChar = 0;
    uint64_t indexNode = 0;
    std::size_t iInit = 0;
    std::vector<const BlockInfoText *> vecInfo = {};
    auto curInfo = BlockInfoText(m_infoText);
    std::size_t indexChain = 0;
    for (std::size_t i = 0; i < index; ++i)
    {
        bool changeInfo = false;
        while ((i - iInit) >= m_chainText[indexChain]->getNbChar(indexNode))
        {
            iInit = i;
            if ((*m_chainText[indexChain])[indexNode]->getType() ==
                NodeText::Type::BLOCKINFO)
            {
                vecInfo.emplace_back(dynamic_cast<const BlockInfoText *>(
                    (*m_chainText[indexChain])[indexNode]));
            }
            else if ((*m_chainText[indexChain])[indexNode]->getType() ==
                     NodeText::Type::BLOCKCLOSING)
            {
                vecInfo.pop_back();
            }
            else
            {
                // Nothing to do
            }
            changeInfo = true;
            ++indexNode;
            while (indexNode >= m_chainText[indexChain]->getSize())
            {
                ++indexChain;
                indexNode = 0;
            }
        }
        if (changeInfo)
        {
            curInfo = BlockInfoText(m_infoText);
            const std::size_t vecInfoSize = vecInfo.size();
            for (std::size_t j = 0; j < vecInfoSize; ++j)
            {
                curInfo += *vecInfo[j];
            }
        }

        const char32_t curChar = static_cast<uint32_t>(
            (*m_chainText[indexChain])[indexNode]->getStr()[i - iInit]);

        const bool curBold =
            curInfo.getInfoText().getInfo<InfoText::Info::STYLE>() &
            InfoText::Style::BOLD;
        float32_t curWhitespaceWidth =
            curInfo.getInfoText()
                .getInfo<InfoText::Info::FONT>()
                ->getGlyph(' ',
                           static_cast<uint32_t>(
                               curInfo.getInfoText()
                                   .getInfo<InfoText::Info::CHAR_SIZE>()),
                           curBold)
                .advance;
        const float32_t curLetterSpacing =
            (curWhitespaceWidth / 3.f) *
            (std::get<1>(curInfo.getInfoText()
                             .getInfo<InfoText::Info::LETTER_SPACING>()) -
             1.f);
        curWhitespaceWidth += curLetterSpacing;
        const float32_t curLineSpacing =
            curInfo.getInfoText()
                .getInfo<InfoText::Info::FONT>()
                ->getLineSpacing(static_cast<uint32_t>(
                    curInfo.getInfoText()
                        .getInfo<InfoText::Info::CHAR_SIZE>())) *
            curInfo.getInfoText()
                .getInfo<InfoText::Info::LINE_SPACING_FACTOR>();

        /*
        for (std::size_t j = 0; j < vecInfo.size(); j++)
        {
            if (vecInfo[vecInfo.size() - 1 - j]->isUsed(InfoText::Info::STYLE))
            {
                curBold = vecInfo[vecInfo.size() - 1 -
        j]->getInfoText().getInfo<InfoText::Info::STYLE>() &
        InfoText::Style::Bold; break;
            }
        }
        */

        // Apply the kerning offset
        position.x +=
            curInfo.getInfoText().getInfo<InfoText::Info::FONT>()->getKerning(
                prevChar, curChar,
                static_cast<uint32_t>(
                    curInfo.getInfoText()
                        .getInfo<InfoText::Info::CHAR_SIZE>()));
        prevChar = curChar;

        // Handle special characters
        switch (curChar)
        {
        case U' ':
            position.x += curWhitespaceWidth;
            continue;
        case U'\t':
            position.x += curWhitespaceWidth * 4;
            continue;
        case U'\n':
            position.y += curLineSpacing;
            position.x = 0;
            continue;
        default:
            break;
        }

        // For regular characters, add the advance offset of the glyph
        if (!std::get<0>(curInfo.getInfoText()
                             .getInfo<InfoText::Info::LETTER_SPACING>()))
        {
            position.x +=
                std::get<1>(curInfo.getInfoText()
                                .getInfo<InfoText::Info::LETTER_SPACING>());
        }
        else
        {
            position.x +=
                curInfo.getInfoText()
                    .getInfo<InfoText::Info::FONT>()
                    ->getGlyph(curChar,
                               static_cast<uint32_t>(
                                   curInfo.getInfoText()
                                       .getInfo<InfoText::Info::CHAR_SIZE>()),
                               curBold)
                    .advance +
                curLetterSpacing;
        }
    }

    // Transform the position to global coordinates
    position = getTransform().transformPoint(position);

    return position;
}

sf::Rect<float32_t> TextComp::getLocalBounds() const
{
    ensureGeometryUpdate();

    return m_bounds;
}

sf::Rect<float32_t> TextComp::getGlobalBounds() const
{
    return getTransform().transformRect(getLocalBounds());
}

void TextComp::setGeomtryNeedUpdate() { m_geometryNeedUpdate = true; }

void TextComp::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    if (nullptr != m_infoText.getInfo<InfoText::Info::FONT>())
    {
        ensureGeometryUpdate();

        states.transform *= getTransform();

        // Only draw the outline if there is something to draw
        /*
        if (std::abs(m_infoText.getInfo<InfoText::Info::THICKNESS>()) >
        m_epsilon_f)
        {
            target.draw(m_outlineVertices.front().data(),
        m_outlineVertices.size(), sf::PrimitiveType::Triangles, states);
        }
        */
        const std::size_t outlineVerticesSize = m_outlineVertices.size();
        for (std::size_t i = 0; i < outlineVerticesSize; ++i)
        {
            states.texture = &std::get<0>(m_fontsSizes[i])
                                  ->getTexture(static_cast<uint32_t>(
                                      std::get<1>(m_fontsSizes[i])));
            target.draw(m_outlineVertices[i].data(),
                        m_outlineVertices[i].size(),
                        sf::PrimitiveType::Triangles, states);
            target.draw(m_vertices[i].data(), m_vertices[i].size(),
                        sf::PrimitiveType::Triangles, states);
        }
    }
}

void TextComp::ensureGeometryUpdate() const
{
    if (nullptr == m_infoText.getInfo<InfoText::Info::FONT>())
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
    m_fontsSizes.clear();
    m_bounds = sf::Rect<float32_t>();

    // No text: nothing to draw
    if (m_chainText.empty())
    {
        return;
    }

    // Compute values related to the text style
    /*
    bool  isBold             = m_infoText.getInfo<InfoText::Info::STYLE>() &
    InfoText::Style::Bold; bool  isUnderlined       =
    m_infoText.getInfo<InfoText::Info::STYLE>() & InfoText::Style::Underlined;
    bool  isStrikeThrough    = m_infoText.getInfo<InfoText::Info::STYLE>() &
    InfoText::Style::StrikeThrough; float32_t italicShear        =
    (m_infoText.getInfo<InfoText::Info::STYLE>() & InfoText::Style::Italic) ?
    0.209f : 0.f; // 12 degrees in radians float32_t underlineOffset    =
    m_infoText.getInfo<InfoText::Info::FONT>()->getUnderlinePosition(m_infoText.getInfo<InfoText::Info::CHAR_SIZE>());
    float32_t underlineThickness =
    m_infoText.getInfo<InfoText::Info::FONT>()->getUnderlineThickness(m_infoText.getInfo<InfoText::Info::CHAR_SIZE>());
    */

    // Compute the location of the strike through dynamically
    // We use the center point of the lowercase 'x' glyph as the reference
    // We reuse the underline thickness as the thickness of the strike through
    // as well
    /*
    sf::Rect<float32_t> xBounds =
    m_infoText.getInfo<InfoText::Info::FONT>()->getGlyph('x',
    m_infoText.getInfo<InfoText::Info::CHAR_SIZE>(), isBold).bounds; float32_t
    strikeThroughOffset = xBounds.top + xBounds.height / 2.f;
    */

    // Precompute the variables needed by the algorithm
    /*
    float32_t whitespaceWidth =
    m_infoText.getInfo<InfoText::Info::FONT>()->getGlyph(' ',
    m_infoText.getInfo<InfoText::Info::CHAR_SIZE>(), isBold).advance; float32_t
    letterSpacing   = ( whitespaceWidth / 3.f ) * (
    m_infoText.getInfo<InfoText::Info::LETTER_SPACING>() - 1.f );
    whitespaceWidth      += letterSpacing;
    float32_t lineSpacing     =
    m_infoText.getInfo<InfoText::Info::FONT>()->getLineSpacing(m_infoText.getInfo<InfoText::Info::CHAR_SIZE>())
    * m_infoText.getInfo<InfoText::Info::LINE_SPACING>(); float32_t x = 0.f;
    float32_t y               =
    static_cast<float32_t>(m_infoText.getInfo<InfoText::Info::CHAR_SIZE>());
    */

    float32_t x = 0.f;
    auto y =
        static_cast<float32_t>(m_infoText.getInfo<InfoText::Info::CHAR_SIZE>());
    float32_t prevX = x;

    // Create one quad for each character
    auto minX =
        static_cast<float32_t>(m_infoText.getInfo<InfoText::Info::CHAR_SIZE>());
    auto minY =
        static_cast<float32_t>(m_infoText.getInfo<InfoText::Info::CHAR_SIZE>());
    float32_t maxX = 0.f;
    float32_t maxY = 0.f;
    char32_t prevChar = 0;
    std::size_t indexNode = 0;
    std::size_t iInit = 0;
    std::vector<const BlockInfoText *> vecInfo = {};
    auto curInfo = BlockInfoText(m_infoText);
    BlockInfoText prevInfo = curInfo;
    std::size_t indexArrayVert = 0;
    std::size_t nbCharTotal = 0;
    const std::size_t chainTextSize = m_chainText.size();
    for (std::size_t i = 0; i < chainTextSize; ++i)
    {
        nbCharTotal += m_chainText[i]->getNbChar();
    }
    std::size_t indexChain = 0;
    // long unsigned curNbChar = m_chainText.front()->getNbChar();
    const sf::Font *curFont = nullptr;
    uint64_t curCharSize = 0;
    std::vector<sf::Vertex> curUndelineVertFill = {};
    std::vector<sf::Vertex> curUndelineVertOutline = {};
    std::vector<sf::Vertex> curStrikeThroughVertFill = {};
    std::vector<sf::Vertex> curStrikeThroughVertOutline = {};
    for (std::size_t i = 0; i < /*m_string.getSize()*/ nbCharTotal; ++i)
    {
        bool changeInfo = false;
        while (i - iInit >= m_chainText[indexChain]->getNbChar(indexNode))
        {
            iInit = i;
            if ((*m_chainText[indexChain])[indexNode]->getType() ==
                NodeText::Type::BLOCKINFO)
            {
                vecInfo.emplace_back(dynamic_cast<const BlockInfoText *>(
                    (*m_chainText[indexChain])[indexNode]));
            }
            else if ((*m_chainText[indexChain])[indexNode]->getType() ==
                     NodeText::Type::BLOCKCLOSING)
            {
                vecInfo.pop_back();
            }
            changeInfo = true;
            ++indexNode;
            while (indexNode >= m_chainText[indexChain]->getSize())
            {
                ++indexChain;
                indexNode = 0;
            }
        }
        if (changeInfo || (0 == i))
        {
            curInfo = BlockInfoText(m_infoText);
            const std::size_t vecInfoSize = vecInfo.size();
            for (std::size_t j = 0; j < vecInfoSize; ++j)
            {
                curInfo += *vecInfo[j];
            }
            if ((curInfo.getInfoText().getInfo<InfoText::Info::FONT>() !=
                 curFont) ||
                (curInfo.getInfoText().getInfo<InfoText::Info::CHAR_SIZE>() !=
                 curCharSize))
            {
                m_fontsSizes.push_back(
                    {curInfo.getInfoText().getInfo<InfoText::Info::FONT>(),
                     curInfo.getInfoText()
                         .getInfo<InfoText::Info::CHAR_SIZE>()});
                curFont = std::get<0>(m_fontsSizes.back());
                curCharSize = std::get<1>(m_fontsSizes.back());
                // std::tie(curFont, curCharSize) = m_fontsSizes.back();
                m_vertices.push_back({});
                m_outlineVertices.push_back({});
                indexArrayVert = m_vertices.size() - 1;
            }
            if (0 == i)
            {
                y = static_cast<float32_t>(
                    curInfo.getInfoText().getInfo<InfoText::Info::CHAR_SIZE>());
            }
            if ((0 != (curInfo.getInfoText().getInfo<InfoText::Info::STYLE>() &
                       InfoText::Style::UNDERLINED)) &&
                (0 == (prevInfo.getInfoText().getInfo<InfoText::Info::STYLE>() &
                       InfoText::Style::UNDERLINED)))
            {
                curUndelineVertFill.clear();
                curUndelineVertOutline.clear();
            }
            else if ((0 ==
                      (curInfo.getInfoText().getInfo<InfoText::Info::STYLE>() &
                       InfoText::Style::UNDERLINED)) &&
                     (0 !=
                      (prevInfo.getInfoText().getInfo<InfoText::Info::STYLE>() &
                       InfoText::Style::UNDERLINED)))
            {
                m_vertices[indexArrayVert].insert(
                    m_vertices[indexArrayVert].end(),
                    curUndelineVertFill.begin(), curUndelineVertFill.end());
                m_outlineVertices[indexArrayVert].insert(
                    m_outlineVertices[indexArrayVert].end(),
                    curUndelineVertOutline.begin(),
                    curUndelineVertOutline.end());
            }
            else
            {
                // Nothing to do
            }

            if ((0 != (curInfo.getInfoText().getInfo<InfoText::Info::STYLE>() &
                       InfoText::Style::STRIKETHROUGH)) &&
                (0 == (prevInfo.getInfoText().getInfo<InfoText::Info::STYLE>() &
                       InfoText::Style::STRIKETHROUGH)))
            {
                curStrikeThroughVertFill.clear();
                curStrikeThroughVertOutline.clear();
            }
            else if ((0 ==
                      (curInfo.getInfoText().getInfo<InfoText::Info::STYLE>() &
                       InfoText::Style::STRIKETHROUGH)) &&
                     (0 !=
                      (prevInfo.getInfoText().getInfo<InfoText::Info::STYLE>() &
                       InfoText::Style::STRIKETHROUGH)))
            {
                m_vertices[indexArrayVert].insert(
                    m_vertices[indexArrayVert].end(),
                    curStrikeThroughVertFill.begin(),
                    curStrikeThroughVertFill.end());
                m_outlineVertices[indexArrayVert].insert(
                    m_outlineVertices[indexArrayVert].end(),
                    curStrikeThroughVertOutline.begin(),
                    curStrikeThroughVertOutline.end());
            }
            else
            {
                // Nothing to do
            }
        }

        bool curBold = curInfo.getInfoText().getInfo<InfoText::Info::STYLE>() &
                       InfoText::Style::BOLD;
        bool curUnderlined =
            curInfo.getInfoText().getInfo<InfoText::Info::STYLE>() &
            InfoText::Style::UNDERLINED;
        bool curStrikeThrough =
            curInfo.getInfoText().getInfo<InfoText::Info::STYLE>() &
            InfoText::Style::STRIKETHROUGH;
        float32_t curItalicShear = 0.f;
        if (0 != (curInfo.getInfoText().getInfo<InfoText::Info::STYLE>() &
                  InfoText::Style::ITALIC))
        {
            curItalicShear = 0.209f;
        }
        const float32_t curUnderlineOffset =
            curInfo.getInfoText()
                .getInfo<InfoText::Info::FONT>()
                ->getUnderlinePosition(static_cast<uint32_t>(
                    curInfo.getInfoText()
                        .getInfo<InfoText::Info::CHAR_SIZE>()));
        const float32_t curUnderlineThickness =
            curInfo.getInfoText()
                .getInfo<InfoText::Info::FONT>()
                ->getUnderlineThickness(static_cast<uint32_t>(
                    curInfo.getInfoText()
                        .getInfo<InfoText::Info::CHAR_SIZE>()));

        const sf::Rect<float32_t> curXBounds =
            curInfo.getInfoText()
                .getInfo<InfoText::Info::FONT>()
                ->getGlyph('x',
                           static_cast<uint32_t>(
                               curInfo.getInfoText()
                                   .getInfo<InfoText::Info::CHAR_SIZE>()),
                           curBold)
                .bounds;
        const float32_t curStrikeThroughOffset =
            curXBounds.top + (curXBounds.height / 2.f);

        float32_t curWhitespaceWidth =
            curInfo.getInfoText()
                .getInfo<InfoText::Info::FONT>()
                ->getGlyph(' ',
                           static_cast<uint32_t>(
                               curInfo.getInfoText()
                                   .getInfo<InfoText::Info::CHAR_SIZE>()),
                           curBold)
                .advance;
        const float32_t curLetterSpacing =
            (curWhitespaceWidth / 3.f) *
            (std::get<1>(curInfo.getInfoText()
                             .getInfo<InfoText::Info::LETTER_SPACING>()) -
             1.f);
        curWhitespaceWidth += curLetterSpacing;
        if (!std::get<0>(curInfo.getInfoText()
                             .getInfo<InfoText::Info::LETTER_SPACING>()))
        {
            curWhitespaceWidth =
                std::get<1>(curInfo.getInfoText()
                                .getInfo<InfoText::Info::LETTER_SPACING>());
        }
        else
        {
            curWhitespaceWidth += curLetterSpacing;
        }
        const float32_t curLineSpacing =
            curInfo.getInfoText()
                .getInfo<InfoText::Info::FONT>()
                ->getLineSpacing(static_cast<uint32_t>(
                    curInfo.getInfoText()
                        .getInfo<InfoText::Info::CHAR_SIZE>())) *
            curInfo.getInfoText()
                .getInfo<InfoText::Info::LINE_SPACING_FACTOR>();

        const char32_t curChar =
            static_cast<uint32_t>((*m_chainText[indexChain])[indexNode]
                                      ->getStr()[i - iInit]) /*m_string[i]*/;

        // Skip the \r char to avoid weird graphical issues
        if (U'\r' == curChar)
        {
            continue;
        }

        // Apply the kerning offset
        if (!std::get<0>(curInfo.getInfoText()
                             .getInfo<InfoText::Info::LETTER_SPACING>()))
        {
            x += 0;
        }
        else
        {
            x += curInfo.getInfoText()
                     .getInfo<InfoText::Info::FONT>()
                     ->getKerning(
                         prevChar, curChar,
                         static_cast<uint32_t>(
                             curInfo.getInfoText()
                                 .getInfo<InfoText::Info::CHAR_SIZE>()));
        }

        // If we're using the underlined style and there's a new line, draw a
        // line
        /*
        if (curUnderlined && (curChar == '\n' && prevChar != '\n'))
        {
            std::cerr << "Underline added (char = n)" << std::endl;
            TextComp::addLine(m_vertices[indexArrayVert], x, y,
        curInfo.getInfoText().getInfo<InfoText::Info::FILL_COLOR>(),
        curUnderlineOffset, curUnderlineThickness, 0);

            if
        (std::abs(curInfo.getInfoText().getInfo<InfoText::Info::THICKNESS>()) >
        m_epsilon_f)
            {
                TextComp::addLine(m_outlineVertices[indexArrayVert], x, y,
        curInfo.getInfoText().getInfo<InfoText::Info::OUTLINE_COLOR>(),
        curUnderlineOffset, curUnderlineThickness,
                                  curInfo.getInfoText().getInfo<InfoText::Info::THICKNESS>());
            }
        }
        */

        // If we're using the strike through style and there's a new line, draw
        // a line across all characters
        /*
        if (curStrikeThrough && (curChar == '\n' && prevChar != '\n'))
        {
            TextComp::addLine(m_vertices[indexArrayVert], x, y,
        curInfo.getInfoText().getInfo<InfoText::Info::FILL_COLOR>(),
        curStrikeThroughOffset, curUnderlineThickness, 0);

            if
        (std::abs(curInfo.getInfoText().getInfo<InfoText::Info::THICKNESS>()) >
        m_epsilon_f)
            {
                TextComp::addLine(m_outlineVertices[indexArrayVert], x, y,
        curInfo.getInfoText().getInfo<InfoText::Info::OUTLINE_COLOR>(),
        curStrikeThroughOffset, curUnderlineThickness,
                                  curInfo.getInfoText().getInfo<InfoText::Info::THICKNESS>());
            }
        }
        */

        prevChar = curChar;

        // Handle special characters
        if ((U' ' == curChar) || (U'\n' == curChar) || (U'\t' == curChar))
        {
            // Update the current bounds (min coordinates)
            minX = std::min(minX, x);
            minY = std::min(minY, y);

            switch (curChar)
            {
            case U' ': {
                if (curUnderlined)
                {
                    TextComp::addLinePart(
                        curUndelineVertFill, prevX, x, y,
                        curInfo.getInfoText()
                            .getInfo<InfoText::Info::FILL_COLOR>(),
                        curUnderlineOffset, curUnderlineThickness, 0);
                    if (std::abs(curInfo.getInfoText()
                                     .getInfo<InfoText::Info::THICKNESS>()) >
                        Func::m_epsilon_f)
                    {
                        TextComp::addLinePart(
                            curUndelineVertOutline, prevX, x, y,
                            curInfo.getInfoText()
                                .getInfo<InfoText::Info::OUTLINE_COLOR>(),
                            curUnderlineOffset, curUnderlineThickness,
                            curInfo.getInfoText()
                                .getInfo<InfoText::Info::THICKNESS>());
                    }
                }
                if (curStrikeThrough)
                {
                    TextComp::addLinePart(
                        curStrikeThroughVertFill, prevX, x, y,
                        curInfo.getInfoText()
                            .getInfo<InfoText::Info::FILL_COLOR>(),
                        curStrikeThroughOffset, curUnderlineThickness, 0);
                    if (std::abs(curInfo.getInfoText()
                                     .getInfo<InfoText::Info::THICKNESS>()) >
                        Func::m_epsilon_f)
                    {
                        TextComp::addLinePart(
                            curStrikeThroughVertOutline, prevX, x, y,
                            curInfo.getInfoText()
                                .getInfo<InfoText::Info::OUTLINE_COLOR>(),
                            curStrikeThroughOffset, curUnderlineThickness,
                            curInfo.getInfoText()
                                .getInfo<InfoText::Info::THICKNESS>());
                    }
                }
                x += curWhitespaceWidth;
                if ((m_widthWrap >= 0.0f) && (m_widthWrap < x))
                {
                    y += curLineSpacing;
                    if (curUnderlined)
                    {
                        m_vertices[indexArrayVert].insert(
                            m_vertices[indexArrayVert].end(),
                            curUndelineVertFill.begin(),
                            curUndelineVertFill.end());
                        m_outlineVertices[indexArrayVert].insert(
                            m_outlineVertices[indexArrayVert].end(),
                            curUndelineVertOutline.begin(),
                            curUndelineVertOutline.end());
                        curUndelineVertFill.clear();
                        curUndelineVertOutline.clear();
                    }
                    if (curStrikeThrough)
                    {
                        m_vertices[indexArrayVert].insert(
                            m_vertices[indexArrayVert].end(),
                            curStrikeThroughVertFill.begin(),
                            curStrikeThroughVertFill.end());
                        m_outlineVertices[indexArrayVert].insert(
                            m_outlineVertices[indexArrayVert].end(),
                            curStrikeThroughVertOutline.begin(),
                            curStrikeThroughVertOutline.end());
                        curStrikeThroughVertFill.clear();
                        curStrikeThroughVertOutline.clear();
                    }
                    x = 0;
                }
                prevX = x;
                break;
            }
            case U'\t': {
                if (curUnderlined)
                {
                    TextComp::addLinePart(
                        curUndelineVertFill, prevX, x, y,
                        curInfo.getInfoText()
                            .getInfo<InfoText::Info::FILL_COLOR>(),
                        curUnderlineOffset, curUnderlineThickness, 0);
                    if (std::abs(curInfo.getInfoText()
                                     .getInfo<InfoText::Info::THICKNESS>()) >
                        Func::m_epsilon_f)
                    {
                        TextComp::addLinePart(
                            curUndelineVertOutline, prevX, x, y,
                            curInfo.getInfoText()
                                .getInfo<InfoText::Info::OUTLINE_COLOR>(),
                            curUnderlineOffset, curUnderlineThickness,
                            curInfo.getInfoText()
                                .getInfo<InfoText::Info::THICKNESS>());
                    }
                }
                if (curStrikeThrough)
                {
                    TextComp::addLinePart(
                        curStrikeThroughVertFill, prevX, x, y,
                        curInfo.getInfoText()
                            .getInfo<InfoText::Info::FILL_COLOR>(),
                        curStrikeThroughOffset, curUnderlineThickness, 0);
                    if (std::abs(curInfo.getInfoText()
                                     .getInfo<InfoText::Info::THICKNESS>()) >
                        Func::m_epsilon_f)
                    {
                        TextComp::addLinePart(
                            curStrikeThroughVertOutline, prevX, x, y,
                            curInfo.getInfoText()
                                .getInfo<InfoText::Info::OUTLINE_COLOR>(),
                            curStrikeThroughOffset, curUnderlineThickness,
                            curInfo.getInfoText()
                                .getInfo<InfoText::Info::THICKNESS>());
                    }
                }
                x += curWhitespaceWidth * 4;
                prevX = x;
                break;
            }
            case U'\n': {
                y += curLineSpacing;
                if (curUnderlined)
                {
                    m_vertices[indexArrayVert].insert(
                        m_vertices[indexArrayVert].end(),
                        curUndelineVertFill.begin(), curUndelineVertFill.end());
                    m_outlineVertices[indexArrayVert].insert(
                        m_outlineVertices[indexArrayVert].end(),
                        curUndelineVertOutline.begin(),
                        curUndelineVertOutline.end());
                    curUndelineVertFill.clear();
                    curUndelineVertOutline.clear();
                }
                if (curStrikeThrough)
                {
                    m_vertices[indexArrayVert].insert(
                        m_vertices[indexArrayVert].end(),
                        curStrikeThroughVertFill.begin(),
                        curStrikeThroughVertFill.end());
                    m_outlineVertices[indexArrayVert].insert(
                        m_outlineVertices[indexArrayVert].end(),
                        curStrikeThroughVertOutline.begin(),
                        curStrikeThroughVertOutline.end());
                    curStrikeThroughVertFill.clear();
                    curStrikeThroughVertOutline.clear();
                }
                x = 0;
                prevX = 0;
                break;
            }
            default: {
                break;
            }
            }

            // Update the current bounds (max coordinates)
            maxX = std::max(maxX, x);
            maxY = std::max(maxY, y);

            // Next glyph, no need to create a quad for whitespace
            continue;
        }

        // Apply the outline
        if (std::abs(
                curInfo.getInfoText().getInfo<InfoText::Info::THICKNESS>()) >
            Func::m_epsilon_f)
        {
            const sf::Glyph &glyph =
                curInfo.getInfoText().getInfo<InfoText::Info::FONT>()->getGlyph(
                    curChar,
                    static_cast<uint32_t>(
                        curInfo.getInfoText()
                            .getInfo<InfoText::Info::CHAR_SIZE>()),
                    curBold,
                    curInfo.getInfoText().getInfo<InfoText::Info::THICKNESS>());

            float32_t left = glyph.bounds.left;
            float32_t top = glyph.bounds.top;
            float32_t right = glyph.bounds.left + glyph.bounds.width;
            float32_t bottom = glyph.bounds.top + glyph.bounds.height;

            // Add the outline glyph to the vertices
            TextComp::addGlyphQuad(
                m_outlineVertices[indexArrayVert], sf::Vector2<float32_t>(x, y),
                curInfo.getInfoText().getInfo<InfoText::Info::OUTLINE_COLOR>(),
                glyph, curItalicShear,
                curInfo.getInfoText().getInfo<InfoText::Info::THICKNESS>());

            // Update the current bounds with the outlined glyph bounds
            minX = std::min(
                minX,
                x + left - curItalicShear * bottom -
                    curInfo.getInfoText().getInfo<InfoText::Info::THICKNESS>());
            maxX = std::max(
                maxX,
                x + right - curItalicShear * top -
                    curInfo.getInfoText().getInfo<InfoText::Info::THICKNESS>());
            minY = std::min(
                minY,
                y + top -
                    curInfo.getInfoText().getInfo<InfoText::Info::THICKNESS>());
            maxY = std::max(
                maxY,
                y + bottom -
                    curInfo.getInfoText().getInfo<InfoText::Info::THICKNESS>());
        }

        // Extract the current glyph's description
        const sf::Glyph &glyph =
            curInfo.getInfoText().getInfo<InfoText::Info::FONT>()->getGlyph(
                curChar,
                static_cast<uint32_t>(
                    curInfo.getInfoText().getInfo<InfoText::Info::CHAR_SIZE>()),
                curBold);

        // Add the glyph to the vertices
        TextComp::addGlyphQuad(
            m_vertices[indexArrayVert], sf::Vector2<float32_t>(x, y),
            curInfo.getInfoText().getInfo<InfoText::Info::FILL_COLOR>(), glyph,
            curItalicShear, 0);

        // Update the current bounds with the non outlined glyph bounds
        if (std::abs(
                curInfo.getInfoText().getInfo<InfoText::Info::THICKNESS>()) <=
            Func::m_epsilon_f)
        {
            float32_t left = glyph.bounds.left;
            float32_t top = glyph.bounds.top;
            float32_t right = glyph.bounds.left + glyph.bounds.width;
            float32_t bottom = glyph.bounds.top + glyph.bounds.height;

            minX = std::min(minX, (x + left) - (curItalicShear * bottom));
            maxX = std::max(maxX, (x + right) - (curItalicShear * top));
            minY = std::min(minY, y + top);
            maxY = std::max(maxY, y + bottom);
        }

        // Advance to the next character
        if (!std::get<0>(curInfo.getInfoText()
                             .getInfo<InfoText::Info::LETTER_SPACING>()))
        {
            x += std::get<1>(curInfo.getInfoText()
                                 .getInfo<InfoText::Info::LETTER_SPACING>());
        }
        else
        {
            x += glyph.advance + curLetterSpacing;
        }
        if (curUnderlined)
        {
            TextComp::addLinePart(
                curUndelineVertFill, prevX, x, y,
                curInfo.getInfoText().getInfo<InfoText::Info::FILL_COLOR>(),
                curUnderlineOffset, curUnderlineThickness, 0);
            if (std::abs(curInfo.getInfoText()
                             .getInfo<InfoText::Info::THICKNESS>()) >
                Func::m_epsilon_f)
            {
                TextComp::addLinePart(
                    curUndelineVertOutline, prevX, x, y,
                    curInfo.getInfoText()
                        .getInfo<InfoText::Info::OUTLINE_COLOR>(),
                    curUnderlineOffset, curUnderlineThickness,
                    curInfo.getInfoText().getInfo<InfoText::Info::THICKNESS>());
            }
        }
        if (curStrikeThrough)
        {
            TextComp::addLinePart(
                curStrikeThroughVertFill, prevX, x, y,
                curInfo.getInfoText().getInfo<InfoText::Info::FILL_COLOR>(),
                curStrikeThroughOffset, curUnderlineThickness, 0);
            if (std::abs(curInfo.getInfoText()
                             .getInfo<InfoText::Info::THICKNESS>()) >
                Func::m_epsilon_f)
            {
                TextComp::addLinePart(
                    curStrikeThroughVertOutline, prevX, x, y,
                    curInfo.getInfoText()
                        .getInfo<InfoText::Info::OUTLINE_COLOR>(),
                    curStrikeThroughOffset, curUnderlineThickness,
                    curInfo.getInfoText().getInfo<InfoText::Info::THICKNESS>());
            }
        }
        prevX = x;
        prevInfo = curInfo;
    }

    // bool  curBold             =
    // curInfo.getInfoText().getInfo<InfoText::Info::STYLE>() &
    // InfoText::Style::Bold;
    bool curUnderlined =
        curInfo.getInfoText().getInfo<InfoText::Info::STYLE>() &
        InfoText::Style::UNDERLINED;
    bool curStrikeThrough =
        curInfo.getInfoText().getInfo<InfoText::Info::STYLE>() &
        InfoText::Style::STRIKETHROUGH;
    // float32_t curUnderlineOffset    =
    // curInfo.getInfoText().getInfo<InfoText::Info::FONT>()->getUnderlinePosition(curInfo.getInfoText().getInfo<InfoText::Info::CHAR_SIZE>());
    // float32_t curUnderlineThickness =
    // curInfo.getInfoText().getInfo<InfoText::Info::FONT>()->getUnderlineThickness(curInfo.getInfoText().getInfo<InfoText::Info::CHAR_SIZE>());
    // sf::Rect<float32_t> curXBounds =
    // curInfo.getInfoText().getInfo<InfoText::Info::FONT>()->getGlyph('x',
    // curInfo.getInfoText().getInfo<InfoText::Info::CHAR_SIZE>(),
    // curBold).bounds; float32_t curStrikeThroughOffset = curXBounds.top +
    // curXBounds.height / 2.f;
    if (curUnderlined)
    {
        m_vertices[indexArrayVert].insert(m_vertices[indexArrayVert].end(),
                                          curUndelineVertFill.begin(),
                                          curUndelineVertFill.end());
        m_outlineVertices[indexArrayVert].insert(
            m_outlineVertices[indexArrayVert].end(),
            curUndelineVertOutline.begin(), curUndelineVertOutline.end());
    }
    if (curStrikeThrough)
    {
        m_vertices[indexArrayVert].insert(m_vertices[indexArrayVert].end(),
                                          curStrikeThroughVertFill.begin(),
                                          curStrikeThroughVertFill.end());
        m_outlineVertices[indexArrayVert].insert(
            m_outlineVertices[indexArrayVert].end(),
            curStrikeThroughVertOutline.begin(),
            curStrikeThroughVertOutline.end());
    }
    // If we're using the underlined style, add the last line
    /*
    if (curUnderlined && (x > 0))
    {
        std::cerr << "Underline added (x > 0)" << std::endl;
        TextComp::addLine(m_vertices[indexArrayVert], x, y,
    curInfo.getInfoText().getInfo<InfoText::Info::FILL_COLOR>(),
    curUnderlineOffset, curUnderlineThickness, 0);

        if (std::abs(curInfo.getInfoText().getInfo<InfoText::Info::THICKNESS>())
    > m_epsilon_f)
        {
            TextComp::addLine(m_outlineVertices[indexArrayVert], x, y,
    curInfo.getInfoText().getInfo<InfoText::Info::OUTLINE_COLOR>(),
    curUnderlineOffset, curUnderlineThickness,
                              curInfo.getInfoText().getInfo<InfoText::Info::THICKNESS>());
        }
    }
    */

    // If we're using the strike through style, add the last line across all
    // characters
    /*
    if (curStrikeThrough && (x > 0))
    {
        TextComp::addLine(m_vertices[indexArrayVert], x, y,
    curInfo.getInfoText().getInfo<InfoText::Info::FILL_COLOR>(),
    curStrikeThroughOffset, curUnderlineThickness, 0);

        if (std::abs(curInfo.getInfoText().getInfo<InfoText::Info::THICKNESS>())
    > m_epsilon_f)
        {
            TextComp::addLine(m_outlineVertices[indexArrayVert], x, y,
    curInfo.getInfoText().getInfo<InfoText::Info::OUTLINE_COLOR>(),
    curStrikeThroughOffset, curUnderlineThickness,
                              curInfo.getInfoText().getInfo<InfoText::Info::THICKNESS>());
        }
    }
    */

    // Update the bounding rectangle
    m_bounds.left = minX;
    m_bounds.top = minY;
    m_bounds.width = maxX - minX;
    m_bounds.height = maxY - minY;
}

} // namespace segment_d1
