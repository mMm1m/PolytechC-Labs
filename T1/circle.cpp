#include "circle.h"
#include <stdexcept>
#include "compare_functions.h"

golchanskiy::Circle::Circle(const golchanskiy::point_t& center, double radius):
  center_(center),
  radius_(radius)
{
  if (golchanskiy::isLess(radius, 0.0) || golchanskiy::isEqual(radius, 0.0))
  {
    throw std::logic_error("Bad circle");
  }
}

double golchanskiy::Circle::getArea() const
{
  return golchanskiy::PI * radius_ * radius_;
}

golchanskiy::rectangle_t golchanskiy::Circle::getFrameRect() const
{
  rectangle_t frame_rect = { 2.0 * radius_, 2.0 * radius_, center_ };
  return frame_rect;
}

void golchanskiy::Circle::move(const golchanskiy::point_t& new_center)
{
  center_ = new_center;
}

void golchanskiy::Circle::doScale(double scale_value)
{
  radius_ *= scale_value;
}

void golchanskiy::Circle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}

