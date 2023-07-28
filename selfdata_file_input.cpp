#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>    
using namespace std;

struct emp
{
	int empno;
	string name;
	string dept;
	string desg;
	int year;
	int sal;
};
int main ()
{
	int empno;
	string name;
	string dept;
	string desg;
	int year;
	int sal;
	ofstream outf("draft_selfdata.txt");

	cout<<"enter the details empno,name,dept,desg,year, sal: "<< endl;
	for(int i=0;i<15;i++)
	{
		cin>>empno>>name>>dept>>desg>>year>>sal;
		outf<<empno<<endl;
		outf<<name<<endl;
		outf<<dept<<endl;
		outf<<desg<<endl;
		outf<<year<<endl;
		outf<<sal<<endl;
		cout<<endl;
	}
	outf.close();
	return 0;
}



// nan        
//prash
//parshva
//pranav
//harsh
//rahul
//rohit
//george
//imran
//shreya
//aayesha
//ria
//lilly
//marshall
//ted
//desg
//Sales managaer            sales 
//soft eng                tech
//sales rep              sales
//inntern                 all
//project manager           HR
//accointa                    fin
//dept
//tech
//HR
//sales
//finance

 

