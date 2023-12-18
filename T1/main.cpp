#include <iostream>
#include <iomanip>
#include <string>
#include "circle.h"
#include "triangle.h"
#include "rectangle.h"
#include "point_operations.h"
#include "storage.h"
#include "shape_operations.h"

int main()
{
  std::streamsize precision = std::cout.precision();
  std::ios_base::fmtflags flags = std::cout.flags();
  golchanskiy::Storage< std::unique_ptr< golchanskiy::Shape > > shapeStorage;
  bool existenceScale = false;
  while (!std::cin.eof()) {
    try {
      std::string line = "";
      std::getline(std::cin, line);
      if (!line.empty()) {
        size_t pos = line.find(' ');
        std::string command = line.substr(0, pos);
        line.erase(0, pos + 1);

        std::unique_ptr< golchanskiy::Shape > shape;
        if (command == "RECTANGLE") {
          golchanskiy::point_t left = golchanskiy::getPointFromString(line);
          golchanskiy::point_t right = golchanskiy::getPointFromString(line);
          shape = std::make_unique< golchanskiy::Rectangle >(left, right);
          shapeStorage.push(std::move(shape));
        } else if (command == "CIRCLE") {
          golchanskiy::point_t circle_center = golchanskiy::readPoint(line);
          double radius = std::stod(golchanskiy::getFirstWord(line));
          shape = std::make_unique< golchanskiy::Circle >(circle_center, radius);
          shapeStorage.push(std::move(shape));
        } else if (command == "TRIANGLE") {
          golchanskiy::point_t point1 = golchanskiy::getPointFromString(line);
          golchanskiy::point_t point2 = golchanskiy::getPointFromString(line);
          golchanskiy::point_t point3 = golchanskiy::getPointFromString(line);
          shape = std::make_unique< golchanskiy::Triangle >(point1, point2, point3);
          shapeStorage.push(std::move(shape));

        } else if (command == "SCALE") {
          golchanskiy::point_t point = golchanskiy::getPointFromString(line);
          double k = std::stod(line.substr(0, line.find(' ')));
          std::cout << std::fixed << std::setprecision(1);
          golchanskiy::printShapes(shapeStorage, std::cout);
          std::cout << '\n';
          for (size_t i = 0; i < shapeStorage.getSize(); ++i) {
            golchanskiy::scale(point, k, shapeStorage[i]);
          }
          golchanskiy::printShapes(shapeStorage, std::cout);
          std::cout << std::setprecision(precision) << '\n';
          std::cout.flags(flags);
          existenceScale = true;
          break;
        }
      }
    } catch (const std::exception& ex) {
      std::cerr << ex.what() << "\n";
    }
  }
  if (shapeStorage.getSize() == 0 || !existenceScale) {
    std::cerr << "Invalid arguments for programm!";
    return 1;
  }
  return 0;
}


