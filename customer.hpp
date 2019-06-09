#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <queue>
#include <vector>
#include <chrono>

#include "hashTable.hpp"


using namespace std;


//Struct for customer, each customer will have a 
//username and password for signing in, a shopping list, and a reserve list
struct Customers
{
    string customerName;
    string username;
    string password;
    vector<storeItem*> shoppingList;
    
};

struct ReservedItem
{
    Customers* customer;
    string itemName;
    int quantRes;
    std::time_t reserveTime;
    // bool pickedUp;
};

class Customer
{
public:
    Customer(Store* store); //Takes in pointer to the store (hashtable) to make sure everything saves properly
    //Store is a class found in hashTable.cpp
    void addUser(); //Method to add a user
    Customers* loginUser(); // Login method that returns pointer to Customers struct
    // void reservedCustomer(string productNamel);
    void viewShoppingList(Customers* c); //Method to view shopping list, takes in Customers* to access
    //proper shopping list
    void addToShoppingList(string productName, Customers* c); //Method to add to shopping list
    //takes in productName to locate in hashtable and customers* to add to customer list
    void printToFile(Customers* ch); // exports shopping list to external file
    void reserveItem(Store* s, Customers* c, string productName, int resQuan); // function for customer to reserve item
    vector<ReservedItem*> reserveVec; 

    
    
    

    
private:
    vector<Customers*> vecCustomers; //vector holding all the customers information
    // queue<reservedCustomer*> reserveQueue;  
    Store* store; // Store class object so that we can use Class:: methods in this class.

};
#endif

