#include <Solver.h>
#include <fstream>
#include <algorithm>
#include <pattern.h>
#include <cmath>
#include <iostream>

#define BORDER1 y - x + 2
#define BORDER0 0
//#define BORDER1 0
#define EPS 1e-9
//#define SOURCE0 -pow(pow(x, 2) + pow(y-1, 2) + 0.1, -1)
#define SOURCE0 0
//#define SOURCE0 10

Solver::Solver() {
    // Constructor implementation
}

Solver::Solver(Mesh mesh, double* pattern, double* borderEquation) {
    //this->pattern = pattern;
    //this->borderEquation = borderEquation;
    mesh_points = mesh.getPoints();
    neighbor_info = mesh.getNeighborInfo();
    solution_points_prev.resize(mesh_points.size());
    solution_points_next.resize(mesh_points.size());
}

void Solver::Step() {
    solution_points_prev = solution_points;
    solution_points_next = solution_points;
    for (int i=0; i < solution_points.size(); i++) {
        SolutionPoint prev_point = solution_points[i];
        if (prev_point.getBorder() == 0) {
            double value = prev_point.getValue();
            int neiborUpIndex = neighbor_info[i].upIndex;
            int neiborDownIndex = neighbor_info[i].downIndex;
            int neiborRightIndex = neighbor_info[i].rightIndex;
            int neiborLeftIndex = neighbor_info[i].leftIndex;
            if (neiborUpIndex == -1 || neiborDownIndex == -1 || neiborLeftIndex == -1 || neiborRightIndex == -1) {
                std::cout << "Warning: Not all neighbors found for point (" << solution_points[i].getX() << ", " << solution_points[i].getY() << ")." << std::endl;
                continue;
            }
            double x = solution_points[i].getX();
            double y = solution_points[i].getY();
            double source = SOURCE0;
            solution_points_next[i].setValue(calcPattern(
                solution_points[neiborDownIndex].getValue(),
                solution_points[neiborUpIndex].getValue(),
                solution_points[neiborLeftIndex].getValue(),
                solution_points[neiborRightIndex].getValue(),
                std::abs(solution_points[neiborDownIndex].getY() - solution_points[i].getY()),
                std::abs(solution_points[neiborUpIndex].getY() - solution_points[i].getY()),
                std::abs(solution_points[neiborLeftIndex].getX() - solution_points[i].getX()),
                std::abs(solution_points[neiborRightIndex].getX() - solution_points[i].getX()),
                source
            ));
            
            if (std::abs(x)<EPS && std::abs(y-1)<EPS) {
            std::cout << "x: " << x << ", y: " << y << ", source:" << source << std::endl;
            
        }
        }
        
    }
    solution_points = solution_points_next;
    
}

bool Solver::CheckConvergence() const {
    for (int i = 0; i < solution_points.size(); i++) {
        if (std::abs(solution_points[i].getValue() - solution_points_prev[i].getValue()) > EPS) {
            return false;
        }
    }
    return true;
}

void Solver::InitialStep() {
    Step();
}

void Solver::Run() {
    GetInitialPoints();
    InitialStep();
    for (;!CheckConvergence();) {
        Step();
    }
    std::cout << "Solution converged!" << std::endl;
    PrintToFile("output.txt");
}

void Solver::GetInitialPoints() {
    solution_points.clear();
    solution_points_next.clear();
    solution_points_prev.clear();
    solution_points.reserve(mesh_points.size());
    solution_points_next.reserve(mesh_points.size());
    solution_points_prev.reserve(mesh_points.size());
    // Initialize solution points
    for (auto point : mesh_points) {
        double x = point->getX();
        double y = point->getY();
        solution_points.push_back(SolutionPoint(x, y, 0.0, point->getBorder()));
        if (point->getBorder() == 0) {
            solution_points.back().setValue(BORDER0);
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

