#ifndef CHAINTEXT_HPP
#define CHAINTEXT_HPP
#include "text/BlockClosingText.hpp"
#include "text/BlockInfoText.hpp"
#include "text/LeafText.hpp"


namespace segment_d1
{

class ChainText final
{
public:
    /** Default constructor */
    ChainText();
    /** Copy constructor
     *  \param other Object to copy from
     */
    ChainText(const ChainText &other);
    /** Assignment operator
     *  \param rhs Object to assign from
     *  \return A reference to this
     */
    explicit ChainText(const std::u32string &str);
    explicit ChainText(const std::string &str);
    ChainText &operator=(const ChainText &rhs);
    /** Default destructor */
    ~ChainText();

    [[nodiscard]] std::size_t getSize() const;
    bool isEmpty() const;
    const NodeText *operator[](const std::size_t i) const;

    uint64_t getNbChar() const;
    uint64_t getNbChar(const uint64_t i) const;

    std::u32string getStr() const;

    std::u32string toStr() const;
private:
    bool parseString(const std::u32string &str, const bool setNodes);

    friend bool operator==(const ChainText &left, const ChainText &right)
    {
        bool res = true;
        if (left.nodes.size() != right.nodes.size())
        {
            res = false;
        }
        if (res)
        {
            const std::size_t nodesSize = left.nodes.size();
            for (std::size_t i = 0; i < nodesSize; ++i)
            {
                res = res && (*left.nodes[i]).isEqual(*right.nodes[i]);
            }
        }
        return res;
    }
    friend bool operator!=(const ChainText &left, const ChainText &right)
    {
        return !(left == right);
    }

    std::vector<NodeText *> nodes;
    std::vector<LeafText> leafs;
    std::vector<BlockInfoText> blocks;
    std::vector<BlockClosingText> blocksClosing;
};

} // namespace segment_d1

#endif // CHAINTEXT_HPP
