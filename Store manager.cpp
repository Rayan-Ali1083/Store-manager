#include <iostream>
#include <string>
#include "shop.h"
#include<unistd.h>
using namespace std;

int main()
{

	system("Color 0A");
	cout <<  "\n\n\n\n\n\n\n\n\n\n    WW   WW   WW  EEEEEEE   LL       CCCCCCC   OOOOOOO  MMMMMMMMMMMM  EEEEEEE  \n";
	sleep(1);
	cout << "    WW   WW   WW  EE        LL       CC        OO   OO  MM   MM   MM  EE       \n";
	sleep(1);
	cout << "    WW   WW   WW  EEEEEEE   LL       CC        OO   OO  MM   MM   MM  EEEEEEE  \n";
	sleep(1);
	cout << "    WW   WW   WW  EE        LL       CC        OO   OO  MM   MM   MM  EE       \n";
	sleep(1);
	cout << "    WW   WW   WW  EE        LL       CC        OO   OO  MM   MM   MM  EE       \n";
	sleep(1);
	cout << "    WWWWWWWWWWWW  EEEEEEE   LLLLLLL  CCCCCCC   OOOOOOO  MM   MM   MM  EEEEEEE  \n";
	sleep(1);
	
	d.check_all();

	shop imtiaz;

	ifstream fin;
	ofstream fout;
	fin.open("Shop Information.dat");
	if (!fin.is_open())
	{
		fout.open("Shop Information.dat");
		fout.close();
		imtiaz.filing_shop_information();
	}
	fin.close();

	imtiaz.login_ui();
}
