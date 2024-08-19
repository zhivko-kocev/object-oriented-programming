#include<stdio.h>
/*
Да се креира структура SkiLift во која се чуваат податоци за името на ски лифтот (низа од 15 знаци), максимален број на корисници што може да опслужи на едно возење, дали е пуштен во функција.

Потоа да се креирa структура SkiCenter во која се чуваат податоци за името на скијачкиот центар, држава во која се наоѓа (низи од 20 знаци), низа од ски лифтови (макс 20) што ги има и број на ски лифтови.

Треба да се направи функција со потпис

void najgolemKapacitet(SkiCenter *sc, int n)
која што ќе го отпечати ски центарот што има најголем капацитет за опслужување скијачи (вкупниот број на скијачи кои може да се опслужуваат во еден момент вкупно на сите ски лифтови во центарот). 
Доколку два ски центри имаат ист капацитет, тогаш се печати оној кој има поголем број на ски лифтови. Притоа треба да се испечатат во посебен ред името, државата и капацитетот на ски центарот. 
Кога се пресметува капацитет на еден ски центар во предвид се земаат само ски лифтовите кои се поставени дека се во функција.
*/
typedef struct SkiLift {
    char ime[15];
    int maxKorisnici;
    int daliEVoFunkcija;
} SkiLift;
typedef struct SkiCenter {
    char ime[20];
    char drzava[20];
    SkiLift skilifts[20];
    int brSkilifts;
} SkiCenter;

int kapacitet(SkiCenter centar){
    int sum=0;
    for (int i = 0; i < centar.brSkilifts; ++i) {
        if(centar.skilifts[i].daliEVoFunkcija==1){
            sum+=centar.skilifts[i].maxKorisnici;
        }
    }
    return sum;
}
void najgolemKapacitet(SkiCenter *centri,int n){
    SkiCenter max=centri[0];
    int maxVk=0;
    for (int i = 0; i < n; ++i) {
        if(kapacitet(centri[i])>maxVk){
            max=centri[i];
            maxVk= kapacitet(centri[i]);
        }else if(kapacitet(centri[i])==maxVk){
            if(centri[i].brSkilifts>max.brSkilifts){
                max=centri[i];
                maxVk= kapacitet(centri[i]);
            }
        }
    }
    printf("%s\n%s\n%d",max.ime,max.drzava,maxVk);
}
int main() {
    int n;
    SkiCenter centri[10];
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", centri[i].ime);
        scanf("%s", centri[i].drzava);
        scanf("%d", &centri[i].brSkilifts);
        for (int j = 0; j < centri[i].brSkilifts; ++j) {
            scanf("%s %d %d", centri[i].skilifts[j].ime, &centri[i].skilifts[j].maxKorisnici,
                  &centri[i].skilifts[j].daliEVoFunkcija);
        }
    }

    najgolemKapacitet(centri,n);

    return 0;
}