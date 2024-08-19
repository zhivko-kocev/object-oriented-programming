//
// Created by Zike Kocev on 21.2.23.
//
#include <stdio.h>
struct dataNaRagjanje{
    int den;
    int mesec;
    int godina;
};
struct licniPodatoci{
    char ime[20];
    char prezime[20];
    struct dataNaRagjanje data;
};
struct Student{
    struct licniPodatoci lp;
    char nasoka[10];
    char indeks[10];

};
void enterStudent(struct Student *s){
    scanf("%s",s->lp.ime);
    scanf("%s",s->lp.prezime);
    scanf("%02d%02d%d",&s->lp.data.den,&s->lp.data.mesec,&s->lp.data.godina);
    scanf("%s",s->nasoka);
    scanf("%s",s->indeks);

}
void printStudent(struct Student s){
    printf("%s %s roden %02d %02d %02d\n"
           "Student na nasoka %s so indeks %s"
           ,s.lp.ime,s.lp.prezime,s.lp.data.den,s.lp.data.mesec,s.lp.data.godina,s.nasoka,s.indeks);
}
int main(){
    struct Student finkas;
    enterStudent(&finkas);
    printStudent(finkas);
    return 0;
}