#ifndef CHAINTEXT_HPP
#define CHAINTEXT_HPP
#include "text/BlockClosingText.hpp"
#include "text/BlockInfoText.hpp"
#include "text/LeafText.hpp"


namespace segment_d1
{

class ChainText
{
public:
    /** Default constructor */
    ChainText();
    /** Default destructor */
    ~ChainText();
    /** Copy constructor
     *  \param other Object to copy from
     */
    ChainText(const ChainText &other);
    /** Assignment operator
     *  \param rhs Object to assign from
     *  \return A reference to this
     */
    ChainText(const std::u32string &str);
    ChainText(const std::string &str);
    // ChainText(const sf::String& str);
    ChainText &operator=(const ChainText &rhs);

    std::size_t getSize() const;
    bool isEmpty() const;
    const NodeText *operator[](std::size_t i) const;

    bool operator==(const ChainText &right) const;
    bool operator!=(const ChainText &right) const;

    uint64_t getNbChar() const;
    uint64_t getNbChar(uint64_t i) const;

    std::u32string getStr() const;

    std::u32string toStr() const;

protected:
private:
    bool parseString(const std::u32string &str, bool setNodes);

    std::vector<NodeText *> nodes;
    std::vector<LeafText> leafs;
    std::vector<BlockInfoText> blocks;
    std::vector<BlockClosingText> blocksClosing;
};

} // namespace segment_d1

#endif // CHAINTEXT_HPP
