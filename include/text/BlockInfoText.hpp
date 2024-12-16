#ifndef BLOCKINFOTEXT_HPP
#define BLOCKINFOTEXT_HPP
#include "text/InfoText.hpp"
#include "text/NodeText.hpp"
#include <array>

namespace segment_d1
{

class BlockInfoText final : public NodeText
{
public:
    /** Default constructor */
    BlockInfoText();
    /** Default destructor */
    ~BlockInfoText();
    /** Copy constructor
     *  \param other Object to copy from
     */
    BlockInfoText(const BlockInfoText &other);
    BlockInfoText(const InfoText &newInfoText);
    BlockInfoText(const std::u32string &str);
    /** Assignment operator
     *  \param rhs Object to assign from
     *  \return A reference to this
     */
    BlockInfoText &operator=(const BlockInfoText &rhs);

    void release() override;

    Type getType() const override;

    const sf::Font *getFont() const;
    uint64_t getCharSize() const;
    const std::tuple<bool, float32_t> &getLetterSpacing() const;
    float32_t getLineSpacingFactor() const;
    InfoText::Style getStyle() const;
    sf::Color getFillColor() const;
    sf::Color getOutlineColor() const;
    float32_t getThickness() const;

    bool isUsed(uint64_t i) const;
    bool isUsed(InfoText::Info info) const;
    bool isUseful() const;

    const InfoText &getInfoText() const;

    const std::u32string &getStr() const override;

    bool operator==(const NodeText &right) const override;
    bool operator!=(const NodeText &right) const override;

    BlockInfoText &operator+=(const BlockInfoText &right);
    BlockInfoText operator+(const BlockInfoText &right) const;

    std::u32string toStr() const override;

protected:
private:
    void setUsed(InfoText::Info info, bool newUsed);

    InfoText infoText;
    std::array<bool, 8> useInfo;
};

} // namespace segment_d1

#endif // BLOCKINFOTEXT_HPP
