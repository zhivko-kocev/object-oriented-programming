#include<iostream>
#include<cstring>
#include <cmath>

using namespace std;

class Employee {
private:
    char name[100]{};
    char surname[100]{};
    int salary;
public:

    Employee(){
        strcpy(this->name,"Unknown");
        strcpy(this->surname,"Unknown");
        this->salary=10000;
    }

    Employee(char *name, char *surname , int salary) {
        strcpy(this->name, name);
        strcpy(this->surname, surname);
        this->salary = salary;
    }

    Employee(const Employee &other) {
        strcpy(this->name, other.name);
        strcpy(this->surname, other.surname);
        this->salary = other.salary;
    }

    ~Employee()=default;

    void printEmployee(){
        cout<<"Employee name: "<<name<<endl;
        cout<<"Employee surname: "<<surname<<endl;
        cout<<"Employee salary: "<<salary<<endl;
    }
    int getSalary() const{return salary;}
};
class TechCompany{
private:
    char name[100]{};
    Employee employees[20];
    int numOfEmployees;
public:
    TechCompany(){
        strcpy(this->name,"Unknown");
        numOfEmployees=0;
    }
    TechCompany(char *name){
        strcpy(this->name,name);
        numOfEmployees=0;
    }
    TechCompany(const TechCompany &other){
        strcpy(this->name,other.name);
        this->numOfEmployees=other.numOfEmployees;
        for (int i = 0; i < numOfEmployees; ++i) {
            this->employees[i]=other.employees[i];
        }
    }
    void addEmployee(const Employee &other){
        employees[numOfEmployees++]=other;
    }
    ~TechCompany()=default;

    char *getName() {
        return name;
    }
    int getNumEmployees() const{
        return numOfEmployees;
    }
    Employee getEmployee(int index){
        return employees[index];
    }
    void setName(char *_name){
        strcpy(this->name,_name);
    }
    double average(){
        double sum=0;
        for (int i = 0; i < numOfEmployees; ++i) {
            sum+= employees[i].getSalary();
        }
        return sum/(double)numOfEmployees;
    }
    double stdSalary(){
        double sum=0;
        for (int i = 0; i < numOfEmployees; ++i) {
            sum+=pow(employees[i].getSalary()-average(),2);
        }
        double var=sum/(numOfEmployees-1);
        return sqrt(var);
    }

};
TechCompany printCompanyWithHighestAverageSalary(TechCompany *companies,int n){
    TechCompany max=companies[0];
    for (int i = 0; i < n; ++i) {
        if(companies[i].average()>max.average()){
            max=companies[i];
        }
    }
    return max;
}
TechCompany printCompanyWithHighestStdSalary(TechCompany *companies,int n){
    TechCompany max=companies[0];
    for (int i = 0; i < n; ++i) {
        if(companies[i].stdSalary()>max.stdSalary()){
            max=companies[i];
        }
    }
    return max;
}
bool isSameCompany(TechCompany &cmp1, TechCompany & cmp2){
    return (strcmp(cmp1.getName(),cmp2.getName())==0);
}
//DO NOT CHANGE main()

int main() {
    const int MAX_COMPANIES = 10;

    TechCompany companies[MAX_COMPANIES];

    int n;
    std::cin >> n;

    for (int i = 0; i < n; i++) {
        char _name[100];
        std::cin >> _name;

        TechCompany company(_name);

        int m;
        std::cin >> m;

        for (int j = 0; j < m; j++) {
            char name[100];
            char surname[100];
            int salary;

            std::cin >> name;

            std::cin >> surname;

            std::cin >> salary;

            Employee employee(name, surname, salary);

            company.addEmployee(employee);
        }

        companies[i] = company;
    }

    TechCompany copy = companies[0];

    std::cout<<"-->Testing get and set methods for one object and copy constructor"<<std::endl;
    char na[100];
    strcpy(na,"copy");
    copy.setName(na);
    std::cout << copy.getName() << std::endl;


    std::cout<<"-->Testing addEmployee function"<<std::endl;
    char nam[100],sur[100];
    strcpy(nam,"John");
    strcpy(sur,"Doe");
    Employee newEmployee(nam, sur, 5000);
    copy.addEmployee(newEmployee);
    std::cout << "Number of employees in copy: " << copy.getNumEmployees() << std::endl;


    std::cout<<"-->Testing copy of first employee"<<std::endl;
    Employee firstEmployee = copy.getEmployee(0);
    firstEmployee.printEmployee();


    std::cout<<"-->Testing methods"<<std::endl;
    TechCompany t = printCompanyWithHighestAverageSalary(companies, n);
    TechCompany t1 = printCompanyWithHighestStdSalary(companies, n);

    std::cout << "Tech company with the highest average salary: " << t.getName() << std::endl;
    std::cout << "Tech company with the highest standard deviation for salaries: " <<t1.getName() << std::endl;

    if (isSameCompany(t, t1)){
        std::cout<<"The tech company: "<<t.getName()<<" has the highest standard deviation and highest average salary"<<std::endl;
    }
    return 0;
}
