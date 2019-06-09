class EmployeeStore
{
public:
    void addStoreItem(string name, int itemID, int quantity);
    void removeStoreItem(string name, int itemID, int quantity);
    void showRestockItems();
    void restockItem(int itemID, int quantity);
}