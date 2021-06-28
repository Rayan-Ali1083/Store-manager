#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <conio.h>
#include "Human.h"
using namespace std;

class login_ui
{
public:
    virtual void login() = 0;												//pure virtual function to be used in derived class
    virtual void logout() = 0;
};

class user : public Human, public login_ui
{
protected:
    char user_name[100];
    char pass[100];

public:
    void setuser_name(char x[100]) { strcat(user_name, x); }				//setters
    void setpass(char x[100]) { strcat(pass, x); }

    string getuser_name() { return user_name; }								//getters
    string getpass() { return pass; }

    user() : Human()														//Human constructors also called
    {
        for (int i = 0; i < 100; i++)
        {
            user_name[i] = ' ';
            pass[i] = ' ';
        }
    }

    char *inputpass();
    void changepass();
};

char *user::inputpass()														//input password
{
    char *x;
    char *z;
    char y;
    int i = 0;
    x = new char[i + 1];
    x[i] = '\0';
    do
    {
        y = getch();
        if (y != '\r')
        {
            z = new char[i + 1];
            i++;
            for (int k = 0; k < i; k++)
            {
                z[k] = x[k];
            }
            delete x;
            x = new char[i + 1];
            for (int k = 0; k < i; k++)
            {
                x[k] = z[k];
            }
            delete z;
            cout << "*";
            x[i - 1] = y;
            x[i] = '\0';
        }
    } while (y != '\r');
    return x;
}

void user::changepass()														//changing password
{
    cin.ignore();
    int i = 3;
    while (i)
    {
        cout << "Enter old password: ";
        string a = inputpass();
        cout << endl;
        if (a == pass)
        {
            system("CLS");
            cout << "Enter new password: ";
            char *b = inputpass();
            cout << endl;
            for (int i = 0; i < strlen(b); i++)
            {
                pass[i] = b[i];
            }
            break;
        }
        else
        {
            i--;
            if (i != 0)
            {
                system("CLS");
                cout << "Wrong password entered" << endl;
                getch();
            }
            else
            {
                system("CLS");
                cout << "Password entered wrong too many times" << endl;
            }
        }
    }
}

#endif
