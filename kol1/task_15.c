#include <stdio.h>
/*
Да се дефинира структура RabotnaNedela во која се чуваат бројот на работни часови за секој работен ден во неделата (5 дена) и број на неделата.
Потоа да се дефинира структура Rabotnik за кој се чува име (низа од 50 знаци) и низа од работни недели (макс 4).

Да се имплементираат следните функции:

int maxNedela(Rabotnik *r) која за проследениот работник ќе го врати бројот на неделата со најмногу работни часови
void table(Rabotnik *r, int n) која за низата од работници ќе отпечати приказ во следниот формат:
Пример

Rab     1   2   3   4   Vkupno
Brianna 192 238 226 225 881
Ava     236 231 184 212 863
Matthew 236 235 219 243 933
Alyssa  240 254 217 228 939
Emma    247 205 204 242 898
каде во секој ред се печати името на работникот и вкупниот број на работни часови за секоја работна недела, како и
вкупниот број на часови за сите недели. Во рамките на редот податоците се разделени со знак за табулатор \t.
*/
#define NEDELI 4
#define DENOVI 5

struct RabotnaNedela
{
    int casovi[5];
};
typedef struct RabotnaNedela RN;

struct Rabotnik
{
    char ime[50];
    RN nedeli[4];
};

typedef struct Rabotnik R;

int zbirNedela(RN nedela)
{
    int zbir = 0;
    for (int i = 0; i < 5; ++i)
    {
        zbir += nedela.casovi[i];
    }
    return zbir;
}

void table(R *rabotnici, int n)
{
    printf("Rab\t1\t2\t3\t4\tVkupno\n");
    for (int i = 0; i < n; ++i)
    {
        printf("%s\t%d\t%d\t%d\t%d\t%d\n", rabotnici[i].ime,
               zbirNedela(rabotnici[i].nedeli[0]),
               zbirNedela(rabotnici[i].nedeli[1]), zbirNedela(rabotnici[i].nedeli[2]),
               zbirNedela(rabotnici[i].nedeli[3]),
               zbirNedela(rabotnici[i].nedeli[3]) + zbirNedela(rabotnici[i].nedeli[2]) +
                   zbirNedela(rabotnici[i].nedeli[1]) + zbirNedela(rabotnici[i].nedeli[0]));
    }
}

int maxNedela(R *rabotnik)
{
    int max = 0, maxind = 0;
    for (int i = 0; i < 4; ++i)
    {
        int mom = 0;
        for (int j = 0; j < 5; ++j)
        {
            mom += rabotnik->nedeli[i].casovi[j];
        }
        if (mom > max)
        {
            max = mom;
            maxind = i + 1;
        }
    }
    return maxind;
}

int main()
{
    int n;
    scanf("%d", &n);
    R rabotnici[n];
    int i;
    for (i = 0; i < n; ++i)
    {
        scanf("%s", rabotnici[i].ime);
        int j;
        for (j = 0; j < NEDELI; ++j)
        {
            int k;
            for (k = 0; k < DENOVI; ++k)
            {
                scanf("%d", &rabotnici[i].nedeli[j].casovi[k]);
            }
        }
    }
    printf("TABLE\n");
    table(rabotnici, n);
    printf("MAX NEDELA NA RABOTNIK: %s\n", rabotnici[n / 2].ime);
    printf("%d\n", maxNedela(&rabotnici[n / 2]));
    return 0;
}
