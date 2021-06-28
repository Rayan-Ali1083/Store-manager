#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Human.h"
#include "file.h"
#include "shop.h"
using namespace std;

class item : public data															//public inheritence of data
{
protected:
    char name[100];
    char des[200];
    float price;
    int stock;
    int stock_limit;
    int stock_max;
    static int n;
    int ID;

public:																			 //setters and getters
    void setname(char x[100]) { strcpy(name, x); }
    void setdes(char x[100]) { strcpy(des, x); }
    void setprice(float x) { price = x; }
    void setstock(int x) { stock = x; }
    void set_stock_limit(int x) { stock_limit = x; }
    void setID(int x) { ID = x; }

    char *getname() { return name; }
    char *getdes() { return des; }
    float getprice() { return price; }
    int getstock() { return stock; }
    int get_stock_limit() { return stock_limit; }
    int getID() { return ID; }

    static void n_inc()
    {
        n++;
    }

    item()																	//default constructor
    {
        for (int i = 0; i < 100; i++)
        {
            name[i] = ' ';
        }
        for (int i = 0; i < 200; i++)
        {
            des[i] = ' ';
        }
        price = 0;
        stock = 0;
        stock_limit = 0;
    }

    void input();
    void changeinfo();
    void viewinfo();

    friend void Add_item();    // adding itiem to customer cart
    friend void remove_item(); // removing item from customer cart
    friend void order_item();  // ordering item less then stock limit

    friend class shop;

    void display_item()
    {
        ifstream fin;
        fin.open("Items Info.dat");

        if (!fin.is_open())
        {

            cout << "Items Info.dat File could not open " << endl;
            exit(1);
        }

        while (!fin.eof())
        {
            fin.read((char *)this, sizeof(*this));
            cout << "ID: " << ID << "\nItem: " << name << endl;
        }
    }

    void filing_add_item()														//filing
    {
        ofstream fout;
        ifstream fin;
        fin.open("Items Info.dat");
        int x = 0;
        while (!fin.eof())
        {
            fin.read((char *)this, sizeof(*this));
            if (x < n)
                x = n;
        }
        fin.close();
        n = x;
        n++;
        fout.open("Items Info.dat");
        if (!fout.is_open())
        {
            cout << endl
                 << "Items Info.dat File could not be open!";
            exit(1);
        }
        input();
        fout.write((char *)this, sizeof(*this));
        fout.close();
    }

    void filing_remove_item()
    {
        ifstream fin;
        ofstream fout;

        fin.open("Items Info.dat");
        if (!fin.is_open())
        {
            cout << endl
                 << "Items Info.dat File could not be open!";
            exit(1);
        }

        fout.open("Items Info Temp.dat");
        if (!fout.is_open())
        {
            cout << endl
                 << "Items Info Temp.dat File could not be open!";
            exit(1);
        }

        display_item();
        int search_id;
        cout << "Enter ID to remove: ";
        cin >> search_id;

        while (!fin.eof())
        {
            fin.read((char *)this, sizeof(*this));
            if (search_id != ID)
            {
                fout.write((char *)this, sizeof(*this));
            }
        }

        fin.close();
        fout.close();

        _fcloseall();
        remove("Items Info.dat");
        rename("Itmes Info Temp.dat", "Items Info.dat");
        fflush(stdin);
    }

    void filing_change_info_item()
    {
        fstream both;
        both.open("Items Info.dat", ios::app | ios::in | ios::out);

        if (!both.is_open())
        {
            cout << "Items Info.dat File cannot be opened";
            exit(1);
        }

        display_item();
        int search_id;
        cout << "Enter ID to update: ";
        cin >> search_id;

        while (!both.eof())
        {
            both.read((char *)this, sizeof(*this));
            if (search_id != ID)
            {
                changeinfo();
                both.write((char *)this, sizeof(*this));
            }
        }

        both.close();
    }

    void filing_view_info()
    {
        ifstream inf;
        inf.open("Items Info.dat");
        if (!inf.is_open())
        {
            cout << "Items Info.dat File cannot be opened";
            exit(1);
        }

        display_item();
        int search_id;
        cout << "Enter ID: ";
        cin >> search_id;

        while (!inf.eof())
        {
            inf.read((char *)this, sizeof(*this));
            if (search_id == ID)
            {
                viewinfo();
                inf.close();
                return;
            }
        }
    }
};

int item::n;

void item::input()																//inputting data
{
    fflush(stdin);
    cout << "Enter Product name: ";
    gets(name);
    cout << "Enter Decription: ";
    gets(des);
    fflush(stdin);
    cout << "Enter price: ";
    cin >> price;
    cout << "Enter Stock: ";
    cin >> stock;
    cout << "Enter the stock limit: ";
    cin >> stock_limit;
    cout << "Enter the maximum stock limit: ";
    cin >> stock_max;
}

void item::viewinfo()															//veiw info for Product
{
    cout << "Product name: " << name << endl;
    cout << "Decription: " << des << endl;
    cout << "Price: " << price << endl;
    cout << "Stock: " << stock << endl;
    cout << "Stock limit: " << stock_limit << endl;
    cout << "Maximum stock limit: " << stock_max << endl;
}

void item::changeinfo()															//change info of product
{
    bool done = true;
    int op;
    while (done)
    {
        cout << "Account information to change:\n";
        cout << "\t1) Name\n\t2) Description\n\t3) Price\n\t4) Stock\n\t5) Stock limit\n\t6) Maximum Stock\n\t7) Exit\n";
        cout << "Option: ";
        cin >> op;
        switch (op)
        {
        case 1:
        	fflush(stdin);
            system("CLS");
            cout << "Enter new Name: ";
            gets(name);
            done = false;
            break;
        case 2:
        	fflush(stdin);
            system("CLS");
            cout << "Enter new Description: ";
            gets(des);
            done = false;
            break;
        case 3:
            system("CLS");
            cout << "Enter new Price: ";
            cin >> price;
            done = false;
            break;
        case 4:
            system("CLS");
            cout << "Enter new Stock: ";
            cin >> stock;
            done = false;
            break;
        case 5:
            system("CLS");
            cout << "Enter Stock limit: ";
            cin >> stock_limit;
            done = false;
            break;
        case 6:
            system("CLS");
            cout << "Enter Maximum Stock: ";
            cin >> stock_max;
            done = false;
            break;
        case 7:
            system("CLS");
            cout << "Exiting !!!";
            done = false;
            break;
        default:
            cout << "Wrong option entered";
            getch();
            system("CLS");
        }
    }
}

#endif
