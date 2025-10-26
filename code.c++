#include <iostream>
#include<iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include<conio.h>

using namespace std;

class Order {
public:
    int userId;
    string name;
    string phoneNumber;
    string address;
    string email;
    int quantity;

    void displayOrderDetails() {
        cout << "Order Details:\n";
        cout << "User ID: " << userId << "\n";
        cout << "Name: " << name << "\n";
        cout << "Phone Number: " << phoneNumber << "\n";
        cout << "Address: " << address << "\n";
        cout << "Email: " << email << "\n";
    }
};

// functions for validation
bool isChar(char c) 
{ 

    return ((c >= 'a' && c <= 'z') 

            || (c >= 'A' && c <= 'Z')); 
} 


bool isDigit(string str) { 
	for (char ch: str) {
		int v = ch;
		if(!(ch >= 48 && ch <= 57)) { // ascii value converted
			return false;
		}
	}
	return true;
} 

bool is_valid(string email) 
{ 
    if (!isChar(email[0])) { 
        return 0; 
    } 
    int At = -1, Dot = -1;
    for (int i = 0; i < email.length(); i++) {
		if (email[i] == '@') { 
            At = i; 
        } 
        else if (email[i] == '.') { 
            Dot = i; 
        } 
    }   
    if (At == -1 || Dot == -1) 
        return 0; 
    if (At > Dot) 
        return 0; 
    return !(Dot >= (email.length() - 1)); 
}

bool isAlphaValue(string str) {
    for (int i = 0; i < str.length(); i++) {
        char a = str[i];
		if (!isalpha(a)) { 
            return false;
        }
    } 
    return true;
}

class Admin {
public:
// Function to add menu items
    void addItem() {
        string itemName;
        double itemPrice;
        int item_id;

        cout << "Enter Item Id : ";
        //cin>> item_id;
        string itemCode;
          while(true) {
		      cin >> itemCode; 
		     if(isDigit(itemCode)) {
			      item_id = stoi(itemCode);
			      break;
		        } else {
			 cout << "Invalid ID!\nPlease enter digits only (0-9),\ntry again.: ";
		     }
	        }

        cout << "Enter the name of the menu item: ";
        // cin.ignore();
        // getline(cin, itemName);
        while(true) {
            cin.ignore();
            getline(cin, itemName);
		
		if(isAlphaValue(itemName)) {
			  break;
		    } else {
			cout << "Invalid product name!\nPlease enter alphabets only (a-z or A-Z),\ntry again.: ";
		  }
	   }

        cout << "Enter the price of the menu item: ";
        cin >> itemPrice;

        // Append the new menu item to the menu file
        ofstream menuFile("menu.txt", ios::app);
        menuFile << item_id << " , " <<  itemName << " , " << itemPrice << "\n";
        menuFile.close();

        cout << "Menu item added successfully!\n";
    }
// Function to modify menu items
    void modifyItem() {
        int item_id;
        string itemName;
        double newPrice;

        cout << "Enter the name of the menu item to modify: ";
        cin.ignore();
        getline(cin, itemName);

        cout << "Enter the new price for the menu item: ";
        cin >> newPrice;

        // Modify the menu item in the menu file
        ifstream inputFile("menu.txt");
        ofstream tempFile("temp.txt");

        string line;
        while (getline(inputFile, line)) {
            size_t found = line.find(itemName);
            if (found != string::npos) {
                tempFile << itemName << "," << newPrice << "\n";
            } else {
                tempFile << line << "\n";
            }
        }

        inputFile.close();
        tempFile.close();

        remove("menu.txt");
        rename("temp.txt", "menu.txt");

        cout << "Menu item modified successfully!\n";
    }
// Function to delete menu items
    void deleteItem() {
        string itemName;

        cout << "Enter the name of the menu item to delete: ";
        cin.ignore();
        getline(cin, itemName);

        // Delete the menu item from the menu file
        ifstream inputFile("menu.txt");
        ofstream tempFile("temp.txt");

        string line;
        while (getline(inputFile, line)) {
            size_t found = line.find(itemName);
            if (found == string::npos) {
                tempFile << line << "\n";
            }
        }

        inputFile.close();
        tempFile.close();

        remove("menu.txt");
        rename("temp.txt", "menu.txt");

        cout << "Menu item deleted successfully!\n";
    }
// Function to view menu items 
  void viewItems() {
    // Display all menu items from the menu file
    ifstream menuFile("menu.txt");
    cout << "---------------------------------------------------------------\n";
    cout << "                  Displaying Menu Items\n";
    cout << "---------------------------------------------------------------\n";
    cout << setw(8) << "Item ID" << setw(20) << "Item Name" << setw(15) << "Item Price" << "\n";
    cout << "---------------------------------------------------------------\n";

    string line;
    while (getline(menuFile, line)) {
        stringstream iss(line);
        char comma;
        int item_id;
        string itemName;
        double itemPrice;

        // Assuming the format of each line is: item_id, item_name, item_price
        if (iss >> item_id >> comma >> itemName >> comma >> itemPrice) {
            cout << setw(8) << item_id << setw(20) << itemName << setw(15) << itemPrice << "\n";
        } else {
            cerr << "Error: Failed to extract item details from the menu line.\n";
            cerr << "Problematic Line: " << line << "\n";
        }
    }

    menuFile.close();
  }
// Function to add staff
   
//Function to view order details
void displayOrder() {
    int userId;
    cout << "Enter your user ID to display the order: ";
    cin >> userId;

    ifstream ordersFile("orders.txt");

    string line;
    bool orderFound = false;

    cout << "-------------------------------------------------------\n";
    cout << "          Displaying Order Details for User " << userId << "\n";
    cout << "-------------------------------------------------------\n";
    cout << setw(8) << "User ID" << setw(9) << "Item ID" << setw(12) << "Item Name" << setw(15) << "Item Price" << setw(10) << "Quantity" << "\n";
    cout << "-------------------------------------------------------\n";

    while (getline(ordersFile, line)) {
        stringstream iss(line);
        char comma;
        int extractedUserId;
        int extractedItemId;
        string itemName;
        double itemPrice;
        int quantity;

        // Extract the order details from the line
        if (iss >> extractedUserId >> comma >> extractedItemId >> comma >> itemName >> comma >> itemPrice >> comma >> quantity) {
            if (extractedUserId == userId) {
                orderFound = true;
                cout << setw(8) << extractedUserId << setw(9) << extractedItemId << setw(12) << itemName << setw(15) << itemPrice << setw(10) << quantity << "\n";
            }
        } else {
            cerr << "Error: Failed to extract order details from the order line.\n";
            cerr << "Problematic Line: " << line << "\n";
        }
    }

    ordersFile.close();

    if (!orderFound) {
        cout << "No orders found for User ID " << userId << "\n";
    }

    cout << "-------------------------------------------------------\n";
}

};

class User {
public:
// Function to view menu items
  void viewItems() {
    // Display all menu items from the menu file
    ifstream menuFile("menu.txt");

    cout << "---------------------------------------------------------------\n";
    cout << "                           Menu\n";
    cout << "---------------------------------------------------------------\n";
    cout << setw(8) << "Item ID" << setw(20) << "Item Name" << setw(15) << "Item Price" << "\n";
    cout << "---------------------------------------------------------------\n";

    string line;
    while (getline(menuFile, line)) {
        stringstream iss(line);
        char comma;
        int item_id;
        string itemName;
        double itemPrice;

        // Assuming the format of each line is: item_id, item_name, item_price
        if (iss >> item_id >> comma >> itemName >> comma >> itemPrice) {
            cout << setw(8) << item_id << setw(20) << itemName << setw(15) << itemPrice << "\n";
        } else {
            cerr << "Error: Failed to extract item details from the menu line.\n";
            cerr << "Problematic Line: " << line << "\n";
        }
    }

    menuFile.close();
}
// Function to place order
     void placeOrder() {
    viewItems();
    int item_id;
    cout << "Enter Item id  ";
    cin >> item_id;

    ifstream menuFile("menu.txt");
    ofstream ordersFile("orders.txt", ios::app);
    string line;
    bool itemFound = false;

    while (getline(menuFile, line)) {

        // Skip empty lines
        if (line.empty()) {
            continue;
        }

        stringstream iss(line);
        int menuItemId;
        string itemName;
        char comma;  // Assuming the format is "item_id, item_name, item_price"
        float itemPrice;

        // Print the line to understand what's being read
       //cout << "Debug: Reading line from menu file: " << line << endl;
      
        // Assuming the format of each line is: item_id, item_name, item_price
        if (iss >> menuItemId >> comma >> itemName >> comma >> itemPrice) {
            if (menuItemId == item_id) {
               // cout << "Debug: Read from line - Item ID: " << menuItemId << ", Item Name: " << itemName << ", Item Price: " << itemPrice << endl;
              //cout << "Item found and added to orders\n";
                
                Order order;
                cout << "Enter user ID: ";
                //cin >> order.userId;
                string userCode;
                while(true) {
		            cin >> userCode;
		            if(isDigit(userCode)) {
			        order.userId = stoi(userCode);
			       break;
		          } else {
        	     cout << "Invalid code!\nPlease enter digits only (0-9),\ntry again.: ";
		           }
	            }

                cout << "Enter Quantity :";
                cin >> order.quantity;
                // Item found, copy the line to orders file
                ordersFile << order.userId << " , " << line << " , "<< order.quantity <<"\n";
                cout << "Your order Item and Price is :\n";
                cout << "Item Name: " << itemName << "\n";
                cout << "Item Price: " << itemPrice << "\n";
                cout << "Quantity :" << order.quantity << endl;
                itemFound = true;
                break;
            }
        }
    }

    if (!itemFound) {
        cout << "Item not found in the menu\n";
    }

    menuFile.close();
    ordersFile.close();

    // Rest of the code for getting user details and saving the order...
    Order order;
    cout << "Enter name: ";
    // cin.ignore();
    // getline(cin, order.name);
     while(true) {
		cin.ignore();
        getline(cin, order.name);
		if(isAlphaValue(order.name)) {
			break;
		} else {
			cout << "Invalid product name!\nPlease enter alphabets only (a-z or A-Z),\ntry again.: ";
		}
	}

    cout << "Enter phone number: ";
    //getline(cin, order.phoneNumber);
    string num;
        while(true) {
		getline(cin, order.phoneNumber);
		if(isDigit(num)) {
		  order.phoneNumber = stoi(num);
		  break;
		} else {
        cout << "Invalid code!\nPlease enter digits only (0-9),\ntry again.: ";
		 }
	 }

    cout << "Enter address: ";
    //getline(cin, order.address);
     while(true) {
		getline(cin, order.address);
		if(isAlphaValue(order.address)) {
			break;
		} else {
			cout << "Invalid product name!\nPlease enter alphabets only (a-z or A-Z),\ntry again.: ";
		}
	}

    cout << "Enter email: ";
   // getline(cin, order.email);
   while(true) {
				cin>>order.email;
				if(is_valid(order.email)) {
					break;
				} else {
					cout << "Invalid email!\nPlease try again.: ";
				}
			}

    // Save user details to user_details.txt
    ofstream userDetailsFile("user_details.txt", ios::app);  // Declare and open userDetailsFile
    userDetailsFile << order.userId << "," << order.name << "," << order.phoneNumber << ","
                    << order.address << "," << order.email << "\n";

    userDetailsFile.close();

    cout << "Order placed successfully!\n";
}
// Function to display order
    void displayOrder() {
    int userId;
    cout << "Enter your user ID to display the order: ";
    cin >> userId;

    ifstream ordersFile("orders.txt");

    string line;
    bool orderFound = false;

    cout << "-------------------------------------------------------\n";
    cout << "          Displaying Order Details for User " << userId << "\n";
    cout << "-------------------------------------------------------\n";
    cout << setw(8) << "User ID" << setw(9) << "Item ID" << setw(12) << "Item Name" << setw(15) << "Item Price" << setw(10) << "Quantity" << "\n";
    cout << "-------------------------------------------------------\n";

    while (getline(ordersFile, line)) {
        stringstream iss(line);
        char comma;
        int extractedUserId;
        int extractedItemId;
        string itemName;
        double itemPrice;
        int quantity;

        // Extract the order details from the line
        if (iss >> extractedUserId >> comma >> extractedItemId >> comma >> itemName >> comma >> itemPrice >> comma >> quantity) {
            if (extractedUserId == userId) {
                orderFound = true;
                cout << setw(8) << extractedUserId << setw(9) << extractedItemId << setw(12) << itemName << setw(15) << itemPrice << setw(10) << quantity << "\n";
            }
        } else {
            cerr << "Error: Failed to extract order details from the order line.\n";
            cerr << "Problematic Line: " << line << "\n";
        }
    }

    ordersFile.close();

    if (!orderFound) {
        cout << "No orders found for User ID " << userId << "\n";
    }

    cout << "-------------------------------------------------------\n";
}
// Funvtion to update order
    void updateOrder() {
        int userId;
        cout << "Enter your user ID to update the order: ";
        cin >> userId;

        // Open the orders file for reading and writing
        ifstream ordersFile("orders.txt");
        ofstream tempFile("temp.txt");

        string line;
        bool orderFound = false;

        while (getline(ordersFile, line)) {
            stringstream iss(line);
            char comma;
            int extractedUserId;
            int extractedItemId;
            string itemName;
            double itemPrice;
            int quantity;

            // Extract the order details from the line
            if (iss >> extractedUserId >> comma >> extractedItemId >> comma >> itemName >> comma >> itemPrice >> comma >> quantity) {
                if (extractedUserId == userId) {
                    orderFound = true;

                    // Display the current order details
                    cout << "----------------Current Order Details--------------------\n";
                    cout << "Item ID: " << extractedItemId << "\n";
                    cout << "Item Name: " << itemName << "\n";
                    cout << "Item Price: " << itemPrice << "\n";
                    cout << "Quantity: " << quantity << "\n";
                    cout << "---------------Enter new Order Details-------------------\n";
                    // Allow the user to update specific information
                    cout << "Enter new Item ID: ";
                    cin >> extractedItemId;

                    cout << "Enter new Item Name: ";
                    cin.ignore();
                    getline(cin, itemName);

                    cout << "Enter new Item Price: ";
                    cin >> itemPrice;

                    cout << "Enter new Quantity: ";
                    cin >> quantity;

                    // Write the updated order details to the temp file
                    tempFile << userId << " , " << extractedItemId << " , " << itemName << " , " << itemPrice << " , " << quantity << "\n";
                    cout << "Order updated successfully!\n";
                } else {
                    // Copy the unchanged order details to the temp file
                    tempFile << extractedUserId << " , " << extractedItemId << " , " << itemName << " , " << itemPrice << " , " << quantity << "\n";
                }
            } else {
                cerr << "Error: Failed to extract order details from the order line.\n";
                cerr << "Problematic Line: " << line << "\n";
            }
        }

        ordersFile.close();
        tempFile.close();

        // Replace the original orders file with the temp file
        remove("orders.txt");
        rename("temp.txt", "orders.txt");

        if (!orderFound) {
            cout << "No orders found for User ID " << userId << "\n";
        }
    }
 // Function to cancel order
    void cancelOrder() {
        int userId;
        cout << "Enter your user ID to cancel the order: ";
        cin >> userId;

        // Remove the order details from the orders file for the given user ID
        ifstream inputFile("orders.txt");
        ofstream tempFile("temp.txt");

        string line;
        while (getline(inputFile, line)) {
            size_t found = line.find(to_string(userId));
            if (found == string::npos) {
                tempFile << line << "\n";
            }
        }

        inputFile.close();
        tempFile.close();

        remove("orders.txt");
        rename("temp.txt", "orders.txt");
        cout<<"\n-------------------------------------------------------\n";
        cout << "                Order Canceled :( \n";
        cout<<"\n-------------------------------------------------------\n";

    }
//Function to display bill
void calculateAndDisplayBill() {
    int userId;
    cout << "Enter your user ID to calculate the bill: ";
    cin >> userId;

    // Calculate the bill based on the order details from the orders file for the given user ID
    ifstream ordersFile("orders.txt");

    string line;
    double totalBill = 0;
    while (getline(ordersFile, line)) {
        stringstream iss(line);
        char comma;
        int extractedUserId;
        int extracteditem_id;
        string itemName;
        double itemPrice;
        int quantity;

        // Extract the user ID, item details, and quantity from the line
        if (iss >> extractedUserId >> comma >> extracteditem_id >> comma >> itemName >> comma >> itemPrice >> comma >> quantity) {
            // Calculate the item total and add it to the overall total
            double itemTotal = itemPrice * quantity;
            totalBill += itemTotal;
             cout<<"-------------------------------------------------------\n";
             cout << "                    BILL:                            \n";
             cout<<"-------------------------------------------------------\n";
            // Display details for the user
            cout << "Item Name: " << itemName << "\n";
            cout << "Item Price: rs" << itemPrice << "\n";
            cout << "Quantity: " << quantity << "\n";
            //cout << "Total: rs" << itemTotal << "\n";
        } else {
            cerr << "Error: Failed to extract item details from the order line.\n";
            cerr << "Problematic Line: " << line << "\n";
        }
    }

    ordersFile.close();

    cout << "Total Bill: rs" << totalBill << "\n";
    cout<<"-------------------------------------------------------\n";

}

};

int main() {
    int choice;
    Admin admin;
    User user;
    char c;

    while (true) {
        cout<<"\n";
        cout<<"******************************************************\n";
        cout<<"----- Welcome to Mother Diary Management System -----\n";
        cout<<"******************************************************\n";
        cout << "|                                                    |\n";
        cout << "|              1) Login as Admin                     |\n";
        cout << "|              2) Login as User                      |\n";
        cout << "|              3) Exit                               |\n";
        cout << "|                                                    |\n";
        cout<<"******************************************************\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                // Admin login logic
                string adminUsername = "admin";
                string adminPassword = "admin123";
                string enteredUsername, enteredPassword;
                cout<<"-------------------- ADMIN LOGIN -------------------\n";
                cout << "Enter admin username: ";
                cin >> enteredUsername;

                cout << "Enter admin password: ";
                //cin >> enteredPassword;
                while(c!=13){
                    c=getch();
                    if(c!=13){
                        enteredPassword += c;
                        cout<<"*";
                    }
                }

                if (enteredUsername == adminUsername && enteredPassword == adminPassword) {
                    while (true) {
                        cout<<"\n\n******************************************************\n";
                        cout <<"|                 Admin Menu                          |\n";
                        cout <<"|             1) Add Items                            |\n";
                        cout <<"|             2) Modify Items                         |\n";
                        cout <<"|             3) Delete Items                         |\n";
                        cout <<"|             4) View Items                           |\n";
                        cout <<"|             5) View order details                   |\n";
                        cout <<"|             6) Logout                               |\n";                        
                        cout<<"******************************************************\n";
                        cout << "Enter your choice: ";
                        cin >> choice;

                        switch (choice) {
                            case 1:
                                admin.addItem();
                                break;
                            case 2:
                                admin.modifyItem();
                                break;
                            case 3:
                                admin.deleteItem();
                                break;
                            case 4:
                                admin.viewItems();
                                break;
                            case 5:
                                admin.displayOrder();
                                break;
                            case 6:
                                cout<<"------------------------------------------------------\n";
                                cout << "               Admin logged out.......\n";
                                cout<<"------------------------------------------------------\n";
                                break;
                            default:
                                cout << "Invalid choice. Please try again.\n";
                        }

                        if (choice == 6) {
                            break;
                        }
                    }
                } else {
                    cout << "Invalid admin credentials. Please try again.\n";
                }

                break;
            }
            case 2: {
                // User login logic
                while (true) {
                    cout<<"\n\n********************************************************\n";
                    cout <<"|                 User Menu                               |\n";
                    cout <<"|             1) View Items                               |\n";
                    cout <<"|             2) Place Order                              |\n";
                    cout <<"|             3) Display Order                            |\n";
                    cout <<"|             4) Update Order                             |\n";
                    cout <<"|             5) Cancel Order                             |\n";
                    cout <<"|             6) Calculate and Display Bill               |\n";
                    cout <<"|             7) Logout                                   |\n";                        
                    cout<<"**********************************************************\n";
                    cout << "Enter your choice: ";
                    cin >> choice;

                    switch (choice) {
                        case 1:
                            user.viewItems();
                            break;
                        case 2:
                            user.placeOrder();
                            break;
                        case 3:
                            user.displayOrder();
                            break;
                        case 4:
                            user.updateOrder();
                            break;
                        case 5:
                            user.cancelOrder();
                            break;
                        case 6:
                            user.calculateAndDisplayBill();
                            break;
                        case 7:
                            cout<<"------------------------------------------------------\n";
                            cout << "               User logged out......\n";
                            cout<<"------------------------------------------------------\n";
                            break;
                        default:
                            cout << "Invalid choice. Please try again.\n";
                    }

                    if (choice == 7) {
                        break;
                    }
                }
                break;
            }
            case 3:
                cout <<"-----------------------------------------\n";
                cout <<"         Exiting the program........      \n";
                cout <<"             Goodbyee......               \n";
                cout <<"-----------------------------------------\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}