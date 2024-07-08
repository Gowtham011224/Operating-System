#include<iostream>
using namespace std;
#include"firstfit.hpp"
#include"bestfit.hpp"
#include"worstfit.hpp"

int main()
{
int m, n;
    cout << "Enter the number of blocks: ";
    cin >> m;
    int blockSize[m];
    cout << "Enter the sizes of blocks:\n";
    for (int i = 0; i < m; ++i)
    {	
	cout << "Block "<<i+1<<":";
        cin >> blockSize[i];
    }

    cout << "Enter the number of processes: ";
    cin >> n;
    int blockSize1[m];
    for (int i = 0; i < m; ++i)
    {
     blockSize1[i]=blockSize[i];  
    }
    int processSize[n];int t;
    cout << "Enter the sizes of processes:\n";
    for (int i = 0; i < n; ++i)
    {
	while(true)
	{
	    cout<< "Process"<<i+1<<":";
            cin >> t;
	    if(t>0)
		    break;
	    cout<<"Size needs to be positive!"<<endl;
	}
	processSize[i]=t;
    }	

do{
cout<<"Menu:"<<endl;
int ch;
cout<<"1.First fit\n2.Best fit\n3.Worst fit\n4.Exit\nYour choice:";
cin>>ch;
switch(ch)
{
	case 1:
		one(blockSize, m, processSize, n);
		for (int i = 0; i < m; ++i)
    {
     blockSize[i]=blockSize1[i];
    }
		break;
	case 2:
		two(blockSize, m, processSize, n);
		for (int i = 0; i < m; ++i)
    {
     blockSize[i]=blockSize1[i];
    }
		break;
	case 3:
		three(blockSize, m, processSize, n);
		for (int i = 0; i < m; ++i)
    {
     blockSize[i]=blockSize1[i];
    }
		break;
	case 4:
		cout<<"Exiting.."<<endl;
		return 0;
	default:
		cout<<"Invalid Input";
}
}while(true);
return 0;
}
