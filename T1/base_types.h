#ifndef BASETYPES_H
#define BASETYPES_H

namespace golchanskiy {
  struct point_t
  {
    double x, y;
  };

  struct rectangle_t
  {
    double width, height;
    point_t pos;
  };

  double getDistance(const point_t& src1, const point_t& src2);
  rectangle_t getRect(const point_t& point1, const point_t& point2);
  point_t scalePoint(const point_t& point, const point_t& center, double k);
  bool isTriangle(double a, double b, double c);

  point_t operator+(const point_t& a, const point_t& b);
  point_t& operator+=(point_t& a, const point_t& b);
  point_t operator-(const point_t& a, const point_t& b);
  point_t& operator-=(point_t& a, const point_t& b);
  point_t operator+(const point_t& a, double b);
  point_t& operator+=(point_t& a, double b);
  point_t operator-(const point_t& a, double b);
  point_t& operator-=(point_t& a, double b);
  bool operator!=(const point_t& a,const point_t& b);

}
#endif

