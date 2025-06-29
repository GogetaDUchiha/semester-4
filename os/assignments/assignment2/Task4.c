#include <stdio.h>

struct process {
    int pid;
    int at; // Arrival Time
    int bt; // Burst Time
    int bt_left;
    int priority;
    int ct; // Completion Time
    int tat;
    int wt;
    int completed;
};

int main() {
    int n, i, time = 0, completed = 0, min_priority, idx;
    struct process p[20];
    float total_tat = 0, total_wt = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Arrival Time for process %d: ", p[i].pid);
        scanf("%d", &p[i].at);
        printf("Enter Burst Time for process %d: ", p[i].pid);
        scanf("%d", &p[i].bt);
        printf("Enter Priority for process %d (smaller = higher priority): ", p[i].pid);
        scanf("%d", &p[i].priority);
        p[i].bt_left = p[i].bt;
        p[i].completed = 0;
    }

    while (completed < n) {
        min_priority = 9999;
        idx = -1;

        for (i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].completed == 0 && p[i].priority < min_priority && p[i].bt_left > 0) {
                min_priority = p[i].priority;
                idx = i;
            }
        }

        if (idx != -1) {
            p[idx].bt_left--;
            time++;

            if (p[idx].bt_left == 0) {
                p[idx].completed = 1;
                p[idx].ct = time;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;

                total_tat += p[idx].tat;
                total_wt += p[idx].wt;
                completed++;
            }
        } else {
            time++; // no process is ready, just wait
        }
    }

    printf("\nPID\tAT\tBT\tPriority\tWT\tTAT\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].priority, p[i].wt, p[i].tat);
    }

    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);

    return 0;
}
