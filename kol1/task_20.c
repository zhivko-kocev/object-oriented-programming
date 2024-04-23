#include <stdio.h>
/*
Во програмскиот јазик C да се креира структура Pacient и истата треба да содржи: (5 поени)

Име и презиме на пациентот ( низа од макс. 100 знаци)
Дали е здраствено осигуран (1-да, 0-не)
Број на прегледи во текот на последниот месец (цел број)
Да се креира структура MaticenDoktor, која во себе содржи: (5 поени)

Име на докторот (низа од 100 знаци)
Број на пациенти (цел број)
Листа од пациенти (низа од максимум 200 елементи од структурата Pacient)
Цена на преглед (децимален број)
Да се креираат метода najuspesen_doktor, која прима низа од променливи од типот
MaticenDoktor и нивниот број; и го печати името, заработената сума и бројот на прегледи на оној
доктор кој заработил најголема сума од пациенти кои ги прегледувал приватно (не се здраствено осигурани) (10 поени).
Доколку два или повеќе доктори имаат иста сума, тогаш се печати оној доктор кој има направено најголем број на
прегледи вкупно во текот на последниот месец. (20 поени)

Функционалност (5 поени).
*/
typedef struct Pacient
{
    char ime[100];
    int zdrastveno;
    int pregledi;
} Pacient;
typedef struct MaticenDoktor
{
    char ime[100];
    int br_pac;
    Pacient niza[200];
    float cena;

} doktor;
int privatno(doktor d)
{
    int suma = 0;
    for (int i = 0; i < d.br_pac; ++i)
    {
        if (d.niza[i].zdrastveno == 0)
        {
            suma += d.niza[i].pregledi;
        }
    }
    return suma;
}
int vkupno(doktor d)
{
    int suma = 0;
    for (int i = 0; i < d.br_pac; ++i)
    {
        suma += d.niza[i].pregledi;
    }
    return suma;
}
void najuspesen_doktor(doktor *d, int n)
{
    doktor max = d[0];
    for (int i = 1; i < n; ++i)
    {
        if (((float)privatno(d[i]) * d[i].cena) > ((float)privatno(max) * max.cena))
        {
            max = d[i];
        }
        else if (((float)privatno(d[i]) * d[i].cena) == ((float)privatno(max) * max.cena))
        {
            if (vkupno(d[i]) > vkupno(max))
            {
                max = d[i];
            }
        }
    }
    printf("%s %.2f %d", max.ime, (float)privatno(max) * max.cena, vkupno(max));
}
int main()
{
    int i, j, n;
    doktor md[200];
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        // ime na doktor
        scanf("%s", md[i].ime);
        // broj na pacienti
        scanf("%d", &md[i].br_pac);
        // cena na pregled
        scanf("%f", &md[i].cena);

        for (j = 0; j < md[i].br_pac; j++)
        {
            scanf("%s", md[i].niza[j].ime);
            scanf("%d", &md[i].niza[j].zdrastveno);
            scanf("%d", &md[i].niza[j].pregledi);
        }
    }
    najuspesen_doktor(md, n);

    return 0;
}
//
// Created by Zike Kocev on 28.2.23.
//
// #include<stdio.h>
// typedef struct Pacient{
//    char ime[100];
//    int zdrastveno;
//    int pregledi;
//}Pacient;
// typedef struct MaticenDoktor{
//    char ime[100];
//    int br_pac;
//    Pacient niza[200];
//    float cena;
//
//}doktor;
// int privatno(doktor d){
//    int suma=0;
//    for (int i = 0; i < d.br_pac; ++i) {
//        if(d.niza[i].zdrastveno==0){suma+=d.niza[i].pregledi;}
//    }
//    return suma;
//}
// int vkupno(doktor d){
//    int suma=0;
//    for (int i = 0; i <d.br_pac ; ++i) {
//        suma+=d.niza[i].pregledi;
//    }
//    return suma;
//}
// void najuspesen_doktor(doktor *d,int n){
//    float maxProfit= 0;
//    int maxVk= 0;
//    doktor max;
//    for (int i = 0; i < n; ++i) {
//        float profit=(float)privatno(d[i]) * d[i].cena;
//        int vk=vkupno(d[i]);
//        if(profit>maxProfit){
//            maxProfit=profit;
//            maxVk=vk;
//            max=d[i];
//        }else if(profit==maxProfit){
//            if(vk>maxVk){
//                maxVk=vk;
//                maxProfit=profit;
//                max=d[i];
//            }
//        }
//    }
//    printf("%s %.2f %d",max.ime,maxProfit,maxVk);
//}
// int main()
//{
//    int i, j, n;
//    doktor md[200];
//    scanf("%d", &n);
//    for (i = 0; i < n; i++){
//        //ime na doktor
//        scanf("%s", md[i].ime);
//        //broj na pacienti
//        scanf("%d", &md[i].br_pac);
//        //cena na pregled
//        scanf("%f", &md[i].cena);
//
//        for (j = 0; j < md[i].br_pac; j++){
//            scanf("%s", md[i].niza[j].ime);
//            scanf("%d", &md[i].niza[j].zdrastveno);
//            scanf("%d", &md[i].niza[j].pregledi);
//        }
//    }
//    najuspesen_doktor(md, n);
//
//    return 0;
//}
