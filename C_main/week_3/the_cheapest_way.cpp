#include <stdio.h>
#include <stdlib.h>

int min(int, int, int);
void findMinPath(int **, int, int);

int main() {
    int m, n;
    int **matrix;

    while (scanf("%d %d", &m, &n) != EOF) {
        matrix = (int **) malloc(sizeof(int *) * m);
        for (int i = 0; i < m; i++) {
            matrix[i] = (int *) malloc(sizeof(int) * n);
            for (int j = 0; j < n; j++) {
                scanf("%d", &matrix[i][j]);
            }
        }

        findMinPath(matrix, m, n);
    }

    return 0;
}

int min(int a, int b, int c) {
    if (a <= b && a <= c) return a;
    else if (b <= a && b <= c) return b;
    else return c;
}

void findMinPath(int** matrix, int m, int n) {
    int memo[m][n];

    // initialize memo
    for (int i = 0; i < m; i++){
        for (int j = 1; j < n; j++)
            memo[i][j] = INT_MAX;
        memo[i][0] = matrix[i][0];
    }

    // fill memo
    for (int j = 1; j < n; j++) {
        for (int i = 0; i < m; i++) {
            int moves[3];
            moves[0] = memo[i][j - 1];
            moves[1] = (i > 0) ? memo[i- 1][j - 1] : INT_MAX;
            moves[2] = (i < m - 1) ? memo[i + 1][j - 1] : memo[0][j - 1];

            memo[i][j] = matrix[i][j] + min(moves[0], moves[1], moves[2]);
        }
    }

    // reconstruct path
    int path[m][2];
    int j = n - 1;

    for (int i = m - 1; j >= 0; j--) {
        path[j][0] = i;
        path[j][1] = j;

        int moves[3];
        moves[0] = (j > 0) ? memo[i][j-1] : INT_MAX;
        moves[1] = (i > 0 && j > 0) ? memo[i-1][j-1] : INT_MAX;
        moves[2] = (i < m - 1 && j > 0) ? memo[i+1][j-1] : memo[0][j-1];

        int minMove = min(moves[0], moves[1], moves[2]);
        if (minMove == moves[0]);
        else if (minMove == moves[1]) i--;
        else {i++; i %= m;}
    }

    // print min path
    for (int i = 0; i < n; i++)
        printf("%d ", matrix[path[i][0]][path[i][1]]);
    printf("\n%d\n", memo[m - 1][n - 1]);
}