#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int id;
    int burst_time;
    int priority;
};

// Function to swap two processes
void swap(Process &a, Process &b) {
    Process temp = a;
    a = b;
    b = temp;
}

int main() {
    int n;
    cout << "Enter Number of Processes: ";
    cin >> n;

    vector<Process> processes(n);

    for(int i = 0; i < n; i++) {
        cout << "Enter Burst Time and Priority Value for Process " << i + 1 << ": ";
        cin >> processes[i].burst_time >> processes[i].priority;
        processes[i].id = i + 1;
    }

    // Sort processes based on priority
    sort(processes.begin(), processes.end(), [](const Process &a, const Process &b) {
        return a.priority < b.priority;
    });

    // Execute processes
    int current_time = 0;
    cout << "\nOrder of Process Execution is:" << endl;
    for(int i = 0; i < n; i++) {
        cout << "P" << processes[i].id << " is executed from " << current_time << " to " << current_time + processes[i].burst_time << endl;
        current_time += processes[i].burst_time;
    }

    // Calculate waiting and turnaround time
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    int wait_time = 0;
    cout << "\nProcess ID\tBurst Time\tWait Time\tTurnaround Time" << endl;
    for(int i = 0; i < n; i++) {
        total_waiting_time += wait_time;
        total_turnaround_time += wait_time + processes[i].burst_time;
        cout << "P" << processes[i].id << "\t\t" << processes[i].burst_time << "\t\t" << wait_time << "\t\t" << wait_time + processes[i].burst_time << endl;
        wait_time += processes[i].burst_time;
    }

    // Calculate average waiting and turnaround time
    float avg_waiting_time = total_waiting_time / (float)n;
    float avg_turnaround_time = total_turnaround_time / (float)n;
    cout << "\nAverage Waiting Time: " << avg_waiting_time << endl;
    cout << "Average Turnaround Time: " << avg_turnaround_time << endl;

    return 0;
}

