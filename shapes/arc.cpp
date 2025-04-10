#include "shapes/arc.h"

arc::arc(point p0, double rad, double ang_start, double ang_end) {
    center_p = p0;
    radius = rad;
    start_angle = ang_start;
    end_angle = ang_end;
}