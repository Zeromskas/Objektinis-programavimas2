#include "functions.h"

void consoleFill(vector<Student> &students)
{
    char addMore;

    do
    {
        students.push_back(dataFill());

        do
        {
            cout << "Ar norite pridėti dar vieną studentą? (t - taip, n - ne) " << endl;
            cin >> addMore;
        } while (addMore != 't' && addMore != 'n');
    } while (addMore == 't');
}

Student dataFill()
{
    string name, surname;
    cout << "Įveskite vardą ir pavardę: " << endl;
    cin >> name >> surname;

    cout << "Įveskite pažymius (jei daugiau pažymių nėra, įveskite bet kokią raidę):" << endl;

    Grades grades;

    int grade = 0;

    while (cin >> grade)
    {
        if (grade >= 0 && grade <= 10)
        {
            grades.homeworkGrades.push_back(grade);
        }
        else
        {
            cout << "Pažymys turi būti tarp 0 ir 10. Bandykite dar kartą: " << endl;
        }
    }

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Įveskite egzamino pažymį: " << endl;
    cin >> grades.examGrade;

    while (grades.examGrade > 10 or grades.examGrade < 0 or cin.fail())
    {
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout << "Egzamino pažymys turi būti dešimtbalėje sistemoje" << endl;
        cout << "Iveskite egzamino pažymį: " << endl;
        cin >> grades.examGrade;
    }

    float average = countAverage(grades);
    float median = countMedian(grades);
    grades.homeworkGrades.clear();

    Student temp(name, surname, average, median);
    cout << "Duomenys įrašyti" << endl;
    return temp;
}

void generateRandom(vector<Student> &students)
{

    int studentCount = 0;
    int gradeCount = 0;
    while (true)
    {
        cout << "Kiek studentų norite generuoti?" << endl;
        cin >> studentCount;
        if (cin.fail() || studentCount <= 0)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Studentų kiekis turi būti sveikas skaičius, didesnis už 0." << endl;
        }
        else
            break;
    }

    while (true)
    {
        cout << "Kiek pažymių norite generuoti kiekvienam studentui?" << endl;
        cin >> gradeCount;
        if (cin.fail() || gradeCount < 0)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Pažymių kiekis turi būti teigiamas sveikasis skaičius." << endl;
        }
        else
            break;
    }
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(0, 10);

    cout << "Duomenys generuojami..." << endl;

    students.reserve(studentCount);

    Grades grades;
    grades.homeworkGrades.reserve(gradeCount);

    for (int i = 0; i < studentCount; ++i)
    {
        string name = "Vardas" + to_string(i);
        string surname = "Pavardė" + to_string(i);
        for (int j = 0; j < gradeCount; j++)
            grades.homeworkGrades.push_back(dist(mt));
        grades.examGrade = dist(mt);
        float average = countAverage(grades);
        float median = countMedian(grades);
        grades.homeworkGrades.clear();
        students.push_back(Student(name, surname, average, median));
    }
}

void generateFile()
{
    int studentCount = 0;
    
    while (true)
    {
        cout << "Kiek studentų norite generuoti?" << endl;
        cin >> studentCount;
        if (cin.fail() || studentCount <= 0 || studentCount > 10000000)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Įveskite studentų kiekį, kad 0<studentų_kiekis<10.000.000" << endl;
        }
        else
            break;
    }


    int gradeCount = 0;
    while (true)
    {
        cout << "Kiek pažymių norite generuoti kiekvienam studentui?" << endl;
        cin >> gradeCount;
        if (cin.fail() || gradeCount <= 0 || gradeCount > 10000000)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Įveskite pažymių kiekį, kad 0<pažymių_kiekis<20" << endl;
        }
        else
            break;
    }

    string filename = "studentai" + to_string(studentCount) + ".txt";

    std::chrono::high_resolution_clock::time_point start_time, end_time;
    start_time = high_resolution_clock::now();

    ofstream out(filename);

    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(0, 10);

    out << setw(15) << left << "Vardas" << setw(20) << left << "Pavardė";

    for (int i = 1; i <= gradeCount; i++)
        out << "ND" << setw(3) << left << i;

    out << "Egzaminas" << endl;

    unique_ptr<ostringstream> oss(new ostringstream());

    for (int i = 1; i <= studentCount; i++)
    {
        (*oss) << "Vardas" << setw(9) << left << i << "Pavardė" << setw(12) << left << i;
        for (int j = 0; j < gradeCount; j++)
            (*oss) << setw(5) << left << dist(mt);

        (*oss) << dist(mt) << endl;
        if ((i + 1) % 10 == 0 || i == studentCount)
        {
            out << oss->str();
            oss->str("");
        }
        if (i % (studentCount / 100) == 0)
            cout << 100 * i / studentCount << "%" << endl;
    }
    end_time = high_resolution_clock::now();
    duration<double> dur = end_time - start_time;
    cout<<"Atsitiktinių pažymių failas 'studentai"<<studentCount<<".txt' sugeneruotas"<<endl;
    cout<< dur.count() <<" s"<< endl;
}

void readFile(vector<Student> &students, string const &filename)
{
    ifstream in(filename);

    if (!in.is_open())
    {
        throw runtime_error("Nepavyko atidaryti failo!");
    }
    cout<<filename<<endl;
    cout << "Duomenys nuskaitomi..." << endl;

    string line;
    getline(in, line);
    int gradeCount = count(line.begin(), line.end(), 'N');

    
    Grades grades;
    grades.homeworkGrades.reserve(gradeCount);
    int grade;
    string name, surname;
    float average, median;

    while (in >> name)
    {
        in >> surname;
        for (int i = 0; i < gradeCount; ++i)
        {
            in >> grade;
            grades.homeworkGrades.push_back(grade);
        }
        in >> grades.examGrade;
        average = countAverage(grades);
        median = countMedian(grades);
        grades.homeworkGrades.clear();
        students.push_back(Student(name, surname, average, median));
    }
    in.close();
}

void sort(vector<Student> &students, string const &sortType)
{
    cout<<"Duomenys rikiuojami pagal "<<sortType<<endl;
    if (sortType == "name")
        sort(students.begin(), students.end(), compareName);
    else if (sortType == "grade")
        sort(students.begin(), students.end(), compareGrade);
}

void print(vector<Student> &students, string const &filename)
{
    cout<<"Duomenys išvedami..."<<endl;

    ofstream out(filename);

    unique_ptr<ostringstream> oss(new ostringstream());

    (*oss) << setw(15) << left << "Vardas" << setw(20) << left << "Pavardė" << setw(18) << left << "Galutinis (Vid.)" << setw(18) << left << "Galutinis (Med.)" << endl
           << "----------------------------------------------------------------" << endl;
    out << oss->str();
    oss->str("");

    for (int i = 0; i < students.size(); ++i)
    {
        (*oss) << students[i];
        if ((i + 1) % 10 == 0 || i + 1 == students.size())
        {
            out << oss->str();
            oss->str("");
        }
    }

    out.close();
    students.clear();
}

float countAverage(Grades &temp)
{
    float average;
    average = temp.homeworkGrades.size() != 0 ? accumulate(temp.homeworkGrades.begin(), temp.homeworkGrades.end(), 0.0) / temp.homeworkGrades.size() : 0.0;
    return average * 0.4 + temp.examGrade * 0.6;
}

float countMedian(Grades &temp)
{
    float median = 0;

    if (temp.homeworkGrades.size() != 0)
    {
        sort(temp.homeworkGrades.begin(), temp.homeworkGrades.end());
        median = temp.homeworkGrades.size() % 2 == 1 ? temp.homeworkGrades[(temp.homeworkGrades.size()) / 2] : (temp.homeworkGrades[(temp.homeworkGrades.size()) / 2 - 1] + temp.homeworkGrades[(temp.homeworkGrades.size()) / 2]) * 1.0 / 2.0;
    }
    return 0.4 * median + 0.6 * temp.examGrade;
} 

bool compareName(const Student &a, const Student &b)
{
    if (a.getSurname() == b.getSurname())
        return a.getName() < b.getName();
    else
        return a.getSurname() < b.getSurname();
}

bool compareGrade(const Student &a, const Student &b)
{
    return a.getAverage() < b.getAverage();
}

vector<Student> split(vector<Student> &students)
{
    cout<<"Duomenys dalinami"<<endl;
    auto it = std::find_if(students.begin(), students.end(), [](const auto &s) { return s.getAverage() >= 5; });
    vector<Student> temp (it, students.end());
    students.resize(students.size()-temp.size());
    return temp;
}
