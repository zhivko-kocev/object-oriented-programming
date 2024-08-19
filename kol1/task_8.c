#include <stdio.h>
/*
Во програмскиот јазик C да се креира структура Laptop за опишување на спецификациите на даден
преносен компјутер. Структурата треба да содржи: (5 поени)

Фирма која го произведува ( низа од 100 знаци)
Големина на монитор во инчи (реален број)
Дали е со touch или не (булова променлива)
Цена (цел број)
Да се креира структура ITStore, што содржи: (5 поени)

Име на продавницата (низа од 100 знаци)
Локација (низа од 100 знаци)
Низа од достапни лаптопи (низа од максимум 100 елементи од структурата Laptop)
Број на елементи во низата (цел број)
Да се креира функција print за печатење на информациите за сите лаптопи во една продавница во формат: (10 поени)

[Ime na prodavnicata] [Lokacija]
[Marka1] [dim_monitor1] [Cena1]
[Marka2] [dim_monitor2] [Cena2]
[Marka3] [dim_monitor3] [Cena3]
...
Да се креира функција najeftina_ponuda, што прима низа од променливи од типот ITStore и го печати името
и локацијата на онаа продавница која нуди најевтин преносен компјутер и неговата цена. Најефтин
преносен компјутер е оној што има најниска цена и плус опција за touch. Ако има повеќе такви продавници,
се печати прво најдената.* (15 поени)*

Да се дополни функцијата main (10 поени).

Од тастатура се внесува бројот на продавници, па потоа за секоја продавница се внесуваат името и локацијата,
а потоа бројот на компјутери, па за секој од компјутерите фирма која го произведува, големина на монитор,
дали има touch и цена. Потоа се печатат сите внесени продавници и најевтината понуда.
*/
typedef struct Laptop
{
    char firma[100];
    float inchi;
    int touch;
    int cena;
} Laptop;
typedef struct ITStore
{
    char ime[100];
    char lokacija[100];
    Laptop laptopi[100];
    int brLaptopi;
} ITStore;
void vnesiLaptop(Laptop *l)
{
    scanf("%s %f %d %d", l->firma, &l->inchi, &l->touch, &l->cena);
}
void vnesiITStore(ITStore *s)
{
    scanf("%s %s %d", s->ime, s->lokacija, &s->brLaptopi);
    for (int i = 0; i < s->brLaptopi; ++i)
    {
        vnesiLaptop(&s->laptopi[i]);
    }
}
void pecatiProdavnica(ITStore *s, int n)
{
    for (int i = 0; i < n; ++i)
    {
        printf("%s %s", s[i].ime, s[i].lokacija);
        for (int j = 0; j < s[i].brLaptopi; ++j)
        {
            printf("%s %.2f %d", s[i].laptopi[j].firma, s[i].laptopi[j].inchi, s[i].laptopi[j].cena);
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
    printf("Najeftina ponuda ima prodavnicata:\n%s %s\n", mesto.ime, mesto.lokacija);
    printf("Najniskata cena iznesuva: %d", min.cena);
}
int main()
{
    ITStore s[100];
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        vnesiITStore(&s[i]);
    }
    pecatiProdavnica(s, n);
    najeftina_ponuda(s, n);

    return 0;
}