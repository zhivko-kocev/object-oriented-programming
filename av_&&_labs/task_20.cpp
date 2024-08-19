#include <iostream>
#include <cstring>
using namespace std;
class Student{
private:
    char *name;
    int age;
    char *major;
public:
    Student(){
        this->name=new char [10];
        strcpy(this->name,"Unknown");
        this->major=new char [10];
        strcpy(this->major,"Unknown");
        this->age=19;
    }
    Student(char *name,int age, char *major){
        this->name=new char [strlen(name)+1];
        strcpy(this->name,name);
        this->major=new char [strlen(major)+1];
        strcpy(this->major,major);
        this->age=age;
    }

    Student(const Student &s){
        this->name=new char [strlen(s.name)+1];
        strcpy(this->name,s.name);
        this->major=new char [strlen(s.major)+1];
        strcpy(this->major,s.major);
        this->age=s.age;
    }

    Student &operator =(const Student &s){
        if(this!=&s){
            delete [] name;
            delete [] major;
            this->name=new char [strlen(s.name)+1];
            strcpy(this->name,s.name);
            this->major=new char [strlen(s.major)+1];
            strcpy(this->major,s.major);
            this->age=s.age;
        }
        return *this;
    }
    ~Student(){
        delete [] name;
        delete [] major;
    }
    void print(){
        cout<<name<<" "<<age<<" "<<major<<endl;
    }
    char *getName(){
        return name;
    }
    int getAge(){
        return age;
    }
};
class Classroom{
private:
    Student *students{};
    int numStudents;
    int capacity;
public:
    Classroom(){
        this->numStudents=0;
        this->capacity=10;
        this->students= nullptr;
    }
    Classroom(const Classroom &c){
        this->numStudents=c.numStudents;
        this->capacity=c.capacity;
        this->students=new Student [this->capacity];
        for (int i = 0; i < this->numStudents; ++i) {
            this->students[i]=c.students[i];
        }
    }
    Classroom &operator =(const Classroom &c){
        if(this!=&c){
            delete [] students;
            this->numStudents=c.numStudents;
            this->capacity=c.capacity;
            this->students=new Student [this->capacity];
            for (int i = 0; i < this->numStudents; ++i) {
                this->students[i]=c.students[i];
            }
        }
        return *this;
    }
    ~Classroom(){
        delete [] students;
    }
    void printStudents(){

        for (int i = 0; i < numStudents; ++i) {
            students[i].print();
        }
    }
    void add(const Student &s){
        if(!numStudents){
            students=new Student[1];
            students[numStudents++]=s;
        }else {
            if(this->numStudents==capacity){
                Student *tmp;
                tmp=new Student [capacity*2];
                capacity*=2;
                for (int i = 0; i < numStudents; ++i) {
                    tmp[i] = students[i];
                }
                tmp[numStudents++] = s;
                delete[] students;
                students = tmp;
            }else {
                Student *tmp;
                tmp = new Student[capacity];
                for (int i = 0; i < numStudents; ++i) {
                    tmp[i] = students[i];
                }
                tmp[numStudents++] = s;
                delete[] students;
                students = tmp;
            }
        }
    }
    void remove(char *name){
        bool indeks=false;
        for (int i = 0; i < numStudents; ++i) {
            if(!strcmp(students[i].getName(),name)){
                indeks=true;
            }
        }
        if(indeks){
            Student *tmp;
            tmp=new Student [capacity];
            for (int j = 0,b=0; j < numStudents; ++j) {
                if(!strcmp(students[j].getName(),name)) {
                    continue;
                }
                tmp[b++] = students[j];
            }
            delete [] students;
            students=tmp;
            numStudents--;
        }
    }
    friend  double findMedianAge(Classroom &);

};
void swap(Student &first,Student &second){
    Student tmp=first;
    first=second;
    second=tmp;
}
void sort(Student *students,int n){
    for (int i = 0; i < n-1; ++i) {
        for (int j = 0; j < n-1; ++j) {
            if(students[j].getAge()>students[j+1].getAge()){
                swap(students[j],students[j+1]);
            }
        }
    }
}
double findMedianAge(Classroom &c){
    double median;
    sort(c.students,c.numStudents);
    if(c.numStudents % 2==0){
        median=c.students[c.numStudents/2].getAge()+c.students[(c.numStudents/2)-1].getAge();
        median/=2.0;
    }else{
        median=c.students[c.numStudents/2].getAge();
    }
    return median;
}
int main() {
    int numClassrooms, numStudents;
    cin >> numClassrooms;
    Classroom classrooms[100];
    Student students[100];

    // Testing add method
    for (int i = 0; i < numClassrooms; i++) {
        cin >> numStudents;
        for (int j = 0; j < numStudents; j++) {
            char name[100], major[100];
            int age;
            cin >> name >> age >> major;
            Student student(name, age, major);
            classrooms[i].add(student);
            students[i * numStudents + j] = student;
        }
        cout << "Classroom " << i << endl;
        classrooms[i].printStudents();
    }


    // Testing findMedianAge method
    int targetClassroom;
    cin >> targetClassroom;
    double medianAge = findMedianAge(classrooms[targetClassroom]);
    cout << "The median age in classroom " << targetClassroom << " is: " << medianAge << endl;

    // Testing remove method
    cin >> numStudents;
    for (int j = 0; j < numStudents; j++) {
        char name[100];
        cin >> name;
        for (int i = 0; i < numClassrooms; i++) {
            classrooms[i].remove(name);
        }
    }
    for (int i = 0; i < numClassrooms; i++) {
        cout << "Classroom " << i << endl;
        classrooms[i].printStudents();
    }

    return 0;
}