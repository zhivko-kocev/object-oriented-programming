#include <iostream>
#include <cstring>
enum Zanr{TRILER,KOMEDIJA,DRAMA};
using namespace std;
class EBook{
private:
    char *name;
    int size;
    Zanr genre;
public:
    EBook(){
        this->name=new char [10];
        strcpy(this->name,"Unknown");
        this->size=0;
        this->genre=TRILER;
    }
    EBook(char*name,int size,Zanr genre){
        this->name=new char [strlen(name)+1];
        strcpy(this->name,name);
        this->size=size;
        this->genre=genre;
    }
    EBook(const EBook &e){
        this->name=new char [strlen(e.name)+1];
        strcpy(this->name,e.name);
        this->size=e.size;
        this->genre=e.genre;
    }
    EBook &operator =(const EBook &e){
        if(this!=&e){
            delete [] name;
            this->name=new char [strlen(e.name)+1];
            strcpy(this->name,e.name);
            this->size=e.size;
            this->genre=e.genre;
        }
        return *this;
    }
    void pecati(){
        cout<<size<<"MB-"<<"\""<<name<<"\""<<endl;
    }
    int getMem(){
        return size;
    }
    Zanr getZanr(){
        return genre;
    }
~EBook(){
        delete [] name;
    }

};
class EReader{
private:
    EBook books[6];
    int numBooks;
    int capacity;
public:
    EReader(int capacity=0){
        this->capacity=capacity;
        this->numBooks=0;
    }
    EBook getEBook(int index){
        return books[index];
    }
    int getBroj(){
        return numBooks;
    }
    int getM(){
        int sum=0;
        for (int i = 0; i < numBooks; ++i) {
            sum+=books[i].getMem();
        }
        return sum;
    }
    void dodadiEBook(EBook &e){
        if(numBooks<5 && this->getM()+e.getMem()<=capacity){
            books[numBooks++]=e;
        }
    }
    void pecatiEBooksDrugZanr(Zanr z){
        for (int i = 0; i < numBooks; ++i) {
            if(books[i].getZanr()!=z){
                books[i].pecati();
            }
        }
    }
    float procentNaMemorijaOdZanr(Zanr z){
        int sum=0;
        for (int i = 0; i < numBooks; ++i) {
            if(books[i].getZanr()==z){
                sum+=books[i].getMem();
            }
        }
        return ((float)sum/(float)capacity)*100;
    }
};
int main() {
    // se testira zadacata modularno
    int testCase;
    cin >> testCase;

    int n, memorija, kojzanr;
    char ime[50];

    if (testCase == 1) {
        cout << "===== Testiranje na klasata EBook ======" << endl;
        cin >> ime;
        cin >> memorija;
        cin >> kojzanr; //se vnesuva 0 za TRILER,1 za KOMEDIJA i 2 za DRAMA
        EBook f(ime, memorija, (Zanr) kojzanr);
        f.pecati();
    } else if (testCase == 2) {
        cout << "===== Testiranje na klasata EReader ======" << endl;
        EReader omileno(50);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za TRILER,1 za KOMEDIJA i 2 za DRAMA
            EBook f(ime, memorija, (Zanr) kojzanr);
            omileno.dodadiEBook(f);
        }
        for (int i = 0; i < n; i++)
            (omileno.getEBook(i)).pecati();
      }
    else if (testCase == 3) {
        cout << "===== Testiranje na metodot dodadiEBook() od klasata EReader ======" << endl;
        EReader omileno(50);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            EBook f(ime, memorija, (Zanr) kojzanr);
            omileno.dodadiEBook(f);
        }
        for (int i = 0; i < omileno.getBroj(); i++)
            (omileno.getEBook(i)).pecati();
    } else if (testCase == 4) {
        cout << "===== Testiranje na metodot pecatiEBooksDrugZanr() od klasata EReader ======" << endl;
        EReader omileno(50);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za TRILER,1 za KOMEDIJA i 2 za DRAMA
            EBook f(ime, memorija, (Zanr) kojzanr);
            omileno.dodadiEBook(f);
        }
        cin >> kojzanr;
        omileno.pecatiEBooksDrugZanr((Zanr) kojzanr);

    } else if (testCase == 5) {
        cout << "===== Testiranje na metodot pecatiEBooksDrugZanr() od klasata EReader ======" << endl;
        EReader omileno(50);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za TRILER,1 za KOMEDIJA i 2 za DRAMA
            EBook f(ime, memorija, (Zanr) kojzanr);
            omileno.dodadiEBook(f);
        }
        cin >> kojzanr;
        omileno.pecatiEBooksDrugZanr((Zanr) kojzanr);

    } else if (testCase == 6){
        cout<<"===== Testiranje na metodot procentNaMemorijaOdZanr() od klasata EReader =====" <<endl;
        EReader omileno(40);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za TRILER,1 za KOMEDIJA i 2 za DRAMA
            EBook f(ime, memorija, (Zanr) kojzanr);
            omileno.dodadiEBook(f);
        }
        cin >> kojzanr;
        cout<<"Procent na e-books od dadeniot zanr iznesuva: "<<omileno.procentNaMemorijaOdZanr((Zanr) kojzanr)<<"%\n";

    }

    return 0;
}