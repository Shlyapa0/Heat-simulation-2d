#include <mesh.h>

Mesh::Mesh(int meshsize) {
    point* points = new point[meshsize];
    int size = meshsize;
}

int Mesh::getSize() {
    return size;
}

point* Mesh::getDataPointer() {
    return points;
}