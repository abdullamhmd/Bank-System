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
    vector<Employee> employees;
    vector<Client> clients;
    vector<Admin> admins;

public:
    void addEmployee(const Employee &employee)
    {
        employees.push_back(employee);
    }

    void addClient(const Client &client)
    {
        clients.push_back(client);
    }

    void addAdmin(const Admin &admin)
    {
        admins.push_back(admin);
    }

    void displayEmployees() const
    {
        for (const Employee &employee : employees)
        {
            employee.displayInfo();
        }
    }

    void displayClients() const
    {
        for (const Client &client : clients)
        {
            client.displayInfo();
        }
    }

    void displayAdmins() const
    {
        for (const Admin &admin : admins)
        {
            admin.displayInfo();
        }
    }
};

int Person::counterId = 1000;

int main()
{
    Employee e1("Zeyad Mohsen", "asdf1234", 6000);
    Employee e2("Ahmed Ali", "ahmed123", 7000);

    Client c1("Abdulla Mohamed", "asdf1212", 6000);
    Client c2("Mohamed Ali", "mohamed12", 3000);

    Admin a1("Omar Hassan", "omar1234", 5000);

    Bank bank;

    bank.addEmployee(e1);
    bank.addEmployee(e2);

    bank.addClient(c1);
    bank.addClient(c2);

    bank.addAdmin(a1);

    cout << "\n===== Employees =====\n";
    bank.displayEmployees();

    cout << "\n===== Clients =====\n";
    bank.displayClients();

    cout << "\n===== Admins =====\n";
    bank.displayAdmins();

    return 0;
}