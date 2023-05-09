#include "functions.h"

int main()
{
    cout<< std::filesystem::path(std::filesystem::current_path()).parent_path() <<endl;
    // time measuring
    std::chrono::high_resolution_clock::time_point total_start, total_end;
    duration<double> dur;

    vector<Student> students;

    int inputType = 4;

    while (inputType != 0 && inputType != 1 && inputType != 2 && inputType != 3)
    {
        cout << endl;
        cout << "Pasirinkite, ką norite daryti: " << endl;
        cout << left << setw(60) << "Skaityti duomenis iš esamo failo (0)"
             << left << setw(60) << "Įvesti duomenis programoje (1)" << endl
             << left << setw(60) << "Generuoti atsitiktinių pažymių failą (2)"
             << left << setw(60) << "Generuoti ir iškart naudoti atsitiktinius (3)" << endl;
        cin >> inputType;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            inputType = 4;
        }
    }

    switch (inputType)
    {
    case 0:
        while (true)
        {
            try
            {
                system("ls *.txt");
                string filename;
                cout << "Įveskite pažymių failo pavadinimą:" << endl;
                cin >> filename;
                total_start = std::chrono::high_resolution_clock::now();
                readFile(students, filename);
                break;
            }
            catch (const exception &e)
            {
                cerr << "Klaida: " << e.what() << endl;
            }
        }
        break;
    case 1:
        consoleFill(students);
        total_start = std::chrono::high_resolution_clock::now();
        break;
    case 2:
        total_start = std::chrono::high_resolution_clock::now();
        generateFile(askRandomCount());
        break;
    case 3:
        total_start = std::chrono::high_resolution_clock::now();
        generateRandom(students, askRandomCount());
        break;
    }

    if (students.empty())
        return 0;

    sort(students.begin(), students.end(), compareName);
    vector<Student> studPass = split(students);

    printBoth(studPass, students);

    total_end = std::chrono::high_resolution_clock::now();

    dur = total_end - total_start;

    cout << "Duomenų apdorojimas užtruko: " << dur.count() << " s" << endl;

    return 0;
}
