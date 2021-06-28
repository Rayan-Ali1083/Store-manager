#pragma once
#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <fstream>
#include <vector>
#include "customer.h"
#include "cashier.h"
#include "manager.h"
#include "item.h"

using namespace std;

vector<customer> all_cus;
vector<cashier> all_cash;
vector<item> all_item;
vector<ORDERED> all_order;
manager Manager;

class file
{
public:
    ifstream fin;
    ofstream fout;
    FILE *fp;

    void getcustomer();
    void getcashier();
    void getitem();
    void getmanager();
    void getorder();
    void getall();
    void store_customer();
    void store_cashier();
    void store_item();
    void store_manager();
    void store_order();
    void store_all();
    void check_all();
} f;

void file::getcustomer()
{

    customer cus;

    fin.open("Customer Information.dat", ios::in | ios::binary);
    if (!fin.is_open())
    {
        cout << "Customer Information.dat File cannnot be opened";
        exit(1);
    }
    fin.read((char *)&cus, sizeof(cus));
    while (!fin.eof())
    {
        all_cus.push_back(cus);
        fin.read((char *)&cus, sizeof(cus));
    }
    fin.close();
}
void file::getcashier()
{

    cashier cash;

    fin.open("Cashier Information.dat", ios::in | ios::binary);
    if (!fin.is_open())
    {
        cout << "Cashier Information.dat File cannnot be opened";
        exit(1);
    }
    fin.read((char *)&cash, sizeof(cash));
    while (!fin.eof())
    {
        all_cash.push_back(cash);
        fin.read((char *)&cash, sizeof(cash));
    }
    fin.close();
}
void file::getitem()
{

    item pro;

    fin.open("Items Info.dat", ios::in);
    if (!fin.is_open())
    {
        cout << "Items Info.dat File cannnot be opened";
        exit(1);
    }
    fin.read((char *)&pro, sizeof(pro));
    while (!fin.eof())
    {
        all_item.push_back(pro);
        fin.read((char *)&pro, sizeof(pro));
    }
    fin.close();
}

void file::getmanager()
{

    manager man;

    fin.open("Manager Information.dat", ios::in | ios::binary);
    if (!fin.is_open())
    {
        cout << "Mananger Information File cannnot be opened";
        exit(1);
    }
    fin.read((char *)&Manager, sizeof(Manager));
    fin.close();
}
void file::getorder()
{

    ORDERED order;

    fp = fopen("orders.txt", "r");
    if (fp == NULL)
    {
        cout << "orders.txt un able to open";
        exit(1);
    }
    fread(&order, sizeof(order), 1, fp);
    while (!feof(fp))
    {
        if (order.quantity != 0)
            all_order.push_back(order);
        fread(&order, sizeof(order), 1, fp);
    }
    fclose(fp);
}
void file::getall()
{
    getcustomer();
    getcashier();
    getitem();
    getmanager();
    getorder();
}
void file::store_customer()
{
    fout.open("Customer Information.dat", ios::trunc | ios::binary);
    for (int i = 0; i < all_cus.size(); i++)
    {
        fout.write((char *)&all_cus[i], sizeof(all_cus[i]));
    }
    all_cus.clear();
    fout.close();
}
void file::store_cashier()
{
    fout.open("Cashier Information.dat", ios::trunc | ios::binary);
    for (int i = 0; i < all_cash.size(); i++)
    {
        fout.write((char *)&all_cash[i], sizeof(all_cash[i]));
    }
    all_cash.clear();
    fout.close();
}
void file::store_item()
{
    fout.open("Items Info.dat", ios::trunc | ios::binary);
    for (int i = 0; i < all_item.size(); i++)
    {
        fout.write((char *)&all_item[i], sizeof(all_item[i]));
    }
    all_item.clear();
    fout.close();
}
void file::store_manager()
{
    fout.open("Manager Information.dat", ios::trunc | ios::binary);
    fout.write((char *)&Manager, sizeof(Manager));
    fout.close();
}
void file::store_order()
{
    fp = fopen("orders.txt", "w");
    for (int i = 0; i < all_order.size(); i++)
    {
        fwrite(&all_order[i], sizeof(all_order[i]), 1, fp);
    }
    all_order.clear();
    fclose(fp);
}
void file::store_all()
{
    store_customer();
    store_cashier();
    store_item();
    store_manager();
    store_order();
}

void file::check_all()
{

    fin.open("Customer Information.dat");
    if (!fin.is_open())
    {
        store_customer();
    }
    fin.close();

    fin.open("Cashier Information.dat");
    if (!fin.is_open())
    {
        store_cashier();
    }
    fin.close();

    fin.open("Items Info.dat");
    if (!fin.is_open())
    {
        store_item();
    }
    fin.close();

    fin.open("Manager Information.dat");
    if (!fin.is_open())
    {
        store_manager();
        manager m;
        m.filing_addmanager();
    }
    fin.close();

    fp = fopen("orders.txt", "r");
    if (fp == NULL)
    {
        fp = fopen("orders.txt", "w");
    }
    fclose(fp);
    _fcloseall();
}

bool manager::login(char user[100], char password[100])
{
    bool success = false;
    if ((strcmp(user, Manager.user_name) == 0) && (strcmp(password, Manager.pass) == 0))
    {
        success = true;
        strcpy(name, Manager.name);
        strcpy(phone_number, Manager.phone_number);
        strcpy(email, Manager.email);
        strcpy(user_name, Manager.user_name);
        strcpy(pass, Manager.pass);
    }
    return success;
}

void manager::logout()
{
    f.store_all();
}

bool cashier::login(char user[100], char password[100])
{
    bool success = false;
    int n_max = 0;
    for (int i = 0; i < all_cash.size(); i++)
    {
        if (n_max < all_cash[i].n)
            n_max = all_cash[i].n;
    }
    for (int i = 0; i < all_cash.size(); i++)
    {
        if ((strcmp(user, all_cash[i].user_name) == 0) && (strcmp(password, all_cash[i].pass) == 0))
        {
            success = true;
            strcpy(name, all_cash[i].name);
            strcpy(phone_number, all_cash[i].phone_number);
            strcpy(email, all_cash[i].email);
            strcpy(user_name, all_cash[i].user_name);
            strcpy(pass, all_cash[i].pass);
            salary = all_cash[i].salary;
            ID = all_cash[i].ID;
            n = n_max;
            break;
        }
    }
    return success;
}

void cashier::logout()
{
    f.store_all();
};

void Add_item()
{
    bool condition = true;
    while (condition)
    {
        cout << "Choose Item\n\n";
        int j = 0, op;
        for (int i = 0; i < all_item.size(); i++)
        {
            cout << i + 1 << ") " << all_item[i].name << endl;
            j = i;
            j += 2;
        }
        cout << j << ") Exit\n";
        cout << "\nOption: ";
        cin >> op;
        if (j == op)
        {
            condition = false;
        }
        else if (op < j)
        {
            op--;
            ITEM_CUS n;
            n.ID = all_item[op].ID;
            strcpy(n.name, all_item[op].name);
            n.price = all_item[op].price;
            cout << "\n\nEnter the quantity: ";
            cin >> n.quantity;
            if (n.quantity < all_item[op].stock)
            {
                all_item[op].stock -= n.quantity;
                Item.push_back(n);
                condition = false;
            }
            else
            {
                cout << "\n\nNot enough items available";
                condition = true;
            }
        }
        else
        {
            system("CLS");
            cout << "Wrong Option selected";
            condition = true;
        }
    }
}

void remove_item()
{
    bool condition = true;
    while (condition)
    {
        cout << "Choose Item\n\n";
        int j = 0, op;
        for (int i = 0; i < all_item.size(); i++)
        {
            cout << i + 1 << ") " << all_item[i].name << endl;
            j = i;
            j += 2;
        }
        cout << j << ") Exit\n";
        cout << "\nOption: ";
        cin >> op;
        if (j == op)
        {
            condition = false;
        }
        else if (op < j)
        {
            op--;
            Item.erase(Item.begin() + op);
            condition = false;
        }
        else
        {
            system("CLS");
            cout << "Wrong Option selected";
            condition = true;
        }
    }
}

void order_item()
{
    bool order = false;
    for (int i = 0; i < all_item.size(); i++)
    {
        if (all_item[i].stock < all_item[i].stock_limit)
        {
            for (int j = 0; j < all_order.size(); j++)
            {
                if (strcmp(all_item[i].name, all_order[i].name) == 0)
                {
                    order = true;
                    break;
                }
            }
            if (!order)
            {
                ORDERED n;
                strcpy(n.name, all_item[i].name);
                n.ID = all_item[i].ID;
                n.quantity = all_item[i].stock_max - all_item[i].stock;
                all_order.push_back(n);
            }
        }
        order = false;
    }
}

#endif