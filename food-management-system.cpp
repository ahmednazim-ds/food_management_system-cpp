#include<iostream>
#include<cstring>
#include<fstream>

using namespace std;

#define MAX_USERS 50
#define MAX_ITEMS 100
#define MAX_RECIPES 100
#define MAX_SALES 500
#define MAX_REQUESTS 100

struct User
{
    string username;
    string password;
    string role;
};

struct Item
{
    string id;
    string name;
    double price;
    int stock;
    string category;
};

struct Recipe
{
    string id;
    string name;
    string ingredients;
    string steps;
};

struct Sale
{
    string itemName;
    int quantity;
    double amount;
};

struct Request
{
    string id;
    string name;
    string category;
    double price;
    int quantity;
};

User users[MAX_USERS];
int userCount = 0;

Item menu[MAX_ITEMS];
int menuCount = 0;

Recipe recipes[MAX_RECIPES];
int recipeCount = 0;

Sale sales[MAX_SALES];
int saleCount = 0;

Request requests[MAX_REQUESTS];
int requestCount = 0;


void loadUsers()
{
    ifstream in("credentials.txt");

    userCount = 0;

    while (in >> users[userCount].username >> users[userCount].password >> users[userCount].role)
    {
        userCount++;
    }
    in.close();
}

void saveUsers()
{
    ofstream out("credentials.txt");

    for (int i = 0; i < userCount; i++)
        out << users[i].username << " " << users[i].password << " " << users[i].role << "\n";

    out.close();
}

void loadMenu()
{
    ifstream in("menu.txt");
    menuCount = 0;

    while (in >> menu[menuCount].id >> menu[menuCount].name >> menu[menuCount].price >> menu[menuCount].stock >> menu[menuCount].category)
    {
        menuCount++;  // BUG FIX: was never incrementing menuCount
    }
    in.close();
}

void saveMenu()
{
    ofstream out("menu.txt");

    for (int i = 0; i < menuCount; i++)
    {
        // BUG FIX: added newline between records and corrected field order to match loadMenu
        out << menu[i].id << " " << menu[i].name << " " << menu[i].price << " " << menu[i].stock << " " << menu[i].category << "\n";
    }

    out.close();
}

void loadRequests()
{
    ifstream in("request.txt");
    requestCount = 0;

    while (in >> requests[requestCount].id >> requests[requestCount].name >> requests[requestCount].category >> requests[requestCount].price >> requests[requestCount].quantity)
    {
        requestCount++;
    }
    in.close();
}

void saveRequests()
{
    ofstream out("request.txt");

    for (int i = 0; i < requestCount; i++)  // BUG FIX: was using requestCount instead of i
    {
        out << requests[i].id << "\n"
            << requests[i].name << "\n"
            << requests[i].category << "\n"
            << requests[i].price << "\n"
            << requests[i].quantity << "\n";
    }
    out.close();
}

void loadSales()
{
    ifstream in("sales.txt");
    saleCount = 0;

    while (in >> sales[saleCount].itemName >> sales[saleCount].quantity >> sales[saleCount].amount)
    {
        saleCount++;  // BUG FIX: was never incrementing saleCount
    }

    in.close();
}

void saveSales()
{
    ofstream out("sales.txt");

    for (int i = 0; i < saleCount; i++)  // BUG FIX: was using saleCount instead of i
    {
        out << sales[i].itemName << "\n"
            << sales[i].quantity << "\n"
            << sales[i].amount << "\n";
    }

    out.close();
}

void Admin_Menu()
{
    int choice;

    do
    {
        cout << "\n--- Admin Menu ---\n";
        cout << "1. Add Employee\n2. Remove Employee\n3. View Employees\n0. Logout\nChoice: ";
        cin >> choice;

        if (choice == 1)
        {
            cout << "Enter Username: ";
            cin >> users[userCount].username;

            cout << "Enter Password: ";
            cin >> users[userCount].password;

            cout << "Enter role: ";
            cin >> users[userCount].role;

            userCount++;  // BUG FIX: was never incrementing userCount after adding
            saveUsers();
        }
        else if (choice == 2)
        {
            string Uname;

            cout << "Enter username to remove: ";
            cin >> Uname;

            for (int i = 0; i < userCount; i++)
            {
                if (Uname == users[i].username)  // BUG FIX: was comparing against users[userCount] instead of users[i]
                {
                    for (int j = i; j < userCount - 1; j++)  // BUG FIX: was incrementing i instead of j, and starting from 0 instead of i
                        users[j] = users[j + 1];

                    userCount--;
                    saveUsers();
                    break;
                }
            }
        }
        else if (choice == 3)
        {
            for (int i = 0; i < userCount; i++)
            {
                cout << users[i].username << " " << users[i].role << "\n";
            }
        }
    } while (choice != 0);

}

void Manager_Menu()
{
    int choice;

    do
    {
        cout << "\n--- Manager Menu ---\n";
        cout << "1. Add Menu Item Request\n2. Increase Stock\n0. Logout\nChoice: ";
        cin >> choice;

        if (choice == 1)
        {
            cout << "Enter Item id: ";
            cin >> requests[requestCount].id;
            cin.ignore();

            cout << "Enter Item name: ";
            cin >> requests[requestCount].name;

            cout << "Enter Item Category: ";
            cin >> requests[requestCount].category;

            cout << "Enter quantity of Item: ";
            cin >> requests[requestCount].quantity;

            cout << "Enter Item price: ";
            cin >> requests[requestCount].price;

            requestCount++;
            saveRequests();
        }
        else if (choice == 2)
        {
            int qty;
            string id;

            cout << "Enter Item id: ";
            cin >> id;

            cout << "Enter quantity to add: ";
            cin >> qty;

            for (int i = 0; i < menuCount; i++)  // BUG FIX: was looping over requestCount instead of menuCount
            {
                if (id == menu[i].id)
                {
                    menu[i].stock += qty;
                    saveMenu();
                    break;
                }
            }
        }

    } while (choice != 0);
}

void Chef_Menu()
{
    int choice;

    do
    {
        cout << "\n--- Chef Menu ---\n";
        cout << "1. View Requests\n2. Add Recipe\n0. Logout\nChoice: ";
        cin >> choice;

        if (choice == 1)
        {
            for (int i = 0; i < requestCount; i++)
            {
                cout << requests[i].id << " " << requests[i].name << "\n";
            }
        }
        else if (choice == 2)
        {
            string id;

            cout << "Enter request id: ";
            cin >> id;

            for (int i = 0; i < requestCount; i++)
            {
                if (requests[i].id == id)
                {
                    menu[menuCount].id = requests[i].id;
                    menu[menuCount].name = requests[i].name;
                    menu[menuCount].category = requests[i].category;
                    menu[menuCount].price = requests[i].price;
                    menu[menuCount].stock = requests[i].quantity;

                    menuCount++;
                    saveMenu();

                    for (int j = i; j < requestCount - 1; j++)  // BUG FIX: used j instead of i to avoid shadowing, start from i not 0, and bound is requestCount-1 to avoid out-of-bounds
                        requests[j] = requests[j + 1];

                    requestCount--;
                    saveRequests();

                    break;
                }
            }
        }

    } while (choice != 0);
}

void Sales_Menu()
{
    int choice;

    do
    {
        cout << "\n--- Sales Menu ---\n";
        cout << "1. Take Order\n0. Logout\nChoice: ";
        cin >> choice;

        if (choice == 1)
        {
            string id;
            int qty;

            cout << "Enter Id: ";
            cin >> id;

            cout << "Enter quantity: ";
            cin >> qty;

            for (int i = 0; i < menuCount; i++)
            {
                if (id == menu[i].id && qty <= menu[i].stock)
                {
                    menu[i].stock -= qty;
                    sales[saleCount].itemName = menu[i].name;    // BUG FIX: was using menu[menuCount] instead of menu[i]
                    sales[saleCount].quantity = qty;
                    sales[saleCount].amount = qty * menu[i].price;  // BUG FIX: same

                    saleCount++;
                    saveSales();
                    saveMenu();

                    cout << "Order Placed\n";
                    break;
                }
            }
        }

    } while (choice != 0);
}

void Login()
{
    string uname, pass;

    cout << "Enter Username: ";
    cin >> uname;

    cout << "Enter Password: ";
    cin >> pass;

    for (int i = 0; i < userCount; i++)
    {
        if (users[i].username == uname && users[i].password == pass)
        {
            if (users[i].role == "Admin") Admin_Menu();
            if (users[i].role == "Manager") Manager_Menu();
            if (users[i].role == "Chef") Chef_Menu();
            if (users[i].role == "Sales") Sales_Menu();
            return;
        }
    }
    cout << "Invalid Credentials!\n";
}

int main()
{
    loadUsers();
    loadMenu();
    loadRequests();
    loadSales();

    int choice;

    do
    {
        cout << "--- Food Management System ---\n";
        cout << "1. Login \n0. Exit \n\nChoice: ";
        cin >> choice;

        if (choice == 1)
        {
            Login();
        }

    } while (choice != 0);

    return 0;
}