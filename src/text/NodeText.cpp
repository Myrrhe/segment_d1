#include "text/NodeText.hpp"

namespace segment_d1
{

NodeText::NodeText()
{
    // ctor
}

NodeText::~NodeText()
{
    // dtor
}

NodeText::NodeText(const NodeText & /*other*/)
{
    // copy ctor
}

NodeText &NodeText::operator=(const NodeText &rhs)
{
    if (this == &rhs)
    {
        return *this; // handle self assignment
    }
    // assignment operator
    return *this;
}

} // namespace segment_d1
