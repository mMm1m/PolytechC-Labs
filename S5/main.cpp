#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include "AVLTree.h"
#include "Processes.h"
#include "PrintMessages.h"
#include "CalculatedExpr.h"

namespace golchanskiy {
  class sumKeys {
    public:
    sumKeys();
    void operator()(const std::pair< int, std::string >&);
    long long getSum() const;
    private:
    long long sum_;
  };
  class sumValues {
    public:
    void operator()(const std::pair< int, std::string >&);
    const std::string& getString() const;
    private:
    std::string str_;
  };

  class sumKeysAndValues {
    public:
    void operator()(const std::pair< int, std::string >&);
    std::string getResult() const;
    private:
    sumKeys sum_;
    sumValues values_;
  };
  using Tree = golchanskiy::AVLTree< int, std::string >;
  Tree getTree(std::istream&);
}

int main(int argc, char** argv)
{
  if (argc != 3) {
    golchanskiy::printNonRightNumberArguments(std::cerr);
    return 1;
  }
  std::fstream in(argv[2]);
  if (!in.good()) {
    golchanskiy::printUnableToRead(std::cerr);
    return 1;
  }
  try {
    auto tree = golchanskiy::getTree(in);
    if (tree.isEmpty()) {
      golchanskiy::printEmpty(std::cout);
      return 0;
    }
    golchanskiy::sumKeysAndValues result;
    std::string traverse = argv[1];
    if (traverse == "ascending")
      result = tree.traverse_lnr(result);
    else if (traverse == "descending")
      result = tree.traverse_rnl(result);
    else if (traverse == "breadth")
      result = tree.traverse_breadth(result);
    else
      throw std::invalid_argument("Unknown way of traverse");
    std::cout << result.getResult() << std::endl;
  }
  catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return 2;
  }
  return 0;
}

namespace golchanskiy {
  sumKeys::sumKeys():
    sum_(0)
  {}

  void sumKeys::operator()(const std::pair< int, std::string >& node)
  {
    sum_ = golchanskiy::add(sum_, node.first);
  }

  long long sumKeys::getSum() const
  {
    return sum_;
  }

  void sumValues::operator()(const std::pair< int, std::string >& node)
  {
    if (!str_.empty())
      str_ += ' ';
    str_ += node.second;
  }

  const std::string& sumValues::getString() const
  {
    return str_;
  }

  void sumKeysAndValues::operator()(const std::pair< int, std::string >& node)
  {
    sum_(node);
    values_(node);
  }

  std::string sumKeysAndValues::getResult() const
  {
    return std::to_string(sum_.getSum()) + ' ' + values_.getString();
  }

  Tree getTree(std::istream& in)
  {
    auto words = golchanskiy::getWords(in, '\n');
    Tree returnable;
    int key = 0;
    std::string value;
    for (auto i = words.cbegin(); i != words.cend(); ++i) {
      key = std::stoi(*i);
      ++i;
      value = *i;
      returnable.insert(key, value);
    }
    return returnable;
  }
}