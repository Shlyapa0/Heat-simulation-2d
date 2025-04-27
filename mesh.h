#ifndef MESH_H
#define MESH_H

#include "shapes/point.h"
#include "region.h"

class Mesh {
    public:
        int getSize();
        Point* getDataPointer();
        Mesh(Region reg, double max_cell_size, double max_reg_size, Point initial_point);
    private:
        int size;
        Point* points;
};

#endif