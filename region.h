#ifndef REGION_H
#define REGION_H

#include "shapes/shape.h"
#include "vector"

class Region {
    public:
        std::vector<Shape*> shapes;
        ~Region();
        Region(std::vector<Shape*> shape_list);
    private:
        int temp;
    };

#endif