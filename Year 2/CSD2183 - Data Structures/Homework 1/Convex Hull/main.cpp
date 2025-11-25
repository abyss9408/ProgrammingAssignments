#include <iostream>
#include <vector>
#include <stack>
#include "point.h"
#include "convex_hull.h"
#include "stack_functions.h"
#include "plot_hull.h"
#include <random>

// Convert stack<Point> to vector<Point> while preserving order
std::vector<Point> stackToVector(std::stack<Point> s) {
  std::vector<Point> result;

  // Extract elements from stack into the vector
  while (!s.empty()) {
      result.push_back(s.top());
      s.pop();
  }
  return result;
}

int main() {
  std::vector<Point> points;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis1(-1000.0, -500.0);
  std::uniform_real_distribution<> dis2(100.0, 500.0);

  for (int i = 0; i < 20; ++i) {
    Point p = {dis1(gen), dis2(gen)};
    points.push_back(p);
  }

  for (const auto &p : points) {
    std::cout << "Point(" << p.x << ", " << p.y << ")\n";
  }

  // User-defined hull
  std::stack<Point> hull_stack = convexHull(points);
  std::vector<Point> hull= stackToVector(hull_stack);
  // Plot the user's solution and the actual convex hull
  plot_hull(points, hull, "convex_hull.html");

  return 0;
}