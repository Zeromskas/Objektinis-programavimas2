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

struct Pazymiai
{
    vector<int> nd;
    int egz = 0;
};

class Studentas
{
private:
    string vardas, pavarde;
    float vidurkis = 0;
    float mediana = 0;

public:
    Studentas(string vard, string pav, float vid, float med)
    {
        vardas = vard;
        pavarde = pav;
        vidurkis = vid;
        mediana = med;
    }
    Studentas()
    {
        vardas = "";
        pavarde = "";
        vidurkis = 0;
        mediana = 0;
    }
    
    friend ostream &operator<<(std::ostream &out, const Studentas &s)
    {
        out << setw(15) << left << s.vardas << setw(20) << left << s.pavarde << setw(18) << left << setprecision(3) << s.vidurkis << setw(18) << left << setprecision(3) << s.mediana << endl;
        return out;
    }

    string getVardas() const
    {
        return vardas;
    }
    string getPavarde() const
    {
        return pavarde;
    }
    float getVidurkis() const
    {
        return vidurkis;
    }
    float getMediana() const
    {
        return mediana;
    }
};



float vidurkioSkaiciavimas(Pazymiai &temp);
float medianosSkaiciavimas(Pazymiai &temp);
void generuotiAtsitiktinius(vector<Studentas> &studentai);
void pildymasKonsoleje(vector<Studentas> &studentai);
void spausdinimas(vector<Studentas> &studentai, string const &filename);
void failoSkaitymas(vector<Studentas> &studentai, string const &filename);
Studentas duomenuIvedimas();
bool compareName(const Studentas &a, const Studentas &b);
bool compareGrade(const Studentas &a, const Studentas &b);
vector<Studentas> splittinimas(vector<Studentas> &studentai);
void rikiavimas(vector<Studentas> &studentai, string const &sortType);
void failoGeneravimas();
