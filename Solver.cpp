#include <Solver.h>
#include <fstream>
#include <algorithm>
#include <pattern.h>
#include <cmath>
#include <iostream>

#define BORDER1 y - x - 2
#define BORDER0 0
#define SOURCE0 pow(pow(x, 2) + pow(y, 2) + 1, -1)

Solver::Solver() {
    // Constructor implementation
}

Solver::Solver(Mesh mesh, double* pattern, double* borderEquation) {
    //this->pattern = pattern;
    //this->borderEquation = borderEquation;
    mesh_points = mesh.getPoints();
    neighbor_info = mesh.getNeighborInfo();
    for (auto point : mesh_points) {
        //double x = point->getX();
        //double y = point->getY();
        //solution_points.push_back(SolutionPoint(x, y, 0.0, point->getBorder()));
    }
    // std::sort(solution_points.begin(), solution_points.end(), [](const SolutionPoint& a, const SolutionPoint& b) {
    //     return a.getX() < b.getX() || (a.getX() == b.getX() && a.getY() < b.getY());
    // });
}

void Solver::Step() {
    solution_points_next = solution_points;
    for (int i=0; i < solution_points.size(); i++) {
        SolutionPoint prev_point = solution_points[i];
        if (prev_point.getBorder() == 0) {
            double value = prev_point.getValue();
            int neiborUpIndex = neighbor_info[i].upIndex;
            int neiborDownIndex = neighbor_info[i].downIndex;
            int neiborRightIndex = neighbor_info[i].rightIndex;
            int neiborLeftIndex = neighbor_info[i].leftIndex;
            double x = solution_points[i].getX();
            double y = solution_points[i].getY();
            double source = SOURCE0;
            //solution_points_next[i].setValue(solution_points[i].getValue()+5);
            solution_points_next[i].setValue(calcPattern(
                solution_points[neiborLeftIndex].getValue(),
                solution_points[neiborRightIndex].getValue(),
                solution_points[neiborUpIndex].getValue(),
                solution_points[neiborDownIndex].getValue(),
                std::abs(solution_points[neiborLeftIndex].getX() - solution_points[i].getX()),
                std::abs(solution_points[neiborRightIndex].getX() - solution_points[i].getX()),
                std::abs(solution_points[neiborDownIndex].getY() - solution_points[i].getY()),
                std::abs(solution_points[neiborUpIndex].getY() - solution_points[i].getY()),
                source
            ));
        }
        std::cout << "Point " << i << ": " << solution_points[i].getValue() 
        << " -> " << solution_points_next[i].getValue() << std::endl;
    }
    solution_points = solution_points_next;
    // // Compare solution_points and solution_points_next
    // bool isConverged = true;
    // for (int i = 0; i < solution_points.size(); i++) {
    //     if (std::abs(solution_points[i].getValue() - solution_points_next[i].getValue()) > 1e-6) {
    //         isConverged = false;
    //         break;
    //     }
    // }

    // if (isConverged) {
    //     std::cout << "Solver has converged." << std::endl;
    // }
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

