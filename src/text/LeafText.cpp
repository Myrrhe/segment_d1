#include "text/LeafText.hpp"

namespace segment_d1
{

LeafText::LeafText() : NodeText(), str(U"")
{
    // ctor
}

LeafText::~LeafText() = default;

LeafText::LeafText(const LeafText &other) = default;

LeafText::LeafText(const std::u32string &newStr) : NodeText(), str(newStr) {}

LeafText &LeafText::operator=(const LeafText &rhs) = default;

void LeafText::release()
{
    // Nothing to do
}

NodeText::Type LeafText::getType() const { return Type::LEAF; }

bool LeafText::isEmpty() const { return str.empty(); }

const std::u32string &LeafText::getStr() const { return str; }

std::size_t LeafText::getSize() const { return str.size(); }

bool LeafText::isEqual(const NodeText &right) const
{
    bool res = false;
    if (getType() == right.getType())
    {
        res = str == dynamic_cast<const LeafText *>(&right)->str;
    }
    return res;
}

std::u32string LeafText::toStr() const { return str; }

} // namespace segment_d1
