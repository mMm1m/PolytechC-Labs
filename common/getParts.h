#ifndef GET_PARTS_H
#define GET_PARTS_H
#include <string>
#include <iosfwd>
#include "ForwardList.h"
#include "Commands.h"

namespace golchanskiy
{
    Dicts getDicts(std::istream&);
    ForwardList< std::string > getWords(std::istream&, char);
}

#endif

