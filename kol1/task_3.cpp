#include <iostream>
#include <cstring>

using namespace std;
/*
За потребите на еден приватен банкар кој тргува со акции, потребно е да се направи модул за менаџирање со клиентски портфолија.

За таа цел, треба да се креира класа StockRecord. Класата треба да содржи:

ID, кој означува која е акцијата која се тргува (низа од 12 знаци)
Име на компанијата која ја издала акцијата (низа од 50 знаци)
Цена според која се купени акциите (реален број)
Моментална цена на акцијата (реален број)
Број на акции кои се купени (цел број)
За класата да се дефинираат потребните конструктори и set метода за моменталната
цена со потпис void setNewPrice(double c) (10 поени). Исто така, да се
имплементираат методи double value() и double profit(). Првата треба да ја
пресметува вредноста на акциите, а втората треба да го пресметува моменталниот
профит од акциите. Пресметката се врши на следниот начин (5 поени):

Вредност = број на акции * моментална цена
Профит = број на акции * (моментална цена - цена по која се купени)
Дополнително, да се преоптовари операторот << за печатење на објектот во следниот формат (5 поени):
Компанија БројНаАкции КуповнаЦена МоменталнаЦена Профит

Да се креира класа Client која содржи:

Име и презиме на клиентот (низа од 60 знаци)
ID на сметка (цел број)
Низа од компании кои ги поседува клиентот (динамичка низа од објекти од класата StockRecord)
Број на објекти во низата (цел број)
За класата Client да се дефинираат потребните конструктори, деструктор и метода
double totalValue() која ќе ја пресметува моменталната вредност на акциите кои ги поседува клиентот.
Таа се пресметува како збир од вредноста на сите акции од секоја компанија од
кои е составено клиентското портфолио (15 поени). Дополнително, за класата да се преоптоварат операторите:

+= за купување на нова компанија во портфолиото (додавање на нов објект од класата StockRecord во низата со компании) (10 поени)

<< за печатење на информации за портфолиото на клиентот така што во првиот ред ќе
бидат прикажани ID на сметката и моменталната вредност на портфолиото одделени со празно место, а во секој
нареден ред ќе бидат прикажани компаниите од кои е составено портфолиото, секоја во посебен ред (5 поени)

Комплетна функционанлост (5 поени)
*/
class StockRecords
{
private:
    char id[12]{};
    char companyName[50]{};
    double price;
    double newPrice{};
    int numShares;

public:
    StockRecords()
    {
        strcpy(id, "0");
        strcpy(companyName, "Unknown");
        price = 0;
        newPrice = 0;
        numShares = 0;
    }
    StockRecords(char *id, char *companyName, double price, int numShares)
    {
        strcpy(this->id, id);
        strcpy(this->companyName, companyName);
        this->price = price;
        this->numShares = numShares;
        newPrice = 0;
    }
    void setNewPrice(double c)
    {
        newPrice = c;
    }
    double value()
    {
        return numShares * newPrice;
    }
    double profit() const
    {
        return numShares * (newPrice - price);
    }
    friend ostream &operator<<(ostream &os, StockRecords const &s)
    {
        os << s.companyName << " " << s.numShares << " " << s.price << " " << s.newPrice << " " << s.profit() << endl;
        return os;
    }
    ~StockRecords() = default;
};

class Client
{
private:
    char name[60]{};
    int id;
    StockRecords *companies;
    int numCompanies;

public:
    Client()
    {
        strcpy(name, "Unknown");
        id = 0;
        numCompanies = 0;
        companies = nullptr;
    }
    Client(char *name, int id)
    {
        strcpy(this->name, name);
        this->id = id;
        numCompanies = 0;
        companies = nullptr;
    }
    ~Client()
    {
        delete[] companies;
    }
    double totalValue() const
    {
        double total = 0;
        for (int i = 0; i < numCompanies; ++i)
        {
            total += companies[i].value();
        }
        return total;
    }
    Client &operator+=(StockRecords const &s)
    {
        if (!numCompanies)
        {
            companies = new StockRecords[numCompanies + 1];
            companies[numCompanies++] = s;
        }
        else
        {
            auto *temp = new StockRecords[numCompanies + 1];
            for (int i = 0; i < numCompanies; ++i)
            {
                temp[i] = companies[i];
            }
            temp[numCompanies] = s;
            delete[] companies;
            companies = temp;
            numCompanies++;
        }
        return *this;
    }
    friend ostream &operator<<(ostream &os, Client const &c)
    {
        os << c.id << " " << c.totalValue() << endl;
        for (int i = 0; i < c.numCompanies; ++i)
        {
            os << c.companies[i];
        }
        return os;
    }
};
int main()
{

    int test;
    cin >> test;

    if (test == 1)
    {
        double price;
        cout << "=====TEST NA KLASATA StockRecord=====" << endl;
        StockRecords sr("1", "Microsoft", 60.0, 100);
        cout << "Konstruktor OK" << endl;
        cin >> price;
        sr.setNewPrice(price);
        cout << "SET metoda OK" << endl;
    }
    else if (test == 2)
    {
        cout << "=====TEST NA METODITE I OPERATOR << OD KLASATA StockRecord=====" << endl;
        char id[12], company[50];
        double price, newPrice;
        int n, shares;
        cin >> n;
        for (int i = 0; i < n; ++i)
        {
            cin >> id;
            cin >> company;
            cin >> price;
            cin >> newPrice;
            cin >> shares;
            StockRecords sr(id, company, price, shares);
            sr.setNewPrice(newPrice);
            cout << sr.value() << endl;
            cout << sr;
        }
    }
    else if (test == 3)
    {
        cout << "=====TEST NA KLASATA Client=====" << endl;
        char companyID[12], companyName[50], clientName[50];
        int clientID, n, shares;
        double oldPrice, newPrice;
        bool flag = true;
        cin >> clientName;
        cin >> clientID;
        cin >> n;
        Client c(clientName, clientID);
        cout << "Konstruktor OK" << endl;
        for (int i = 0; i < n; ++i)
        {
            cin >> companyID;
            cin >> companyName;
            cin >> oldPrice;
            cin >> newPrice;
            cin >> shares;
            StockRecords sr(companyID, companyName, oldPrice, shares);
            sr.setNewPrice(newPrice);
            c += sr;
            if (flag)
            {
                cout << "Operator += OK" << endl;
                flag = false;
            }
        }
        cout << c;
        cout << "Operator << OK" << endl;
    }
    return 0;
}