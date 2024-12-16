#include "text/ChainText.hpp"
#include "func.hpp"
#include <iostream>

namespace segment_d1
{

ChainText::ChainText() : nodes({}), leafs({}), blocks({}), blocksClosing({})
{
    // ctor
}

ChainText::~ChainText()
{
    // dtor
}

ChainText::ChainText(const ChainText &other)
    : nodes(other.nodes), leafs(other.leafs), blocks(other.blocks),
      blocksClosing(other.blocksClosing)
{
    // copy ctor
}

ChainText::ChainText(const std::u32string &str)
    : nodes({}), leafs({}), blocks({}), blocksClosing({})
{
    if (str.empty())
    {
        return;
    }
    if (parseString(str, false))
    {
        parseString(str, true);
    }
    else
    {
        std::string str8 = "";
        Func::utf32ToUtf8(str.begin(), str.end(), std::back_inserter(str8));
        std::cout << "Error during the parsing of the string : " << str8
                  << " to make a ChainText." << std::endl;
        nodes = {};
        leafs = {};
        blocks = {};
        blocksClosing = {};
    }
}

ChainText::ChainText(const std::string &str)
    : nodes({}), leafs({}), blocks({}), blocksClosing({})
{
    if (str.empty())
    {
        return;
    }
    std::u32string u32str = U"";
    // sf::Utf8::toUtf32(str.begin(), str.end(), std::back_inserter(u32str));
    Func::utf8ToUtf32(str.begin(), str.end(), std::back_inserter(u32str));
    if (parseString(u32str, false))
    {
        parseString(u32str, true);
    }
    else
    {
        std::cout << "Error during the parsing of the string : " << str
                  << " to make a ChainText." << std::endl;
        nodes = {};
        leafs = {};
        blocks = {};
        blocksClosing = {};
    }
}
/*
ChainText::ChainText(const sf::String& str) : ChainText(str.toUtf32())
{

}
*/
ChainText &ChainText::operator=(const ChainText &rhs)
{
    if (this == &rhs)
    {
        return *this; // handle self assignment
    }
    // assignment operator
    nodes = rhs.nodes;
    leafs = rhs.leafs;
    blocks = rhs.blocks;
    blocksClosing = rhs.blocksClosing;
    return *this;
}

std::size_t ChainText::getSize() const { return nodes.size(); }

bool ChainText::isEmpty() const
{
    bool noText = true;
    for (std::size_t i = 0; i < nodes.size(); i++)
    {
        if (nodes[i]->getType() == NodeText::Type::LEAF)
        {
            noText = noText && dynamic_cast<LeafText *>(nodes[i])->isEmpty();
        }
    }
    return noText;
}

const NodeText *ChainText::operator[](std::size_t i) const { return nodes[i]; }

bool ChainText::operator==(const ChainText &right) const
{
    if (nodes.size() != right.nodes.size())
    {
        return false;
    }
    for (std::size_t i = 0; i < nodes.size(); i++)
    {
        if (*nodes[i] != *right.nodes[i])
        {
            return false;
        }
    }
    return true;
}

bool ChainText::operator!=(const ChainText &right) const
{
    return !(*this == right);
}

uint64_t ChainText::getNbChar() const
{
    uint64_t res = 0;
    for (std::size_t i = 0; i < nodes.size(); i++)
    {
        if (nodes[i]->getType() == NodeText::Type::LEAF)
        {
            res += dynamic_cast<LeafText *>(nodes[i])->getSize();
        }
    }
    return res;
}

uint64_t ChainText::getNbChar(uint64_t i) const
{
    if (nodes[i]->getType() != NodeText::Type::LEAF)
    {
        return 0;
    }
    else
    {
        return dynamic_cast<LeafText *>(nodes[i])->getSize();
    }
}

std::u32string ChainText::getStr() const
{
    std::u32string res = U"";
    for (std::size_t i = 0; i < nodes.size(); i++)
    {
        bool ty = nodes[i]->getType() == NodeText::Type::LEAF;
        if (ty)
        {
            res += dynamic_cast<LeafText *>(nodes[i])->getStr();
        }
    }
    return res;
}

std::u32string ChainText::toStr() const
{
    std::u32string res = U"";
    for (std::size_t i = 0; i < nodes.size(); i++)
    {
        res += nodes[i]->toStr();
    }
    return res;
}

bool ChainText::parseString(const std::u32string &str, bool setNodes)
{
    int countSlash = 0;
    // uint64_t indexInit = 0;
    uint64_t indexFina = 0;
    uint64_t sizeLeaf = 0;
    uint64_t sizeBlock = 0;
    uint64_t sizeClosingBlock = 0;
    std::u32string currLeaf = U"";
    for (uint64_t i = 0; i < str.size(); i++)
    {
        if (str[i] == U'<' && countSlash % 2 == 0)
        {
            if (/*indexInit != i*/ !currLeaf.empty())
            {
                if (!setNodes)
                {
                    sizeLeaf++;
                }
                else
                {
                    // leafs.emplace_back(str.substr(indexInit, i - indexInit));
                    leafs.emplace_back(currLeaf);
                    nodes.emplace_back(&leafs.back());
                }
            }
            indexFina = str.find(U'>', i);
            if (indexFina == std::string::npos)
            {
                return false;
            }
            if (str.substr(i, indexFina - i + 1) == U"</>")
            {
                if (!setNodes)
                {
                    sizeClosingBlock++;
                }
                else
                {
                    blocksClosing.emplace_back(/*BlockClosingText()*/);
                    nodes.emplace_back(&blocksClosing.back());
                }
            }
            else
            {
                if (!setNodes)
                {
                    sizeBlock++;
                }
                else
                {
                    blocks.emplace_back(str.substr(i + 1, indexFina - (i + 1)));
                    nodes.emplace_back(&blocks.back());
                }
            }
            // indexInit = indexFina + 1;
            i = indexFina;
            countSlash = 0;
            currLeaf = U"";
        }
        else if (str[i] == U'\\')
        {
            countSlash++;
            if (countSlash % 2 == 0)
            {
                currLeaf += U'\\';
            }
        }
        else
        {
            countSlash = 0;
            currLeaf += str[i];
        }
        if (sizeClosingBlock > sizeBlock)
        {
            return false;
        }
    }
    if (/*indexInit != str.size()*/ !currLeaf.empty())
    {
        if (!setNodes)
        {
            sizeLeaf++;
        }
        else
        {
            // leafs.emplace_back(str.substr(indexInit, str.size() -
            // indexInit));
            leafs.emplace_back(currLeaf);
            nodes.emplace_back(&leafs.back());
        }
    }
    if (!setNodes)
    {
        leafs.reserve(sizeLeaf);
        blocks.reserve(sizeBlock);
        blocksClosing.reserve(sizeClosingBlock);
        nodes.reserve(sizeLeaf + sizeBlock + sizeClosingBlock);
    }
    return true;
}

} // namespace segment_d1
