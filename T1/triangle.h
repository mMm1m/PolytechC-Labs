#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "shape.h"

namespace golchanskiy {
  class Triangle: public Shape {
    public:
     Triangle() = delete;
     Triangle(const point_t& a, const point_t& b, const point_t& c);
     ~Triangle() = default;

     double getArea() const override;
     rectangle_t getFrameRect() const override;
     void move(double dx, double dy) override;
     void move(const point_t& pos) override;
     void doScale(double k) override;
    private:
     point_t a_;
     point_t b_;
     point_t c_;
     point_t getCenter() const;
     double getAB() const;
     double getAC() const;
     double getBC() const;
  };
}

#endif

