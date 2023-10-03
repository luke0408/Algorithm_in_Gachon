#include <stdio.h>

#define MAX_WON 100000
#define MAX_N 100

int costs[MAX_N];
int nCosts = 0;

int sumCosts() {
    int sum = 0;
    for (int i = 0; i < nCosts; i++) sum += costs[i];
    return sum;
}

int main() {
    while(1) {
        scanf("%d", &nCosts);
        if (nCosts == 0) break;
        if (nCosts < 1 || nCosts > MAX_N) continue;

        int i = 0, j = 0;
        for (i = 0; i < nCosts; i++) {
            scanf("%d", &costs[i]);
            if (costs[i] < 0 || costs[i] > MAX_WON) i--;
        }

        int sum = sumCosts();
        int avg = sum / nCosts;
        int taken = 0, given = 0;

        for (j = 0; j < nCosts; j++) {
            costs[j] < avg ? taken += -(costs[j] - avg) : given += costs[j] - avg;
        }

        int min = taken < given ? taken : given;
        int flag = nCosts % 2 == 0 ? (nCosts / 2) : ((nCosts - 1) / 2);

        printf("$ %d\n", flag > 2 ? min - 10 : min);
    }
}