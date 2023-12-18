#ifndef S4_COMMANDSS2_H
#define S4_COMMANDSS2_H

#include <string>
#include <iostream>
#include <stdexcept>
#include "PrintMessages.h"

namespace golchanskiy {
  const std::string MESSAGE = "Unknown dictionary";

  template< typename AllDicts >
  std::ostream& print(std::ostream& out, const std::string& name, const AllDicts& dicts)
  {
    auto it = dicts.cfind(name);
    if (it == dicts.cend())
      throw std::invalid_argument(MESSAGE);
    if (it->second.isEmpty()) {
      golchanskiy::printEmpty(out);
      return out;
    }
    out << name;
    for (auto&& data: it->second)
      out << ' ' << data.first << ' ' << data.second;
    out << std::endl;
    return out;
  }

  template< typename Dict, typename AllDicts >
  Dict complement(const std::string& Name_, const std::string& Name, const AllDicts& dicts)
  {
    auto leftConstIt = dicts.cfind(Name_);
    auto rightConstIt = dicts.cfind(Name);
    if ((leftConstIt == dicts.cend()) || (rightConstIt == dicts.cend()))
      throw std::invalid_argument(MESSAGE);
    if (leftConstIt->second.isEmpty() || rightConstIt->second.isEmpty())
      return leftConstIt->second;
    auto returnable = leftConstIt->second;
    auto rightIt = rightConstIt->second.cbegin();
    auto returnableIt = returnable.begin();
    std::less< int > cmp;
    while ((returnableIt != returnable.end()) && (rightIt != rightConstIt->second.cend())) {
      if (cmp(returnableIt->first, rightIt->first)) {
        while ((returnableIt != returnable.end()) && cmp(returnableIt->first, rightIt->first)) {
          ++returnableIt;
        }
      } else if (cmp(rightIt->first, returnableIt->first)) {
        while ((rightIt != rightConstIt->second.cend()) && cmp(rightIt->first, returnableIt->first)) {
          ++rightIt;
        }
      }
      if ((returnableIt == returnable.end()) || (returnableIt == rightConstIt->second.cend()))
        return returnable;
      if (!cmp(returnableIt->first, rightIt->first) && !cmp(rightIt->first, returnableIt->first)) {
        ++returnableIt;
        returnable.pop(rightIt->first);
        ++rightIt;
      } else {
        ++returnableIt;
        ++rightIt;
      }
    }
    return returnable;
  }

  template< typename Dict, typename AllDicts >
  Dict intersect(const std::string& lhsName, const std::string& rhsName, const AllDicts& dicts)
  {
    auto leftConstIt = dicts.cfind(lhsName);
    auto rightConstIt = dicts.cfind(rhsName);
    if ((leftConstIt == dicts.cend()) || (rightConstIt == dicts.cend()))
      throw std::invalid_argument(MESSAGE);
    if ((leftConstIt->second.isEmpty()) || (rightConstIt->second.isEmpty()))
      return Dict();
    auto returnable = Dict();
    auto leftIt = leftConstIt->second.cbegin();
    auto rightIt = rightConstIt->second.cbegin();
    std::less< int > cmp;
    while ((leftIt != leftConstIt->second.cend()) && (rightIt != rightConstIt->second.cend())) {
      if (cmp(leftIt->first, rightIt->first)) {
        while ((leftIt != leftConstIt->second.cend()) && cmp(leftIt->first, rightIt->first)) {
          ++leftIt;
        }
      } else if (cmp(rightIt->first, leftIt->first)) {
        while ((rightIt != rightConstIt->second.cend()) && cmp(rightIt->first, leftIt->first)) {
          ++rightIt;
        }
      }
      if ((leftIt == leftConstIt->second.cend()) || (rightIt == rightConstIt->second.cend()))
        return returnable;
      if (!cmp(leftIt->first, rightIt->first) && !cmp(rightIt->first, leftIt->first))
        returnable.push(leftIt->first, leftIt->second);
      ++leftIt;
      ++rightIt;
    }
    return returnable;
  }

  template< typename Dict, typename AllDicts >
  Dict unite(const std::string& lhsName, const std::string& rhsName, const AllDicts& dicts)
  {
    auto leftConstIt = dicts.cfind(lhsName);
    auto rightConstIt = dicts.cfind(rhsName);
    if ((leftConstIt == dicts.cend()) || (rightConstIt == dicts.cend()))
      throw std::invalid_argument(MESSAGE);
    if (leftConstIt->second.isEmpty())
      return rightConstIt->second;
    if (rightConstIt->second.isEmpty())
      return leftConstIt->second;
    auto returnable = leftConstIt->second;
    auto rightIt = rightConstIt->second.cbegin();
    while (rightIt != rightConstIt->second.cend()) {
      if (returnable.cfind(rightIt->first) == returnable.cend())
        returnable.push(rightIt->first, rightIt->second);
      ++rightIt;
    }
    return returnable;
  }
}

#endif
