#ifndef T1_RECTANGLE_HPP
#define T1_RECTANGLE_HPP

#include "shape.h"
#include "base_types.h"

namespace golchanskiy
{
  class Rectangle: public Shape
  {
    public:
     Rectangle(const Rectangle&) = default;
     Rectangle(const point_t&, const point_t&);
     explicit Rectangle(const rectangle_t&);
     ~Rectangle() override = default;
     double getArea() const override;
     rectangle_t getFrameRect() const override;
     void move(const point_t&) override;
     void move(double , double ) override;
     void doScale(double ) override;
    private:
     rectangle_t rectangle_;
  };
}
#endif

