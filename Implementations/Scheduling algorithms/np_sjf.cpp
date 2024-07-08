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
        cout << "Process " << i + 1 << ":\n";
        processes[i].pid = i + 1;
        cout << "Arrival Time: ";
        cin >> processes[i].arrivalTime;
        cout << "Burst Time: ";
        cin >> processes[i].burstTime;
    }

    // Sort processes based on arrival time
    sort(processes.begin(), processes.end(), [](const Process &a, const Process &b) {
        return a.arrivalTime < b.arrivalTime;
    });

    int currentTime = 0;
    int totalWaitingTime = 0;
    vector<Process> executedProcesses; // Store executed processes

    cout << "\nGantt Chart:\n";
    cout << "---------------------------------------------\n";

    while (!processes.empty()) {
        // Find the process with the shortest burst time among arrived processes
        auto shortest = min_element(processes.begin(), processes.end(), [&](const Process &a, const Process &b) {
            return a.burstTime < b.burstTime && a.arrivalTime <= currentTime;
        });

        if (shortest->arrivalTime > currentTime) {
            currentTime = shortest->arrivalTime;
        }

        cout << "  |  P" << shortest->pid << "  ";
        shortest->startTime = currentTime;
        shortest->waitingTime = currentTime - shortest->arrivalTime;
        currentTime += shortest->burstTime;
        shortest->endTime = currentTime;
        totalWaitingTime += shortest->waitingTime;

        executedProcesses.push_back(*shortest); // Store executed process

        // Remove the executed process
        processes.erase(shortest);
    }
    cout << "|" << endl;
    cout << "---------------------------------------------\n";

    cout << "\nProcess Details:\n";
    cout << "---------------------------------------------\n";
    for (const Process &p : executedProcesses) {
        cout << "Process " << p.pid << ":\n";
        cout << "Start Time: " << p.startTime << ", End Time: " << p.endTime << ", Waiting Time: " << p.waitingTime << endl;
        cout << "---------------------------------------------\n";
    }

    return 0;
}

