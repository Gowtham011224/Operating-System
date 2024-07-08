#include <iostream>
#include <string>
#include <vector>
#define S 20
#define mod 5
using namespace std;

int hashFunction(int inp) 
{
    return inp % mod;
}

int main() {
    int numFiles;
    cout << "Starting no. of nodes for each index : "<< S <<endl;
    cout << "Enter the number of files: ";
    cin >> numFiles;

    vector<string> filenames;
    vector<int> fileSizes;

    for (int i = 0; i < numFiles; ++i) 
    {
        string filename;
        int fileSize;

        cout << "Enter the name of file " << i + 1 << ": ";
        cin >> filename;
        filenames.push_back(filename);

        cout << "Enter the size of file " << i + 1 << ": ";
        cin >> fileSize;
        fileSizes.push_back(fileSize);
    }

    vector<int> fileindex;
    for (int i = 0; i < numFiles; ++i) 
    {
        fileindex.push_back(hashFunction(filenames[i].length()));
    }
	
    vector<int> space;
    int size;
    for(int j=0; j<mod ; j++)
    {
	    size=0;
    for(int i=0; i<numFiles;++i)
    {	
	if(j==fileindex[i])
	{
		size+=fileSizes[i];
	}
    }
    	space.push_back(size);
    }
    
    for(int i=0;i<mod;i++)
    {	
	    cout<<endl;
	    cout<<i<<"th index:";
	    if(space[i]>20)
		    cout<<"(no of nodes increased than default)";
	    cout<<endl;
	    if(space[i]>0)
	    {
		    int st=0;
		    cout<<"File name(s):\t\tStart:\t\tFilesize:"<<endl<<endl;
	    for(int j=0;j<numFiles;j++)
	    {
		    if(fileindex[j]==i)
		    {
			    cout<<filenames[j]<<"\t\t\t"<<st<<"\t\t\t"<<fileSizes[j]<<endl;
			    st+=fileSizes[j];
		    }
	    }
	    cout<<"Total no. of nodes used : "<<st<<endl;
	    }
	    else
		    cout<<"No files"<<endl;
    }
    return 0;
}

