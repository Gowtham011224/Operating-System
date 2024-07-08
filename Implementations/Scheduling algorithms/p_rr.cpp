#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include<stdio.h>
using namespace std;
int main() {
    // vector<int> at = {0, 1, 3,5,6};
    // vector<int> bt = {8, 6, 3,4,2};
    // int p = at.size();
        int p;
        vector<int> at;
        vector<int> bt;
        cout<<"Enter Number of Process : ";
        cin>>p;
        for(int i=0;i<p;i++)
        {
            int a,b;
            cout<<"Enter Arival Time & Burst Time : ";
            cin>>a>>b;
            at.push_back(a);
            bt.push_back(b);
        }
    vector<int> ct(p);
    vector<int> wt(p);
    vector<int> tat(p);
    queue<pair<int, int>> q; 
    vector<vector<int>> order;
    for(int i = 0; i < p; i++) 
    {
        order.push_back({at[i], i});
    }
    sort(order.begin(), order.end());

    int t = 0;
    int tq;
    cout << "Enter Time Quantum: ";
    cin >> tq;
    cout<<"Gantts chart :"<<endl;
    cout<<t<<"  ";

    while (!q.empty() || !order.empty()) 
    {
        while (!order.empty() && order.front()[0] <= t) 
        {
            int idx = order.front()[1];
            q.push({bt[idx], idx});
            order.erase(order.begin());
        }
        if (!q.empty()) 
        {
            auto [burst, idx] = q.front();
            q.pop();

            int execution_time = min(burst, tq);
            t += execution_time;
            burst -= execution_time;

            if (burst == 0) 
            {
                ct[idx] = t;
                tat[idx] = ct[idx] - at[idx];
                wt[idx] = tat[idx] - bt[idx];
            } 
            else 
            {
                while (!order.empty() && order.front()[0] <= t) 
                {
                    int idx = order.front()[1];
                    q.push({bt[idx], idx});
                    order.erase(order.begin());
                }
                q.push({burst, idx});
            }
            cout<<"P"<<idx<< "   "<<t<<"  ";
        } 
        else 
        {
            t = order.front()[0];
            cout<<t<<"   ";
        }
    }
    cout<<endl;
    int atat = 0, awt = 0;
    cout<<"Process  CT     WT      TAT  "<<endl;
    for(int i = 0; i < bt.size(); i++) {
        atat += tat[i];
        awt += wt[i]; 
        printf("  P%d%7d%6d%9d\n",i+1,ct[i],wt[i],tat[i]);
    }

    cout << "Average TAT: " << 1.0 * atat / p << endl;
    cout << "Average WT: " << 1.0 * awt / p << endl;

    return 0;
}
