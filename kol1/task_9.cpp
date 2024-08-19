#include <iostream>
/*
The same text from task_8.c just in cpp.
*/
using namespace std;
typedef struct Laptop
{
    char firma[100];
    float inchi;
    bool touch;
    int cena;
} Laptop;
typedef struct ITStore
{
    char ime[100];
    char lokacija[100];
    Laptop laptopi[100];
    int brLaptopi;
} ITStore;
void vnesiLaptop(Laptop &l)
{
    cin >> l.firma >> l.inchi >> l.touch >> l.cena;
}
void vnesiITStore(ITStore &s)
{
    cin >> s.ime >> s.lokacija >> s.brLaptopi;
    for (int i = 0; i < s.brLaptopi; ++i)
    {
        vnesiLaptop(s.laptopi[i]);
    }
}
void pecatiProdavnica(ITStore *s, int n)
{
    for (int i = 0; i < n; ++i)
    {
        cout << s[i].ime << " " << s[i].lokacija << endl;
        for (int j = 0; j < s[i].brLaptopi; ++j)
        {
            cout << s[i].laptopi[j].firma << " " << s[i].laptopi[j].inchi << " " << s[i].laptopi[j].cena << endl;
        }
    }
}
void najeftina_ponuda(ITStore *s, int n)
{
    ITStore mesto;
    Laptop min;
    int flag = 1;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < s[i].brLaptopi; ++j)
        {
            if (flag)
            {
                if (s[i].laptopi[j].touch == 1)
                {
                    mesto = s[i];
                    min = s[i].laptopi[j];
                    flag = 0;
                    continue;
                }
                else
                {
                    continue;
                }
            }
            if (s[i].laptopi[j].cena < min.cena && s[i].laptopi[j].touch == 1)
            {
                min = s[i].laptopi[j];
                mesto = s[i];
            }
        }
    }
    cout << "Najeftina ponuda ima prodavnicata: \n"
         << mesto.ime << " " << mesto.lokacija << endl;
    cout << "Najniskata cena iznesuva: " << min.cena;
}
int main()
{
    ITStore s[100];
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        vnesiITStore(s[i]);
    }
    pecatiProdavnica(s, n);
    najeftina_ponuda(s, n);

    return 0;
}