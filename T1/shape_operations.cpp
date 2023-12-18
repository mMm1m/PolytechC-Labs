#include "shape_operations.h"
#include <iostream>

void golchanskiy::scale(const point_t& point, double k, std::unique_ptr< Shape >& shape)
{
  if (k <= 0.0) {
    throw std::logic_error("Incorrect value for k!");
  }
  point_t center1 = shape->getFrameRect().pos;
  shape->move(point);
  point_t center2 = shape->getFrameRect().pos;
  double x = center2.x - center1.x;
  double y = center2.y - center1.y;
  shape->scale(k);
  shape->move(-x * k, -y * k);
}

double golchanskiy::getSummaryArea(const golchanskiy::Storage< std::unique_ptr< Shape > >& storage)
{
  double area = 0.0;
  for (size_t i = 0; i < storage.getSize(); ++i) {
    area += storage[i]->getArea();
  }
  return area;
}

std::pair< golchanskiy::point_t, golchanskiy::point_t > golchanskiy::getCoordinatesOfFrame(const golchanskiy::rectangle_t& rectangle)
{
  point_t center = rectangle.pos;
  point_t left{center.x - rectangle.width / 2.0, center.y - rectangle.height / 2.0};
  point_t right{center.x + rectangle.width / 2.0, center.y + rectangle.height / 2.0};
  return std::pair< point_t, point_t >(left, right);
}

void golchanskiy::printCoordinatesOfFrame(const golchanskiy::Storage< std::unique_ptr< Shape > >& storage, std::ostream& os)
{
  size_t size = storage.getSize();
  for (size_t i = 0; i < size; ++i) {
    auto pointPair = getCoordinatesOfFrame(storage[i]->getFrameRect());
    os << pointPair.first << " " << pointPair.second;
    if (i != size - 1) {
      os << " ";
    }
  }
}

void golchanskiy::printShapes(const golchanskiy::Storage< std::unique_ptr< Shape > >& storage, std::ostream& os)
{
  os << golchanskiy::getSummaryArea(storage) << " ";
  golchanskiy::printCoordinatesOfFrame(storage, os);
}


