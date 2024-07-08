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

int check(vector<int> a, vector<int> b) {
    return a[2] < b[2];
}

int calculateLCM(vector<int>& nums) {
    int result = 1;
    for (int num : nums) {
        result = lcm(result, num);
    }
    return result;
}

int main() {
	
    int numTasks;
    cout << "Enter the number of tasks: ";
    cin >> numTasks;

    vector<int> periods(numTasks);
    vector<int> executionTimes(numTasks);
    for (int i = 0; i < numTasks; i++) {
        cout << "Enter period and execution time for task " << i + 1 << ": ";
        cin >> periods[i] >> executionTimes[i];
    }

    // Calculate total utilization
    double totalUtilization = 0.0;
    for (int i = 0; i < numTasks; i++) {
        totalUtilization += (double)executionTimes[i] / periods[i];
    }

    // Calculate upper bound for RMS
    double upperBound = numTasks * (pow(2.0, 1.0 / numTasks) - 1);

    cout << "Total utilization: " << totalUtilization << endl;
    cout << "Upper bound for RMS: " << upperBound << endl;

    // Check schedulability
    if (totalUtilization <= upperBound) {
        cout << "\nAs " << totalUtilization << " <= " << upperBound << ",";
        cout << "\nThe System is surely Schedulable according to Rate Monotonic Scheduling (RMS)." << endl;
    } else {
        cout << "\nNot Sure that whether it can be schedulable according to RMS....." << endl;
        return 1;
    }

    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> q;
    int period_lcm = calculateLCM(periods);
    cout << "LCM of periods: " << period_lcm << endl;

    vector<vector<int>> task;
    vector<vector<int>> order;
    for (int i = 0; i < numTasks; i++) {
        order.push_back({periods[i], i});
    }
    sort(order.begin(), order.end());
    for (int i = 0; i < numTasks; i++) {
        int te = 0;
        int ind = order[i][1];
        while (te != period_lcm) {
            task.push_back({1 + i, ind, te, executionTimes[ind]});
            te += periods[ind];
        }
    }
    sort(task.begin(), task.end(), check);

    int t = 0;
    while (!task.empty() || !q.empty()) {
        while (!task.empty() && task[0][2] <= t) {
            q.push(task[0]);
            task.erase(task.begin());
        }
        t++;
        if (!q.empty()) {
            vector<int> temp = q.top();
            q.pop();
            temp[3]--;
            if (temp[3] != 0)
                q.push(temp);
            cout << t - 1 << "  " << temp[1] << "  " << t << endl;
        } else
            cout << t - 1 << "  -  " << t << endl;
    }
    return 0;
}

