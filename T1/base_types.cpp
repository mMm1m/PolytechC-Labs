#include "base_types.h"
#include "point_operations.h"

#include <cmath>

double golchanskiy::getDistance(const point_t& src1, const point_t& src2)
{
  return std::sqrt(std::pow(src1.x - src2.x, 2) + std::pow(src1.y - src2.y, 2));
}

golchanskiy::point_t golchanskiy::scalePoint(const point_t& point, const point_t& center, const double k)
{
  return point_t{k * (point.x - center.x) + center.x, k * (point.y - center.y) + center.y};
}

golchanskiy::rectangle_t golchanskiy::getRect(const point_t& p1, const point_t& p2)
{
  double width = std::abs(p1.x - p2.x);
  double height = std::abs(p1.y - p2.y);
  return rectangle_t{width, height, point_t{(p1.x + p2.x) / 2, (p1.y + p2.y) / 2}};
}

bool golchanskiy::isTriangle(const double a, const double b, const double c)
{
  return (a < b + c) && (c < a + b) && (b < a + c) && (a > 0) && (b > 0) && (c > 0);
}

golchanskiy::point_t golchanskiy::operator+(const point_t& a, const point_t& b)
{
  return point_t{a.x + b.x, a.y + b.y};
}

golchanskiy::point_t& golchanskiy::operator+=(point_t& a, const point_t& b)
{
  return a = a + b;
}

golchanskiy::point_t golchanskiy::operator-(const point_t& a, const point_t& b)
{
  return point_t{a.x - b.x, a.y - b.y};
}

golchanskiy::point_t& golchanskiy::operator-=(point_t& a, const point_t& b)
{
  return a = a - b;
}

golchanskiy::point_t golchanskiy::operator+(const point_t& a, const double b)
{
  return point_t{a.x + b, a.y + b};
}

golchanskiy::point_t& golchanskiy::operator+=(point_t& a, const double b)
{
  return a = a + b;
}

golchanskiy::point_t golchanskiy::operator-(const point_t& a, const double b)
{
  return point_t{a.x - b, a.y - b};
}

golchanskiy::point_t& golchanskiy::operator-=(point_t& a, const double b)
{
  return a = a - b;
}

bool golchanskiy::operator!=(const point_t& a, const point_t& b)
{
  return !(a == b);
}

