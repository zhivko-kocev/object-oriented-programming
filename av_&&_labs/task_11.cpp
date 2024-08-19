#include <iostream>
#include <fstream>
using namespace std;
// Class to define the properties
class Employee {
public:
    string Name;
    int Employee_ID;
    int Salary;
};
int main(){
    Employee Emp_1;
    Emp_1.Name="John";
    Emp_1.Employee_ID=2121;
    Emp_1.Salary=11000;
    //Wriring this data to Employee.txt
    ofstream file1;
    file1.open("D:\\Codes\\CLionProjects\\KocewOOP\\new.txt", ios::app);
    file1.write((char*)&Emp_1,sizeof(Emp_1));
    file1.close();
    //Reading data from EMployee.txt
    ifstream file2;
    file2.open("D:\\Codes\\CLionProjects\\KocewOOP\\new.txt",ios::in);
    file2.seekg(0);
    file2.read((char*)&Emp_1,sizeof(Emp_1));
    printf("\nName :%s",Emp_1.Name.c_str());
    printf("\nEmployee ID :%d",Emp_1.Employee_ID);
    printf("\nSalary :%d",Emp_1.Salary);
    file2.close();
    return 0;
}