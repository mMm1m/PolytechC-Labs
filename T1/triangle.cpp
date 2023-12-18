#include "triangle.h"

#include <cmath>
#include <algorithm>
#include <stdexcept>

#include "base_types.h"

namespace {
  const std::string TRIANGLE_ERROR = "Can't create this triangle";
}

golchanskiy::Triangle::Triangle(const point_t& a, const point_t& b, const point_t& c):
  a_(a),
  b_(b),
  c_(c)
{
  if (!isTriangle(getAB(), getBC(), getAC())) {
    throw std::logic_error(TRIANGLE_ERROR);
  }
}

double golchanskiy::Triangle::getArea() const
{
  double ab = getAB();
  double bc = getBC();
  double ac = getAC();
  double halfOfPerimeter = (ab + bc + ac) / 2;
  return std::sqrt(halfOfPerimeter * (halfOfPerimeter - ab) * (halfOfPerimeter - bc) * (halfOfPerimeter - ac));
}

golchanskiy::rectangle_t golchanskiy::Triangle::getFrameRect() const
{
  point_t min{std::min({a_.x, b_.x, c_.x}), std::min({a_.y, b_.y, c_.y})};
  point_t max{std::max({a_.x, b_.x, c_.x}), std::max({a_.y, b_.y, c_.y})};
  return getRect(min, max);
}

void golchanskiy::Triangle::move(const point_t& pos)
{
  point_t center = getCenter();
  move(pos.x - center.x, pos.y - center.y);
}

void golchanskiy::Triangle::move(const double dx, const double dy)
{
  point_t dp = {dx, dy};
  a_ += dp;
  b_ += dp;
  c_ += dp;
}

void golchanskiy::Triangle::doScale(const double k)
{
  point_t center = getCenter();
  a_ = scalePoint(a_, center, k);
  b_ = scalePoint(b_, center, k);
  c_ = scalePoint(c_, center, k);
}

golchanskiy::point_t golchanskiy::Triangle::getCenter() const
{
  return point_t{(a_.x + b_.x + c_.x) / 3, (a_.y + b_.y + c_.y) / 3};
}

double golchanskiy::Triangle::getAB() const
{
  return getDistance(a_, b_);
}

double golchanskiy::Triangle::getAC() const
{
  return getDistance(a_, c_);
}

double golchanskiy::Triangle::getBC() const
{
  return getDistance(b_, c_);
}


