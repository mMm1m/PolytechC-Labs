#include <iostream>
#include <fstream>
#include <string>
#include "TreeDictionary.h"
#include "CommandsS2.h"
#include "Processes.h"

int main(int argc, char** argv)
{
  using Dict = golchanskiy::TreeDict< int, std::string >;
  using AllDicts = golchanskiy::TreeDict< std::string, Dict >;
  if (argc == 1) {
    golchanskiy::printNoFile(std::cerr);
    return 1;
  }
  std::ifstream fin(argv[1]);
  if (!fin.good()) {
    golchanskiy::printUnableToRead(std::cerr);
    return 1;
  }
  try {
    auto data = golchanskiy::getDictsFromStream< Dict, AllDicts >(fin);
    fin.close();
    while (!std::cin.eof()) {
      try {
        golchanskiy::processCommand< Dict, AllDicts >(std::cin, std::cout, data);
      }
      catch (const std::invalid_argument&) {
        golchanskiy::printInvalidCommand(std::cout);
      }
    }
  }
  catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return 2;
  }
  return 0;
}
