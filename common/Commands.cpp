#include "Commands.h"
#include <iostream>
#include <stdexcept>
#include "Errors.h"

namespace golchanskiy
{
    std::string MESSAGE = "Unknown dictionary";
    std::ostream& printEmptyCommand(std::ostream& out)
    {
        return out << "<EMPTY>" << std::endl;
    }
    std::ostream& print(std::ostream& out, const std::string& name, const Dicts & dicts)
    {
        auto it = dicts.cfind(name);
        if (it == dicts.cend())
            throw std::invalid_argument(MESSAGE);
        if (it->second.isEmpty())
        {
            golchanskiy::printEmptyCommand(out);
            return out;
        }
        out << name;
        for (auto && data: it->second)
            out << ' ' << data.first << ' ' << data.second;
        out << std::endl;
        return out;
    }
    Dictionary< int, std::string > complement(const std::string& lhs, const std::string& rhs, const Dicts & dicts)
    {
        auto lhsCIterator = dicts.cfind(lhs);
        auto rhsCIterator = dicts.cfind(rhs);
        if ((lhsCIterator == dicts.cend()) || (rhsCIterator == dicts.cend()))
            throw std::invalid_argument(MESSAGE);
        if (lhsCIterator->second.isEmpty() || rhsCIterator->second.isEmpty())
            return lhsCIterator->second;
        auto returnable = lhsCIterator->second;
        auto rhsIterator = rhsCIterator->second.cbegin();
        auto retIterator = returnable.begin();
        std::less< int > cmp;
        while ((retIterator != returnable.end()) && (rhsIterator != rhsCIterator->second.cend()))
        {
            if (cmp(retIterator->first, rhsIterator->first))
                while ((retIterator != returnable.end()) && cmp(retIterator->first, rhsIterator->first))
                {
                    ++retIterator;
                }
            else if (cmp(rhsIterator->first, retIterator->first))
                while ((rhsIterator != rhsCIterator->second.cend()) && cmp(rhsIterator->first, retIterator->first))
                {
                    ++rhsIterator;
                }
            if ((retIterator == returnable.end()) || (rhsIterator == rhsCIterator->second.cend()))
                return returnable;
            if (!cmp(retIterator->first, rhsIterator->first) && !cmp(rhsIterator->first, retIterator->first))
            {
                ++retIterator;
                returnable.pop(rhsIterator->first);
                ++rhsIterator;
            }
            else
            {
                ++retIterator;
                ++rhsIterator;
            }
        }
        return returnable;
    }
    Dictionary< int, std::string > intersect(const std::string& lhsName, const std::string& rhsName, const Dicts & dicts)
    {
        auto lhsCIt = dicts.cfind(lhsName);
        auto rhsCIt = dicts.cfind(rhsName);
        if ((lhsCIt == dicts.cend()) || (rhsCIt == dicts.cend()))
            throw std::invalid_argument(MESSAGE);
        if ((lhsCIt->second.isEmpty()) || (rhsCIt->second.isEmpty()))
            return Dictionary< int, std::string >();
        auto returnable = Dictionary< int, std::string >();
        auto lhsIterator = lhsCIt->second.cbegin();
        auto rhsIterator = rhsCIt->second.cbegin();
        std::less< int > cmp;
        while ((lhsIterator != lhsCIt->second.cend()) && (rhsIterator != rhsCIt->second.cend()))
        {
            if (cmp(lhsIterator->first, rhsIterator->first))
                while ((lhsIterator != lhsCIt->second.cend()) && cmp(lhsIterator->first, rhsIterator->first))
                {
                    ++lhsIterator;
                }
            else if (cmp(rhsIterator->first, lhsIterator->first))
                while ((rhsIterator != rhsCIt->second.cend()) && cmp(rhsIterator->first, lhsIterator->first))
                {
                    ++rhsIterator;
                }
            if ((lhsIterator == lhsCIt->second.cend()) || (rhsIterator == rhsCIt->second.cend()))
                return returnable;
            if (!cmp(lhsIterator->first, rhsIterator->first) && !cmp(rhsIterator->first, lhsIterator->first))
                returnable.push(lhsIterator->first, lhsIterator->second);
            ++lhsIterator;
            ++rhsIterator;
        }
        return returnable;
    }
    Dictionary< int, std::string > unite(const std::string& lhs, const std::string& rhs, const Dicts & dicts)
    {
        auto lhsCIterator = dicts.cfind(lhs);
        auto rhsCIterator = dicts.cfind(rhs);
        if ((lhsCIterator == dicts.cend()) || (rhsCIterator == dicts.cend()))
            throw std::invalid_argument(MESSAGE);
        if (lhsCIterator->second.isEmpty())
            return rhsCIterator->second;
        if (rhsCIterator->second.isEmpty())
            return lhsCIterator->second;
        auto returnable = lhsCIterator->second;
        auto rhsIt = rhsCIterator->second.cbegin();
        while (rhsIt != rhsCIterator->second.cend())
        {
            if (returnable.cfind(rhsIt->first) == returnable.cend())
                returnable.push(rhsIt->first, rhsIt->second);
            ++rhsIt;
        }
        return returnable;
    }
}

