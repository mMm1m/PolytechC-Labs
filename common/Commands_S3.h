#ifndef COMMANDS_H
#define COMMANDS_H
#include <iosfwd>
#include <string>
#include "BiDirectionalList.h"
#include "Dictionary.h"

namespace golchanskiy
{
    using ll = long long;
    using str = std::string;
    using AllLists = Dictionary< str , BidirectionalList< ll > >;
    using List = BidirectionalList< ll >;
    using Args = BidirectionalList< str >;
    std::ostream& print(std::ostream&, const std::string&, const AllLists&);
    void replace(const str&, ll, ll, AllLists&);
    void replace(const str&, ll, const str&, AllLists&);
    void remove(const str&, ll, AllLists&);
    void remove(const str&, const str&, AllLists&);
    List concat(const Args&, const AllLists&);
    bool equal(const Args&, const AllLists&);
}

#endif

