#include <iostream>
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


struct Studentas
{
    string vardas, pavarde;
    float vidurkis = 0;
    float mediana = 0;
};

struct Pazymiai
{
    vector<int> nd;
    int egz = 0;
};

float vidurkioSkaiciavimas(Pazymiai &temp);
float medianosSkaiciavimas(Pazymiai &temp);
void generuotiAtsitiktinius(vector<Studentas> &studentai);
void pildymasKonsoleje(vector<Studentas> &studentai);
void spausdinimas(vector<Studentas> &studentai, string const &filename);
void failoSkaitymas(vector<Studentas> &studentai, string const &filename);
void duomenuIvedimas(Studentas &temp);
bool compareName(const Studentas &a, const Studentas &b);
bool compareGrade(const Studentas &a, const Studentas &b);
vector<Studentas> splittinimas(vector<Studentas> &studentai);
void rikiavimas(vector<Studentas> &studentai, string const &sortType);
void failoGeneravimas();
void splittinimas2(vector<Studentas> &studentai, vector<Studentas> &studPass, vector<Studentas> &studFail);