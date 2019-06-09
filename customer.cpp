#include "customer.hpp"
#include "hashTable.hpp"
#include "employees.hpp"
#include <ctime>
#include <iostream>
#include <queue>
#include <fstream>
#include <string>
#include <vector>
#include <ratio>


class Employee;

using namespace std;

Customer::Customer(Store* store)
{
    this->store = store;
}

void Customer::addUser()
{
    Customers* newCustomer = new Customers;
    
    string name;
    cout << "Enter Customer Name: " << endl;
    getline(cin, name);

    string userName;
    cout << "Enter Customer Username: " << endl;
    cin >> userName;

    string passwordIn;
    cout << "Enter Customer Password: " << endl;
    cin >> passwordIn;

    newCustomer->customerName = name;
    newCustomer->username = userName;
    newCustomer->password = passwordIn;

    vecCustomers.push_back(newCustomer);
}

Customers* Customer::loginUser()
{
    
    Customers* thisCust;
    // int loginAttempt = 0;
    bool inVec = false;
    string username;
    cout << "Enter Username: " << endl;
    cout << "*To return to menu enter '0'*" << endl;
    cin >> username;

    string password;
    cout << "Enter Password: " << endl;
    cout << "*To return to menu enter '0'*" << endl;
    cin >> password;

    if(username == "0" || password == "0")
    {
        return NULL;
    }

    for(int i = 0; i < vecCustomers.size(); i++)
    {
        if(username.compare(vecCustomers[i]->username) == 0 && password.compare(vecCustomers[i]->password) == 0)
        {
            thisCust = vecCustomers[i];
            inVec = true;
        }
    }

    if(inVec == true)
    {
        cout << "Welcome " << thisCust->customerName << endl;
        return thisCust;
    }
    
    else
    {
        cout << "Username or password is wrong, plese try again." << endl;
        loginUser();
    }
    
}

// void Customer::reserveItem(string productName, Customers* c, int reserveQuantity)
// {
    
//     std::vector<storeItem*> temp = store->searchStore(productName);

//     if(temp.size() == 0)
//     {
//         cout << "item not in store" << endl;
//         return;
//     }
//     else
//     {
        
//         if(temp.size() = 1)
//         temp = store->searchStore(productName);
//         if(temp->quantity == 0)
//         {
//             cout << "Item out of stock." << endl;
//             return;
//         }

//         if(reserveQuantity > temp->quantity)
//         {
//             cout << "Item quantity lower than requested quantity, please enter a quantity equal or lower than: " << temp->quantity << "." << endl;
//             return;
//         }
//         else
//         {
//             enqueueCustomer(temp);
//             temp->quantity = temp->quantity - reserveQuantity;
//         }
//     }    
// }

void Customer::addToShoppingList(string productName, Customers* c)
{
    std::vector<storeItem*> temp = store->searchStore(productName);
    if(temp.size() == 0)
    {
        cout << "Item not in store" << endl;
        return;
    }
    else if(temp.size() == 1)
    {
        c->shoppingList.push_back(temp[0]);
        return;
    }
    else
    {
        // for(int i = 0; i < temp.size(); i++)
        // {
        //     store->printProductInfo(temp);
        // }
        store->printProductInfo(temp);
        cout << "Enter more accurate product name from list above: " << endl;
        string prodName;
        getline(cin, prodName);

        for(int i = 0; i < temp.size(); i++)
        {
            if(temp[i]->itemName.compare(prodName) == 0)
            {
                cout << "found and added" << endl;
                c->shoppingList.push_back(temp[i]);
                return;
            }
        }
    }
}

void Customer::viewShoppingList(Customers* c)
{
    // Store store;
    if(c->shoppingList.size() <= 0)
    {
        cout << "Shopping list empty" << endl;
    }
    cout << "VIEW SHOPPING CART" << endl;
    for(int i = 0; i < c->shoppingList.size(); i++)
    {
        cout << "Product " << i+1 << ":" << endl;
        store->printProductInfo(store->searchStore(c->shoppingList[i]->itemName));
    }
}

void Customer::printToFile(Customers* c)
{
    ofstream myFile;
    myFile.open("Shopping List");
    myFile << "==========" << endl;
    myFile << "=== Shopping List ===" << endl;

    for(int i = 0; i < c->shoppingList.size(); i++)
    {
        string item = c->shoppingList[i]->itemName;
        int quant = c->shoppingList[i]->quantity;
        int aisleNum = c->shoppingList[i]->aisleNumber;
        
        myFile << "==========" << endl;
        myFile << "== Item " << i + 1 << " ==" << endl;
        myFile << "Item Name: " << item << endl;
        myFile << "Item Quantity in Stock: " << quant << endl;
        myFile << "Item Found in Aisle: " << aisleNum << endl;
        myFile << "==========" << endl; 
    }

}

void Customer::reserveItem(Store* store, Customers* c, string productName, int resQuan)
{
    std::vector<storeItem*> temp = store->searchStore(productName);
    if(temp.size() == 0)
    {
        cout << "Item not in store" << endl;
        return;
    }
    else if(temp.size() == 1)
    {
        c->shoppingList.push_back(temp[0]);
        return;
    }
    else
    {
        store->printProductInfo(temp);
        cout << "Enter more accurate product name from list above: " << endl;
        string prodName;
        getline(cin, prodName);
        int quantityRes;
        
        for(int i = 0; i < temp.size(); i++)
        {
            if(temp[i]->itemName.compare(prodName) == 0)
            {
                if(temp[i]->quantity < resQuan)
                {
                    cout << "Requested quantity more than stock quantity." << endl;
                    cout << "Please enter quantity equal or less than: " << temp[i]->quantity << endl;
                    cin >> quantityRes;
                    reserveItem(store, c, productName, quantityRes);
                }

                else
                {
                    ReservedItem* resItem;

                    temp[i]->quantity -= resQuan;
                    ReservedItem tempRes;
                    resItem->customer = c;
                    resItem->quantRes = resQuan; 
                    resItem->reserveTime = std::time(0); 
                    reserveVec.push_back(&tempRes);
                    cout << "Item reserved" << endl;
                    return;
                }
            }
        }
    }
}

