#include <iostream>
using namespace std;
/*
Да се имплементира класа List во којашто ќе се чуваат информации за:

броеви што се дел од листата (динамички алоцирана низа од цели броеви)
бројот на броеви што се дел од листата
За класата да се дефинираат следните методи:

конструктор (со аргументи), copy-конструктор, деструктор, оператор =
void pecati()метод што ќе ги печати информациите за листата во форматот:
[број на елементи во листата]: x1 x2 .. xn sum: [сума] average: [просек]
int sum() метод што ја враќа сумата на елементите во листата
double average() метод што ќе го враќа просекот на броевите во листата
Дополнително, креирајте класата ListContainer, во која што ќе се чуваат информации за:

низа од листи (динамички алоцирана низа од објекти од класата List)
број на елементи во низата од листи (цел број)
број на обиди за додавање на листа во контејнерот (цел број првично поставен на нула)
За класата потребно е да ги дефинирате следните методи:

конструктор (default), copy-конструктор, деструктор, оператор =
void pecati() метод што ќе ги печати информациите за контејнерот во форматот:
List number: [реден број на листата] List info: [испечатени информации за листата со методот List::pecati()] \n sum: [сума] average: [просек]
доколку контејнерот е празен се печати само порака The list is empty.
void addNewList(List l) метод со којшто се додава листа во контејнерот
Напомена: една листа се додава во контејнерот ако и само ако има различна сума од сите листи што се веќе додадени во контејнерот
int sum() метод што ја враќа сумата на сите елементи во сите листи
double average() метод што го враќа просекот на сите елементи во сите листи во контејнерот
*/
class List
{
private:
    int *broevi;
    int brBroevi;

public:
    List()
    {
        broevi = new int[0];
        brBroevi = 0;
    }
    ~List()
    {
        delete[] broevi;
    }
    List(int *broevi, int brBroevi)
    {
        this->broevi = new int[brBroevi];
        for (int i = 0; i < brBroevi; i++)
            this->broevi[i] = broevi[i];
        this->brBroevi = brBroevi;
    }
    List(const List &l)
    {
        this->brBroevi = l.brBroevi;
        this->broevi = new int[l.brBroevi];
        for (int i = 0; i < l.brBroevi; i++)
            this->broevi[i] = l.broevi[i];
    }
    List &operator=(const List &l)
    {
        if (this != &l)
        {
            delete[] broevi;
            brBroevi = l.brBroevi;
            broevi = new int[l.brBroevi];
            for (int i = 0; i < l.brBroevi; i++)
                broevi[i] = l.broevi[i];
        }
        return *this;
    }
    int sum()
    {
        int suma = 0;
        for (int i = 0; i < brBroevi; i++)
        {
            suma += broevi[i];
        }
        return suma;
    }
    double average()
    {
        return sum() * 1.0 / brBroevi;
    }
    void pecati()
    {
        cout << brBroevi << ": ";
        for (int i = 0; i < brBroevi; i++)
        {
            cout << broevi[i] << " ";
        }
        cout << "sum: " << sum();
        cout << " average: " << average();
    }
    int getbrBroevi()
    {
        return brBroevi;
    }
};

class ListContainer
{
private:
    List *listi;
    int brElementi;
    int brObidi;

public:
    ListContainer()
    {
        listi = new List[0];
        brElementi = 0;
        brObidi = 0;
    }
    ~ListContainer()
    {
        delete[] listi;
    }
    ListContainer(const ListContainer &lc)
    {
        this->brObidi = lc.brObidi;
        this->brElementi = lc.brElementi;
        this->listi = new List[lc.brElementi];
        for (int i = 0; i < lc.brElementi; i++)
        {
            this->listi[i] = lc.listi[i];
        }
    }
    ListContainer &operator=(const ListContainer &lc)
    {
        if (this != &lc)
        {
            delete[] listi;
            brObidi = lc.brObidi;
            brElementi = lc.brElementi;
            listi = new List[lc.brElementi];
            for (int i = 0; i < lc.brElementi; i++)
            {
                listi[i] = lc.listi[i];
            }
        }
        return *this;
    }
    int sum()
    {
        int suma = 0;
        for (int i = 0; i < brElementi; i++)
        {
            suma += listi[i].sum();
        }
        return suma;
    }
    double average()
    {
        int suma = sum();
        int broevi = 0;
        for (int i = 0; i < brElementi; i++)
        {
            broevi += listi[i].getbrBroevi();
        }
        return suma / (broevi * 1.0);
    }
    void addNewList(List l)
    {
        ++brObidi;
        for (int i = 0; i < brElementi; i++)
        {
            if (l.sum() == listi[i].sum())
                return;
        }
        List *tmp = new List[brElementi + 1];
        for (int i = 0; i < brElementi; i++)
        {
            tmp[i] = listi[i];
        }
        tmp[brElementi++] = l;
        delete[] listi;
        listi = tmp;
    }
    void print()
    {
        if (!brElementi)
        {
            cout << "The list is empty" << endl;
            return;
        }
        else
        {
            for (int i = 0; i < brElementi; i++)
            {
                cout << "List number: " << i + 1 << " List info: ";
                listi[i].pecati();
                cout << endl;
            }
        }
        cout << "Sum: " << sum();
        cout << " Average: " << average() << endl;
        cout << "Successful attempts: " << brElementi << " Failed attempts: " << brObidi - brElementi << endl;
    }
};
int main()
{

    ListContainer lc;
    int N;
    cin >> N;

    for (int i = 0; i < N; i++)
    {
        int n;
        int niza[100];

        cin >> n;

        for (int j = 0; j < n; j++)
        {
            cin >> niza[j];
        }

        List l = List(niza, n);

        lc.addNewList(l);
    }

    int testCase;
    cin >> testCase;

    if (testCase == 1)
    {
        cout << "Test case for operator =" << endl;
        ListContainer lc1;
        lc1.print();
        cout << lc1.sum() << " " << lc.sum() << endl;
        lc1 = lc;
        lc1.print();
        cout << lc1.sum() << " " << lc.sum() << endl;
    }
    else
    {
        lc.print();
    }
}