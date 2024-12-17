#ifndef BLOCKCLOSINGTEXT_HPP
#define BLOCKCLOSINGTEXT_HPP
#include "text/NodeText.hpp"

namespace segment_d1
{

class BlockClosingText final : public NodeText
{
public:
    /** Default constructor */
    BlockClosingText();
    /** Copy constructor
     *  \param other Object to copy from
     */
    BlockClosingText(const BlockClosingText &other);
    /** Assignment operator
     *  \param rhs Object to assign from
     *  \return A reference to this
     */
    BlockClosingText &operator=(const BlockClosingText &rhs);
    /** Default destructor */
    ~BlockClosingText() override;

    void release() override;

    Type getType() const override;

    const std::u32string &getStr() const override;

    bool isEqual(const NodeText &right) const override;

    std::u32string toStr() const override;

protected:
private:
    friend bool operator==(const BlockClosingText &left,
                           const BlockClosingText &right)
    {
        return left.getType() == right.getType();
    }
    friend bool operator!=(const BlockClosingText &left,
                           const BlockClosingText &right)
    {
        return !(left == right);
    }
};

} // namespace segment_d1

#endif // BLOCKCLOSINGTEXT_HPP
