#include <stdio.h>

typedef struct {
    char name;
    int arrival_time;
    int service_time;
    int start_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
} Person;

void calculateTimes(Person persons[], int n) {
    int current_time = 0;
    for (int i = 0; i < n; i++) {
        // Start time for the person is the maximum of current_time or their arrival time
        persons[i].start_time = (current_time > persons[i].arrival_time) ? current_time : persons[i].arrival_time;
        
        // Completion time is start time + service time
        persons[i].completion_time = persons[i].start_time + persons[i].service_time;
        
        // Calculate waiting time (start_time - arrival_time)
        persons[i].waiting_time = persons[i].start_time - persons[i].arrival_time;
        
        // Calculate turnaround time (completion_time - arrival_time)
        persons[i].turnaround_time = persons[i].completion_time - persons[i].arrival_time;
        
        // Update current time to be the completion time of the current person
        current_time = persons[i].completion_time;
    }
}

void printTable(Person persons[], int n) {
    printf("\nPerson Details Table:\n");
    printf("-------------------------------------------------------------\n");
    printf("| Person | Arrival Time | Start Time | Completion Time | Turnaround Time | Waiting Time |\n");
    printf("-------------------------------------------------------------\n");
    
    for (int i = 0; i < n; i++) {
        printf("|   %c    |     %2d       |     %2d     |      %2d       |       %2d        |      %2d      |\n",
               persons[i].name, persons[i].arrival_time, persons[i].start_time, persons[i].completion_time,
               persons[i].turnaround_time, persons[i].waiting_time);
    }
    printf("-------------------------------------------------------------\n");
}

void printGanttChart(Person persons[], int n) {
    printf("\nGantt Chart:\n");
    for (int i = 0; i < n; i++) {
        printf("| %c ", persons[i].name);
    }
    printf("|\n");

    for (int i = 0; i < n; i++) {
        printf("%d    ", persons[i].completion_time);
    }
    printf("\n");
}

void calculateAverageTimes(Person persons[], int n) {
    int total_waiting_time = 0, total_turnaround_time = 0;
    
    for (int i = 0; i < n; i++) {
        total_waiting_time += persons[i].waiting_time;
        total_turnaround_time += persons[i].turnaround_time;
    }
    
    printf("\nAverage Waiting Time = %.2f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time = %.2f\n", (float)total_turnaround_time / n);
}

int main() {
    Person persons[] = {
        {'A', 0, 15, 0, 0, 0, 0},
        {'B', 2, 10, 0, 0, 0, 0},
        {'C', 5, 3, 0, 0, 0, 0},
        {'D', 6, 6, 0, 0, 0, 0},
        {'E', 7, 5, 0, 0, 0, 0}
    };
    
    int n = sizeof(persons) / sizeof(persons[0]);
    
    // Calculate the start time, completion time, waiting time, and turnaround time for each person
    calculateTimes(persons, n);
    
    // Print the table with details
    printTable(persons, n);
    
    // Print the Gantt chart
    printGanttChart(persons, n);
    
    // Calculate and print average waiting time and average turnaround time
    calculateAverageTimes(persons, n);
    
    return 0;
}

