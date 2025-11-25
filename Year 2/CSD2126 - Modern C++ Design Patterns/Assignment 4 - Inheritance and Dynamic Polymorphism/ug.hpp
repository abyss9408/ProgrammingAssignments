///////////////////////////////////////////////////////////////////////////////
// File Name:      ug.hpp
//
// Description:    The header file for defining class Undergraduate.
//
// IMPORTANT NOTE: This file should NOT be modified.
///////////////////////////////////////////////////////////////////////////////

#ifndef UNDERGRADUATE_HPP
#define UNDERGRADUATE_HPP

#include "student.hpp"
#include <string>
#include <vector>

/**
* @brief Undergraduate is-a Student:
*/
class Undergraduate : public Student {
private:
  std::string udorm; // dormitory name
  std::string uyear; // year in college (Freshman, Sophomore, Junior, Senior)
  static int ucount; // how many enrolled undergraduates?

public:
/**
* @brief Constructor for an Undergraduate student.
* The ctor parses comma-separated line starting with character 'U' and
* sets up general Student part plus specialized undergraduate information.
* This function must use the Student(std::string&) ctor to set up the
* general Student information consisting of id, name, yob, project grade,
* unknown number of homework grades.
* Then, this ctor will add the dormitory name and college year. Further,
* the ctor will increment the static data member ucount that keeps track
* of how many undergraduates are enrolled.
*
* @param line Line of comma-separated text from input file
*/
  Undergraduate(std::string& line);

// Each Undergraduate is unique. Therefore, they cannot be default constructed
// nor can there be replicas of an Undergraduate object.
  Undergraduate() = default;
  Undergraduate(Undergraduate const&) = delete;
  Undergraduate& operator=(Undergraduate const&) = delete;
  virtual ~Undergraduate() = default;

/**
* @brief Accessor for a student's residence hall.
*
* @return The residence hall in which the student resides.
*/
  std::string dormitory() const;

/**
* @brief Accessor for a student's year in college.
*
* @return The year in college of the student.
*/
  std::string year() const;

/**
* @brief Get the total number of undergraduate students.
* Note that this is a static member function that should
* return the current value of static data member ucount.
*
* @return The number of undergraduate students.
*/
  static int count();

/**
* @brief Prints the details of Undergraduate Student using
* Student::print_details() to print Student details.
* In addition to the fields printed by Student::print_details(), this function
* should print type of student (Undergraduate Student), residence hall, and 
* year in college (Freshman, Sophomore, Junior, Senior).
*
* @example Your function must follow this format to print details of
* a student:
* Id = 12
* Name = Rob Holding
* Age = 26
* Project = 72
* Assignment = [71, 62, 83, 74, 86, 82, 77]
* Total = 75.1
* Grade = CR
* Type = Undergraduate Student
* Residence Hall = England Hall
* Year in College = Senior
*/
  virtual void print_details() const override;

/**
* @brief Get the total score of a student.
*  Algorithm for computing total score for Undergraduate students is:
*  Mean of homework grades is worth 70% of total score;
*  Project score           is worth 30% of total score.
* @return The total score of the student.
*/
  virtual double total_score() const override;

/**
* @brief Computes letter grade obtained by a student.
* Algorithm for computing letter grade for Undergraduate students is:
* Letter grade N  if total grade < 70 and
* letter grade CR if total grade >= 70 
* @return The letter grade of the student.
*
* Note: It can be hard to keep track of which derived class functions
* are meant to override which base class functions. Fortunately, we
* can get compiler help to check. We can explicitly declare that a
* function is meant to override. Assuming that the derived class
* functions were meant to override, we can say so by adding override.
* Explicit use of override is particularly useful in large, complicated
* class hierarchies.
*/
  virtual std::string course_grade() const override;
};

#endif // end #ifndef UNDERGRADUATE_HPP
