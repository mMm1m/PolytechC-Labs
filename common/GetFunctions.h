#ifndef STREAM_PROCESSING_H
#define STREAM_PROCESSING_H
#include <iosfwd>
#include <string>
#include "BiDirectionalList.h"
#include "Dictionary.h"
#include "Commands_S3.h"

namespace golchanskiy
{
    Dictionary<std::string, BidirectionalList<long long>> getLists(std::istream&);
    BidirectionalList<std::string> getWords(std::istream&, char delim);
}

#endif

