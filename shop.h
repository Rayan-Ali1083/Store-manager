#ifndef SHOP_H
#define SHOP_H

#include <iostream>
#include <string>
#include "file.h"

using namespace std;

item product;
cashier cash;
customer cus;
manager man;

file d;

class shop : public data
{
protected:
    char name[100];
    char address[200];
    char email[50];

public:
    shop()
    {
        for (int i = 0; i < 100; i++)
        {
            name[i] = ' ';
        }
        for (int i = 0; i < 50; i++)
            email[i] = ' ';
        for (int i = 0; i < 200; i++)
            address[i] = ' ';
    }
    void setname(char x[100]) { strcpy(name, x); }										//setters
    void setaddress(char x[200]) { strcpy(address, x); }
    void setemail(char x[50]) { strcpy(email, x); }

    string getname() { return name; }													//getters
    string getaddress() { return address; }
    string getemail() { return email; }

    void input();
    void changeinfo();
    void viewinfo();

    void login_ui();

    void manager_ui();
    void product_detail_ui();
    void cashier_detail_ui();
    void shop_detail_ui();
    void manager_account_detail_ui();
    void view_cashier_ui();
    void view_item_ui();
    void view_order_ui();

    void cashier_ui();
    void cashier_account_detail_ui();
    void customer_ui();
    bool customer_registered_ui();
    void items_ui();

    void filing_shop_information()														//filing for shop
    {
        ofstream fout;
        fout.open("Shop Information.dat", ios::app);
        if (!fout.is_open())
        {
            cout << "Shop Information.dat File cannot be opened";
            exit(1);
        }

        input();
        fout.write((char *)this, sizeof(*this));
        fout.close();
    }

    void filing_view_shop_information()													//view shop details from file
    {
        ifstream inf;
        inf.open("Shop Information.dat");
        if (!inf.is_open())
        {
            cout << "Shop Information.dat File cannot be opened";
            exit(1);
        }

        inf.read((char *)this, sizeof(*this));
        viewinfo();
        inf.close();
        return;
    }

    void filing_change_information()													//changing info from saved file
    {
        fstream f;
        f.open("Shop Information.dat", ios::app | ios::in | ios::out);
        if (!f.is_open())
        {
            cout << "Shop Information.dat File cannot be opened";
            exit(1);
        }
        f.read((char *)this, sizeof(*this));
        changeinfo();
        f.write((char *)this, sizeof(*this));
        f.close();
        return;
    }
};

void shop::input()
{
    fflush(stdin);
    cout << "Enter the Shop name: ";
    gets(name);
    cout << "Enter the address: ";
    gets(address);
    fflush(stdin);
    cin.ignore();
    cout << "Enter the email address: ";
    gets(email);
    cout << endl;
}

void shop::viewinfo()
{
    cout << "Shop: " << name << endl;
    cout << "Address: " << address << endl;
    cout << "Email address: " << email << endl;
}

void shop::changeinfo()
{
    bool condition = true;
    while (condition)
    {
        int op;
        fflush(stdin);
        cout << "Enter number to change information" << endl;
        cout << "\n\t1) Shop Name\n\t2) Address\n\t3) Email Address\n\t4) Exit\n";
        cout << "Option: ";
        cin >> op;
        fflush(stdin);
        switch (op)
        {
        case 1:
            system("CLS");
            cout << "Enter the new Shop name: ";
            gets(name);
            break;
        case 2:
            system("CLS");
            cout << "Enter the new address: ";
            gets(address);
            break;
        case 3:
            system("CLS");
            cout << "Enter the new email address: ";
            gets(email);
            break;
        case 4:
            system("CLS");
            condition = false;
            break;
        default:
            system("CLS");
            cout << "Wrong option entered";
        }
    }
}

void shop::login_ui()
{
    char user[100];
    char pass[100];
    while (1)
    {
        system("CLS");
        fflush(stdin);
        d.getall();
        cout << "Login Menu\n";
        cout << "\n\tUser Name: ";
        gets(user);
        cout << "\n\tPassword: ";
        gets(pass);

        bool success = man.login(user, pass);

        if (!success)
        {
            success = cash.login(user, pass);
            if (success)
            {
                system("CLS");
                cashier_ui();
            }
        }
        else
        {
            system("CLS");
            manager_ui();
        }

        if (!success)
        {
            system("CLS");
            cout << "Wrong password or username\n";
            d.store_all();
            getch();
        }
    }
}

void shop::manager_ui()
{
    bool condition = true;
    while (condition)
    {
        system("CLS");
        cout << "Main Menu\n";
        cout << "\n\t1) Product Details\n\t2) Cashier Detail\n\t3) Shop Details\n\t4) Account Detail\n\t5) logout\n";
        int op;
        cout << "Option: ";
        cin >> op;
        switch (op)
        {
        case 1:
            system("CLS");
            product_detail_ui();
            break;
        case 2:
            system("CLS");
            cashier_detail_ui();
            break;
        case 3:
            system("CLS");
            shop_detail_ui();
            break;
        case 4:
            system("CLS");
            manager_account_detail_ui();
            break;
        case 5:
            system("CLS");
            Manager.logout();
            condition = false;
            break;
        default:
            system("CLS");
            cout << "Wrong Option entered";
            getch();
        }
    }
}

void shop::product_detail_ui()
{
    bool condition = true;
    while (condition)
    {
        system("CLS");
        cout << "Product Detail Menu\n";
        cout << "\t1) Add product\n\t2) View Items\n\t3) View Order's \n\t4) Exit\n";
        int op;
        cout << "Option: ";
        cin >> op;
        item tmp;
        switch (op)
        {
        case 1:
            system("CLS");
            tmp.input();
            all_item.push_back(tmp);
            break;
        case 2:
            system("CLS");
            view_item_ui();
            break;
        case 3:
            system("CLS");
            view_order_ui();
            break;
        case 4:
            system("CLS");
            condition = false;
            break;
        default:
            system("CLS");
            cout << "Wrong Option entered";
            getch();
        }
    }
}

void shop::view_item_ui()
{
    bool condition = true;
    while (condition)
    {
        int j = 0, op;
        system("CLS");
        cout << "Items Menu\n\n";

        for (int i = 0; i < all_item.size(); i++)
        {
            cout << i + 1 << ") " << all_item[i].getname() << endl;
            j = i;
            j += 2;
        }
        if (j == 0)
        {
            cout << "No items available";
            getch();
            break;
        }
        cout << j << ") Exit\n\n";
        cout << "Option: ";
        cin >> op;
        if (op == j)
        {
            condition = false;
        }
        else
        {
            op--;
            while (1)
            {
                system("CLS");
                cout << "Items Detail\n\n";
                all_item[op].viewinfo();
                cout << "\n\nPress C to change Info OR Press R to delete OR Press any key to return";
                char ch = getch();

                if (tolower(ch) == 'c')
                {
                    system("CLS");
                    all_item[op].changeinfo();
                }
                else if (tolower(ch) == 'r')
                {
                    system("CLS");
                    all_item.erase(all_item.begin() + op);
                    break;
                }
                else
                {
                    break;
                }
            }
        }
    }
}

void shop::view_order_ui()
{
    bool condition = true;
    while (condition)
    {
        system("CLS");
        cout << "Order's Menu\n\n";
        int j = 0, op;
        for (int i = 0; i < all_order.size(); i++)
        {
            cout << i + 1 << ") " << all_order[i].name << endl;
            j = i;
            j += 2;
        }
        if (j == 0)
        {
            cout << "No Order's available";
            getch();
            break;
        }
        cout << j << ") Exit\n\n";
        cout << "Option: ";
        cin >> op;
        if (op == j)
        {
            condition = false;
        }
        else
        {
            op--;
            while (1)
            {
                system("CLS");
                cout << "Order Detail\n\n";
                Manager.vieworder(all_order[op]);
                cout << "\n\nPress R to recieve OR Press any key to return";
                char ch = getch();

                if (tolower(ch) == 'r')
                {
                    system("CLS");
                    for (int i = 0; i < all_item.size(); i++)
                    {
                        if (strcmp(all_order[op].name, all_item[i].name) == 0)
                        {
                            all_item[i].stock += all_order[op].quantity;
                        }
                    }
                    all_order.erase(all_order.begin() + op);
                    break;
                }
                else
                {
                    d.store_order();
                    break;
                }
            }
        }
    }
}

void shop::cashier_detail_ui()
{
    bool condition = true;
    while (condition)
    {
        system("CLS");
        cout << "Main Menu\n";
        cout << "\t1) Add cashier\n\t2) View Cashiers\n\t3) Exit\n";
        int op;
        cout << "Option: ";
        cin >> op;
        cashier tmp;
        switch (op)
        {
        case 1:
            system("CLS");
            tmp.input();
            all_cash.push_back(tmp);
            break;
        case 2:
            system("CLS");
            view_cashier_ui();
            break;
        case 3:
            system("CLS");
            condition = false;
            break;
        default:
            system("CLS");
            cout << "Wrong Option entered";
            getch();
        }
    }
}

void shop::view_cashier_ui()
{
    bool condition = true;
    while (condition)
    {
        system("CLS");
        cout << "Cashier Menu\n\n";
        int j = 0, op;
        for (int i = 0; i < all_cash.size(); i++)
        {
            cout << i + 1 << ") " << all_cash[i].get_name() << endl;
            j = i;
            j += 2;
        }
        if (j == 0)
        {
            cout << "No Cashiers found";
            getch();
            break;
        }
        cout << j << ") Exit\n";
        cout << "Option: ";
        cin >> op;
        if (op == j)
        {
            condition = false;
        }
        else
        {
            op--;
            while (1)
            {
                system("CLS");
                cout << "Cashier Detail\n\n";
                all_cash[op].viewinfo();
                cout << "\n\nPress C to change Info OR Press R to delete OR Press any key to return";
                char ch = getch();

                if (tolower(ch) == 'c')
                {
                    system("CLS");
                    all_cash[op].changeinfo();
                }
                else if (tolower(ch) == 'r')
                {
                    system("CLS");
                    all_cash.erase(all_cash.begin() + op);
                    break;
                }
                else
                {
                    break;
                }
            }
        }
    }
}

void shop::manager_account_detail_ui()
{
    while (1)
    {
        cout << "Account details\n\n";
        man.viewinfo();
        cout << "\n\n";
        char a;
        cout << "Press C to change Information OR Press any key to exit";
        a = getch();
        if (tolower(a) == 'c')
        {
            system("CLS");
            man.changeinfo();
            Manager = man;
            getch();
        }
        else
        {
            break;
        }
    }
}

void shop::shop_detail_ui()
{

    while (1)
    {
        cout << "Shop details\n\n";
        filing_view_shop_information();
        cout << "\n\n";
        char a;
        cout << "Press C to change Information OR Press any key to exit";
        a = getch();
        if (tolower(a) == 'c')
        {
            system("CLS");
            filing_change_information();
        }
        else
        {
            break;
        }
    }
}

void shop::cashier_ui()
{
    bool condition = true;
    while (condition)
    {
        system("CLS");
        cout << "Main Menu\n";
        cout << "\t1) Customer\n\t2) Change Account details\n\t3) Logout\n";
        int op;
        cout << "\nOption: ";
        cin >> op;
        switch (op)
        {
        case 1:
            system("CLS");
            customer_ui();
            break;
        case 2:
            system("CLS");
            cashier_account_detail_ui();
            break;
        case 3:
            system("CLS");
            cash.logout();
            condition = false;
            break;
        default:
            system("CLS");
            cout << "Wrong Option entered";
            getch();
        }
    }
}

void shop::cashier_account_detail_ui()
{
    while (1)
    {
        cout << "Account details\n\n";
        cash.viewinfo();
        cout << "\n\n";
        char a;
        cout << "Press C to change Information OR Press any key to exit";
        a = getch();
        if (tolower(a) == 'c')
        {
            system("CLS");
            cash.changeinfo();
            getch();
        }
        else
        {
            break;
        }
    }
}

void shop::customer_ui()
{
    bool condition = true;
    while (condition)
    {
        system("CLS");
        bool found = false;
        cout << "Customer Menu\n";
        cout << "\t1) Register customer\n\t2) Customer registered\n\t3) Exit\n";
        int op;
        cout << "\nOption: ";
        cin >> op;
        switch (op)
        {
        case 1:
            system("CLS");
            cus.input();
            all_cus.push_back(cus);
            items_ui();
            condition = false;
            break;
        case 2:
            system("CLS");
            found = customer_registered_ui();
            condition = !found;
            if (found)
                items_ui();
            break;
        case 3:
            system("CLS");
            condition = false;
            break;
        default:
            system("CLS");
            cout << "Wrong Option entered";
            getch();
        }
    }
}

bool shop::customer_registered_ui()
{
    system("CLS");
    bool found = false;
    cout << "Customer Selection\n\n";
    cout << "Enter Customer Phone Number: ";
    cus.set_phone_num();
    for (int i = 0; i < all_cus.size(); i++)
    {
        if (strcmp(cus.get_phone_num(), all_cus[i].get_phone_num()) == 0)
        {
            found = true;
            cus = all_cus[i];
            break;
        }
    }
    if (!found)
    {
        system("CLS");
        char name[100];
        fflush(stdin);
        cout << "Customer Not found\n\n";
        cout << "Enter customer Name: ";
        gets(name);
        cus.set_name(name);
        int j = 0, op;
        for (int i = 0, j = 0; i < all_cus.size(); i++)
        {
            if (strcmp(cus.get_name(), all_cus[i].get_name()) == 0)
            {
                j++;
                cout << j << ")\n";
                all_cus[i].viewinfo();
            }
        }
        if (j == 0)
        {
            cout << "\n\nNo customers availabe\n\n";
        }
        cout << j << ") Exit\n\n";
        cout << "Option: ";
        cin >> op;
        if (j == op)
        {
            return found;
        }
        for (int i = 0, j = 0; i < all_cus.size(); i++)
        {
            if (strcmp(cus.get_name(), all_cus[i].get_name()) == 0)
            {
                j++;
                if (op == j)
                {
                    found = true;
                    cus = all_cus[i];
                    break;
                }
            }
        }
    }
    return found;
}

void shop::items_ui()
{
    bool condition = true;
    while (condition)
    {
        system("CLS");
        cus.viewinfo();
        cout << "\n\nProduct Menu\n\n";
        cus.viewbill();
        cout << "\n\n1) Add item to cart\n2) Remove item from cart\n3) Generate Bill";
        int op;
        cout << "\n\nOption: ";
        cin >> op;
        switch (op)
        {
        case 1:
            system("CLS");
            Add_item();
            order_item();
            break;
        case 2:
            system("CLS");
            remove_item();
            break;
        case 3:
            system("CLS");
            cus.viewbill();
            cus.calpoints();
            getch();
            Item.clear();
            condition = false;
            break;
        default:
            cout << "Wrong Option entered";
            getch();
        }
    }
}

#endif
