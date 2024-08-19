#include <iostream>
#include <cstring>
using namespace std;
/*
Туристичка агенција нуди различни понуди за транспорт на патници. За секоја понуда се чуваат податоци за дестинацијата (низа од знаци), основна цена (цел број) и податок за растојанието до дестинацијата изразено во km (цел број).

Од класата Transport да се изведат класите AvtomobilTransport и KombeTransport за моделирање на понудите за транспорт кои нудат транспорт со автомобил или комбе, соодветно. За секоја понуда за транспорт со автомобил се чува податок
за тоа дали во понудата има платен шофер (булова променлива),
а за транспорт со комбе бројот на луѓе кои може да се превезат во комбето (цел број). (5 поени)

За секој објект од двете изведени класи треба да бидат на располагање следниве методи:

конструктор со аргументи што одговараат на податочните членови и set и get методи за податочните членови (5 поени)
метод cenaTransport, за пресметување на цената на понудата на следниот начин:
За транспорт со автомобил - основната цена се зголемува за 20% ако има платен шофер
За транспорт со комбе - основната цена ќе се намали зависно од бројот на патници во комбето. За секој патник во комбето цената се намалува за 200 (10 поени)
преоптоварен оператор < за споредба на две понуди за транспорт на патник според растојанието до дестинацијата. (5 поени)
Да се имплементира функција pecatiPoloshiPonudi што на влез прима низа од понуди за транспорт на патник, бројот на елементите од низата и една понуда T.
Функцијата ја печати дестинацијата, растојанието до дестинацијата и цената за понудите од низата кои се поскапи од понудата T сортирани во растечки редослед по растојанието до дестинацијата (погледни го повикот на функцијата) (10 поени)

Комплетна функционалност на кодот (5 поени)
*/
class Transport
{
protected:
    char destination[20]{};
    int price;
    int km;

public:
    Transport(char *destination, int price, int km)
    {
        strcpy(this->destination, destination);
        this->price = price;
        this->km = km;
    }
    bool operator<(const Transport &t) const
    {
        return this->km < t.km;
    }

    char *getDest()
    {
        return destination;
    }

    int getKm()
    {
        return km;
    }

    virtual int cenaTransport() = 0;

    virtual ~Transport() = default;
};

class AvtomobilTransport : public Transport
{
private:
    bool driver;

public:
    AvtomobilTransport(char *destination, int price, int km, bool driver) : Transport(destination, price, km)
    {
        this->driver = driver;
    }
    int cenaTransport() override
    {
        if (driver)
        {
            return price * 1.20;
        }
        else
        {
            return price;
        }
    }
};

class KombeTransport : public Transport
{
private:
    int numSeats;

public:
    KombeTransport(char *destination, int price, int km, int numSeats) : Transport(destination, price, km)
    {
        this->numSeats = numSeats;
    }
    int cenaTransport() override
    {
        return price - (numSeats * 200);
    }
};

void pecatiPoloshiPonudi(Transport **offers, int n, Transport &t)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1; j++)
        {
            if ((*offers[j + 1]) < (*offers[j]))
            {
                Transport *tmp = offers[j];
                offers[j] = offers[j + 1];
                offers[j + 1] = tmp;
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (offers[i]->cenaTransport() > t.cenaTransport())
            cout << offers[i]->getDest() << " " << offers[i]->getKm() << " " << offers[i]->cenaTransport() << endl;
    }
}

int main()
{

    char destinacija[20];
    int tip, cena, rastojanie, lugje;
    bool shofer;
    int n;
    cin >> n;
    Transport **ponudi;
    ponudi = new Transport *[n];

    for (int i = 0; i < n; i++)
    {

        cin >> tip >> destinacija >> cena >> rastojanie;
        if (tip == 1)
        {
            cin >> shofer;
            ponudi[i] = new AvtomobilTransport(destinacija, cena, rastojanie, shofer);
        }
        else
        {
            cin >> lugje;
            ponudi[i] = new KombeTransport(destinacija, cena, rastojanie, lugje);
        }
    }

    AvtomobilTransport nov("Ohrid", 2000, 600, false);
    pecatiPoloshiPonudi(ponudi, n, nov);

    for (int i = 0; i < n; i++)
        delete ponudi[i];
    delete[] ponudi;
    return 0;
}
