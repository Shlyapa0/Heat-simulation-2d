#include "region.h"

Region::Region(std::vector<Shape*> shape_list) {
    for (auto i : shape_list) {
        shapes.push_back(i);
    }
}