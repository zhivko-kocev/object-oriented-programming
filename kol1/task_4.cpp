#include <iostream>
#include <cstring>
using namespace std;
/*
(40 поени)

Да се креира класа Patnik во која се чуваат податоци за патниците на еден воз и
тоа: име (низа од максимум 100 знаци), класа на вагон во која се вози (цел број 1 или 2) и велосипед (булова променлива).

За оваа класа да се преоптоварат:

Оператор << - за печатење на информациите за патникот во формат:
Име на патник

Бројот на класата (1 или 2)

Дали има велосипед?

Потоа да се креира клaса Voz во која се чува: крајна дестинација (низа од максимум 100 знаци)
, динамички алоцирана низа од објекти од класата Patnik, како и број на елементи во низата
(цел број), број на дозволени велосипеди (цел број).

За класата да се обезбедат:

Оператор += – за додавање нов патник во воз. Патник со велосипед ќе може да се качи во воз само ако возот го дозволува тоа.
Оператор << - за печатење на крајната дестинација до која вози и листата на патници
Функција со потпис: patniciNemaMesto(). Со оваа функција се пресметува вкупниот
број на патници (од 1-ва класа и 2-ра класа) за кои нема место да влезат во возот
со велосипед. Притоа треба да се внимава дека во пресметувањето на вкупниот број
патници со велосипеди кои ќе влезат во возот прво треба да се земат предвид
патниците од 1-ва класа, а потоа се дозволува да влегуваат патниците од 2-ра класа
се додека не се достигне максималниот број на дозволени велосипеди во возот.
На крај се печати бројот на патници со велосипеди кои остануваат (не влегуваат во возот)
од 1-ва класа, а потоа од 2-ра класа.
*/
class Patnik
{
private:
    char ime[100];
    int klasa;
    bool velosiped;

public:
    char *getIme() { return this->ime; }
    int getKlasa() { return this->klasa; }
    bool getVelosiped() { return this->velosiped; }
    Patnik(char ime[100] = "", int klasa = 0, bool velosiped = false)
    {
        strcpy(this->ime, ime);
        this->klasa = klasa;
        this->velosiped = velosiped;
    }
    friend ostream &operator<<(ostream &output, Patnik &p)
    {
        output << p.ime << endl;
        output << p.klasa << endl;
        output << p.velosiped << endl;

        return output;
    }
    Patnik(const Patnik &p)
    {
        strcpy(this->ime, p.ime);
        this->klasa = p.klasa;
        this->velosiped = p.velosiped;
    }
    Patnik &operator=(const Patnik &p)
    {
        if (this != &p)
        {
            strcpy(this->ime, p.ime);
            this->klasa = p.klasa;
            this->velosiped = p.velosiped;
        }
        return *this;
    }
};
class Voz
{
private:
    char destinacija[100];
    Patnik *patnici;
    int n;
    int brDozvoleni;

public:
    Voz(char destinacija[100] = "", int brDozvoleni = 0, Patnik *patnici = nullptr, int n = 0)
    {
        strcpy(this->destinacija, destinacija);
        this->n = 0;
        this->brDozvoleni = brDozvoleni;
        this->patnici = new Patnik[n];
        for (int i = 0; i < n; i++)
        {
            this->patnici[i] = patnici[i];
        }
    }
    Voz &operator+=(Patnik &p)
    {
        if ((!p.getVelosiped() && brDozvoleni == 0) || brDozvoleni != 0)
        {
            Patnik *tmp = new Patnik[n + 1];
            for (int i = 0; i < n; i++)
            {
                tmp[i] = this->patnici[i];
            }
            delete[] this->patnici;
            patnici = tmp;
            this->patnici[n] = p;
            this->n++;
        }
        return *this;
    }
    Voz(const Voz &v)
    {
        strcpy(this->destinacija, v.destinacija);
        this->n = v.n;
        this->brDozvoleni = v.brDozvoleni;
        this->patnici = new Patnik[n];
        for (int i = 0; i < n; i++)
        {
            this->patnici[i] = v.patnici[i];
        }
    }
    Voz &operator=(Voz &v)
    {
        if (this != &v)
        {
            strcpy(this->destinacija, v.destinacija);
            this->n = v.n;
            this->brDozvoleni = v.brDozvoleni;
            delete[] this->patnici;
            this->patnici = new Patnik[n];
            for (int i = 0; i < n; i++)
            {
                this->patnici[i] = v.patnici[i];
            }
        }
        return *this;
    }
    friend ostream &operator<<(ostream &output, Voz &v)
    {
        output << v.destinacija << endl;
        for (int i = 0; i < v.n; i++)
        {
            output << v.patnici[i] << endl;
        }
        return output;
    }
    void patniciNemaMesto()
    {
        int prvaKlasa = 0, vtoraKlasa = 0;
        for (int i = 0; i < this->n; i++)
        {
            if (patnici[i].getKlasa() == 1 && patnici[i].getVelosiped())
                prvaKlasa++;
            else if (patnici[i].getKlasa() == 2 && patnici[i].getVelosiped())
                vtoraKlasa++;
        }
        if (prvaKlasa >= brDozvoleni)
            prvaKlasa = prvaKlasa - brDozvoleni;
        else if (prvaKlasa < brDozvoleni)
        {
            brDozvoleni = brDozvoleni - prvaKlasa;
            prvaKlasa = 0;
            if (vtoraKlasa >= brDozvoleni)
                vtoraKlasa = vtoraKlasa - brDozvoleni;
            else if (vtoraKlasa < brDozvoleni)
                vtoraKlasa = 0;
        }
        cout << "Brojot na patnici od 1-va klasa koi ostanale bez mesto e: " << prvaKlasa << endl;
        cout << "Brojot na patnici od 2-ra klasa koi ostanale bez mesto e: " << vtoraKlasa << endl;
    }
};
int main()
{
    Patnik p;
    char ime[100], destinacija[100];
    int n;
    bool velosiped;
    int klasa;
    int maxv;
    cin >> destinacija >> maxv;
    cin >> n;
    Voz v(destinacija, maxv);
    // cout<<v<<endl;
    for (int i = 0; i < n; i++)
    {
        cin >> ime >> klasa >> velosiped;
        Patnik p(ime, klasa, velosiped);
        // cout<<p<<endl;
        v += p;
    }
    cout << v;
    v.patniciNemaMesto();

    return 0;
}