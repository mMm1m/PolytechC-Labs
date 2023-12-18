#include "DataStruct.h"
#include <iostream>
#include "KeyParse.h"
#include "StreamGuard.h"

std::istream& golchanskiy::operator>>(std::istream& in, DataStruct& data)
{
  if (!golchanskiy::istreamSentry(in))
    return in;
  DataStruct input_data;
  in >> Delimeter_IO{'('} >> Delimeter_IO{':'};
  for (int i = 0; i < 3 && in; i++) {
    std::string value;
    in >> value;
    if (value == "key1")
      in >> ULL_IO{input_data.key1};
    else if (value == "key2")
      in >> LL_IO{input_data.key2};
    else if (value == "key3")
      in >> String_IO{input_data.key3};
    else
      in.setstate(std::ios::failbit);
    in >> Delimeter_IO{':'};
  }
  in >> Delimeter_IO{')'};
  if (in)
    data = input_data;
  return in;
}

std::ostream& golchanskiy::operator<<(std::ostream& out, const DataStruct& data)
{
  if (!golchanskiy::ostreamSentry(out))
    return out;
  golchanskiy::StreamGuard StreamGuard(out);
  out << "(:key1 " << golchanskiy::ULL_IO{data.key1};
  out << ":key2 " << golchanskiy::LL_IO{data.key2};
  out << ":key3 " << golchanskiy::String_IO{data.key3} << ":)";
  return out;
}

bool golchanskiy::operator<(const DataStruct& lhs, const DataStruct& rhs)
{
  if (lhs.key1 != rhs.key1)
    return lhs.key1 < rhs.key1;
  else if (lhs.key2 != rhs.key2)
    return lhs.key2 < rhs.key2;
  else
    return lhs.key3.size() < rhs.key3.size();
}
