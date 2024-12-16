#include "text/LeafText.hpp"

namespace segment_d1
{

LeafText::LeafText() : NodeText(), str(U"")
{
    // ctor
}

LeafText::~LeafText()
{
    // dtor
}

LeafText::LeafText(const LeafText &other) : NodeText(other), str(other.str)
{
    // copy ctor
}

LeafText::LeafText(const std::u32string &newStr) : NodeText(), str(newStr) {}

LeafText &LeafText::operator=(const LeafText &rhs)
{
    if (this == &rhs)
    {
        return *this; // handle self assignment
    }
    // assignment operator
    NodeText::operator=(rhs);
    str = rhs.str;
    return *this;
}

void LeafText::release() {}

NodeText::Type LeafText::getType() const { return Type::LEAF; }

bool LeafText::isEmpty() const { return str.empty(); }

const std::u32string &LeafText::getStr() const { return str; }

std::size_t LeafText::getSize() const { return str.size(); }

bool LeafText::operator==(const NodeText &right) const
{
    if (getType() != right.getType())
    {
        return false;
    }
    else
    {
        return str == dynamic_cast<const LeafText *>(&right)->str;
    }
}

bool LeafText::operator!=(const NodeText &right) const
{
    return !(*this == right);
}

std::u32string LeafText::toStr() const { return str; }

} // namespace segment_d1
