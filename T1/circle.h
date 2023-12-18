#ifndef T1_CIRCLE_HPP
#define T1_CIRCLE_HPP

#include <cmath>
#include "base_types.h"
#include "shape.h"

namespace golchanskiy
{
  const double PI = std::acos(-1.0);

  class Circle: public Shape
  {
    public:
     Circle(const Circle&) = default;
     Circle(const point_t&, double );
     ~Circle() override = default;

     double getArea() const override;
     rectangle_t getFrameRect() const override;
     void move(double dx, double dy) override;
     void move(const point_t&) override;
     void doScale(double) override;

    private:
     point_t center_;
     double radius_;
  };
}

#endif

