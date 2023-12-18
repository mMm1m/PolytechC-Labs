#ifndef COMMANDS_H
#define COMMANDS_H
#include <string>
#include <iosfwd>
#include "Dictionary.h"
#include "ForwardList.h"

namespace golchanskiy
{
    using Dicts = Dictionary< std::string, Dictionary< int, std::string > >;
    std::ostream& print(std::ostream&, const std::string&, const Dicts &);
    Dictionary< int, std::string > complement(const std::string&, const std::string&, const Dicts &);
    Dictionary< int, std::string > intersect(const std::string&, const std::string&, const Dicts &);
    Dictionary< int, std::string > unite(const std::string&, const std::string&, const Dicts &);
}

#endif

