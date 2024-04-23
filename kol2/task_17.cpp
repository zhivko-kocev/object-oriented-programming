#include <iostream>
#include <cstring>
using namespace std;
/*
Да се имплементира апстрактна класа FudblaskaEkipa во која се чува: (5 поени)

име на тренерот на екипата (максимум 100 знаци)
бројот на постигнати голови на последните 10 натпревари, последниот натпревар е на позиција 9, предпоследниот на позиција 8, итн (поле од 10 цели броеви)
Од класата FudblaskaEkipa да се изведат класите Klub и Reprezentacija. За секој клуб дополнително се чува податок за името и бројот на титули што ги има освоено, а за репрезентацијата се чуваат податоци за името на државата и вкупен број на меѓународни настапи. За овие класи да се имплементираат следните методи:

соодветен конструктор (5 поени)
оператор << за печатење на стандарден излез во формат [IME_NA_KLUB/DRZHAVA]\n[TRENER]\n[USPEH]\n (5 поени)
преоптоварен оператор+= за додавање на голови од последниот натпревар (внимавајте секогаш се чуваат головите само од последните 10 натпревари) (10 поени)
метод uspeh, за пресметување на успехот на тимот на следниот начин:
За Klub се пресметува како збир од збирот на головите од последните 10 натпревари помножен со 3 и бројот на титули помножен со 1000 (на пр. голови = {2, 0, 1, 3, 2, 0, 1, 4, 2, 3} и број на титули = 3, достигнување = 18 * 3 + 3 * 1000 = 3054)
За Reprezentacija како збир од збирот на головите од последните 10 натпревари помножен со 3 и бројот на меѓународни настапи помножен со 50 (на пр. голови = {2, 0, 1, 3, 2, 0, 1, 4, 2, 3} и број на меѓународни настапи=150, достигнување = 18 * 3 + 150 * 50 = 7554) (10 поени)
преоптоварен оператор > за споредба на две фудбласки екипи од каков било вид (клубови или репрезентации) според успехот (5 поени)
Да се имплементира функција najdobarTrener што на влез прима низа од покажувачи кон FudblaskaEkipa и големина на низата и го печати тимот со најголем успех (10 поени).
*/
class FudbalskaEkipa
{
protected:
    char coach[100]{};
    int goals[10]{};

public:
    FudbalskaEkipa(char *coach, int *goals)
    {
        strcpy(this->coach, coach);
        for (int i = 0; i < 10; ++i)
        {
            this->goals[i] = goals[i];
        }
    }

    virtual int uspeh() const = 0;

    virtual const char *getName() const = 0;

    friend ostream &operator<<(ostream &os, const FudbalskaEkipa &f)
    {
        os << f.getName() << endl;
        os << f.coach << endl;
        os << f.uspeh() << endl;
        return os;
    }
    FudbalskaEkipa &operator+=(int goal)
    {
        for (int i = 0; i < 9; ++i)
        {
            goals[i] = goals[i + 1];
        }
        goals[9] = goal;
        return *this;
    }
    int getGoals() const
    {
        int sum = 0;
        for (int i = 0; i < 10; ++i)
        {
            sum += goals[i];
        }
        return sum;
    }
    virtual ~FudbalskaEkipa() = default;
};

class Klub : public FudbalskaEkipa
{
private:
    char name[100]{};
    int numTitles;

public:
    Klub(char *coach, int *goals, char *name, int numTitles) : FudbalskaEkipa(coach, goals)
    {
        this->numTitles = numTitles;
        strcpy(this->name, name);
    }
    int uspeh() const override
    {
        return (this->getGoals() * 3) + (numTitles * 1000);
    }
    const char *getName() const override
    {
        return name;
    }
};
class Reprezentacija : public FudbalskaEkipa
{
private:
    char name[100];
    int matches;

public:
    Reprezentacija(char *coach, int *goals, char *name, int matches) : FudbalskaEkipa(coach, goals)
    {
        this->matches = matches;
        strcpy(this->name, name);
    }
    int uspeh() const override
    {
        return (this->getGoals() * 3) + (matches * 50);
    }
    const char *getName() const override
    {
        return name;
    }
};

void najdobarTrener(FudbalskaEkipa **team, int n)
{
    FudbalskaEkipa *max = team[0];
    for (int i = 0; i < n; ++i)
    {
        if (team[i]->uspeh() > max->uspeh())
        {
            max = team[i];
        }
    }
    cout << (*max);
}

int main()
{
    int n;
    cin >> n;
    FudbalskaEkipa **ekipi = new FudbalskaEkipa *[n];
    char coach[100];
    int goals[10];
    char x[100];
    int tg;
    for (int i = 0; i < n; ++i)
    {
        int type;
        cin >> type;
        cin.getline(coach, 100);
        cin.getline(coach, 100);
        for (int j = 0; j < 10; ++j)
        {
            cin >> goals[j];
        }
        cin.getline(x, 100);
        cin.getline(x, 100);
        cin >> tg;
        if (type == 0)
        {
            ekipi[i] = new Klub(coach, goals, x, tg);
        }
        else if (type == 1)
        {
            ekipi[i] = new Reprezentacija(coach, goals, x, tg);
        }
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i)
    {
        cout << *ekipi[i];
    }
    cout << "===== DODADI GOLOVI =====" << endl;
    for (int i = 0; i < n; ++i)
    {
        int p;
        cin >> p;
        cout << "dodavam golovi: " << p << endl;
        *ekipi[i] += p;
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i)
    {
        cout << *ekipi[i];
    }
    cout << "===== NAJDOBAR TRENER =====" << endl;
    najdobarTrener(ekipi, n);
    for (int i = 0; i < n; ++i)
    {
        delete ekipi[i];
    }
    delete[] ekipi;
    return 0;
}