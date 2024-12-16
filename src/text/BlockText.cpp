#include "text/BlockText.hpp"
#include "Constants.hpp"

namespace segment_d1
{

BlockText::BlockText() : NodeText(), infoText(), blocks({})
{
    // ctor
}

BlockText::~BlockText()
{
    // dtor
}

BlockText::BlockText(const BlockText &other)
    : NodeText(other), infoText(other.infoText), blocks(other.blocks)
{
    release();
}

BlockText::BlockText(const std::u32string &str)
    : NodeText(), infoText(), blocks({})
{
    if (str.empty())
    {
    }
    /*
    std::vector<std::u32string> vecStr = {};
    uint64_t level = 0;
    for (int i = str.size() - 1; i >= 0; --i)
    {
        if (!((level += (str[i] == U'>') - (str[i] == U'<')))
         && (str[i] == 'U' || str[i] == 'I' || (str[i] == '-' &&
    !std::isdigit(str[i + 1]))))
        {
    */
    /*
    return new Oper(str[i] != U'-' ? str[i] != U'I' ? Oper::Op::UNION :
    Oper::Op::INTER : Oper::Op::SUBST, createTree(str.substr(0, i)),
                    createTree(str.substr(i + 1, std::string::npos)));
    */
    /*
        }
    }
    */
    /*
    if (str.front() == U'(')
    {
        for (int i = 0; i < str.size(); ++i)
        {
            if (!(level += (str[i] == U')') - (str[i] == U'(')))
            {
                return createTree(str.substr(1, i - 1));
            }
        }
        return nullptr;
    }
    else
    {
        if (str.front() == '{')
        {
            return new Set(str.substr(1, str.find('}', 0) - 1));
        }
        else
        {
            int posCl = std::min(str.find('[', 1), str.find(']', 1));
            int posSe = str.find(';', 0);
            return new Set(std::stoi(str.substr(1, posSe - 1), nullptr, 10) +
    (str.front() != '['), std::stoi(str.substr(posSe + 1, posCl - posSe - 1),
    nullptr, 10) - (str[posCl] != ']'));
        }
    }
    */
}

BlockText &BlockText::operator=(const BlockText &rhs)
{
    if (this == &rhs)
    {
        return *this; // handle self assignment
    }
    // assignment operator
    NodeText::operator=(rhs);
    infoText = rhs.infoText;
    blocks = rhs.blocks;
    return *this;
}

void BlockText::release()
{
    for (std::size_t i = 0; i < blocks.size(); i++)
    {
        blocks[i]->release();
    }
    for (std::size_t i = 0; i < blocks.size(); i++)
    {
        delete blocks[i];
    }
    blocks.resize(0);
    blocks.clear();
}

NodeText::Type BlockText::getType() const { return Type::BLOCK; }

bool BlockText::operator==(const NodeText &right) const
{
    if (getType() != right.getType())
    {
        return false;
    }
    else
    {
        bool isEqual =
            infoText == dynamic_cast<const BlockText *>(&right)->infoText;
        for (std::size_t i = 0; i < blocks.size(); i++)
        {
            isEqual =
                isEqual && *const_cast<const NodeText *>(blocks[i]) == right;
        }
        return isEqual;
    }
}

bool BlockText::operator!=(const NodeText &right) const
{
    return !(*this == right);
}

const std::u32string &BlockText::getStr() const { return EmptyStr32; }

std::u32string BlockText::toStr() const { return U""; }

} // namespace segment_d1
