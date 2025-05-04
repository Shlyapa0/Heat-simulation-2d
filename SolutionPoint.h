#ifndef SOLUTIONPOINT_H
#define SOLUTIONPOINT_H

class SolutionPoint {
    public:
        SolutionPoint();
        SolutionPoint(const double x_val, const double y_val);
        SolutionPoint(const double x_val, const double y_val, const double value_val);
        SolutionPoint(const double x_val, const double y_val, const double value_val, const int num_border_val) : x(x_val), y(y_val), value(value_val), num_border(num_border_val) {};
        SolutionPoint(const SolutionPoint& other) : x(other.x), y(other.y), value(other.value), num_border(other.num_border) {}
        SolutionPoint& operator=(const SolutionPoint& other);
        double getX() const;
        double getY() const;
        double getValue() const;
        void setValue(double value_val);
        ~SolutionPoint() {};
    private:
        double x;
        double y;
        double value;
        int num_border; //0 - not a border
};

#endif