#include <stdio.h>
#include <stdlib.h>

#define MAX 10

struct node {
    int data;
    struct node *link;
};

const char *sehirler[] = {
    "A: Istanbul",
    "B: Ankara",
    "C: Izmir",
    "D: Bursa",
    "E: Antalya"
};

struct node *addqueue(struct node *p, int val) {
    struct node *temp;
    if (p == NULL) {
        p = (struct node *)malloc(sizeof(struct node));
        if (p == NULL) {
            exit(0);
        }
        p->data = val;
        p->link = NULL;
    } else {
        temp = p;
        while (temp->link != NULL) {
            temp = temp->link;
        }
        temp->link = (struct node *)malloc(sizeof(struct node));
        temp = temp->link;
        if (temp == NULL) {
            exit(0);
        }
        temp->data = val;
        temp->link = NULL;
    }
    return p;
}

struct node *deleteq(struct node *p, int *val) {
    struct node *temp;
    if (p == NULL) {
        printf("Kuyruk bos\n");
        return NULL;
    }
    *val = p->data;
    temp = p;
    p = p->link;
    free(temp);
    return p;
}

void dfs(int x, int visited[], int adj[][MAX], int n) {
    int j;
    visited[x] = 1;
    printf("Ziyaret edilen dugum: %d (%s)\n", x, sehirler[x]);

    for (j = 0; j < n; j++) {
        if (adj[x][j] == 1 && visited[j] == 0) {
            dfs(j, visited, adj, n);
        }
    }
}

void bfs(int adj[][MAX], int x, int visited[], int n, struct node **p) {
    int y, j;
    *p = addqueue(*p, x);

    do {
        *p = deleteq(*p, &y);
        if (visited[y] == 0) {
            printf("Ziyaret edilen dugum: %d (%s)\n", y, sehirler[y]);
            visited[y] = 1;
            for (j = 0; j < n; j++) {
                if ((adj[y][j] == 1) && (visited[j] == 0)) {
                    *p = addqueue(*p, j);
                }
            }
        }
    } while ((*p) != NULL);
}

int main() {
    int n = 5;
    int i, visited[MAX];
    struct node *start = NULL;

    int adj[MAX][MAX] = {
        {0, 1, 0, 1, 0},
        {1, 0, 1, 0, 1},
        {0, 1, 0, 0, 0},
        {1, 0, 0, 0, 1},
        {0, 1, 0, 1, 0}
    };

    printf("--- DFS Algoritmasi ile (Baslangic: Istanbul) ---\n");
    for (i = 0; i < n; i++)
        visited[i] = 0;

    for (i = 0; i < n; i++) {
        if (visited[i] == 0)
            dfs(i, visited, adj, n);
    }

    printf("\n--- BFS Algoritmasi ile (Baslangic: Istanbul) ---\n");
    for (i = 0; i < n; i++)
        visited[i] = 0;

    for (i = 0; i < n; i++) {
        if (visited[i] == 0)
            bfs(adj, i, visited, n, &start);
    }

    return 0;
}