#include "functions.h"

std::filesystem::path exe_dir = std::filesystem::path(std::filesystem::current_path()).parent_path();

std::chrono::high_resolution_clock::time_point start_time, end_time;
duration<double> dur;


void consoleFill(vector<Student> &students)
{
    char addMore;

    do
    {
        dataFill(students);

        do
        {
            cout << "Ar norite pridėti dar vieną studentą? (t - taip, n - ne) " << endl;
            cin >> addMore;
        } while (addMore != 't' && addMore != 'n');
    } while (addMore == 't');
}

void dataFill(vector<Student> &students)
{
    string name, surname;
    cout << "Įveskite vardą ir pavardę: " << endl;
    cin >> name >> surname;

    cout << "Įveskite pažymius (jei daugiau pažymių nėra, įveskite bet kokią raidę):" << endl;

    vector<int> homeworkGrades;

    int grade = 0;

    while (cin >> grade)
    {
        if (grade >= 0 && grade <= 10)
        {
            homeworkGrades.push_back(grade);
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
    cin >> grade;

    while (grade > 10 or grade < 0 or cin.fail())
    {
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout << "Egzamino pažymys turi būti dešimtbalėje sistemoje" << endl;
        cout << "Iveskite egzamino pažymį: " << endl;
        cin >> grade;
    }

    students.emplace_back(name, surname, homeworkGrades, grade);

    cout << "Duomenys įrašyti" << endl;
}

vector<int> askRandomCount()
{
    vector<int> answer; // answer vector (0 - student count, 1 - grade count)
    answer.reserve(2);

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
    answer.push_back(studentCount);

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
    answer.push_back(studentCount);

    return answer;
}

void generateRandom(vector<Student> &students, vector<int> count)
{
    start_time = high_resolution_clock::now();

    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(0, 10);

    cout << "Duomenys generuojami: ";

    students.reserve(count[0]);

    vector<int> homeworkGrades;

    homeworkGrades.reserve(count[1]);

    for (int i = 0; i < count[0]; ++i)
    {
        for (int j = 0; j < count[1]; j++)
            homeworkGrades.push_back(dist(mt));
        students.emplace_back("Vardas" + to_string(i), "Pavardė" + to_string(i), homeworkGrades, dist(mt));
    }

    end_time = high_resolution_clock::now();
    dur = end_time - start_time;
    cout << dur.count() << " seconds";

    cout << endl;
}

void generateFile(vector<int> count)
{


    string filename = "studentai" + to_string(count[0]) + ".txt";

    start_time = high_resolution_clock::now();

    ofstream out(exe_dir / filename);

    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(0, 10);

    out << setw(15) << left << "Vardas" << setw(20) << left << "Pavardė";

    for (int i = 1; i <= count[1]; i++)
        out << "ND" << setw(3) << left << i;

    out << "Egzaminas" << endl;

    unique_ptr<ostringstream> oss(new ostringstream());

    bool displayPercentage = count[0] > 100;

    for (int i = 1; i <= count[0]; i++)
    {
        (*oss) << "Vardas" << setw(9) << left << i << "Pavardė" << setw(12) << left << i;
        for (int j = 0; j < count[1]; j++)
            (*oss) << setw(5) << left << dist(mt);

        (*oss) << dist(mt) << endl;
        if ((i + 1) % 10 == 0 || i == count[0])
        {
            out << oss->str();
            oss->str("");
        }
        if (displayPercentage)
            if (i % (count[0] / 100) == 0)
                cout << 100 * i / count[0] << "%" << endl;
    }
    end_time = high_resolution_clock::now();
    dur = end_time - start_time;
    cout << "Atsitiktinių pažymių failas 'studentai" << count[0] << ".txt' sugeneruotas ("<< exe_dir / filename <<")" << endl;
    cout << dur.count() << " seconds";

    cout << endl;
}

void readFile(vector<Student> &students, string const &filename)
{


    ifstream in(exe_dir / filename);

    if (!in.is_open())
    {
        throw runtime_error("Nepavyko atidaryti failo!");
    }
    cout << exe_dir / filename << endl;
    cout << "Duomenys nuskaitomi: ";

    start_time = high_resolution_clock::now();

    string line;
    getline(in, line);

    while (in >> students);

    in.close();

    end_time = high_resolution_clock::now();
    dur = end_time - start_time;
    cout << dur.count() << " seconds";

    cout << endl;
}

void printBoth(vector<Student> &students1, vector<Student> &students2)
{
    cout << "Duomenys išvedami: ";
    start_time = high_resolution_clock::now();

    print(students1, "studPass.txt");
    print(students2, "studFail.txt");

    end_time = high_resolution_clock::now();
    dur = end_time - start_time;
    cout << dur.count() << " seconds";

    cout << endl;
}

void print(vector<Student> &students, string const &filename)
{
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
    students.shrink_to_fit();
}

bool compareName(const Student &a, const Student &b)
{
    if (a.getSurname() == b.getSurname())
        return a.getName() < b.getName();
    else
        return a.getSurname() < b.getSurname();
}

vector<Student> split(vector<Student> &students)
{
    start_time = high_resolution_clock::now();

    cout << "Duomenys dalinami: ";
    auto it = std::stable_partition(students.begin(), students.end(), [](const auto &s)
                                    { return s.getAverage() < 5; });
    vector<Student> temp(it, students.end());
    students.resize(students.size() - temp.size());
    students.shrink_to_fit();

    end_time = high_resolution_clock::now();
    dur = end_time - start_time;
    cout << dur.count() << " seconds";

    cout << endl;

    return temp;
}
