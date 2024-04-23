#include <iostream>
#include <cstring>

using namespace std;
/*
Фирмата FINKI Cloud има потреба од решение за управување со image датотеките од различните оперативни системи кои ги користат при сетирање на нови сервери. За таа цел потребно е да се дефинираат следниве класи:

OperativenSistem
Во класата OperativenSistem треба да се чуваат следниве податоци:

име на оперативниот систем (динамички алоцирана низа од знаци)
верзија (float)
тип (енумерација со можни вредности LINUX, UNIX, WINDOWS)
големина (во GB) (float)
Дополнително, во рамките на класата потребно е да се дефинира:

конструктори со и без параметри
copy constructor
destructor
преоптоварување на операторот =
метод за печатење на информациите - void pecati() (видете го излезот од тест примерите за структурата)
метод за проверка на еднаквост помеѓу два оперативни системи (два оперативни системи се еднакви ако имаат исто име, верзија, тип и големина) - bool ednakviSe(const OperativenSistem &os)
метод за споредба на верзии помеѓу два оперативни система - int sporediVerzija(const OperativenSistem &os), кој ќе враќа 0 доколку верзиите се исти, -1 доколку верзијата на оперативниот систем од аргументот е поголема и 1 во преостанатиот случај.
метод за проверка дали два оперативни системи се од иста фамилија. Два оперативни системи се од иста фамилија доколку имаат исто име и се од ист тип. bool istaFamilija(const OperativenSistem &sporedba)
Repozitorium
Во класата Repozitorium треба да се чуваат следниве податоци:

име на репозиториумот (низа од 20 знака)
динамички алоцирана низа од OperativenSistem
број на оперативни системи кои моментално се наоѓаат во репозиториумот (int)
Дополнително, во рамките на класата потребно е да се дефинира:

конструктор Repozitorium(const char *ime)
деструктор
метод void pecatiOperativniSistemi() кој ќе ги печати сите оперативни системи кои се дел од репозиториумот
метод void izbrishi(const OperativenSistem &operativenSistem) кој ќе го избрише оперативниот систем проследен како аргумент, доколку тој се наоѓа во репозиториумот. Да се користи методот ednakviSe за споредба на два оперативни система.
метод за додавање на оперативен систем (void dodadi(const OperativenSistem &nov)) кој ќе го има следново однесување:
Доколку веќе постои оперативен систем од иста фамилија (да се користи методот за проверка на фамилија) кој е постар од проследениот оперативен систем, тогаш постоечкиот оперативен систем се заменува со новиот.
Во секој друг случај, проследениот оперативен систем се додава како дополнителен во репозиториумот.
*/
enum TYPE
{
    LINUX,
    UNIX,
    WINDOWS
};

class OperativeSystem
{
private:
    char *name;
    float version;
    TYPE type;
    float size;

public:
    OperativeSystem(char *name = "Windows", float version = 1.0, TYPE type = WINDOWS, float size = 12.7)
    {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->version = version;
        this->type = type;
        this->size = size;
    }

    OperativeSystem(OperativeSystem const &os)
    {
        this->name = new char[strlen(os.name) + 1];
        strcpy(this->name, os.name);
        this->version = os.version;
        this->type = os.type;
        this->size = os.size;
    }

    ~OperativeSystem()
    {
        delete[] name;
    }

    OperativeSystem &operator=(OperativeSystem const &os)
    {
        if (this != &os)
        {
            delete[] name;
            this->name = new char[strlen(os.name) + 1];
            strcpy(this->name, os.name);
            this->version = os.version;
            this->type = os.type;
            this->size = os.size;
        }
        return *this;
    }

    void print()
    {
        cout << "Ime: " << name << " Verzija: " << version << " Tip: " << type << " Golemina:" << size << "GB" << endl;
    }

    bool equal(OperativeSystem const &os)
    {
        if (!strcmp(this->name, os.name) && this->version == os.version && this->size == os.size &&
            this->type == os.type)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    int versionCompare(OperativeSystem const &os) const
    {
        if (this->version > os.version)
        {
            return 1;
        }
        else if (this->version < os.version)
        {
            return -1;
        }
        else
        {
            return 0;
        }
    }
    bool sameFamily(OperativeSystem const &os)
    {
        if (!strcmp(this->name, os.name) && this->type == os.type)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

class Repository
{
private:
    char name[20]{};
    OperativeSystem *systems;
    int numOS;

public:
    Repository(char *name = "untitled")
    {
        strcpy(this->name, name);
        numOS = 0;
        systems = nullptr;
    }
    ~Repository()
    {
        delete[] systems;
    }
    void printRepository()
    {
        cout << "Repozitorium: " << name << endl;
        for (int i = 0; i < numOS; ++i)
        {
            systems[i].print();
        }
    }
    void add(OperativeSystem const &os)
    {
        if (numOS == 0)
        {
            this->systems = new OperativeSystem[numOS + 1];
            systems[numOS++] = os;
        }
        else
        {
            for (int i = 0; i < numOS; ++i)
            {
                if (systems[i].sameFamily(os))
                {
                    if (systems[i].versionCompare(os) == -1)
                    {
                        systems[i] = os;
                        return;
                    }
                }
            }
            OperativeSystem *tmp;
            tmp = new OperativeSystem[numOS + 1];
            for (int i = 0; i < numOS; ++i)
            {
                tmp[i] = systems[i];
            }
            tmp[numOS++] = os;
            delete[] systems;
            systems = tmp;
        }
    }
    void remove(OperativeSystem const &os)
    {
        int count = 0;
        for (int i = 0; i < numOS; ++i)
        {
            if (!systems[i].equal(os))
            {
                count++;
            }
        }
        OperativeSystem *tmp;
        tmp = new OperativeSystem[count];
        count = 0;
        for (int i = 0; i < numOS; ++i)
        {
            if (!systems[i].equal(os))
            {
                tmp[count++] = systems[i];
            }
        }
        delete[] systems;
        systems = tmp;
        numOS = count;
    }
};

int main()
{
    char repoName[20];
    cin >> repoName;
    Repository repozitorium = Repository(repoName);
    int brojOperativniSistemi = 0;
    cin >> brojOperativniSistemi;
    char ime[20];
    float verzija;
    int tip;
    float golemina;
    for (int i = 0; i < brojOperativniSistemi; i++)
    {
        cin >> ime;
        cin >> verzija;
        cin >> tip;
        cin >> golemina;
        OperativeSystem os = OperativeSystem(ime, verzija, (TYPE)tip, golemina);
        repozitorium.add(os);
    }

    repozitorium.printRepository();
    cin >> ime;
    cin >> verzija;
    cin >> tip;
    cin >> golemina;
    OperativeSystem os = OperativeSystem(ime, verzija, (TYPE)tip, golemina);
    cout << "=====Brishenje na operativen sistem=====" << endl;
    repozitorium.remove(os);
    repozitorium.printRepository();
    return 0;
}