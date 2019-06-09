#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include "hashTable.hpp"
#include "customer.hpp"
#include "employees.hpp"

using namespace std;

void loginOptions(Customers* c, Store* s, Customer* ch); //a function that takes logged-in users to another menu

void employeeLoginOptions(Employees* e, Store* s, Customer* c, Employee* emp);
void employeeOptions( Store* s, Employee* e, Customer* customer);
void customerOptions(Store* s, Customer* ch);

int main()
{
	Store thisStore(20);
	Customer customer(&thisStore);
	Employee employee(&thisStore);
	//employee.readEmpFile(&thisStore);
	thisStore.readInItems(&thisStore);

	int choice = 0;
	while(choice != 3)
	{
		cout << "===============================" << endl;
		cout << "===== ZADISON SUPERMARKET =====" << endl;
		cout << "===============================" << endl;
		cout << "- Welcome to Zadison Supermarket -" << endl;

        cout << "1. Customer  Menu" << endl;
        cout << "2. Employee Menu" << endl;
        cout << "3. Quit" << endl;

		cin >> choice;

		switch(choice)
		{
			case 1:
			{
				cin.ignore();
				customerOptions(&thisStore, &customer);

				choice = 1;
				break;
			}
			case 2:
			{
				cin.ignore();
				employeeOptions(&thisStore, &employee, &customer);
				choice = 2;
				break;
			}
			case 3:
			{
				cin.ignore();
				cout << "Have a good day!" << endl;

				choice = 3;
				break;
			}
			default:
			{
				cin.ignore();
				cout << "Please enter a number between 1 and three: " << endl;
				break;
			}
		}
	
	}


	
	return 0;
}

void loginOptions(Customers* c, Store* s, Customer* ch)
{
	int choice = 0;

	while(choice != 5)
	{
		cout << "===== USER MENU =====" << endl;
		cout << "-- Welcome: " << c->customerName << " --" << endl;
		cout << "1. Search Store" << endl;
		cout << "2. Add to Shopping List" << endl;
		cout << "3. View Shopping List" << endl;
        cout << "4. Save Shopping List" << endl;
		//cout << "5. Reserve Store Item" << endl;
        cout << "5. Logout" << endl;

		cin >> choice;

		switch(choice)
		{
			case 1:
			{
				cin.ignore();
				string itemName;
				cout << "-Search Store-" << endl;
				cout << "Enter Product Name:" << endl;
				getline(cin, itemName);
                // cout << "TEST: " << itemName << endl;
				std::vector<storeItem*> temp = s->searchStore(itemName);
                // cout << "Test SIze: " << s->currentSize << endl;
				s->printProductInfo(temp);

				choice = 1;
				break;
			}
			case 2:
			{
				cin.ignore();
				string itemName;
				cout << "-Add to Shopping List-" << endl;
				cout << "Enter Product Name:" << endl;
				getline(cin, itemName);
				ch->addToShoppingList(itemName, c);

				choice = 2;
				break;
			}
			case 3:
			{
				cin.ignore();
				cout << "-View Shopping List-" << endl;
				ch->viewShoppingList(c);

				choice = 3;
				break;
			}
            case 4:
            {
                cin.ignore();
                ch->printToFile(c);

                choice = 4;
                break;
            }
            case 5:
			{
				cin.ignore();
				cout << "Goodbye!" << endl;
                choice = 6;
			}
			default:
			{
				cout << "Please enter a number between 1 and 6: " << endl;
				break;
			}
		}
	}
}

void customerOptions(Store* s, Customer* ch)
{
	int choice = 0;

	while(choice != 3)
	{
		cout << "===============================" << endl;
		cout << "======= ZADISON SUPERMARKET =======" << endl;
		cout << "===============================" << endl;
		cout << "-- Welcome to Zadison Supermarket --" << endl;

        cout << "1. Sign In" << endl;
        cout << "2. Sign Up" << endl;
        cout << "3. Quit" << endl;


        cin >> choice;

        switch(choice)
        {
            case 1:
            {
                cin.ignore();
                Customers* temp;
                temp = ch->loginUser();
                loginOptions(temp, s, ch);
                if(loginOptions == NULL)
                {
                    return;
                }
                choice = 1;
                break;
            }
            case 2:
            {
                cin.ignore();
                ch->addUser();
                choice = 2;
                break;
            }
            case 3:
            {
                cin.ignore();
                cout << "Goodbye!" << endl;
                choice = 3;
                break;
            }
            default:
            {
                cout << "Please enter a number between 1 and 3:" << endl;
                break;
            }
        }
	}
}

void employeeLoginOptions(Employees* e, Store* s, Customer* c, Employee* emp)
{
	int choice = 0;

    while(choice != 7)
    {
        cout<<"======Main Menu======"<<endl;
        cout<<"1. Add an item"<<endl;
        cout<<"2. Search for an item"<<endl;
        cout<<"3. View items expiring soon"<<endl;
        cout<<"4. View items that need to be restocked"<<endl;
        cout<<"5. Remove item"<<endl;
        cout<<"6. Log Out"<<endl;

       
        cin>>choice;
        
        switch(choice)
        {
            case 1:
            {
                cin.ignore();
                string name;
                cout << "Enter Product Name:" << endl;
                getline(cin, name);
                cin.ignore();

                string idString;
                cout<<"Enter Product ID#: "<<endl;
                getline(cin, idString);
                int iD = stoi(idString);
                cin.ignore();

                cout<<" Enter Quantity To Be Added: "<<endl;
                string quantityString;
                getline(cin, quantityString);
                int quantity = stoi(quantityString);
                cin.ignore();

                cout<<" Enter Expiration Date (YYYYMMDD): "<<endl;
                string expirationDate;
                getline(cin, expirationDate);
                int dateInt = stoi(expirationDate);
                cin.ignore();

                cout<<" Enter Expiration Date (MM/DD/YYYY): "<<endl;
                string expirationString;
                getline(cin, expirationString);
                cin.ignore();

                s->addStoreItem(name, iD, quantity, dateInt, expirationString);
                choice = 1;
                break;
            }
            case 2:
            {
                cin.ignore();
				string itemName;
				cout << "-Search Store-" << endl;
				cout << "Enter Product Name:" << endl;
				getline(cin, itemName);
                // cout << "TEST: " << itemName << endl;
				std::vector<storeItem*> temp = s->searchStore(itemName);
				s->printProductInfo(temp);

				choice = 2;
				break;
			}
            case 3:
            {
                queue<storeItem> expiringQueue;
                expiringQueue = s->expiringSoon();
                for(int i = 0; i < 50; i++)
                    {
                        s->printItemInformation(&expiringQueue.front());
                        expiringQueue.pop();
                    }
                
                break;
            }
            case 4:
            {
                queue<storeItem>restockQueue;
                restockQueue = s->restockQueue(10);

                for(int i=0; i<50; i++)
                {
                    cout<<restockQueue.front().itemName<<"--quantity in stock: "<<restockQueue.front().quantity<<endl;
                    restockQueue.pop();
                }

            }
            case 5:
            {
                cout<<"Enter name of item to delete: "<<endl;
                string name;
                cin.ignore();
                getline(cin, name);
                cin.ignore();
                cout<<"Enter quantity of "<<name<<" to delete: "<<endl;
                string quantString;
                getline(cin,quantString);
                cin.ignore();
                s->removeStoreItem(name, atoi(quantString.c_str()));
                break;
            }
            /*case 6:
            {
                //emp->viewResList(c);
                break;
            }*/
            case 6:
            {
                cout<<"Goodbye "<<e->userName<<endl;
                break;
            }
            default:
            {
                cout<<"Please enter a number between 1 and 4: "<<endl;
                break;
            }

        }
	}
}


void employeeOptions( Store* store, Employee* employee, Customer* customer)
{
	int choice = 0;

	while(choice != 2)
	{
		cout << "===============================" << endl;
		cout << "======= ZADISON SUPERMARKET =======" << endl;
		cout << "===============================" << endl;
		cout << "-- Welcome to Zadison Supermarket --" << endl;

        cout << "1. Sign In" << endl;
        //cout << "2. Sign Up" << endl;
        cout << "2. Quit" << endl;


        cin >> choice;

        switch(choice)
        {
            case 1:
            {
                cin.ignore();
                Employees* temp;
                temp = employee->login();
                employeeLoginOptions(temp, store, customer, employee);
                if(employeeLoginOptions == NULL)
                {
                    break;
                }
                choice = 1;
                break;
            }
            case 2:
            {
                cin.ignore();
                cout << "Goodbye!" << endl;
                choice = 3;
                break;
            }
            default:
            {
                cout << "Please enter a number between 1 and 3:" << endl;
                break;
            }
        }
	}
}