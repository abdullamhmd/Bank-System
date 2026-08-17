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
    bool status;
    static int counterId;

public:
    Person(string name, string password) : name(name), password(password)
    {
        status = true;
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

    void setStatus(bool status) { this->status = status; }

    const int &getId() const { return id; }
    const string &getName() const { return name; }
    const string &getPassword() const { return password; }
    const bool getStatus() const { return status; }

    virtual void dispalyInfo()
    {
        cout << "============================\n";
        cout << "Id is: " << id << endl;
        cout << "Name is: " << name << endl;
        cout << "Password is: " << password << endl;
    }

    virtual bool statusActivtion() = 0;
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

    bool statusActivtion() { return getStatus(); }
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

    bool statusActivtion() { return getStatus(); }
};

int Person::counterId = 1000;

int main()
{
    Employee m1("Zeyad Mohsen", "asdf1234", 3500);

    Client c1("Abdulla Mohamed", "asdf1212", 6000);

    return 0;
}