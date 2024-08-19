#include <stdio.h>
#include <string.h>
/*
Да се креира структура Proizvod во која се чуваат податоци за кодот напрозиводот (низа од 20 знаци),
единична цена на производ (цел број), бројот на достапни производи кои ги има во еден магацин (цел број) .

Потоа да се креирa структура Narachka во која се чуваат податоци за името лицето кое ја прави нарачката
(низи од 15 знаци), низа од Proizvodi (максимум 10) кои ги има во нарачката, низа од бројот на нарачани
производи за секоја производ посебно (максимум10) и бројот на производи во нарачката .

Треба да се направи функција со потпис

void pecatiFaktura(Narachka n)

која што ќе ги отпечати една фактура за една нарачка (n) .

Во фактурата во првиот ред се печати: Faktura za XXXXX, каде XXXXX е името на лицето кое ја прави нарачката.

Ако сите производи може да се нарачаат печатат нарачаните производи, подредени по азбучен ред според кодот на производот.
Во следните редови, во секој ред посебно се печати кодот на производот, единична цена на производот, број на нарачани
производи и вкупната цена на производот (сите се одделени со едно празно место) . Исто така бројот на достапни производи од
тој производ да се ажурира (да се намали за бројот на нарачани производи од тој производ). Во последниот ред да се отпечати:
Vkupnata suma na fakturata e XXX, каде XXX е вкупната сума за цените за сите нарачани производи.

Ако постои производ кој не може да биде нарачан затоа што во магацинот не се достапни нарачаниот број производи тогаш
не може да се изготви фактура за нарачката. На екранот да се отпечати: Fakturata ne moze da se izgotvi.
*/
typedef struct Proizvod
{
    char kod[20];
    int cena, dostapni;
} Proizvod;
typedef struct Narachka
{
    char ime[15];
    Proizvod proizvodi[10];
    int narachani[10];
    int n;
} Narachka;
void swap(Proizvod *p1, Proizvod *p2)
{
    Proizvod tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}
void sortiraj(Proizvod *niza, int n)
{
    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = 0; j < n - 1; ++j)
        {
            if (strcmp(niza[j].kod, niza[j + 1].kod) > 0)
            {
                swap(&niza[j], &niza[j + 1]);
            }
        }
    }
}
void pecatiFaktura(Narachka n)
{
    printf("Faktura za %s\n", n.ime);
    int vk = 0;
    for (int i = 0; i < n.n; ++i)
    {
        int vkupno = (n.proizvodi[i].cena) * (n.narachani[i]);
        if (n.narachani[i] > n.proizvodi[i].dostapni)
        {
            printf("Fakturata ne moze da se izgotvi");
            return;
        }
        printf("%s %d %d %d\n", n.proizvodi[i].kod, n.proizvodi[i].cena, n.narachani[i], vkupno);
        vk += vkupno;
    }
    printf("Vkupnata suma na fakturata e %d", vk);
}
void azuriraj(Narachka *narachka)
{
    for (int i = 0; i < narachka->n; ++i)
    {
        narachka->proizvodi[i].dostapni -= narachka->narachani[i];
    }
}
int main()
{

    Narachka narachka;

    scanf("%s %d", narachka.ime, &narachka.n);

    for (int i = 0; i < narachka.n; ++i)
    {

        scanf("%s %d %d", narachka.proizvodi[i].kod, &narachka.proizvodi[i].cena, &narachka.proizvodi[i].dostapni);
    }

    for (int j = 0; j < narachka.n; ++j)
    {
        scanf("%d", &narachka.narachani[j]);
    }
    sortiraj(narachka.proizvodi, narachka.n);
    pecatiFaktura(narachka);
    azuriraj(&narachka);
    return 0;
}