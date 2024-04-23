#include <iostream>
#include <cstring>
using namespace std;
/*
Да се дефинира класа Ucesnik за учесник во маратон за кој ќе се чуваат информации за:

име (динамички алоцирана низа од знаци)
пол (bool)
возраст (цел број) (5 поени).
За потребите на оваа класа да се преоптоварат потребните конструктори и да се напише соодветен деструктор. (10 поени)

Дополнително за оваа класа да се преоптоварат:

оператор за споредување > (споредува двајца учесници според возраста) (5 поени)
операторот за проследување на излезен тек << кој ќе ги печати името, полот (машки/женски) и возраста, секој во посебен ред. (5 поени)
Да се дефинира класа Maraton за кој се чуваат:

локација (низа од максимум 100 знаци)
низа од Ucesnik објекти (динмички алоцирана низа од објекти од класата Ucesnik)
број на учесници (цел број) (5 поени).
За потребите на оваа класа да се преоптоварат потребните конструктори и да се напише соодветен деструктор. (10 поени) Исто така да се имплементираат следните методи:

оператор += за додавање нов Ucesnik на маратонот Maraton. (10 поени)
prosecnoVozrast() вреќа просечена возраст на учесниците на маратонот (5 поени)
pecatiPomladi(Ucesnik &u) ги печати сите учесници помлади од учесникот проследен како аргумент на методот. (5 поени)

*/
class Ucesnik
{
private:
    char *ime;
    bool maski;
    int vozrast;

public:
    Ucesnik(char *ime = "", bool maski = true, int vozrast = 0)
    {
        this->ime = new char[strlen(ime) + 1];
        strcpy(this->ime, ime);
        this->maski = maski;
        this->vozrast = vozrast;
    }
    Ucesnik(const Ucesnik &copy)
    {
        this->ime = new char[strlen(copy.ime) + 1];
        strcpy(this->ime, copy.ime);
        this->maski = copy.maski;
        this->vozrast = copy.vozrast;
    }
    Ucesnik &operator=(const Ucesnik &copy)
    {
        if (this != &copy)
        {
            this->ime = new char[strlen(copy.ime) + 1];
            strcpy(this->ime, copy.ime);
            this->maski = copy.maski;
            this->vozrast = copy.vozrast;
        }
        return *this;
    }
    bool operator>(Ucesnik &compare)
    {
        if (this->vozrast > compare.vozrast)
            return true;
        else
            return false;
    }
    friend ostream &operator<<(ostream &o, Ucesnik &print)
    {
        o << print.ime << endl;
        if (print.maski)
            o << "mashki" << endl;
        else
            o << "zhenski" << endl;
        o << print.vozrast << endl;
        return o;
    }
    int getvozrast()
    {
        return this->vozrast;
    }
};
class Maraton
{
private:
    char lokacija[100]{};
    Ucesnik *niza;
    int broj;

public:
    Maraton(char *lokacija = nullptr, Ucesnik *niza = nullptr, int broj = 0)
    {
        strcpy(this->lokacija, lokacija);
        this->broj = broj;
        this->niza = new Ucesnik[broj];
        for (int i = 0; i < broj; i++)
            this->niza[i] = niza[i];
    }
    Maraton(const Maraton &copy)
    {
        strcpy(this->lokacija, copy.lokacija);
        this->broj = copy.broj;
        this->niza = new Ucesnik[copy.broj];
        for (int i = 0; i < copy.broj; i++)
            this->niza[i] = copy.niza[i];
    }
    Maraton &operator=(const Maraton &copy)
    {
        if (this != &copy)
        {
            strcpy(this->lokacija, copy.lokacija);
            this->broj = copy.broj;
            this->niza = new Ucesnik[copy.broj];
            for (int i = 0; i < copy.broj; i++)
                this->niza[i] = copy.niza[i];
        }
        return *this;
    }
    Maraton &operator+=(const Ucesnik &add)
    {
        auto *tmp = new Ucesnik[broj + 1];
        for (int i = 0; i < broj; i++)
            tmp[i] = niza[i];
        tmp[broj++] = add;
        delete[] niza;
        niza = tmp;
        return *this;
    }
    double prosecnoVozrast()
    {
        double prosek = 0;
        for (int i = 0; i < broj; i++)
            prosek = prosek + niza[i].getvozrast();
        return prosek / broj;
    }
    void pecatiPomladi(Ucesnik &print)
    {
        for (int i = 0; i < broj; i++)
            if (print > niza[i])
                cout << niza[i];
    }
};
int main()
{
    char ime[100];
    bool maski;
    int vozrast, n;
    cin >> n;
    char lokacija[100];
    cin >> lokacija;
    Maraton m(lokacija);
    auto **u = new Ucesnik *[n];
    for (int i = 0; i < n; ++i)
    {
        cin >> ime >> maski >> vozrast;
        u[i] = new Ucesnik(ime, maski, vozrast);
        m += *u[i];
    }
    m.pecatiPomladi(*u[n - 1]);
    cout << m.prosecnoVozrast() << endl;
    for (int i = 0; i < n; ++i)
    {
        delete u[i];
    }
    delete[] u;
    return 0;
}