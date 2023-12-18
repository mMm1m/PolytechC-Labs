#ifndef S4_PRINTMESSAGES_H
#define S4_PRINTMESSAGES_H

#include <iosfwd>

namespace golchanskiy {
  std::ostream& printEmpty(std::ostream&);

  std::ostream& printNoFile(std::ostream&);

  std::ostream& printUnableToRead(std::ostream&);

  std::ostream& printInvalidCommand(std::ostream&);

  std::ostream& printNonRightNumberArguments(std::ostream&);
}

#endif
