#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;
/*
Да се креира класа која претставува слика (Image) во рамките на еден компјутер. За секоја датотека се чуваат (5 поени):

име на сликата (дин. алоцирана низа од знаци). Предефинирано поставено на untitled.
име на корисникот кој е сопственик на датотеката (низа од макс. 50 знаци). Предефинирано поставено на unknown.
димензии на сликата (2 цели броеви кои претставуваат ширина и висина во пиксели). Предефинирано поставени на 800.
Од класата Imageда се изведе класата TransparentImage, која претставува слика која содржи поддржува транспарентност. За транспарентна слика дополнително се чува :

дали поддржува нивоа на транспарентност (bool променлива, предефинирано не поддржува транспарентност).
За класите Image и TransparentImage да биде достапна метода (fileSize)за пресметка на големината на сликата (во бајти). Големината се пресметува на сл. начин (5 поени):

за објектите од класата Image, големината на датотеката е еднаква на:висината * ширината * 3.
за TransparentImage, доколку поддржува нивоа на транспарентност, големината на датотеката е еднаква на ширина * висина * 4. Доколку не поддржува транспарентност,
големината на сликата се пресметува како ширина * висина + бр._на_пиксели_присутни_во_сликата / 8.
За класите Image и TransparentImage да се преоптоварат следниве оператори (5 поени):

оператор << кој ги печати податоците од датотеката во сл. формат:

ime_fajl avtor golemina_na_fajlot_vo_bajti

оператор > кој ги споредува сликите според нивната големина.

Да се дефинира класа Folder, што репрезентира директориум во кој може да се поставуваат слики. За секој фолдер се чува (5 поени):

име на фолдерот (низа од макс 255 знаци)
име на корисникот кој е сопственик на фолдерот (низа од макс. 50 знаци). Предефинирано поставено на unknown.
низа од покажувачи кон Image објекти (макс. 100 во рамките на еден фолдер).
Да се имплементираат следниве методи (5 поени):

метода за пресметка на големината на фолдерот (folderSize). Големината на фолдерот е сума од големините од сите слики во рамките на фолдерот.

метода за пронаоѓање на наголемата слика во рамките на фолдерот (getMaxFile). Методата враќа покажувач кон најголемата слика во фолдерот (сметано во бајти).

За класата Folder да се имплементира и оператор += кој додава објекти од типот Image/TransparentImage во рамките на фолдерот (5 поени).

Да се креираат следниве функционалности за класите (5 поени):

operator << - со кој се печатат податоците за фолдерот во формат (5 поени):

ime_folder sopstvenik --

imeslika avtor goleminanafajlotvo_bajti
imeslika avtor goleminanafajlotvobajti -- goleminanafoldervo_bajti
operator [] - кој враќа покажувач кон соодветната слика во фолдерот.
Доколку не постои слика на тој индекс, треба да се врати NULL (5 поени).

Да се креира и глобална функција max_folder_size која го прима низа од објекти од типот
Folder и го враќа фолдерот кој има зафаќа најмногу простор (во бајти). (5 поени)

Да се овозможи правилно функционирање на класите (потребни set или get
методи/оператори/конструктори/деструктори) според изворниот код кој е веќе зададен.
Сите податочни членови на класите се protected. (5 поени)
*/
class Image
{
protected:
    char *imeslika;
    char ime[50];
    int sirina;
    int visina;

public:
    Image(const char *imeslika = "untitled", const char *ime = "unknown", int sirina = 800, int visina = 800)
    {
        this->imeslika = new char[strlen(imeslika) + 1];
        strcpy(this->imeslika, imeslika);
        strcpy(this->ime, ime);
        this->sirina = sirina;
        this->visina = visina;
    }
    Image(const Image &i)
    {
        this->imeslika = new char[strlen(i.imeslika) + 1];
        strcpy(this->imeslika, i.imeslika);
        strcpy(this->ime, i.ime);
        this->sirina = i.sirina;
        this->visina = i.visina;
    }
    Image &operator=(const Image &i)
    {
        if (this != &i)
        {
            delete[] imeslika;
            this->imeslika = new char[strlen(i.imeslika) + 1];
            strcpy(this->imeslika, i.imeslika);
            strcpy(this->ime, i.ime);
            this->sirina = i.sirina;
            this->visina = i.visina;
        }
        return *this;
    }
    bool operator>(Image &i)
    {
        return fileSize() > i.fileSize();
    }
    virtual int fileSize()
    {
        return visina * sirina * 3;
    }
    virtual ~Image() { delete[] imeslika; }

    friend ostream &operator<<(ostream &out, Image &img)
    {
        out << img.imeslika << " " << img.ime << " " << img.fileSize() << endl;
        return out;
    }
    virtual void print()
    {
        cout << imeslika << " " << ime << " " << fileSize() << endl;
    }
};
class TransparentImage : public Image
{
protected:
    bool transparentnost;

public:
    TransparentImage(const char *imeslika = "untitled", const char *ime = "unknown", int sirina = 800, int visina = 800, bool transparentnost = true) : Image(imeslika, ime, sirina, visina)
    {
        this->transparentnost = transparentnost;
    }
    TransparentImage(const TransparentImage &i) : Image(i)
    {
        this->transparentnost = i.transparentnost;
    }
    TransparentImage &operator=(const TransparentImage &i)
    {
        if (this != &i)
        {
            delete[] imeslika;
            this->imeslika = new char[strlen(i.imeslika) + 1];
            strcpy(this->imeslika, i.imeslika);
            strcpy(this->ime, i.ime);
            this->sirina = i.sirina;
            this->visina = i.visina;
            this->transparentnost = i.transparentnost;
        }
        return *this;
    }

    int fileSize()
    {
        if (transparentnost)
        {
            return sirina * visina * 4;
        }
        else
        {
            return sirina * visina + (sirina * visina) / 8;
        }
    }
    friend ostream &operator<<(ostream &out, TransparentImage &img)
    {
        out << img.imeslika << " " << img.ime << " " << img.fileSize() << endl;
        return out;
    }
    bool operator>(TransparentImage &i)
    {
        return fileSize() > i.fileSize();
    }
    void print()
    {
        cout << imeslika << " " << ime << " " << fileSize() << endl;
    }
    ~TransparentImage() {}
};

class Folder
{

protected:
    char ime[257];
    char imekorisnik[50];
    Image *niza[100];
    int n;

public:
    Folder(const char *ime = "", const char *imekorisnik = "unknown")
    {
        strcpy(this->ime, ime);
        strcpy(this->imekorisnik, imekorisnik);
        this->n = 0;
    }
    Folder(const Folder &f)
    {
        strcpy(this->ime, f.ime);
        strcpy(this->imekorisnik, f.imekorisnik);
        this->n = f.n;
        for (int i = 0; i < n; i++)
        {
            this->niza[i] = f.niza[i];
        }
    }

    Folder &operator+=(Image &i)
    {
        this->niza[n++] = &i;
        return *this;
    }

    Folder &operator+=(TransparentImage &i)
    {
        this->niza[n++] = &i;
        return *this;
    }

    int folderSize()
    {
        int golemina = 0;
        for (int i = 0; i < n; i++)
        {
            golemina += niza[i]->fileSize();
        }
        return golemina;
    }
    Image *getMaxFile() const
    {
        Image *max = niza[0];
        for (int i = 0; i < n; i++)
        {
            if (*niza[i] > *max)
            {
                *max = *niza[i];
            }
        }
        return max;
    }
    Image *operator[](int index)
    {
        if (index < 0 || index >= n)
            return 0;
        Image *max = niza[index];
        return max;
    }

    friend ostream &operator<<(ostream &o, Folder &f)
    {
        o << f.ime << " " << f.imekorisnik << endl;
        o << "--" << endl;
        for (int i = 0; i < f.n; i++)
        {
            f.niza[i]->print();
        }
        o << "--" << endl;
        o << "Folder size: " << f.folderSize() << endl;
        return o;
    }
};
Folder &max_folder_size(Folder *niza, int n)
{
    int index;
    int max = niza[0].folderSize();
    for (int i = 0; i < n; i++)
    {
        if (niza[i].folderSize() >= max)
        {
            max = niza[i].folderSize();
            index = i;
        }
    }
    return niza[index];
}

int main()
{

    int tc; // Test Case

    char name[255];
    char user_name[51];
    int w, h;
    bool tl;

    cin >> tc;

    if (tc == 1)
    {
        // Testing constructor(s) & operator << for class File

        cin >> name;
        cin >> user_name;
        cin >> w;
        cin >> h;

        Image f1;

        cout << f1;

        Image f2(name);
        cout << f2;

        Image f3(name, user_name);
        cout << f3;

        Image f4(name, user_name, w, h);
        cout << f4;
    }
    else if (tc == 2)
    {
        // Testing constructor(s) & operator << for class TextFile
        cin >> name;
        cin >> user_name;
        cin >> w >> h;
        cin >> tl;

        TransparentImage tf1;
        cout << tf1;

        TransparentImage tf4(name, user_name, w, h, tl);
        cout << tf4;
    }
    else if (tc == 3)
    {
        // Testing constructor(s) & operator << for class Folder
        cin >> name;
        cin >> user_name;

        Folder f3(name, user_name);
        cout << f3;
    }
    else if (tc == 4)
    {
        // Adding files to folder
        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image *f;
        TransparentImage *tf;

        int sub, fileType;

        while (1)
        {
            cin >> sub; // Should we add subfiles to this folder
            if (!sub)
                break;

            cin >> fileType;
            if (fileType == 1)
            { // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name, user_name, w, h);
                dir += *f;
            }
            else if (fileType == 2)
            {
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name, user_name, w, h, tl);
                dir += *tf;
            }
        }
        cout << dir;
    }
    else if (tc == 5)
    {
        // Testing getMaxFile for folder

        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image *f;
        TransparentImage *tf;

        int sub, fileType;

        while (1)
        {
            cin >> sub; // Should we add subfiles to this folder
            if (!sub)
                break;

            cin >> fileType;
            if (fileType == 1)
            { // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name, user_name, w, h);
                dir += *f;
            }
            else if (fileType == 2)
            {
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name, user_name, w, h, tl);
                dir += *tf;
            }
        }
        cout << *(dir.getMaxFile());
    }
    else if (tc == 6)
    {
        // Testing operator [] for folder

        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image *f;
        TransparentImage *tf;

        int sub, fileType;

        while (1)
        {
            cin >> sub; // Should we add subfiles to this folder
            if (!sub)
                break;

            cin >> fileType;
            if (fileType == 1)
            { // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name, user_name, w, h);
                dir += *f;
            }
            else if (fileType == 2)
            {
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name, user_name, w, h, tl);
                dir += *tf;
            }
        }

        cin >> sub; // Reading index of specific file
        cout << *dir[sub];
    }
    else if (tc == 7)
    {
        // Testing function max_folder_size
        int folders_num;

        Folder dir_list[10];

        Folder dir;
        cin >> folders_num;

        for (int i = 0; i < folders_num; ++i)
        {
            cin >> name;
            cin >> user_name;
            dir = Folder(name, user_name);

            Image *f;
            TransparentImage *tf;

            int sub, fileType;

            while (1)
            {
                cin >> sub; // Should we add subfiles to this folder
                if (!sub)
                    break;

                cin >> fileType;
                if (fileType == 1)
                { // Reading File
                    cin >> name;
                    cin >> user_name;
                    cin >> w >> h;
                    f = new Image(name, user_name, w, h);
                    dir += *f;
                }
                else if (fileType == 2)
                {
                    cin >> name;
                    cin >> user_name;
                    cin >> w >> h;
                    cin >> tl;
                    tf = new TransparentImage(name, user_name, w, h, tl);
                    dir += *tf;
                }
            }
            dir_list[i] = dir;
        }

        cout << max_folder_size(dir_list, folders_num);
    }
    return 0;
}