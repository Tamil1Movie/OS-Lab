#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

typedef struct {
    char name;
    int arrival_time, burst_time, completion_time, turnaround_time, waiting_time, remaining_time;
    bool completed;
} Process;

// Function to calculate completion time for Non-Preemptive SJF
void sjf_non_preemptive(Process p[], int n) {
    int current_time = 0, completed = 0;
    
    while (completed != n) {
        int min_index = -1, min_bt = INT_MAX;
        
        // Find the process with the shortest burst time that has arrived
        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].arrival_time <= current_time && p[i].burst_time < min_bt) {
                min_bt = p[i].burst_time;
                min_index = i;
            }
        }

        if (min_index == -1) {
            current_time++;  // No process is available, so increment time
            continue;
        }

        // Process execution
        p[min_index].completion_time = current_time + p[min_index].burst_time;
        current_time = p[min_index].completion_time;
        p[min_index].completed = true;
        completed++;
    }
}

// Function to calculate completion time for Preemptive SJF (SRTF)
void sjf_preemptive(Process p[], int n) {
    int current_time = 0, completed = 0, shortest = -1, min_rt = INT_MAX;

    while (completed != n) {
        // Find the process with the shortest remaining time
        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= current_time && p[i].remaining_time > 0 && p[i].remaining_time < min_rt) {
                shortest = i;
                min_rt = p[i].remaining_time;
            }
        }

        if (shortest == -1) {
            current_time++;
            continue;
        }

        // Execute process
        p[shortest].remaining_time--;
        current_time++;

        if (p[shortest].remaining_time == 0) {
            p[shortest].completion_time = current_time;
            completed++;
            min_rt = INT_MAX; // Reset min remaining time for next selection
        }
    }
}

// Function to compute TAT and WT
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
    printf("\nCustomer\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%c\t\t%d\t%d\t%d\t%d\t%d\n", p[i].name, p[i].arrival_time, p[i].burst_time,
               p[i].completion_time, p[i].turnaround_time, p[i].waiting_time);
    }
}

// Function to display Gantt Chart
void print_gantt_chart(Process p[], int n) {
    printf("\nGantt Chart: ");
    for (int i = 0; i < n; i++) {
        printf("| %c ", p[i].name);
    }
    printf("|\n");
}

// Main function
int main() {
    Process p[] = {
        {'A', 0, 10, 0, 0, 0, 10, false},
        {'B', 1, 7, 0, 0, 0, 7, false},
        {'C', 2, 2, 0, 0, 0, 2, false},
        {'D', 4, 5, 0, 0, 0, 5, false},
        {'E', 6, 20, 0, 0, 0, 20, false}
    };
    int n = sizeof(p) / sizeof(p[0]);

    // Non-preemptive SJF
    printf("\n--- Non-Preemptive SJF ---\n");
    sjf_non_preemptive(p, n);
    compute_tat_wt(p, n);
    display_results(p, n);
    compute_avg(p, n);
    print_gantt_chart(p, n);

    // Reset process values for preemptive SJF
    for (int i = 0; i < n; i++) {
        p[i].completion_time = 0;
        p[i].turnaround_time = 0;
        p[i].waiting_time = 0;
        p[i].remaining_time = p[i].burst_time;
        p[i].completed = false;
    }

    // Preemptive SJF (SRTF)
    printf("\n--- Preemptive SJF (SRTF) ---\n");
    sjf_preemptive(p, n);
    compute_tat_wt(p, n);
    display_results(p, n);
    compute_avg(p, n);
    print_gantt_chart(p, n);

    return 0;
}

