#include <iostream>
#include <cstring>
using namespace std;
class Book{
private:
    char *name;
    int *isbn;
    int pages;
public:
    Book(){
        this->name=new char[10];
        strcpy(this->name,"Unknown");
        this->isbn=new int[5];
        this->pages=100;
    }
    Book(char *name,int *isbn,int pages){
        this->name=new char[strlen(name)];
        strcpy(this->name,name);
        this->isbn=new int[5];
        for (int i = 0; i < 5; ++i) {
            this->isbn[i]=isbn[i];
        }
        this->pages=pages;
    }
    Book(const Book &b){
        this->name=new char[strlen(b.name)];
        strcpy(this->name,b.name);
        this->isbn=new int[5];
        for (int i = 0; i < 5; ++i) {
            this->isbn[i]=b.isbn[i];
        }
        this->pages=b.pages;
    }
    Book &operator =(const Book &b){
        if(this!=&b){
            delete [] name;
            delete [] isbn;
            this->name=new char[strlen(b.name)];
            strcpy(this->name,b.name);
            this->isbn=new int[5];
            for (int i = 0; i < 5; ++i) {
                this->isbn[i]=b.isbn[i];
            }
            this->pages=b.pages;
        }
        return *this;
    }
    bool operator ==(const Book &b){
        for (int i = 0; i < 5; ++i) {
            if(isbn[i]!=b.isbn[i]){
                return false;
            }
        }
        return true;
    }
    friend ostream &operator <<(ostream &os,const Book &b){
        os<<"Title: "<<b.name<<" ISBN: [ ";
        for (int i = 0; i < 5; ++i) {
            os<<b.isbn[i]<<" ";
        }
        os<<"]"<<endl;
        return os;
    }
    int getPages(){
        return pages;
    }


};
class BorrowABook{
private:
    char name[100];
    Book *books;
    int numBooks;
public:
    BorrowABook(char *name=""){
        strcpy(this->name,name);
        this->books= nullptr;
        this->numBooks=0;
    }
    BorrowABook(const BorrowABook &b){
        strcpy(this->name,b.name);
        this->numBooks=b.numBooks;
        this->books= new Book[b.numBooks];
        for (int i = 0; i < b.numBooks; ++i) {
            this->books[i]=b.books[i];
        }
    }
    BorrowABook &operator = (const BorrowABook &b){
        if(this!=&b){
            delete [] books;
            strcpy(this->name,b.name);
            this->numBooks=b.numBooks;
            this->books= new Book[b.numBooks];
            for (int i = 0; i < b.numBooks; ++i) {
                this->books[i]=b.books[i];
            }
        }
        return *this;
    }
    BorrowABook &operator +=(const Book &b){
        if(!numBooks){
            books=new Book[1];
            books[numBooks++]=b;
        }else{
            Book *tmp=new Book[numBooks+1];
            for (int i = 0; i < numBooks; ++i) {
                tmp[i]=books[i];
            }
            tmp[numBooks++]=b;
            delete [] books;
            books=tmp;
        }
        return *this;
    }
    BorrowABook &operator -=(const Book &b){
        int index=-1;
        for (int i = 0; i < numBooks; ++i) {
            if(books[i]==b){
                index=i;
                break;
            }
        }
        if(index!=-1){
            Book *tmp=new Book[numBooks-1];
            for (int i = 0,k=0; i < numBooks; ++i) {
                if(i!=index){
                    tmp[k++]=books[i];
                }
            }
            numBooks--;
            delete [] books;
            books=tmp;
        }
        return *this;
    }
    void printNumberOfPages(int max){
        for (int i = 0; i < numBooks; ++i) {
            if(books[i].getPages()>max){
                cout<<books[i];
            }
        }
    }
    void print(){
        for (int i = 0; i < numBooks; ++i) {
            cout<<books[i];
        }
    }
};
int main(){
    BorrowABook store("Literatura");
    for (int i = 0; i < 4; ++i) {
        char name[50];
        int isbn[5],pages;
        cin>>name;
        for (int j = 0; j < 5; ++j) {
            cin>>isbn[j];
        }
        cin>>pages;
        Book b = Book(name,isbn,pages);
        store+=b;
    }
    int isbn[5]={1,2,1,1,1};
    Book b1("Rebbeca",isbn,100);
    store-=b1;
    store.print();
    cout<<"------------------------------------"<<endl;
    store.printNumberOfPages(150);
    return 0;
}