#include <iostream>
#include <cstring>

using namespace std;

class Country {
private:
    char name[100]{};
    char capital[100]{};
    double area;
    double population;
public:
    Country(char *name = "", char *capital = "", double area = 0, double population = 0) {
        strcpy(this->name, name);
        strcpy(this->capital, capital);
        this->area = area;
        this->population = population;
    }

    ~Country() = default;

    char *getName() {
        return name;
    }

    char *getCapital() {
        return capital;
    }

    double getArea() {
        return area;
    }

    void setArea(double a) {
        area = a;
    }

    double getPopulation() {
        return population;
    }

    void setPopulation(double p) {
        population = p;
    }

    void setName(const char *n) {
        strcpy(name, n);
    }

    void setCapital(const char *c) {
        strcpy(capital, c);
    }
    void display(){
        cout<<"Country: "<<name<<endl;
        cout<<"Capital: "<<capital<<endl;
        cout<<"Area: "<<area<<endl;
        cout<<"Population: "<<population<<endl;

    }
};
void swap(Country &first,Country &second){
    Country tmp=first;
    first=second;
    second=tmp;
}
void sortCountries(Country *countries, int n){
    for (int i = 0; i < n-1; ++i) {
        for (int j = 0; j < n-1; ++j) {
            if(countries[j].getArea()<countries[j+1].getArea()){
                swap(countries[j],countries[j+1]);
            }
        }
    }
}
int main() {
    Country countries[10];
    int n;
    char name[100]{};
    char capital[100]{};
    double area;
    double population;
    cin>>n;
    for (int i = 0; i < n; ++i) {
        cin>>name>>capital>>area>>population;
        countries[i]=Country(name,capital,area,population);
    }
    sortCountries(countries,n);
    for (int i = 0; i < n; ++i) {
        countries[i].display();
    }
    return 0;
}