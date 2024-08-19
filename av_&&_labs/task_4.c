#include <stdio.h>
struct grad{
    char ime[20];
    long ziteli;
};
struct pretsedatel{
    char ime[20];
    char prezime[20];
    char partija[20];
};
struct drzava{
    char ime[20];
    struct pretsedatel p;
    struct grad glavenGrad;
    long brZiteli;
};
void vnesiDrzava(struct drzava *d){
    scanf("%s",d->ime);
    scanf("%s",d->p.ime);
    scanf("%s",d->p.prezime);
    scanf("%s",d->p.partija);
    scanf("%s",d->glavenGrad.ime);
    scanf("%ld",&d->glavenGrad.ziteli);
    scanf("%ld",&d->brZiteli);
}
void pecatiPretsedatel(struct drzava d){
    printf("%s %s",d.p.ime,d.p.prezime);
}
int main(){
    struct drzava drzavi[100];
    struct drzava max;
    int n;
    scanf("%d",&n);
    for (int i = 0; i < n; ++i) {
        vnesiDrzava(&drzavi[i]);
    }
    max=drzavi[0];
    for (int i = 0; i < n; ++i) {
        if(max.glavenGrad.ziteli<drzavi[i].glavenGrad.ziteli){
            max=drzavi[i];
        }
    }
    pecatiPretsedatel(max);
    return 0;
}