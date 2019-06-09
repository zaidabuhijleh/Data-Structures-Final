#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "hashTable.hpp"
#include "employees.hpp"
#include "customer.hpp"

class Customer;

using namespace std;

Employee::Employee(Store* store)
{
    this->store  = store;
}
// function adds employee to employee vector
void Employee::addEmployee(int iD, string userName, string password)
{
    Employees* newEmployee = new Employees;

    newEmployee->empID = iD;
    newEmployee->userName = userName;
    newEmployee->password = password;

    vecEmployees.push_back(newEmployee);
}

// function asks for employee username and password to login employee
Employees* Employee::login()
{
    ifstream myfile("usernamePasswords.csv");
    string Line;
    Employees* emp;
    cout<<"Loading Employee Info..."<<endl;
    //getline(myFile, line);
    while(getline(myfile,Line))
    {
        stringstream Ss;
        Ss<<Line;
        string name;
        string idString;
        string username;
        string password;


        getline(Ss, username, ',');

        getline(Ss, password, ',');

        getline(Ss, idString, ',');

        addEmployee(atoi(idString.c_str()), username, password);
    }
    Employees* thisEmp;
    // int loginAttempt = 0;
    bool inVec = false;
    string username;
    cout << "Enter Username: " << endl;
    cin >> username;

    string password;
    cout << "Enter Password: " << endl;
    cin >> password;

    for(int i = 0; i < vecEmployees.size(); i++)
    {
        if(username.compare(vecEmployees[i]->userName) == 0 && password.compare(vecEmployees[i]->password) == 0)
        {
            thisEmp = vecEmployees[i];
            inVec = true;
        }
    }

    if(inVec == true)
    {
        cout << "Welcome " << thisEmp->userName << endl;
        return thisEmp;
    }
    
    else
    {
        cout << "Username or password is wrong, please try again." << endl;
        login();
    }
    
}


/*void Employee::viewResList(Customer* c)
{
    vector<ReservedItem*> rv = c->reserveVec;
    for(int i = 0; i < rv.size(); i ++)
    {
        cout << " ==== Customer " << i + 1 << "====" << endl;
        cout << "Customer Name: " << rv[i]->customer->customerName << endl;
        cout << "Customer's Reserve Item: " << endl;
        cout << "Item Name: " << rv[i]->itemName << endl;
        cout << "Quantity Requested: " << rv[i]->quantRes << endl;
        cout << "Reservation Time: " << rv[i]->reserveTime << endl;
        cout << "================" << endl;
    }
}*/