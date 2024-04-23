#include <iostream>
#include <cstring>

using namespace std;
/*
Да се креира класа за опишување на еден сервис за мобилни уреди. За секој мобилен телефон се чуваат податоци за модел (низа од 100 знаци), тип на уред (смартфон или компјутер),
потребни часови за основна проверка (децимален број), година на производство (цел број). (5 поени)

Сите уреди имаат исто времетраење за основна проверка и истата изнесува 1 час. Оваа вредност може да се смени со одлука на сервисот.
Дополнително, уредите кои се понови од 2015 година имаат потреба од дополнителени 1.5 часа за проверка. При проверка, лаптопите имаат потреба од дополнителни 2 часа за софтверска дијагностика (5 поени).

За оваа класа да се имплементира оператор << за печатење на уред во формат:

[modelnauredotl]
[tipnaured] [casovizaproverka]

Каде часовите за проверка се оние од основната проверка+ дополнителни 2 часа доколку уредот е понов од 2015 + 2 часа доколу уредот е лаптоп (5 поени)

Да се креира класа MobileServis во која се чува адреса (низа од 100 знаци), низа од уреди (динамички алоцирана низа) и број на уреди.(5 поени)

За класата да се обезбедат:

operatoror+= за додавање на нов уред во сервисот.(5 поени) Не смее да се дозволи годината на производство на уредот да биде поголема од 2019 или помала од 2000.
Ако се направи обид за додавање на уред со невалидна година, треба да се генерира исклучок InvalidProductionDate. (10 поени)

Функција pecatiUredi со која се печатат сите уреди со времето потребно за нивната проверка во сервисот (5 поени).

Да се обезбедат сите дополнителни методи потребни за правилно функционирање на програмата. (5 поени)
*/
enum tip
{
    smartphone,
    computer
};
class InvalidProductionDate
{
public:
    void message()
    {
        cout << "Невалидна година на производство" << endl;
    }
};

class Device
{
private:
    char name[100]{};
    tip type;
    int year;
    static int repairHours;

public:
    Device()
    {
        this->year = 2000;
        this->type = smartphone;
        strcpy(this->name, "Unknown");
    }
    Device(char *name, tip type, int year)
    {
        this->year = year;
        this->type = type;
        strcpy(this->name, name);
    }
    int getRepairHours() const
    {
        int r = 0;
        if (year > 2015)
        {
            r += 2;
        }
        if (type == computer)
        {
            r += 2;
        }
        return repairHours + r;
    }
    friend ostream &operator<<(ostream &os, const Device &d)
    {
        os << d.name << endl;
        if (d.type == smartphone)
        {
            os << "Mobilen " << d.getRepairHours() << endl;
        }
        else
        {
            os << "Laptop " << d.getRepairHours() << endl;
        }
        return os;
    }
    int getYear() const
    {
        return year;
    }

    static void setPocetniCasovi(int i);
};
int Device::repairHours = 1;

void Device::setPocetniCasovi(int i)
{
    Device::repairHours = i;
}

class MobileServis
{
private:
    char adress[100]{};
    Device *devices;
    int numDevices;

public:
    MobileServis(char *adress)
    {
        strcpy(this->adress, adress);
        this->devices = nullptr;
        this->numDevices = 0;
    }
    MobileServis &operator+=(const Device &d)
    {
        if (d.getYear() < 2000 || d.getYear() > 2019)
        {
            throw InvalidProductionDate();
        }
        else
        {
            if (!numDevices)
            {
                this->devices = new Device[1];
                this->devices[numDevices++] = d;
            }
            else
            {
                Device *tmp = new Device[numDevices + 1];
                for (int i = 0; i < numDevices; ++i)
                {
                    tmp[i] = devices[i];
                }
                tmp[numDevices++] = d;
                delete[] devices;
                devices = tmp;
            }
            return *this;
        }
    }
    void pecatiCasovi()
    {
        cout << "Ime: " << adress << endl;
        for (int i = 0; i < numDevices; ++i)
        {
            cout << devices[i];
        }
    }
};
int main()
{
    int testCase;
    cin >> testCase;
    char ime[100];
    int tipDevice;
    int godina;
    int n;
    Device devices[50];
    if (testCase == 1)
    {
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> tipDevice;
        cin >> godina;
        Device ig(ime, (tip)tipDevice, godina);
        cin >> ime;
        MobileServis t(ime);
        cout << ig;
    }
    if (testCase == 2)
    {
        cout << "===== Testiranje na operatorot += ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime, (tip)tipDevice, godina);
            t += tmp;
        }
        t.pecatiCasovi();
    }
    if (testCase == 3)
    {
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime, (tip)tipDevice, godina);
            try
            {
                t += tmp;
            }
            catch (InvalidProductionDate &e)
            {
                e.message();
            }
        }
        t.pecatiCasovi();
    }
    if (testCase == 4)
    {
        cout << "===== Testiranje na konstruktori ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime, (tip)tipDevice, godina);
            try
            {
                t += tmp;
            }
            catch (InvalidProductionDate &e)
            {
                e.message();
            }
        }
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }
    if (testCase == 5)
    {
        cout << "===== Testiranje na static clenovi ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime, (tip)tipDevice, godina);

            t += tmp;
        }
        t.pecatiCasovi();
        cout << "===== Promena na static clenovi ======" << endl;
        Device::setPocetniCasovi(2);
        t.pecatiCasovi();
    }

    if (testCase == 6)
    {
        cout << "===== Testiranje na kompletna funkcionalnost ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime, (tip)tipDevice, godina);
            try
            {
                t += tmp;
            }
            catch (InvalidProductionDate &e)
            {
                e.message();
            }
        }
        Device::setPocetniCasovi(3);
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }

    return 0;
}
