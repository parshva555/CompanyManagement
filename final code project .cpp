//*************************************************COMPANY MANAGEMENT SYSTEM*******************************************************************
#include <iostream>
#include <conio.h>
#include <string>
#include <fstream>
#include <windows.h>
#include <stdlib.h>
#include <iomanip>  
using namespace std;
//*********************************************PRE REQ FOR LOGIN FUNCTION**************************************************************************

struct password
{
	string us;
	string pd;
	int code;
};
struct password p[15];

//*********************************************PRE REQ FOR SELF DATA FUNCTION***********************************************************************

struct emp
{
	int empno;
	string name;
	string dept;
	string desg;
	int year;
	int sal;
};
struct emp e[15];

//*********************************************PRE REQ FOR TO DO LIST FUNCTION***********************************************************************

void fixcount();
typedef struct ToDo todo;
struct ToDo
{
	char data[100];
 	todo *link;
 	int count;
};
todo *start=NULL;

//***********************************************PRE REQ FOR LEAVE APPLICATION FUNCTION***************************************************************

struct leave 
{
	int empno;
	string name ;
	string status;	
};
struct leave l[5];
int f=-1;
int r=-1;
int total_leave=0;

void write_leave()
{
	ofstream outf("leave_file.txt");
	for(int i=0;i<total_leave;i++)
	{
		outf<<l[i].empno<<endl;
		outf<<l[i].name<<endl;
		outf<<l[i].status<<endl;
	}
	outf.close();
}

void read_leave()
{
	ifstream inf("leave_file.txt");
	for ( int i=0;i<total_leave;i++)
	{
		inf>>l[i].empno;
		inf>>l[i].name;
		inf>>l[i].status;
	}	
	inf.close();
	
}
//*********************************************************INHERITANCE CLASSES************************************************************************

class employee  //Base class
{
	public:
		void login(); 
		void selfdata_display(); 
		void to_dolist(); 
		void leave_apply();	
		void change_pd();
};

class admin:public employee
{
	public:
		admin()
		{
			system("color Df");
			cout<<setw(75)<<"WELCOME TO RK INDUSTRIES "<<endl;
			cout<<setw(75)<<"COMPANY MANAGEMENT SYSTEM "<<endl;
		}
		void login(); 
		void selfdata_display();
		void leave_apply(); 
		void sort_data();
		void annual_sort();
};

//*********************************************************EMPLOYEE FUNCTIONS************************************************************************

//*********************************************************LOGIN************************************************************************

bool login_into()
{
	int i ;
	system("color 2f");
	string username,password,un,pw;
	cout<<"ENTER YOUR USERNAME PLEASE : ";
	cin>>username;
	cout<<"\n\nENTER YOUR PASSWORD PLEASE : ";
	cin>>password;
	for(i=0;i<15;i++)
	{
		if(username==p[i].us && password==p[i].pd)
		{
			return true;	
		}
	}
	return false ;	
}

void employee :: login()
{
	string us;
	string pd;
	int code;
	ifstream inf("pdfile.txt");
	for ( int i=0;i<15;i++)
	{
		inf>>p[i].us;
		inf>>p[i].pd;
		inf>>p[i].code;
	}	
	inf.close();
	int ch,i;
	system("cls");
	system("color 2F");
	cout<<setw(50)<<"LOGIN TO PROGRAM\n\n "<<endl;
	bool status = login_into();
	if(!status)
	{
		cout<<"\nEORROR!!!\nWRONG PASSWORD OR USERNAME ENTERED\n";
		exit(0);
	}
	else
	{
		cout<<"LOGIN SUCCESSFULL"<<endl;
		cout<<"WELCOME TO THE SYSTEM"<<endl;
	}
}

//*********************************************************TO DOD LIST************************************************************************

void welcomeUser()
{
	system("color 4F");
    cout<<endl<<endl<<endl<<endl<<endl;
    cout<<"\t-----------------------------------------------------------------------------------------------------\n\n";
    cout<<"\t************************************* YOUR TODO LIST *************************************************\n\n";
    cout<<"\t------------------------------------------------------------------------------------------------------";
    cout<<"\n\n\n\t\t*******************************WELCOME*******************************\n\n\n\n\n\n\n\n\n\t";
    system("pause");
}
void seeToDo()
{
	system("cls");
    todo *temp;
    temp=start;
    if(start==NULL)
    {
    	cout<<"\nEmpty TODO\n\n";
	}
    while(temp!=NULL)
	{
		cout<<")",temp->count;
        puts(temp->data);
        fflush(stdin);
        temp=temp->link;
    }
    cout<<"\n\n\n";
    system("pause");
}
void createToDo()
{
    char k;
    todo *t,*temp;
    system("cls");
    while(1)
	{
		cout<<"\nWant to add?y/n";
        fflush(stdin);
        cin>>k;
        if(k=='n'|| k=='N')
        {
        	break;
		} 
        if(k=='y' || k=='Y')
		{
			if(start==NULL)
			{
        		t=(todo *)calloc(1,sizeof(todo));
        		start=t;
        		cout<<"\nADD it..\n";
        		fflush(stdin);
        		gets(t->data);
        		t->count=1;
        		start->link=NULL;
      		}
       		else
			{
       			temp=(todo *)calloc(1,sizeof(todo));
       			cout<<"\nADD it..\n";
       			fflush(stdin);
		       gets(temp->data);
		       temp->link=NULL;
		       t->link=temp;
		       t=t->link;
            }
        fixcount();
        }
        else 
        {
        	cout<<"\n\n INDVALID INPUT!!";
        	break;
		}
    }
}

void delToDo()
{
	system("cls");
    int d;
    todo *temp1,*temp;
    cout<<"\nEnter the no of the todo you want to remove\n";
    scanf("%d",&d);
    temp1=start;
    temp=start->link;
    while(1)
	{
    	if(temp1->count==d)
		{
    		start=start->link;
    		free(temp1);
    		fixcount();
    		break;
  		}
	    if(temp->count==d)
		{
	        temp1->link=temp->link;
	        free(temp);
	        fixcount();
	        break;
	    }
	    else
		{
	        temp1=temp;
	        temp=temp->link;
	    }
	}
	system("pause");
}
void fixcount()
{
	todo *temp;
    int i=1;
    temp=start;
    while(temp!=NULL)
	{
    	temp->count=i;
    	i++;
    	temp=temp->link;
    }
}
void updateToDo()
{
	system("cls");
    todo *temp,*t;
    char k;
    while(1)
	{
		cout<<"\nWant to add?y/n";
        fflush(stdin);
        cin>>k;
        if(k=='n')
            break;
        cout<<"\nADD it..\n";
        temp=(todo *)calloc(1,sizeof(todo));
        fflush(stdin);
        gets(temp->data);
        temp->link=NULL;
        t=start;
        while(t->link!=NULL)
		{
        	t=t->link;
        }
      	t->link=temp;
      	fixcount();
	}
	cout<<"\n\n";
	system("pause");
}

void employee :: to_dolist()
{
	system("cls");
	int choice;
    welcomeUser();
    system("color 3F");
    cout<<"\n1.See Your ToDo List";
    cout<<"\n2.Create Your ToDos";
    cout<<"\n3.Delete Your ToDos";
    cout<<"\n4.Update Your ToDos";
    cout<<"\n5.Exit";
    cout<<"\n\nEnter your choice..";
    cin>>choice;
    switch(choice)
	{
		case 1:
			seeToDo();
        	break;
        case 2:
            createToDo();
            break;
        case 3:
            delToDo();
            break;
        case 4:
            updateToDo();
            break;
        case 5:
       	    break;
    }
}

//*********************************************************SELF DATA************************************************************************

void employee :: selfdata_display()
{
	system("cls");
	system("color 5F");
	ifstream inf("draft_selfdata.txt");
	for ( int i=0;i<15;i++)
	{
		inf>>e[i].empno;
		inf>>e[i].name;
		inf>>e[i].dept;
		inf>>e[i].desg;
		inf>>e[i].year;
		inf>>e[i].sal;
	}
	cout<<"\n\n********************* DISPLAYING EMPLOYEE DETAILS ************************* \n\n"<<endl;
	cout<<"EMP_NO"<<setw(15)<<"NAME"<<setw(20)<<"DEPT"<<setw(25)<<"DESG"<<setw(15)<<"YEAR"<<endl;
	for ( int i=0;i<15;i++)
	{
		cout<<"\n--------------------------------------------------------------------------------------"<<endl;
		cout<<e[i].empno<<setw(20)<<e[i].name<<setw(20)<<e[i].dept<<setw(25)<<e[i].desg<<setw(15)<<e[i].year<<endl;
	}	
	inf.close();
	cout<<"\n\n";
	system("PAUSE");
	system("cls");
	
}

//*********************************************************LEAVE APPLICATION************************************************************************

void employee :: leave_apply()
{
	system("cls");
	system(" color 3F");
	int no;
	string name ;
	cout<<"\n\t\t\tLEAVE APPLICATION"<<endl;
	cout<<"\n\nAPPLY YOUR LEAVE HERE!!!!!\n";
	cout<<"PLEASE ENTER YOUR EMPLOYEE NUMBER:\t\t ";
	cin>>no;
	cout<<"\nPLEASE ENTER YOUR NAME:\t\t ";
	cin>>name;
	cout<<"\nAdding your Application to the Queue "<<endl;
	// enque array 
	read_leave();
	if (r==15)
 	{
 		cout<<"LEAVE APPLICATIONN IS FULL\nCANNOT APPLY SORRY!!!";
	}
	else 
	{
		r++;
		l[r].empno=no;
		l[r].name=name;
		l[r].status="Applied";	
		total_leave++;
	}	
	write_leave();
	system("PAUSE");
}



//*********************************************************CHANGE PASSSWORD************************************************************************

bool change()
{
	int i; 
	int change;
	system("cls");
	system("color 4f");
	cout<<"\nENTER YOUR CODE PLEASE"<<endl;
	cin>>change;	
	for (i=0;i<15;i++)
	{
		if(change==p[i].code )
		{
			return true;
		}		
	}
	return false;
}
void employee :: change_pd()
{
	int i;
	bool status = change();
	if(!status)
	{
		cout<<"\nEORROR!!!\nWRONG PASSWORD ENTERED\n";
	}
	else
	{
		cout<<"\nYOU HAVE SUCCESFULLY VERIFIED YOURSELF"<<endl;
		string pass,pass1;
		cout<<"ENTER YOUR NEW PASSWORD "<<endl;
		cin>>pass1;
		// to change in struct 
		for (i=0;i<15;i++)
		{
			p[i].pd=pass1;		
		}
		//to change in file
		ofstream outf("pdfile.txt");
		for(int i=0;i<15;i++)
		{
			outf<<p[i].us<<endl;
			outf<<p[i].pd<<endl;
			outf<<p[i].code<<endl;
			cout<<endl;
		}
		outf.close();
	}
}

//*********************************************************ADMIN FUNCTIONS************************************************************************

//*********************************************************LOGIN************************************************************************

void admin::login()
{
	system ("cls");
	system("color 2F");
	cout<<"\n\nPLEASE ENTER YOUR ADMINISTRATIVE CREDENTIALS "<<endl;
	string username ;
	string password ;
	cout<<"\nPLEASE ENTER YOUR USERNAME : ";
	cin>>username;
	cout<<"\nPLEASE ENTER YOUR PASSWORD : ";
	cin>>password;
	
	if(username=="admin" && password=="admin123")
	{
		cout<<"Welcome to the Portal "<<endl;
	}
	else 
	{
		cout<<"\nSorry invalid credetials \n";
		system("PAUSE");
	}

}

//*********************************************************SELF DATA************************************************************************

void admin::selfdata_display()
{
	system ("cls ");
	system ("color 5F");
	struct emp e[15];
	ifstream inf("draft_selfdata.txt");
	for ( int i=0;i<15;i++)
	{
		inf>>e[i].empno;
		inf>>e[i].name;
		inf>>e[i].dept;
		inf>>e[i].desg;
		inf>>e[i].year;
		inf>>e[i].sal;
	}
	cout<<"\n\n********************* DISPLAYING EMPLOYEE DETAILS ************************* \n\n"<<endl;
	cout<<"EMP_NO"<<setw(15)<<"NAME"<<setw(20)<<"DEPT"<<setw(25)<<"DESG"<<setw(15)<<"YEAR"<<setw(15)<<"SAL"<<endl;
	for ( int i=0;i<15;i++)
	{
		cout<<"\n---------------------------------------------------------------------------------------------------------------"<<endl;
		cout<<e[i].empno<<setw(20)<<e[i].name<<setw(20)<<e[i].dept<<setw(25)<<e[i].desg<<setw(15)<<e[i].year<<setw(15)<<e[i].sal<<endl;
	}
	inf.close();
	system("PAUSE");
	system("cls");	
}

//*********************************************************LEAVE APPLICATION************************************************************************

void admin :: leave_apply()
{
	system("cls");
	system(" color 3F");
	cout<<"\n\t\t\tLEAVE APPLICATION"<<endl;
	read_leave();
	///// leave approval
	if (r==f)
 	{
 		cout<<"NO PENDING APPLICATION\n\n";
	}
	else  
	{
		l[f+1].status="Approved";
		cout<<"\n\nApproved leave for : \n"<<endl;
		cout<<l[f+1].empno<<"\t\t"<<l[f+1].name<<endl;
		f++;
	}
	write_leave();
	system("PAUSE");
}
//*********************************************************SORT DATA************************************************************************

void admin :: sort_data()
{
	system("cls");
	system(" color 1F");
	cout<<"\n\n\t\t\tSORTING EMPLOYEE DATA ON THE BASIS OF YEAR OF JOINING\n\n "<<endl;
	int i ,j;
	struct emp temp;
	struct emp e[15];
	ifstream inf("draft_selfdata.txt");
	for ( int i=0;i<15;i++)
	{
		inf>>e[i].empno;
		inf>>e[i].name;
		inf>>e[i].dept;
		inf>>e[i].desg;
		inf>>e[i].year;
		inf>>e[i].sal;
	}

	for  (i=0;i<14 ;i++)         
	{
		for (j=0;j<14-i;j++)
		{
			if (e[j].year>e[j+1].year)
			{
				temp=e[j];
				e[j]=e[j+1];
				e[j+1]=temp;
			}
		}
	}
	cout<<"\n\n********************* DISPLAYING EMPLOYEE DETAILS ************************* \n\n"<<endl;
	cout<<"EMP_NO"<<setw(15)<<"NAME"<<setw(20)<<"DEPT"<<setw(25)<<"DESG"<<setw(15)<<"YEAR"<<setw(15)<<"SAL"<<endl;
	for ( int i=0;i<15;i++)
	{
		cout<<"\n---------------------------------------------------------------------------------------------------------------"<<endl;
		cout<<e[i].empno<<setw(20)<<e[i].name<<setw(20)<<e[i].dept<<setw(25)<<e[i].desg<<setw(15)<<e[i].year<<setw(15)<<e[i].sal<<endl;
	}
	system("PAUSE");		
}

//*********************************************************ANNUAL SALES SORT************************************************************************

void company_sales_profit2022()
{
	system("color B");
	string pn1,pn2,pn3,pn4,pn5;
	float c1,c2,c3,c4,c5;
	int u1,u2,u3,u4,u5;
	int s1,s2,s3,s4,s5;
	long long int t1,t2,t3,t4,t5,total_c,total_s,profit,x1,x2,x3,x4,x5;
	ifstream read;
	read.open("company2022.txt");
	getline(read,pn1);
	getline(read,pn2);
	getline(read,pn3);
	getline(read,pn4);
	getline(read,pn5);
	read>>c1>>c2>>c3>>c4>>c5;
	read>>s1>>s2>>s3>>s4>>s5;

	cout<<"Enter how many Television units are Sold:"; cin>>u1;
	cout<<"Enter how many Laptop units are Sold:"; cin>>u2;
	cout<<"Enter how many AC units are Sold:"; cin>>u3;
	cout<<"Enter how many Adapter units are Sold:"; cin>>u4;
	cout<<"Enter how many Washing Machine units are Sold:"; cin>>u5; cout<<"\n";
	t1=u1*s1;
	t2=u2*s2;
	t3=u3*s3;
	t4=u4*s4;
	t5=u5*s5;
	
	cout<<"---------------------------------------------------------------------------------------------------------------"<<endl;
	cout<<"------------------------------------------------COMPANY SALES(2022)--------------------------------------------"<<endl;
	cout<<"---------------------------------------------------------------------------------------------------------------"<<endl;
	cout<<" SR.No\tPRODUCT\t\t\tCOST PRICE(Rs)\t\tSELLING PRICE(Rs)\tUNITS\t\tTOTAL PRICE(Rs)"<<endl<<"---------------------------------------------------------------------------------------------------------------"<<endl;
	cout<<" 1.\t"<<pn1<<"\t\t"<<c1<<"\t\t\t"<<s1<<"\t\t\t"<<u1<<"\t\t"<<t1<<endl<<"---------------------------------------------------------------------------------------------------------------"<<endl;
	cout<<" 2.\t"<<pn2<<"\t\t\t"<<c2<<"\t\t\t"<<s2<<"\t\t\t"<<u2<<"\t\t"<<t2<<endl<<"---------------------------------------------------------------------------------------------------------------"<<endl;
	cout<<" 3.\t"<<pn3<<"\t\t\t"<<c3<<"\t\t\t"<<s3<<"\t\t\t"<<u3<<"\t\t"<<t3<<endl<<"---------------------------------------------------------------------------------------------------------------"<<endl;
	cout<<" 4.\t"<<pn4<<"\t\t\t"<<c4<<"\t\t\t"<<s4<<"\t\t\t"<<u4<<"\t\t"<<t4<<endl<<"---------------------------------------------------------------------------------------------------------------"<<endl;
	cout<<" 5.\t"<<pn5<<"\t\t"<<c5<<"\t\t\t"<<s5<<"\t\t\t"<<u5<<"\t\t"<<t5<<endl<<"---------------------------------------------------------------------------------------------------------------"<<endl;
	total_c=c1*u1+c2*u2+c3*u3+c4*u4+c5*u5;
	total_s=s1*u1+s2*u2+s3*u3+s4*u4+s5*u5;
	profit=total_s-total_c;
	
	cout<<"The Total Profit made in the Year 2022 is:"<<profit<<endl<<endl<<endl;
	
	x1=s1*u1-c1*u1;
	x2=s2*u2-c2*u2;
	x3=s3*u3-c3*u3;
	x4=s4*u4-c4*u4;
	x5=s5*u5-c5*u5;
	int arr[5]={x1,x2,x3,x4,x5};
	for(int i=0;i<5;i++)
	{
		int currentelement=arr[i];
		int j=i-1;
		while(arr[j]>currentelement && j>=0){
			arr[j+1]=arr[j];
			j--;	
		}
		arr[j+1]=currentelement;
	}
	cout<<"The highest Profit was made by selling "<<pn5<<" and the profit was:"<<arr[4]<<endl<<endl<<endl;
	system("PAUSE");
}
void company_sales_profit2020()
{
	system("color B");
	string pn1,pn2,pn3,pn4,pn5;
	float c1,c2,c3,c4,c5;
	int u1,u2,u3,u4,u5;
	int s1,s2,s3,s4,s5;
	long long int t1,t2,t3,t4,t5,total_c,total_s,profit,x1,x2,x3,x4,x5;
	ifstream read;
	read.open("company2020.txt");
	getline(read,pn1);
	getline(read,pn2);
	getline(read,pn3);
	getline(read,pn4);
	getline(read,pn5);
	read>>c1>>c2>>c3>>c4>>c5;
	read>>s1>>s2>>s3>>s4>>s5;
	read>>u1>>u2>>u3>>u4>>u5;
	t1=u1*s1;
	t2=u2*s2;
	t3=u3*s3;
	t4=u4*s4;
	t5=u5*s5;
	
	cout<<"---------------------------------------------------------------------------------------------------------------"<<endl;
	cout<<"------------------------------------------------COMPANY SALES(2020)--------------------------------------------"<<endl;
	cout<<"---------------------------------------------------------------------------------------------------------------"<<endl;
	cout<<" SR.No\tPRODUCT\t\t\tCOST PRICE(Rs)\t\tSELLING PRICE(Rs)\tUNITS\t\tTOTAL PRICE(Rs)"<<endl<<"---------------------------------------------------------------------------------------------------------------"<<endl;
	cout<<" 1.\t"<<pn1<<"\t\t\t"<<c1<<"\t\t\t"<<s1<<"\t\t\t"<<u1<<"\t\t"<<t1<<endl<<"---------------------------------------------------------------------------------------------------------------"<<endl;
	cout<<" 2.\t"<<pn2<<"\t\t\t"<<c2<<"\t\t\t"<<s2<<"\t\t\t"<<u2<<"\t\t"<<t2<<endl<<"---------------------------------------------------------------------------------------------------------------"<<endl;
	cout<<" 3.\t"<<pn3<<"\t\t"<<c3<<"\t\t\t"<<s3<<"\t\t\t"<<u3<<"\t\t"<<t3<<endl<<"---------------------------------------------------------------------------------------------------------------"<<endl;
	cout<<" 4.\t"<<pn4<<"\t\t"<<c4<<"\t\t\t"<<s4<<"\t\t\t"<<u4<<"\t\t"<<t4<<endl<<"---------------------------------------------------------------------------------------------------------------"<<endl;
	cout<<" 5.\t"<<pn5<<"\t\t\t"<<c5<<"\t\t\t"<<s5<<"\t\t\t"<<u5<<"\t\t"<<t5<<endl<<"---------------------------------------------------------------------------------------------------------------"<<endl;
	total_c=c1*u1+c2*u2+c3*u3+c4*u4+c5*u5;
	total_s=s1*u1+s2*u2+s3*u3+s4*u4+s5*u5;
	profit=total_s-total_c;
	
	cout<<"The Total Profit made in the Year 2020 is:"<<profit<<endl<<endl<<endl;
	
	x1=s1*u1-c1*u1;
	x2=s2*u2-c2*u2;
	x3=s3*u3-c3*u3;
	x4=s4*u4-c4*u4;
	x5=s5*u5-c5*u5;
	int arr[5]={x1,x2,x3,x4,x5};
	for(int i=0;i<5;i++)
	{
		int currentelement=arr[i];
		int j=i-1;
		while(arr[j]>currentelement && j>=0){
			arr[j+1]=arr[j];
			j--;	
		}
		arr[j+1]=currentelement;
	}
	cout<<"The highest Profit was made by selling "<<pn5 <<" and the profit was:"<<arr[4]<<endl<<endl<<endl;
	system("PAUSE");
}
void company_sales_profit2021()
{
	system("color B");
	string pn1,pn2,pn3,pn4,pn5;
	float c1,c2,c3,c4,c5;
	int u1,u2,u3,u4,u5;
	int s1,s2,s3,s4,s5;
	long long int t1,t2,t3,t4,t5,total_c,total_s,profit,x1,x2,x3,x4,x5;
	ifstream read;
	read.open("company2021.txt");
	getline(read,pn1);
	getline(read,pn2);
	getline(read,pn3);
	getline(read,pn4);
	getline(read,pn5);
	read>>c1>>c2>>c3>>c4>>c5;
	read>>s1>>s2>>s3>>s4>>s5;
	read>>u1>>u2>>u3>>u4>>u5;
	t1=u1*s1;
	t2=u2*s2;
	t3=u3*s3;
	t4=u4*s4;
	t5=u5*s5;
	
	cout<<"---------------------------------------------------------------------------------------------------------------"<<endl;
	cout<<"------------------------------------------------COMPANY SALES(2021)--------------------------------------------"<<endl;
	cout<<"---------------------------------------------------------------------------------------------------------------"<<endl;
	cout<<" SR.No\tPRODUCT\t\t\tCOST PRICE(Rs)\t\tSELLING PRICE(Rs)\tUNITS\t\tTOTAL PRICE(Rs)"<<endl<<"---------------------------------------------------------------------------------------------------------------"<<endl;
	cout<<" 1.\t"<<pn1<<"\t\t\t"<<c1<<"\t\t\t"<<s1<<"\t\t\t"<<u1<<"\t\t"<<t1<<endl<<"---------------------------------------------------------------------------------------------------------------"<<endl;
	cout<<" 2.\t"<<pn2<<"\t\t"<<c2<<"\t\t\t"<<s2<<"\t\t\t"<<u2<<"\t\t"<<t2<<endl<<"---------------------------------------------------------------------------------------------------------------"<<endl;
	cout<<" 3.\t"<<pn3<<"\t\t"<<c3<<"\t\t\t"<<s3<<"\t\t\t"<<u3<<"\t\t"<<t3<<endl<<"---------------------------------------------------------------------------------------------------------------"<<endl;
	cout<<" 4.\t"<<pn4<<"\t\t"<<c4<<"\t\t\t"<<s4<<"\t\t\t"<<u4<<"\t\t"<<t4<<endl<<"---------------------------------------------------------------------------------------------------------------"<<endl;
	cout<<" 5.\t"<<pn5<<"\t\t"<<c5<<"\t\t\t"<<s5<<"\t\t\t"<<u5<<"\t\t"<<t5<<endl<<"---------------------------------------------------------------------------------------------------------------"<<endl;
	total_c=c1*u1+c2*u2+c3*u3+c4*u4+c5*u5;
	total_s=s1*u1+s2*u2+s3*u3+s4*u4+s5*u5;
	profit=total_s-total_c;
	
	cout<<"The Total Profit made in the Year 2021 is:"<<profit<<endl<<endl<<endl;
	
	x1=s1*u1-c1*u1;x2=s2*u2-c2*u2;x3=s3*u3-c3*u3;x4=s4*u4-c4*u4;x5=s5*u5-c5*u5;
	int arr[5]={x1,x2,x3,x4,x5};
	for(int i=0;i<5;i++)
	{
		int currentelement=arr[i];
		int j=i-1;
		while(arr[j]>currentelement && j>=0){
			arr[j+1]=arr[j];
			j--;	
		}
		arr[j+1]=currentelement;
	}
	cout<<"The highest Profit was made by selling "<<pn4 <<" and the profit was:"<<arr[4]<<endl<<endl<<endl;
	system("PAUSE");
}
void admin::annual_sort()
{
	int ch;
	system("cls");
	system("color B");
	cout<<"**************SALES***************"<<endl;
	cout<<"1.View the Sales of the Year 2020."<<endl;
	cout<<"2.View the Sales of the Year 2021."<<endl;
	cout<<"3.View the Sales of the Year 2022."<<endl;
	cout<<"4.Exit"<<endl;
	cout<<"Enter the choice:";
	cin>>ch;
	switch(ch)
	{
		case 1:
			company_sales_profit2020();
			break;
		case 2:
			company_sales_profit2021();
			break;
		case 3:
			company_sales_profit2022();
			break;
		case 4 :
			break;
		default:
			cout<<"Enter a valid choice."<<endl;
	}
}

//*********************************************************ANNUAL SALES SORT************************************************************************

int main()
{
	//pre req for queue : Updating the Queue parameters
	string line;
	int count=0 ,count1=0;
	string empno;
	string name ;
	string status;
	ifstream inf1("leave_file.txt");
	while(inf1.peek()!=EOF)
	{
		getline(inf1, line);
		count++;
	}
	inf1.close();
	
	ifstream inf("leave_file.txt");
	while(inf.peek()!=EOF)
	{
		inf>>empno;
		inf>>name;
		inf>>status;
		if (status =="Approved")
		{
			count1++;
		}
	}	
	inf.close();
		
	total_leave=count/3;
	r=total_leave-1;
	f=count1-1;
	//************************************************int main*****************************************************
	employee a1;
	admin a2;
    cout<<endl<<endl<<endl;
    cout<<"\t\t\t****************************************************************************************\n\n";
    cout<<"\t\t\t                                         MENU   \n\n";
    cout<<"\t\t\t****************************************************************************************";
	cout<<("\n\n\n\t\t\tENTER 1 TO LOGIN AS EMPLOYEE\n\t\t\tENTER 2 TO LOGIN AS ADMIN")<<endl;
	cout<<"\n\n\t\t\tENTER YOUR CHOICE :\t\t";
	int ch,ch2,ch3;
	cin>>ch;
	switch(ch)
	{
		case 1:
			a1.login(); 
			while(1)
			{
				system("cls");
				system("color 5F");
				cout<<"\n\t\t\t***********************************MENU************************************\n"<<endl;
				cout<<("\n\t\t\t1.To-do list\n\t\t\t2.Self-data display\n\t\t\t3.Leave application\n\t\t\t4.Change password\n\t\t\t5.Logout");
				cout<<"\n\n\t\t\tENTER YOUR CHOICE : ";
				cin>>ch2;
				switch(ch2)
				{
					case 1:
						a1.to_dolist();
						break;
				
					case 2:
						a1.selfdata_display();
						break;
						
					case 3:
					    a1.leave_apply();
					    break;
						
					case 4:
						a1.change_pd();
						break;
					
					case 5:
						cout<<"YOU HAVE SUCCESFULLY LOGGED OUT"<<endl;
						exit(0);
				}
			}
			
			
			break;
			
		case 2:
			a2.login(); // admin login
			while(1)
			{
				system("cls");
				system("color 5F");
				cout<<"\n***********************************MENU************************************\n"<<endl;
				cout<<"\n\t\t\t1.Self-data display\n\t\t\t2.Leave Application \n\t\t\t3.Sort data \n\t\t\t4.Annual sales display \n\t\t\t5.Logout "<<endl;
				cout<<"\t\t\t\nENTER YOUR CHOICE : ";
				cin>>ch3;
				switch(ch3)
				{
					case 1:
						a2.selfdata_display();
						break;
			
					case 2:
						a2.leave_apply();
						break;
				
					case 3:
					    a2.sort_data();
						break;
						
					case 4 :
						a2.annual_sort();
					    break;
					
					case 5 :
						cout<<"YOU HAVE SUCCESFULLY LOGGED OUT"<<endl;
						exit(0);
				}	
			}	
	}
}
