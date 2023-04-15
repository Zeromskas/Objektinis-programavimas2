#include "functions.h"

int main()
{
    vector<Studentas> studentai;

    int ivedimoTipas = 4;

    
    while (ivedimoTipas != 0 && ivedimoTipas != 1 && ivedimoTipas != 2 && ivedimoTipas != 3)
    {
        cout<<endl;
        cout<<"Pasirinkite, ką norite daryti: "<<endl;
        cout << left << setw(60) << "Skaityti duomenis iš esamo failo (0)"
             <<left<<setw(60)<<"Įvesti duomenis programoje (1)" << endl
             << left << setw(60)<<"Generuoti atsitiktinių pažymių failą (2)"
             <<left<<setw(60)<< "Generuoti ir iškart naudoti atsitiktinius (3)" << endl;
        cin >> ivedimoTipas;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            ivedimoTipas = 4;
        }
    }

    switch (ivedimoTipas)
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
                    failoSkaitymas(studentai, filename);
                    break;
                }
                catch (const exception &e)
                {
                    cerr << "Klaida: " << e.what() << endl;
                }
            }
            break;
        case 1:
            pildymasKonsoleje(studentai);
            break;
        case 2:
            failoGeneravimas();
            break;
        case 3:
            generuotiAtsitiktinius(studentai);
            break;
    }

    if (studentai.empty())
        return 0;

    rikiavimas(studentai, "grade");
    vector<Studentas> studPass=splittinimas(studentai);
    rikiavimas(studentai, "name");
    rikiavimas(studPass, "name");

    spausdinimas(studPass, "studPass.txt");
    studPass.clear();
    spausdinimas(studentai, "studFail.txt");
    studentai.clear();
    
    return 0;
}
