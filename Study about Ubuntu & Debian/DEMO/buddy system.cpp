#include<bits/stdc++.h>
using namespace std;

// Size of vector of pairs
int size;

// Global vector of pairs to store
// address ranges available in free list
vector<pair<int, int>> free_list[100000];

// Map used as hash map to store the starting
// address as key and size of allocated segment
// key as value
map<int, int> mp;

void initialize(int sz)
{
    // Maximum number of powers of 2 possible
    int n = ceil(log(sz) / log(2));
    ::size = n + 1;

    for(int i = 0; i <= n; i++)
        free_list[i].clear();

    // Initially whole block of specified
    // size is available
    free_list[n].push_back(make_pair(0, sz - 1));
}

void allocate(int sz)
{
    // Calculate index in free list
    // to search for block if available
    int n = ceil(log(sz) / log(2));

    // Block available
    if (free_list[n].size() > 0)
    {
        pair<int, int> temp = free_list[n][0];

        // Remove block from free list
        free_list[n].erase(free_list[n].begin());
        cout << "Memory from " << temp.first
             << " to " << temp.second << " allocated"
             << "\n";

        // map starting address with
        // size to make deallocating easy
        mp[temp.first] = temp.second -
                         temp.first + 1;
    }
    else
    {
        int i;
        for(i = n + 1; i < ::size; i++)
        {
            // Find block size greater than request
            if(free_list[i].size() != 0)
                break;
        }

        // If no such block is found
        // i.e., no memory block available
        if (i == ::size)
        {
            cout << "Sorry, failed to allocate memory \n";
        }
        // If found
        else
        {
            pair<int, int> temp;
            temp = free_list[i][0];

            // Remove first block to split it into halves
            free_list[i].erase(free_list[i].begin());
            i--;

            for(; i >= n; i--)
            {
                // Divide block into two halves
                pair<int, int> pair1, pair2;
                pair1 = make_pair(temp.first,
                                  temp.first +
                                  (temp.second -
                                  temp.first) / 2);
                pair2 = make_pair(temp.first +
                                  (temp.second -
                                  temp.first + 1) / 2,
                                  temp.second);

                free_list[i].push_back(pair1);

                // Push them in free list
                free_list[i].push_back(pair2);
                temp = free_list[i][0];

                // Remove first free block to
                // further split
                free_list[i].erase(free_list[i].begin());
            }
            cout << "Memory from " << temp.first
                 << " to " << temp.second
                 << " allocated" << "\n";

            mp[temp.first] = temp.second -
                             temp.first + 1;
        }
    }
}

void deallocate(int start)
{
    if(mp.find(start) == mp.end())
    {
        cout << "Memory at " << start
             << " not allocated \n";
        return;
    }

    // Merge with buddy block if available
    int size = mp[start];
    int buddy, buddy_size, index;
    while(true)
    {
        // Calculate buddy address and size
        buddy = (start % (2 * size) == 0) ? (start + size) : (start - size);
        buddy_size = mp[buddy];

        // Check if buddy exists and is free
        if(mp.find(buddy) != mp.end() && buddy_size == size)
        {
            // Merge the blocks
            index = ceil(log(size) / log(2));
            mp.erase(start);
            mp.erase(buddy);

            // Remove buddy from free list
            free_list[index].erase(remove(free_list[index].begin(),
                                    free_list[index].end(),
                                    make_pair(min(start, buddy), max(start, buddy))),
                                    free_list[index].end());
            
            // Recalculate start and size for next iteration
            start = min(start, buddy);
            size *= 2;
        }
        else
        {
            break;
        }
    }

    // Add merged block to free list
    index = ceil(log(size) / log(2));
    free_list[index].push_back(make_pair(start, start + size - 1));
    cout << "Memory from " << start << " to " << start + size - 1 << " deallocated" << endl;
}

// Driver code
int main()
{
    int total;
    cout << "Enter total memory size: ";
    cin >> total;

    initialize(total);

    while(true)
    {
        int req;
        cout << "Enter memory allocation request (-1 to exit): ";
        cin >> req;
        if(req == -1)
            break;

        allocate(req);
    }

    while(true)
    {
        int dealloc;
        cout << "Enter memory deallocation request (-1 to exit): ";
        cin >> dealloc;
        if(dealloc == -1)
            break;

        deallocate(dealloc);
    }

    return 0;
}

