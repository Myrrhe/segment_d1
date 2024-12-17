#ifndef NODETEXT_HPP
#define NODETEXT_HPP
#include <cstdint>
#include <string>

namespace segment_d1
{

class NodeText
{
public:
    enum class Type : uint64_t
    {
        LEAF,
        BLOCK,
        BLOCKINFO,
        BLOCKCLOSING
    };

    /** Default constructor */
    NodeText();
    /** Copy constructor
     *  \param other Object to copy from
     */
    NodeText(const NodeText &other);
    /** Assignment operator
     *  \param rhs Object to assign from
     *  \return A reference to this
     */
    NodeText &operator=(const NodeText &rhs);
    /** Default destructor */
    virtual ~NodeText();

    virtual void release() = 0;

    virtual Type getType() const = 0;

    virtual const std::u32string &getStr() const = 0;

    // virtual bool operator==(const NodeText &right) const = 0;
    // virtual bool operator!=(const NodeText &right) const = 0;

    virtual bool isEqual(const NodeText &right) const = 0;

    virtual std::u32string toStr() const = 0;
};

} // namespace segment_d1

#endif // NODETEXT_HPP
