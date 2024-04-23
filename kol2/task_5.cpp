#include <iostream>
#include <cstring>
#define MAX 100
using namespace std;
/*
Да се креира класа Customer за опишување на купувачи на една книжара. За секој купувач се чуваат податоци за:

името (низа од 50 знаци),
електронска адреса (низа од 50 знаци),
вид на купувач (стандардни, лојални или вип),
основен попуст (цел број изразен во проценти),
дополнителен попуст (цел број изразен во проценти) и
број на купени производи. (5 поени)
Сите лојални купувачи со покажување на клуб картичка имаат право на основниот попуст при купување од книжарата.
Основниот попуст е ист за сите лојални купувачи и изнесува 10%. Оваа вредност може да се смени со одлука на раководството на книжарата.
Дополнителниот попуст е фиксен и може да го користат само вип купувачите и изнесува 20%. Стандардните купувачи немаат право на попуст (5 поени).

За оваа класа да се имплементира оператор << за печатење на купувач во формат:

[ime_na_kupuvac]
[email_na_kupuvac]
[broj_na_proizvodi]
[vid_na_kupuvac] [popust_sto_moze_da_go_koristi]
каде попустот е 0% ако купувачот е стандарден, вредноста на основниот попуст, ако е лојален или збир од основниот и дополнителниот попуст, ако купувачот е вип. (5 поени)

Да се креира класа за онлајн книжара FINKI-bookstore во која се чува низа од регистрирани купувачи (динамички алоцирана низа) и број на купувачи. (5 поени) За класата да се обезбедат:

operator+= (10 поени) за додавање купувач во листата од купувачи, но само ако веќе не е дел од неа (ако во листата нема купувач со иста електронска адреса).
Ако во листата постои корисник со иста електронска адреса, треба да се генерира исклучок UserExistsException.
Потребно е да се обезбеди справување со исклучокот во функцијата main на означеното место. Во ваква ситуација се печати порака "The user already exists in the list" (5 поени).
Функција update со која сите стандардни купувачи со купени повеќе од 5 производи стануваат лојални, а сите лојални купувачи со над 10 купени производи, стануваат вип (5 поени).
Оператор << за печатење на информациите за сите регистрирани купувачи (5 поени).
Да се обезбедат сите дополнителни методи потребни за правилно функционирање на програмата. (10 поени)
*/
enum typeC
{
    standard,
    loyal,
    vip
};
class UserExistsException
{
public:
    void message()
    {
        cout << "The user already exists in the list!" << endl;
    }
};
class Customer
{
private:
    char name[50]{};
    char email[50]{};
    typeC type;
    static int baseDiscount;
    const static int additionalDiscount = 20;
    int numBought;

public:
    Customer()
    {
        strcpy(this->name, "Unknown");
        strcpy(this->email, "Unknown");
        this->type = standard;
        this->numBought = 0;
    }
    Customer(char *name, char *email, typeC type, int numBought)
    {
        strcpy(this->name, name);
        strcpy(this->email, email);
        this->type = type;
        this->numBought = numBought;
    }
    friend ostream &operator<<(ostream &os, const Customer &c)
    {
        os << c.name << endl;
        os << c.email << endl;
        os << c.numBought << endl;
        if (c.type == standard)
        {
            os << "standard " << 0 << endl;
        }
        else if (c.type == loyal)
        {
            os << "loyal " << baseDiscount << endl;
        }
        else if (c.type == vip)
        {
            os << "vip " << baseDiscount + additionalDiscount << endl;
        }
        return os;
    }
    void setDiscount1(int num)
    {
        baseDiscount = num;
    }
    void setType(typeC _type)
    {
        this->type = _type;
    }
    typeC getType()
    {
        return type;
    }
    char *getEmail()
    {
        return email;
    }
    int getBought()
    {
        return numBought;
    }
};
int Customer::baseDiscount = 10;

class FINKI_bookstore
{
private:
    Customer *customers{};
    int numCostumers;

public:
    FINKI_bookstore()
    {
        this->customers = nullptr;
        this->numCostumers = 0;
    }
    FINKI_bookstore(const FINKI_bookstore &fb)
    {
        this->customers = new Customer[numCostumers];
        this->numCostumers = fb.numCostumers;
        for (int i = 0; i < fb.numCostumers; ++i)
        {
            this->customers[i] = fb.customers[i];
        }
    }
    FINKI_bookstore &operator=(const FINKI_bookstore &fb)
    {
        if (this != &fb)
        {
            delete[] customers;
            this->customers = new Customer[numCostumers];
            this->numCostumers = fb.numCostumers;
            for (int i = 0; i < fb.numCostumers; ++i)
            {
                this->customers[i] = fb.customers[i];
            }
        }
        return *this;
    }
    void setCustomers(Customer *customerss, int n)
    {
        this->customers = new Customer[n];
        this->numCostumers = n;
        for (int i = 0; i < n; ++i)
        {
            this->customers[i] = customerss[i];
        }
    }
    FINKI_bookstore &operator+=(Customer &c)
    {
        if (!numCostumers)
        {
            customers = new Customer[1];
            customers[numCostumers++] = c;
        }
        else
        {
            for (int i = 0; i < numCostumers; ++i)
            {
                if (!strcmp(c.getEmail(), customers[i].getEmail()))
                {
                    throw UserExistsException();
                }
            }
            Customer *tmp = new Customer[numCostumers + 1];
            for (int i = 0; i < numCostumers; ++i)
            {
                tmp[i] = customers[i];
            }
            tmp[numCostumers++] = c;
            delete[] customers;
            customers = tmp;
        }
    }
    void update()
    {
        for (int i = 0; i < numCostumers; ++i)
        {
            if (customers[i].getType() == standard && customers[i].getBought() > 5)
            {
                customers[i].setType(loyal);
            }
            else if (customers[i].getType() == loyal && customers[i].getBought() > 10)
            {
                customers[i].setType(vip);
            }
        }
    }
    friend ostream &operator<<(ostream &os, const FINKI_bookstore &fb)
    {
        for (int i = 0; i < fb.numCostumers; ++i)
        {
            os << fb.customers[i];
        }
        return os;
    }
    ~FINKI_bookstore()
    {
        delete[] customers;
    }
};
int main()
{
    int testCase;
    cin >> testCase;

    char name[MAX];
    char email[MAX];
    int tC;
    int discount;
    int numProducts;

    if (testCase == 1)
    {
        cout << "===== Test Case - Customer Class ======" << endl;
        cin.get();
        cin.getline(name, MAX);
        cin.getline(email, MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC)tC, numProducts);
        cout << c;
    }

    if (testCase == 2)
    {
        cout << "===== Test Case - Static Members ======" << endl;
        cin.get();
        cin.getline(name, MAX);
        cin.getline(email, MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC)tC, numProducts);
        cout << c;

        c.setDiscount1(5);

        cout << c;
    }

    if (testCase == 3)
    {
        cout << "===== Test Case - FINKI-bookstore ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for (int i = 0; i < n; ++i)
        {
            cin.get();
            cin.getline(name, MAX);
            cin.getline(email, MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC)tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << fc << endl;
    }

    if (testCase == 4)
    {
        cout << "===== Test Case - operator+= ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for (int i = 0; i < n; ++i)
        {
            cin.get();
            cin.getline(name, MAX);
            cin.getline(email, MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC)tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name, MAX);
        cin.getline(email, MAX);
        cin >> tC;
        cin >> numProducts;
        Customer c(name, email, (typeC)tC, numProducts);
        fc += c;

        cout << fc;
    }

    if (testCase == 5)
    {
        cout << "===== Test Case - operator+= (exception) ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for (int i = 0; i < n; ++i)
        {
            cin.get();
            cin.getline(name, MAX);
            cin.getline(email, MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC)tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name, MAX);
        cin.getline(email, MAX);
        cin >> tC;
        cin >> numProducts;
        Customer c(name, email, (typeC)tC, numProducts);
        try
        {
            fc += c;
            cout << fc;
        }
        catch (UserExistsException &e)
        {
            e.message();
        }
        cout << fc;
    }

    if (testCase == 6)
    {
        cout << "===== Test Case - update method  ======" << endl
             << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for (int i = 0; i < n; ++i)
        {
            cin.get();
            cin.getline(name, MAX);
            cin.getline(email, MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC)tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << "Update:" << endl;
        fc.update();
        cout << fc;
    }
    return 0;
}
