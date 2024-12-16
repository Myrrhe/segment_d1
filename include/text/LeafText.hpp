#ifndef LEAFTEXT_HPP
#define LEAFTEXT_HPP
#include "text/NodeText.hpp"
#include <string>

namespace segment_d1
{

class LeafText final : public NodeText
{
public:
    /** Default constructor */
    LeafText();
    /** Default destructor */
    ~LeafText();
    /** Copy constructor
     *  \param other Object to copy from
     */
    LeafText(const LeafText &other);
    LeafText(const std::u32string &newStr);
    /** Assignment operator
     *  \param other Object to assign from
     *  \return A reference to this
     */
    LeafText &operator=(const LeafText &other);

    void release() override;

    Type getType() const override;

    bool isEmpty() const;

    const std::u32string &getStr() const override;

    std::size_t getSize() const;

    bool operator==(const NodeText &right) const override;
    bool operator!=(const NodeText &right) const override;

    std::u32string toStr() const override;

protected:
private:
    std::u32string str;
};

} // namespace segment_d1

#endif // LEAFTEXT_HPP
