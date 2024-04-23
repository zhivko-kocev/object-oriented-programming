#include <iostream>
using namespace std;
/*
Да се креира структура Igrac во која се чуваат податоци за еден играч на компјутерската игра.
За играчот се чуваат информации за корисничкото име на играчот (низа од 15 знаци), број на ниво
до кој играчот е стигнат (цел број) и број на освоени поени (цел број) (10 поени).

Потоа да се креирa структура KompjuterskaIgra во која се чуваат податоци за името на играта
(низа од 20 знаци), низа од играчи кои ја играат играта (најмногу 30) и бројот на играчи. (10 поени)

Треба да се направи функција со потпис (15 поени)

void najdobarIgrac(KompjuterskaIgra *lista, int n)
Оваа функција треба да го испечати името на најдобриот играч на онаа игра која има најголема
популарност (ја играат наjголем број на играчи). Најдобар играч е играчот кој има најголем број на
освоени поени. Ако има повеќе играчи со ист максимален број на освоени поени, најдобар е играчот кој има достигнато најголемо ниво.

Печатењето е во форматот: "Najdobar igrac e igracot so korisnicko ime XXXXX koj ja igra igrata YYYYYY".
(XXXXXX е корисничкото име на најдобриот играч,а YYYYY е името на играта која ја играат најголем број на играчи)

(Забелешка: секогаш ќе има точно еден најдобар играч)

Функционалност на задачата и дополнување на main функцијата (10 поени)

Забелешка: Задачата да се реши во програмскиот јазик C+
*/
typedef struct Igrac
{
    char user[15];
    int nivo;
    int brPoeni;
} Igrac;
typedef struct KompjuterskaIgra
{
    char ime[20];
    Igrac igraci[30];
    int brIgraci;
} KompjuterskaIgra;
void vnesiIgrac(Igrac &igrac)
{
    cin >> igrac.user >> igrac.nivo >> igrac.brPoeni;
}
void vnesiIgra(KompjuterskaIgra &igra)
{
    cin >> igra.ime >> igra.brIgraci;
    for (int i = 0; i < igra.brIgraci; ++i)
    {
        vnesiIgrac(igra.igraci[i]);
    }
}
KompjuterskaIgra najdobra(KompjuterskaIgra *igri, int n)
{
    KompjuterskaIgra max;
    int maxIgraci = 0;
    for (int i = 0; i < n; ++i)
    {
        if (igri[i].brIgraci > maxIgraci)
        {
            maxIgraci = igri[i].brIgraci;
            max = igri[i];
        }
    }
    return max;
}
void najdobarIgrac(KompjuterskaIgra *igri, int n)
{
    KompjuterskaIgra naj = najdobra(igri, n);
    int maxPoeni = 0;
    Igrac max;
    for (int i = 0; i < naj.brIgraci; ++i)
    {
        if (naj.igraci[i].brPoeni > maxPoeni)
        {
            maxPoeni = naj.igraci[i].brPoeni;
            max = naj.igraci[i];
        }
        else if (naj.igraci[i].brPoeni == maxPoeni)
        {
            if (naj.igraci[i].nivo > max.nivo)
            {
                max = naj.igraci[i];
            }
        }
    }
    cout << "Najdobar igrac e igracot so korisnicko ime " << max.user << " koj ja igra igrata " << naj.ime;
}
int main()
{
    int n;
    KompjuterskaIgra igri[20];
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        vnesiIgra(igri[i]);
    }
    najdobarIgrac(igri, n);
    return 0;
}