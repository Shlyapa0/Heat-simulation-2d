#ifndef SOLVER_H
#define SOLVER_H

#include <vector>
#include "SolutionPoint.h"
#include "mesh.h"

class Solver {
    public:
        Solver();
        Solver(Mesh mesh, double* pattern, double* borderEquation);
        void Run();
        void GetInitialPoints();
        void InitialStep();
        void Step();
        void PrintToFile(const std::string& filename) const;
        bool CheckConvergence() const;
        std::vector<SolutionPoint> GetSolutionPoints() const;
    private:
        std::vector<SolutionPoint> solution_points;
        std::vector<SolutionPoint> solution_points_next;
        std::vector<SolutionPoint> solution_points_prev;
        std::vector<Point*> mesh_points;
        std::vector<NeighborInfo> neighbor_info;
        //double* pattern;
        //double* borderEquation;
};



#endif // SOLVER_H