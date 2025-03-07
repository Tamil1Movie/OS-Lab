#include <stdio.h>
#include <stdbool.h>

typedef struct {
    char name;
    int arrival_time, burst_time, remaining_time, completion_time, turnaround_time, waiting_time;
} Process;

// Function to implement Round Robin Scheduling
void round_robin(Process p[], int n, int time_quantum) {
    int current_time = 0, completed = 0;
    bool in_queue[n];
    
    for (int i = 0; i < n; i++) {
        p[i].remaining_time = p[i].burst_time;
        in_queue[i] = false;
    }

    printf("\nGantt Chart (Time Quantum = %d): ", time_quantum);
    
    while (completed < n) {
        bool executed = false;
        for (int i = 0; i < n; i++) {
            if (p[i].remaining_time > 0 && p[i].arrival_time <= current_time) {
                in_queue[i] = true;
                
                printf("| %c (%d) ", p[i].name, current_time);
                
                if (p[i].remaining_time > time_quantum) {
                    current_time += time_quantum;
                    p[i].remaining_time -= time_quantum;
                } else {
                    current_time += p[i].remaining_time;
                    p[i].completion_time = current_time;
                    p[i].remaining_time = 0;
                    completed++;
                }
                
                executed = true;
            }
        }
        
        // If no process was executed, move time forward
        if (!executed) {
            current_time++;
        }
    }
    printf("| %d |\n", current_time);
}

// Function to compute Turnaround Time (TAT) and Waiting Time (WT)
void compute_tat_wt(Process p[], int n) {
    for (int i = 0; i < n; i++) {
        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
        p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
    }
}

// Function to calculate average TAT and WT
void compute_avg(Process p[], int n) {
    float avg_tat = 0, avg_wt = 0;
    for (int i = 0; i < n; i++) {
        avg_tat += p[i].turnaround_time;
        avg_wt += p[i].waiting_time;
    }
    printf("\nAverage Turnaround Time: %.2f", avg_tat / n);
    printf("\nAverage Waiting Time: %.2f\n", avg_wt / n);
}

// Function to display process details
void display_results(Process p[], int n) {
    printf("\nUser\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%c\t%d\t%d\t%d\t%d\t%d\n", p[i].name, p[i].arrival_time, p[i].burst_time,
               p[i].completion_time, p[i].turnaround_time, p[i].waiting_time);
    }
}

// Main function
int main() {
    Process p[] = {
        {'A', 0, 20, 0, 0, 0, 0},
        {'B', 1, 7, 0, 0, 0, 0},
        {'C', 3, 3, 0, 0, 0, 0},
        {'D', 6, 12, 0, 0, 0, 0},
        {'E', 8, 8, 0, 0, 0, 0}
    };
    int n = sizeof(p) / sizeof(p[0]);

    // Round Robin with time quantum = 4
    printf("\n--- Round Robin Scheduling with Time Quantum = 4 ---\n");
    round_robin(p, n, 4);
    compute_tat_wt(p, n);
    display_results(p, n);
    compute_avg(p, n);

    // Reset process values for Time Quantum = 2
    for (int i = 0; i < n; i++) {
        p[i].completion_time = 0;
        p[i].turnaround_time = 0;
        p[i].waiting_time = 0;
        p[i].remaining_time = p[i].burst_time;
    }

    // Round Robin with time quantum = 2
    printf("\n--- Round Robin Scheduling with Time Quantum = 2 ---\n");
    round_robin(p, n, 2);
    compute_tat_wt(p, n);
    display_results(p, n);
    compute_avg(p, n);

    return 0;
}

