#include <iostream>

using namespace std;

void bestFit(int blockSize[], int m, int processSize[], int n)
{
    int allocation[n];

    for(int i = 0; i < n; i++)
    {
        int bestBlockIndex = -1; // Initialize index of best fit block for current process
        for(int j = 0; j < m; j++)
        {
            if(blockSize[j] >= processSize[i])
            {
                if(bestBlockIndex == -1 || blockSize[j] < blockSize[bestBlockIndex])
                {
                    bestBlockIndex = j; // Update index of best fit block
                }
            }
        }

        if(bestBlockIndex != -1)
        {
            allocation[i] = bestBlockIndex + 1; // Allocate the process to best fit block
            blockSize[bestBlockIndex] -= processSize[i]; // Update block size
        }
        else
        {
            allocation[i] = 0; // Mark process as not allocated if no suitable block found
        }
    }

    cout << endl << " Process Table:\nProcess No.\tProcess Size\tBlock no.\n";
    for(int i = 0; i < n; i++)
    {
        cout << " " << i + 1 << "\t\t" << processSize[i] << "\t\t";
        if(allocation[i] != 0)
            cout << allocation[i];
        else
            cout << "Not Allocated";
        cout << endl;
    }

    cout << endl << " Block Table After:\nBlock No.\tBlock Size\t\n";
    for(int i = 0; i < m; i++)
    {
        cout << " " << i + 1 << "\t\t" << blockSize[i] << "\t\t";
        cout << endl;
    }
}

void two(int blockSize[],int m,int processSize[], int n)
{
       cout << endl << "Block Table Before:\nBlock No.\tBlock Size\t\n";
    for(int i = 0; i < m; i++)
    {
        cout << " " << i + 1 << "\t\t" << blockSize[i] << "\t\t";
        cout << endl;
    }
    bestFit(blockSize, m, processSize, n);

    int rem = 0;
    for(int i = 0; i < m; i++)
        rem += blockSize[i];
    cout << "Remaining unused space due to fragmentation: " << rem << endl;

    return ;
}
