#include <stdio.h>
#include <limits.h>

#define MAX 100

int n;
int at[MAX], bt[MAX], pr[MAX];

// ---------------- Utility ----------------
void reset(int rt[]) {
    for (int i = 0; i < n; i++){
        rt[i] = bt[i];
    }
}

void print(int ct[]) {
    for (int i = 0; i < n; i++)
        printf("P%d CT=%d\n", i+1, ct[i]);
}

// ---------------- SJF NP ----------------
void sjf_np() {
    int ct[MAX], done[MAX] = {0};
    int time = 0, completed = 0;

    while (completed < n) {
        int idx = -1, min = INT_MAX;

        for (int i = 0; i < n; i++){
            if (!done[i] && at[i] <= time && bt[i] < min){
                min = bt[i];
                idx = i;
            }
            
            if (idx == -1) { 
                time++; 
                continue; 
            }
        }

        time += bt[idx];
        ct[idx] = time;
        done[idx] = 1;
        completed++;
    }

    print(ct);
}

// ---------------- SJF P ----------------
void sjf_p() {
    int ct[MAX], rt[MAX];
    reset(rt);

    int time = 0, completed = 0;

    while (completed < n) {
        int idx = -1, min = INT_MAX;

        for (int i = 0; i < n; i++)
            if (at[i] <= time && rt[i] > 0 && rt[i] < min)
                min = rt[i], idx = i;

        if (idx == -1) { time++; continue; }

        rt[idx]--;
        time++;

        if (rt[idx] == 0)
            ct[idx] = time, completed++;
    }

    print(ct);
}

// ---------------- Priority NP ----------------
void priority_np() {
    int ct[MAX], done[MAX] = {0};
    int time = 0, completed = 0;

    while (completed < n) {
        int idx = -1, best = INT_MAX;

        for (int i = 0; i < n; i++)
            if (!done[i] && at[i] <= time && pr[i] < best)
                best = pr[i], idx = i;

        if (idx == -1) { time++; continue; }

        time += bt[idx];
        ct[idx] = time;
        done[idx] = 1;
        completed++;
    }

    print(ct);
}

// ---------------- Priority P ----------------
void priority_p() {
    int ct[MAX], rt[MAX];
    reset(rt);

    int time = 0, completed = 0;

    while (completed < n) {
        int idx = -1, best = INT_MAX;

        for (int i = 0; i < n; i++)
            if (at[i] <= time && rt[i] > 0 && pr[i] < best)
                best = pr[i], idx = i;

        if (idx == -1) { time++; continue; }

        rt[idx]--;
        time++;

        if (rt[idx] == 0)
            ct[idx] = time, completed++;
    }

    print(ct);
}

// ---------------- Round Robin ----------------
void rr(int tq) {
    int ct[MAX], rt[MAX];
    reset(rt);

    int time = 0, done;

    do {
        done = 1;

        for (int i = 0; i < n; i++) {
            if (rt[i] > 0 && at[i] <= time) {
                done = 0;

                if (rt[i] > tq) {
                    time += tq;
                    rt[i] -= tq;
                } else {
                    time += rt[i];
                    rt[i] = 0;
                    ct[i] = time;
                }
            }
        }

        if (done) time++;

    } while (!done);

    print(ct);
}

// ---------------- MAIN ----------------
int main() {
    n = 3;
    at[0] = 0; bt[0] = 16; pr[0] = 2;
    at[1] = 2; bt[1] = 8;  pr[1] = 3;
    at[2] = 4; bt[2] = 3;  pr[2] = 1;

    printf("SJF Non-Preemptive\n");
    sjf_np();

    printf("\nSJF Preemptive\n");
    sjf_p();

    printf("\nPriority Non-Preemptive\n");
    priority_np();

    printf("\nPriority Preemptive\n");
    priority_p();

    printf("\nRound Robin (TQ=2)\n");
    rr(2);

    return 0;
}