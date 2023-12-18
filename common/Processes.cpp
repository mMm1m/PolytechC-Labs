#include "Processes.h"
#include <string>
#include "S2/ForwardList.h"
#include "TreeNode.h"

namespace golchanskiy {
  ForwardList< std::string > getWords(std::istream& in, char chars_)
  {
    auto words = ForwardList< std::string >();
    char next = in.get();
    while ((next != chars_) && !in.eof()) {
      std::string element_;
      while (!std::isspace(next) && (next != chars_) && !in.eof()) {
        element_.push_back(next);
        next = in.get();
      }
      words.pushBack(element_);
      next = (next == chars_) ? next : in.get();
    }
    return words;
  }

  template< typename Dict >
  Dict getDictionary(const ForwardList< std::string >& input)
  {
    Dict dict;
    int key = 0;
    std::string value;
    for (auto i = (++input.cbegin()); i != input.cend(); ++i) {
      if (std::isdigit(i->front()) || (i->front() == '-')) {
        key = std::stoi(*i);
        continue;
      }
      value = *i;
      dict.push(key, value);
    }
    return dict;
  }

  template< typename Dict, typename AllDicts >
  AllDicts getDictsFromStream(std::istream& in)
  {
    if (!in.good())
      throw std::logic_error("Unable to read!\n");
    AllDicts dicts;
    while (!in.eof()) {
      auto words = golchanskiy::getWords(in, '\n');
      if (words.isEmpty())
        continue;
      auto element_ = golchanskiy::getDictionary< Dict >(words);
      dicts.push(words.front(), element_);
    }
    return dicts;
  }

  template< typename Dict, typename AllDicts >
  void processCommand(std::istream& in, std::ostream& out, AllDicts& data)
  {
    auto words = golchanskiy::getWords(in, '\n');
    if (words.isEmpty())
      return;
    if (words.getSize() < 2)
      throw std::invalid_argument("Not enough args!\n");
    auto wordsIt = words.cbegin();
    std::string command = *(wordsIt++);
    std::string name = *(wordsIt++);
    if (command == "print") {
      golchanskiy::print< AllDicts >(out, name, data);
      return;
    }
    if (words.getSize() < 4)
      throw std::invalid_argument("Not enough args!\n");
    std::string left_ = *(wordsIt++);
    std::string right_ = *wordsIt;
    if (command == "complement")
      data.push(name, golchanskiy::complement< Dict, AllDicts >(left_, right_, data));
    else if (command == "intersect")
      data.push(name, golchanskiy::intersect< Dict, AllDicts >(left_, right_, data));
    else if (command == "union")
      data.push(name, golchanskiy::unite< Dict, AllDicts >(left_, right_, data));
    else
      throw std::invalid_argument("Unknown command");
  }
}
