#include <iostream>
#include <cstring>
using namespace std;
class Zichara{
private:
    char *mesto{};
    int cena;
public:
    Zichara(){
        this->mesto=new char[10];
        strcpy(this->mesto,"Unknown");
        this->cena=0;
    }
    Zichara(char *mesto,int cena){
        this->mesto=new char[strlen(mesto)+1];
        strcpy(this->mesto,mesto);
        this->cena=cena;
    }
    Zichara(const Zichara &z){
        if(this!=&z){
            this->mesto=new char [strlen(z.mesto)+1];
            strcpy(this->mesto,z.mesto);
            this->cena=z.cena;
        }
    }
    Zichara &operator =(const Zichara &z){
        if(this!=&z){
            delete [] this->mesto;
            this->mesto=new char [strlen(z.mesto)+1];
            strcpy(this->mesto,z.mesto);
            this->cena=z.cena;
        }
        return *this;
    }
    ~Zichara(){
        delete [] mesto;
    }
    int getCena() const{
        return cena;
    }
};
class PlaninarskiDom{
private:
    char ime[15]{};
    int ceni[2]{};
    char klasa;
    bool imaZichara;
    Zichara *zichara;
public:
    PlaninarskiDom(){
        strcpy(this->ime,"Unknown");
        this->ceni[0]=0;this->ceni[1]=0;
        this->klasa='F';
        this->imaZichara= false;
        this->zichara= nullptr;
    }
    PlaninarskiDom(char *ime,int *ceni,char klasa){
        strcpy(this->ime,ime);
        this->ceni[0]=ceni[0];this->ceni[1]=ceni[1];
        this->klasa=klasa;
        this->imaZichara=false;
        this->zichara= nullptr;
    }
    PlaninarskiDom(const PlaninarskiDom &p){

        if(this!=&p){
            strcpy(this->ime,p.ime);
            this->ceni[0]=p.ceni[0];this->ceni[1]=p.ceni[1];
            this->klasa=p.klasa;
            this->imaZichara=p.imaZichara;
            this->zichara= p.zichara;
        }
    }
    void setZichara(Zichara &z){
        this->zichara=&z;
        this->imaZichara=true;
    }
    PlaninarskiDom &operator --(){
        if(this->klasa!='F'){
            this->klasa++;
        }
        return *this;
    }
    friend ostream &operator <<(ostream &os,const PlaninarskiDom &p){
           os<<p.ime<<" klasa:"<<p.klasa;
          return p.imaZichara? os<<" so Zichara"<<endl : os<<endl;
    }
    bool operator <=(char k) const{
        return this->klasa >= k;
    }
    void presmetajDnevenPrestoj(int den,int mesec,int &cena){
        try{
            if(!(den>=1&&den<=31) || !(mesec>=1&&mesec<=12)) throw 1;
            if(mesec>=4 && mesec<=8){
                if(imaZichara){
                    cena=ceni[0]+zichara->getCena();
                } else{
                    cena=ceni[0];
                }
            }else{
                if(imaZichara){
                    cena=ceni[1]+zichara->getCena();
                }else{
                    cena=ceni[1];
                }
            }
        }catch(int){
            throw;
        }
    }

};
int main(){

    PlaninarskiDom p; //креирање на нов објект од класата планинарски дом

    //во следниот дел се вчитуваат информации за планинарскиот дом
    char imePlaninarskiDom[15],mestoZichara[30],klasa;
    int ceni[12];
    int dnevnakartaZichara;
    bool daliZichara;
    cin>>imePlaninarskiDom;
    for (int i=0;i<2;i++) cin>>ceni[i];
    cin>>klasa;
    cin>>daliZichara;

    //во следниот дел се внесуваат информации и за жичарата ако постои
    if (daliZichara) {
        cin>>mestoZichara>>dnevnakartaZichara;
        PlaninarskiDom pom(imePlaninarskiDom,ceni,klasa);
        Zichara r(mestoZichara,dnevnakartaZichara);
        pom.setZichara(r);
        p=pom;
    }
    else{
        auto *pok=new PlaninarskiDom(imePlaninarskiDom,ceni,klasa);
        p=*pok;
    }

    //се намалува класата на планинарскиот дом за 2
    --p;
    --p;

    int cena;
    int den,mesec;
    cin>>den>>mesec;
    try{
        p.presmetajDnevenPrestoj(den,mesec,cena);
        cout<<"Informacii za PlaninarskiDomot:"<<endl;
        cout<<p;
        if (p<='D')
            cout<<"Planinarskiot dom za koj se vneseni informaciite ima klasa poniska ili ista so D\n";
        cout<<"Cenata za "<<den<<"."<<mesec<<" e "<<cena;
    }
    catch (int){
        cout<<"Mesecot ili denot e greshno vnesen!";
    }
}