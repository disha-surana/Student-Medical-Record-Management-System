#include<fstream.h>
#include<conio.h>
#include<string.h>
#include<stdio.h>
#include<dos.h>

class st_med
{
int admno,sclass;
char name[25],bloodgr[4];
float weight,height;

public:

void input();
void output()
{
	cout<<"\n\t"<<admno<<"\t"<<name<<"\t"<<bloodgr<<"\t\t"<<weight<<"\t"<<height<<"\t"<<sclass;
}
int get_admno()
{
	return admno;
}
int get_class()
{
	return sclass;
}
int get_bg();
};
int st_med::get_bg()
{
	if(strcmpi(bloodgr,"a+")==0)
	return(1);
	else
	if(strcmpi(bloodgr,"a-")==0)
	return(-1);
	else
	if(strcmpi(bloodgr,"b+")==0)
	return(2);
	else
	if(strcmpi(bloodgr,"b-")==0)
	return(-2);
	else
	if(strcmpi(bloodgr,"o+")==0)
	return(3);
	else
	if(strcmpi(bloodgr,"o-")==0)
	return(-3);
	else
	if(strcmpi(bloodgr,"ab+")==0)
	return(4);
	else
	if(strcmpi(bloodgr,"ab-")==0)
	return(-4);

	return -999;

}

void st_med::input()
{
cout<<"\n\n\t Enter admission number";
cin>>admno;
cout<<"\n\t Enter name of student";
gets(name);
cout<<"\n\t Enter blood group of student";
cin>>bloodgr;
cout<<"\n\t Enter weight in kg of student";
cin>>weight;
cout<<"\n\t Enter height in cm of student";
cin>>height;
cout<<"\n\t Enter class of student";
cin>>sclass;
}
void main()
{
	st_med ob;
	int choice,n,flag,loc,small;
	fstream file,file1,file2;
	char ch1[3],ch;
	double n_record;

	clrscr();
	cout<<"\n\n\t \t\t\t   WELCOME \n";
	delay(1200);

	do
	{
	cout<<"\n\t\t\t RAMJAS STUDENTS MEDICAL RECORDS :";

	cout<<"\n\n\n\t\t MENU\n";
	cout<<"\n\t 1 to add record";
	cout<<"\n\t 2 to add record from beginning";
	cout<<"\n\t 3 to display all records";
	cout<<"\n\t 4 to display a particular record";
	cout<<"\n\t 5 to modify a record";
	cout<<"\n\t 6 to delete a record ";
	cout<<"\n\t 7 to count total no. of records";
	cout<<"\n\t 8 to display records of a particular class";
	cout<<"\n\t 9 to display records of a particular bloodgroup";
	cout<<"\n\t 10 to quit";

	cout<<"\n\n\t Enter choice";
	cin>>choice;

	switch(choice)
	{
	//Adding records
		case 1:

		file.open("medical.dat",ios::app|ios::binary);

		clrscr();
		cout<<"\n\t\t\t RAMJAS STUDENTS MEDICAL RECORDS :";

		do
		{
			ob.input();
			file.write((char*)&ob,sizeof(ob));
			cout<<"\n\n\t more records (Y/N)";
			cin>>ch;
		}
		while(ch=='y'||ch=='Y');
		file.close();
		break;

		//adding records from beginning
		case 2:

		clrscr();
		cout<<"\n\t\t\t RAMJAS STUDENTS MEDICAL RECORDS :";

		file.open("medical.dat",ios::out|ios::binary);

		do
		{
			ob.input();
			file.write((char*)&ob,sizeof(ob));
			cout<<"\n\n\t more records (Y/N)";
			cin>>ch;
		}
		while(ch=='y'||ch=='Y');
		file.close();
		break;

		//display all records
		case 3:
		clrscr();
		cout<<"\n\t\t\t RAMJAS STUDENTS MEDICAL RECORDS :";

		file.open("medical.dat",ios::in|ios::binary);
		cout<<"\n\n\tAdmno\tName\t\tBloodgroup\tWeight\tHeight\tclass ";

		while(file.read((char*)&ob,sizeof(ob)))
		{
			ob.output();
		}

		file.close();
		break;

	       //display particular record
		case 4:

		cout<<"\n Enter admission no. of the student whose data to be displayed";
		cin>>n;

		clrscr();
		cout<<"\n\t\t RAMJAS STUDENTS MEDICAL RECORDS :";

		cout<<"\n\n\tAdmno\tName\t\tBloodgroup\tWeight\tHeight\tclass ";

		file.open("medical.dat",ios::in|ios::binary);


		while(file.read((char*)&ob,sizeof(ob)))
		{
			if(ob.get_admno()==n)
			ob.output();
		}

		file.close();
		break;

		//to modify a particular record
		case 5:

		clrscr();
		cout<<"\n\t\t\t RAMJAS STUDENTS MEDICAL RECORDS :";

		cout<<"\n Enter admission no. of student whose record to be modified";
		cin>>n;


		flag=0;
		file.open("medical.dat",ios::in|ios::ate|ios::out|ios::binary);
		file.seekg(0);

		while(file.read((char*)&ob,sizeof(ob)))
		{

			if(ob.get_admno()==n)
			{
				flag=1;
				loc=file.tellg();
				break;
			}
		}

		if(flag==1)
		{

			cout<<"\n\t Old Record";
			cout<<"\n\tAdmno\tName\t\tBloodgroup\tWeight\tHeight\tclass ";
			ob.output();
			cout<<"\n\tEnter modifications";
			ob.input();
			file.seekg(loc-sizeof(ob));

			file.write((char*)&ob,sizeof(ob));
			cout<<"\n\tModifications done\n";
			cout<<"\n\tAdmno\tName\t\tBloodgroup\tWeight\tHeight\tclass ";
			ob.output();

		}
		else
		{
			cout<<"\n\n\t Record not found";
		}
		file.close();
		break;

		//to delete a record
		case 6:
		clrscr();
		cout<<"\n\t\t\t RAMJAS STUDENTS MEDICAL RECORDS :";

		cout<<"\n\n\t Enter admission no. of the student whose record to be deleted";
		cin>>n;flag=0;

		file.open("medical.dat",ios::in|ios::binary);
		file1.open("temp.dat",ios::out|ios::binary);

		while(file.read((char*)&ob,sizeof(ob)))
		{
			if(ob.get_admno()==n)
			{
				flag=1;
				cout<<"\n\n\tRecord to be deleted:";
				cout<<"\n\n\tAdmno\tName\t\tBloodgroup\tWeight\tHeight\tclass ";
				ob.output();

			}
			else
			{
				file1.write((char*)&ob,sizeof(ob));
			}
		}
		file.close();
		file1.close();
		if(flag==0)
		{
			remove("temp.dat");
			cout<<"\n\n\t Record doesn't exist";
		}
		else
		{
			remove("medical.dat");
			rename("temp.dat","medical.dat");
			cout<<"\n\n\t Record deleted";
		}
		break;

		//to count records
		case 7:

		clrscr();
		cout<<"\n\t\t\t RAMJAS STUDENTS MEDICAL RECORDS :";

		file.open("medical.dat",ios::in|ios::binary);
		file.seekg(0,ios::end);

		n_record=file.tellg()/sizeof(ob);

		cout<<"\n\n\t Total records ="<<n_record;
		break;

		//display records according to class
		case 8:
		clrscr();
		cout<<"\n\t\t\t RAMJAS STUDENTS MEDICAL RECORDS :";

		cout<<"\n\n\t Enter class of the students whose data to be displayed";
		cin>>n;
		flag=0;
		cout<<"\n\n\tAdmno\tName\t\tBloodgroup\tWeight\tHeight\tclass ";

		file.open("medical.dat",ios::in|ios::binary);


		while(file.read((char*)&ob,sizeof(ob)))
		{
			if(ob.get_class()==n)
			{
			ob.output();
			flag=1;
			}
		}
		if(flag==0)
		cout<<"\n\n\t Records of class "<<n<<" does'nt exist";

		file.close();
		break;

		//display records of particular bloodgroup

		case 9:
		clrscr();
		cout<<"\n\t\t\t RAMJAS STUDENTS MEDICAL RECORDS :";

		cout<<"\n\n\t Enter bloodgroup of the students whose data to be displayed";
		cin>>ch1;


	if(strcmpi(ch1,"a+")==0)
	n=1;
	else
	if(strcmpi(ch1,"a-")==0)
	n=-1;
	else
	if(strcmpi(ch1,"b+")==0)
	n=2;
	else
	if(strcmpi(ch1,"b-")==0)
	n=-2;
	else
	if(strcmpi(ch1,"o+")==0)
	n=3;
	else
	if(strcmpi(ch1,"o-")==0)
	n=-3;
	else
	if(strcmpi(ch1,"ab+")==0)
	n=4;
	else
	if(strcmpi(ch1,"ab-")==0)
	n=-4;


		flag=0;
		file.open("medical.dat",ios::in|ios::binary);
		int i=0;

		while(file.read((char*)&ob,sizeof(ob)))
		{
			if(ob.get_bg()==n)
			{
				flag=1;
				i++;
			}
			else
			flag=0;
			if(flag==1)
			{
				if(i==1)
				{
				cout<<"\n\n\tAdmno\tName\t\tBloodgroup\tWeight\tHeight\tclass ";
				}
				ob.output();

			}



		}
		if(flag==0)
		cout<<"\n\n\t Records of students having "<<ch1<<" bloodgroup don't exist";

		file.close();
		break;


		case 10:
		cout<<"\n\n\t End of job";
		break;

		default:
		cout<<"\n\n\t Wrong choice";
	}
      cout<<"\n\t press any key";
      getch();

      clrscr();
      }
      while (choice!=10);
}














