#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
} Process;

void print_chart(Process p[], int size, int execution_order[]) {
    float total_wt = 0, total_tat = 0, total_rt = 0;

    printf("Gantt Chart: ");
    for (int i = 0; i < size; i++) {
        printf("|   P%d   ", execution_order[i]);
    }
    printf("|\n");

    printf("%-7s %-7s %-7s %-7s %-7s %-7s\n", "PID", "AT", "BT", "WT", "TAT", "RT");
    
    for (int i = 0; i < size; i++) {
        int idx = -1;
        for (int j = 0; j < size; j++) {
            if (p[j].pid == execution_order[i]) {
                idx = j;
                break;
            }
        }
        
        printf("%-7d %-7d %-7d %-7d %-7d %-7d\n",
               p[idx].pid, p[idx].arrival_time, p[idx].burst_time,
               p[idx].waiting_time, p[idx].turnaround_time, p[idx].response_time);
               
        total_wt += p[idx].waiting_time;
        total_tat += p[idx].turnaround_time;
        total_rt += p[idx].response_time;
    }

    printf("\nAverage Waiting Time: %.2f\n", total_wt / size);
    printf("Average Turnaround Time: %.2f\n", total_tat / size);
    printf("Average Response Time: %.2f\n\n", total_rt / size);
}

void FCFS_sort_by_arrival(Process p[], int size){
    for(int i = 0; i < size; i++){
        for(int j = i + 1; j < size; j++){
            if(p[j].arrival_time < p[i].arrival_time){
                Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

void FCFS_execute(Process p[], int size){
    printf(" ----- First Come First Served Executing -----\n");
    FCFS_sort_by_arrival(p, size);
    int current_time = p[0].arrival_time;
    int execution_order[size];

    for (int i = 0; i < size; i++) {
        p[i].waiting_time    = current_time - p[i].arrival_time;
        p[i].response_time   = current_time - p[i].arrival_time;
        p[i].turnaround_time = current_time + p[i].burst_time - p[i].arrival_time;

        current_time += p[i].burst_time;
        execution_order[i] = p[i].pid;
    }
    printf(" ----- First Come First Served End -----\n");
    print_chart(p, size, execution_order);
}

void SJF_sort_by_burst(Process p[], int size){
    for(int i = 0; i < size; i++){
        for(int j = i + 1; j < size; j++){
            if(p[j].burst_time < p[i].burst_time){
                Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
    for(int i = 0; i < size - 1; i++){
        if(p[i].burst_time == p[i+1].burst_time){
            if(p[i].arrival_time < p[i+1].arrival_time) {
                continue;
            }else{
                Process temp = p[i];
                p[i] = p[i+1];
                p[i+1] = temp;
            }
        }
    }
}

void SJF_execute(Process p[], int size) {
    printf(" ----- Shortest Job First Executing -----\n");
    int current_time = 0;
    int completed_count = 0;
    int execution_order[size];
    
    int completed_processes[size];
    for (int i = 0; i < size; i++) {
        completed_processes[i] = 0; 
    }

    while (completed_count < size) {
        Process ready_queue[size];
        int ready_count = 0;

        for (int i = 0; i < size; i++) {
            if (p[i].arrival_time <= current_time && completed_processes[i] == 0) {
                ready_queue[ready_count] = p[i];
                ready_count++;
            }
        }

        if (ready_count > 0) {
            SJF_sort_by_burst(ready_queue, ready_count);

            int exec_idx = -1;
            for (int i = 0; i < size; i++) {
                if (p[i].pid == ready_queue[0].pid) {
                    exec_idx = i;
                    break;
                }
            }

            p[exec_idx].response_time = current_time - p[exec_idx].arrival_time;
            p[exec_idx].waiting_time = p[exec_idx].response_time;
            
            current_time += p[exec_idx].burst_time;
            
            p[exec_idx].turnaround_time = p[exec_idx].waiting_time + p[exec_idx].burst_time;
            
            completed_processes[exec_idx] = 1;
            execution_order[completed_count] = p[exec_idx].pid;
            completed_count++;
        } else {
            current_time++;
        }
    }
    printf(" ----- Shortest Job First End -----\n");
    print_chart(p, size, execution_order);
}


int main() {
    int n;
    printf("Enter the number of processes: ");
    if(scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input.\n");
        return 1;
    }

    Process p[n];
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter the arrival time for process %d: ", i + 1);
        scanf("%d", &p[i].arrival_time);
        printf("Enter the burst time for process %d: ", i + 1);
        scanf("%d", &p[i].burst_time);
    }

    printf("\n");
    
    Process p_fcfs[n];
    for(int i = 0; i < n; i++) p_fcfs[i] = p[i];
    FCFS_execute(p_fcfs, n);

    for (int i = 0; i < n; i++) {
        p[i].waiting_time = 0;
        p[i].turnaround_time = 0;
        p[i].response_time = 0;
    }

    Process p_sjf[n];
    for(int i = 0; i < n; i++) p_sjf[i] = p[i];
    SJF_execute(p_sjf, n);

    return 0;
}