#include "getParts.h"
#include <iostream>
#include <istream>
#include <string>
#include <stdexcept>
#include "Dictionary.h"
#include "ForwardList.h"
#include "Commands.h"

namespace golchanskiy
{
    Dictionary< int, std::string > getDict(const ForwardList< std::string >& in)
    {
        Dictionary< int, std::string > returnable;
        int key = 0;
        std::string string;
        for (auto i = (++in.cbegin()); i != in.cend(); ++i)
        {
            if (std::isdigit(i->front()))
            {
                key = std::stoi(*i);
                continue;
            }
            string = *i;
            returnable.push(key, string);
        }
        return returnable;
    }
    Dicts getDicts(std::istream& in)
    {
        if (!in.good())
            throw std::logic_error("Unable to read!\n");
        Dicts dicts;
        while (!in.eof())
        {
            auto words = getWords(in, '\n');
            if (words.isEmpty())
                continue;
            Dictionary< int, std::string > elem = getDict(words);
            dicts.push(words.front(), elem);
        }
        return dicts;
    }
    ForwardList< std::string > getWords(std::istream& in, char char_)
    {
        auto words = ForwardList< std::string >();
        char next = in.get();
        while ((next != char_) && !in.eof())
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

