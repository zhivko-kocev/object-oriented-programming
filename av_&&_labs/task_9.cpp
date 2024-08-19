#include <iostream>
#include <cstring>
using namespace std;
class Movie{
private:
    char name[100]{};
    double rating;
    double revenue;
public:
    Movie(char *name="untitled",double rating=0,double revenue=0){
        strcpy(this->name,name);
        this->rating=rating;
        this->revenue=revenue;
    }
    ~Movie()=default;
    void setName(const char *n){
        strcpy(this->name, n);
    }
    void setRating(double r){
        rating=r;
    }
    void setRevenue(double r){
        revenue=r;
    }
    const char *getName(){
        return name;
    }
    double getRating(){
        return rating;
    }
    double getRevenue(){
        return revenue;
    }
    void display(){
        cout<<"Name of film: "<<name<<endl;
        cout<<"Rating: "<<rating<<endl;
        cout<<"Revenue: "<<revenue<<endl;
    }

};
void displayMostPopular(Movie *movies,int n){
    Movie max=movies[0];
    for (int i = 0; i < n; ++i) {
        if(movies[i].getRevenue()>max.getRevenue()){
            max=movies[i];
        }
    }cout<<"Name of film: "<<max.getName()<<endl;
    cout<<"Rating: "<<max.getRating()<<endl;
    cout<<"Revenue: "<<max.getRevenue()<<endl;


}
int main(){
    int n;
    cin>>n;
    Movie movies[10];
    char name[100];
    double rating,revenue;
    for (int i = 0; i < n; ++i) {
        cin>>name>>rating>>revenue;
        movies[i]=Movie(name,rating,revenue);
    }
    displayMostPopular(movies,n);

    return 0;
}