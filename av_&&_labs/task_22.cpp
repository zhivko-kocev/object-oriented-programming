#include <iostream>
#include <cstring>
using namespace std;
class Vehicle{
private:
    char registration[9];
    char *driverName;
    int location;
    int maxPassengers;
    int distanceDriven;
public:
    Vehicle(){
        this->driverName=new char [10];
        strcpy(this->driverName,"Unknown");
        strcpy(this->registration,"Unknown");
        this->location=0;
        this->maxPassengers=0;
        this->distanceDriven=0;
    }
    Vehicle(char *registration,char *driverName,int location,int maxPassengers){
        this->driverName=new char[strlen(driverName)+1];
        strcpy(this->driverName,driverName);
        strcpy(this->registration,registration);
        this->location=location;
        this->maxPassengers=maxPassengers;
        this->distanceDriven=0;
    }
    Vehicle(const Vehicle &v){
        this->driverName=new char[strlen(v.driverName)+1];
        strcpy(this->driverName,v.driverName);
        strcpy(this->registration,v.registration);
        this->location=v.location;
        this->maxPassengers=v.maxPassengers;
        this->distanceDriven=v.distanceDriven;
    }
    Vehicle &operator =(const Vehicle &v){
        if(this!=&v){
            delete [] driverName;
            this->driverName=new char[strlen(v.driverName)+1];
            strcpy(this->driverName,v.driverName);
            strcpy(this->registration,v.registration);
            this->location=v.location;
            this->maxPassengers=v.maxPassengers;
            this->distanceDriven=v.distanceDriven;
        }
        return *this;
    }
    void print(){
        cout<<driverName<<" "<<registration<<" "<<location<<" "<<maxPassengers<<endl;
    }
    ~Vehicle(){
        delete [] driverName;
    }
};
class RideApp{
private:
    char name[50];
    Vehicle *vehicles;
    int numVehicles;
public:
    RideApp(){
    }

};
int main(){
    Vehicle v("KA2112AD","Stefan",5,6);
    Vehicle v2= Vehicle("KA3412AD","Cvetan",5,8);
    Vehicle v3;
    v3=v;
    v.print();
    v2.print();
    v3.print();
    return 0;
}