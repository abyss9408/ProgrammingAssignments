#include<stack>
#include "point.h"

Point nextToTop(std::stack<Point>& stack) {
    // Function to get the next-to-top element from the stack
    Point top = stack.top();
    stack.pop();
    Point nextTop = stack.top();
    stack.push(top);
    return nextTop;
}