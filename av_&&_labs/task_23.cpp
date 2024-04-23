#include <iostream>
#include <cstring>

using namespace std;
class Airplane
{
private:
    char registration[13];
    char *name;
    char airport[21];
    int state;
    int hours;

public:
    Airplane(char *registration = "", char *name = "", char *airport = "", int hours = 0, int state = 0)
    {
        strcpy(this->registration, registration);
        strcpy(this->airport, airport);
        this->name = new char[strlen(name)];
        strcpy(this->name, name);
        this->state = state;
        this->hours = hours;
    }
    Airplane(const Airplane &a)
    {
        strcpy(this->registration, a.registration);
        strcpy(this->airport, a.airport);
        this->name = new char[strlen(a.name)];
        strcpy(this->name, a.name);
        this->state = a.state;
        this->hours = a.hours;
    }
    Airplane &operator=(const Airplane &a)
    {
        if (this != &a)
        {
            delete[] name;
            strcpy(this->registration, a.registration);
            strcpy(this->airport, a.airport);
            this->name = new char[strlen(a.name)];
            strcpy(this->name, a.name);
            this->state = a.state;
            this->hours = a.hours;
        }
        return *this;
    }

    void print()
    {
        cout << "ID: " << registration << " - ";
        if (state == 0)
        {
            cout << "NOT_WORKING ";
        }
        else if (state == 1)
        {
            cout << "REPAIRING ";
        }
        else
        {
            cout << "WORKING ";
        }
        cout << name << ", " << hours << ", " << airport << endl;
    }
    int getState()
    {
        return state;
    }
    char *getAirport()
    {
        return airport;
    }
    int getHours()
    {
        return hours;
    }
    void setState(int s)
    {
        state = s;
    }
    char *getName()
    {
        return name;
    }
    bool equals(const Airplane &a)
    {
        return (!strcmp(a.registration, registration) && !strcmp(a.airport, airport) && !strcmp(a.name, name) && state == a.state && hours == a.hours);
    }
};
class AirportService
{
private:
    char name[21];
    Airplane *airplanes;
    int numAirplanes;

public:
    AirportService(char *name = "")
    {
        this->airplanes = nullptr;
        this->numAirplanes = 0;
        strcpy(this->name, name);
    }
    AirportService(const AirportService &a)
    {
        strcpy(this->name, a.name);
        this->airplanes = new Airplane[a.numAirplanes];
        this->numAirplanes = a.numAirplanes;
        for (int i = 0; i < a.numAirplanes; ++i)
        {
            this->airplanes[i] = a.airplanes[i];
        }
    }
    AirportService &operator=(const AirportService &a)
    {
        if (this != &a)
        {
            delete[] airplanes;
            strcpy(this->name, a.name);
            this->airplanes = new Airplane[a.numAirplanes];
            this->numAirplanes = a.numAirplanes;
            for (int i = 0; i < a.numAirplanes; ++i)
            {
                this->airplanes[i] = a.airplanes[i];
            }
        }
        return *this;
    }
    void print()
    {
        cout << name << endl;
        for (int i = 0; i < numAirplanes; ++i)
        {
            airplanes[i].print();
        }
    }
    void addAirplane(Airplane plane)
    {
        if (!plane.getState())
        {
            plane.setState(1);
            bool flag = false;
            int indeks;
            for (int i = 0; i < numAirplanes; ++i)
            {
                if (!strcmp(plane.getName(), airplanes[i].getName()))
                {
                    flag = true;
                    indeks = i;
                }
            }
            if (flag)
            {
                if (plane.getHours() > airplanes[indeks].getHours())
                {
                    airplanes[indeks] = plane;
                }
            }
            else if (!numAirplanes)
            {
                airplanes = new Airplane[1];
                airplanes[numAirplanes++] = plane;
            }
            else
            {
                Airplane *tmp = new Airplane[numAirplanes + 1];
                for (int i = 0; i < numAirplanes; ++i)
                {
                    tmp[i] = airplanes[i];
                }
                tmp[numAirplanes++] = plane;
                delete[] airplanes;
                airplanes = tmp;
            }
        }
    }
    void remove(Airplane plane)
    {
        auto *tmp = new Airplane[numAirplanes - 1];
        for (int i = 0, b = 0; i < numAirplanes; ++i)
        {
            if (!airplanes[i].equals(plane))
            {
                tmp[b++] = airplanes[i];
            }
        }
        delete[] airplanes;
        airplanes = tmp;
        numAirplanes--;
    }
    Airplane serviceOldestAirplane()
    {
        Airplane oldest = airplanes[0];
        for (int i = 0; i < numAirplanes; ++i)
        {
            if (oldest.getHours() < airplanes[i].getHours())
            {
                oldest = airplanes[i];
            }
            else if (oldest.getHours() == airplanes[i].getHours())
            {
                if (strstr(oldest.getName(), name) != nullptr)
                {
                }
                else if (strstr(airplanes[i].getName(), name) != nullptr)
                {
                    oldest = airplanes[i];
                }
            }
        }
        remove(oldest);
        oldest.setState(2);
        return oldest;
    }
};

int main()
{
    int testCase;
    cin >> testCase;
    char ID[12];
    char company_name[20];
    char company_airport[20];
    int flight_hours;
    int state;
    if (testCase == 1)
    {
        cout << "TESTING CONSTRUCTOR FOR AIRPLANE" << endl;
        Airplane a;
        cout << "TEST FOR DEFAULT CONSTRUCTOR PASSED" << endl;
        Airplane a1("ZHN-96-TY", "FINKI-Airline", "TMF", 13);
        cout << "TEST FOR CONSTRUCTOR WITH 3 ARGUMENTS PASSED" << endl;
        Airplane a2("ZHN-96-TA", "FINKI1-Airline", "TMF", 13, 0);
        cout << "TEST FOR CONSTRUCTOR WITH 4 ARGUMENTS PASSED" << endl;
    }
    else if (testCase == 2)
    {
        cout << "TESTING COPY-CONSTRUCTOR AND OPERATOR = (ASSIGNMENT) FOR AIRPLANE" << endl;
        Airplane p("ZHN-96-TA", "FINKI-Airline", "TMF", 13, 0);
        Airplane p1(p);
        cout << "TEST FOR COPY CONSTRUCTOR PASSED" << endl;
        Airplane p2;
        p2 = p;
        cout << "TEST FOR OPERATOR = (ASSIGNMENT) PASSED" << endl;
    }
    else if (testCase == 3)
    {
        cout << "TESTING PRINT() FOR AIRPLANE" << endl;
        cin >> ID >> company_name >> company_airport >> flight_hours >> state;
        Airplane p(ID, company_name, company_airport, flight_hours, state);
        p.print();
    }
    else if (testCase == 4)
    {
        cout << "TESTING CONSTRUCTOR FOR AIRPORTSERVICE" << endl;
        AirportService as("FINKI");
        cout << "TEST PASSED" << endl;
    }
    else if (testCase == 5)
    {
        cout << "TESTING ADD() AND PRINT() FOR AIRPORTSERVICE" << endl;
        AirportService as("FINKI");
        int n;
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            cin >> ID >> company_name >> company_airport >> flight_hours >> state;
            Airplane p(ID, company_name, company_airport, flight_hours, state);
            as.addAirplane(p);
        }
        as.print();
    }
    else if (testCase == 6)
    {
        cout << "TESTING serviceOldestAirplane() AND PRINT() FOR AIRPORTSERVICE" << endl;
        AirportService as("FINKI");
        int n;
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            cin >> ID >> company_name >> company_airport >> flight_hours >> state;
            Airplane p(ID, company_name, company_airport, flight_hours, state);
            as.addAirplane(p);
        }
        Airplane p = as.serviceOldestAirplane();
        cout << "Removed plane:" << endl;
        p.print();
        cout << "-----------------" << endl;
        as.print();
    }
    else if (testCase == 7)
    {
        cout << "TESTING COPY CONSTRUCTOR AND OPERATOR = FOR AIRPORTSERVICE" << endl;
        AirportService as("FINKI");
        Airplane a1("ZHN-96-TY", "FINKI-Airline", "TMF", 13);
        as.addAirplane(a1);

        AirportService s1 = as; // copy constructor
        AirportService s2;
        s2 = s1; // operator =
        s1.print();
        s2.print();
    }
    return 0;
}