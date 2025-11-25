#ifndef CONVEX_HULL_H
#define CONVEX_HULL_H

#include <vector>
#include <stack>
#include "point.h"

// Function declarations
double crossProduct(const Point& a, const Point& b, const Point& c);
Point findMinYPoint(const std::vector<Point>& points);
void sortPointsByPolarAngle(std::vector<Point>& points, const Point& p0);
std::stack<Point> convexHull(std::vector<Point>& points);

#endif // CONVEX_HULL_H