#include<bits/stdc++.h>
using namespace std;

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int lcm(int a, int b) {
    int gc = gcd(a, b);
    return (a / gc) * b;
}

int calculateLCM(vector<int>& nums) {
    int result = 1;
    for (int num : nums) {
        result = lcm(result, num);
    }
    return result;
}

int main() {
    int num_tasks;
    cout << "Enter the number of tasks: ";
    cin >> num_tasks;

    vector<int> c(num_tasks), d(num_tasks), p(num_tasks);
    cout << "Enter computation time, deadline, and period for each task:" << endl;
    for (int i = 0; i < num_tasks; i++) {
        cout << "Task " << i + 1 << ":" << endl;
        cout << "Computation time: ";
        cin >> c[i];
        cout << "Deadline: ";
        cin >> d[i];
        cout << "Period: ";
        cin >> p[i];
    }

    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> q;
    int period_lcm = calculateLCM(p);
    cout << "Least Common Multiple of periods: " << period_lcm << endl;

    vector<vector<int>> task;
    for (int i = 0; i < num_tasks; i++) {
        int temp = 0;
        while (temp <= period_lcm) {
            task.push_back({temp + d[i], temp, c[i], i + 1, d[i]}); 
            temp += p[i];
        }
    }
    sort(task.begin(), task.end(), [](const vector<int>& a, const vector<int>& b) {
        return a[1] < b[1];
    });

    int t = 0;
    
    while (!task.empty() || !q.empty()) {
        if (t >= period_lcm) break; 
	while (!task.empty() && task[0][1] <= t) {
            q.push(task[0]);
            task.erase(task.begin());
        }
        t++;

        if (!q.empty()) {
            vector<int> temp = q.top();
            q.pop();
            temp[2]--;
            if (temp[2] != 0)
                q.push(temp);
            cout << t - 1 << "  " << temp[3] << "  " << t << endl;
      } else {
            cout << t - 1 << "  -  " << t << endl;
        }
    }

     return 0;
}
