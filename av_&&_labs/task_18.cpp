#include <iostream>
#include <cstring>
using namespace std;
class Book{
protected:
    char ISBN[20]{};
    char title[50]{};
    char author[30]{};
    double price;
public:
    Book(){
        strcpy(this->ISBN,"Unknown");
        strcpy(this->author,"Unknown");
        strcpy(this->title,"Unknown");
        this->price=0;
    }
    Book(char *ISBN,char *title,char *author,float price){
        strcpy(this->ISBN,ISBN);
        strcpy(this->author,author);
        strcpy(this->title,title);
        this->price=price;
    }
   virtual double bookPrice ()=0;

    bool operator >(const Book &other) const{
        if(this->price>other.price){
            return true;
        }
        return false;
    }
    friend ostream &operator << (ostream &os,Book &other){
        os<<other.ISBN<<": "<<other.title<<", "<<other.author<<" "<<other.bookPrice()<<endl;
        return os;
    }

    virtual ~Book()= default;

    virtual bool getOnline()=0;


};
class OnlineBook:public Book{
private:
    char *url;
    int size;
    bool isOnline=true;
public:
    OnlineBook(char *ISBN,char *title,char *author,float price,char *url,int size):Book(ISBN,title,author,price){
        this->url=new char [strlen(url)+1];
        strcpy(this->url,url);
        this->size=size;
    }
    OnlineBook(const OnlineBook &o):Book(o){
        this->url=new char [strlen(o.url)+1];
        strcpy(this->url,o.url);
        this->size=o.size;
    }
    OnlineBook &operator =(const OnlineBook &o){
        if(this!=&o){
            Book::operator=(o);
            delete [] url;
            this->url=new char[strlen(o.url)+1];
            strcpy(this->url,o.url);
            this->size=o.size;
        }
        return *this;
    }
    double bookPrice() override{
        if(size>20) {
            return price+(price*0.2);
        }
        return price;
    }
    void setISBN(char *isbn){
        strcpy(this->ISBN,isbn);
    }
    ~OnlineBook() override{
        delete [] url;
    }
    bool getOnline()override{
        return isOnline;
    }
};
class PrintBook:public Book{
private:
    double weight{};
    bool inStore{};
    bool isOnline=false;
public:
    PrintBook(char *ISBN,char *title,char *author,float price,double weight,bool inStore):Book(ISBN,title,author,price){
        this->weight=weight;
        this->inStore=inStore;
    }
    double bookPrice()override{
        if(this->weight>0.7){
            return price+(price*0.15);
        }
        return price;
    }

    bool getOnline()override{
        return isOnline;
    }
    ~PrintBook() override =default;


};
void mostExpensiveBook(Book **books,int n){
    Book *max;
    max=books[0];
    int online=0,printed=0;
    for (int i = 0; i < n; ++i) {
     if(books[i]->getOnline()){
         online++;
     }else{
         printed++;
     }
     if(*books[i]>*max){
         max=books[i];
     }
    }
    cout<<"FINKI-Education"<<endl;
    cout<<"Total number of online books: "<<online<<endl;
    cout<<"Total number of print books: "<<printed<<endl;
    cout<<"The most expensive book is:"<<endl;
    cout<<*max;

}
int main(){

    char isbn[20], title[50], author[30], url[100];
    int size, tip;
    float price, weight;
    bool inStock;
    Book  **books;
    int n;

    int testCase;
    cin >> testCase;

    if (testCase == 1){
        cout << "====== Testing OnlineBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++){
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> url;
            cin >> size;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new OnlineBook(isbn, title, author, price, url, size);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 2){
        cout << "====== Testing OnlineBook CONSTRUCTORS ======" << endl;
        cin >> isbn;
        cin.get();
        cin.getline(title, 50);
        cin.getline(author, 30);
        cin >> price;
        cin >> url;
        cin >> size;
        cout << "CONSTRUCTOR" << endl;
        OnlineBook ob1(isbn, title, author, price, url, size);
        cout << ob1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        OnlineBook ob2(ob1);
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
        cout << "OPERATOR =" << endl;
        ob1 = ob2;
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
    }
    if (testCase == 3){
        cout << "====== Testing PrintBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++){
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> weight;
            cin >> inStock;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 4){
        cout << "====== Testing method mostExpensiveBook() ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i<n; i++){

            cin >> tip >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            if (tip == 1) {

                cin >> url;
                cin >> size;

                books[i] = new OnlineBook(isbn, title, author, price, url, size);

            }
            else {
                cin >> weight;
                cin >> inStock;

                books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            }
        }

        mostExpensiveBook(books, n);
    }

    for (int i = 0; i<n; i++) delete books[i];
    delete[] books;
    return 0;
}
