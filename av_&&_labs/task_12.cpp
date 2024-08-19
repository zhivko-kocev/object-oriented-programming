#include<iostream>
#include<cstring>
using namespace std;
class Film{
private:
    char name[100]{};
    double rating;
    double revenue;
public:
    Film(){
        strcpy(this->name,"Untitled");
        this->rating=0;
        this->revenue=0;
    }
    Film(char *name,double rating,double revenue){
        strcpy(this->name,name);
        this->rating=rating;
        this->revenue=revenue;
    }
    void setName(char *_name){
        strcpy(this->name,_name);
    }
    void setRevenue(double _revenue){
        this->revenue=_revenue;
    }
    void setRating(double _rating){
        this->rating=_rating;
    }
    void display(){
        cout<<"Name of film: "<<name<<endl;
        cout<<"Rating: "<<rating<<endl;
        cout<<"Revenue: "<<revenue<<endl;
    }
    double getRevenue(){
        return revenue;
    }
};

void printMostPopularFilm(Film *films,int n){
    Film max=films[0];
    for (int i = 0; i < n; ++i) {
        if(films[i].getRevenue()>max.getRevenue()){
            max=films[i];
        }
    }
    max.display();
}
int main() {
    int n;
    cin >> n;
    Film films[100];

    char name[100];
    double rating;
    double revenue;

    for (int i = 0; i < n-1; i++)  {
        cin>>name;
        cin >> rating;
        cin >> revenue;

        // testing constructor with arguments
        films[i] = Film(name, rating, revenue);

    }


    // testing set methods and display for last element
    cin>>name;
    cin >> rating;
    cin >> revenue;
    films[n-1].setName(name);
    films[n-1].setRating(rating);
    films[n-1].setRevenue(revenue);

    cout<<"-->Testing set methods and display()"<<endl;
    films[n-1].display();
    cout<<endl;

    cout<<"-->Testing printMostPopularFilm()"<<endl;
    printMostPopularFilm(films , n);
    return 0;
}
