#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

typedef struct {
    char name;
    int arrival_time, burst_time, priority, completion_time, turnaround_time, waiting_time, remaining_time, start_time;
    bool completed;
} Process;

// Function to calculate completion time for Non-Preemptive Priority Scheduling
void priority_non_preemptive(Process p[], int n) {
    int current_time = 0, completed = 0;

    while (completed != n) {
        int min_index = -1, min_priority = INT_MAX;
        
        // Find the highest-priority process that has arrived
        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].arrival_time <= current_time && p[i].priority < min_priority) {
                min_priority = p[i].priority;
                min_index = i;
            }
        }

        if (min_index == -1) {
            current_time++; // No process is available, increment time
            continue;
        }

        // Process execution
        p[min_index].start_time = current_time; // Start time of process
        p[min_index].completion_time = current_time + p[min_index].burst_time;
        current_time = p[min_index].completion_time;
        p[min_index].completed = true;
        completed++;
    }
}

// Function to calculate completion time for Preemptive Priority Scheduling
void priority_preemptive(Process p[], int n) {
    int current_time = 0, completed = 0, highest_priority_index = -1;

    while (completed != n) {
        int min_priority = INT_MAX;

        // Find the process with the highest priority (lower number) that has arrived
        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= current_time && p[i].remaining_time > 0 && p[i].priority < min_priority) {
                min_priority = p[i].priority;
                highest_priority_index = i;
            }
        }

        if (highest_priority_index == -1) {
            current_time++; // No process is available, increment time
            continue;
        }

        // Execute process for 1 unit time
        if (p[highest_priority_index].remaining_time == p[highest_priority_index].burst_time) {
            p[highest_priority_index].start_time = current_time; // Start time of process
        }

        p[highest_priority_index].remaining_time--;
        current_time++;

        if (p[highest_priority_index].remaining_time == 0) {
            p[highest_priority_index].completion_time = current_time;
            completed++;
        }
    }
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
    printf("\nCustomer\tAT\tBT\tPriority\tST\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%c\t\t%d\t%d\t%d\t\t%d\t%d\t%d\t%d\n", p[i].name, p[i].arrival_time, p[i].burst_time,
               p[i].priority, p[i].start_time, p[i].completion_time, p[i].turnaround_time, p[i].waiting_time);
    }
}

// Function to display Gantt Chart
void print_gantt_chart(Process p[], int n) {
    printf("\nGantt Chart: \n");
    int time = 0;
    
    // Print the person name in the Gantt chart
    for (int i = 0; i < n; i++) {
        printf("| %c ", p[i].name);
    }
    printf("|\n");

    // Print the start time of each process in the Gantt chart
    for (int i = 0; i < n; i++) {
        printf("%d   ", p[i].start_time);
    }
    printf("\n");

    // Print the completion time of each process in the Gantt chart
    for (int i = 0; i < n; i++) {
        printf("%d   ", p[i].completion_time);
    }
    printf("\n");
}

// Main function
int main() {
    Process p[] = {
        {'A', 1, 15, 5, 0, 0, 0, 15, false},
        {'B', 3, 5, 3, 0, 0, 0, 5, false},
        {'C', 4, 12, 1, 0, 0, 0, 12, false},
        {'D', 6, 25, 2, 0, 0, 0, 25, false},
        {'E', 7, 2, 4, 0, 0, 0, 2, false}
    };
    int n = sizeof(p) / sizeof(p[0]);

    // Non-Preemptive Priority Scheduling
    printf("\n--- Non-Preemptive Priority Scheduling ---\n");
    priority_non_preemptive(p, n);
    compute_tat_wt(p, n);
    display_results(p, n);
    compute_avg(p, n);
    print_gantt_chart(p, n);

    // Reset process values for Preemptive Priority Scheduling
    for (int i = 0; i < n; i++) {
        p[i].completion_time = 0;
        p[i].turnaround_time = 0;
        p[i].waiting_time = 0;
        p[i].remaining_time = p[i].burst_time;
        p[i].completed = false;
    }

    // Preemptive Priority Scheduling
    printf("\n--- Preemptive Priority Scheduling ---\n");
    priority_preemptive(p, n);
    compute_tat_wt(p, n);
    display_results(p, n);
    compute_avg(p, n);
    print_gantt_chart(p, n);

    return 0;
}

