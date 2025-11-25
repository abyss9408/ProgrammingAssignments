///////////////////////////////////////////////////////////////////////////////
// File Name:      student.hpp
//
// Description:    The header file for class Student.
//
// IMPORTANT NOTE: You will not submit this file - therefore you should NOT 
//                 modify this file.
///////////////////////////////////////////////////////////////////////////////

#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <string>
#include <vector>
#include <chrono>
#include <ctime>

/**
* @brief An abstract base class for a Student.
*/
class Student {
private:
  int sid;                 // a student's unique id.
  std::string sname;       // a student's name
  int syob;                // a student's year of birth
  double sproj;            // a student's grade for project work
  std::vector<double> shw; // a student's homework grades
  static int scount;       // how many enrolled students?

protected:
/**
* @brief Computes mean/average of values in container assignmentsScore
* @param none
* @return Mean/average of values in assignmentScore
*/
  double hw_mean() const;

public:
/**
* @brief A constructor for a Student that parses student information from one
* line of comma-separated file.
* This ctor will parse the line for information common to all students:
* Name of student, Year of birth, Project score, Unknown count of homework grades.
*
*    U,Tom Sawyer,1993,89 55 71 71 63 60 78 83,Eastwood,Senior
* If the ctor's parameter consists of this sequence of characters:
*    G,Rex Fernando,1997,68 57 90 81 96 80 95 78 67 86,Cryptography,Amit Sahai
* the ctor must extract this common information: Rex Fernando (name), 
* 1997 (year of birth), 68 (project grade), and nine homework grades
* (57 90 81 96 80 95 78 67 86) and assign this information to the appropriate
* data members.
*
* If the ctor's parameter consists of this sequence of characters:
*    U,Tom Sawyer,1993,89 55 71 71 63 60 78 83,Eastwood,Senior
* the ctor must extract this common information: Tom Sawyer (name), 
* 1993 (year of birth), 89 (project grade), and seven homework grades
* (55 71 71 63 60 78 83) and assign this information to the appropriate
* data members.
* NOTE: The number of homework grades for a student (irrespective of whether
* they're graduate or undergraduate) is unknown - we can only know this
* count when the line is parsed.
*
* In addition, the function must increment static data member Student::scount.
* Note that the input file doesn't specify a student id. Instead, this ctor will
* generate a monotonically increasing ID for a student based on their order in
* the input file. The IDs are non-zero and start with 1. That is, the first
* student encountered will be assigned an ID of 1, the second student encountered
* will be assigned an ID of 2, and so on.
*
* @param line Line of comma-separated text from input file
*/
  Student(std::string& line);

// Each Student is unique. Therefore, they cannot be default constructed
// nor can there be replicas of a Student.
  Student() = default;
  Student(Student const&) = delete;
  Student& operator=(Student const&) = delete;
  virtual ~Student() = default;

/**
* @brief Accessor for student's id.
*
* @return The id of the student.
*/
  int id() const;

/**
* @brief Accessor for student's name.
*
* @return The name of the student.
*/
  std::string name() const;

/**
* @brief Accessor for student's year of birth.
*
* @return The year of birth of the student.
*/
  int yob() const;

/**
* @brief Computes student's age.
* This function uses student's year of birth in data member syob and the
* current year (determined from C++ standard library) to compute the 
* student's age.
*
* @return The student's age.
*/
  int age() const {
    std::time_t now_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    struct tm *chrono_timeinfo = std::localtime(&now_time);
    int x = 1900 + chrono_timeinfo->tm_year;
    return x - syob;
  }

/**
* @brief Accessor for student's project score.
*
* @return The project score of the student.
*/
  double project_score() const;

/**
* @brief Get the count of students.
* Note that this is a static member function that should
* return the current value of static data member scount.
*
* @return Student count.
*/
  static int count();

/**
* @brief Prints the details of Student.
* This method prints the common information about a student:
* id, name, age (this member function is defined for you), project score, 
* homework assignment grades, total grade (call the virtual function
* total_score() that must be implemented by derived class), and the
* course grade (call the virtual function course_grade() that must be
* implemented by derived class).
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
*/
  virtual void print_details() const;

/**
* @brief Get the total score of a student. 
* Student class will not define this function!!! Instead, since this is a
* pure virtual function, the derived class will implement this function. 
* @return Total score of student computed from project and homework grades.
*/
  virtual double total_score() const = 0;

/**
* @brief Computes letter grade obtained by a student.
* Student class will not define this function!!! Instead, since this is a
* pure virtual function, the derived class will implement this function.
* @return The letter grade of the student.
*         Possible letter grades are "CR" and "N".
*/
  virtual std::string course_grade() const = 0;
};

#endif // end #ifndef STUDENT_HPP
