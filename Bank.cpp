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
    Person(string name, string password)
    {
        setName(name);
        setPassword(password);
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

    int getId() const { return id; }
    const string &getName() const { return name; }
    const string &getPassword() const { return password; }
    bool getStatus() const { return status; }

    virtual void displayInfo() const
    {
        cout << "============================\n";
        cout << "Id is: " << id << endl;
        cout << "Name is: " << name << endl;
        cout << "Password is: " << password << endl;
    }

    virtual bool statusActivation() const = 0;
};

class Employee : public Person
{
private:
    double salary;

public:
    Employee(string name, string password, double salary) : Person(name, password), salary(0) { setSalary(salary); }

    void setSalary(double salary)
    {
        if (salary >= 5000)
            this->salary = salary;
        else
            cout << "Salary must be at least 5000." << endl;
    }

    double getSalary() const { return salary; }

    void displayInfo() const override
    {
        Person::displayInfo();
        cout << "Salary is: " << salary << endl;
    }

    bool statusActivation() const override { return getStatus(); }
};

class Client : public Person
{
private:
    double balance;

public:
    Client(string name, string password, double balance) : Person(name, password), balance(0) { setBalance(balance); }

    void setBalance(double balance)
    {
        if (balance >= 1500)
            this->balance = balance;
        else
            cout << "Balance must be at least 1500." << endl;
    }

    double getBalance() const { return balance; }

    void displayInfo() const override
    {
        Person::displayInfo();
        cout << "Balance is: " << balance << endl;
    }

    void deposit(double amount)
    {
        if (!getStatus())
        {
            cout << "Account is inactive." << endl;
            return;
        }

        if (amount > 0)
            balance += amount;
        else
            cout << "Invalid deposit amount." << endl;
    }

    void withdraw(double amount)
    {
        if (!getStatus())
        {
            cout << "Account is inactive." << endl;
            return;
        }

        if (amount > 0 && amount <= balance)
            balance -= amount;
        else
            cout << "Invalid withdrawal amount." << endl;
    }

    void transferTo(double amount, Client &recipient)
    {
        if (!getStatus())
        {
            cout << "Your account is inactive." << endl;
            return;
        }

        if (!recipient.getStatus())
        {
            cout << "Recipient account is inactive." << endl;
            return;
        }

        if (&recipient == this)
        {
            cout << "Cannot transfer to the same account." << endl;
            return;
        }

        if (amount > 0 && amount <= balance)
        {
            balance -= amount;
            recipient.balance += amount;
        }
        else
        {
            cout << "Invalid transfer amount." << endl;
        }
    }

    bool statusActivation() const override { return getStatus(); }
};

int Person::counterId = 1000;

int main()
{
    Employee m1("Zeyad Mohsen", "asdf1234", 6000);
    Client c1("Abdulla Mohamed", "asdf1212", 6000);

    Person *p1 = &m1;
    Person *p2 = &c1;

    p1->displayInfo();
    p2->displayInfo();

    cout << boolalpha;
    cout << p1->statusActivation() << endl;
    cout << p2->statusActivation() << endl;

    return 0;
}