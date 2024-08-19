#include <iostream>
#include <cstring>
using namespace std;
/*
Издавачката куќа FINKI-Education издава онлајн и печатени книги. За секоја книга се чуваат податоци за
ISBN бројот (низа од најмногу 20 знаци), насловот (низа од најмногу 50 знаци), авторот (низа од најмногу 30 знаци)
и основната цена изразена во $ (реален број). Класата за опишување на книгите е апстрактна (5 поени).

За секоја онлајн книга дополнително се чуваат податоци за url од каде може да се симне
(динамички резервирана низа од знаци) и големината изразена во MB (цел број). За секоја печатена книга дополнително
се чуваат податоци за масата изразена во килограми (реален број) и дали ја има на залиха (логичка променлива). (5 поени)

За секој објект од двете изведени класи треба да бидат на располагање следниве методи:

Метод bookPrice, за пресметување на продажната цена на книгата на следниот начин: (10 поени)

За онлајн книга - цената се зголемува за 20% од основната цена ако книгата е поголема од 20MB

За печатена книга - цената се зголемува за 15% од основната цена ако масата на книгата е поголема од 0.7kg

Преоптоварен оператор > за споредба на две книги од каков било вид според нивната цена. (5 поени)

Преоптоварен оператор << за печатење на податоците за книгите во формат: (5 поени)
Да се имплементира функција mostExpensiveBook со потпис:

void mostExpensiveBook (Book** books, int n)

во која се печати вкупниот број на онлајн, односно, печатени книги во проследената низа посебно.
(5 поени) Потоа се наоѓа и печати најскапата книга. (5 поени)

Да се обезбедат сите потребни функции за правилно функционирање на програмата. (5 поени)
*/
class Book
{
protected:
    char ISBN[20]{};
    char title[50]{};
    char author[30]{};
    double price;

public:
    Book()
    {
        strcpy(this->ISBN, "");
        strcpy(this->author, "");
        strcpy(this->title, "");
        this->price = 0;
    }
    Book(char *ISBN, char *title, char *author, double price)
    {
        strcpy(this->ISBN, ISBN);
        strcpy(this->author, author);
        strcpy(this->title, title);
        this->price = price;
    }
    Book(const Book &other)
    {
        strcpy(this->ISBN, other.ISBN);
        strcpy(this->author, other.author);
        strcpy(this->title, other.title);
        this->price = other.price;
    }
    virtual double bookPrice() = 0;
    bool operator>(Book &other)
    {
        if (this->bookPrice() > other.bookPrice())
        {
            return true;
        }
        return false;
    }
    friend ostream &operator<<(ostream &os, Book &book)
    {
        os << book.getISBN() << ": " << book.getTitle() << ", " << book.getAuthor() << " " << book.bookPrice() << endl;
        return os;
    }
    virtual ~Book() = default;
    char *getISBN()
    {
        return ISBN;
    }
    char *getTitle()
    {
        return title;
    }
    char *getAuthor()
    {
        return author;
    }
    virtual bool isOnline() = 0;
};

class OnlineBook : public Book
{
private:
    char url[100];
    int size;
    bool online = true;

public:
    OnlineBook() : Book()
    {
        strcpy(this->url, "");
        this->size = 0;
    }
    OnlineBook(char *ISBN, char *title, char *author, double price, char *url, int size) : Book(ISBN, title, author, price)
    {
        strcpy(this->url, url);
        this->size = size;
    }
    OnlineBook(const OnlineBook &other) : Book(other)
    {
        strcpy(this->url, other.url);
        this->size = other.size;
    }
    double bookPrice() override
    {
        if (size > 20)
        {
            return price * 1.2;
        }
        else
        {
            return price;
        }
    }

    ~OnlineBook() override
    {
    }
    void setISBN(char *isbn)
    {
        strcpy(this->ISBN, isbn);
    }
    bool isOnline() override
    {
        return online;
    }
};

class PrintBook : public Book
{
private:
    double weight;
    bool inStore;
    bool online = false;

public:
    PrintBook() : Book()
    {
        this->weight = 0;
        this->inStore = false;
    }
    PrintBook(char *ISBN, char *title, char *author, double price, double weight, bool inStore) : Book(ISBN, title, author, price)
    {
        this->weight = weight;
        this->inStore = inStore;
    }
    PrintBook(const PrintBook &other) : Book(other)
    {
        this->weight = other.weight;
        this->inStore = other.inStore;
    }
    double bookPrice() override
    {
        if (weight > 0.7)
        {
            return price * 1.15;
        }
        else
        {
            return price;
        }
    }

    bool isOnline() override
    {
        return online;
    }
    ~PrintBook() override = default;
};
void mostExpensiveBook(Book **books, int n)
{
    int online = 0, printed = 0;
    Book *max = books[0];
    for (int i = 0; i < n; ++i)
    {
        if (books[i]->isOnline())
        {
            online++;
        }
        else
        {
            printed++;
        }
        if (*books[i] > *max)
        {
            max = books[i];
        }
    }
    cout << "FINKI-Education" << endl;
    cout << "Total number of online books: " << online << endl;
    cout << "Total number of print books: " << printed << endl;
    cout << "The most expensive book is:" << endl;
    cout << *max;
}
int main()
{

    char isbn[20], title[50], author[30], url[100];
    int size, tip;
    float price, weight;
    bool inStock;
    Book **books;
    int n;

    int testCase;
    cin >> testCase;

    if (testCase == 1)
    {
        cout << "====== Testing OnlineBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++)
        {
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
    if (testCase == 2)
    {
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
    if (testCase == 3)
    {
        cout << "====== Testing PrintBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++)
        {
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
    if (testCase == 4)
    {
        cout << "====== Testing method mostExpensiveBook() ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++)
        {

            cin >> tip >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            if (tip == 1)
            {

                cin >> url;
                cin >> size;

                books[i] = new OnlineBook(isbn, title, author, price, url, size);
            }
            else
            {
                cin >> weight;
                cin >> inStock;

                books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            }
        }

        mostExpensiveBook(books, n);
    }

    for (int i = 0; i < n; i++)
        delete books[i];
    delete[] books;
    return 0;
}
