#ifndef MESH_H
#define MESH_H

#include "shapes/point.h"

class Mesh {
    public:
        int getSize();
        point* getDataPointer();
        Mesh(int size);
    private:
        int size;
        point* points;
};

#endif