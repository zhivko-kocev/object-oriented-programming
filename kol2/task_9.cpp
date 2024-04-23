#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;
/*
Да се имплементира класа Trud во која се чуваат информации за: (5 поени)

вид на труд (еден знак и тоа C за конференциски труд, J за труд во списание)
година на издавање (цел број).
Да се имплементира класа Student во која се чува: (5 поени)

името на студентот (низа од најмногу 30 карактери)
индекс (цел број)
година на упис (цел број)
листа на оцени од положени предмети (низа од цели броеви)
број на положени предмети (цел број)
За оваа класа да се имплементираат следните методи:

функција rang() што пресметува просек од положените испити на студентот (5 поени)
оператор << за печатење на студентот во формат: (5 поени)

Индекс Име Година на упис ранг

Да се имплементира класа PhDStudent во која покрај основните информации за студентот дополнително се чува: (5 поени)

листа од објавени трудови (динамички резервирана низа од објекти од класата Trud)
бројот на трудови (цел број)
Во оваа класа да се препокрие соодветно функцијата rang() така што на просекот од положените испити ќе се додаде и збирот од поените од објавените трудови на PhD студентот.
Во зависност од видот на трудот, секој универзитет има посебен начин на бодување на трудовите. Начинот на бодување е ист за сите PhD студенти.
Иницијално да се смета дека конференциски труд се бодува со 1 поен, а труд во списание со 3 поени. Универзитетот има можност да ги менува вредностите на бодовите. (5 поени + 5 поени)

За оваа класа да се обезбеди:

оператор += за додавање нов објект од класата Trud во листата (5 поени).
Ако се направи обид да се внесе труд што е издаден порано од годината на упис на студентот да се фрли исклучок (објект од класата Exception).
Справувањето со исклучокот треба да се реализира во главната функција main каде што е потребно, но и во конструктор ако е потребно.
Ако бил генериран исклучок треба да се отпечати соодветна порака за грешка "Ne moze da se vnese dadeniot trud", а новиот труд нема да се внесе во листата на трудови од студентот. (10 поени)
Напомена: Сите променливи на класите се чуваат како приватни.

Да се обезбедат сите потребни функции за правилно функционирање на програмата. (5 поени)
*/

class Exception
{
public:
    void message()
    {
        cout << "Ne moze da se vnese dadeniot trud" << endl;
    }
};

class Trud
{
private:
    char type;
    int year;
    static int C_POINTS;
    static int J_POINTS;

public:
    Trud()
    {
        this->type = 'C';
        this->year = 2000;
    }

    Trud(char type, int year)
    {
        this->type = type;
        this->year = year;
    }

    static void setC_POINTS(int c)
    {
        Trud::C_POINTS = c;
    }

    static void setJ_POINTS(int j)
    {
        Trud::J_POINTS = j;
    }

    int getPoints()
    {
        if (tolower(type) == 'c')
        {
            return C_POINTS;
        }
        else
        {
            return J_POINTS;
        }
    }

    int getYear()
    {
        return year;
    }

    friend istream &operator>>(istream &in, Trud &t)
    {
        in >> t.type >> t.year;
        return in;
    }
};

int Trud::C_POINTS = 1;
int Trud::J_POINTS = 3;

class Student
{
private:
    char name[30]{};
    int index;
    int year;
    int grades[50]{};
    int numGrades;

public:
    Student(char *name, int index, int year, int *grades, int numGrades)
    {
        strcpy(this->name, name);
        this->index = index;
        this->year = year;
        this->numGrades = numGrades;
        for (int i = 0; i < numGrades; ++i)
        {
            this->grades[i] = grades[i];
        }
    }

    virtual double rang() const
    {
        double sum = 0;
        for (int i = 0; i < numGrades; ++i)
        {
            sum += grades[i];
        }
        return sum / numGrades;
    }

    friend ostream &operator<<(ostream &os, const Student &s)
    {
        os << s.index << " " << s.name << " " << s.year << " " << s.rang() << endl;
        return os;
    }

    int getIndex()
    {
        return index;
    }

    virtual Student &operator+=(Trud &t)
    {
        cout << "Ne postoi PhD student so indeks " << index << endl;
        return *this;
    }

    friend class PhDStudent;
};

class PhDStudent : public Student
{
private:
    Trud *trud;
    int brTrud;

public:
    PhDStudent(char *name, int index, int year, int *grades, int numGrades, Trud *trud, int brTrud) : Student(name,
                                                                                                              index,
                                                                                                              year,
                                                                                                              grades,
                                                                                                              numGrades)
    {
        this->trud = new Trud[brTrud];
        int cnt = 0;
        for (int i = 0, b = 0; i < brTrud; ++i)
        {
            if (trud[i].getYear() < year)
            {
                cout << "Ne moze da se vnese dadeniot trud" << endl;
                cnt++;
                continue;
            }
            this->trud[b++] = trud[i];
        }
        this->brTrud = brTrud - cnt;
    }

    PhDStudent(const PhDStudent &p) : Student(p)
    {
        this->trud = new Trud[p.brTrud];
        for (int i = 0; i < p.brTrud; ++i)
        {
            this->trud[i] = p.trud[i];
        }
        this->brTrud = p.brTrud;
    }

    PhDStudent &operator=(const PhDStudent &p)
    {
        if (this != &p)
        {
            delete[] trud;
            this->trud = new Trud[p.brTrud];
            for (int i = 0; i < p.brTrud; ++i)
            {
                this->trud[i] = p.trud[i];
            }
            this->brTrud = p.brTrud;
        }
        return *this;
    }

    double rang() const override
    {
        double r1 = Student::rang();
        double r2 = 0;
        for (int i = 0; i < brTrud; ++i)
        {
            r2 += trud[i].getPoints();
        }
        return r1 + r2;
    }

    PhDStudent &operator+=(Trud &t) override
    {
        if (t.getYear() < year)
        {
            throw Exception();
        }
        Trud *tmp = new Trud[brTrud + 1];
        for (int i = 0; i < brTrud; ++i)
        {
            tmp[i] = trud[i];
        }
        tmp[brTrud++] = t;
        delete[] trud;
        trud = tmp;
        return *this;
    }

    ~PhDStudent()
    {
        delete[] trud;
    }
};

int main()
{
    int testCase;
    cin >> testCase;

    int god, indeks, n, god_tr, m, n_tr;
    int izbor; // 0 za Student, 1 za PhDStudent
    char ime[30];
    int oceni[50];
    char tip;
    Trud trud[50];

    if (testCase == 1)
    {
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        Student s(ime, indeks, god, oceni, n);
        cout << s;

        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++)
        {
            cin >> tip;
            cin >> god_tr;
            Trud t(tip, god_tr);
            trud[j] = t;
        }
        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
        cout << phd;
    }
    if (testCase == 2)
    {
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i < m; i++)
        {
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0)
            {
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else
            {
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++)
                {
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        for (int i = 0; i < m; ++i)
        {
            if (niza[i]->getIndex() == indeks)
            {
                (*niza[i]) += t;
            }
        }

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 3)
    {
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i < m; i++)
        {
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0)
            {
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else
            {
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++)
                {
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        for (int i = 0; i < m; ++i)
        {
            if (niza[i]->getIndex() == indeks)
            {
                (*niza[i]) += t;
            }
        }

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 4)
    {
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++)
        {
            cin >> tip;
            cin >> god_tr;
            Trud t(tip, god_tr);
            trud[j] = t;
        }
        try
        {
            PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
            cout << phd;
        }
        catch (Exception &e)
        {
            e.message();
        }
    }
    if (testCase == 5)
    {
        cout << "===== Testiranje na isklucoci ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i < m; i++)
        {
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0)
            {
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else
            {
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++)
                {
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        for (int i = 0; i < m; ++i)
        {
            if (niza[i]->getIndex() == indeks)
            {
                try
                {
                    (*niza[i]) += t;
                }
                catch (Exception &e)
                {
                    e.message();
                }
            }
        }

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 6)
    {
        cout << "===== Testiranje na static clenovi ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i < m; i++)
        {
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0)
            {
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else
            {
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++)
                {
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        int conf, journal;
        cin >> conf;
        cin >> journal;

        Trud::setC_POINTS(conf);
        Trud::setJ_POINTS(journal);

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    return 0;
}