#include "PrintMessages.h"
#include <iostream>

namespace golchanskiy {
  std::ostream& printEmpty(std::ostream& out)
  {
    out << "<EMPTY>" << std::endl;
    return out;
  }

  std::ostream& printNoFile(std::ostream& out)
  {
    out << "No file to read" << std::endl;
    return out;
  }

  std::ostream& printUnableToRead(std::ostream& out)
  {
    out << "Unable to read the file" << std::endl;
    return out;
  }

  std::ostream& printInvalidCommand(std::ostream& out)
  {
    out << "<INVALID COMMAND>" << std::endl;
    return out;
  }

  std::ostream& printNonRightNumberArguments(std::ostream& out)
  {
    out << "<Non right number of arguments>";
    return out;
  }
}
