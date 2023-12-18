#include "rectangle.h"
#include <stdexcept>
#include "compare_functions.h"

golchanskiy::Rectangle::Rectangle(const golchanskiy::rectangle_t& rect):
  rectangle_(rect)
{
  if (rect.height == 0.0 || rect.width == 0.0)
  {
    throw std::logic_error("Degenerate rectangle");
  }
}

golchanskiy::Rectangle::Rectangle(const golchanskiy::point_t& A, const golchanskiy::point_t& B):
  Rectangle(getRect(A, B))
{
  if (golchanskiy::isGreater(A, B))
  {
    throw std::logic_error("Wrong rectangle");
  }
}

double golchanskiy::Rectangle::getArea() const
{
  return rectangle_.width * rectangle_.height;
}

golchanskiy::rectangle_t golchanskiy::Rectangle::getFrameRect() const
{
  return rectangle_;
}

void golchanskiy::Rectangle::move(const golchanskiy::point_t& barycenter)
{
  rectangle_.pos = barycenter;
}

void golchanskiy::Rectangle::move(double dx, double dy)
{
  rectangle_.pos.x += dx;
  rectangle_.pos.y += dy;
}

void golchanskiy::Rectangle::doScale(double scale_value)
{
  rectangle_.height *= scale_value;
  rectangle_.width *= scale_value;
}


