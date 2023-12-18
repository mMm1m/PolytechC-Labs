#ifndef POINT_OPERATIONS_HPP
#define POINT_OPERATIONS_HPP

#include <cmath>
#include <iosfwd>
#include <memory>
#include "base_types.h"

namespace golchanskiy {
  void movePoint(point_t& point, double x, double y);
  point_t moveRelatively(const point_t& p, const point_t& p1, double k);
  double getPartOfShoelaceScheme(const point_t& p1, const point_t& p2);
  point_t getPointFromString(std::string& line);
  bool operator==(const point_t& lhs, const point_t& rhs);
  std::ostream& operator<<(std::ostream& os, const point_t& point);
  std::string getFirstWord(std::string&);
  golchanskiy::point_t readPoint(std::string&);

}
#endif

