#include <iostream>
#include <cstring>
using namespace std;
/*
Потребно е да се имплементираат класи File (датотека) и Folder (директориум) за работа со едноставен податочен систем.

Во класата File треба да се чуваат следниве податоци:

Име на датотеката (динамички алоцирана низа од знаци)
Екстензија на датотеката (енумерација со можни вредности: txt, pdf, exe)
Име на сопственикот на датотеката (динамички алоцирана низа од знаци)
Големина на датотеката (цел број на мегабајти)
Дополнително, во класата потребно е да се напишат и:

Конструктор без параметри
Конструктор со параметри
Конструктор за копирање
Деструктор
Преоптоварување на операторот =
Метод за печатење на информациите за една датотека (видете го излезот од тест примерите за структурата на печатење) - print()
Метод за проверка на еднаквост помеѓу две датотеки со потпис bool equals(const File & that) кој ќе враќа true ако датотеките имаат исто име, екстензија и сопственик
Метод за споредба на типот помеѓу две датотеки со потпис bool equalsType(const File & that) кој ќе враќа true ако датотеките се од ист тип, т.е. имаат исто име и екстензија
Во класата Folder треба да се чуваат следниве податоци:

Име на директориумот (динамички алоцирана низа од знаци)
Број на датотеки во него (на почеток директориумот е празен)
Динамички алоцирана низа од датотеки, објекти од класата File
Дополнително, во класата потребно е да се напишат и:

Конструктор со потпис Folder(const char* name)
Деструктор
Метод за печатење на информациите за еден директориум (видете го излезот од тест примерите за структурата на печатење) - print()
Метод за бришење на датотека од директориумот со потпис void remove(const File & file) кој ќе ја избрише првата датотека од директориумот која е еднаква според equals методот
Метод за додавање на датотека во директориумот со потпис void add(const File & file) кој ќе додава датотеката во директориумотПотребно е да се имплементираат класи File (датотека) и Folder (директориум) за работа со едноставен податочен систем.

Во класата File треба да се чуваат следниве податоци:

Име на датотеката (динамички алоцирана низа од знаци)
Екстензија на датотеката (енумерација со можни вредности: txt, pdf, exe)
Име на сопственикот на датотеката (динамички алоцирана низа од знаци)
Големина на датотеката (цел број на мегабајти)
Дополнително, во класата потребно е да се напишат и:

Конструктор без параметри
Конструктор со параметри
Конструктор за копирање
Деструктор
Преоптоварување на операторот =
Метод за печатење на информациите за една датотека (видете го излезот од тест примерите за структурата на печатење) - print()
Метод за проверка на еднаквост помеѓу две датотеки со потпис bool equals(const File & that) кој ќе враќа true ако датотеките имаат исто име, екстензија и сопственик
Метод за споредба на типот помеѓу две датотеки со потпис bool equalsType(const File & that) кој ќе враќа true ако датотеките се од ист тип, т.е. имаат исто име и екстензија
Во класата Folder треба да се чуваат следниве податоци:

Име на директориумот (динамички алоцирана низа од знаци)
Број на датотеки во него (на почеток директориумот е празен)
Динамички алоцирана низа од датотеки, објекти од класата File
Дополнително, во класата потребно е да се напишат и:

Конструктор со потпис Folder(const char* name)
Деструктор
Метод за печатење на информациите за еден директориум (видете го излезот од тест примерите за структурата на печатење) - print()
Метод за бришење на датотека од директориумот со потпис void remove(const File & file) кој ќе ја избрише првата датотека од директориумот која е еднаква според equals методот
Метод за додавање на датотека во директориумот со потпис void add(const File & file) кој ќе додава датотеката во директориумот
*/
enum EXTENSION
{
    PDF,
    TXT,
    EXE
};
class File
{
private:
    char *fileName;
    EXTENSION extension;
    char *user;
    int size;

public:
    File(char *fileName = "untitled", char *user = "user", int size = 1, EXTENSION extension = TXT)
    {
        this->fileName = new char[strlen(fileName) + 1];
        strcpy(this->fileName, fileName);
        this->user = new char[strlen(user) + 1];
        strcpy(this->user, user);
        this->size = size;
        this->extension = extension;
    }

    File(File const &f)
    {
        this->fileName = new char[strlen(f.fileName) + 1];
        strcpy(this->fileName, f.fileName);
        this->user = new char[strlen(f.user) + 1];
        strcpy(this->user, f.user);
        this->size = f.size;
        this->extension = f.extension;
    }

    File &operator=(File const &f)
    {
        if (this != &f)
        {

            delete[] fileName;
            this->fileName = new char[strlen(f.fileName) + 1];
            strcpy(this->fileName, f.fileName);
            delete[] user;
            this->user = new char[strlen(f.user) + 1];
            strcpy(this->user, f.user);
            this->size = f.size;
            this->extension = f.extension;
        }
        return *this;
    }

    ~File()
    {
        delete[] fileName;
        delete[] user;
    }

    void print()
    {
        cout << "File name: " << fileName << ".";
        switch (extension)
        {
        case TXT:
            cout << "txt" << endl;
            break;
        case PDF:
            cout << "pdf" << endl;
            break;
        case EXE:
            cout << "exe" << endl;
            break;
        }
        cout << "File owner: " << user << endl;
        cout << "File size: " << size << endl;
    }

    bool equals(File const &other)
    {
        if ((!strcmp(this->fileName, other.fileName)) && (!strcmp(this->user, other.user)) &&
            (this->extension == other.extension))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool equalsType(File const &other)
    {
        if ((!strcmp(this->fileName, other.fileName)) && (this->extension == other.extension))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

class Folder
{
private:
    char *folderName;
    int numFiles;
    File *files;

public:
    Folder(const char *folderName = "untitled")
    {
        this->folderName = new char[strlen(folderName) + 1];
        strcpy(this->folderName, folderName);
        numFiles = 0;
        files = nullptr;
    }
    ~Folder()
    {
        delete[] folderName;
        delete[] files;
    }
    void print()
    {
        cout << "Folder name: " << folderName << endl;
        for (int i = 0; i < numFiles; ++i)
        {
            files[i].print();
        }
    }
    void add(File const &f)
    {
        if (numFiles == 0)
        {
            this->files = new File[numFiles + 1];
            files[numFiles++] = f;
        }
        else
        {
            File *tmp;
            tmp = new File[numFiles + 1];
            for (int i = 0; i < numFiles; ++i)
            {
                tmp[i] = files[i];
            }
            tmp[numFiles++] = f;
            delete[] files;
            files = tmp;
        }
    }
    void remove(File const &f)
    {
        if (numFiles == 0)
        {
            cout << "No files to delete" << endl;
        }
        else
        {
            File *tmp;
            int count = 0;
            for (int i = 0; i < numFiles; ++i)
            {
                if (!files[i].equals(f))
                {
                    count++;
                }
            }
            tmp = new File[count];
            count = 0;
            for (int i = 0; i < numFiles; ++i)
            {
                if (!files[i].equals(f))
                {
                    tmp[count++] = files[i];
                }
            }
            delete[] files;
            files = tmp;
            numFiles = count;
        }
    }
};

int main()
{
    char fileName[20];
    char fileOwner[20];
    int ext;
    int fileSize;
    int testCase;
    cin >> testCase;
    if (testCase == 1)
    {
        cout << "======= FILE CONSTRUCTORS AND = OPERATOR =======" << endl;
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File created = File(fileName, fileOwner, fileSize, (EXTENSION)ext);
        File copied = File(created);
        File assigned = created;

        cout << "======= CREATED =======" << endl;
        created.print();
        cout << endl;
        cout << "======= COPIED =======" << endl;
        copied.print();
        cout << endl;
        cout << "======= ASSIGNED =======" << endl;
        assigned.print();
    }
    else if (testCase == 2)
    {
        cout << "======= FILE EQUALS & EQUALS TYPE =======" << endl;
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File first(fileName, fileOwner, fileSize, (EXTENSION)ext);
        first.print();

        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File second(fileName, fileOwner, fileSize, (EXTENSION)ext);
        second.print();

        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File third(fileName, fileOwner, fileSize, (EXTENSION)ext);
        third.print();

        bool equals = first.equals(second);
        cout << "FIRST EQUALS SECOND: ";
        if (equals)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        equals = first.equals(third);
        cout << "FIRST EQUALS THIRD: ";
        if (equals)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        bool equalsType = first.equalsType(second);
        cout << "FIRST EQUALS TYPE SECOND: ";
        if (equalsType)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        equalsType = second.equals(third);
        cout << "SECOND EQUALS TYPE THIRD: ";
        if (equalsType)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;
    }
    else if (testCase == 3)
    {
        cout << "======= FOLDER CONSTRUCTOR =======" << endl;
        cin >> fileName;
        Folder folder(fileName);
        folder.print();
    }
    else if (testCase == 4)
    {
        cout << "======= ADD FILE IN FOLDER =======" << endl;
        char name[20];
        cin >> name;
        Folder folder(name);

        int iter;
        cin >> iter;

        while (iter > 0)
        {
            cin >> fileName;
            cin >> fileOwner;
            cin >> fileSize;
            cin >> ext;

            File file(fileName, fileOwner, fileSize, (EXTENSION)ext);
            folder.add(file);
            iter--;
        }
        folder.print();
    }
    else
    {
        cout << "======= REMOVE FILE FROM FOLDER =======" << endl;
        char name[20];
        cin >> name;
        Folder folder(name);

        int iter;
        cin >> iter;

        while (iter > 0)
        {
            cin >> fileName;
            cin >> fileOwner;
            cin >> fileSize;
            cin >> ext;

            File file(fileName, fileOwner, fileSize, (EXTENSION)ext);
            folder.add(file);
            iter--;
        }
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File file(fileName, fileOwner, fileSize, (EXTENSION)ext);
        folder.remove(file);
        folder.print();
    }
    return 0;
}