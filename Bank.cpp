#include <iostream>
#include <string>
#include <cctype>
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

    void setName(string name)
    {
        bool valid = true;
        for (char c : name)
        {
            if (!isalpha(c) && c != ' ')
            {
                valid = false;
                break;
            }
        }
        if (name.size() >= 5 && name.size() <= 20 && valid)
            this->name = name;
        else
            cout << "Name is invalid" << endl;
    }

    void setPassword(string password)
    {
        if (password.length() >= 8 && password.length() <= 20)
            this->password = password;
        else
            cout << "Password length must be between 8 and 20 characters" << endl;
    }

    const int &getId() const { return id; }
    const string &getName() const { return name; }
    const string &getPassword() const { return password; }

    virtual void dispalyInfo()
    {
        cout << "============================\n";
        cout << "Id is: " << id << endl;
        cout << "Name is: " << name << endl;
        cout << "Password is: " << password << endl;
    }
};

class Employee : public Person
{
private:
    double salary;

public:
    Employee(string name, string password, double salary) : Person(name, password), salary(salary) {}

    void setSalary(double salary)
    {
        if (salary >= 5000)
            this->salary = salary;
        else
            cout << "Salary must be at least 5000." << endl;
    }

    const double &getSalary() const { return salary; }

    void dispalyInfo() override
    {
        Person::dispalyInfo();
        cout << "Salary is: " << salary << endl;
    }
};

class Client : public Person
{
private:
    double balance;

public:
    Client(string name, string password, double balance) : Person(name, password), balance(balance) {}

    void setBalance(double balance)
    {
        if (balance >= 1500)
            this->balance = balance;
        else
            cout << "Balance must be at least 1500." << endl;
    }

    const double &getBalance() const { return balance; }

    void dispalyInfo() override
    {
        Person::dispalyInfo();
        cout << "Balance is: " << balance << endl;
    }

    void deposit(double amount)
    {
        if (amount > 0)
            balance += amount;
        else
            cout << "Amount must be greater than zero." << endl;
    }

    void withdraw(double amount)
    {
        if (amount >= balance)
            balance -= amount;
        else
            cout << "Amount must be greater than Balance." << endl;
    }

    void transferTo(double amount, Client &recipient)
    {
        if (amount >= balance)
        {
            balance -= amount;
            recipient.balance += amount;
        }
        else
            cout << "Amount must be greater than Balance." << endl;
    }
};

int Person::counterId = 1000;

int main()
{
    Person p1("Abdulla Mohamed", "asd123");
    Person p2("Ahmed Adel", "asd123");
    Person p3("Aya Aymen", "asd123");

    Employee m1("Zeyad Mohsen", "asdf1234", 3500);

    return 0;
}