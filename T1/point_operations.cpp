#include "point_operations.h"
#include <iostream>

namespace {
  double getPartOfPoint(std::string& str)
  {
    size_t pos = str.find(' ');
    double crdt = std::stod(str.substr(0, pos));
    pos = (pos == std::string::npos) ? std::string::npos : pos + 1;
    str.erase(0, pos);
    return crdt;
  }
}

void golchanskiy::movePoint(point_t& point, double x, double y)
{
  point.x += x;
  point.y += y;
}

golchanskiy::point_t golchanskiy::moveRelatively(const golchanskiy::point_t& center, const golchanskiy::point_t& point, double k)
{
  double x = center.x + k * (point.x - center.x);
  double y = center.y + k * (point.y - center.y);
  return golchanskiy::point_t{x, y};
}

bool golchanskiy::operator==(const golchanskiy::point_t& lhs, const golchanskiy::point_t& rhs)
{
  return lhs.x == rhs.x && lhs.y == rhs.y;
}

double golchanskiy::getPartOfShoelaceScheme(const golchanskiy::point_t& p1, const golchanskiy::point_t& p2)
{
  return (p1.x + p2.x) * (p1.y - p2.y);
}

std::ostream& golchanskiy::operator<<(std::ostream& os, const golchanskiy::point_t& point)
{
  os << point.x << " " << point.y;
  return os;
}

golchanskiy::point_t golchanskiy::getPointFromString(std::string& line)
{
  double x = getPartOfPoint(line);
  double y = getPartOfPoint(line);
  return point_t{x, y};
}

std::string golchanskiy::getFirstWord(std::string& data)
{
  size_t first_space = data.find_first_of(' ');
  std::string result = data.substr(0, first_space);
  size_t erase_index = (first_space == std::string::npos) ? first_space : first_space + 1;
  data.erase(0, erase_index);
  return result;
}

golchanskiy::point_t golchanskiy::readPoint(std::string& data)
{
  double x = std::stod(golchanskiy::getFirstWord(data));
  double y = std::stod(golchanskiy::getFirstWord(data));
  return golchanskiy::point_t { x, y };
}

