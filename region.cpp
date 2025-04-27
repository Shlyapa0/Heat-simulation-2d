#include "region.h"

Region::~Region()
{
    for (Shape* shape : shapes) {
        delete shape;
    }
    shapes.clear();
}

Region::Region(const std::vector<Shape*>& shape_list)
{
    for (Shape* shape : shape_list) {
        shapes.push_back(shape);
    }
}

Shape* Region::getShape(int i) {
    return shapes[i];
}