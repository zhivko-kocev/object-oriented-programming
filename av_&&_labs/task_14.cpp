#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

class User {
private:
    char *id{};
    char *username{};
    char *password{};

    void copy(const User &other) {
        this->id = new char[strlen(other.id) + 1];
        this->username = new char[strlen(other.username) + 1];
        this->password = new char[strlen(other.password) + 1];
        strcpy(this->id, other.id);
        strcpy(this->username, other.username);
        strcpy(this->password, other.password);
    }

    void freeMem() {
        delete[] id;
        delete[] username;
        delete[] password;
    }

public:
    User() {
        this->id = new char[10];
        this->username = new char[10];
        this->password = new char[10];
        strcpy(this->id, "000000000");
        strcpy(this->username, "Unknown");
        strcpy(this->password, "Unknown");
    }

    User(char *id, char *username, char *password) {
        this->id = new char[strlen(id) + 1];
        this->username = new char[strlen(username) + 1];
        this->password = new char[strlen(password) + 1];
        strcpy(this->id, id);
        strcpy(this->username, username);
        strcpy(this->password, password);
    }

    User(const User &other) {
        copy(other);
    }

    User &operator=(const User &other) {
        if (this != &other) {
            freeMem();
            copy(other);
        }
        return *this;
    }

    friend ostream &operator<<(ostream &os, const User &other) {
        return os << "ID:" << other.id << " Username:" << other.username << " Password:" << other.password << endl;
    }

    ~User() {
        freeMem();
    }

    void setUsername(char *_username) {
        delete[] username;
        username = new char[strlen(_username) + 1];
        strcpy(username, _username);
    }

    void setPassword(char *_password) {
        delete[] username;
        username = new char[strlen(_password) + 1];
        strcpy(username, _password);
    }

    bool SaveToFile(const char *filename) {
        ofstream outF(filename, ios::out | ios::app);

        if (!outF)
            return false;

        outF.write((char *) &*this, sizeof(*this));
        outF.write((char *) "\n", 1);


        outF.close();


        return true;
    }

};

bool ReadFromFile(const char *filename, User &u) {
    ifstream outF(filename, ios::out);

    if (!outF)
        return false;

    outF.read((char *) &u, sizeof(u));
    cout << u;
    outF.close();
    return true;
}

int main() {
    User u("223117", "Kocew", "zikekocev");
    u.SaveToFile(R"(D:\Codes\CLionProjects\KocewOOP\new.txt)");
    User u1("223137", "Kocc", "azadaddsa");
    u.SaveToFile(R"(D:\Codes\CLionProjects\KocewOOP\new.txt)");
    return 0;
}