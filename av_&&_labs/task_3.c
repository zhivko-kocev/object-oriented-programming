//
// Created by Zike Kocev on 22.2.23.
//
#include <stdio.h>
#include <ctype.h>
struct poeni{
    int b1;
    int b2;
    int b3;
    int b4;
};
struct Student{
    char ime[20];
    char prezime[20];
    char indeks [10];
    struct poeni p;
};
int vkupno(struct Student s){
    return s.p.b1+s.p.b2+s.p.b3+s.p.b4;
}
void sort(struct Student *s,int n){
    for (int i = 0; i < n-1; ++i) {
        if(vkupno(s[i])< vkupno(s[i+1])){
            struct Student tmp;
            tmp=s[i];
            s[i]=s[i+1];
            s[i+1]=tmp;
        }
    }
}
void vnesiStudent(struct Student *s){
    scanf("%s",s->ime);
    scanf("%s",s->prezime);
    scanf("%s",s->indeks);
    scanf("%d%d%d%d",&s->p.b1,&s->p.b2,&s->p.b3,&s->p.b4);
}
void pecatiStudent(struct Student s){
    printf("%s %s %s %d",s.ime,s.prezime,s.indeks, vkupno(s));
}
void smeni(char *i,char *p){
    i[0]=toupper(i[0]);
    p[0]=toupper(p[0]);
}
int main(){
    struct Student studenti[100];
    int n;
    scanf("%d",&n);
    for (int i = 0; i < n; ++i) {
        vnesiStudent(&studenti[i]);
    }
    sort(studenti,n);
    for (int i = 0; i < n; ++i) {
        smeni(studenti[i].ime,studenti[i].prezime);
        pecatiStudent(studenti[i]);
        printf("\n");
    }
    return 0;
}