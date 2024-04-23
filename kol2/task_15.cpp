#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;
/*
Дадена е дел од дефиниција на класата StudentKurs. За секој студент кој слуша некој курс се чуваат информации за неговото име (низа од знаци), оценка од писмен дел (цел број) и дали студентот сака да биде испрашуван и усно (булова променлива).

Оцената за писмениот дел е вредност од 1 до МАX. MAX има почетна вредност 10 која е иста е за сите и може да се промени со соодветна функција setMAX(). (5 поени)

Кај оние студенти кои сакаат да бидат испрашувани усно и добиваат и описна оценка. Имплементирај соодветна класа StudentKursUsno во која се чуваат дополнителни информации за описна оценка на усното испрашување (динамичко алоцирана низа од знаци).
Описни оценки може да бидат: odlicen, dobro, losho.... Ако описната оценка е odlicen тогаш оцената ќе биде најмногу за оценки 2 повисока од оценката од писмениот дел, ако е dobro оценката ќе биде најмногу за 1 повисока, а ако е losho за 1 пониска.
Ако студентот добие некоја друга описна оценка, неговата оценка ќе остане иста со оценката од писмениот дел.

Во класите StudentKurs и StudentKursUsno треба да се имплементираат потребните конструктори, функции за поставување и преземање и деструктор. (5 поени)

За сите објекти од класите треба да се обезбедат следните функции:

преоптоварен оператор << во кој се печатат информации за студентот на курсот во формат: Ime --- ocenka (5 поени)
оcenka() – ја враќа оценката на студентот на курсот (5 поени)
Во класата StudentKursUsno дефинирај ја функцијата:

преоптоварен оператор += за поставување на описна оценка на студентот(5 поени)
Ако се направи обид да се внесе описна оценка во која покрај букви има и други знаци треба да се фрли исклучок (објект од класата BadInputException). Фатете го исклучокот во главната функција каде што е потребно.
Откако ќе го фатите отпечатете соодветна порака за грешка (Greshna opisna ocenka) и справете се со исклучокот така што тие знаци ќе отстранат од стрингот со описната оценка (ако описната оценка била dо1ba0r ќе се промени во dоbar). (10 поени)

Дадена е дел од дефиницијата на класата KursFakultet во која се чуваат информаци за името на курсот (низа од 30 знаци) и за студентите запишани на курсот (низа од 20 покажувачи кон класата StudentKurs) како и бројот на студенти запишани на курсот.

Еден студент кој запишал некој курс ќе го положи курсот ако има барем MINOCENKA. Вредноста MINOCENKA е членка на класата StudentKurs и има фиксна вредност 6 која не може да се промени. (5 поени)

Во класата KursFakultet имплементирај ги функциите:

функција pecatiStudenti() во која се печатат сите студенти кои го положиле курсот, секој во посебен ред. Претходно во првиот ред се печати: Kursot XXXXX go polozile: (5 поени).

функција postaviOpisnaOcenka(char * ime, char* opisnaOcenka) во која на студентот на курсот со даденото име му се поствува описна оценка. Ако тоа не е можно функцијата не прави ништо (15 поени).

Комплетна функционалност (5 поени)
*/
class BadInputException
{
private:
    char *opisnaOcena;

public:
    BadInputException(char *opisnaOcena)
    {
        this->opisnaOcena = new char[strlen(opisnaOcena) + 1];
        strcpy(this->opisnaOcena, opisnaOcena);
    }
    void message()
    {
        cout << "Greshna opisna ocenka" << endl;
    }
    char *clearOpisna()
    {
        int n = strlen(opisnaOcena);
        for (int i = 0; i < n; ++i)
        {
            if (isdigit(opisnaOcena[i]))
            {
                for (int j = i; j < n - 1; ++j)
                {
                    opisnaOcena[j] = opisnaOcena[j + 1];
                }
                char *tmp = new char[n - 1];
                strncpy(tmp, opisnaOcena, n - 1);
                delete[] opisnaOcena;
                opisnaOcena = tmp;
                i--;
                n--;
            }
        }
        return opisnaOcena;
    }
};
class StudentKurs
{
protected:
    char ime[30]{};
    int ocenka;
    bool daliUsno;
    static int MAX;
    const static int MINOCENKA = 6;

public:
    StudentKurs(char *ime, int finalenIspit)
    {
        strcpy(this->ime, ime);
        this->ocenka = finalenIspit;
        this->daliUsno = false;
    }
    static void setMAX(int max)
    {
        StudentKurs::MAX = max;
    }
    bool getDaliUsno() const
    {
        return daliUsno;
    }
    virtual int ocena() const
    {
        return ocenka;
    }
    friend ostream &operator<<(ostream &os, const StudentKurs &s)
    {
        os << s.ime << " --- " << s.ocena() << endl;
        return os;
    }
    char *getIme()
    {
        return ime;
    }
    virtual StudentKurs &operator+=(char *opisnaOcena)
    {
        return *this;
    }
    static int getMIN()
    {
        return MINOCENKA;
    }
};
int StudentKurs::MAX = 10;

class StudentKursUsno : public StudentKurs
{
private:
    char *opisnaOcenka;

public:
    StudentKursUsno(char *ime, int finalenIspit) : StudentKurs(ime, finalenIspit)
    {
        this->daliUsno = true;
        this->opisnaOcenka = nullptr;
    }
    int ocena() const override
    {
        int o = StudentKurs::ocena();
        if (!strcmp(opisnaOcenka, "odlicen"))
        {
            if (o + 2 > MAX)
            {
                return o;
            }
            return o + 2;
        }
        else if (!strcmp(opisnaOcenka, "dobro"))
        {
            if (o + 1 > MAX)
            {
                return o;
            }
            return o + 1;
        }
        else
        {
            return o - 1;
        }
    }
    StudentKursUsno &operator+=(char *opisnaOcena) override
    {
        if (!strcmp(opisnaOcena, "odlicen") || !strcmp(opisnaOcena, "dobro") || !strcmp(opisnaOcena, "losho"))
        {
            this->opisnaOcenka = new char[strlen(opisnaOcena)];
            strcpy(this->opisnaOcenka, opisnaOcena);
            return *this;
        }
        else
        {
            throw BadInputException(opisnaOcena);
        }
    }
    ~StudentKursUsno()
    {
        delete[] opisnaOcenka;
    }
    friend ostream &operator<<(ostream &os, const StudentKursUsno &s)
    {
        os << s.ime << " --- " << s.ocena() << endl;
        return os;
    }
};

class KursFakultet
{
private:
    char naziv[30]{};
    StudentKurs *studenti[20]{};
    int broj;

public:
    KursFakultet(char *naziv, StudentKurs **studenti, int broj)
    {
        strcpy(this->naziv, naziv);
        for (int i = 0; i < broj; i++)
        {
            // ako studentot ima usno isprashuvanje
            if (studenti[i]->getDaliUsno())
            {
                this->studenti[i] = new StudentKursUsno(*dynamic_cast<StudentKursUsno *>(studenti[i]));
            }
            else
                this->studenti[i] = new StudentKurs(*studenti[i]);
        }
        this->broj = broj;
    }
    ~KursFakultet()
    {
        for (int i = 0; i < broj; i++)
            delete studenti[i];
    }

    void postaviOpisnaOcenka(char *ime, char *opisna)
    {
        for (int i = 0; i < broj; ++i)
        {
            if (!strcmp(studenti[i]->getIme(), ime))
            {
                try
                {
                    *studenti[i] += opisna;
                }
                catch (BadInputException &e)
                {
                    e.message();
                    *studenti[i] += e.clearOpisna();
                }
            }
        }
    }

    void pecatiStudenti()
    {
        cout << "Kursot " << naziv << " go polozile:" << endl;
        for (int i = 0; i < broj; ++i)
        {
            if (studenti[i]->ocena() >= StudentKurs::getMIN())
            {
                cout << (*studenti[i]);
            }
        }
    }
};

int main()
{

    StudentKurs **niza;
    int n, m, ocenka;
    char ime[30], opisna[10];
    bool daliUsno;
    cin >> n;
    niza = new StudentKurs *[n];
    for (int i = 0; i < n; i++)
    {
        cin >> ime;
        cin >> ocenka;
        cin >> daliUsno;
        if (!daliUsno)
            niza[i] = new StudentKurs(ime, ocenka);
        else
            niza[i] = new StudentKursUsno(ime, ocenka);
    }

    KursFakultet programiranje("OOP", niza, n);
    cin >> m;

    for (int i = 0; i < m; i++)
    {
        cin >> ime >> opisna;
        programiranje.postaviOpisnaOcenka(ime, opisna);
    }

    StudentKurs::setMAX(9);

    programiranje.pecatiStudenti();

    for (int i = 0; i < n; i++)
        delete niza[i];
    delete[] niza;
}
