#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <iostream>
#include <vector>
#include <string>
#include "customer.hpp"
#include "hashTable.hpp"

using namespace std;

struct Employees
{
    int empID;
    string userName;
    string password;
};

class Employee
{
public:
    Employee(Store* store);
    void addEmployee(int iD, string userName, string password); // adds employee to employee vector
    Employees* login(); // function to allow employee to login
    vector<Employees*> vecEmployees; // vector of employee login info
    //void viewResList(Customer* c); // function for employee to view reservations made by customer -- does not work 
private:
    Store* store;
};

#endif
