#include <iostream>
#include <ostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <limits>
#include <fstream>
#include <vector>
#include <random>
#include <string>
#include <chrono>
#include <sstream>
#include <iterator>
#include <filesystem>

using std::accumulate;
using std::cerr;
using std::cin;
using std::copy;
using std::count;
using std::cout;
using std::endl;
using std::exception;
using std::fixed;
using std::getline;
using std::ifstream;
using std::istream;
using std::left;
using std::move;
using std::mt19937;
using std::numeric_limits;
using std::ofstream;
using std::ostream;
using std::ostringstream;
using std::random_device;
using std::right;
using std::runtime_error;
using std::setprecision;
using std::setw;
using std::sort;
using std::streamsize;
using std::string;
using std::stringstream;
using std::swap;
using std::to_string;
using std::uniform_int_distribution;
using std::unique_ptr;
using std::vector;
using std::chrono::duration;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::chrono::milliseconds;
using std::chrono::seconds;

class Person
{
protected:
    string name, surname;
    
    Person(string nam, string sur)
    {
        name = nam;
        surname = sur;
    }
    Person()
    {
        name = "";
        surname = "";
    }
    virtual ~Person()
    {
        name.clear();
        surname.clear();
    }

    virtual string getName() const = 0;
};

class Student: public Person
{
private:
    float average, median;

public:
    Student(string nam, string sur, vector<int> &homeworkGrades, int examGrade) : Person(nam, sur)
    {
        average = countFinal(countAverage(homeworkGrades), examGrade);
        median = countFinal(countMedian(homeworkGrades), examGrade);
        homeworkGrades.clear();
    }

    Student(string nam, string sur, float avg, float med) : Person(nam, sur), average(avg), median(med)
    {}
    Student(const Student &other) : Person(other.name, other.surname), average(other.average), median(other.median)
    {}
    Student(Student &&other) : Person(std::move(other.name), std::move(other.surname)), average(std::move(other.average)), median(std::move(other.median))
    {}
    Student() : Person(), average(0.0), median(0.0)
    {}

    friend ostream &operator<<(std::ostream &out, const Student &s)
    {
        out << setw(15) << left << s.name << setw(20) << left << s.surname << setw(18) << left
            << setprecision(3) << s.average << setw(18) << left << setprecision(3) << s.median << endl;
        return out;
    }
    friend istream &operator>>(std::istream &in, vector<Student> &s)
    {
        string line;
        getline(in, line);
        if (!in)
        {
            return in;
        }

        stringstream ss(line);

        string name, surname;
        ss >> name >> surname;

        vector<int> homeworkGrades;
        int grade;
        while (ss >> grade)
        {
            homeworkGrades.push_back(grade);
        }

        int examGrade = homeworkGrades.back();
        homeworkGrades.pop_back();
        s.emplace_back(name, surname, homeworkGrades, examGrade);
        return in;
    }
    Student &operator=(const Student &other)
    {
        if (this != &other)
        {
            this->name = other.name;
            this->surname = other.surname;
            this->average = other.average;
            this->median = other.median;
        }
        return *this;
    }
    Student &operator=(Student &&other)
    {
        if (this != &other)
        {
            name = std::move(other.name);
            surname = std::move(other.surname);
            average = std::move(other.average);
            median = std::move(other.median);
        }
        return *this;
    }

    float countAverage(vector<int> const &homeworkGrades)
    {
        float average;
        average = homeworkGrades.size() != 0 ? accumulate(homeworkGrades.begin(), homeworkGrades.end(), 0.0) / homeworkGrades.size() : 0.0;
        return average;
    }
    float countMedian(vector<int> &homeworkGrades)
    {
        float median = 0;

        if (homeworkGrades.size() != 0)
        {
            sort(homeworkGrades.begin(), homeworkGrades.end());
            median = homeworkGrades.size() % 2 == 1 ? homeworkGrades[(homeworkGrades.size()) / 2] : (homeworkGrades[(homeworkGrades.size()) / 2 - 1] + homeworkGrades[(homeworkGrades.size()) / 2]) * 1.0 / 2.0;
        }
        return median;
    }
    float countFinal(float grade, int &exam)
    {
        return grade * 0.4 + exam * 0.6;
    }


    ~Student()
    {
        average=0;
        median=0;
    }

    string getName() const override
    {
        return name;
    }
    string getSurname() const
    {
        return surname;
    }
    float getAverage() const
    {
        return average;
    }
    float getMedian() const
    {
        return median;
    }
};

/// @brief Asks the user to input a number of students and a number of grades for each student, then puts them into a vector.
/// @return vector of integers, first element is the number of students, second is the number of grades for each student
vector<int> askRandomCount();

/// @brief Generates a file with students' list and their grades, generated randomly
/// @param count vector of integers, first element is the number of students, second is the number of grades for each student
void generateFile(vector<int> count);

/// @brief Asks the user how many students and how many grades for each to generate, then generates and puts them into a vector.
/// @param students vector of students
/// @param count vector of integers, first element is the number of students, second is the number of grades for each student
void generateRandom(vector<Student> &students, vector<int> count);

/// @brief Calls dataFill() function, after which it asks if there more students to be added. Function repeats until there are no more students to be added.
void consoleFill(vector<Student> &students);

/// @brief Asks the user to input student's name, surname and grades, then puts it into a vector.
/// @param students vector of students
void dataFill(vector<Student> &students);

/// @brief Tries to open a given file, if successful, reads the data from it and puts it into a vector.
/// @param students vector of students
/// @param filename filename to read from
void readFile(vector<Student> &students, string const &filename);

/// @brief Takes two students and compares their surname, returns true if a's surname is smaller than b's, false otherwise. If surnames are equal, checks their names.
/// @param a First student to compare
/// @param b Second student to compare
/// @return True if a's name is smaller than b's, false otherwise
bool compareName(const Student &a, const Student &b);

/// @brief Splits students into two vectors, one with passing grades, other with failing grades.
/// @param students vector of students
/// @return Vector of students with passing grades
vector<Student> split(vector<Student> &students);

/// @brief Takes two vectors and calls print() function for each of them
/// @param students1 vector of students that have a passing grade
/// @param students2 vector of students that have a failing grade
void printBoth(vector<Student> &students1, vector<Student> &students2);

/// @brief Takes a vector of students and prints it to a file, then clears the data from the vector
/// @param students vector of students
/// @param filename output filename
void print(vector<Student> &students, string const &filename);
