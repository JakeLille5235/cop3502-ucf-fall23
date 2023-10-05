#include <stdio.h>
#include <stdlib.h>


// global variables
int **bridges;
int *visited;

// prototype
void floodfill(int island, int N);

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    // dynamically allocate memory for bridges and visited array
    bridges = (int **)malloc((N + 1) * sizeof(int *));
    visited = (int *)malloc((N + 1) * sizeof(int));
    for (int i = 0; i <= N; ++i) {
        bridges[i] = (int *)calloc(N + 1, sizeof(int));
        visited[i] = 0;
    }

    // read bridge connections
    for (int i = 0; i < M; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        bridges[a][b] = 1;
        bridges[b][a] = 1; // bridges go both ways
    }

    floodfill(1, N); // start floodfill from island 1

    // check if all islands are connected
    int connected = 1;
    for (int i = 1; i <= N; ++i) {
        if (!visited[i]) {
            connected = 0;
            break;
        }
    }

    // output the result
    if (connected) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }

    // free allocated memory
    for (int i = 0; i <= N; ++i) {
        free(bridges[i]);
    }
    free(bridges);
    free(visited);

    return 0;
}

void floodfill(int island, int N) {
    visited[island] = 1;
    for (int i = 1; i <= N; ++i) {
        if (bridges[island][i] == 1 && !visited[i]) {
            floodfill(i, N);
        }
    }
}
