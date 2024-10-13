#include <iostream>
#include <algorithm>
using namespace std;

struct Process {
    int pid;      // Process ID
    int bt;       // Burst Time
    int at;       // Arrival Time
    int ct;       // Completion Time
    int tat;      // Turnaround Time
    int wt;       // Waiting Time
};

// Function to compare processes according to their arrival time
bool compareArrival(Process a, Process b) {
    return a.at < b.at;
}

// Function to calculate the SJF scheduling
void sjfScheduling(Process proc[], int n) {
    // Sort processes by arrival time
    sort(proc, proc + n, compareArrival);
    
    int time = 0;  // Current time
    int completed = 0;  // Number of completed processes
    
    while (completed != n) {
        int idx = -1;
        int min_bt = 1e9;  // Set initial value for the minimum burst time as infinity

        // Find the process with the shortest burst time that has arrived
        for (int i = 0; i < n; i++) {
            if (proc[i].at <= time && proc[i].bt < min_bt && proc[i].ct == 0) {
                min_bt = proc[i].bt;
                idx = i;
            }
        }
        
        if (idx != -1) {
            // Update the time with the selected process' burst time
            time += proc[idx].bt;

            // Completion time for selected process
            proc[idx].ct = time;

            // Turnaround time = Completion time - Arrival time
            proc[idx].tat = proc[idx].ct - proc[idx].at;

            // Waiting time = Turnaround time - Burst time
            proc[idx].wt = proc[idx].tat - proc[idx].bt;

            // Process is completed
            completed++;
        } else {
            time++;  // If no process has arrived, increment the time
        }
    }
}

// Function to display the results
void displayResults(Process proc[], int n) {
    float total_tat = 0, total_wt = 0;
    
    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << proc[i].pid << "\t" << proc[i].at << "\t" << proc[i].bt << "\t" 
             << proc[i].ct << "\t" << proc[i].tat << "\t" << proc[i].wt << "\n";
             
        total_tat += proc[i].tat;
        total_wt += proc[i].wt;
    }

    cout << "\nAverage Turnaround Time: " << total_tat / n;
    cout << "\nAverage Waiting Time: " << total_wt / n << "\n";
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    Process proc[n];
    
    for (int i = 0; i < n; i++) {
        cout << "Enter Arrival Time and Burst Time for Process " << i + 1 << ": ";
        proc[i].pid = i + 1;
        cin >> proc[i].at >> proc[i].bt;
        proc[i].ct = 0;  // Initialize completion time to 0
    }

    // Call the SJF scheduling function
    sjfScheduling(proc, n);

    // Display the results
    displayResults(proc, n);

    return 0;
}
