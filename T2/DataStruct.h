#ifndef T2_DATASTRUCT_H
#define T2_DATASTRUCT_H

#include <utility>
#include <string>

namespace golchanskiy
{
  struct DataStruct
  {
    unsigned long long key1;
    long long key2;
    std::string key3;
  };

  std::ostream& operator<<(std::ostream&, const DataStruct&);
  std::istream& operator>>(std::istream&, DataStruct&);
  bool operator<(const DataStruct&, const DataStruct&);
}

#endif
