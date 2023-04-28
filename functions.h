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

class Student
{
private:
    string name, surname;
    float average, median;

public:
    Student(string nam, string sur, vector<int> &homeworkGrades, int examGrade)
    {
        name = nam;
        surname = sur;
        average = countFinal(countAverage(homeworkGrades), examGrade);
        median = countFinal(countMedian(homeworkGrades), examGrade);
        homeworkGrades.clear();
    }
    Student(string nam, string sur, float avg, float med)
    {
        name = nam;
        surname = sur;
        average = avg;
        median = med;
    }
    Student(const Student &other)
    {
        this->name = other.name;
        this->surname = other.surname;
        this->average = other.average;
        this->median = other.median;
    }
    Student(Student &&other)
    {
        this->name = move(other.name);
        this->surname = move(other.surname);
        this->average = move(other.average);
        this->median = move(other.median);
    }
    Student()
    {
        name = "";
        surname = "";
        average = 0.0;
        median = 0.0;
    }

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
            average = other.average;
            median = other.median;

            other = Student();
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

void generateRandom(vector<Student> &students);
void consoleFill(vector<Student> &students);
void print(vector<Student> &students, string const &filename);
void printBoth(vector<Student> &students1, string const &filename1, vector<Student> &students2, string const &filename2);
void readFile(vector<Student> &students, string const &filename);
void dataFill(vector<Student> &students);
bool compareName(const Student &a, const Student &b);
vector<Student> split(vector<Student> &students);
void generateFile();
