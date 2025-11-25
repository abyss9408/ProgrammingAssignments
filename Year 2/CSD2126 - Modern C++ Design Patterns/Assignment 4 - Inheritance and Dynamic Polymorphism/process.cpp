// provide file header here

#include "process.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

void parse_file(std::ifstream &ifs, std::vector<Student*>& vs,
                std::vector<Student*>& vus, std::vector<Student*>& vgs) {
  // TODO: Implement this method.
  // See function header in process.hpp for additional information
  
}

void print_records(std::vector<Student*> const& v) {
  // TODO: Implement this method.
  // See function header in process.hpp for additional information
  
}

void print_stats(std::vector<Student*> const& v) {
  // TODO: Implement this method.
  // See function header in process.hpp for additional information

  // # of students in container.
  // compute and print mean of the total score.
  // sort and print the students based on their total score.

}

/**
* @brief Return memory allocated by operator new ONLY using pointers contained
* in container specified by first parameter. Why? Because containers specified
* in the next two containers reference the same memory locations as elements of
* first container, double deletion will cause undefined run-time behavior.
* Next, clear contents of all 3 containers.
*
* @param vs Reference to vector<Student*> containing pointers to all students.
* @param vs Reference to vector<Student*> containing pointers to undergraduates.
* @param vs Reference to vector<Student*> containing pointers to graduates.
*/
void cleanup(std::vector<Student*>& vs, std::vector<Student*>& vus, std::vector<Student*>& vgs) {
  // delete memory previously allocated by operator new
  for (Student *ps : vs) {
    delete ps;
  }
  // avoid double deletion!!!
  vs.clear();
  vus.clear();
  vgs.clear();
}
