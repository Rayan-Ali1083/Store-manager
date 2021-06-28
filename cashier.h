//cashier.h
#ifndef CASHIER_H
#define CASHIER_H

#include <iostream>
#include <string>
#include <ctime>
#include <stdlib.h>
#include <fstream>
#include "user.h"															// included to inherit from user class
using namespace std;

class item;																	// to be used in a friend function
class manager;

class cashier : public user													// public inheritence from user class to access memebers
{
protected:
	float salary;
	static int n;
	int ID;

public:
	void setsalary(float x) { salary = x; }									//getters and setters
	float getsalary() { return salary; }

	cashier() : user()														//constructor of user & cashier called
	{
		salary = 0;
		n_inc();
		ID = n;
	}

	static void n_inc()														//static function 
	{
		n++;
	}

	void input();
	void viewinfo();
	void changeinfo();
	void login() {}
	bool login(char user[100], char password[100]);
	void logout();
	friend void order_item(item, manager);									// friend functions for item and manager

																			//filing

	void filing_add_cashier()												// adding a cashier
	{
		ofstream file;														// creating file to write
		file.open("Cashier Information.dat", ios::app);						//appending file
		if (!file.is_open())												//checking wether file can be opened or not
		{
			cout << endl << "Cashier Information.dat File could not be open!";
			exit(1);
		}
		cashier tmp;														//creating an obj of cashier. used for storing cashier data
		tmp.input();
		file.write((char *)&tmp, sizeof(tmp));
		file.close();
	}

	bool filing_get_cashier()												//return type bool check if exit 
	{																		//opening file to read
		ifstream fin;
		bool exi = false;
		while (1)
		{
			system("CLS");
			int i = 1, j, op;
			fin.open("Cashier Information.dat");

			if (!fin.is_open())
			{
				cout << endl
					 << "Cashier Information.dat File could not be open!";
				exit(1);
			}

			cout << "Select Cashier:\n";
			cashier tmp;
			while (!fin.eof())
			{
				fin.read((char *)&tmp, sizeof(tmp));
				cout << i << ") " << name << endl;
				i++;
				j = i;
			}

			cout << j << ") Exit\n";
			cout << "Option: ";
			cin >> op;

			if (op == j)
			{
				exi = true;
				break;
			}

			else if (op < j && op > 0)
			{
				op--;
				fin.seekg(op + sizeof(tmp), ios::beg);						//jumping to a speciic position in 
				fin.read((char *)this, sizeof(tmp));
				break;
			}

			else
			{
				cout << "Wrong Option";
				getch();
			}
		}
		return exi;
	}

	void filing()
	{
		ifstream fin;
		fin.open("Cashier Information.dat");								//opening .dat file
		ofstream fout;
		fout.open("Cashier Temp Information.dat");
		cashier tmp;
		while (!fin.eof())
		{
			fin.read((char *)&tmp, sizeof(tmp));
			if (tmp.ID == ID)
			{
				fout.write((char *)this, sizeof(this));
			}
			else
			{
				fout.write((char *)&tmp, sizeof(tmp));
			}
		}
		fin.close();
		fout.close();
		_fcloseall();
		remove("Cashier Information.dat");									//removing cashier info
		rename("Cashier Temp Information.dat", "Cashier Information.dat");	//renaming cashier temp info to cashierinfpo
	}

	void filing_remove()													//remvoing a cashier
	{
		ifstream fin;
		fin.open("Cashier Information.dat");
		ofstream fout;
		fout.open("Cashier Temp Information.dat");
		cashier tmp;
		while (!fin.eof())
		{
			fin.read((char *)&tmp, sizeof(tmp));							//matching ids of existing cashier
			if (tmp.ID == ID)
			{
				continue;
			}
			else
			{
				fout.write((char *)&tmp, sizeof(tmp));
			}
		}
		fin.close();
		fout.close();
		_fcloseall();
		remove("Cashier Information.dat");
		rename("Cashier Temp Information.dat", "Cashier Information.dat");
	}

};
int cashier::n;

void cashier::input()														//entering data
{
	fflush(stdin);
	cout << "Enter Name: ";
	gets(name);
	cout << "Enter Phone number: ";
	set_phone_num();
	fflush(stdin);
	cout << "\nEnter the email address: ";
	gets(email);
	cout << "Enter User Name: ";
	gets(user_name);
	cout << "Enter Password: ";
	gets(pass);
	cout << "\nEnter Salary: ";
	cin >> salary;
}

void cashier::changeinfo()													//changing info
{
	bool done = true;
	int op;
	while (done)
	{
		fflush(stdin);
		cout << "Account information to change:\n";
		cout << "\t1) Name\n\t2) Phone Number\n\t3) Email\n\t4) User Name\n\t5) Password\n\t6) Exit\n";
		cout << "Option: ";
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
			cout << "Exiting !!!";
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

void cashier::viewinfo()													//output info on screen
{
	cout << "ID: " << ID << endl;
	cout << "Name: " << name << endl;
	cout << "Phone number: ";
	for(int a=0;a<11;a++){
		cout << phone_number[a];
	}
	cout << "\nEmail: " << email << endl;
	cout << "Salary: " << salary << endl;
	cout << "User Name: " << user_name << endl;
	cout << "Password: " << pass << endl;
}
#endif
