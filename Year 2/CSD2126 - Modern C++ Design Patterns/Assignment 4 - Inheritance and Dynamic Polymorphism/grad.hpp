///////////////////////////////////////////////////////////////////////////////
// File Name:      grad.hpp
//
// Description:    Header file for defining class Graduate.
//
// IMPORTANT NOTE: This file should NOT be modified.
///////////////////////////////////////////////////////////////////////////////

#ifndef GRADSTUDENT_HPP
#define GRADSTUDENT_HPP

#include "student.hpp"
#include <iostream>

/**
* @brief Graduate is-a Student:
*/
class Graduate : public Student {
private:
  std::string gresearch; // research area
  std::string gadvisor;  // name of advisor
  static int gcount;    // how many enrolled graduates?

public:
/**
* @brief Constructor for an Graduate student.
* The ctor parses comma-separated line starting with character 'G' and
* sets up general Student part plus specialized graduate information.
* This function must use the Student(std::string&) ctor to set up the
* general Student information consisting of id, name, yob, project grade,
* unknown number of homework grades.
* Then, this ctor will add the student's research topic and their faculty
* advisor's name. Further, the ctor will increment the static data member
* gcount that keeps track of how many graduates are enrolled.
*
* @param line Line of comma-separated text from input file
*/
  Graduate(std::string& line);

// Each Graduate is unique. Therefore, they cannot be default constructed
// nor can there be replicas of a Graduate object.
  Graduate() = default;
  Graduate(Graduate const&) = delete;
  Graduate& operator=(Graduate const&) = delete;
  virtual ~Graduate() = default;

/**
* @brief Accessor for the student's research area.
*
* @return The research area of the student.
*/
  std::string research() const;

/**
* @brief Accessor for the student's advisor.
*
* @return The advisor of the student.
*/
  std::string advisor() const;

/**
* @brief Get the total number of graduate students.
* Note that this is a static member function that should
* return the current value of static data member gcount.
*
* @return The number of graduate students.
*/
  static int count();

/**
* @brief Prints the details of Graduate Student using
* Student::print_details() to print Student details.
* In addition to the fields printed by Student::print_details(),
* this function should print type of student (Graduate Student),
* research area, and name of student's faculty advisor.
*
* @example Your function must follow this format to print details of
* a student:
* Id = 2
* Name = Bernd Leno
* Age = 29
* Project = 92
* Assignment = [80, 91, 75, 91, 93, 92, 95, 76, 78, 88]
* Total = 88.95
* Grade = CR
* Type = Graduate Student
* Research Area = School of Keeping
* Advisor = Joachim Loew
*/
  virtual void print_details() const override;

/**
* @brief Get the total score of a student.
* Algorithm for computing total score for Graduate students is:
* Mean of homework grades is worth 50% of total score;
* Project score           is worth 50% of total score.
* @return The total score of the student.
*/
  virtual double total_score() const override;

/**
* @brief Computes letter grade obtained by a student.
*        Algorithm for computing letter grade for Graduate students is:
*        Letter grade N  if total grade < 80 and
*        letter grade CR if total grade >= 80 
* @return The letter grade of the student.
*
*        What is the purpose of override specifier?
*        It can be hard to keep track of which derived class functions
*        are meant to override which base class functions. Fortunately, we
*        can get compiler help to check. We can explicitly declare that a
*        function is meant to override. Assuming that the derived class
*        functions were meant to override, we can say so by adding override.
*        Explicit use of override is particularly useful in large, complicated
*        class hierarchies.
*/
  virtual std::string course_grade() const override;
};

#endif // end of #ifndef GRADSTUDENT_HPP
