#include <iostream>
#include <cstring>

using namespace std;
/*
Да се дефинира класа Vozac во која се чуваат информации за:

име (низа од максимум 100 знаци)
возраст (цел број)
број на трки (цел број)
дали е ветеран (да/не).
Да се преоптоварат:

операторот << за печатење кој ќе ги печати името, возраст, бројот на трки и дали е ветеран (се печати VETERAN)
операторот == за споредување на два возачи според заработувачката по трка.
Од оваа класа да се изведат две нови класи Avtomobilist и Motociklist.

За автомобилистот дополнително се чува:

цена на автомобилот (децимален број).
За мотоциклистот дополнително се чува:

моќност на мотор (цел број).
Заработувачката по трка на возачите се пресметува како:

за автомобилостот заработувачката по трка е $\frac{CENA_{AVTOMOBIL}}{5}$
за мотоциклистот заработувачката по трка е $MOKJNOST_NA_MOTOR * 20$
Секој автомобилист плаќа данок на заработка. Да се напишат соодветни методи за пресметување данок:

за автомобилисти: ако бројот на трки е поголем од 10 стапката на данок е 15% од заработката, инаку 10% од заработката.
за мотоциклисти: ако е ветеран стапката на данок е 25% од заработката, инаку 20% од заработката.
Да се напше надворешна функција soIstaZarabotuvachka која како аргументи прима низа од покажувачи од класата Vocac, нивниот
број, како и покажувач кон ојбект од возач и враќа како резултат бројот на возачи кои имаат иста заработувачка по трка со
проследениот возач.
*/
class Driver
{
protected:
    char name[100]{};
    int age;
    int numRaces;
    bool isVeteran;
    int profit;

public:
    Driver(char *name, int age, int numRaces, bool isVeteran)
    {
        strcpy(this->name, name);
        this->age = age;
        this->numRaces = numRaces;
        this->isVeteran = isVeteran;
        this->profit = 0;
    }

    friend ostream &operator<<(ostream &os, const Driver &d)
    {
        os << d.name << endl;
        os << d.age << endl;
        os << d.numRaces << endl;
        if (d.isVeteran)
        {
            os << "VETERAN" << endl;
        }
        return os;
    }
    bool operator==(const Driver &other) const
    {
        return this->profit == other.profit;
    }
    virtual double danok() = 0;
    virtual ~Driver() = default;
};

class CarDriver : public Driver
{
private:
    float carPrice;

public:
    CarDriver(char *name, int age, int numRaces, bool isVeteran, float carPrice) : Driver(name, age, numRaces,
                                                                                          isVeteran)
    {
        this->carPrice = carPrice;
        this->profit = this->carPrice / 5;
    }
    double danok() override
    {
        if (numRaces > 10)
        {
            return profit * 0.15;
        }
        else
        {
            return profit * 0.10;
        }
    }
};
class MotoDriver : public Driver
{
private:
    int motoPower;

public:
    MotoDriver(char *name, int age, int numRaces, bool isVeteran, int motoPower) : Driver(name, age, numRaces, isVeteran)
    {
        this->motoPower = motoPower;
        this->profit = this->motoPower * 20;
    }
    double danok() override
    {
        if (isVeteran)
        {
            return profit * 0.25;
        }
        else
        {
            return profit * 0.20;
        }
    }
};

int soIstaZarabotuvachka(Driver **pDriver, int n, Driver *pDriver1)
{
    int counter = 0;
    for (int i = 0; i < n; ++i)
    {
        if (*pDriver[i] == *pDriver1)
        {
            counter++;
        }
    }
    return counter;
}

int main()
{
    int n, x;
    cin >> n >> x;
    Driver **v = new Driver *[n];
    char ime[100];
    int vozrast;
    int trki;
    bool vet;
    for (int i = 0; i < n; ++i)
    {
        cin >> ime >> vozrast >> trki >> vet;
        if (i < x)
        {
            float cena_avto;
            cin >> cena_avto;
            v[i] = new CarDriver(ime, vozrast, trki, vet, cena_avto);
        }
        else
        {
            int mokjnost;
            cin >> mokjnost;
            v[i] = new MotoDriver(ime, vozrast, trki, vet, mokjnost);
        }
    }
    cout << "=== DANOK ===" << endl;
    for (int i = 0; i < n; ++i)
    {
        cout << *v[i];
        cout << v[i]->danok() << endl;
    }
    cin >> ime >> vozrast >> trki >> vet;
    int mokjnost;
    cin >> mokjnost;
    Driver *vx = new MotoDriver(ime, vozrast, trki, vet, mokjnost);
    cout << "=== VOZAC X ===" << endl;
    cout << *vx;
    cout << "=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===" << endl;
    cout << soIstaZarabotuvachka(v, n, vx);
    for (int i = 0; i < n; ++i)
    {
        delete v[i];
    }
    delete[] v;
    delete vx;
    return 0;
}
