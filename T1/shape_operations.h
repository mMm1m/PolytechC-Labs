#ifndef SHAPE_OPERATIONS_HPP
#define SHAPE_OPERATIONS_HPP

#include "point_operations.h"
#include "shape.h"
#include "storage.h"

namespace golchanskiy {
  void scale(const point_t& point, double k, std::unique_ptr< Shape >& shape);
  double getSummaryArea(const Storage< std::unique_ptr< Shape > >& storage);
  std::pair< point_t, point_t > getCoordinatesOfFrame(const rectangle_t& rectangle);
  void printCoordinatesOfFrame(const Storage< std::unique_ptr< Shape > >& storage, std::ostream& os);
  void printShapes(const Storage< std::unique_ptr< Shape > >& storage, std::ostream& os);
}
#endif

