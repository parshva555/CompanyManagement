#include <iostream>
#include <conio.h>
#include <string>
#include <fstream>
#include <windows.h>
#include <stdlib.h>
///function to put dtaat into a file 
using namespace std;
int main ()
{
	string us;
	string pd;
	string code;
	ofstream outf("pdfile.txt");

	cout<<"enter the username , password , code : "<< endl;
	for(int i=0;i<15;i++)
	{
		cin>>us>>pd>>code;
		outf<<us<<endl;
		outf<<pd<<endl;
		outf<<code<<endl;
		cout<<endl;
	}
	outf.close();
	return 0;
}


////name293
//security code 100
	
