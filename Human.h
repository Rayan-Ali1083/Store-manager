#ifndef HUMAN_H
#define HUMAN_H

#include <iostream>
#include <cstring>
#include <ctype.h>
#include <stdio.h>
#include <iomanip>
#include <cstdlib>
#include <conio.h>
#include <string>

using namespace std;

class data
{
public:
	virtual void input() = 0;													//virtual functions to make sure that derived class have them
																				//and object of Human can not be made
	virtual void changeinfo() = 0;
	virtual void viewinfo() = 0;
};

class Human : public data														//public inheritence of data class
{
protected:
	char name[100];
	char phone_number[11];
	char email[50];

public:
	Human()
	{
		for (int i = 0; i < 100; i++)											//initializing name, email, phone number
		{
			name[i] = ' ';
		}
		for (int i = 0; i < 50; i++)
			email[i] = ' ';
		for (int i = 0; i < 11; i++)
			phone_number[i] = ' ';
	} 																			//setters are made for future updation
	void set_name(char name[100])
	{
		strcpy(this->name, name);
	}
	void set_email(char email[100])
	{
		strcpy(this->email, email);
	}
	void set_phone_num()
	{
		int a = 0;
		char x;
		for (a = 0; a < 11; a++)
		{
			x = _getche();														//using _getche() so that user dont have to press enter
			phone_number[a] = x;
		}
	}
	char *get_name()															//getters 
	{
		return name;
	}
	char *get_email()
	{
		return email;
	}
	char *get_phone_num()
	{
		return phone_number;
	}
};

#endif
