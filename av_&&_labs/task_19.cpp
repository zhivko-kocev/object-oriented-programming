#include <iostream>
#include <cstring>
using namespace std;
class DisciplinaryAction{
private:
    char *name;
    int index;
    char *cause;
public:
    DisciplinaryAction(){
        this->name=new char [10];
        strcpy(this->name,"Unknown");
        this->cause=new char [10];
        strcpy(this->cause,"Unknown");
        this->index=0;
    }
    DisciplinaryAction(char *name,int index,char *cause){
        this->name=new char [strlen(name)+1];
        strcpy(this->name,name);
        this->cause=new char [strlen(cause)+1];
        strcpy(this->cause,cause);
        this->index=index;
    }

    DisciplinaryAction(const DisciplinaryAction &d){
        this->name=new char [strlen(d.name)+1];
        strcpy(this->name,d.name);
        this->cause=new char [strlen(d.cause)+1];
        strcpy(this->cause,d.cause);
        this->index=d.index;
    }

    DisciplinaryAction &operator =(const DisciplinaryAction &d){

        if(this!=&d){
            delete [] name;
            delete [] cause;
            this->name=new char [strlen(d.name)+1];
            strcpy(this->name,d.name);
            this->cause=new char [strlen(d.cause)+1];
            strcpy(this->cause,d.cause);
            this->index=d.index;
        }
        return *this;
    }

    ~DisciplinaryAction(){
        delete [] name;
        delete [] cause;
    }

    void setIndex(int _index){
        this->index=_index;
    }

    int getIndex(){
        return this->index;
    }
    void print(){
        cout<<"Student: "<<name<<endl;
        cout<<"Student's index: "<<index<<endl;
        cout<<"Reason: "<<cause<<endl;
    }
};
int main() {
    int n;
    cin >> n;

    /// Testing Default constructor and equal operator
    /// Array input

    DisciplinaryAction arr[n];

    for (int i = 0; i < n; i++) {
        char name[100];
        char reason[100];
        int index;

        cin >> name >> index >> reason;

        arr[i] = DisciplinaryAction(name, index, reason);
    }

    cout << "-- Testing operator = & print() --\n";
    arr[0].print();

    /// Testing copy constructor & set index

    DisciplinaryAction merka(arr[0]);
    merka.setIndex(112233);

    cout << "\n-- Testing copy constructor & set index --\n";
    cout << "-------------\n";
    cout << "Source:\n";
    cout << "-------------\n";
    arr[0].print();

    cout << "\n-------------\n";
    cout << "Copied and edited:\n";
    cout << "-------------\n";
    merka.print();

    /// Testing if array is OK

    cout << "\n-- Testing if array was inputted correctly --\n";

    for (int i = 0; i < n; i++)
        arr[i].print();

    return 0;
}