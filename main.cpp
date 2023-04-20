#include "functions.h"

int main()
{
    vector<Student> students;

    int inputType = 4;

    while (inputType != 0 && inputType != 1 && inputType != 2 && inputType != 3)
    {
        cout<<endl;
        cout<<"Pasirinkite, ką norite daryti: "<<endl;
        cout << left << setw(60) << "Skaityti duomenis iš esamo failo (0)"
             <<left<<setw(60)<<"Įvesti duomenis programoje (1)" << endl
             << left << setw(60)<<"Generuoti atsitiktinių pažymių failą (2)"
             <<left<<setw(60)<< "Generuoti ir iškart naudoti atsitiktinius (3)" << endl;
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
            break;
        case 2:
            generateFile();
            break;
        case 3:
            generateRandom(students);
            break;
    }

    if (students.empty())
        return 0;

    sort(students, "grade");
    vector<Student> studPass=split(students);
    sort(students, "name");
    sort(studPass, "name");

    print(studPass, "studPass.txt");
    studPass.clear();
    print(students, "studFail.txt");
    students.clear();
    
    return 0;
}
