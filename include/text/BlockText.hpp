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
    /** Default destructor */
    ~BlockText();
    /** Copy constructor
     *  \param other Object to copy from
     */
    BlockText(const std::u32string &str);
    BlockText(const BlockText &other);
    /** Assignment operator
     *  \param rhs Object to assign from
     *  \return A reference to this
     */
    BlockText &operator=(const BlockText &rhs);

    void release() override;

    Type getType() const override;

    const std::u32string &getStr() const override;

    bool operator==(const NodeText &right) const override;
    bool operator!=(const NodeText &right) const override;

    std::u32string toStr() const override;

protected:
private:
    InfoText infoText;
    std::vector<NodeText *> blocks;
};

} // namespace segment_d1

#endif // BLOCKTEXT_HPP
