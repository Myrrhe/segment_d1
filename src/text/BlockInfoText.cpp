#include "text/BlockInfoText.hpp"
#include "Constants.hpp"
#include "Func.hpp"

namespace segment_d1
{

BlockInfoText::BlockInfoText() : NodeText(), infoText(), useInfo()
{
    // ctor
}

BlockInfoText::~BlockInfoText()
{
    // dtor
}

BlockInfoText::BlockInfoText(const BlockInfoText &other)
    : NodeText(other), infoText(other.infoText), useInfo(other.useInfo)
{
    // copy ctor
}

BlockInfoText::BlockInfoText(const InfoText &newInfoText)
    : NodeText(), infoText(newInfoText), useInfo()
{
    useInfo.fill(true);
}

BlockInfoText::BlockInfoText(const std::u32string &str)
    : NodeText(), infoText(), useInfo()
{
    infoText = InfoText(str);
    useInfo.fill(false);
    std::vector<std::u32string> vecStr = Func::split(str, U',');
    for (std::size_t i = 0; i < vecStr.size(); ++i)
    {
        std::pair<std::u32string, std::u32string> keyVal =
            Func::getKeyValueLine(vecStr[i]);
        if (keyVal.first == InfoText::Keys32[1])
        {
            // infoText.setCharSize(std::stoul(keyVal.second, nullptr, 10));
            useInfo[1] = true;
        }
        else if (keyVal.first == InfoText::Keys32[2])
        {
            // infoText.setLetterSpacing(std::stof(keyVal.second, nullptr));
            useInfo[2] = true;
        }
        else if (keyVal.first == InfoText::Keys32[3])
        {
            // infoText.setLineSpacing(std::stof(keyVal.second, nullptr));
            useInfo[3] = true;
        }
        else if (keyVal.first == InfoText::Keys32[4])
        {
            // infoText.setStyle(static_cast<InfoText::Style>(std::stoul(keyVal.second,
            // nullptr, 10)));
            useInfo[4] = true;
        }
        else if (keyVal.first == InfoText::Keys32[5])
        {
            // infoText.setFillColor(sf::Color(std::stoul(keyVal.second,
            // nullptr, 10)));
            useInfo[5] = true;
        }
        else if (keyVal.first == InfoText::Keys32[6])
        {
            // infoText.setOutlineColor(sf::Color(std::stoul(keyVal.second,
            // nullptr, 10)));
            useInfo[6] = true;
        }
        else if (keyVal.first == InfoText::Keys32[7])
        {
            // infoText.setThickness(std::stof(keyVal.second, nullptr));
            useInfo[7] = true;
        }
    }
}

BlockInfoText &BlockInfoText::operator=(const BlockInfoText &rhs)
{
    if (this == &rhs)
    {
        return *this; // handle self assignment
    }
    // assignment operator
    NodeText::operator=(rhs);
    infoText = rhs.infoText;
    useInfo = rhs.useInfo;
    return *this;
}

void BlockInfoText::release() {}

NodeText::Type BlockInfoText::getType() const { return Type::BLOCKINFO; }

const sf::Font *BlockInfoText::getFont() const { return infoText.getFont(); }

uint64_t BlockInfoText::getCharSize() const { return infoText.getCharSize(); }

const std::tuple<bool, float32_t> &BlockInfoText::getLetterSpacing() const
{
    return infoText.getLetterSpacing();
}

float32_t BlockInfoText::getLineSpacingFactor() const
{
    return infoText.getLineSpacingFactor();
}

InfoText::Style BlockInfoText::getStyle() const { return infoText.getStyle(); }

sf::Color BlockInfoText::getFillColor() const
{
    return infoText.getFillColor();
}

sf::Color BlockInfoText::getOutlineColor() const
{
    return infoText.getOutlineColor();
}

float32_t BlockInfoText::getThickness() const
{
    return infoText.getThickness();
}

bool BlockInfoText::isUsed(uint64_t i) const { return useInfo[i]; }

bool BlockInfoText::isUsed(InfoText::Info info) const
{
    switch (info)
    {
    case InfoText::Info::FONT: {
        return useInfo[0];
        break;
    }
    case InfoText::Info::CHAR_SIZE: {
        return useInfo[1];
        break;
    }
    case InfoText::Info::LETTER_SPACING: {
        return useInfo[2];
        break;
    }
    case InfoText::Info::LINE_SPACING_FACTOR: {
        return useInfo[3];
        break;
    }
    case InfoText::Info::STYLE: {
        return useInfo[4];
        break;
    }
    case InfoText::Info::FILL_COLOR: {
        return useInfo[5];
        break;
    }
    case InfoText::Info::OUTLINE_COLOR: {
        return useInfo[6];
        break;
    }
    case InfoText::Info::THICKNESS: {
        return useInfo[7];
        break;
    }
    default: {
        return false;
        break;
    }
    }
}

void BlockInfoText::setUsed(InfoText::Info info, bool newUsed)
{
    switch (info)
    {
    case InfoText::Info::FONT: {
        useInfo[0] = newUsed;
        break;
    }
    case InfoText::Info::CHAR_SIZE: {
        useInfo[1] = newUsed;
        break;
    }
    case InfoText::Info::LETTER_SPACING: {
        useInfo[2] = newUsed;
        break;
    }
    case InfoText::Info::LINE_SPACING_FACTOR: {
        useInfo[3] = newUsed;
        break;
    }
    case InfoText::Info::STYLE: {
        useInfo[4] = newUsed;
        break;
    }
    case InfoText::Info::FILL_COLOR: {
        useInfo[5] = newUsed;
        break;
    }
    case InfoText::Info::OUTLINE_COLOR: {
        useInfo[6] = newUsed;
        break;
    }
    case InfoText::Info::THICKNESS: {
        useInfo[7] = newUsed;
        break;
    }
    default: {
        break;
    }
    }
}

const InfoText &BlockInfoText::getInfoText() const { return infoText; }

bool BlockInfoText::isUseful() const
{
    bool useful = false;
    for (InfoText::Info i = InfoText::Info::INFO_BEGIN;
         i < InfoText::Info::NB_INFO; i++)
    {
        useful = useful || isUsed(i);
    }
    return useful;
}

bool BlockInfoText::operator==(const NodeText &right) const
{
    if (getType() != right.getType())
    {
        return false;
    }
    const BlockInfoText *rightP = dynamic_cast<const BlockInfoText *>(&right);
    bool isEqual = infoText == rightP->infoText;
    for (uint64_t i = 0; i < 8; i++)
    {
        isEqual = isEqual && useInfo[i] == rightP->useInfo[i];
    }
    return isEqual;
}

bool BlockInfoText::operator!=(const NodeText &right) const
{
    return !(*this == right);
}

BlockInfoText &BlockInfoText::operator+=(const BlockInfoText &right)
{
    if (right.isUsed(InfoText::Info::FONT))
    {
        infoText.setInfo<InfoText::Info::FONT>(
            right.getInfoText().getInfo<InfoText::Info::FONT>());
        setUsed(InfoText::Info::FONT, true);
    }
    if (right.isUsed(InfoText::Info::CHAR_SIZE))
    {
        infoText.setInfo<InfoText::Info::CHAR_SIZE>(
            right.getInfoText().getInfo<InfoText::Info::CHAR_SIZE>());
        setUsed(InfoText::Info::CHAR_SIZE, true);
    }
    if (right.isUsed(InfoText::Info::LETTER_SPACING))
    {
        infoText.setInfo<InfoText::Info::LETTER_SPACING>(
            right.getInfoText().getInfo<InfoText::Info::LETTER_SPACING>());
        setUsed(InfoText::Info::LETTER_SPACING, true);
    }
    if (right.isUsed(InfoText::Info::LINE_SPACING_FACTOR))
    {
        infoText.setInfo<InfoText::Info::LINE_SPACING_FACTOR>(
            right.getInfoText().getInfo<InfoText::Info::LINE_SPACING_FACTOR>());
        setUsed(InfoText::Info::LINE_SPACING_FACTOR, true);
    }
    if (right.isUsed(InfoText::Info::STYLE))
    {
        infoText.setInfo<InfoText::Info::STYLE>(
            right.getInfoText().getInfo<InfoText::Info::STYLE>());
        setUsed(InfoText::Info::STYLE, true);
    }
    if (right.isUsed(InfoText::Info::FILL_COLOR))
    {
        infoText.setInfo<InfoText::Info::FILL_COLOR>(
            right.getInfoText().getInfo<InfoText::Info::FILL_COLOR>());
        setUsed(InfoText::Info::FILL_COLOR, true);
    }
    if (right.isUsed(InfoText::Info::OUTLINE_COLOR))
    {
        infoText.setInfo<InfoText::Info::OUTLINE_COLOR>(
            right.getInfoText().getInfo<InfoText::Info::OUTLINE_COLOR>());
        setUsed(InfoText::Info::OUTLINE_COLOR, true);
    }
    if (right.isUsed(InfoText::Info::THICKNESS))
    {
        infoText.setInfo<InfoText::Info::THICKNESS>(
            right.getInfoText().getInfo<InfoText::Info::THICKNESS>());
        setUsed(InfoText::Info::THICKNESS, true);
    }
    return *this;
}

BlockInfoText BlockInfoText::operator+(const BlockInfoText &right) const
{
    return BlockInfoText(*this) += right;
}

const std::u32string &BlockInfoText::getStr() const { return EmptyStr32; }

std::u32string BlockInfoText::toStr() const
{
    if (!isUseful())
    {
        return U"";
    }
    std::u32string res = U"<";
    for (InfoText::Info i = InfoText::Info::INFO_BEGIN;
         i < InfoText::Info::NB_INFO; i++)
    {
        if (isUsed(i))
        {
            if (res != U"<")
            {
                res += InfoText::Separator;
            }
            res += InfoText::getKeyStr32(i) + U"=" + infoText.getValStr(i);
        }
    }
    res += U'>';
    return res;
}

} // namespace segment_d1
