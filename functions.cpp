#include "functions.h"

void pildymasKonsoleje(vector<Studentas> &studentai)
{
    char testi;
    Studentas temp;

    do
    {
        duomenuIvedimas(temp);
        studentai.push_back(temp);

        do
        {
            cout << "Ar norite pridėti dar vieną studentą? (t - taip, n - ne) " << endl;
            cin >> testi;
        } while (testi != 't' && testi != 'n');
    } while (testi == 't');
}

void duomenuIvedimas(Studentas &temp)
{
    cout << "Įveskite vardą ir pavardę: " << endl;
    cin >> temp.vardas >> temp.pavarde;

    cout << "Įveskite pažymius (jei daugiau pažymių nėra, įveskite bet kokią raidę):" << endl;

    Pazymiai pazymiai;

    int p = 0;

    while (cin >> p)
    {
        if (p >= 0 && p <= 10)
        {
            pazymiai.nd.push_back(p);
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

    cout << "įveskite egzamino pažymį: " << endl;
    cin >> pazymiai.egz;

    while (pazymiai.egz > 10 or pazymiai.egz < 0 or cin.fail())
    {
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout << "Egzamino pažymys turi būti dešimtbalėje sistemoje" << endl;
        cout << "Iveskite egzamino pažymį: " << endl;
        cin >> pazymiai.egz;
    }

    temp.vidurkis = vidurkioSkaiciavimas(pazymiai);
    temp.mediana = medianosSkaiciavimas(pazymiai);
    pazymiai.nd.clear();

    cout << "Duomenys įrašyti" << endl;
}

void generuotiAtsitiktinius(vector<Studentas> &studentai)
{

    int studentuKiekis = 0;
    int pazymiuKiekis = 0;
    while (true)
    {
        cout << "Kiek studentų norite generuoti?" << endl;
        cin >> studentuKiekis;
        if (cin.fail() || studentuKiekis <= 0)
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
        cin >> pazymiuKiekis;
        if (cin.fail() || pazymiuKiekis < 0)
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

    studentai.reserve(studentuKiekis);

    Studentas temp;
    Pazymiai pazymiai;
    pazymiai.nd.reserve(pazymiuKiekis);

    for (int i = 0; i < studentuKiekis; ++i)
    {
        temp.vardas = "vardas" + to_string(i);
        temp.pavarde = "pavarde" + to_string(i);
        for (int j = 0; j < pazymiuKiekis; j++)
            pazymiai.nd.push_back(dist(mt));
        pazymiai.egz = dist(mt);
        temp.vidurkis = vidurkioSkaiciavimas(pazymiai);
        temp.mediana = medianosSkaiciavimas(pazymiai);
        pazymiai.nd.clear();
        studentai.push_back(temp);
    }
}

void failoGeneravimas()
{

    int studentuKiekis = 0;
    
    while (true)
    {
        cout << "Kiek studentų norite generuoti?" << endl;
        cin >> studentuKiekis;
        if (cin.fail() || studentuKiekis <= 0 || studentuKiekis > 10000000)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Įveskite studentų kiekį, kad 0<studentų_kiekis<10.000.000" << endl;
        }
        else
            break;
    }


    int pazymiuKiekis = 0;
    while (true)
    {
        cout << "Kiek pažymių norite generuoti kiekvienam studentui?" << endl;
        cin >> pazymiuKiekis;
        if (cin.fail() || pazymiuKiekis <= 0 || pazymiuKiekis > 10000000)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Įveskite pažymių kiekį, kad 0<pažymių_kiekis<20" << endl;
        }
        else
            break;
    }

    string filename = "studentai" + to_string(studentuKiekis) + ".txt";

    std::chrono::high_resolution_clock::time_point start_time, end_time;
    start_time = high_resolution_clock::now();

    ofstream out(filename);

    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(0, 10);

    out << setw(15) << left << "Vardas" << setw(20) << left << "Pavardė";

    for (int i = 1; i <= pazymiuKiekis; i++)
        out << "ND" << setw(3) << left << i;

    out << "Egzaminas" << endl;

    unique_ptr<ostringstream> oss(new ostringstream());

    for (int i = 1; i <= studentuKiekis; i++)
    {
        (*oss) << "Vardas" << setw(9) << left << i << "Pavardė" << setw(12) << left << i;
        for (int j = 0; j < pazymiuKiekis; j++)
            (*oss) << setw(5) << left << dist(mt);

        (*oss) << dist(mt) << endl;
        if ((i + 1) % 10 == 0 || i == studentuKiekis)
        {
            out << oss->str();
            oss->str("");
        }
        if (i % (studentuKiekis / 100) == 0)
            cout << 100 * i / studentuKiekis << "%" << endl;
    }
    end_time = high_resolution_clock::now();
    duration<double> dur = end_time - start_time;
    cout<<"Atsitiktinių pažymių failas 'studentai"<<studentuKiekis<<".txt' sugeneruotas"<<endl;
    cout<< dur.count() <<" s"<< endl;
}

void failoSkaitymas(vector<Studentas> &studentai, string const &filename)
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
    int pazymiuKiekis = count(line.begin(), line.end(), 'N');

    Studentas temp;
    Pazymiai pazymiai;
    pazymiai.nd.reserve(pazymiuKiekis);
    int p;

    while (in >> temp.vardas)
    {
        in >> temp.pavarde;
        for (int i = 0; i < pazymiuKiekis; ++i)
        {
            in >> p;
            pazymiai.nd.push_back(p);
        }
        in >> pazymiai.egz;
        temp.vidurkis = vidurkioSkaiciavimas(pazymiai);
        temp.mediana = medianosSkaiciavimas(pazymiai);
        pazymiai.nd.clear();
        studentai.push_back(temp);
    }

    // while (std::getline(in, line))
    // {
    //     std::stringstream ss(line);
    //     ss >> temp.vardas >> temp.pavarde;
    //     for (int i = 0; i < pazymiuKiekis; ++i)
    //     {
    //         ss>>p;
    //         pazymiai.nd.push_back(p);
    //     }
    //     ss >> pazymiai.egz;
    //     temp.vidurkis = vidurkioSkaiciavimas(pazymiai);
    //     temp.mediana = medianosSkaiciavimas(pazymiai);
    //     pazymiai.nd.clear();
    //     studentai.push_back(temp);
    // }

    in.close();
}

void rikiavimas(vector<Studentas> &studentai, string const &sortType)
{
    cout<<"Duomenys rikiuojami pagal "<<sortType<<endl;
    if (sortType == "name")
        sort(studentai.begin(), studentai.end(), compareName);
    else if (sortType == "grade")
        sort(studentai.begin(), studentai.end(), compareGrade);
}

void spausdinimas(vector<Studentas> &studentai, string const &filename)
{
    cout<<"Duomenys išvedami..."<<endl;

    ofstream out(filename);

    unique_ptr<ostringstream> oss(new ostringstream());

    (*oss) << setw(15) << left << "Vardas" << setw(20) << left << "Pavardė" << setw(18) << left << "Galutinis (Vid.)" << setw(18) << left << "Galutinis (Med.)" << endl
           << "----------------------------------------------------------------" << endl;
    out << oss->str();
    oss->str("");

    for (int i = 0; i < studentai.size(); ++i)
    {
        (*oss) << setw(15) << left << studentai[i].vardas << setw(20) << left << studentai[i].pavarde << setw(18) << left << setprecision(3) << studentai[i].vidurkis << setw(18) << left << setprecision(3) << studentai[i].mediana << endl;
        if ((i + 1) % 10 == 0 || i + 1 == studentai.size())
        {
            out << oss->str();
            oss->str("");
        }
    }

    out.close();
    studentai.clear();
}

float vidurkioSkaiciavimas(Pazymiai &temp)
{
    float vidurkis;
    vidurkis = temp.nd.size() != 0 ? accumulate(temp.nd.begin(), temp.nd.end(), 0.0) / temp.nd.size() : 0.0;
    return vidurkis * 0.4 + temp.egz * 0.6;
}

float medianosSkaiciavimas(Pazymiai &temp)
{
    float mediana = 0;

    if (temp.nd.size() != 0)
    {
        sort(temp.nd.begin(), temp.nd.end());
        mediana = temp.nd.size() % 2 == 1 ? temp.nd[(temp.nd.size()) / 2] : (temp.nd[(temp.nd.size()) / 2 - 1] + temp.nd[(temp.nd.size()) / 2]) * 1.0 / 2.0;
    }
    return 0.4 * mediana + 0.6 * temp.egz;
} 

bool compareName(const Studentas &a, const Studentas &b)
{
    if (a.pavarde == b.pavarde)
        return a.vardas < b.vardas;
    else
        return a.pavarde < b.pavarde;
}

bool compareGrade(const Studentas &a, const Studentas &b)
{
    return a.vidurkis < b.vidurkis;
}

vector<Studentas> splittinimas(vector<Studentas> &studentai)
{
    cout<<"Duomenys dalinami"<<endl;
    auto it = std::find_if(studentai.begin(), studentai.end(), [](const auto &s) { return s.vidurkis >= 5; });
    vector<Studentas> temp (it, studentai.end());
    studentai.resize(studentai.size()-temp.size());
    return temp;
}

void splittinimas2(vector<Studentas> &studentai, vector<Studentas> &studPass, vector<Studentas> &studFail)
{
    cout << "Duomenys dalinami" << endl;
    auto it = std::find_if(studentai.begin(), studentai.end(), [](const auto &s) { return s.vidurkis >= 5; });
    studPass.resize(std::distance(it, studentai.end()));
    copy(it, studentai.end(), studPass.begin());
    std::advance(it, -1);
    studFail.resize(std::distance(studentai.begin(), it));
    copy(studentai.begin(), it, studFail.begin());
    studentai.clear();
}