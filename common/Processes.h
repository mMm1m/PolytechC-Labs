#ifndef STREAM_PROCESSING_S2_H
#define STREAM_PROCESSING_S2_H

#include <string>
#include <iosfwd>
#include <functional>
#include "S2/ForwardList.h"
#include "CommandsS2.h"

namespace golchanskiy {
  ForwardList< std::string > getWords(std::istream&, char);

  template< typename Dict >
  Dict getDictionary(const ForwardList< std::string >& input);

  template< typename Dict, typename AllDicts >
  AllDicts getDictsFromStream(std::istream& in);

  template< typename Dict, typename AllDicts >
  void processCommand(std::istream& in, std::ostream& out, AllDicts& data);
}

#endif
