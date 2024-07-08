#include<iostream>
using namespace std;

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
                	cout<<trav->nodenum<<" -> ";
                trav=trav->next;
        }
	cout<<" null "<<endl;
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

list<string> names;
list<int> ids;
list<int> stloc;

void checkavail(string name,int id,int si,int st)
{
	int count=cas();
	cout<<endl<<"The free spaces before count is:"<<cas()<<endl;
	if(si>count)
	{
		cout<<"Not enough memory availabe."<<endl;
		return;
	}
	list<int> avail;
	int a=st;
	struct node* trav;
	struct node* trav1;
	for(int i=0;i<si;i++)
	{	
		trav=start;
		while(trav->nodenum!=a)
			trav=trav->next;
		if(trav->id!=0)
		{
			i--;
			a++;
			if(a==S+1)
				a=1;
			continue;
		}
		avail.push_front(a);
		a++;
		if(a==S+1)
			a=1;
	}

	cout<<endl<<"The free nodes chosen is/are:";
	for(list<int>::reverse_iterator i=avail.rbegin();i!=avail.rend();i++)
        {
		cout<<*i<<"  ";
	}
	cout<<endl<<endl;

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
	stloc.push_back(avail.back());
	cout<<"Added"<<endl;
	count=cas();
        cout<<endl<<"The free spaces after count is:"<<cas()<<endl;
}

void getfile()
{
	string n;
	int i,si,st;
	cout<<"Enter file name:";
	cin>>n;
	int f=0;
	cout<<"Enter file id:";
	cin>>i;
	while(true)
	{
		for(list<int>::iterator m=ids.begin();m!=ids.end();m++)
		{
			if(i==*m)
				f=1;
		}
		if(f==0)
			break;
		else
		{
			cout<<"ID already exist.Enter different ID:";
			cin>>i;
			f=0;
		}
	}
	cout<<"Enter file size:";
	cin>>si;
	if(si<=0)
	{
		cout<<"Invalid input"<<endl;
		return;
	}
	cout<<"Enter start node:";
	cin>>st;
	if(st>S && st<=0)
	{
		cout<<"Invalid Input"<<endl;
		return;
	}
	checkavail(n,i,si,st);
}

void displaydetail()
{
	int t,f=0;
	cout<<"Available file ids:";
	if(ids.empty())
	{
		cout<<endl<<"No files"<<endl;
		return;
	}
	for(list<int>::iterator i=ids.begin();i!=ids.end();i++)
        {
		cout<<*i<<"\t";
	}
	cout<<endl<<endl;
	cout<<"Enter the file id to know details:";
	cin>>t;
	string na;
	int startloc;
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
	list<int>::iterator k=stloc.begin();
	for(list<int>::iterator i=ids.begin();i!=ids.end();i++,j++,k++)
	{
		if(*i==t)
		{
			na=*j;
			startloc=*k;
		}
	}
	cout<<endl;
	cout<<"File name:"<<na<<endl;
	cout<<"File id:"<<t<<endl;
	cout<<"Allocation:"<<endl;
        struct node* trav=start;
	int i=startloc;
	while(trav->nodenum!=i)
        	trav=trav->next;
	while(trav!=nullptr)
	{
                cout<<trav->nodenum<<" --> ";
                trav=trav->nextloc;
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


