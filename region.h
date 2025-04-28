#ifndef REGION_H
#define REGION_H

#include "shapes/shape.h"
#include "vector"

class Region {
    public:
        ~Region();
        Region(const std::vector<Shape*>& shape_list);
        size_t getSize();
        Shape* getShape(int i);
    private:
        std::vector<Shape*> shapes;
    };

#endif