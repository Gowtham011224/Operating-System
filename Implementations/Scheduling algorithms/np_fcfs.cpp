#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int startTime;
    int endTime;
    int waitingTime;
};

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    // Input process details
    cout << "Enter process id, arrival time, and burst time for each process:\n";
    for (int i = 0; i < n; ++i) {
        cout << "Process " << i +1 << ":\n";
        processes[i].pid=i+1;
        cout << "Arrival Time: ";
        cin >> processes[i].arrivalTime;
        cout << "Burst Time: ";
        cin >> processes[i].burstTime;
    }

    // Sort processes based on arrival time
    sort(processes.begin(), processes.end(), [](const Process &a, const Process &b) {
        return a.arrivalTime < b.arrivalTime;
    });
    float sum=0.0;
    int currentTime = 0;
    cout << "\nGantt Chart:\n";
    cout << "---------------------------------------------\n";
    for (int i = 0; i < n; ++i) {
        cout << "  |  P" << processes[i].pid << "  ";
        processes[i].startTime = max(currentTime, processes[i].arrivalTime);
        processes[i].waitingTime = processes[i].startTime - processes[i].arrivalTime;
        currentTime = processes[i].startTime + processes[i].burstTime;
        processes[i].endTime = currentTime;
	sum+=processes[i].waitingTime;
    }
    cout << "|" << endl;
    cout << "---------------------------------------------\n";

    // Print process details
    cout << "\nProcess Details:\n";
    cout << "---------------------------------------------\n";
    for (const Process &p : processes) {
        cout << "Process " << p.pid << ":\n";
        cout << "Start Time: " << p.startTime << ", End Time: " << p.endTime << ", Waiting Time: " << p.waitingTime << endl;
        cout << "---------------------------------------------\n";
    }
	float awt=sum/n;	
    cout<<"Average Waiting Time : "<< awt <<endl;
    return 0;
}

