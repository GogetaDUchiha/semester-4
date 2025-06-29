#include <stdio.h>

struct process {
    int pid;
    int bt;    // Burst time
    int at;    // Arrival time
    int wt;    // Waiting time
    int tat;   // Turnaround time
    int completed;
};

int main() {
    int n, time = 0, completed = 0;
    float total_wt = 0, total_tat = 0;

    struct process p[20];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Arrival Time for process %d: ", p[i].pid);
        scanf("%d", &p[i].at);
        printf("Enter Burst Time for process %d: ", p[i].pid);
        scanf("%d", &p[i].bt);
        p[i].completed = 0;
    }

    while (completed < n) {
        int idx = -1;
        int min_bt = 9999;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && !p[i].completed && p[i].bt < min_bt) {
                min_bt = p[i].bt;
                idx = i;
            }
        }

        if (idx != -1) {
            p[idx].wt = time - p[idx].at;
            p[idx].tat = p[idx].wt + p[idx].bt;
            time += p[idx].bt;
            p[idx].completed = 1;
            completed++;

            total_wt += p[idx].wt;
            total_tat += p[idx].tat;
        } else {
            time++; // if no process is ready, increase time
        }
    }

    printf("\nPID\tAT\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].wt, p[i].tat);
    }

    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);

    return 0;
}
