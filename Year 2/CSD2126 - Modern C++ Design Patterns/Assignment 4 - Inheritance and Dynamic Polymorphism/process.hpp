///////////////////////////////////////////////////////////////////////////////
// File Name:      process.hpp
//
// Description:    Methods to perform some processing on student objects.
//
// IMPORTANT NOTE: This file should NOT be modified.
///////////////////////////////////////////////////////////////////////////////

#ifndef PROCESS_HPP
#define PROCESS_HPP

#include "student.hpp"
#include "ug.hpp"
#include "grad.hpp"
#include <fstream>
#include <vector>

/**
* @brief Parse comma-separated file containing students' records - one line
* per student. Each line of text contains a comma-separated list of information
* common to all students.
* The function will read a line, determine whether the line pertains to a
* Undergraduate or Graduate student.
* If first non-whitespace character in file is U, then the line contains
* information pertaining to an undergrad; otherwise, if the first non-white
* space character is G, then the line contains information pertaining to a grad
* student.
* Depending on the type of Student, the appropriate ctor is used to initialize
* either a Graduate or Undergraduate object on the free store.
* Since Graduate is-a Student and Undergraduate is-a Student, the value returned
* by operator new is assigned to a variable of type Student*.
* This pointer is added to a vector container that will be the repository of
* ALL students.
* In addition, pointers to free store objects of type Graduate are added to a
* vector container that will be the repository of ONLY grad students. Likewise,
* pointers to free store objects of type Undergraduate are added to a vector
* container that will be the repository of ONLY undergrad students. This is
* a common idiom: initialize an object on the free store only once with multiple
* containers containing pointers to that free store object.
*
* @param ifs Input file stream with students' data.
* @param students   Reference to vector<Student*> that will be filled with
*                   pointers to every student in file.
* @param undergrads Reference to vector<Student*> that will be filled with
*                   pointers to undergraduate students in file.
* @param grads      Reference to vector<Student*> that will be filled with
*                   pointers to graduate students in file.
*/
void parse_file(std::ifstream& ifs,
                std::vector<Student*>& students,
                std::vector<Student*>& undergrads,
                std::vector<Student*>& grads);

/**
* @brief Use dynamic-binding (run-time polygmorphism) to print details of
*        students represented in std::vector<Student*> container.
*
* @param students Read-only reference to std::vector<Student*>.
*/
void print_records(std::vector<Student*> const& students);

/**
* @brief Computes and prints following statistics: student count; mean of
*        total score; and sorted list of students in DESCENDING order using 
*        a student's total score as sorting criterion with each line  
*        consisting of the following information:
*        student id, student name, total score, course grade.
*
* @param students Read-only reference to vector<Student*> for which statistics
*                 are to be computed.
*/
void print_stats(std::vector<Student*> const& students);

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
void cleanup(std::vector<Student*>& vs, 
             std::vector<Student*>& vus,
             std::vector<Student*>& vgs);

#endif // end #ifndef PROCESS_HPP
