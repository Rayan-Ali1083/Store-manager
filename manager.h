#ifndef MANAGER_H
#define MANAGER_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "user.h"

using namespace std;

class item;

struct ORDERED																		//struct used for items
{
	int ID;
	char name[100];
	int quantity;
} order;

class manager : public user															//public inheritencece
{
public:
	manager() : user() {}

	manager(const manager &obj)
	{
		strcpy(name, obj.name);
		strcpy(email, obj.email);
		strcpy(phone_number, obj.phone_number);
		strcpy(user_name, obj.user_name);
		strcpy(pass, obj.pass);
	}

	void input();
	void changeinfo();
	void viewinfo();
	void login() {}
	bool login(char user[100], char password[100]);
	void logout();
	void vieworder(ORDERED order);
	friend void order_item(vector<item>, manager); // ordering item less then stock limit
	
	void filing_addmanager()														//filing
	{
		ofstream outf;
		outf.open("Manager Information.dat", ios::trunc);
		if (!outf.is_open())
		{
			cout << "Manager Information.dat File cannot be opened";
			exit(1);
		}
		input();
		outf.write((char *)this, sizeof(*this));
		outf.close();
	}

	void filing_get_manager()														//ouputing manger details
	{
		_fcloseall();
		ifstream inf;
		inf.open("Manager Information.dat");
		if (!inf.is_open())
		{
			cout << "Mananger Information File cannnot be opened";
			exit(1);
		}

		inf.read((char *)this, sizeof(*this));
		inf.close();
	}

	void filing()
	{
		ofstream outf;
		outf.open("Manager Information.dat", ios::trunc);
		outf.write((char *)this, sizeof(*this));
		outf.close();
	}


	void filing_addorder()															//storing orders
	{
		FILE *fp;
		fp = fopen("Order Info.txt", "w+");
		fwrite(&order, sizeof(order), 1, fp);
		fclose(fp);
	}

	bool filing_display_order()														//reading orders from file
	{
		FILE *fp;
		int i = 0, op;
		bool f = true;
		fp = fopen("Order Info.txt", "r");
		cout << "Select order's recieved\n";
		while (feof(fp))
		{
			fread(&order, sizeof(order), 1, fp);
			cout << i << "- \n";
			cout << "\tName: " << order.name << "\n\tID: " << order.ID << "\n\tquantity: " << order.quantity << endl;
			i++;
		}
		cout << i << ") Exit";
		cout << "Option: ";
		cin >> op;
		if (op != i && op < i)
		{
			f = false;
			for (int j = 0; j < op; j++)
			{
				fread(&order, sizeof(order), 1, fp);
			}
		}
		fclose(fp);
		return f;
	}

	void filing_remove_order(int ID)												//removing orders
	{
		FILE *fp, *ft;
		int i = 1, op;
		fp = fopen("Order Info.txt", "r");
		ft = fopen("Order Info TEMP.txt", "w");

		while (feof(fp))
		{
			i++;
			fread(&order, sizeof(order), 1, fp);
			if (order.ID != ID)
			{
				fwrite(&order, sizeof(order), 1, ft);
			}
		}

		fclose(fp);
		fclose(ft);
		_fcloseall();
		remove("Order Info.txt");
		rename("Order Info TEMP.txt", "Order Info.txt");
	}
};

void manager::input()
{
	fflush(stdin);
	cout << "Enter Name: ";
	gets(name);
	cout << "Enter Phone number: ";
	set_phone_num();
	cout << "\nEnter email: ";
	gets(email);
	cout << "Enter User Name: ";
	gets(user_name);
	cout << "Enter Password: ";
	gets(pass);
}

void manager::changeinfo()
{
	bool done = true;
	while (done)
	{
		fflush(stdin);
		cout << "Account information to change:\n";
		cout << "\t1) Name\n\t2) Phone Number\n\t3) Email\n\t4) User Name\n\t5) Password\n\t6) Exit\n";
		cout << "Option: ";
		int op;
		cin >> op;
		char *password;
		switch (op)
		{
		case 1:
			fflush(stdin);
			system("CLS");
			cout << "Enter new Name: ";
			gets(name);
			break;
		case 2:
			fflush(stdin);
			system("CLS");
			cout << "Enter new Phone Number: ";
			set_phone_num();
			break;
		case 3:
			fflush(stdin);
			system("CLS");
			cout << "Enter new Email: ";
			gets(email);
			break;
		case 4:
			fflush(stdin);
			system("CLS");
			cout << "Enter new User Name: ";
			gets(user_name);
			break;
		case 5:
			fflush(stdin);
			system("CLS");
			cout << "Enter new Password: ";
			gets(pass);
			break;
		case 6:
			fflush(stdin);
			system("CLS");
			done = false;
			break;
		default:
			fflush(stdin);
			cout << "Wrong option entered";
			getch();
			system("CLS");
		}
	}
}

void manager::viewinfo()
{
	cout << "Name: " << name << endl;
	cout << "Phone number: ";
	for(int a=0;a<11;a++){
		cout << phone_number[a];
	}
	cout << endl;
	cout << "Email: " << email << endl;
	cout << "User Name: " << user_name << endl;
	cout << "Password: " << pass << endl;
}

void manager::vieworder(ORDERED order)
{
	cout << "Name: " << order.name << endl;
	cout << "ID: " << order.ID << endl;
	cout << "Quantity: " << order.quantity << endl;
}
#endif
