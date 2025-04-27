#include <mesh.h>
#include <shapes/section.h>

Mesh::Mesh(Region reg, double max_cell_size, double max_reg_size, Point initial_point) {
    size = max_cell_size;
    Section r1 = Section(initial_point, Point(max_reg_size, 0));
    r1.intersect(reg.getShape(1));
}

int Mesh::getSize() {
    return size;
}

Point* Mesh::getDataPointer() {
    return points;
}