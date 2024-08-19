#include <stdio.h>
/*
Во програмскиот јазик C да се креира структура Vozenje за опишување на адреналински возења во забавен парк. Структурата треба да содржи: (5 поени)

Име на возењето ( низа од 100 знаци)
Времетраење во минути (цел број)
Цена (децимален број)
Дали има студентски попуст (1-да, 0-не)
Да се креира структура ZabavenPark, што содржи: (10 поени)

Име на забавниот парк (низа од 100 знаци)
Локација (низа од 100 знаци)
Низа од адреналински возења во паркот (низа од максимум 100 елементи од структурата Vozenje)
Број на елементи во низата (цел број)
Да се креира функција print за печатење на информациите за сите возења во забавниот парк во формат: (10 поени)

[Ime na parkot] [Lokacija]
[Ime1] [Vremetraenje1] [Cena1]
[Ime2] [Vremetraenje2] [Cena2]
[Ime3] [Vremetraenje3] [Cena3]
...
Да се креира функција najdobar_park, што прима низа од променливи од типот ZabavenPark и го печати името
и локацијата на паркот кој е најефтин за посета од страна на студенти. Најефтин парк е оној што
содржи најголем број возења со студентски попуст. Ако повеќе паркови ги делат овие карактеристики, да се
испечати паркот со најголемото времетраење од сите возења.* (20 поени)*

Да се дополни функцијата main (5 поени).
*/
typedef struct Vozenje
{
    char ime[100];
    int vreme;
    float cena;
    int popust;
} Vozenje;
typedef struct ZabavenPark
{
    char ime[100];
    char lokacija[100];
    Vozenje vozenja[100];
    int brVozenja;
} ZabavenPark;
void vnesiVozenje(Vozenje *v)
{
    scanf("%s %d %f %d", v->ime, &v->vreme, &v->cena, &v->popust);
}
void vnesiPark(ZabavenPark *p)
{
    scanf("%s %s %d", p->ime, p->lokacija, &p->brVozenja);
    for (int i = 0; i < p->brVozenja; ++i)
    {
        vnesiVozenje(&p->vozenja[i]);
    }
}
void print(ZabavenPark *parkovi, int n)
{
    for (int i = 0; i < n; ++i)
    {
        printf("%s %s\n", parkovi[i].ime, parkovi[i].lokacija);
        for (int j = 0; j < parkovi[i].brVozenja; ++j)
        {
            printf("%s %d %.2f\n", parkovi[i].vozenja[j].ime, parkovi[i].vozenja[j].vreme, parkovi[i].vozenja[j].cena);
        }
    }
}
int maxTraenje(ZabavenPark park)
{
    int sum = 0;
    for (int i = 0; i < park.brVozenja; ++i)
    {
        sum += park.vozenja[i].vreme;
    }
    return sum;
}
ZabavenPark najPopust(ZabavenPark *parkovi, int n)
{
    int sum, maxSum = 0, maxVreme = 0;
    ZabavenPark max;
    for (int i = 0; i < n; ++i)
    {
        sum = 0;
        for (int j = 0; j < parkovi[i].brVozenja; ++j)
        {
            if (parkovi[i].vozenja[j].popust == 1)
            {
                sum += parkovi[i].brVozenja;
            }
        }
        if (sum > maxSum)
        {
            maxSum = sum;
            max = parkovi[i];
            maxVreme = maxTraenje(parkovi[i]);
        }
        else if (sum == maxSum)
        {
            if (maxTraenje(parkovi[i]) > maxVreme)
            {
                maxSum = sum;
                max = parkovi[i];
                maxVreme = maxTraenje(parkovi[i]);
            }
        }
    }
    return max;
}
void najdobar_park(ZabavenPark *parkovi, int n)
{
    ZabavenPark naj = najPopust(parkovi, n);
    printf("Najdobar park: %s %s", naj.ime, naj.lokacija);
}
int main()
{
    int n;
    scanf("%d", &n);
    ZabavenPark parkovi[20];
    for (int i = 0; i < n; ++i)
    {
        vnesiPark(&parkovi[i]);
    }
    print(parkovi, n);
    najdobar_park(parkovi, n);
    return 0;
}