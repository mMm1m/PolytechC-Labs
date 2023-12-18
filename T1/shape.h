#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <stdexcept>
#include "point_operations.h"

namespace golchanskiy {
  class Shape {
    public:
     virtual ~Shape() = default;

     virtual double getArea() const = 0;
     virtual rectangle_t getFrameRect() const = 0;
     virtual void move(const point_t& point) = 0;
     virtual void move(double x, double y) = 0;
     void scale(double k);
    private:
     virtual void doScale(double k) = 0;
  };
}
#endif

