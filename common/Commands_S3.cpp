#include "Commands_S3.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include "BiDirectionalList.h"

namespace golchanskiy
{
    std::ostream& print(std::ostream& out, const std::string& name, const AllLists& lists)
    {
        auto dict = lists.cfind(name);
        if (dict == lists.cend())
            throw std::invalid_argument("Unknown list");
        if (dict->second.isEmpty())
        {
            out << "<EMPTY>" << std::endl;
            return out;
        }
        auto listIt = dict->second.cbegin();
        out << name << ' ';
        while (listIt != dict->second.cend())
        {
            out << *listIt;
            ++listIt;
            if (listIt != dict->second.cend())
                out << ' ';
        }
        out << std::endl;
        return out;
    }
    void replace(const std::string& name, long long first, long long second, AllLists& lists)
    {
        auto dictIt = lists.find(name);
        if (dictIt == lists.end())
            throw std::invalid_argument("Unknown list");
        auto listIt = dictIt->second.begin();
        while (listIt != dictIt->second.end())
        {
            if (*listIt == first)
                *listIt = second;
            ++listIt;
        }
    }
    void replace(const std::string& name, long long first, const std::string& second, AllLists& lists)
    {
        auto thisIt = lists.find(name);
        auto secondIt = lists.cfind(second);
        if ((thisIt == lists.end()) || (secondIt == lists.cend()))
            throw std::invalid_argument("Unknown list");
        auto listIt = thisIt->second.begin();
        auto secondListIt = secondIt->second.cbegin();
        while (listIt != thisIt->second.end())
        {
            if (*listIt == first)
            {
                thisIt->second.erase(listIt);
                while (secondListIt != secondIt->second.cend())
                {
                    thisIt->second.insert(listIt, *secondListIt);
                    ++secondListIt;
                }
                secondListIt = secondIt->second.cbegin();
                listIt = (listIt == thisIt->second.end()) ? listIt : --listIt;
            }
            if (listIt == thisIt->second.end())
                break;
            ++listIt;
        }
    }
    void remove(const std::string& name, long long elem, AllLists& lists)
    {
        auto dictIt = lists.find(name);
        if (dictIt == lists.end())
            throw std::invalid_argument("Unknown list");
        auto listIt = dictIt->second.begin();
        while (listIt != dictIt->second.end())
        {
            if (*listIt == elem)
                dictIt->second.erase(listIt);
            else
                ++listIt;
        }
    }
    void remove(const std::string& name, const std::string& src, AllLists& lists)
    {
        auto srcIt = lists.find(src);
        if ((lists.cfind(name) == lists.cend()) || (srcIt == lists.end()))
            throw std::invalid_argument("Unknown list");
        auto srcListIt = srcIt->second.begin();
        while (srcListIt != srcIt->second.end())
        {
            remove(name, *srcListIt, lists);
            ++srcListIt;
        }
    }
    List concat(const Args& args, const AllLists& lists)
    {
        if (args.isEmpty())
            return List();
        auto argsIt = args.cbegin();
        List returnable;
        while (argsIt != args.cend())
        {
            auto srcIt = lists.cfind(*argsIt);
            if (srcIt == lists.cend())
                throw std::invalid_argument("Unknown list");
            auto argListIt = srcIt->second.cbegin();
            while (argListIt != srcIt->second.cend())
            {
                returnable.pushBack(*argListIt);
                ++argListIt;
            }
            ++argsIt;
        }
        return returnable;
    }
    bool equal(const Args& args, const AllLists& lists)
    {
        if (args.isEmpty())
            throw std::invalid_argument("No args");
        auto argsIt = args.cbegin();
        while (argsIt != args.cend())
        {
            auto lhsIt = lists.cfind(*argsIt);
            ++argsIt;
            if (argsIt == args.cend())
                break;
            auto rhsIt = lists.cfind(*argsIt);
            if ((lhsIt == lists.cend()) || (rhsIt == lists.cend()))
                throw std::invalid_argument("Unknown list");
            if (lhsIt->second != rhsIt->second)
                return false;
        }
        return true;
    }
}

