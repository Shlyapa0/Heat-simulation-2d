#ifndef MESH_H
#define MESH_H

#include "shapes/point.h"
#include "region.h"

struct NeighborInfo {
    int upIndex = -1;
    int downIndex = -1;
    int leftIndex = -1;
    int rightIndex = -1;
};

class Mesh {
    public:
        int getSize();
        std::vector<Point*> getPoints();
        Mesh(Region reg, double max_reg_size, double cell_sz, Point& initial_p);
        void getPointsX(std::vector<Point*>& initialPoints, std::optional<const Shape*> ptr1);
        void getPointsY(std::vector<Point*>& initialPoints, Point* initial_point, std::optional<const Shape*> ptr1);
    private:
        Point* points;
        double cell_size;
        Point initial_point;
        std::vector<Point*> allPoints;
        std::vector<NeighborInfo> neighborInfo;
        void findNeighbors(int index);
        void findNeighbors();
        void addBorder(int index, Region reg);
    public:
        std::vector<NeighborInfo> getNeighborInfo();
};

#endif