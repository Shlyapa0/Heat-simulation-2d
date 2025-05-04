#include <Solver.h>
#include <fstream>

#define BORDER1 y - x - 2

Solver::Solver() {
    // Constructor implementation
}

Solver::Solver(Mesh mesh, double* pattern, double* borderEquation) {
    //this->pattern = pattern;
    //this->borderEquation = borderEquation;
    mesh_points = mesh.getPoints();
    for (auto point : mesh_points) {
        double x = point->getX();
        double y = point->getY();
        solution_points.push_back(SolutionPoint(x, y));
    }
}

void Solver::Step() {
    // Perform a single step of the solver
    
}

void Solver::Run() {
    // Main loop for the solver
    GetInitialPoints();
    Step();
}

void Solver::GetInitialPoints() {
    // Initialize solution points
    for (auto point : mesh_points) {
        double x = point->getX();
        double y = point->getY();
        solution_points.push_back(SolutionPoint(x, y));
        if (point->getBorder() == 0) {
            solution_points.back().setValue(0.0);
        } else {
            solution_points.back().setValue(BORDER1);
        }
    }
}

void Solver::PrintToFile(const std::string& filename) const {
    std::ofstream fout;
    fout.open(filename);
    for (const auto& point : solution_points) {
        fout << point.getX() << ' ' << point.getY() << ' ' << point.getValue() << std::endl;
    }
}