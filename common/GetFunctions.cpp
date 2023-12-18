#include "GetFunctions.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include "BiDirectionalList.h"

namespace
{
    golchanskiy::BidirectionalList<long long> getList(const golchanskiy::BidirectionalList<std::string>& words)
    {
        golchanskiy::BidirectionalList<long long> returnable;
        for (auto it = (++words.cbegin()); it != words.cend(); ++it)
            returnable.pushBack(std::stoi(*it));
        return returnable;
    }
    golchanskiy::AllLists getLists(std::istream& in)
    {
        if (!in.good())
            throw std::logic_error("Unable to read from the stream");
        golchanskiy::AllLists returnable;
        while (!in.eof())
        {
            auto words = golchanskiy::getWords(in, '\n');
            if (words.isEmpty())
                continue;
            auto list = getList(words);
            returnable.push(words.front(), list);
        }
        return returnable;
    }
    golchanskiy::BidirectionalList<std::string> getWords(std::istream& in, char char_)
    {
        golchanskiy::BidirectionalList<std::string> words;
        char next = in.get();
        while ((next != char_) && (next != char_) && !in.eof())
        {
            std::string elem;
            while (!std::isspace(next) && (next != char_) && !in.eof())
            {
                elem.push_back(next);
                next = in.get();
            }
            words.pushBack(elem);
            next = (next == char_) ? next : in.get();
        }
        return words;
    }
}

