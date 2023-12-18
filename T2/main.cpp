#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include "DataStruct.h"

int main()
{
  using istream_iterator = std::istream_iterator< golchanskiy::DataStruct >;
  using ostream_iter = std::ostream_iterator< golchanskiy::DataStruct >;
  std::vector< golchanskiy::DataStruct > vector_data;
  while (!std::cin.eof()) {
    std::cin.clear();
    std::copy(istream_iterator(std::cin), istream_iterator(), std::back_inserter(vector_data));
  }
  std::sort(vector_data.begin(), vector_data.end());
  std::copy(vector_data.begin(), vector_data.end(), ostream_iter(std::cout, "\n"));
  return 0;
}
