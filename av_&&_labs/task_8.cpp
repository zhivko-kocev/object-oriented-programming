#include <iostream>
#include <cstring>

using namespace std;

class Employee {
private:
    char name[20];
    int salary;
    char job[20];
public:
    Employee(){}
    Employee(char *_name, int _salary, char *_job) {
        strcpy(name, _name);
        strcpy(job, _job);
        salary = _salary;
    }

};

int main() {
    char name[20],job[20];
    int salary;
    Employee employees[100];
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> name >> salary >> job;
        employees[i] = Employee(name,salary,job);
    }

    return 0;
}