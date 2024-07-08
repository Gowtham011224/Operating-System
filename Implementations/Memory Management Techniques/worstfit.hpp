#include <iostream>

using namespace std;

void worstFit(int blockSize[], int m, int processSize[], int n)
{
    int allocation[n];
    int max=0;

    for(int i=0;i<n;i++)
    {
	for (int j = 1; j < m; j++)
    	{
		if(blockSize[j]>blockSize[max])
		max=j;
    	}
    	if(blockSize[max]>=processSize[i])
    	{
		allocation[i]=max+1;
		blockSize[max]-=processSize[i];
    	}
	else
		allocation[i]=0;
    }
    
    cout <<endl<< " Process Table:\nProcess No.\tProcess Size\tBlock no.\n";
    for (int i = 0; i < n; i++)
    {
        cout << " " << i + 1 << "\t\t" << processSize[i] << "\t\t";
        if (allocation[i] != 0)
            cout << allocation[i];
        else
            cout << "Not Allocated";
        cout << endl;
    }

    cout <<endl<< " Block Table After:\nBlock No.\tBlock Size\t\n";
    for (int i = 0; i < m; i++)
	    
    {
        cout << " " << i + 1 << "\t\t" << blockSize[i] << "\t\t";
        cout << endl;
    }	
}

void three(int blockSize[],int m,int processSize[], int n)
{
        cout <<endl<<" Block Table Before:\nBlock No.\tBlock Size\t\n";
    for (int i = 0; i < m; i++)
    {
        cout << " " << i + 1 << "\t\t" << blockSize[i] << "\t\t";
        cout << endl;
    }
    worstFit(blockSize, m, processSize, n);
    int rem=0;
    for(int i=0;i<m;i++)
    	    rem+=blockSize[i];
    cout<<"Remaining unused space due to fragmentation:"<<rem<<endl;
    return ;
}


