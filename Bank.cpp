#include <iostream>
#include <string>
#include <cctype>
#include <vector>
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
        cout << "===== Personal Information =====" << endl;
        cout << "ID        : " << id << endl;
        cout << "Name      : " << name << endl;
        cout << "Password  : " << password << endl;
        cout << "Status    : " << (status ? "Active" : "Inactive") << endl;
    }

    virtual bool statusActivation() const = 0;

    virtual ~Person() {}
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

class Admin : public Person
{
private:
    double balance;

public:
    Admin(string name, string password, double balance) : Person(name, password), balance(0)
    {
        setBalance(balance);
    }

    void setBalance(double balance)
    {
        if (balance >= 5000)
            this->balance = balance;
        else
            cout << "Balance must be at least 5000." << endl;
    }

    double getBalance() const { return balance; }

    void displayInfo() const override
    {
        Person::displayInfo();
        cout << "Balance is: " << balance << endl;
    }

    bool statusActivation() const override { return getStatus(); }
};

class Bank
{
private:
    vector<Person *> person;

public:
    void addPerson(Person *person) { this->person.push_back(person); }

    void displayAll()
    {
        for (int i = 0; i < person.size(); i++)
        {
            person[i]->displayInfo();
        }
    }
};

int Person::counterId = 1000;

int main()
{
    Bank bank;

    Person *ptr[] = {
        new Employee("Zeyad Mohsen", "asdf1234", 6000),
        new Employee("Ahmed Ali", "ahmed123", 7000),
        new Client("Abdulla Mohamed", "asdf1212", 6000),
        new Client("Mohamed Ali", "mohamed12", 3000),
        new Admin("Omar Hassan", "omar1234", 5000)};

    for (Person *p : ptr)
    {
        bank.addPerson(p);
    }

    bank.displayAll();

    for (Person *p : ptr)
    {
        delete p;
    }

    return 0;
}