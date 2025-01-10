#include "text/ChainText.hpp"
#include "Func.hpp"
#include "Logger.hpp"
#include <iostream>

namespace segment_d1
{

ChainText::ChainText() : nodes({}), leafs({}), blocks({}), blocksClosing({})
{
    // ctor
}

ChainText::~ChainText() = default;

ChainText::ChainText(const ChainText &other) = default;

ChainText::ChainText(const std::u32string &str)
    : nodes({}), leafs({}), blocks({}), blocksClosing({})
{
    if (!str.empty())
    {
        if (parseString(str, false))
        {
            if (!parseString(str, true))
            {
                Logger().info("Error parsing");
            }
        }
        else
        {
            std::string str8 = "";
            Func::utf32ToUtf8(str.begin(), str.end(), std::back_inserter(str8));
            Logger().info("Error during the parsing of the string : " + str8 +
                          " to make a ChainText.");
            nodes = {};
            leafs = {};
            blocks = {};
            blocksClosing = {};
        }
    }
}

ChainText::ChainText(const std::string &str)
    : nodes({}), leafs({}), blocks({}), blocksClosing({})
{
    if (!str.empty())
    {
        std::u32string u32str = U"";
        Func::utf8ToUtf32(str.begin(), str.end(), std::back_inserter(u32str));
        if (parseString(u32str, false))
        {
            if (!parseString(u32str, true))
            {
                Logger().info("Error parsing");
            }
        }
        else
        {
            Logger().info("Error during the parsing of the string : " + str +
                          " to make a ChainText.");
            nodes = {};
            leafs = {};
            blocks = {};
            blocksClosing = {};
        }
    }
}

ChainText &ChainText::operator=(const ChainText &rhs) = default;

std::size_t ChainText::getSize() const { return nodes.size(); }

bool ChainText::isEmpty() const
{
    bool noText = true;
    const std::size_t nodesSize = nodes.size();
    for (std::size_t i = 0; i < nodesSize; ++i)
    {
        if (nodes[i]->getType() == NodeText::Type::LEAF)
        {
            noText = noText && dynamic_cast<LeafText *>(nodes[i])->isEmpty();
        }
    }
    return noText;
}

const NodeText *ChainText::operator[](const std::size_t i) const
{
    return nodes[i];
}

uint64_t ChainText::getNbChar() const
{
    uint64_t res = 0;
    const std::size_t nodesSize = nodes.size();
    for (std::size_t i = 0; i < nodesSize; ++i)
    {
        if (nodes[i]->getType() == NodeText::Type::LEAF)
        {
            res += dynamic_cast<LeafText *>(nodes[i])->getSize();
        }
    }
    return res;
}

uint64_t ChainText::getNbChar(const uint64_t i) const
{
    uint64_t res = 0;
    if (nodes[i]->getType() == NodeText::Type::LEAF)
    {
        res = dynamic_cast<LeafText *>(nodes[i])->getSize();
    }
    return res;
}

std::u32string ChainText::getStr() const
{
    std::u32string res = U"";
    const std::size_t nodesSize = nodes.size();
    for (std::size_t i = 0; i < nodesSize; ++i)
    {
        if (nodes[i]->getType() == NodeText::Type::LEAF)
        {
            res += dynamic_cast<LeafText *>(nodes[i])->getStr();
        }
    }
    return res;
}

std::u32string ChainText::toStr() const
{
    std::u32string res = U"";
    const std::size_t nodesSize = nodes.size();
    for (std::size_t i = 0; i < nodesSize; ++i)
    {
        res += nodes[i]->toStr();
    }
    return res;
}

bool ChainText::parseString(const std::u32string &str, const bool setNodes)
{
    int32_t countSlash = 0;
    uint64_t indexFina = 0;
    uint64_t sizeLeaf = 0;
    uint64_t sizeBlock = 0;
    uint64_t sizeClosingBlock = 0;
    std::u32string currLeaf = U"";
    const std::size_t strSize = str.size();
    for (std::size_t i = 0; i < strSize; ++i)
    {
        if ((U'<' == str[i]) && (0 == (countSlash % 2)))
        {
            if (/*indexInit != i*/ !currLeaf.empty())
            {
                if (!setNodes)
                {
                    ++sizeLeaf;
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
            if (str.substr(i, (indexFina + 1) - i) == U"</>")
            {
                if (!setNodes)
                {
                    ++sizeClosingBlock;
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
                    ++sizeBlock;
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
        else if (U'\\' == str[i])
        {
            ++countSlash;
            if (0 == (countSlash % 2))
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
            ++sizeLeaf;
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
