#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <cmath>
#include "point.h"
#include "stack_functions.h"

double crossProduct(const Point& a, const Point& b, const Point& c) {
    // Function to compute the cross product of two vectors (a -> b and a -> c)
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

Point findMinYPoint(const std::vector<Point>& points) {
    // Function to find the point with the minimum y-coordinate (and leftmost if tie)
    Point p0 = points[0];
    for (const Point& p : points)
    {
        if (p.y < p0.y || (p.y == p0.y && p.x < p0.x))
        {
            p0 = p;
        }
    }
    return p0;
}

void sortPointsByPolarAngle(std::vector<Point>& points, const Point& p0) {
    // Function to sort points based on polar angle with respect to p_0
    for (size_t i = 0; i < points.size(); ++i)
    {
        if (points[i].x == p0.x && points[i].y == p0.y)
        {
            std::swap(points[i], points[0]);
            break;
        }
    }

    std::sort(points.begin() + 1, points.end(),
        [&p0](const Point& p1, const Point& p2)
        {
            double cross = crossProduct(p0, p1, p2);
            if (cross == 0)
            {
                // If points are collinear, sort by distance from p0
                double d1 = (p1.x - p0.x) * (p1.x - p0.x) + 
                           (p1.y - p0.y) * (p1.y - p0.y);
                double d2 = (p2.x - p0.x) * (p2.x - p0.x) + 
                           (p2.y - p0.y) * (p2.y - p0.y);
                return d1 < d2;
            }
            return cross > 0;
        });
}

// Function to compute the convex hull using Graham Scan
std::stack<Point> convexHull(std::vector<Point>& points) {
    // Step 1: Find the point with the minimum y-coordinate (p0)
    Point p0 = findMinYPoint(points);

    // Step 2: Sort the points based on polar angle with respect to p0
    sortPointsByPolarAngle(points, p0);

    // Step 3: Initialize the stack with the first three points
    std::stack<Point> hull;
    hull.push(points[0]);
    hull.push(points[1]);
    hull.push(points[2]);

    // Step 4: Process the remaining points
    for (size_t i = 3; i < points.size(); ++i)
    {
        // Remove points that make a non-left turn
        while (hull.size() > 1 && crossProduct(nextToTop(hull), hull.top(), points[i]) <= 0)
        {
            hull.pop();
        }
        hull.push(points[i]);
    }
    
    // Step 5: Return the stack containing the convex hull points
    return hull;
}