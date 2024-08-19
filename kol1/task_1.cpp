#include <iostream>
#include <cstring>
using namespace std;
/*
Да се дефинира класата Pesna во која се чуваат информации за (5 поени):

име на песна (динамички алоцирано поле од знаци)
времетраење на песната во минути
тип на песна кој може да биде: поп, рап или рок (енумерација tip)
Да се обезбедат сите потребни методи за класата за правилно функционирање на програмата. (10 поени)

Дополнително за оваа класа да се дефинира методот:

pecati() - функција во која ќе се печатат одделени со цртичка(-): името на
песната во наводници и времетраењето на песната со постфикс min. (5 поени)
Да се креира класата CD во која се чуваат информации за (5 поени):

низа од песни снимени на CD-то (Поле од најмногу 10 објекти од класата Pesna )
број на песни снимени на CD-то
максимално времетраење на песните на CD-то (во минути)
Да се обезбедат сите потребни методи за класата за правилно функционирање на програмата. (5 поени)

Дополнително за оваа класа да се дефинираат методите:

dodadiPesna (Pesna p) - со кој се додава песната p на CDто, но само ако има доволно преостанато место (земајќи го
предвид максималното времетраење на песните на CDто и времетраењата на песните на CD-то) и ако има помалку од 10 песни на CD-то. (10 поени)
pecatiPesniPoTip(tip t) – со кој се печатат информациите за сите песни од тип t (поп, рап или рок). (10 поени)
Комплетна функционалност (5 поени).
*/
enum genre
{
    POP,
    RAP,
    ROCK
};

class Song
{
private:
    char *name;
    int length;
    genre type;

public:
    Song()
    {
        name = nullptr;
        length = 2;
        type = POP;
    }

    Song(char *name, int length, genre type)
    {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->length = length;
        this->type = type;
    }
    Song &operator=(Song const &s)
    {
        if (this != &s)
        {
            delete[] name;
            name = new char[strlen(s.name) + 1];
            strcpy(name, s.name);
            length = s.length;
            type = s.type;
        }
        return *this;
    }
    void print()
    {
        cout << "\"" << name << "\"-" << length << "min" << endl;
    }
    int getLenght() const
    {
        return length;
    }
    genre getGenre()
    {
        return type;
    }
    char *getName()
    {
        return name;
    }
    ~Song() = default;
    ;
};
class CD
{
private:
    Song *songs;
    int numSongs;
    int cdLength;
    int momLength = 0;

public:
    CD()
    {
        numSongs = 0;
        cdLength = 0;
        songs = nullptr;
    }
    CD(int length)
    {
        cdLength = length;
        numSongs = 0;
        songs = nullptr;
    }
    void addSong(Song const &s)
    {
        if (momLength + s.getLenght() <= cdLength && numSongs < 10)
        {
            if (!numSongs)
            {
                this->songs = new Song[numSongs + 1];
                songs[numSongs++] = s;
                momLength = s.getLenght();
            }
            else
            {
                Song *tmp = new Song[numSongs + 1];
                for (int i = 0; i < numSongs; ++i)
                {
                    tmp[i] = songs[i];
                }
                tmp[numSongs++] = s;
                delete[] songs;
                songs = tmp;
                momLength += s.getLenght();
            }
        }
    }
    Song getSong(int index)
    {
        return songs[index];
    }
    void printSongsByGenre(genre type)
    {
        for (int i = 0; i < numSongs; ++i)
        {
            if (songs[i].getGenre() == type)
            {
                cout << "\"" << songs[i].getName() << "\"-" << songs[i].getLenght() << "min" << endl;
            }
        }
    }
    int getNum() const
    {
        return numSongs;
    }
    ~CD()
    {
        delete[] songs;
    }
};

int main()
{
    int testCase;
    cin >> testCase;

    int n, minuti, kojtip;
    char ime[50];

    if (testCase == 1)
    {
        cout << "===== Testiranje na klasata Pesna ======" << endl;
        cin >> ime;
        cin >> minuti;
        cin >> kojtip; // se vnesuva 0 za POP,1 za RAP i 2 za ROK
        Song p(ime, minuti, (genre)kojtip);
        p.print();
    }
    else if (testCase == 2)
    {
        cout << "===== Testiranje na klasata CD ======" << endl;
        CD omileno(20);
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; // se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Song p(ime, minuti, (genre)kojtip);
            omileno.addSong(p);
        }
        for (int i = 0; i < n; i++)
            (omileno.getSong(i)).print();
    }
    else if (testCase == 3)
    {
        cout << "===== Testiranje na metodot dodadiPesna() od klasata CD ======" << endl;
        CD omileno(20);
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; // se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Song p(ime, minuti, (genre)kojtip);
            omileno.addSong(p);
        }
        for (int i = 0; i < omileno.getNum(); i++)
            (omileno.getSong(i)).print();
    }
    else if (testCase == 4)
    {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
        CD omileno(20);
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; // se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Song p(ime, minuti, (genre)kojtip);
            omileno.addSong(p);
        }
        cin >> kojtip;
        omileno.printSongsByGenre((genre)kojtip);
    }
    else if (testCase == 5)
    {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
        CD omileno(20);
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; // se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Song p(ime, minuti, (genre)kojtip);
            omileno.addSong(p);
        }
        cin >> kojtip;
        omileno.printSongsByGenre((genre)kojtip);
    }
    return 0;
}
