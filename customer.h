//customer.h
#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include "Human.h"

using namespace std;

struct ITEM_CUS																		//struct to contain item info
{
	int ID;
	char name[100];
	int quantity;
	float price;
};

vector<ITEM_CUS> Item;																//vector of data type ITEM_CUS

float amount;

class customer : public Human
{
protected:
	int point;
	static int n;
	
public:
	customer() : Human()															//Human & customer constructor called
	{
		point = 0;																	//initializing the data member point
	}

	customer(const customer &obj)													//parameterized constructor
	{
		strcpy(name, obj.name);
		strcpy(email, obj.email);
		strcpy(phone_number, obj.phone_number);
		point = point;
	}

	static void n_inc()
	{
		n++;
	}
	void viewinfo();																//veiw customer details
	void changeinfo();																//change customer info
	void input();																	//input customer data
	int calpoints();																//contains formula to calculate points
	float usepoints();																//use points instead of money to pay the bills
	void viewbill();																//view info of bill
	float Bill();																	//Calculating bill
	friend void Add_item(); 														//adding item to customer's cart
	friend void remove_item();														//remove item from customer's cart

	bool search_customer()															//searching for a customer 
	{
		ifstream inf;
		char search_phn[11];
		char nam[100];
		int op, i = 1;
		bool found = false;
		inf.open("Customer Information.dat", ios::app);
		if (!inf.is_open())
		{
			cout << "Customer Information.dat File cannot be opened";
			exit(1);
		}

		while (!inf.eof())
		{
			inf.read((char *)this, sizeof(*this));									//comparing entered phone number from file to locate
																					//customer and then delete
			if (strcmp(search_phn, phone_number))
			{
				inf.close();
				found = true;
			}
		}
		if (!found)																	//using name to search for the customer incase the
																					//phone number isnt registered
		{
			cout << "Phone number isnt registerd!\nSearch using Name!";
			cout << "Enter Name to be searched:";

			gets(nam);

			inf.seekg(0, ios::beg);													//seeks to the start of the files

			while (!inf.eof())
			{
				char nam[100];
				inf.read((char *)this, sizeof(*this));
				if (strcmp(nam, name))
				{
					cout << i << ") \n";
					i++;
					viewinfo();
				}
			}
			cout << endl
				 << i << ") Not available\n";
			cout << "Select Option: ";
			cin >> op;
			if (op != i)
			{
				for (int j = 0; j < op;)
				{
					inf.read((char *)this, sizeof(*this));
					if (strcmp(nam, name))
					{
						j++;
						found = true;
					}
				}
			}
		}
		inf.close();
		return found;
	}

	void filing_addcustomer()														//adding a new customer
	{
		ofstream outf;
		outf.open("Customer Information.dat", ios::app);
		if (!outf.is_open())
		{
			cout << "Customer Information.dat File cannot be opened";
			exit(1);
		}
		input();
		outf.write((char *)this, sizeof(*this));
		outf.close();
	}

	void filing_customer_view()														//veiwing a customer
	{
		ifstream inf;
		char search_phn[11];
		char nam[100];
		inf.open("Customer Information.dat", ios::app);
		if (!inf.is_open())
		{
			cout << "Customer Information.dat File cannot be opened";
			exit(1);
		}

		while (!inf.eof())
		{
			char nam[100];
			inf.read((char *)this, sizeof(*this));
			if (strcmp(search_phn, phone_number))									//searching using phone number
			{
				viewinfo();
				inf.close();
				return;
			}

			cout << "Phone number isnt registerd!\nSearch using Name!";
			cout << "Enter Name to be searched:";

			gets(nam);

			inf.seekg(0, ios::beg);

			while (!inf.eof())
			{
				char nam[100];
				inf.read((char *)this, sizeof(*this));
				if (strcmp(nam, name))
				{
					viewinfo();
					inf.close();
					return;
				}
			}
		}
		inf.close();
	}

	void filing_change_info()														//changing info
	{
		char search_phn[11];
		char nam[100];
		fstream f;
		f.open("Customer Information.dat", ios::app | ios::in | ios::out);
		if (!f.is_open())
		{
			cout << "Customer Information.dat File cannot be opened";
			exit(1);
		}
	jump:
		cout << "Enter Phone Number to locate the Customer's Info:";				//using phone number to locate
		cin >> search_phn;

		while (!f.eof())
		{
			f.read((char *)this, sizeof(*this));
			if (strcmp(search_phn, phone_number))
			{
				changeinfo();
				f.write((char *)this, sizeof(*this));
				f.close();
				return;
			}

			cout << "Phone number isnt registerd!\nSearch using Name!\nEnter Name to be searched:";

			gets(nam);
			f.seekp(0, ios::beg);
			while (1) 												//many customers can have the same name so this will view info of
																	//all the customers with the same name
			{
				if (nam == name)
				{
					viewinfo();
					cout << "For which displayed customers, Enter phone number to be deleted!";
					goto jump;
				}
			}
		}
		f.close();
	}

	void filing_delete_customer()									// deleting a customer
	{
		ofstream fout;
		char search_phn[11];
		fout.open("Customer Information Temporary.dat");

		ifstream fin;
		fin.open("Customer Information.dat");

		while (!fin.eof())
		{
			fin.read((char *)this, sizeof(*this));
			if (!strcmp(search_phn, phone_number))				//comparing phone number
			{
				fout.write((char *)this, sizeof(*this));
			}
		}

		fout.close();
		fin.close();

		remove("Customer Information.dat");
		rename("Customer Information Temporary.dat", "Customer Information.dat");
		fflush(stdin);
	}
};

int customer::n;

void customer::input()											//data input
{
	fflush(stdin);
	cout << "Enter Name: ";
	gets(name);
	cout << "Enter Phone number: ";
	set_phone_num();
	cout << "\nEnter email: ";
	gets(email);
}

void customer::viewinfo()										//veiwing info
{
	cout << "Name: " << name << endl;
	cout << "Phone number: " << get_phone_num() << endl;
	cout << "Email: " << email << endl;
	cout << "Points: " << point << endl;
}

void customer::changeinfo()										//changes customers info
{
	bool done = true;
	int op;
	while (done)
	{
		fflush(stdin);
		cout << "Account information to change:\n";
		cout << "\t1) Name\n\t2) Phone Number\n\t3) Email\n\t4) Exit\n";
		cout << "Option: ";
		cin >> op;
		switch (op)
		{
		case 1:
			system("CLS");
			cout << "Enter new Name: ";
			gets(name);
			break;
		case 2:
			system("CLS");
			cout << "Enter new Phone Number: ";
			set_phone_num();
			break;
		case 3:
			system("CLS");
			cout << "Enter new Email: ";
			gets(email);
			break;
		case 4:
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

int customer::calpoints()										//a made formula for calculating points a customers earns
{
	int gained = amount * 0.01;
	point = point + gained;
	return point;
}

float customer::usepoints()										//decides wether the customer wants to use the points or save them
{
	int use;
	int discount;
	bool done = true;
	while (done)
	{
		cout << "One point is equal to Rs. 10\n";
		cout << "Enter Number of points to use: ";
		cin >> use;
		discount = use * 10;
		if (point >= use && discount <= amount)
		{
			amount = amount - discount;
			done = false;
		}
		else
		{
			cout << "Wrong value entered please try again";
		}
	}
	return discount;
}

void customer::viewbill()										//shows the total bill
{
	cout << setw(20) << "Item" << setw(20) << "Quantity" << setw(20) << "Price" << endl;	//setting spaces from left to display properly
	for (int i = 0; i < Item.size(); i++)
	{
		cout << setw(20) << Item[i].name << setw(20) << Item[i].quantity << setw(20) << "Rs. " << fixed << setprecision(2) << Item[i].price * Item[i].quantity << endl;
	}
	amount = 0;
	for (int i = 0; i < Item.size(); i++)
	{
		amount = amount + (Item[i].price * (float)Item[i].quantity);
	}
	cout << "\n\nBill: Rs. " << fixed << setprecision(2) << amount << endl;
}

float customer::Bill()											//shows bill after points used
{
	bool discount = false;
	float x;
	if (point > 0)
	{
		x = usepoints();
		discount = true;
	}
	system("CLS");
	viewbill();
	if (discount)
		cout << "\n\nBill After Discount: Rs. " << fixed << setprecision(2) << amount - x << endl;
	return amount;
}

#endif
