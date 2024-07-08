#include<iostream>
using namespace std;

#include<random>
#include<list>
#include<string>

#define S 30
int N=S;

struct node
{
	int id;
	struct node* next;
	int nodenum;
	struct node* nextloc;
}*start=nullptr;

int menu()
{
	int ch;
	cout<<"Menu:\n1.Add file\n2.Display file details\n3.Display free spaces\n4.Display memory\n5.Exit\nEnter choice:";
	cin>>ch;
	return ch;
}

void createnode()
{
	struct node* n=(struct node*)malloc(sizeof(struct node));
	n->id=0;
	n->nodenum=N--;
	n->next=start;
	start=n;
}

void removejunk()
{
	struct node* trav=start->next;
	free(start);
	start=trav;
}

void displaymem()
{
	cout<<"Memory:\n";
	struct node* trav=start;
	for(int i=1;i<=S;i++)
	{
		cout<<trav->id<<"\t";
		if(i%5==0)
			cout<<endl;
		trav=trav->next;
	}
}

void displayfree()
{
	cout<<"Free available spaces:"<<endl;
	struct node* trav=start;
        for(int i=1;i<=S;i++)
        {
                if(trav->id==0)
                	cout<<trav->nodenum<<"\t";
                trav=trav->next;
        }
	cout<<endl;
}

int cas()
{
    int c = 0;
    struct node* trav = start;
    while (trav != nullptr)
    {
        if (trav->id == 0)
            c++;
        trav = trav->next;
    }
    return c;
}


int r()
{
	random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int>distribution(1,S);
	return distribution(gen);
}

list<string> names;
list<int> ids;

void checkavail(string name,int id,int si)
{
	int count=cas();
	cout<<"The free spaces count is:"<<cas()<<endl;
	if(si>count)
	{
		cout<<"Not enough memory availabe."<<endl;
		return;
	}
	list<int> avail;
	int a,f;
	struct node* trav;
	struct node* trav1;
	for(int i=0;i<si;i++)
	{	
		f=0;
		a=r();
		for(list<int>::iterator it=avail.begin();it!=avail.end();it++)
		{
			if(*it==a)
				f=1;
		}
		if(f==1)
		{
			i--;
			continue;
		}
		trav=start;
		while(trav->nodenum!=a)
			trav=trav->next;
		if(trav->id!=0)
		{
			i--;
			continue;
		}
		avail.push_front(a);
	}
	struct node* trav3=nullptr;
	for(list<int>::iterator i=avail.begin();i!=avail.end();i++)
	{
		trav1=start;
                while(trav1->nodenum!=*i)
                        trav1=trav1->next;
                trav1->id=id;
		trav1->nextloc=trav3;
		trav3=trav1;
	}
	names.push_back(name);
	ids.push_back(id);
	cout<<"Added"<<endl;
}

void getfile()
{
	string n;
	int i,si;
	cout<<"Enter file name:";
	cin>>n;
	cout<<"Enter file id:";
	cin>>i;
	cout<<"Enter file size:";
	cin>>si;
	checkavail(n,i,si);
}

void displaydetail()
{
	int t,f=0;
	cout<<"Enter the file id:";
	cin>>t;
	string na;
	for(list<int>::iterator i=ids.begin();i!=ids.end();i++)
        {
		if(*i==t)	
		       f=1;	
	}
	if(f==0)
	{
		cout<<"Invalid input"<<endl;
		return;
	}
	list<string>::iterator j=names.begin();
	for(list<int>::iterator i=ids.begin();i!=ids.end() && j!=names.end();i++,j++)
	{
		if(*i==t)
			na=*j;
	}
	cout<<endl;
	cout<<"File name:"<<na<<endl;
	cout<<"File id:"<<t<<endl;
	struct node* trav=start;
        for(int i=1;i<=S;i++)
        {
                if(trav->id==t)
                        cout<<trav->nodenum<<" --> ";
                trav=trav->next;
        }
	cout<<"NULL"<<endl;
}


int main()
{
	int ch;
	cout<<"Memory size is fixed to "<<S<<" units..(Can be changed in #define S)"<<endl;
	for(int i=1;i<=S;i++)
		createnode();
	
	while(true)
	{
		cout<<endl;
		ch=menu();
		cout<<endl;
		switch(ch)
		{
			case 1:
				getfile();
				break;
			case 2:
				displaydetail();
				break;
			case 3:
				displayfree();
				break;
			case 4:
				displaymem();
				break;
			case 5:
				cout<<"Exiting program...\n";
				return 0;
			default:
				cout<<"Invalid Input\n";
		}
	}
	
	for(int i=1;i<=S;i++)
		removejunk();
	return 0;
}
