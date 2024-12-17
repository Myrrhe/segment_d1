#include "text/BlockClosingText.hpp"
#include "Constants.hpp"

namespace segment_d1
{

BlockClosingText::BlockClosingText() : NodeText()
{
    // ctor
}

BlockClosingText::~BlockClosingText() = default;

BlockClosingText::BlockClosingText(const BlockClosingText &other) = default;

BlockClosingText &
BlockClosingText::operator=(const BlockClosingText &rhs) = default;

void BlockClosingText::release()
{
    // Nothing to do
}

NodeText::Type BlockClosingText::getType() const { return Type::BLOCKCLOSING; }

bool BlockClosingText::isEqual(const NodeText &right) const
{
    return getType() == right.getType();
}

const std::u32string &BlockClosingText::getStr() const { return EmptyStr32; }

std::u32string BlockClosingText::toStr() const { return U"</>"; }

} // namespace segment_d1
