#include <iostream>
#include <cstring>
using namespace std;
/*
Да се креира структура Воз во која се чуваат податоци за релацијата по која се
движи возот (низа од најмногу 50 знаци), предвиден бројот на километри што треба
да се поминат (реален број), како и бројот на патници во возот (цел број).
Потоа да се креирa структура ZeleznickaStanica во која се чуваат податоци за
градот во кој се наоѓа (низа од 20 знаци), низа од возови што поаѓаат од
станицата (најмногу 30) и бројот на возови (цел број).
Треба да се направи функција со потпис
void najkratkaRelacija(ZeleznickaStanica* zs, int n, char* grad)
во која се печати релацијата и бројот на километри на возот што поминува
најкратка релација (најмалку километри), а поаѓа од железничката станица од
градот што се проследува како влезен аргумент. Ако има повеќе возови со ист
најмал број на километри, да се испечати релацијата на последниот таков.
Забелешка: Задачата да се реши во програмскиот јазик C++
*/
typedef struct Voz
{
    char relacija[50];
    float kilometri;
    int brPatnici;
} Voz;
typedef struct ZeleznickaStanica
{
    char grad[20];
    Voz vozovi[30];
    int brVozovi;
} ZeleznickaStanica;
void vnesiVoz(Voz &v)
{
    cin >> v.relacija >> v.kilometri >> v.brPatnici;
}
void vnesiZeleznicka(ZeleznickaStanica &z)
{
    cin >> z.grad >> z.brVozovi;
    for (int i = 0; i < z.brVozovi; ++i)
    {
        vnesiVoz(z.vozovi[i]);
    }
}
ZeleznickaStanica istGrad(ZeleznickaStanica *stanici, int n, char *grad)
{
    for (int i = 0; i < n; ++i)
    {
        if (strcmp(stanici[i].grad, grad) == 0)
        {
            return stanici[i];
        }
    }
}
void najkratkaRelacija(ZeleznickaStanica *z, int n, char *grad)
{
    ZeleznickaStanica gr = istGrad(z, n, grad);
    int flag = 1;
    float min;
    char rel[50];
    for (int i = 0; i < gr.brVozovi; ++i)
    {
        if (flag)
        {
            min = gr.vozovi[i].kilometri;
            strcpy(rel, gr.vozovi[i].relacija);
            flag = 0;
            continue;
        }
        if (gr.vozovi[i].kilometri <= min)
        {
            min = gr.vozovi[i].kilometri;
            strcpy(rel, gr.vozovi[i].relacija);
        }
    }
    cout << "Najkratka relacija: " << rel << " (" << min << " km)" << endl;
}
int main()
{

    int n;
    cin >> n;

    ZeleznickaStanica zStanica[100];
    for (int i = 0; i < n; i++)
    {
        vnesiZeleznicka(zStanica[i]);
    }

    char grad[25];
    cin >> grad;

    najkratkaRelacija(zStanica, n, grad);
    return 0;
}
