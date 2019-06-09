#include "employees.hpp"
#include "hashTable.hpp"
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include "hashTable.hpp"
#include "customer.hpp"

using namespace std;

Store::Store(int tableSize)
{
    hashTable = new storeItem*[tableSize];
    hashTableSize = tableSize;
    for(int i = 0; i < hashTableSize; i++)
    {
        hashTable[i] = new storeItem;
        hashTable[i] = NULL;
    }
}

int Store::getHash(string itemName)
{
    int hash = 5381;

    for(auto c : itemName)
    {
        hash = (hash << 5) + hash + c;
    }

    hash = hash % hashTableSize;

    if(hash < 0)
    {
        hash = hash + hashTableSize;
    }

    return hash;
}

void Store::readInItems(Store* hT)
{
    // fstream myFile("Grocery_UPC_Database_Revised.csv");
    fstream myFile("test_file.csv");
	if(!myFile.is_open())
	{
		cout << "file not open" << endl;
	}
	string line;
	storeItem product;
	
	cout<<"Loading grocery inventory..."<<endl;
	//getline(myFile, line);
	while(getline(myFile,line))
	{
		stringstream ss;
		ss<<line;
		string upc14;
		string Brand;
		string itemName;
		string quantity;
		string expirationDate;
		string expirationString;


		getline(ss, upc14, ',');

		getline(ss, Brand, ',');

		getline(ss, itemName, ',');
		// cout<< "ITEM NAME: " << itemName<<endl;

		getline(ss, quantity, ',');

		getline(ss, expirationDate, ',');

		getline(ss, expirationString, ',');
		// cout<<expirationString<<endl;

		hT->addStoreItem(itemName, atoi(upc14.c_str()), atoi(quantity.c_str()), atoi(expirationDate.c_str()), expirationString);
    }
}



void Store::printProductInfo(std::vector<storeItem*> items)
{

    // storeItem* item = searchStore(productName);
    for(storeItem* item : items) {
        if(item == NULL)
        {
            cout << "NULL PTR" << endl;
            return;
        }
        cout <<  "PRODUCT INFO" << endl;
        cout << "-------" << endl;
        cout << "Item Name: " << item->itemName << endl;
        cout << "Item ID#: " << item->itemID << endl;
        cout << "Item Quantity: " << item->quantity << endl;
        cout << "Found in aisle: " << item->aisleNumber << endl;
    }
}

void Store::incrementProductCount(std::string productName)
{
    
    std::vector<storeItem*> ptrs = searchStore(productName);

    for(storeItem* ptr : ptrs) {
        ptr->quantity = ptr->quantity+1;
    }
}

void Store::removeStoreItem(string name, int quantity)
{
    vector<storeItem*> temp = searchStore(name);
    for(int i = 0; i < temp.size(); i++)
    {
        if(temp[i]->quantity-quantity<0)
        {
            temp[i]->quantity=0;
        }
        else
        {
            temp[i]->quantity -= quantity;
        }
    }
    
    printProductInfo(temp);
}

void Store::addStoreItem(string productName, int productID, int productQuantity, int expirationDate, string expirationString)
{
    // cout << "in addstoreItem" << endl;
    if(searchStore(productName).size() > 0)
    {
        // cout << "incrementing" << endl;
        incrementProductCount(productName);
        return;
    }
    int index = getHash(productName);
    storeItem* prev = NULL;
    storeItem* temp = hashTable[index];
    while (temp != NULL)
    {
        // cout << "traversing down list" << endl;
        prev = temp;
        temp = temp->nextItemInList;
    }
    // cout << " hehe" << endl;
    temp = new storeItem;
    temp->itemName = productName;
    temp->itemID = productID;
    temp->quantity = productQuantity;
    temp->expirationDate = expirationDate;
    temp->expirationString = expirationString;
    temp->nextItemInList = NULL;
    temp->aisleNumber = index%20;
    if (prev == NULL)
    {
        // cout << "here" << endl;
        hashTable[index]= temp;
        
        return;
    }
    else
    {
        temp->itemName = productName;
        prev->nextItemInList = temp;
        incrementProductCount(productName);

        // cout << "Item name: " << temp->itemName << endl;
        // cout << "Item quantity: " << temp->quantity << endl;
        // cout << "Aisle Number: " << temp->aisleNumber << endl << endl;
        
        // currentSize += 1;
        return;
    }
    

}

void Store::printItemInformation(storeItem* m)
{
	if(m==NULL)
	{
		cout << "Item not found." << endl;
	}
    cout << "Item Name: " << m->itemName << endl;
    cout << "Found in Aisle: " << m->aisleNumber << endl;
    cout << "Quantity in Stock: " << m->quantity << endl;
    cout << "Expiring: "<<m->expirationString<<endl;
    return;
}

std::vector<storeItem*> Store::searchStore(string productName)
{
    std::vector<storeItem*> retItems;
    int index = getHash(productName);
    storeItem* temp = hashTable[index];
    while(temp!=NULL){
        if(temp->itemName.find(productName) != string::npos)
        {
            retItems.push_back(temp);
            // return temp;
        }
        temp = temp->nextItemInList;
    }
    return retItems;
}

queue<storeItem> Store::restockQueue(int n)
{
    queue<storeItem> myQueue;
    storeItem* temp;
    storeItem* post;
    storeItem tempy;
    for(int i=0; i<hashTableSize; i++)
    {
        temp = hashTable[i];
        post = temp->nextItemInList;
        while(post!=NULL)
        {
            if(temp->quantity < n)
            {
                myQueue.push(*temp);
            }
            temp = temp->nextItemInList;
            post = post->nextItemInList;
        }
    }
    return myQueue;
}


queue<storeItem> Store::returnQueue(int n)
{
    queue<storeItem> myQueue;
    storeItem* temp;
    int max=0;
    storeItem array[n+1];
    array[0].expirationDate=1000000;
    for(int k=1; k<(n+1); k++){
        array[k].expirationDate=100000000;
    }

    for(int i=1; i<(n+1); i++)
    {
        max = 0;
        for(int j=0; j<(hashTableSize); j++)
        {   
            temp = hashTable[j];
            while(temp!=NULL)
            {
                if(array[i].expirationDate > temp->expirationDate && temp->expirationDate > array[i-1].expirationDate)
                {
                    array[i].expirationDate = temp->expirationDate;
                    array[i].expirationString = temp->expirationString;
                    array[i].itemName = temp->itemName;
                    

                }
                temp = temp->nextItemInList;
            }
        }
    }
    for(int k=1; k<(n+1); k++)
    {
        myQueue.push(array[k]);
    }
    
    return myQueue;
}

queue<storeItem> Store::expiringSoon()
{
    queue<storeItem> myQueue;
    storeItem* temp;
    int max=0;
    storeItem array[50+1];
    array[0].expirationDate=1000000;
    for(int k=1; k<(50+1); k++){
        array[k].expirationDate=100000000;
    }

    for(int i=1; i<(50+1); i++)
    {
        max = 0;
        for(int j=0; j<(hashTableSize); j++)
        {   
            temp = hashTable[j];
            while(temp!=NULL)
            {
                if(array[i].expirationDate > temp->expirationDate && temp->expirationDate > array[i-1].expirationDate)
                {
                    array[i].expirationDate = temp->expirationDate;
                    array[i].expirationString = temp->expirationString;
                    array[i].itemName = temp->itemName;
                    array[i].itemID = temp->itemID;
                    array[i].quantity = temp->quantity;
                    array[i].aisleNumber = temp->aisleNumber;
                    

                }
                temp = temp->nextItemInList;
            }
        }
    }
    for(int k=1; k<(50+1); k++)
    {
        myQueue.push(array[k]);
    }
    
    return myQueue;
}