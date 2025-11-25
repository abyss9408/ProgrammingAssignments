///////////////////////////////////////////////////////////////////////////////
// File Name:      driver-oop.cpp
//
// Description:    The main program for Lab on OOP, inheritance, and
//                 run-time polymorphism.
//
// IMPORTANT NOTE: This file should NOT be modified.
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "student.hpp"
#include "ug.hpp"
#include "grad.hpp"
#include "process.hpp"

// static function declarations ...
static void print_all(std::vector<Student*> const&);
static void print_ug(std::vector<Student*> const&);
static void print_grad(std::vector<Student*> const&);

/**
 * @brief The program execution begins here.
 * @param argc The number of command-line arguments.
 * @param argv The command line arguments: there should be three arguments.
 * The first argument is the program name (that we'll ignore).
 * The second argument is the name of the file containing students' records.
 * The third argument determines the type of output:
 * 1: prints information about undergraduates including statistics
 * 2: prints information about graduate students including statistics.
 * 3: prints information about ALL students including statistics
 * 4: prints all the information specified by arguments 1, 2, and 3.
 * @return 0 for normal program termination, -1 for abnormal termination.
 */
int main(int argc, char *argv[]) {
  // is program being used correctly?
  if (argc < 3) {
    std::cerr << "usage: " << argv[0] << " <students.txt> output-type" << "\n";
    return 0;
  }

  // is file specified on command-line valid?
  std::ifstream ifs{argv[1]};
  if (!ifs) {
    std::cerr << "Unable to open input file " << argv[1] << "!!!\n";
    return 0;
  }

  // parse file and populate containers with pointers to derived class objects
  std::vector<Student*> vs;  // container for (pointers to) ALL students
  std::vector<Student*> vus; // container for (pointers to) undergrads
  std::vector<Student*> vgs; // container for (pointers to) grads
  parse_file(ifs, vs, vus, vgs);

  std::cout << "Total number of students in course               = "
            << Student::count() << "\n";
  std::cout << "Total number of undergraduate students in course = "
            << Undergraduate::count() << "\n";
  std::cout << "Total number of graduate students in course      = "
            << Graduate::count() << "\n\n";
  
  int output_type = std::stoi(std::string(argv[2]));
  output_type = (output_type < 1) ? 1 : (output_type > 4) ? 4 : output_type;
  switch (output_type) {
    case 1: print_ug(vus); break;
    case 2: print_grad(vgs); break;
    case 3: print_all(vs); break;
    case 4: print_ug(vus); print_grad(vgs); print_all(vs); break;
  }

  cleanup(vs, vus, vgs);
}

// print all information about students in course
static void print_all(std::vector<Student*> const& vs) {
  std::cout << "STUDENT INFORMATION" << "\n";
  std::cout << "---------------------------------" << "\n";
  print_records(vs);

  std::cout << "STUDENT STATISTICS" << "\n";
  std::cout << "--------------------------------" << "\n";
  print_stats(vs);
}

static void print_ug(std::vector<Student*> const& vus) {
  std::cout << "UNDERGRADUATE STUDENT INFORMATION" << "\n";
  std::cout << "---------------------------------" << "\n";
  print_records(vus);

  std::cout << "UNDERGRADUATE STUDENT STATISTICS" << "\n";
  std::cout << "--------------------------------" << "\n";
  print_stats(vus);
}

static void print_grad(std::vector<Student*> const& vgs) {
  std::cout << "GRADUATE STUDENT INFORMATION" << "\n";
  std::cout << "----------------------------" << "\n";
  print_records(vgs);

  std::cout << "GRADUATE STUDENT STATISTICS" << "\n";
  std::cout << "--------------------------------" << "\n";
  print_stats(vgs);
}
