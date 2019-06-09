#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct storeItem
{
    string itemName;
    //string brandName;
    int itemID;
    int quantity;
    int aisleNumber;
    int expirationDate;
    string expirationString;
    storeItem* nextItemInList;
};



class Store
{
public:
    Store(int tableSize); // Hashtable constructor
    //~Store();
    void incrementProductCount(std::string productName); //for restocking purposes  
    void addStoreItem(string productName, int productID, int productQuantity, int expirationDate, string expirationString);//adds item to hashtable
    void removeStoreItem(string name, int quantity);
    std::vector<storeItem*> searchStore(string productName);//searches store, returns vector of storeItem* that contain similar words to the one entered in function
    void printProductInfo(std::vector<storeItem*> items); //prints necessary product info 
    queue<storeItem> returnQueue(int n); //Shows items in order of experation dates, queue size entered as argument
    void readInItems(Store* hT); //reads in store items from spreadsheet 
    queue<storeItem> expiringSoon(); // returns queue of items that are expiring in order of which items are expiring soonest
    queue<storeItem> restockQueue(int n); // returns a queue of which items have less than n products left
    void printItemInformation(storeItem* m); // prints item information
    
    
private:
    int getHash(string itemName); //assigns item hash
    storeItem** hashTable; //the hash table
    int hashTableSize;//the size of the hashtable
};
#endif
