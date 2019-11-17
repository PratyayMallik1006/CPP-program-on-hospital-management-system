#include<iostream.h>
#include<conio.h>
#include<fstream.h>
#include<stdio.h>
#include<iomanip.h>

class hospital
{
    int PatientId;
    char name[30];
    char address[50];
    char BloodGrp[5];

    public:
    void main_menu();    //to dispay the main menu
    void add();        //to Admit a patient
    void display();    //to display the patient record
    void Patients();    //to display admited patient
    void edit();    //to edit the patient record
    int check(int);    //to check room status
    void modify(int);    //to modify the record
    void delete_rec(int);    //to delete the record
};

void hospital::main_menu()
{
	  int choice=0;

	 do
    {
		  clrscr();
		  cout<<"\n\t\t\t\t*************";
	cout<<"\n\t\t\t\t* MAIN MENU *";
	cout<<"\n\t\t\t\t*************";
	cout<<"\n\n\n\t\t\t1.Admit a patient";
	cout<<"\n\t\t\t2.patient Record";
	cout<<"\n\t\t\t3.Admited Patients";
	cout<<"\n\t\t\t4.Edit Record";
	cout<<"\n\t\t\t5.Exit";
	cout<<"\n\n\t\t\tEnter Your Choice: ";
	cin>>choice;

	switch(choice)
	{
	    case 1: add();
		    break;
	    case 2: display();
		    break;
	    case 3: Patients();
		    break;
	    case 4: edit();
		    break;
	    case 5: break;
	    default:
		    {
			cout<<"\n\n\t\t\tWrong choice!!!";
			cout<<"\n\t\t\tPress any key to continue!!";
			getch();
		    }
	}
    } while(choice!=5);

}
void hospital::add()
{
    clrscr();
    int r,flag;
    ofstream fout("Record.dat",ios::app);

    cout<<"\n Enter Patient Detalis";
    cout<<"\n **********************";
    cout<<"\n\n Patient Id: ";
    cin>>r;
    flag=check(r);

    if(flag)
	cout<<"\n This Patient is already admited!!!";
    else
    {
	PatientId=r;
	cout<<" Name: ";
	gets(name);
	cout<<" Address: ";
	gets(address);
	cout<<" Blood Grp : ";
	gets(BloodGrp);
	fout.write((char*)this,sizeof(hospital));
	cout<<"\n Patient is admited!!!";
    }

    cout<<"\n Press any key to continue!!";
    getch();
    fout.close();
}

void hospital::display()
{
    clrscr();
    ifstream fin("Record.dat",ios::in);
    int r,flag;
    cout<<"\n Enter PatientId: ";
    cin>>r;

    while(!fin.eof())
    {
	fin.read((char*)this,sizeof(hospital));
	if(PatientId==r)
	{
	    clrscr();
	    cout<<"\n Patient Details";
	    cout<<"\n ****************";
				cout<<"\n\n PatientId: "<<PatientId;
				cout<<"\n Name: "<<name;
				cout<<"\n Address:"<<address;
				cout<<"\n BloodGrp no: "<<BloodGrp;
	    flag=1;
	    break;
	}
    }

    if(flag==0)
	cout<<"\n Sorry PatientId. not found!!";

    cout<<"\n\n Press any key to continue!!";
    getch();
    fin.close();
}

void hospital::Patients()
{
    clrscr();
    ifstream fin("Record.dat",ios::in);
    cout<<"\n\t\t\tList Of Patients Admited";
    cout<<"\n\t\t\t*********************";
	 cout<<"\n\n"<<setw(5)<<" PatientId."<<setw(15)<<"Name"<<setw(25)<<"Address"<<setw(29)<<"Blood Grp\n\n";

	 while(!fin.eof())
	 {
	fin.read((char*)this,sizeof(hospital));
		  cout<<setw(5)<<PatientId<<setw(18)<<name;
		  cout<<setw(25)<<address<<setw(28)<<BloodGrp;
    }

    cout<<"\n\n\n\t\t\tPress any key to continue!!";
    getch();
    fin.close();
}

void hospital::edit()
{
    clrscr();
    int choice,r;

    cout<<"\n EDIT MENU";
    cout<<"\n *********";
    cout<<"\n\n 1.Modify Patient Record";
    cout<<"\n 2.Delete Patient Record";

    cout<<"\n Enter your choice: ";
    cin>>choice;

    clrscr();
    cout<<"\n Enter PatientId: ";
    cin>>r;

    switch(choice)
    {
	case 1: modify(r);
		break;
	case 2: delete_rec(r);
		break;
	default: cout<<"\n Wrong Choice!!";
    }

    cout<<"\n Press any key to continue!!!";
    getch();
}

int hospital::check(int r)
{
    int flag=0;
    ifstream fin("Record.dat",ios::in);
    while(!fin.eof())
    {
	fin.read((char*)this,sizeof(hospital));
	if(PatientId==r)
	{
	    flag=1;
		break;
	}
    }

    fin.close();
    return(flag);
}
 
void hospital::modify(int r)
{
    long pos,flag=0;
    fstream file("Record.dat",ios::in|ios::out|ios::binary);
    
    while(!file.eof())
    {
        pos=file.tellg();
        file.read((char*)this,sizeof(hospital));
        if(PatientId==r)
        {
            cout<<"\n Enter New Details";
            cout<<"\n *****************";
            cout<<"\n Name: ";
            gets(name);
            cout<<" Address: ";
            gets(address);
            cout<<" BloodGrp no: ";
            gets(BloodGrp);
            
            file.seekg(pos);
            file.write((char*)this,sizeof(hospital));
            cout<<"\n Record is modified!!";
            flag=1;
            break;
        }
    }
    
    if(flag==0)
        cout<<"\n Sorry PatientId. not found!!";
        
    file.close();
}

 
void hospital::delete_rec(int r)
{
    int flag=0;
    char ch;
    ifstream fin("Record.dat",ios::in);
    ofstream fout("temp.dat",ios::out);
    
    while(!fin.eof())
    {
        fin.read((char*)this,sizeof(hospital));
        if(PatientId==r)
        {
            cout<<"\n Name: "<<name;
            cout<<"\n Address: "<<address;
            cout<<"\n Pone No: "<<BloodGrp;
            cout<<"\n\n Do you want to delete this record(y/n): ";
            cin>>ch;
            
            if(ch=='n')
            fout.write((char*)this,sizeof(hospital));
            
            flag=1;
        }
        else
            fout.write((char*)this,sizeof(hospital));
    }
    
    fin.close();
    fout.close();
    
    if(flag==0)
        cout<<"\n Sorry PatientId. not found!!";
    else
    {
        remove("Record.dat");
        rename("temp.dat","Record.dat");
    }
}
 
void main()
{
    hospital h;
    
    clrscr();
    cout<<"\n\t\t\t****************************";
    cout<<"\n\t\t\t* HOSPITAL  MANAGEMENT PROJECT *";
    cout<<"\n\t\t\t****************************";

    
    cout<<"\n\n\n\n\t\tMade By:";

    cout<<"1. Pratyay Mallik\n\t\t\t2.Biswarup Ray\n\t\t\t3. Debanjana\n\t\t\t4.Achintiya Pandey";

    cout<<"\n\n\n\n\n\t\t\t\tPress any key to continue!!";
    getch();
    h.main_menu();
}
