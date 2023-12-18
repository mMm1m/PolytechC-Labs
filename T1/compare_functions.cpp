#include "base_types.h"
#include "compare_functions.h"
#include <limits>

namespace
{
  int compare(double x, double y)
  {
    return x - y < -std::numeric_limits< double >::epsilon() ? -1 : x - y > std::numeric_limits< double >::epsilon() ? 1 : 0;
  }
}

bool golchanskiy::isLess(double x, double y)
{
  return compare(x, y) < 0;
}

bool golchanskiy::isEqual(double x, double y)
{
  return compare(x, y) == 0;
}

bool golchanskiy::isGreater(double x, double y)
{
  return compare(x, y) > 0;
}

bool golchanskiy::isGreater(const golchanskiy::point_t& A, const golchanskiy::point_t& B)
{
  return isGreater(A.x, B.x) && isGreater(A.y, B.y);
}

