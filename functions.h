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
using std::left;
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



class Student
{
private:
    string name, surname;
    float average = 0;
    float median = 0;

public:
    Student(string nam, string sur, float avg, float med)
    {
        name = nam;
        surname = sur;
        average = avg;
        median = med;
    }
    Student()
    {
        name = "";
        surname = "";
        average = 0;
        median = 0;
    }

    friend ostream &operator<<(std::ostream &out, const Student &s)
    {
        out << setw(15) << left << s.name << setw(20) << left << s.surname << setw(18) << left
            << setprecision(3) << s.average << setw(18) << left << setprecision(3) << s.median << endl;
        return out;
    }

    string getName() const
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

float countAverage(vector<int> &homeworkGrades);
float countMedian(vector<int> &homeworkGrades);
float countFinal(float grade, int &exam);
void generateRandom(vector<Student> &students);
void consoleFill(vector<Student> &students);
void print(vector<Student> &students, string const &filename);
void readFile(vector<Student> &students, string const &filename);
Student dataFill();
bool compareName(const Student &a, const Student &b);
bool compareGrade(const Student &a, const Student &b);
vector<Student> split(vector<Student> &students);
void sort(vector<Student> &students, string const &sortType);
void generateFile();
