#ifndef BLOCKTEXT_HPP
#define BLOCKTEXT_HPP
#include "text/InfoText.hpp"
#include "text/NodeText.hpp"
#include <vector>

namespace segment_d1
{

class BlockText final : public NodeText
{
public:
    /** Default constructor */
    BlockText();
    /** Copy constructor
     *  \param other Object to copy from
     */
    explicit BlockText(const std::u32string_view &str);
    BlockText(const BlockText &other);
    /** Assignment operator
     *  \param rhs Object to assign from
     *  \return A reference to this
     */
    BlockText &operator=(const BlockText &rhs);
    /** Default destructor */
    ~BlockText() override;

    void release() override;

    Type getType() const override;

    const std::u32string &getStr() const override;

    bool isEqual(const NodeText &right) const override;

    std::u32string toStr() const override;

private:
    InfoText infoText;
    std::vector<NodeText *> blocks;

    friend bool operator==(const BlockText &left, const BlockText &right)
    {
        bool res = false;
        if (left.getType() == right.getType())
        {
            res = left.infoText == right.infoText;
            const std::size_t blocksSize = left.blocks.size();
            for (std::size_t i = 0; i < blocksSize; ++i)
            {
                res = res && (*const_cast<const NodeText *>(left.blocks[i]))
                                 .isEqual(right);
            }
        }
        return res;
    }
    friend bool operator!=(const BlockText &left, const BlockText &right)
    {
        return !(left == right);
    }
};

} // namespace segment_d1

#endif // BLOCKTEXT_HPP
