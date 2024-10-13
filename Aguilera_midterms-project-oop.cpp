#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include <vector>  

using namespace std;

string toLowerCase(const string& str) {
    string lowerStr = "";
    for (int i = 0; i < str.length(); ++i) {
        char c = str[i];
        lowerStr += (c >= 'A' && c <= 'Z') ? c + 32 : c; 
    }
    return lowerStr;
}

bool isValidCategory(const string& category) {
    string lowerCategory = toLowerCase(category);
    return (lowerCategory == "clothing" || lowerCategory == "electronics" || lowerCategory == "entertainment");
}

bool isValidField(const string& field) {
    string lowerField = toLowerCase(field);
    return (lowerField == "quantity" || lowerField == "price");
}

bool isValidOrder(const string& order) {
    string lowerOrder = toLowerCase(order);
    return (lowerOrder == "ascending" || lowerOrder == "descending");
}

string capitalizeFirstLetter(const string& str) {
    if (str.empty()) return str;
    string capitalizedStr = str;
    capitalizedStr[0] = toupper(capitalizedStr[0]);
    for (size_t i = 1; i < capitalizedStr.length(); ++i) {
        capitalizedStr[i] = tolower(capitalizedStr[i]);
    }
    return capitalizedStr;
}

int inputInteger(const string& prompt) {
    int value;
    cout << prompt;
    while (!(cin >> value) || value < 1) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input! Please enter a valid number: ";
    }
    return value;
}

double inputDouble(const string& prompt) {
    double value;
    cout << prompt;
    while (!(cin >> value) || value < 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input! Please enter a valid positive number: ";
    }
    return value;
}

class Item {
private:
    string id;
    string name;
    int quantity;
    double price;
    string category;

public:
    Item(string id = "", string name = "", int quantity = 0, double price = 0.0, string category = "")
        : id(id), name(name), quantity(quantity), price(price), category(category) {}

    string getId() const { return id; }
    string getName() const { return name; }
    int getQuantity() const { return quantity; }
    double getPrice() const { return price; }
    string getCategory() const { return category; }

    void setQuantity(int newQuantity) { quantity = newQuantity; }
    void setPrice(double newPrice) { price = newPrice; }

    void display() const {
        cout << setw(20) << left << capitalizeFirstLetter(id) 
             << setw(20) << left << capitalizeFirstLetter(name) 
             << setw(20) << left << quantity
             << setw(20) << left << price 
             << setw(20) << left << capitalizeFirstLetter(category)  << endl;
    }
    
    void displayItemsByCategoryAndSortItems() const {
        cout << setw(20) << left << capitalizeFirstLetter(id) 
             << setw(20) << left << capitalizeFirstLetter(name) 
             << setw(20) << left << quantity
             << setw(20) << left << price << endl;
    }
};

class InventoryBase {
public:
    virtual void addItem(const Item& item) = 0;
    virtual void updateItem(const string& id, const string& field, double newValue) = 0;
    virtual void removeItem(const string& id) = 0;
    virtual void displayItemsByCategory(const string& category) = 0;
    virtual void displayAllItems() = 0;
    virtual void searchItem(const string& id) = 0;
    virtual void sortItems(const string& sortBy, const string& order) = 0;
    virtual void displayLowStockItems() = 0;
};

class Inventory : public InventoryBase {
private:
    vector<Item> items;  // Replace array with vector


     
    void bubbleSort(const string& sortBy, const string& order) {
    	int itemCount = items.size();
        for (int i = 0; i < itemCount - 1; i++) {
            for (int j = 0; j < itemCount - i - 1; j++) {
                bool condition;
                if (sortBy == "quantity") {
                    condition = (order == "ascending") ? items[j].getQuantity() > items[j + 1].getQuantity()
                                                       : items[j].getQuantity() < items[j + 1].getQuantity();
                } else if (sortBy == "price") { 
                    condition = (order == "ascending") ? items[j].getPrice() > items[j + 1].getPrice()
                                                       : items[j].getPrice() < items[j + 1].getPrice();
                } // using ternary functions for a concise way to express conditional expressions
                if (condition) {
                    Item temp = items[j];
                    items[j] = items[j + 1];
                    items[j + 1] = temp;
                }
            }
        }
    }
    

public:
	
     	~Inventory() = default;

    void addItem(const Item& item) override {
        items.push_back(item);  
        cout << "Item added successfully!" << endl;
    }

    int findItemById(const string& id) {
        for (int i = 0; i < items.size(); i++) {
            if (toLowerCase(items[i].getId()) == toLowerCase(id)) {
                return i; 
            }
        }
        return -1; 
    }

	void updateItem(const string& id, const string& field, double newValue) override {
   		 int index = findItemById(id);

    	if (index == -1) {
        	cout << "Item not found!" << endl;
        	return;
   	 	}	
   	 	
    	if (toLowerCase(field) == "quantity") {
       		int oldQuantity = items[index].getQuantity();
        	items[index].setQuantity(newValue);
        	cout << "Quantity of Item " << items[index].getName() << " updated from " << oldQuantity << " to " << items[index].getQuantity() << endl;
   		} else if (toLowerCase(field) == "price") {
        	double oldPrice = items[index].getPrice();
       		items[index].setPrice(newValue);
        	cout << "Price of Item " << items[index].getName() << " updated from " << oldPrice << " to " << items[index].getPrice() << endl;
   		 }
	}

    void removeItem(const string& id) override {
    	if (items.empty()) {
            cout << "There are no items to remove in the inventory!" << endl;
            return;
        }
        int index = findItemById(id);
        if (index != -1) {
            cout << "Item " << items[index].getName() << " has been removed from the inventory." << endl;
            items.erase(items.begin() + index);  // Use vector erase
        } else {
            cout << "Item not found!" << endl;
        }
    }

    void displayItemsByCategory(const string& category) override {
    	if (items.empty()) {
            cout << "There are no items to display in the inventory!" << endl;
            return;
        }
        bool found = false;
        for (int i = 0; i < items.size(); i++) {
            if (toLowerCase(items[i].getCategory()) == toLowerCase(category)) {
            	
            	if (found == false) {
                
                cout << setw(20) << left << "ID" << setw(20) << left << "Name" 
                     << setw(20) << left << "Quantity" << setw(20) << left << "Price" << endl;
            	}
            	
                found = true;
          		items[i].displayItemsByCategoryAndSortItems();
            }
        }
        if (found == false) {
            cout << "No items found in this category." << endl;
        }
    }

    void displayAllItems() override {
        if (items.empty()) {
            cout << "There are no items to display in the inventory!" << endl;
            return;
        }
        cout << setw(20) << left << "ID" << setw(20) << left << "Name" << setw(20) << left << "Quantity" << setw(20) << left << "Price" << setw(20) << left << "Category" << endl;
        for (int i = 0; i < items.size(); i++) {
          items[i].display();
        }
    }

    void searchItem(const string& id) override {
		bool found = false;
    
    for (int i = 0; i < items.size(); i++) {
        if (toLowerCase(items[i].getId()) == toLowerCase(id)) {
            if (found == false) {
                
                cout << setw(20) << left << "ID" << setw(20) << left << "Name" 
                     << setw(20) << left << "Quantity" << setw(20) << left << "Price" 
                     << setw(20) << left << "Category" << endl;
            }
            found = true;
            items[i].display();
            break; 
        }
    }

    		if (found == false) {
      		  cout << "Item not found!" << endl;
    	}
	}

    void sortItems(const string& sortBy, const string& order) override {
    	
    	if (items.empty()) {
                cout << "There are no items to sort in the inventory!" << endl;
                return;
            }
        bubbleSort(sortBy, order);
        
       		 cout << setw(20) << left << "ID" << setw(20) << left << "Name" << setw(20) << left << "Quantity" << setw(20) << left << "Price" << endl;
       		 
  		for (int i = 0; i < items.size(); i++) {
        	items[i].displayItemsByCategoryAndSortItems();
   		 }
    }

    void displayLowStockItems() override {
        bool found = false;
          for (int i = 0; i < items.size(); i++) {
          	if (items[i].getQuantity() <= 5) {
            	if (found == false) {
                
                cout << setw(20) << left << "ID" << setw(20) << left << "Name" 
                     << setw(20) << left << "Quantity" << setw(20) << left << "Price" << endl;
            	}
            	found = true;
				items[i].display();
        }
    }
    if (found == false) {
        cout << "No items with low stock found." << endl;
    }
}
    
    bool isEmpty() const {
        return items.empty();
    }
};


int main() {
    Inventory i1;
    string id, name, category, sortBy, order, field;
    int quantity, choice;
    double price, newValue;

    do {
    	system ("cls");
        cout << "\nMenu:\n"
             << "1 - Add Item\n"
             << "2 - Update Item\n"
             << "3 - Remove Item\n"
             << "4 - Display Items by Category\n"
             << "5 - Display All Items\n"
             << "6 - Search Item\n"
             << "7 - Sort Items\n"
             << "8 - Display Low Stock Items\n"
             << "9 - Exit\n";
        choice = inputInteger("Enter your choice: ");

        switch (choice) {
        case 1: {
        	
        	 do {
                cout << "Enter Category (clothing/electronics/entertainment): ";
                cin >> category;

                if (isValidCategory(category) == false) {
                    cout << "Category " << category << " does not exist!" << endl;
                }
            } while (isValidCategory(category) == false);
            
            cout << "Enter Item ID: ";
            cin >> id;
            cout << "Enter Item Name: ";
            cin >> name;

            quantity = inputInteger("Enter Quantity: ");
            price = inputDouble("Enter Price: ");

            Item newItem(id, name, quantity, price, category);
            i1.addItem(newItem);
            break;
        }

        case 2: {
        	
        	if (i1.isEmpty()) {
                cout << "There are no items to update in the inventory!" << endl;
                break;
            }
            
            cout << "Enter Item ID to update: ";
            cin >> id;
            
                int index = i1.findItemById(id);  

   			 if (index == -1) {
     	   		cout << "Item not found!" << endl;
        		break;  
   			 }
   			 
            do {
                cout << "Enter Field to update (quantity/price): ";
                cin >> field;
                if (isValidField(field) == false) {
                    cout << "Invalid input! Please enter 'quantity' or 'price'." << endl;
                }
            } while (isValidField(field) == false);

            if (toLowerCase(field) == "quantity") {
                newValue = inputInteger("Enter new quantity: ");
            } else {
                newValue = inputDouble("Enter new price: ");
            }

            i1.updateItem(id, field, newValue);
            break;
        }

        case 3: {
        	if (i1.isEmpty()) {
                cout << "There are no items to remove in the inventory!" << endl;
                break;
            }
            
            cout << "Enter Item ID to remove: ";
            cin >> id;
            i1.removeItem(id);
            break;
        }

        case 4: {
        	if (i1.isEmpty()) {
                cout << "There are no items to display in the inventory!" << endl;
                break;
            }
            
            do {
                cout << "Enter Category (clothing/electronics/entertainment): ";
                cin >> category;

                if (isValidCategory(category) == false) {
                    cout << "Category " << category << " does not exist!" << endl;
                }
            } while (isValidCategory(category) == false);

            i1.displayItemsByCategory(category);
            break;
        }

        case 5: {
            i1.displayAllItems();
            break;
        }
        
        case 6: {
        
        if (i1.isEmpty()) {
                cout << "There are no items to search in the inventory!" << endl;
                break;
            }
            
            cout << "Enter Item ID to search: ";
            cin >> id;
            i1.searchItem(id);
            break;
        }

        case 7: {
        	
        	if (i1.isEmpty()) {
                cout << "There are no items to sort in the inventory!" << endl;
                break;
            }

            do {
                cout << "Sort by (quantity/price): ";
                cin >> sortBy;
                if (isValidField(sortBy) == false) {
                    cout << "Invalid input! Please enter 'quantity' or 'price'." << endl;
                }
            } while (isValidField(sortBy) == false);

            do {
                cout << "Order (ascending/descending): ";
                cin >> order;
                if (isValidOrder(order) == false) {
                    cout << "Invalid input! Please enter 'ascending' or 'descending'." << endl;
                }
            } while (isValidOrder(order) == false);

            i1.sortItems(sortBy, order);
            break;
        }

        case 8: {
            i1.displayLowStockItems();
            break;
        }

        case 9:
            cout << "Exiting Inventory Management System.." << endl;
            break;

        default:
            cout << "Invalid choice! Please try again." << endl;
            break;
        }
		
		cout << endl;
		system ("pause");
    } while (choice != 9);

    return 0;
}
