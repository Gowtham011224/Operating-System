#include <iostream>

using namespace std;

void firstFit(int blockSize[], int m, int processSize[], int n)
{
    int allocation[n];
    int t;
    for (int i = 0; i < n; i++)
    {
	t=0;
        for (int j = 0; j < m; j++)
        {
            if (blockSize[j] >= processSize[i])
            {   
		t=1;
                allocation[i] = j+1;
                blockSize[j] -= processSize[i];
                break;
            }
        }
	if(t==0)
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

void one(int blockSize[],int m,int processSize[], int n)
{
   
    cout <<endl<<" Block Table Before:\nBlock No.\tBlock Size\t\n";
    for (int i = 0; i < m; i++)
    {
        cout << " " << i + 1 << "\t\t" << blockSize[i] << "\t\t";
        cout << endl;
    }
    firstFit(blockSize, m, processSize, n);
    int rem=0;
    for(int i=0;i<m;i++)
    	rem+=blockSize[i];
    cout<<"Remaining unused space due to fragmentation:"<<rem<<endl;
    return ;
}


