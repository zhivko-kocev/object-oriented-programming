#include <iostream>
#include <cstring>
using namespace std;
class DisciplinaryAction{
private:
    char *name{};
    int index{};
    char *reason{};
    int numSessions{};
public:
    DisciplinaryAction(char *name= "",int index=0,char *reason= "",int numSessions=0){
        this->name=new char[strlen(name)];
        strcpy(this->name,name);
        this->index=index;
        this->reason=new char[strlen(reason)];
        strcpy(this->reason,reason);
        this->numSessions=numSessions;
    }
    DisciplinaryAction(const DisciplinaryAction &d){
        this->name=new char[strlen(d.name)];
        strcpy(this->name,d.name);
        this->index=d.index;
        this->reason=new char[strlen(d.reason)];
        strcpy(this->reason,d.reason);
        this->numSessions=d.numSessions;
    }
    DisciplinaryAction &operator=(const DisciplinaryAction &d){
        if(this!=&d){
            delete [] name;
            delete [] reason;
            this->name=new char[strlen(d.name)];
            strcpy(this->name,d.name);
            this->index=d.index;
            this->reason=new char[strlen(d.reason)];
            strcpy(this->reason,d.reason);
            this->numSessions=d.numSessions;
        }
        return *this;
    }
    ~DisciplinaryAction(){
        delete [] name;
        delete [] reason;
    }

    int getIndex()  {
        return index;
    }

    void setIndex(int _index) {
        index = _index;
    }

    friend ostream &operator<<(ostream &os, const DisciplinaryAction &action) {
        os<<"Student: "<<action.name<<endl;
        os<<"Student's index: "<<action.index<<endl;
        os<<"Reason: "<<action.reason<<endl;
        os<<"Sessions: "<<action.numSessions<<endl;
        return os;
    }
    bool operator >=(const DisciplinaryAction &d) const{
        return  (numSessions >= d.numSessions);
    }
    DisciplinaryAction &operator ++(){
        numSessions++;
        return *this;
    }
};
int main(){
    DisciplinaryAction d1;
    DisciplinaryAction d2("Zhivko",223117,"Kavga",3);
    d1=d2;
    cout<<d1<<endl;
    cout<<d2<<endl;
    ++d1;
    ++d1;
    cout<<d1<<endl;
    cout<<(d1>=d2)<<endl;
    cout<<(d2>=d1)<<endl;

}