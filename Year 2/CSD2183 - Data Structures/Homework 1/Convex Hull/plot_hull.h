#ifndef PLOT_HULL_H
#define PLOT_HULL_H

#include "point.h"
#include <string>
#include <vector>

void plot_hull(const std::vector<Point> &points, const std::vector<Point> &hull,
               const std::string &filename);

#endif // PLOT_HULL_H