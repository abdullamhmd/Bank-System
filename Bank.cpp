#include <iostream>
#include <string>
#include <exception>
using namespace std;

class Person
{
private:
    int id;
    string name;
    string password;

    static int counterId;

public:
    Person(string name, string password) : name(name), password(password)
    {
        counterId++;
        id = counterId;
    }

    void setName(string name) { this->name = name; }
    void setPassword(string password) { this->password = password; }

    int getId() { return id; }
    string getName() { return name; }
    string getPassword() { return password; }

    void dispalyInfo()
    {
        cout << "============================\n";
        cout << "Id is: " << id << endl;
        cout << "Name is: " << name << endl;
        cout << "Password is: " << password << endl;
    }
};

int Person::counterId = 1000;

int main()
{
    Person p1("Abdulla", "asd123");
    Person p2("Ahmed", "asd123");
    Person p3("Aya", "asd123");

    p1.dispalyInfo();
    p2.dispalyInfo();
    p3.dispalyInfo();

    cout << p2.getId();
    cout << p1.getId();

    return 0;
}